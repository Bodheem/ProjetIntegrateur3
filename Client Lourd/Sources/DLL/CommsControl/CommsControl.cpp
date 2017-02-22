//////////////////////////////////////////////////////////////////////////////
/// @file CommsControl.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Client
//////////////////////////////////////////////////////////////////////////////
#include "CommsControl.h"
#include <iostream>
#include <stdint.h>
#include <thread>
#include <future>
#include <tchar.h>
#include <Windows.h>
#include <strsafe.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include "GameServerControl\GameServerControl.h"
#include "tinyxml2.h"

#ifndef SERVERTESTER
#include "../Application/FacadeModele.h"
#include "../Application/FacadeJeu.h"
#include "../../../Serveur/SharedFiles/Utilitaire.h"
#include "../../../Serveur/SharedFiles/AbstractSocketV2.h"
#else
#include "../../../../Serveur/SharedFiles/Utilitaire.h"
#include "../../../../Serveur/SharedFiles/AbstractSocketV2.h"
#endif

////////////////////////////////////
#pragma region Constructeur / Destructeurs / Autre
/// Constructeur
CommsControl::CommsControl()
{
	chatControl_ = new ChatControl();
	gameControl_ = new GameControl();
}
/// Destructeur
CommsControl::~CommsControl()
{
	delete chatControl_;
	delete socketCommunication_;
}
/// Retourner le User
User* CommsControl::getUser() 
{
	return user_;
}

/// Print timestamp to console
void CommsControl::printTimestamp(std::string message)
{
	using namespace std::chrono;
	milliseconds ms = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
		);
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
		+ "m." + std::to_string(seconde_) + "s." + std::to_string(ms.count()%1000) + "ms";
	spacers += ((heure_ < 10) ? " " : "");
	spacers += ((minute_ < 10) ? " " : "");
	spacers += ((seconde_ < 10) ? " " : "");
	spacers += ((ms.count() % 1000 < 100) ? " " : "");
	spacers += ((ms.count() % 1000 < 10) ? " " : "");
	str += spacers + " " + message + "\n";
	std::cout << str;
}
#pragma endregion

