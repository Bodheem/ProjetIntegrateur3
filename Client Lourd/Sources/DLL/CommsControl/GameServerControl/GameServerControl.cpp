//////////////////////////////////////////////////////////////////////////////
/// @file ServerControl.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////
#undef UNICODE
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "GameServerControl.h"
#include <windows.h>
#include <winsock2.h>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <future>
	#ifndef SERVERTESTER
#include "../../../Serveur/SharedFiles/AbstractSocketV2.h"
#include "../../../Serveur/SharedFiles/IP.h"
#else
#include "../../../../../Serveur/SharedFiles/AbstractSocketV2.h"
#include "../../../../../Serveur/SharedFiles/IP.h"
#endif
#include "../../Application/FacadeJeu.h"
#include "../Application/FacadeModele.h"

// link with Ws2_32.lib
#pragma comment( lib, "ws2_32.lib" )

////////////////////////////////////
#pragma region // Constructeur / Destructeur / Singleton Pointer
/// Initialize Static pointer
GameServerControl* GameServerControl::GameServerControlPointer = nullptr;
/// Static function to destroy pointer to main form
void GameServerControl::deletePointer()
{
	if (GameServerControlPointer != nullptr)
		delete GameServerControlPointer;
	GameServerControlPointer = nullptr;
}
/// Static function to obtain pointer to main form
GameServerControl* GameServerControl::getPointer()
{
	if (GameServerControlPointer == nullptr)
		GameServerControlPointer = new GameServerControl();
	return GameServerControlPointer;
}
/// Constructeur
GameServerControl::GameServerControl()
{
	serverData_ = GameServerData::getPointer();
	GameServerControlPointer = this;
}
/// Destructeur
GameServerControl::~GameServerControl()
{
	killAllThreads();

	AbstractSocket::TCPSocket* a = TCPSocketList_[5035];
	AbstractSocket::TCPSocket* b = TCPSocketList_[5045];
	AbstractSocket::UDPSocket* c = UDPSocketList_[5040];
	AbstractSocket::UDPSocket* d = UDPSocketList_[5050];
	TCPSocketList_.clear();
	UDPSocketList_.clear();
	delete a, b, c, d;

	/*while (!TCPSocketList_.empty())
	{
		auto itr = TCPSocketList_.begin();
		delete itr->second;
	}
	while (!UDPSocketList_.empty())
	{
		auto itr = UDPSocketList_.begin();
		delete itr->second;
	}*/
	/*while (!TCPSocketList_.empty())
	{
		auto itr = TCPSocketList_.begin();
		AbstractSocket::TCPSocket* sock = itr->second;
		itr->second = nullptr;
		delete sock;
		TCPSocketList_.erase(itr);
	}
	while (!UDPSocketList_.empty())
	{
		auto itr = UDPSocketList_.begin();
		AbstractSocket::UDPSocket* sock = itr->second;
		itr->second = nullptr;
		delete sock;
		UDPSocketList_.erase(itr);
	}*/

	delete serverData_;
	GameServerControlPointer = nullptr;
}

#pragma endregion

////////////////////////////////////
#pragma region // Utility Functions
/// Completely reinitialize multiplayer server
void GameServerControl::resetGameServer()
{

}
/// Print timestamp to console
void GameServerControl::printTimestamp(std::string message)
{
	time_t timestamp;
	time(&timestamp);
	struct tm now;
	localtime_s(&now, &timestamp);
	int heure_ = now.tm_hour;
	int minute_ = now.tm_min;
	int seconde_ = now.tm_sec;
	std::string str = "";
	std::string spacers = "";
	// Write Timestamp
	str += std::to_string(heure_) + "h." + std::to_string(minute_)
		+ "m." + std::to_string(seconde_) + "s.";
	spacers += ((heure_ < 10) ? " " : "");
	spacers += ((minute_ < 10) ? " " : "");
	spacers += ((seconde_ < 10) ? " " : "");
	str += spacers + " " + message;
	std::cout << str;
}
/// Initialise le serveur de jeu
void GameServerControl::startServer(int numberOfPlayers, std::string mapName)
{
	serverData_->configureGame(numberOfPlayers, mapName);
	if (!initializeCommunications())
		return;
	serverData_->campaignIndex_ = 0;
}
/// Kill all threads
void GameServerControl::killAllThreads()
{
	GLOBAL_KILL_THREAD_ORDER = true;
	while (!THREAD_COMMS_DEAD)
		Sleep(50);
	while (!THREAD_STATUS_DEAD)
		Sleep(50);
	while (!THREAD_SNAPSHOT_DEAD)
		Sleep(50);
	while (!THREAD_CONNEC_DEAD)
		Sleep(50);
}