////////////////////////////////////
#pragma region // Multithreading safety
/// Obtain Secure ServerData Lock
void CommsControl::obtainSecureLock(std::string lastCaller)
{
	safetyMutex_.lock();
	safetyMutexIsLocked_ = true;
	safetyMutexLastCaller = lastCaller;
}
/// Release Secure ServerData Lock
void CommsControl::releaseSecureLock()
{
	safetyMutex_.unlock();
	safetyMutexIsLocked_ = false;
	safetyMutexLastCaller = "";
}
#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // Connexion et tests
/// Connection initiale au Server et obtention du port de communication dédié
bool CommsControl::initializeCommunications(std::string ip)
{
	obtainSecureLock("InitializeCommunications");
	if (!Utilitaire::addresseCorrecte(ip))
	{
		releaseSecureLock();
		return false;
	}

	// Initial Winsock Cleanup
	WSADATA wsaDataClean;
	int err = WSAStartup(MAKEWORD(2, 2), &wsaDataClean);
	if (err != 0)
	{
		/* Tell the user that we could not find a usable */
		/* Winsock DLL.                                  */
		std::cout << "WSAStartup failed with error: " << err << std::endl;
		return false;
	}
	/* Confirm that the WinSock DLL supports 2.2.*/
	if (LOBYTE(wsaDataClean.wVersion) != 2 || HIBYTE(wsaDataClean.wVersion) != 2)
	{
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		std::cout << "Could not find a usable version of Winsock2.dll" << std::endl;
		WSACleanup();
		return false;
	}
	else
	{
		WSACleanup();
	}

	// Init WinSock
	WSADATA wsaData;
	int wsaStartupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsaStartupResult != 0)
	{
		std::cout << "Erreur de WSAStartup: " << wsaStartupResult << std::endl;
		releaseSecureLock();
		return false;
	}

	// Obtenir les informations de connection initiales. Probablement de l'utilisateur plus tard
	std::string addresse = "";
	std::string port = "";
	addresse = ip;
	port = "5000";
	//Utilitaire::obtenirInformationsConnection(addresse, port);
	if (addresse.empty() || port.empty())
	{
		WSACleanup();
		releaseSecureLock();
		return false;
	}

	// Se connecter au serveur
	socketInitial_ = new AbstractSocket::TCPSocket(5000);
	bool resultatConnection = AbstractSocket::CreateSocket(socketInitial_, addresse, port);
	if (!resultatConnection)
	{
		WSACleanup();
		releaseSecureLock();
		return false;
	}
	std::cout << "Connection etablie!" << std::endl;
	serverIPStr_ = addresse;
	serverIPClass_ = new IP(serverIPStr_);

	// Handshake initial
	std::string messageHi = "hi";
	bool handshakeRes = AbstractSocket::SendString(socketInitial_, messageHi);
	if (!handshakeRes)
	{
		WSACleanup();
		releaseSecureLock();
		return false;
	}

	// Obtenir le port de communication dédié
	int32_t receivedPort;
	bool initialPortRes = AbstractSocket::ReceiveInt(socketInitial_, receivedPort);
	if (!initialPortRes)
	{
		WSACleanup();
		releaseSecureLock();
		return false;
	}


	// Assignation du port recu
	assignedPort_ = receivedPort;
	serverDedicatedPort_ = std::to_string(assignedPort_);
	std::cout << std::endl << "Port recu: " << receivedPort << "." << std::endl;
	//system("pause");
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	// Terminaison de la connection avec le thread principal du serveur
	delete socketInitial_;
	releaseSecureLock();
	
	return true;
}
/// Verb 69: Test communications
bool CommsControl::commsTest()
{
	obtainSecureLock("CommsTest");

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "COMMS TEST: Executing Comms Test" << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int verb = 69;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	int out = 25;
	if (!AbstractSocket::SendInt(socketCommunication_, out))
	{
		std::cout << "COMMS TEST FAIL AT SENDINT" << std::endl;
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	//std::cout << "COMMS TEST: INT SENT: " << out << std::endl;

	int in = -1;
	if (!AbstractSocket::ReceiveInt(socketCommunication_, in))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVEINT" << std::endl;
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	//std::cout << "COMMS TEST: INT RECEIVED: " << in << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::string messageout(out, (char)('a' + i));
		if (!AbstractSocket::SendString(socketCommunication_, messageout))
		{
			std::cout << "COMMS TEST FAIL AT SENDSTRING" << std::endl;
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}
		//std::cout << "COMMS TEST: STRING SENT OF LENGTH: " << messageout.length() << "/" << out << std::endl << messageout << std::endl;

		std::string messagein;
		if (!AbstractSocket::ReceiveString(socketCommunication_, in, messagein))
		{
			std::cout << "COMMS TEST FAIL AT RECEIVESTRING" << std::endl;
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}
		//std::cout << "COMMS TEST: STRING RECEIVED OF LENGTH: " << messagein.length() << "/" << in << std::endl << messagein << std::endl;
	}

	std::string messageout(out, 'a');
	if (!AbstractSocket::SendString(socketCommunication_, messageout))
	{
		std::cout << "COMMS TEST FAIL AT SENDSTRING" << std::endl;
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	//std::cout << "COMMS TEST: STRING SENT OF LENGTH: " << messageout.length() << std::endl << messageout << std::endl;

	std::string messagein;
	if (!AbstractSocket::ReceiveString(socketCommunication_, in, messagein))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVESTRING" << std::endl;
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	//std::cout << "COMMS TEST: STRING RECEIVED OF LENGTH: " << messagein.length() << std::endl << messagein << std::endl;
	
	std::string packageout = "le tabarnak de string";
	if (!AbstractSocket::SendStringPackage(socketCommunication_, packageout))
	{
		std::cout << "COMMS TEST FAIL AT SENDSTRINGPACKAGE" << std::endl;
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	//std::cout << "COMMS TEST: STRING PACKAGE SENT OF LENGTH: " << packageout.length() << std::endl << packageout << std::endl;

	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, packagein))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVESTRINGPACKAGE" << std::endl;
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	//std::cout << "COMMS TEST: STRING PACKAGE RECEIVED OF LENGTH: " << packagein.length() << std::endl << packagein << std::endl;

	std::vector<std::string> vectorout = { "un petit string", "un ben ben ben ben ben ben ben ben plus gros string", "un string pareil",
		"un autre string pareil", "un calisse de string avec un backslash n\n de calisse de marde" };
	if (!AbstractSocket::SendMultipleStringPackage(socketCommunication_, vectorout))
	{
		std::cout << "COMMS TEST FAIL AT SENDMULTIPLESTRINGPACKAGE" << std::endl;
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	//std::cout << "COMMS TEST: MULTIPLE STRING PACKAGE SENT OF SIZE: " << vectorout.size() << std::endl;
	//for (std::string message : vectorout)
	//	std::cout << message << std::endl;

	std::vector<std::string> vectorin;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socketCommunication_, vectorin))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVEMULTIPLESTRINGPACKAGE" << std::endl;
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	//std::cout << "COMMS TEST: MULTIPLE STRING PACKAGE RECEIVED OF SIZE: " << vectorin.size() << std::endl;
	//for (std::string message : vectorin)
	//	std::cout << message << std::endl;

	std::vector<int> intvectorout;
	for (int i = 0; i < 10; i++)
		intvectorout.push_back(i);
	if (!AbstractSocket::SendMultipleIntPackage(socketCommunication_, intvectorout))
	{
		std::cout << "COMMS TEST FAIL AT SENDMULTIPLEINTPACKAGE" << std::endl;
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	//std::cout << "COMMS TEST: MULTIPLE INT PACKAGE SENT OF SIZE: " << intvectorout.size() << std::endl;
	//for (int message : intvectorout)
	//	std::cout << std::to_string(message) << std::endl;

	std::vector<int> intvectorin;
	if (!AbstractSocket::ReceiveMultipleIntPackage(socketCommunication_, intvectorin))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVEMULTIPLESTRINGPACKAGE" << std::endl;
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	//std::cout << "COMMS TEST: MULTIPLE STRING PACKAGE RECEIVED OF SIZE: " << intvectorin.size() << std::endl;
	//for (int message : intvectorin)
	//	std::cout << std::to_string(message) << std::endl;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "COMMS TEST: All TCP Tests Succesfull" << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	AbstractSocket::UDPSocket* socketUDP = new AbstractSocket::UDPSocket(5036);
	IP* target = serverIPClass_;

	if (!AbstractSocket::SendInt(socketUDP, out, target))
	{
		std::cout << "COMMS TEST FAIL AT SENDINT" << std::endl;
		delete socketUDP;
		releaseSecureLock();
		return false;
	}
	//std::cout << "COMMS TEST: INT SENT: " << out << std::endl;

	int in2 = -1;
	IP* received = new IP();
	if (!AbstractSocket::ReceiveInt(socketUDP, in2, received))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVEINT" << std::endl;
		delete socketUDP;
		releaseSecureLock();
		return false;
	}
	delete received;
	//std::cout << "COMMS TEST: INT RECEIVED: " << in << std::endl;

	for (int i = 0; i < 10; i++)
	{
		std::string messageout(out, 'a');
		if (!AbstractSocket::SendString(socketUDP, messageout, target))
		{
			std::cout << "COMMS TEST FAIL AT SENDSTRING" << std::endl;
			delete socketUDP;
			releaseSecureLock();
			return false;
		}
		//std::cout << "COMMS TEST: STRING SENT OF LENGTH: " << messageout.length() << "/" << out << std::endl << messageout << std::endl;

		std::string messagein;
		IP* received2 = new IP();
		if (!AbstractSocket::ReceiveString(socketUDP, in, messagein, received2))
		{
			std::cout << "COMMS TEST FAIL AT RECEIVESTRING" << std::endl;
			delete socketUDP;
			releaseSecureLock();
			return false;
		}
		delete received2;
		//std::cout << "COMMS TEST: STRING RECEIVED OF LENGTH: " << messagein.length() << "/" << in << std::endl << messagein << std::endl;
	}

	if (!AbstractSocket::SendString(socketUDP, messageout, target))
	{
		std::cout << "COMMS TEST FAIL AT SENDSTRING" << std::endl;
		delete socketUDP;
		releaseSecureLock();
		return false;
	}
	//std::cout << "COMMS TEST: STRING SENT OF LENGTH: " << messageout.length() << std::endl << messageout << std::endl;

	messagein.clear();
	IP* received3 = new IP();
	if (!AbstractSocket::ReceiveString(socketUDP, in, messagein, received3))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVESTRING" << std::endl;
		delete socketUDP;
		releaseSecureLock();
		return false;
	}
	delete received3;
	//std::cout << "COMMS TEST: STRING RECEIVED OF LENGTH: " << messagein.length() << std::endl << messagein << std::endl;
	
	//if (!AbstractSocket::SendStringPackage(socketCommunication_, socketUDP, packageout, target))
	//{
	//	std::cout << "COMMS TEST FAIL AT SENDSTRINGPACKAGE UDP ONLY" << std::endl;
	//	delete socketUDP;
	//	releaseSecureLock();
	//	return false;
	//}
	////std::cout << "COMMS TEST: STRING PACKAGE SENT OF LENGTH: " << packageout.length() << std::endl << packageout << std::endl;

	//packagein.clear();
	//IP* received4 = new IP();
	//if (!AbstractSocket::ReceiveStringPackage(socketUDP, packagein, received4))
	//{
	//	std::cout << "COMMS TEST FAIL AT RECEIVESTRINGPACKAGE UDP ONLY" << std::endl;
	//	delete socketUDP;
	//	releaseSecureLock();
	//	return false;
	//}
	//delete received4;
	//std::cout << "COMMS TEST: STRING PACKAGE RECEIVED OF LENGTH: " << packagein.length() << std::endl << packagein << std::endl;

	std::string longmessage = std::string(2000, '*');
	if (!AbstractSocket::SendStringPackage(socketCommunication_, socketUDP, longmessage, target))
	{
		std::cout << "COMMS TEST FAIL AT SENDSTRINGPACKAGE UDP TCP" << std::endl;
		delete socketUDP;
		releaseSecureLock();
		return false;
	}
	//std::cout << "COMMS TEST: STRING PACKAGE SENT OF LENGTH: " << packageout.length() << std::endl << packageout << std::endl;

	packagein.clear();
	IP* received5 = new IP();
	if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, socketUDP, packagein, received5))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVESTRINGPACKAGE UDP TCP" << std::endl;
		delete socketUDP;
		releaseSecureLock();
		return false;
	}
	delete received5;
	//std::cout << "COMMS TEST: STRING PACKAGE RECEIVED OF LENGTH: " << packagein.length() << std::endl << packagein << std::endl;

	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "COMMS TEST: All UDP Tests Succesfull" << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_; 
	delete socketUDP;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 0: Abandon du socket réservé. Requiert de refaire initializeCommunications par après
bool CommsControl::executeAbandonSocket()
{
	obtainSecureLock("AbandonSocket");
	int verb = 0;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	
	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, packagein))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (packagein == "ACK-S")
	{
		// Nettoyage final de l'instance de communication
		delete socketCommunication_;
		socketCommunication_ = nullptr;
		WSACleanup();
		serverDedicatedPort_.clear();
		assignedPort_ = -1;
		releaseSecureLock();
		return true;
	}
	else
	{
		// Terminaison de la connection avec le thread principal du serveur
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
}
/// Connection à l'hote multijoueur
bool CommsControl::initializeMultiplayerGame()
{
	// Connect to Host
	GLOBAL_KILL_THREAD_ORDER = false;
	socketConnexionMultiplayer_ = new AbstractSocket::TCPSocket(5045);

	IP* hostip = gameControl_->getHostIP();

	std::string addresseHote = hostip->getStringIP();
	bool resultatConnection = AbstractSocket::CreateSocket(socketConnexionMultiplayer_, addresseHote, "5045");
	if (!resultatConnection)
	{
		std::cout << "Echec d'initialisation de la partie multijoueur!" << std::endl;
		std::cout << "Erreur a la connexion initiale" << std::endl;
		delete socketConnexionMultiplayer_;
		socketConnexionMultiplayer_ = nullptr;
		return false;
	}
	std::cout << "Connection etablie a l'hote multijoueur a l'IP: " << addresseHote << "!" << std::endl;

	// Step 1: Send initial handshaking
	std::string expected = "Kept you waiting, huh?";
	bool commsRes = AbstractSocket::SendString(socketConnexionMultiplayer_, expected);
	if (!commsRes)
	{
		std::cout << "Echec d'initialisation de la partie multijoueur!" << std::endl;
		std::cout << "Erreur a l'envoi du message initial" << std::endl;
		delete socketConnexionMultiplayer_;
		socketConnexionMultiplayer_ = nullptr;
		return false;
	}

	// Step 2: Send Player Number
	int playerNumber = gameControl_->getPlayerNumber(user_);

	commsRes = AbstractSocket::SendInt(socketConnexionMultiplayer_, playerNumber);
	if (!commsRes)
	{
		std::cout << "Echec d'initialisation de la partie multijoueur!" << std::endl;
		std::cout << "Erreur a l'envoi de l'index de joueur" << std::endl;
		delete socketConnexionMultiplayer_;
		socketConnexionMultiplayer_ = nullptr;
		return false;
	}

	// Step 3: Get Current Campaign Map Index
	int campaignIndex = -1;
	commsRes = AbstractSocket::ReceiveInt(socketConnexionMultiplayer_, campaignIndex);
	if (!commsRes || campaignIndex == -1)
	{
		std::cout << "Echec d'initialisation de la partie multijoueur!" << std::endl;
		std::cout << "Erreur a la reception de l'index de carte" << std::endl;
		delete socketConnexionMultiplayer_;
		socketConnexionMultiplayer_ = nullptr;
		return false;
	}
	gameControl_->setCampaignIndex(campaignIndex);

	std::string packagein;
	// Step 4: Get Host Response
	commsRes = AbstractSocket::ReceiveString(socketConnexionMultiplayer_, 5, packagein);
	if (!commsRes)
	{
		std::cout << "Echec d'initialisation de la partie multijoueur!" << std::endl;
		std::cout << "Erreur a la reception d'etat" << std::endl;
		delete socketConnexionMultiplayer_;
		socketConnexionMultiplayer_ = nullptr;
		return false;
	}
	if (packagein == "ACK-J")
	{
		std::cout << "Initialisation de la partie multijoueur!" << std::endl;
		// Start multiplayer Communication
		gameControl_->setGameStatus(gameControl_->etatPartieDEBUT);

		initializeMultiplayerCommunications(gameControl_->getHostIP()->getStringIP());

		delete socketConnexionMultiplayer_;
		socketConnexionMultiplayer_ = nullptr;
		return true;
	}
	else if (packagein == "ACK-F")
	{
		std::cout << "Echec d'initialisation de la partie multijoueur!" << std::endl;
		std::cout << "Index de joueur possiblement refuse" << std::endl;
		delete socketConnexionMultiplayer_;
		socketConnexionMultiplayer_ = nullptr;
		return false;
	}
	delete socketConnexionMultiplayer_;
	socketConnexionMultiplayer_ = nullptr;
	return false;
}
bool CommsControl::initializeMultiplayerCommunications(std::string hostIP)
{
	// Création des sockets
	try {
		createMultiplayerSocketVector();
	}
	catch (...) {
		std::cout << "Erreur de connections lors de la creation des sockets multijoueur. Abandon." << std::endl;
		system("pause");
		return false;
	}

	// Lancement des threads asynchrones de communication
	// Communication avec les joueurs TCP 5035
	//threadReturnList_.push_back(std::async(std::launch::async, &MPMultiThreadCommunicationHandling, MPTCPSocketList_[5035], this));
	std::thread t1(&MPMultiThreadCommunicationHandling, MPTCPSocketList_[5035], this);
	// Envoie des SnapShot de la carte en cours UDP 5040
	//threadReturnList_.push_back(std::async(std::launch::async, &MPMultiThreadSnapShotHandling, MPUDPSocketList_[5040], this));
	std::thread t2(&MPMultiThreadSnapShotHandling, MPUDPSocketList_[5040], this);
	// Réception des états des boutons des joueurs UDP 5050
	//threadReturnList_.push_back(std::async(std::launch::async, &MPMultiThreadStatusHandling, MPUDPSocketList_[5050], this));
	std::thread t3(&MPMultiThreadStatusHandling, MPUDPSocketList_[5050], this);

	t1.detach();
	t2.detach();
	t3.detach();
	std::cout << "Connections etablies sur tout les ports multijoueurs avec succes. Debut de l'ecoute." << std::endl;
	return true;
}
bool CommsControl::createMultiplayerSocketVector()
{
	// Création du SOCKETS TCP
	// Création du Socket
	AbstractSocket::TCPSocket* socket = new AbstractSocket::TCPSocket(5035);
	// Ajout du socket à la liste
	MPTCPSocketList_[5035] = socket;
	
	// Création des SOCKETS UDP
	for (int i = 40; i <= 50; i += 10)
	{
		// Création du Socket
		AbstractSocket::UDPSocket* socket = new AbstractSocket::UDPSocket(5000 + i);
		// Ajout à la liste
		MPUDPSocketList_[5000 + i] = socket;
	}
	return true;
}
#pragma endregion