#pragma endregion

////////////////////////////////////
#pragma region // Multithreading safety
/// Obtain Secure GameServerData Lock
void GameServerControl::obtainSecureLock(std::string lastCaller)
{
	serverData_->safetyMutex_.lock();
	serverData_->safetyMutexIsLocked_ = true;
	serverData_->safetyMutexLastCaller = lastCaller;
}
/// Release Secure GameServerData Lock
void GameServerControl::releaseSecureLock()
{
	serverData_->safetyMutex_.unlock();
	serverData_->safetyMutexIsLocked_ = false;
	serverData_->safetyMutexLastCaller = "";
}

#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // Communication Threads

// Thread de communication 1: TCP 5035
// Communication passive qui attend une connexion
// Gère l'état de la partie et permet de la débuter et d'envoyer des ordres de contrôles aux joueurs
int MultiThreadCommunicationHandling(AbstractSocket::TCPSocket* sd_, GameServerControl* serverControl_)
{
	// Regulièrement, envoyer "PREP" jusqu'à ce que tout les joueurs soient connectés 
	// ET qu'on aie envoyer un dernier PREP
	// ET que la partie roule depuis 2 SSTICK, envoyer "GO"
	// Attendre les conditions de fin de partie puis envoyer le message correspondant
	serverControl_->THREAD_COMMS_DEAD = false;
	int timeDelta = 0;
	auto then = std::chrono::steady_clock::now();
	sockaddr_in sinRemote;
	int nAddrSize = sizeof(sinRemote);
	for (;;)
	{
		// Vérification pour l'ordre d'éxecution des threads
		if (serverControl_->GLOBAL_KILL_THREAD_ORDER)
		{
			serverControl_->THREAD_COMMS_DEAD = true;
			return 0;
		}

		// Vérifie si une connection est en attente
		fd_set readSet;
		FD_ZERO(&readSet);
		FD_SET(sd_->socket_, &readSet);
		timeval timeout;
		timeout.tv_sec = 0;  // Zero timeout (poll)
		timeout.tv_usec = 50000;
		AbstractSocket::TCPSocket* socketTemp;
		// Adresse IP
		std::string IPstr;
		// Valeurs de l'adresse IP
		int a, b, c, d;
		// Connection en attente
		int selectReturn = select((int)sd_->socket_, &readSet, NULL, NULL, &timeout);
		if (selectReturn >= 1)
		{
			// Create a SOCKET for accepting incoming requests.
			// Accept the connection in  blocking
			socketTemp = new AbstractSocket::TCPSocket(accept(sd_->socket_, (sockaddr*)&sinRemote, &nAddrSize), sd_->port_);
			if (socketTemp->socket_ != INVALID_SOCKET) 
			{
				IPstr = inet_ntoa(sinRemote.sin_addr);
				a = sinRemote.sin_addr.S_un.S_un_b.s_b1;
				b = sinRemote.sin_addr.S_un.S_un_b.s_b2;
				c = sinRemote.sin_addr.S_un.S_un_b.s_b3;
				d = sinRemote.sin_addr.S_un.S_un_b.s_b4;
			}
			else 
			{
				delete socketTemp;
				if (serverControl_->serverData_->getGameStatus(0) == serverControl_->serverData_->etatPartieDEBUT ||
					serverControl_->serverData_->getGameStatus(0) == serverControl_->serverData_->etatPartieSTART || 
					serverControl_->serverData_->getGameStatus(0) == serverControl_->serverData_->etatPartieGAME)
				{
					// Calcule l'avancement du temps et gère les déconnexions des joueurs
					auto now = std::chrono::steady_clock::now();
					timeDelta = (int)std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count();
					then = now;
					serverControl_->serverData_->updatePlayerTimeouts(timeDelta);
				}
				continue;
			}
			//SOCKET socket = (SOCKET)sd_->socket_;
		}
		else // Aucune connection en attente
		{
			// Timeout, no one's here
			if (selectReturn == 0)
			{
				if (serverControl_->serverData_->getGameStatus(0) == serverControl_->serverData_->etatPartieDEBUT ||
					serverControl_->serverData_->getGameStatus(0) == serverControl_->serverData_->etatPartieSTART ||
					serverControl_->serverData_->getGameStatus(0) == serverControl_->serverData_->etatPartieGAME)
				{
					// Calcule l'avancement du temps et gère les déconnexions des joueurs
					auto now = std::chrono::steady_clock::now();
					timeDelta = (int)std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count();
					then = now;
					serverControl_->serverData_->updatePlayerTimeouts(timeDelta);
				}
			}
			else // Some Socket Error
			{
				int err = WSAGetLastError();
				std::cout << "Erreur dans la connexion initiale! Select err no: " << err << std::endl;
			}
			continue;
		}

		// Préléminaire: Obtenir les infos de l'utilisateur
		sockaddr_in peeraddr;
		int size = sizeof(peeraddr);
		getsockname(socketTemp->socket_, (struct sockaddr *)&peeraddr, &size);
		//struct sockaddr_in *s = (struct sockaddr_in *)&peeraddr;
		std::string port = std::to_string(ntohs(peeraddr.sin_port));
		//std::cout << "Connection acceptee de : " << IPstr << ":" << port << "." << std::endl;
		
		// IP du joueur
		IP* playerIP = new IP(a, b, c, d);

		// No du joueur
		int player = serverControl_->serverData_->getPlayerByIP(*playerIP);
		// Reset le timeout du joueur
		serverControl_->serverData_->resetPlayerTimeout(player);
		// Etat de la partie pour le joueur
		std::string etatGame = serverControl_->serverData_->getGameStatus(player);

		// Étape 1: Envoie de l'état de la partie aux joueur
		if (!AbstractSocket::SendString(socketTemp, etatGame))
		{
			delete socketTemp;
			delete playerIP;
			continue;
		}

		// Étape 2: Attente d'une reponse des joueurs en fonction de l'état de jeu
		if (etatGame == serverControl_->serverData_->etatPartieDEBUT)
		{
			std::string packagein;
			if (!AbstractSocket::ReceiveString(socketTemp, 5, packagein))
			{
				delete socketTemp;
				delete playerIP;
				continue;
			}
			if (FacadeModele::obtenirInstance()->getPause())
				serverControl_->serverData_->setPlayerReady(1, true);
			else
				serverControl_->serverData_->setPlayerReady(1, false);

			if (packagein == "RDY_2")
				serverControl_->serverData_->setPlayerReady(2, true);
			if (packagein == "RDY_3")
				serverControl_->serverData_->setPlayerReady(3, true);
			if (packagein == "RDY_4")
				serverControl_->serverData_->setPlayerReady(4, true);
			if (packagein == "NOT_2")
				serverControl_->serverData_->setPlayerReady(2, false);
			if (packagein == "NOT_3")
				serverControl_->serverData_->setPlayerReady(3, false);
			if (packagein == "NOT_4")
				serverControl_->serverData_->setPlayerReady(4, false);

			if (serverControl_->serverData_->allPlayersReady())
			{
				serverControl_->serverData_->setGameStatus(serverControl_->serverData_->etatPartieSTART);
				serverControl_->serverData_->setPlayerReady(2, false);
				serverControl_->serverData_->setPlayerReady(3, false);
				serverControl_->serverData_->setPlayerReady(4, false);
			}
		}
		else if (etatGame == serverControl_->serverData_->etatPartieSTART)
		{
			std::string packagein;
			if (!AbstractSocket::ReceiveString(socketTemp, 5, packagein))
			{
				delete socketTemp;
				delete playerIP;
				continue;
			}
			if (FacadeModele::obtenirInstance()->getPause())
				serverControl_->serverData_->setPlayerReady(1, true);
			else
				serverControl_->serverData_->setPlayerReady(1, false);

			if (packagein == "GO__2")
				serverControl_->serverData_->setPlayerReady(2, true);
			if (packagein == "GO__3")
				serverControl_->serverData_->setPlayerReady(3, true);
			if (packagein == "GO__4")
				serverControl_->serverData_->setPlayerReady(4, true);
			if (packagein == "NO__2")
				serverControl_->serverData_->setPlayerReady(2, false);
			if (packagein == "NO__3")
				serverControl_->serverData_->setPlayerReady(3, false);
			if (packagein == "NO__4")
				serverControl_->serverData_->setPlayerReady(4, false);

			if (serverControl_->serverData_->allPlayersReady())
			{
				serverControl_->serverData_->setGameStatus(serverControl_->serverData_->etatPartieGAME);
			}
		}
		else if (etatGame == serverControl_->serverData_->etatPartieGAME ||
			etatGame == serverControl_->serverData_->etatJoueurMORT )
		{
			// Vérifier si tout les joueurs ont gagnés
			if (serverControl_->serverData_->allPlayersWon())
			{
				std::cout << "DETECTED ALL PLAYERS WON" << std::endl;
				serverControl_->serverData_->setGameStatus(serverControl_->serverData_->etatPartieWIN);
			}
			// Vérifier si tout les joueurs ont perdus
			if (serverControl_->serverData_->allPlayersDead())
			{
				std::cout << "DETECTED ALL PLAYERS LOST" << std::endl;
				serverControl_->serverData_->setGameStatus(serverControl_->serverData_->etatPartieLOSE);
			}
			// TODO Handling de la perte des joueurs, des scores maybe, etc
		}
		else if (etatGame == serverControl_->serverData_->etatPartieWIN)
		{
			std::cout << "ETAT PARTIE EST WIN" << std::endl;
			// TODO handle next map in campaign maybe
			// Its in serverControl_->serverData_->incrementCampaignIndex
		}
		else if (etatGame == serverControl_->serverData_->etatPartieLOSE)
		{
			std::cout << "ETAT PARTIE EST LOSE" << std::endl;
			// TODO kick to menu
		}

		
		// Nettoyage
		delete socketTemp;
		delete playerIP;
	}
	serverControl_->THREAD_COMMS_DEAD = true;
	return 0;
}