////////////////////////////////////
#pragma region // // // Autres Fonctions
/// Retourne true si la partie est commencée
bool CommsControl::isGameStarted()
{
	if (gameControl_ != nullptr)
		if (gameControl_->getGameStatus() != gameControl_->etatPartieNOTHING 
			&& gameControl_->getGameStatus() != gameControl_->etatPartieLOBBY)
			return true;
	return false;
}
/// Retourne true si le joueur est l'hote
bool CommsControl::isHostMachine()
{
	return user_->getUserName() == gameControl_->getRoom()->getHostName();
}
/// En tant qu'Host, dire que la partie est gagnée
void CommsControl::setGameWon()
{
	gameServer_->serverData_->setGameStatus(gameServer_->serverData_->etatPartieWIN);
}
/// En tant qu'Host, dire que la partie est perdue
void CommsControl::setGameLost()
{
	gameServer_->serverData_->setGameStatus(gameServer_->serverData_->etatPartieLOSE);
}
/// En tant qu'Host, dire à un joueur qu'il a perdu
void CommsControl::asHostSetPlayerLost(int playerNumber)
{
	gameServer_->serverData_->setPlayerDead(playerNumber);
}
/// En tant qu'Host, dire à un joueur qu'il a gagné
void CommsControl::asHostSetPlayerWin(int playerNumber)
{
	gameServer_->serverData_->setPlayerWon(playerNumber);

}
/// Informe le host que le joueur a perdu
void CommsControl::asPlayerSetPlayerLost()
{
	gameControl_->setPlayerDead();
}
/// Informe le host que le joueur a gagné
void CommsControl::asPlayerSetPlayerWon()
{
	gameControl_->setPlayerWon();
}
/// Kill all threads
void CommsControl::killAllThreads()
{
	GLOBAL_KILL_THREAD_ORDER = true;
	std::cout << "Multiplayer Comms Threads Shutting down" << std::endl;
	while (!THREAD_COMMS_DEAD)
		Sleep(100);
	while (!THREAD_STATUS_DEAD)
		Sleep(100);
	while (!THREAD_SNAPSHOT_DEAD)
		Sleep(100);
}
/// Completely reinitialize multiplayer controls
void CommsControl::resetMultiplayer()
{
	obtainSecureLock("ResetMultiplayer");
	killAllThreads();
	gameControl_->resetGameControl();
	if (gameServer_ != nullptr)
	{
		gameServer_->killAllThreads();
		gameServer_->resetGameServer();
		GameServerControl::deletePointer();
		gameServer_ = nullptr;
	}
	for (auto itr = MPTCPSocketList_.begin(); itr != MPTCPSocketList_.end(); itr++)
		delete (*itr).second;
	for (auto itr = MPUDPSocketList_.begin(); itr != MPUDPSocketList_.end(); itr++)
		delete (*itr).second;
	releaseSecureLock();
}
/// Returns the Multiplayer Game Status
std::string CommsControl::getMPGameStatus()
{
	if (gameControl_->getRoom()->getHostName() == user_->getUserName())
	{
		// Host
		return gameServer_->serverData_->getGameStatus(1);
	}
	else
	{
		// Player
		return gameControl_->getGameStatus();
	}
}
/// Return true if playing a game online
bool CommsControl::isGameOnline()
{
	if (gameControl_ == nullptr || gameControl_->getRoom() == nullptr)
		return false;

	return getMPGameStatus() != gameControl_->etatPartieNOTHING;
}
/// Prepare next game in campaign Mode
void CommsControl::MPPrepareNextGame()
{
	// Prepare next game as Host
	if (gameServer_ != nullptr)
	{
		gameServer_->serverData_->incrementCampaignIndex();
		gameControl_->incrementCampaignIndex();
		gameServer_->serverData_->setGameStatus(gameServer_->serverData_->etatPartieDEBUT);
	}
	else // Prepare next game as player
	{
		gameControl_->incrementCampaignIndex();
		gameControl_->setGameStatus(gameControl_->etatPartieDEBUT);
		gameControl_->setPlayerNotReady();
	}
}
#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // Communication Threads

// Thread de communication 1: TCP 5035
// Communication passive qui attend une connexion
// Gère l'état de la partie et permet de la débuter et d'envoyer des ordres de contrôles aux joueurs
int MPMultiThreadCommunicationHandling(AbstractSocket::TCPSocket* sd_, CommsControl* control_)
{
	control_->THREAD_COMMS_DEAD = false;
	int timeDelta = 0;
	auto then = std::chrono::steady_clock::now();
	// Regulièrement, envoyer "PREP" jusqu'à ce que tout les joueurs soient connectés 
	// ET qu'on aie envoyer un dernier PREP
	// ET que la partie roule depuis 2 SSTICK, envoyer "GO"
	// Attendre les conditions de fin de partie puis envoyer le message correspondant
	for (;;)
	{
		// Vérification pour l'ordre d'éxecution des threads
		if (control_->GLOBAL_KILL_THREAD_ORDER)
		{
			control_->THREAD_COMMS_DEAD = true;
			return 0;
		}
		// Attente
		Sleep(control_->COMMS_REFRESH_TIME);
		// Création de la connexion au serveur
		if (!AbstractSocket::CreateSocket(sd_, control_->gameControl_->getHostIP()->getStringIP(), "5035"))
		{
			// Échec de communication
			delete sd_;
			sd_ = new AbstractSocket::TCPSocket(5035);

			// Calcule l'avancement du temps et gère la perte de communication au Host
			if (control_->gameControl_->getGameStatus() == control_->gameControl_->etatPartieDEBUT ||
				control_->gameControl_->getGameStatus() == control_->gameControl_->etatPartieSTART ||
				control_->gameControl_->getGameStatus() == control_->gameControl_->etatPartieGAME)
			{
				auto now = std::chrono::steady_clock::now();
				timeDelta = (int)std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count();
				then = now;
				control_->gameControl_->updateTimeout(timeDelta);
			}

			continue;
		}

		// Reset le timeout
		control_->gameControl_->resetTimeout();
		
		// Étape 1: Reception de l'état de la partie
		std::string etatGame;
		if (!AbstractSocket::ReceiveString(sd_, 5, etatGame))
		{
			delete sd_;
			sd_ = new AbstractSocket::TCPSocket(5035);
			continue;
		}
		control_->gameControl_->setGameStatus(etatGame);

		// Étape 2: Envoi de messages spéciaux selon l'état de la partie
		std::string gamestate = control_->gameControl_->getGameStatus();
		if (gamestate == control_->gameControl_->etatPartieDEBUT)
		{
			std::string message;
			int i = control_->gameControl_->getPlayerNumber(control_->user_);

			if (FacadeModele::obtenirInstance()->getPause())
				message = "RDY_" + std::to_string(i);
			else
				message = "NOT_" + std::to_string(i);
			
			if (!AbstractSocket::SendString(sd_, message))
			{
				delete sd_;
				sd_ = new AbstractSocket::TCPSocket(5035);
				continue;
			}
		}
		else if (gamestate == control_->gameControl_->etatPartieSTART)
		{
			std::string message;
			if (FacadeModele::obtenirInstance()->getPause())
			{
				control_->gameControl_->setPlayerReady();
				int i = control_->gameControl_->getPlayerNumber(control_->user_);
				message = "GO__" + std::to_string(i);
			}
			else
			{
				int i = control_->gameControl_->getPlayerNumber(control_->user_);
				message = "NO__" + std::to_string(i);
			}

			if (!AbstractSocket::SendString(sd_, message))
			{
				delete sd_;
				sd_ = new AbstractSocket::TCPSocket(5035);
				continue;
			}

			std::cout << "ETAT PARTIE START" << std::endl;
		}
		else if (gamestate == control_->gameControl_->etatPartieGAME)
		{
			// TODO YONNI la game doit être en train de rouler

			// TODO YONNI gérer si joueur est dead, call setPlayerDead()
			// std::cout << "ETAT PARTIE GAME" << std::endl;
		}
		else if (gamestate == control_->gameControl_->etatPartieWIN)
		{
			// TODO possiblement handle les campagnes ou dequoi
			control_->gameControl_->setPlayerWon();
			//std::cout << "YOU WON" << std::endl;
		}
		else if (gamestate == control_->gameControl_->etatPartieLOSE)
		{
			// TODO retourner au main menu?
			control_->gameControl_->setPlayerDead();
			//std::cout << "YOU LOSE" << std::endl;
		}

		/*
		// Étape 3: Envoie de l'état actuel du joueur
		std::string messageout;
		messageout = control_->gameControl_->getPlayerStatus();

		if (!AbstractSocket::SendString(sd_, messageout))
		{
			delete sd_;
			sd_ = new AbstractSocket::TCPSocket(control_->assignedPort_);
			continue;
		}*/

		// Nettoyage
		delete sd_;
		sd_ = new AbstractSocket::TCPSocket(control_->assignedPort_);
		// Calcule l'avancement du temps et gère la perte de communication au Host
		if (control_->gameControl_->getGameStatus() == control_->gameControl_->etatPartieDEBUT ||
			control_->gameControl_->getGameStatus() == control_->gameControl_->etatPartieSTART ||
			control_->gameControl_->getGameStatus() == control_->gameControl_->etatPartieGAME)
		{
			auto now = std::chrono::steady_clock::now();
			timeDelta = (int)std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count();
			then = now;
			control_->gameControl_->updateTimeout(timeDelta);
		}
	}
	control_->THREAD_COMMS_DEAD = true;
	return 0;
}

// Thread de communication 2: UDP 5040
// Communication active vers les joueurs
// Envoie aux 50 ms un SnapShot de la map actuelle pour synchronisé
// la partie avec les joueurs
int MPMultiThreadSnapShotHandling(AbstractSocket::UDPSocket* sd_, CommsControl* control_)
{
	control_->THREAD_SNAPSHOT_DEAD = false;
	for (;;)
	{
		// Vérification pour l'ordre d'éxecution des threads
		if (control_->GLOBAL_KILL_THREAD_ORDER)
		{
			control_->THREAD_SNAPSHOT_DEAD = true;
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
		// TODO this probably going to fuck
		//if (select(sd_->socket_, &readSet, NULL, NULL, &timeout) != 1)
		//	continue; // Aucun packet en attente
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
				std::cout << "Erreur dans la reception du SnapShot! Select err no: " << err << std::endl;
			}
			continue;
		}

		IP* remoteIP = new IP();
		// Step 1: Recevoir le SnapShot
		std::string controlStatus;
		if (!AbstractSocket::ReceiveStringPackage(sd_, controlStatus, remoteIP))
		{
			// Refresh socket
			delete sd_;
			sd_ = new AbstractSocket::UDPSocket(5040);
			// Less rigorous error checking required
			continue;
		}


		// Appliquer les modifications
		FacadeJeu::applyModification(controlStatus);
	}
	control_->THREAD_SNAPSHOT_DEAD = true;
	return 0;
}

// Thread de communication 3: UDP 5050
// Communication passive qui attend un message
// Recoit aux 10ms, par joueur, l'état de leurs boutons pour simuler la physique
int MPMultiThreadStatusHandling(AbstractSocket::UDPSocket* sd_, CommsControl* control_)
{
	control_->THREAD_STATUS_DEAD = false;
	for (;;)
	{
		// Vérification pour l'ordre d'éxecution des threads
		if (control_->GLOBAL_KILL_THREAD_ORDER)
		{
			IP* gameHost = control_->gameControl_->getHostIP();
			// Envoyer au Host qu'on se deconnecte
			if (!AbstractSocket::SendString(sd_, "DEAD", gameHost))
			{
				// Less rigorous error checking required
			}
			control_->THREAD_STATUS_DEAD = true;
			return 0;
		}
		// Aux 20ms
		Sleep(control_->STATUS_REFRESH_TIME);
		if (control_->gameControl_->getGameStatus() == control_->gameControl_->etatPartieGAME &&
			control_->gameControl_->getPlayerStatus() != control_->gameControl_->etatJoueurMORT)
		{
			// Step 1: Obtenir l'état des boutons
			std::string numeroJoueur = std::to_string(control_->gameControl_->getPlayerNumber(control_->getUser()));
			std::string paletteGauche = std::to_string(FacadeJeu::obtenirInstance()->obtenirEtatBouton(0));
			std::string paletteDroite = std::to_string(FacadeJeu::obtenirInstance()->obtenirEtatBouton(1));
			std::string ressort = std::to_string(FacadeJeu::obtenirInstance()->obtenirEtatBouton(2));

			// Step 2: Obtenir un string contenant l'état des boutons sur 4 bytes
			std::string message = "";
			// B0: numero du joueur
			// B1: palette gauche
			// B2: palette droite
			// B3: ressort
			
			message = numeroJoueur + paletteGauche + paletteDroite + ressort;

			IP* gameHost = control_->gameControl_->getHostIP();
			// Step 3: Envoyer au serveur
			if (!AbstractSocket::SendString(sd_, message, gameHost))
			{
				// Refresh socket
				delete sd_;
				sd_ = new AbstractSocket::UDPSocket(5050);
				// Less rigorous error checking required
				continue;
			}
		}
	}
	control_->THREAD_STATUS_DEAD = true;
	return 0;
}
#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // Looped Actions
/// Not Used: TODO maybe use it
bool CommsControl::executeLoopingCommunicationActions()
{
	obtainSecureLock("LoopingCommunications");
	// TODO
	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 1: Keep Alive sur le socket
bool CommsControl::executeKeepAlive()
{
	obtainSecureLock("KeepAlive");
	int verb = 1;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	
	std::string packageout = "HEART";
	if (!AbstractSocket::SendString(socketCommunication_, packageout))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::string packagein;
	if (!AbstractSocket::ReceiveString(socketCommunication_, 4, packagein))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (packagein == "BEAT")
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return true;
	}
	else
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
}
#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // User Account Related
/// Verb 12: Création de compte Utilisateur
bool CommsControl::executeCreateUserAccount(std::string username, std::string password, std::string email, bool &accountCreated)
{
	obtainSecureLock("CreateUserAccount");
	accountCreated = false;
	std::cout << "Creating New User Account" << std::endl;
	int verb = 12;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorout = { username, password, email };
	if (!AbstractSocket::SendMultipleStringPackage(socketCommunication_, vectorout))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, packagein))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (packagein == "ACK-F")
		accountCreated = false;
	else
		if (packagein == "ACK-S")
			accountCreated = true;
		else
		{
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}

	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 11: Login avec compte Utilisateur
bool CommsControl::executeLogin(std::string username, std::string password, bool &loginAccepted)
{
	obtainSecureLock("Login");
	loginAccepted = false;
	std::cout << "Logging in with credentials" << std::endl;
	int verb = 11;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorout = { username, password };
	if (!AbstractSocket::SendMultipleStringPackage(socketCommunication_, vectorout))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, packagein))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (packagein == "ACK-F")
		loginAccepted = false;
	else
		if (packagein == "ACK-S")
			loginAccepted = true;
		else
		{
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}

	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 10: Logout avec compte Utilisateur
bool CommsControl::executeLogout(bool &logoutSuccessful)
{
	obtainSecureLock("Logout");
	logoutSuccessful = false;
	std::cout << "Logging out" << std::endl;
	int verb = 10;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, packagein))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (packagein == "ACK-F")
		logoutSuccessful = false;
	else
		if (packagein == "ACK-S")
		{
			logoutSuccessful = true;
			delete chatControl_;
			chatControl_ = new ChatControl();
		}
		else
		{
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}

	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 13: Obtenir les informations du compte Utilisateur