// Thread de communication 2: UDP 5040
// Communication active vers les joueurs
// Envoie aux 50 ms un SnapShot de la map actuelle pour synchronisé
// la partie avec les joueurs
int MultiThreadSnapShotHandling(AbstractSocket::UDPSocket* sd_, GameServerControl* serverControl_)
{
	serverControl_->THREAD_SNAPSHOT_DEAD = false;
	for (;;)
	{
		// Vérification pour l'ordre d'éxecution des threads
		if (serverControl_->GLOBAL_KILL_THREAD_ORDER)
		{
			serverControl_->THREAD_SNAPSHOT_DEAD = true;
			return 0;
		}
		std::string etatpartie = serverControl_->serverData_->getGameStatus(0);
		if (etatpartie == serverControl_->serverData_->etatPartieDEBUT)
		{
			// Nothing, keep sleeping
			Sleep(200);
			continue;
		}
		else if (etatpartie == serverControl_->serverData_->etatPartieSTART)
		{
			// Nothing, keep sleeping
			Sleep(200);
			continue;
		}
		else if (etatpartie == serverControl_->serverData_->etatPartieGAME)
		{
			// à intervalle régulier
			Sleep(serverControl_->SNAPSHOT_REFRESH_TIME);

			// Step 2: Obtenir un string contenant SnapShot
			std::string message = FacadeJeu::createSnapshot();

			// Step 3: Envoyer à chaque joueur
			for (auto each : serverControl_->serverData_->getAllPlayers())
				if (!AbstractSocket::SendStringPackage(sd_, message, each))
				{
					// Refresh socket
					delete sd_;
					sd_ = new AbstractSocket::UDPSocket(5040);
					// Less rigorous error checking required
					continue;
				}
		}
		else if (etatpartie == serverControl_->serverData_->etatPartieWIN)
		{
			std::string message = "Game is WOOONNNNN";
			Sleep(500);
		}
		else if (etatpartie == serverControl_->serverData_->etatPartieLOSE)
		{
			std::string message = "haha you lose";
			Sleep(500);
		}
		
	}
	serverControl_->THREAD_SNAPSHOT_DEAD = true;
	return 0;
}