bool CommsControl::executeGetUserAccountInfo(bool &success)
{
	obtainSecureLock("GetUserAccountInfo");
	success = false;
	int verb = 13;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorin1;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socketCommunication_, vectorin1))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorin2;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socketCommunication_, vectorin2))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorin3;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socketCommunication_, vectorin3))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorin4;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socketCommunication_, vectorin4))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorin5;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socketCommunication_, vectorin5))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	delete user_;
	user_ = new User(vectorin1[0], vectorin1[1], vectorin1[2]);
	bool res = user_->setBasicInfo(vectorin1);
	res &= user_->setMapInfo(vectorin2);
	res &= user_->setAchievementsInfo(vectorin3);
	res &= user_->setAvatarUnlocked(vectorin4);
	user_->assignerStatistique(vectorin5, true);

	success = res;
	std::string packageout = res ? "ACK-S" : "ACK-F";
	if (!AbstractSocket::SendStringPackage(socketCommunication_, packageout))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 14: Mettre à jour les informations du compte Utilisateur
bool CommsControl::executeUpdateUserAccountInfo(bool &success)
{
	obtainSecureLock("UpdateUserAccountInfo");
	success = false;
	int verb = 14;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorout1 = user_->getBasicInfo();
	if (!AbstractSocket::SendMultipleStringPackage(socketCommunication_, vectorout1))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorout2 = user_->getMapInfo();
	if (!AbstractSocket::SendMultipleStringPackage(socketCommunication_, vectorout2))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorout3 = user_->getAchievementsInfo();
	if (!AbstractSocket::SendMultipleStringPackage(socketCommunication_, vectorout3))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorout4 = user_->getAvatarUnlocked();
	if (!AbstractSocket::SendMultipleStringPackage(socketCommunication_, vectorout4))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorout5 = user_->obtenirStatistique();
	if (!AbstractSocket::SendMultipleStringPackage(socketCommunication_, vectorout5))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, packagein))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (packagein != "ACK-S")
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	success = true;
	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 15: Reset password du compte Utilisateur
bool CommsControl::executeResetUserAccountPassword(std::string username, bool &success)
{
	obtainSecureLock("ResetUserAccountPassword");
	success = false;
	int verb = 15;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	std::string packageout = username;
	if (!AbstractSocket::SendStringPackage(socketCommunication_, packageout))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, packagein))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (packagein == "ACK-F")
		success = false;
	else
		if (packagein == "ACK-S")
			success = true;
		else
		{
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}

	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // Chat Related
/// Verb 21: Obtenir la liste des salles de chat
bool CommsControl::executeUpdateChatRoomList(std::vector<std::string>& listeChatRoom)
{
	obtainSecureLock("UpdateChatRoomList");
	//std::cout << "Updating local user Chatroom list" << std::endl;
	int verb = 21;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	std::vector<std::string> vectorin;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socketCommunication_, vectorin))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	// If user not logged in
	if (vectorin[0] == "ACK-F")
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	chatControl_->updateChatRoomList(vectorin);
	listeChatRoom.insert(listeChatRoom.end(), vectorin.begin(), vectorin.end());
	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 22: Envoyer un nouveau message au chat
bool CommsControl::executeSendNewChatMessage(std::string message, std::string chatRoomName)
{
	obtainSecureLock("SendNewChatMessage");
	//std::cout << "Sending new lobby message" << std::endl;
	int verb = 22;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorout = { message, chatRoomName };
	if (!AbstractSocket::SendMultipleStringPackage(socketCommunication_, vectorout))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Requête à la base de donnée: Historique delta de la salle de chat
bool CommsControl::RequestMessageHistoryUpdate(std::string chatRoomName, std::vector<std::string> &messageList)
{
	obtainSecureLock("requestMessageHistoryUpdate");
	for (ChatRoom* room : chatControl_->getChatRooms())
	{
		if (room->getRoomName() == chatRoomName)
		{
			std::vector<std::string> vec = room->getUnseenMessages();
			messageList.insert(messageList.end(), vec.begin(), vec.end());
			releaseSecureLock();
			return true;
		}
	}
	releaseSecureLock();
	return true;
}
/// Requête à la base de donnée: Historique complète de la salle de chat
bool CommsControl::RequestMessageHistoryComplete(std::string chatRoomName, std::vector<std::string> &messageList)
{
	obtainSecureLock("requestMessageHistoryComplete");
	for (ChatRoom* room : chatControl_->getChatRooms())
	{
		if (room->getRoomName() == chatRoomName)
		{
			std::vector<std::string> vec = room->getAllMessages();
			messageList.insert(messageList.end(), vec.begin(), vec.end());
			releaseSecureLock();
			return true;
		}
	}
	releaseSecureLock();
	return true;
}
/// Verb 23: Obtenir les nouveaux messages du chat
bool CommsControl::executeRequestMessageHistoryUpdate()
{
	obtainSecureLock("RequestMessageHistoryUpdate");
	//std::cout << "Requesting Chatroom History" << std::endl;
	int verb = 23;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	std::vector<std::string> vectorout;
	for (ChatRoom* room : chatControl_->getChatRooms())
	{
		vectorout.push_back(room->getRoomName());
	}
	if (!AbstractSocket::SendMultipleStringPackage(socketCommunication_, vectorout))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	for (ChatRoom* room : chatControl_->getChatRooms())
	{
		std::vector<std::string> messages;
		if (!AbstractSocket::ReceiveMultipleStringPackage(socketCommunication_, messages))
		{
			
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}
		for (std::string message : messages)
			room->addNewMessage(new ChatMessage(message));
	}

	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // Game Room Related

/// Verb 31: Obtenir la liste des salles de jeu
bool CommsControl::executeUpdateGameRoomList(std::vector<std::string>& listeGameRoom)
{
	obtainSecureLock("UpdateGameRoomList");
	//std::cout << "Updating local Gameroom list" << std::endl;
	int verb = 31;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	std::vector<std::string> vectorin;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socketCommunication_, vectorin))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	listeGameRoom.insert(listeGameRoom.end(), vectorin.begin(), vectorin.end());
	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 32: Création d'une salle de jeu
bool CommsControl::executeCreateGameRoom(bool &success)
{
	obtainSecureLock("CreateGameRoom");
	success = false;
	//std::cout << "Creating Game Room" << std::endl;
	int verb = 32;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, packagein))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (packagein == "ACK-F")
		success = false;
	else
		if (packagein == "ACK-S")
			success = true;
		else
		{
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}

	gameControl_->createGameRoom(true, user_);

	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 33: Joindre une salle de jeu
bool CommsControl::executeJoinGameRoom(std::string chatRoomName, std::string password, bool &success)
{
	obtainSecureLock("JoinGameRoom");
	success = false;
	//std::cout << "Joining Game Room" << std::endl;
	int verb = 33;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	std::vector<std::string> vectorout = { chatRoomName, password };
	if (!AbstractSocket::SendMultipleStringPackage(socketCommunication_, vectorout))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, packagein))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (packagein == "ACK-F")
		success = false;
	else
		if (packagein == "ACK-S")
			success = true;
		else
		{
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}
	if (success)
	{
		std::string host;
		if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, host))
		{
			
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}
		if (host != "ACK-F")
			gameControl_->createGameRoom(false, new User(host, "temp", "temp"));
	}
	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 34: Joindre automatiquement une salle de jeu
bool CommsControl::executeMatchmaking(bool &success, bool &host)
{
	obtainSecureLock("Matchmaking");
	success = false;
	host = false;
	//std::cout << "Automatic Matchmaking" << std::endl;
	int verb = 34;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, packagein))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (packagein == "ACK-F")
		success = false;
	else if (packagein == "ACK-S")
		success = true;
	else if (packagein == "ACK-H")
	{
		success = true;
		host = true;
	}
	else
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (success && !host)
	{
		std::string hostname;
		if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, hostname))
		{
			
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}
		if (hostname != "ACK-F")
			gameControl_->createGameRoom(false, new User(hostname, "temp", "temp"));
	}

	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 35: Quitter une salle de jeu
bool CommsControl::executeLeaveGameRoom(bool &success)
{
	obtainSecureLock("LeaveGameRoom");
	success = false;
	if (gameControl_->getRoom() == nullptr)
	{
		releaseSecureLock();
		return false;
	}
	//std::cout << "Leaving Game Room" << std::endl;
	int verb = 35;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	//// Send if game was won if host
	//if (gameServer_ != nullptr)
	//{
	//	std::string packageout = gameServer_->serverData_->allPlayersWon() ? "WON__" : "LOSE_";
	//	if (!AbstractSocket::SendString(socketCommunication_, packageout))
	//	{
	//		delete socketCommunication_;
	//		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	//		releaseSecureLock();
	//		return false;
	//	}
	//}
	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, packagein))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (packagein == "ACK-F")
		success = false;
	else
		if (packagein == "ACK-S")
			success = true;
		else
		{
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}

	// Leave game
	if (success)
	{
		if (gameServer_ != nullptr)
		{
			gameServer_->killAllThreads();
			GameServerControl::deletePointer();
			gameServer_ = nullptr;
		}
		/*else
		{
			AbstractSocket::TCPSocket* a = MPTCPSocketList_[5035];
			AbstractSocket::UDPSocket* b = MPUDPSocketList_[5040];
			AbstractSocket::UDPSocket* c = MPUDPSocketList_[5050];
			MPTCPSocketList_.clear();
			MPUDPSocketList_.clear();
			delete a, b, c;
		}*/
		killAllThreads();
		if (socketConnexionMultiplayer_ != nullptr)
			delete socketConnexionMultiplayer_;
		for (auto &it : MPTCPSocketList_)
			closesocket(it.second->socket_);
		for (auto &it : MPUDPSocketList_) 
			closesocket(it.second->socket_);
		MPTCPSocketList_.clear();
		MPUDPSocketList_.clear();

		delete gameControl_;
		gameControl_ = new GameControl();
	}
	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 41: Débuter une partie
bool CommsControl::executeStartGame(bool &success)
{
	obtainSecureLock("StartGame");
	success = false;
	if (gameControl_->getRoom() == nullptr)
	{
		releaseSecureLock();
		return false;
	}
	//std::cout << "Starting Game Simulation" << std::endl;
	int verb = 41;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, packagein))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (packagein == "ACK-F")
		success = false;
	else
		if (packagein == "ACK-S")
			success = true;
		else
		{
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}
	if (success)
	{
		int numberOfPlayers = gameControl_->getRoom()->getNumberOfPlayers();
		std::string mapName = gameControl_->getRoom()->getMapName();
		// If success, actually start game server thread and such
		gameServer_ = GameServerControl::getPointer();
		gameServer_->startServer(numberOfPlayers, mapName);
	}
	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 42: Se mettre comme prêt
bool CommsControl::executeSetReady(bool status, bool &success)
{
	obtainSecureLock("SetReady");
	success = false;
	if (gameControl_->getRoom() == nullptr)
	{
		releaseSecureLock();
		return false;
	}
	//std::cout << "Swapping Ready Status" << std::endl;
	int verb = 42;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	std::vector<std::string> packageout;
	packageout.push_back(user_->getUserName());
	packageout.push_back(status ? "1" : "0");
	if (!AbstractSocket::SendMultipleStringPackage(socketCommunication_, packageout))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 44: Mettre à jour les informations de la salle de jeu actuelle
bool CommsControl::executeUpdateGameRoomInfo(std::vector<std::string> info, std::vector<std::string> &updatedInfo, bool &success)
{
	obtainSecureLock("UpdateGameRoomInfo");
	success = false;
	if (gameControl_->getRoom() == nullptr)
	{
		releaseSecureLock();
		return false;
	}
	//std::cout << "Updating Game Room Information" << std::endl;
	int verb = 44;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	// Send Updated Information if Host
	if (gameControl_->getRoom()->getHostName() == user_->getUserName())
	{
		if (!AbstractSocket::SendMultipleStringPackage(socketCommunication_, info))
		{
			
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}
	}

	// Receive Updated Information
	std::vector<std::string> vectorin;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socketCommunication_, vectorin))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	updatedInfo = vectorin;

	if (gameControl_->getRoom() == nullptr)
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	GameRoom* room = gameControl_->getRoom();

	std::string hostIP = updatedInfo.back();
	updatedInfo.pop_back();
	room->setHostIP(new IP(hostIP));
	std::string gameHasStarted = updatedInfo.back();
	updatedInfo.pop_back();

	std::string instaDeath = updatedInfo.back();
	updatedInfo.pop_back();
	std::string gameTime = updatedInfo.back();
	updatedInfo.pop_back();
	std::string gameType = updatedInfo.back();
	updatedInfo.pop_back();
	std::string map = updatedInfo.back();
	updatedInfo.pop_back();
	room->updateGameInfo(map, gameType, gameTime, instaDeath == "1");
	updatedInfo.push_back(map);
	updatedInfo.push_back(gameType);
	updatedInfo.push_back(gameTime);
	updatedInfo.push_back(instaDeath);


	/*if (gameHasStarted == "YES")
	{
		if (user_->getUserName() != gameControl_->getRoom()->getHostName())
			initializeMultiplayerGame();
	}*/

	success = true;
	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 45: Mettre à jour les informations des joueurs de la salle de jeu actuelle