// Thread de communication 3: TCP 5045
// Communication passive qui attend une connexion
// Recoit les connexions des utilisateurs (nouveaux ou reconnectant) 
// et note leur adresse IP localement pour les autres threads
int MultiThreadConnectionHandling(AbstractSocket::TCPSocket* sd_, GameServerControl* serverControl_)
{
	serverControl_->THREAD_CONNEC_DEAD = false;
	sockaddr_in sinRemote;
	int nAddrSize = sizeof(sinRemote);
	for (;;)
	{
		// Vérification pour l'ordre d'éxecution des threads
		if (serverControl_->GLOBAL_KILL_THREAD_ORDER)
		{
			serverControl_->THREAD_CONNEC_DEAD = true;
			return 0;
		}

		// Vérifie si une connection est en attente
		fd_set readSet;
		FD_ZERO(&readSet);
		FD_SET(sd_->socket_, &readSet);
		timeval timeout;
		timeout.tv_sec = 0;  // Zero timeout (poll)
		timeout.tv_usec = 50000;
		AbstractSocket::TCPSocket* socketTemp;
		// Adresse IP
		std::string IPstr;
		// Valeurs de l'adresse IP
		int a, b, c, d;
		// Connection en attente
		int selectReturn = select((int)sd_->socket_, &readSet, NULL, NULL, &timeout);
		if (selectReturn >= 1)
		{
			// Create a SOCKET for accepting incoming requests.
			// Accept the connection in  blocking
			socketTemp = new AbstractSocket::TCPSocket(accept(sd_->socket_, (sockaddr*)&sinRemote, &nAddrSize), sd_->port_);
			if (socketTemp->socket_ != INVALID_SOCKET)
			{
				IPstr = inet_ntoa(sinRemote.sin_addr);
				a = sinRemote.sin_addr.S_un.S_un_b.s_b1;
				b = sinRemote.sin_addr.S_un.S_un_b.s_b2;
				c = sinRemote.sin_addr.S_un.S_un_b.s_b3;
				d = sinRemote.sin_addr.S_un.S_un_b.s_b4;
			}
			else
			{
				delete socketTemp;
				continue;
			}
		}
		else // Aucune connection en attente
		{
			// Timeout, no one's here
			if (selectReturn == 0)
			{
				int port = sd_->port_;
				delete sd_;
				sd_ = new AbstractSocket::TCPSocket(port);
			}
			else // Some Socket Error
			{
				int err = WSAGetLastError();
				std::cout << "Erreur dans la connexion initiale! Select err no: " << err << std::endl;
			}
			continue;
		}

		// Préléminaire: Obtenir les infos de l'utilisateur
		sockaddr_in peeraddr;
		int size = sizeof(peeraddr);
		getsockname(socketTemp->socket_, (struct sockaddr *)&peeraddr, &size);
		//struct sockaddr_in *s = (struct sockaddr_in *)&peeraddr;
		std::string port = std::to_string(ntohs(peeraddr.sin_port));
		std::cout << "Connection acceptee de : " << IPstr << ":" << port << "." << std::endl;
		IP playerIP(a, b, c, d);

		// Étape 1: Reception du handshake initial "Kept you waiting, huh?" depuis le nouvel utilisateur
		std::string handShakeMessage;
		std::string expected = "Kept you waiting, huh?";
		bool handshakeSuccess = AbstractSocket::ReceiveString(socketTemp, (int)expected.length(), handShakeMessage);
		if (!handshakeSuccess)
		{
			std::cout << "FAILED RECEIVING HANDSHAKE" << std::endl;
			delete socketTemp;
			continue;
		}
		if (handShakeMessage != expected)
		{
			std::cout << "FAILED RECEIVING HANDSHAKE" << std::endl;
			delete socketTemp;
			continue;
		}

		// Étape 2: Réception du numéro assigné au joueur par le Serveur
		int indexJoueur = -1;
		if (!AbstractSocket::ReceiveInt(socketTemp, indexJoueur))
		{
			std::cout << "FAILED RECEIVING PLAYER NUMBER" << std::endl;
			delete socketTemp;
			continue;
		}

		// Étape 3: Envoyer au joueur le numéro de carte de la campagne courrante
		if (!AbstractSocket::SendInt(socketTemp, serverControl_->serverData_->getCampaignIndex()))
		{
			std::cout << "FAILED SENDING CAMPAIGN INDEX" << std::endl;
			delete socketTemp;
			continue;
		}

		// Étape 4: Réponse au joueur et assignation de l'IP du joueur 
		std::string packageout;
		if (serverControl_->serverData_->assignPlayerIP(playerIP, indexJoueur)
			|| indexJoueur == -1
			|| indexJoueur > serverControl_->serverData_->getNumberOfPlayers()
			)
			packageout = "ACK-J";
		else
			packageout = "ACK-F";
		if (!AbstractSocket::SendString(socketTemp, packageout))
		{
			std::cout << "FAILED SENDING ANSWER TO CLIENT" << std::endl;
			delete socketTemp;
			continue;
		}

		// Nettoyage
		delete socketTemp;
		std::cout << "Joueur numéro " << indexJoueur << " connecte avec success." << std::endl;
	}
	serverControl_->THREAD_CONNEC_DEAD = true;
	return 0;
}