bool CommsControl::executeUpdateGameRoomPlayerInfo(std::vector<std::string> &updatedInfo, bool &success)
{
	obtainSecureLock("UpdateGameRoomPlayerInfo");
	success = false;
	if (gameControl_->getRoom() == nullptr)
	{
		releaseSecureLock();
		return false;
	}
	//std::cout << "Updating Game Room Information" << std::endl;
	int verb = 45;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	// Receive Updated Information
	std::vector<std::string> vectorin;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socketCommunication_, vectorin))
	{
		
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	updatedInfo = vectorin;

	std::string hostIP = updatedInfo.back();
	updatedInfo.pop_back();
	GameRoom* room = gameControl_->getRoom();
	room->setHostIP(new IP(hostIP));
	std::string gameHasStarted = updatedInfo.back();
	updatedInfo.pop_back();

	std::string check1 = user_->getUserName() + ":RDY";
	std::string check2 = user_->getUserName() + ":NOT";
	for (int i = 1; i < 4; i++)
	{
		if (updatedInfo[i] == check1 || updatedInfo[i] == check2)
		{
			gameControl_->getRoom()->addPlayerToSlot(user_, i+1);
		}
		else
		{
			std::string toSplit = updatedInfo[i];
			std::vector <std::string> cutName = Utilitaire::stringSplit(toSplit, ":");
			gameControl_->getRoom()->addPlayerToSlot(new User(cutName[0], "temp", "temp"), i+1);
			gameControl_->getRoom()->setPlayerReady(new User(cutName[0], "temp", "temp"), cutName[1] == "RDY");
		}
	}
	if (gameHasStarted == "YES")
	{
		if (user_->getUserName() != gameControl_->getRoom()->getHostName())
			if (gameControl_->getGameStatus() == gameControl_->etatPartieNOTHING ||
				gameControl_->getGameStatus() == gameControl_->etatPartieLOBBY)
			{
				// Terminaison de la connection avec le thread principal du serveur
				delete socketCommunication_;
				socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
				releaseSecureLock();
				// Départ de la partie multijoueurs
				initializeMultiplayerGame(); 
				success = true;
				return true;
			}
	}

	success = true;
	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 50: Obtenir les informations pour se reconnecter à une partie pré-existante
bool CommsControl::executeRejoinPreviousGame(bool &success)
{
	obtainSecureLock("RejoinPreviousGame");
	success = false;

	// TODO later and also design on serverside first

	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region// // // Game Map Related

/// Verb 61: Download toutes les cartes disponibles du serveur
bool CommsControl::executeDownloadMap(bool &success)
{
	obtainSecureLock("DownloadMap");
	success = false;
	std::vector<std::string> names;
	std::vector<std::string> maps;
	std::vector<std::string> images;
	std::cout << "Receiving New Files From Server" << std::endl;

	int verb = 61;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	// Receive number of maps
	int numberOfMaps = -1;
	if (!AbstractSocket::ReceiveInt(socketCommunication_, numberOfMaps))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	if (numberOfMaps == -1)
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	// Receive Map Names
	for (int i = 0; i < numberOfMaps; i++)
	{
		std::string thisName;
		// Receive map name Information
		if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, thisName))
		{
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			std::cout << "Failed When Receiving Names" << std::endl;
			releaseSecureLock();
			return false;
		}
		names.push_back(thisName);
	}
	std::cout << "    All Names Received" << std::endl;

	// Receive Map Data
	for (int i = 0; i < numberOfMaps; i++)
	{
		std::string thisMap;
		if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, thisMap))
		{
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			std::cout << "Failed When Receiving Map Data" << std::endl;
			releaseSecureLock();
			return false;
		}
		maps.push_back(thisMap);
	}
	std::cout << "    All Map Data Received" << std::endl;
	
	// Receive Map Images
	AbstractSocket::UDPSocket* udpSocket = new AbstractSocket::UDPSocket(assignedPort_);
	for (int i = 0; i < numberOfMaps; i++)
	{
		std::string thisImage;
		// Receive map images Information
		IP* sender = new IP();
		if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, thisImage))
		//if (!AbstractSocket::ReceiveStringPackage(socketCommunication_, udpSocket, thisImage, sender))
		{
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			std::cout << "Failed When Receiving Images" << std::endl;
			releaseSecureLock();
			return false;
		}
		images.push_back(thisImage);
		delete sender;
	}
	std::cout << "    All Map Image Received" << std::endl;

	while (!maps.empty())
	{
		std::string mapName = names.back();
		names.pop_back();
		std::string fileNameMap = "..\\Exe\\zones\\" + mapName + ".xml";
		std::string fileNameImage = "..\\Exe\\zones\\" + mapName + ".jpg";
		std::string infoMap = maps.back();
		maps.pop_back();
		std::string infoImage = images.back();
		images.pop_back();

		// Structure XML pour la reception
		tinyxml2::XMLDocument document;
		document.Parse(infoMap.c_str(), infoMap.size());
		document.SaveFile(fileNameMap.c_str());

		std::ofstream newPic;
		newPic.open(fileNameImage, std::ios::binary);
		newPic << infoImage;
		newPic.close();
	}

	std::cout << "Successfully Received " << numberOfMaps << " New Files From Server" << std::endl;
	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	delete udpSocket;
	success = true;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}
/// Verb 62: Upload toutes les cartes modifiées au serveur
bool CommsControl::executeUploadMap(bool &success)
{
	obtainSecureLock("UploadMap");
	success = false;

	std::cout << "Sending New Files To Server" << std::endl;
	int verb = 62;
	if (!AbstractSocket::SendVerb(socketCommunication_, serverIPStr_, serverDedicatedPort_, verb))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	
	std::vector<std::string> names;
	std::vector<std::string> maps;
	std::vector<std::string> images;

	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR szDir[MAX_PATH];
	DWORD dwError = 0;

	// Prepare string for use with FindFile functions. Copy the
	// string to a buffer.
	std::string path = "..\\exe\\zones\\";
	StringCchCopy(szDir, MAX_PATH, (path + "*.xml").c_str());

	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		std::cout << "Fail: incapable de trouver le premier fichier" << std::endl;
		if (!AbstractSocket::SendInt(socketCommunication_, -1))
		{
			delete socketCommunication_;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}
		delete socketCommunication_;
		success = true;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return true;
	}

	// Loading all map data
	do 
	{
		std::string rawFilename = std::string(ffd.cFileName);
		names.push_back(std::string(rawFilename, 0, rawFilename.length() - 4));
		std::ifstream finxml(path + names.back() + ".xml", std::ios::binary);
		std::ostringstream ostrmxml;
		ostrmxml << finxml.rdbuf();
		maps.push_back(ostrmxml.str());
		std::ifstream finjpg(path + names.back() + ".jpg", std::ios::binary);
		std::ostringstream ostrmjpg;
		ostrmjpg << finjpg.rdbuf();
		images.push_back(ostrmjpg.str());

	}
	while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{
		std::cout << "Fail: incapable de trouver le premier fichier" << std::endl;
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}
	FindClose(hFind);

	// Send number of maps
	if (!AbstractSocket::SendInt(socketCommunication_, (int32_t)maps.size()))
	{
		delete socketCommunication_;
		socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
		releaseSecureLock();
		return false;
	}

	// Send Map Names
	for (int i = 0; i < maps.size(); i++)
		if (!AbstractSocket::SendStringPackage(socketCommunication_, names[i]))
		{
			delete socketCommunication_;
			std::cout << "Failed When Sending Names" << std::endl;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}

	// Send Map Data
	std::cout << "    All Names Sent" << std::endl;
	for (int i = 0; i < maps.size(); i++)
		if (!AbstractSocket::SendStringPackage(socketCommunication_, maps[i]))
		{
			delete socketCommunication_;
			std::cout << "Failed When Sending Map Data" << std::endl;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}
	std::cout << "    All Map Data Sent" << std::endl;

	// Send Map Images
	AbstractSocket::UDPSocket* udpSocket = new AbstractSocket::UDPSocket(assignedPort_);
	for (int i = 0; i < maps.size(); i++)
		if (!AbstractSocket::SendStringPackage(socketCommunication_, images[i]))
		//if (!AbstractSocket::SendStringPackage(socketCommunication_, udpSocket, images[i], serverIPClass_))
		{
			delete socketCommunication_;
			std::cout << "Failed When Sending Images" << std::endl;
			socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
			releaseSecureLock();
			return false;
		}
	std::cout << "    All Map Images Sent" << std::endl;

	std::cout << "Successfully Sent " << maps.size() << " Files To Server" << std::endl;
	// Terminaison de la connection avec le thread principal du serveur
	delete socketCommunication_;
	delete udpSocket;
	success = true;
	socketCommunication_ = new AbstractSocket::TCPSocket(assignedPort_);
	releaseSecureLock();
	return true;
}

#pragma endregion