// Thread de communication 4: UDP 5050
// Communication passive qui attend un message
// Recoit aux 10ms, par joueur, l'état de leurs boutons pour simuler la physique
int MultiThreadStatusHandling(AbstractSocket::UDPSocket* sd_, GameServerControl* serverControl_)
{
	serverControl_->THREAD_STATUS_DEAD = false;
	for (;;)
	{
		// Vérification pour l'ordre d'éxecution des threads
		if (serverControl_->GLOBAL_KILL_THREAD_ORDER)
		{
			serverControl_->THREAD_STATUS_DEAD = true;
			return 0;
		}
		// Vérifie si une connection est en attente
		fd_set readSet;
		FD_ZERO(&readSet);
		FD_SET(sd_->socket_, &readSet);
		timeval timeout;
		timeout.tv_sec = 0;  // Zero timeout (poll)
		timeout.tv_usec = 50000;
		// Connection en attente
		int selectResult = select(0, &readSet, NULL, NULL, &timeout);
		if (selectResult < 1)
		{
			// Timeout, no one's here
			if (selectResult == 0)
			{
			}
			else // Some Socket Error
			{
				int err = WSAGetLastError();
				std::cout << "Erreur dans la reception du Status! Select err no: " << err << std::endl;
			}
			continue;
		}


		IP* playerIP = new IP();
		// Step 1: Obtenir message
		std::string controlStatus;
		if (!AbstractSocket::ReceiveString(sd_, 4, controlStatus, playerIP))
		{
			// Refresh socket
			delete sd_;
			sd_ = new AbstractSocket::UDPSocket(5050);
			// Less rigorous error checking required
			continue;
		}
		std::string etatpartie = serverControl_->serverData_->getGameStatus(0);
		int numeroJoueur = controlStatus[0] - '0';
		if (controlStatus == "DEAD")
		{
			// Handle player reporting being DEAD
			serverControl_->serverData_->setPlayerDisconnected(numeroJoueur);
		}
		else if (etatpartie == serverControl_->serverData_->etatPartieGAME)
		{
			bool paletteGauche = (controlStatus[1] == '1');
			bool paletteDroite = (controlStatus[2] == '1');
			bool ressort = (controlStatus[3] == '1');
			int colorshift = numeroJoueur - 1;

			// Step 3: Envoyer etats a facade modele selon le numero du joueur
			
			// Activer ou désactiver les palettes gauches du bon joueur
			if (paletteGauche)
				FacadeJeu::obtenirInstance()->activerPalettesGauches(colorshift);
			else
				FacadeJeu::obtenirInstance()->desactiverPalettesGauches(colorshift);

			// Activer ou désactiver les palettes droites du bon joueur
			if (paletteDroite)
				FacadeJeu::obtenirInstance()->activerPalettesDroites(colorshift);
			else
				FacadeJeu::obtenirInstance()->desactiverPalettesDroites(colorshift);

			// Activer ou désactiver les ressorts
			if (ressort)
				FacadeJeu::obtenirInstance()->compresserRessort(colorshift); // TODO shouldnt this user colorshit
			else
				FacadeJeu::obtenirInstance()->relacherRessort(colorshift); // TODO YONNI CHECK THIS OUT

		}
	}
	serverControl_->THREAD_STATUS_DEAD = true;
	return 0;
}

#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // Connection related

// Initialise les threads de communication
bool GameServerControl::initializeCommunications()
{
	// Initialisation de Winsock
#ifndef SERVERTESTER
#else
	std::cout << ":::Initialisation du serveur:::" << std::endl;
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		std::cerr << "Error at WSAStartup()";
		return false;
	}
#endif

	// Création des sockets
	try {
		createSocketVector();
	}
	catch (...) {
		std::cout << "Erreur de connections lors de la creation des sockets. Abandon." << std::endl;
		system("pause");
		return false;
	}

	// Lancement des threads asynchrones de communication
	// Communication avec les joueurs TCP 5035
	//threadReturnList_.push_back(std::async(std::launch::async, &MultiThreadCommunicationHandling, TCPSocketList_[5035], this));
	std::thread t1(MultiThreadCommunicationHandling, TCPSocketList_[5035], this);
	// Envoie des SnapShot de la carte en cours UDP 5040
	//threadReturnList_.push_back(std::async(std::launch::async, &MultiThreadSnapShotHandling, UDPSocketList_[5040], this));
	std::thread t2(MultiThreadSnapShotHandling, UDPSocketList_[5040], this);
	// Gestion des connexions et reconnexions des utilisateurs TCP 5045
	//threadReturnList_.push_back(std::async(std::launch::async, &MultiThreadConnectionHandling, TCPSocketList_[5045], this));
	std::thread t3(MultiThreadConnectionHandling, TCPSocketList_[5045], this);
	// Réception des états des boutons des joueurs UDP 5050
	//threadReturnList_.push_back(std::async(std::launch::async, &MultiThreadStatusHandling, UDPSocketList_[5050], this));
	std::thread t4(MultiThreadStatusHandling, UDPSocketList_[5050], this);
	t1.detach();
	t2.detach();
	t3.detach();
	t4.detach();

	std::cout << "Connections etablies sur tout les ports avec succes. Debut de l'ecoute." << std::endl;
	return true;
}
// Établi les connections des SOCKETS requis pour la communication
void GameServerControl::createSocketVector()
{
	// Création des SOCKETS TCP
	for (int i = 35; i <= 45; i += 10)
	{
		// Création du Socket
		AbstractSocket::TCPSocket* socket = new AbstractSocket::TCPSocket(5000 + i);
		// Ajout du socket à la liste
		TCPSocketList_[5000 + i] = socket;
	}
	// Création des SOCKETS UDP
	for (int i = 40; i <= 50; i+= 10)
	{
		// Création du Socket
		AbstractSocket::UDPSocket* socket = new AbstractSocket::UDPSocket(5000 + i);
		// Ajout à la liste
		UDPSocketList_[5000 + i] = socket;
	}
}

#pragma endregion

// http://www.winsocketdotnetworkprogramming.com/winsock2programming/index.html

// WOW, SUCH INFO, MUCH SOCKETS

// More things to read

// http://www.winsocketdotnetworkprogramming.com/winsock2programming/index.html

// http://www.winsocketdotnetworkprogramming.com/winsock2programming/winsock2advancediomethod5chap.html

// http://www.winsocketdotnetworkprogramming.com/winsock2programming/winsock2advancedscalableapp6chap.html

// http://www.winsocketdotnetworkprogramming.com/winsock2programming/winsock2advancedmulticast9chap.html

// http://www.winsocketdotnetworkprogramming.com/winsock2programming/winsock2advancednamedpipe15chap.html

// http://www.winsocketdotnetworkprogramming.com/winsock2programming/winsock2codedownload.html

// http://www.winsocketdotnetworkprogramming.com/winsock2programming/winsock2advancedcode1e.html

// http://www.winsocketdotnetworkprogramming.com/winsock2programming/winsock2advancedcode1f.html

// http://www.binarytides.com/udp-socket-programming-in-winsock/