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

#include "ServerControl.h"
#include <Windows.h>
#include <winsock2.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <future>
#include <iostream>
#include <stdint.h>
#include <thread>
#include <future>
#include <tchar.h>
#include <strsafe.h>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include "..\..\..\SharedFiles\AbstractSocketV2.h"
#include "../../../SharedFiles/IP.h"
#include "..\..\..\SharedFiles\Utilitaire.h"
#include "../XML/tinyxml2.h"

// link with Ws2_32.lib
#pragma comment( lib, "ws2_32.lib" )

////////////////////////////////////
#pragma region // Constructeur / Destructeurs / Static Pointer
/// Initialize Static pointer
ServerControl* ServerControl::ServerControlPointer = nullptr;
/// Static function to obtain pointer to main form
ServerControl* ServerControl::getPointer()
{
	if (ServerControlPointer == nullptr)
		ServerControlPointer = new ServerControl();
	return ServerControlPointer;
}
/// Constructeur
ServerControl::ServerControl()
{
	serverData_ = ServerData::getPointer();
	if (serverData_->safetyMutexIsLocked_ && serverData_->safetyMutexLastCaller != "")
	{
		serverData_->safetyMutex_.unlock();
		serverData_->safetyMutexIsLocked_ = false;
		serverData_->safetyMutexLastCaller = "";
	}
	for (int i = 0; i < MAX_SOCKET_ALLOWED; i++)
		portStatus_.push_back(new PortStatus(5001+i, serverData_));
	ServerControlPointer = this;
}
/// Destructeur
ServerControl::~ServerControl()
{
	while (!portStatus_.empty())
	{
		PortStatus* p = portStatus_.back();
		portStatus_.pop_back();
		delete p;
	}
	while (!TCPSocketList_.empty())
	{
		AbstractSocket::TCPSocket* s = TCPSocketList_.back();
		TCPSocketList_.pop_back();
		delete s;
	}
	WSACleanup();
	ServerControlPointer = nullptr;
}
#pragma endregion

////////////////////////////////////
#pragma region // Multithreading safety
/// Obtain Secure ServerData Lock
void ServerControl::obtainSecureLock(std::string lastCaller)
{
	serverData_->safetyMutex_.lock();
	serverData_->safetyMutexIsLocked_ = true;
	serverData_->safetyMutexLastCaller = lastCaller;
}
/// Release Secure ServerData Lock
void ServerControl::releaseSecureLock()
{
	serverData_->safetyMutex_.unlock();
	serverData_->safetyMutexIsLocked_ = false;
	serverData_->safetyMutexLastCaller = "";
}
#pragma endregion

////////////////////////////////////
#pragma region // Fonctions Autres
/// Print timestamp to console
void ServerControl::printTimestamp(std::string message)
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

/// Disconnect everyone from the server
void ServerControl::disconnectEveryone()
{
	for (auto port : portStatus_)
	{
		port->logoutUser();
	}
}

/// Disconnect specific user from the server
void ServerControl::disconnectUser(std::string username)
{
	for (auto port : portStatus_)
	{
		if (port->getUser() != nullptr)
			if (port->getUser()->getUserName() == username)
			{
				port->logoutUser();
				break;
			}
	}
}

/// Thread principal du projet
bool ServerControl::mainThreadLoop()
{
	if (!initializeCommunications())
		return true;
	IP* ip = AbstractSocket::getLocalIP();
	while (!ALL_THREADS_ARE_DEAD)
	{
		// Do things like waiting for user commands
		std::string command;
		std::cin >> command;
		if (command == "help")
		{
			std::cout << "Listing all commands: " << std::endl;
			std::cout << "kill: stop server" << std::endl;
			std::cout << "refresh: refresh server sockets" << std::endl;
			std::cout << "resetsecurity: reset all passwords to 12345" << std::endl;
			std::cout << "resetconnections: kick everyone" << std::endl;
		}
		if (command == "kill")
		{
			GLOBAL_KILL_THREAD_ORDER = true;
			std::cout << "Shutting down in 5 seconds";
			for (int i = 0; i < 5; i++)
			{
				Sleep(1000);
				std::cout << ".";
			}
			std::cout << std::endl << "Shutting down" << std::endl;
			
			ALL_THREADS_ARE_DEAD = true;
			WSACleanup();
		}
		if (command == "resetsecurity")
		{
			obtainSecureLock("User Function: Reset All Passwords");
			serverData_->userControl_->resetAllPasswords(Utilitaire::encryptDecrypt("12345"));
			releaseSecureLock();
		}
		if (command == "resetconnections")
		{
			obtainSecureLock("User Function: Disconnect Everyone");
			disconnectEveryone();
			releaseSecureLock();
		}
		if (command == "refresh")
		{
			GLOBAL_KILL_THREAD_ORDER = true;
			Sleep(1000);
			std::cout << std::endl << "Refreshing" << std::endl;

			ALL_THREADS_ARE_DEAD = true;
			WSACleanup();
			return false;
		}
		std::cin.clear();
	}
	return true;
}
#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // Threaded Communication
/// Thread de communication 5000: Connection TCP et obtention de port unique
int MultiThreadConnectionHandling(AbstractSocket::TCPSocket* sd_, ServerControl* control_)
{
	sockaddr_in sinRemote;
	int nAddrSize = sizeof(sinRemote);
	while (true)
	{
		// Vérification pour l'ordre d'éxecution des threads
		if (control_->GLOBAL_KILL_THREAD_ORDER)
		{
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
		std::string IPstr;
		// Connection en attente
		int selectReturn = select(sd_->socket_, &readSet, NULL, NULL, &timeout);
		if (selectReturn >= 1)
		{
			// Create a SOCKET for accepting incoming requests.
			// Accept the connection in  blocking
			socketTemp = new AbstractSocket::TCPSocket(accept(sd_->socket_, (sockaddr*)&sinRemote, &nAddrSize), sd_->port_);
			if (socketTemp->socket_ != INVALID_SOCKET) 
			{
				IPstr = inet_ntoa(sinRemote.sin_addr);
			}
			else 
			{
				delete socketTemp;
				int err = WSAGetLastError();
				std::cout << "Erreur dans la connexion initiale! Accept err no: " << err << std::endl;
				continue;
			}
		}
		else 
			if (selectReturn == 0) // Timeout, no one's here
			{
				continue;
			}
			else // Some Socket Error
			{
				int err = WSAGetLastError();
				std::cout << "Erreur dans la connexion initiale! Select err no: " << err << std::endl;
				continue;
			}

		// Préléminaire: Obtenir les infos de l'utilisateur
		sockaddr_in peeraddr;
		int size = sizeof(peeraddr);
		getsockname(socketTemp->socket_, (struct sockaddr *)&peeraddr, &size);
		struct sockaddr_in *s = (struct sockaddr_in *)&peeraddr;
		std::string port = std::to_string(ntohs(peeraddr.sin_port));
		std::cout << "Connection acceptee au port 5000 de : " << IPstr << ":" << port << "." << std::endl;

		// Étape 1: Reception du handshake initial "hi" de la taille depuis l'utilisateur
		std::string handShakeMessage;
		bool handshakeSuccess = AbstractSocket::ReceiveString(socketTemp, 2, handShakeMessage);
		if (!handshakeSuccess)
		{
			delete socketTemp;
			continue;
		}
		if (handShakeMessage != "hi")
		{
			delete socketTemp;
			continue;
		}

		// Obtention d'un port libre
		//**************************//
		control_->obtainSecureLock("Initial Connection Handling");
		//**************************//
		IP* newClientIP = new IP(IPstr);
		int32_t availablePort = -1;
		auto it = control_->portStatus_.begin();
		while (it != control_->portStatus_.end())
		{
			PortStatus* p = (*it);
			if (p->isUsed())
				if (p->getRemoteIP()->getStringIP() == newClientIP->getStringIP())
					p->markAbandonned();
			++it;
		}
		it = control_->portStatus_.begin();
		while (availablePort == -1 && it != control_->portStatus_.end())
		{
			PortStatus* p = (*it);
			if (!p->isUsed())
			{
				p->markUsed();
				availablePort = p->getPortNumber();
				p->setRemoteIP(newClientIP);
			}
			++it;
		}
		//**************************//
		control_->releaseSecureLock();
		//**************************//

		// Étape 2: Envoie du premier port de connection libre
		std::cout << "Reconnexion au port " << availablePort << "." << std::endl;
		bool portSendSuccess = AbstractSocket::SendInt(socketTemp, availablePort);
		if (!portSendSuccess)
		{
			delete socketTemp;
			continue;
		}
		// Nettoyage
		delete socketTemp;
	}
	return 0;
}

/// Thread de communication 5001-5050: Connection TCP et communication privée avec client
int MultiThreadUserHandling(AbstractSocket::TCPSocket* sd_, ServerControl* control_, PortStatus* thisPortStatus_)
{
	std::vector<int> ret;
	sockaddr_in sinRemote;
	int nAddrSize = sizeof(sinRemote);
	while (true)
	{
		// Vérification pour l'ordre d'éxecution des threads
		if (control_->GLOBAL_KILL_THREAD_ORDER)
		{
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
		std::string IPstr;
		int a, b, c, d;
		// Connection en attente
		int selectReturn = select(sd_->socket_, &readSet, NULL, NULL, &timeout);
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
				int err = WSAGetLastError();
				std::cout << "Erreur dans la connexion initiale! Accept err no: " << err << std::endl;
				continue;
			}
			//SOCKET socket = (SOCKET)sd_->socket_;
		}
		else // Aucune connection en attente
		{
			// Timeout, no one's here
			if (selectReturn == 0) 
			{
			}
			else // Some Socket Error
			{
				int err = WSAGetLastError();
				std::cout << "Erreur dans la connexion initiale! Select err no: " << err << std::endl;
			}
			// Check if port is abandonned
			if (thisPortStatus_->checkTimeout())
			{
				thisPortStatus_->markAbandonned();
			}
			continue;
		}

		// Préléminaire: Obtenir les infos de l'utilisateur
		sockaddr_in peeraddr;
		int size = sizeof(peeraddr);
		getsockname(socketTemp->socket_, (struct sockaddr *)&peeraddr, &size);
		struct sockaddr_in *s = (struct sockaddr_in *)&peeraddr;
		std::string port = std::to_string(ntohs(peeraddr.sin_port));
		//std::cout << "Communication acceptee De : " << IP << ":" << port << "." << std::endl;
		
		// Réception du Verbe
		int32_t receivedVerb;
		if (!AbstractSocket::ReceiveInt(socketTemp, receivedVerb))
		{
			delete socketTemp;
			continue;
		}

		//std::cout << "Verbe recu: " << receivedVerb << "." << std::endl;

		// Traitement du Verbe
		try
		{
			bool verbResponse = false;
			switch (receivedVerb)
			{
				// Liste des cas où l'utilisateur doit être connecté
			case 1:
			case 10:
			case 13:
			case 14:
			case 21:
			case 22:
			case 23:
			case 31:
			case 32:
			case 33:
			case 34:
			case 35:
			case 41:
			case 42:
			case 44:
			case 45:
			case 50:
			case 61:
			case 62:
				if (!control_->executeSendVerbResponse(socketTemp, thisPortStatus_, true, new IP(a, b, c, d)))
				{
					verbResponse = false;
					break;
				}
				verbResponse = true;
				break;
				// Liste des cas où l'utilisateur peut ne pas être connecté
			case 0:
			case 11:
			case 12:
			case 15:
			case 69:
				if (!control_->executeSendVerbResponse(socketTemp, thisPortStatus_, false, new IP(a, b, c, d)))
				{
					verbResponse = false;
					break;
				}
				verbResponse = true;
				break;
			}
			if (verbResponse)
			{
				switch (receivedVerb)
				{
				case -1:
					control_->commsTest(socketTemp, thisPortStatus_);
					break;
				case 0:
					control_->executeAbandonSocket(socketTemp, thisPortStatus_);
					break;
				case 1:
					control_->executeKeepAlive(socketTemp, thisPortStatus_);
					break;
				case 10:
					control_->executeLogout(socketTemp, thisPortStatus_);
					break;
				case 11:
					control_->executeLogin(socketTemp, thisPortStatus_);
					break;
				case 12:
					control_->executeCreateUserAccount(socketTemp, thisPortStatus_);
					break;
				case 13:
					control_->executeGetUserAccountInfo(socketTemp, thisPortStatus_);
					break;
				case 14:
					control_->executeUpdateUserAccountInfo(socketTemp, thisPortStatus_);
					break;
				case 15:
					control_->executeResetUserAccountPassword(socketTemp, thisPortStatus_);
					break;
				case 21:
					control_->executeUpdateChatRoomList(socketTemp, thisPortStatus_);
					break;
				case 22:
					control_->executeSendNewChatMessage(socketTemp, thisPortStatus_);
					break;
				case 23:
					control_->executeRequestMessageHistoryUpdate(socketTemp, thisPortStatus_);
					break;
				case 69:
					control_->commsTest(socketTemp, thisPortStatus_);
					break;
				case 31:
					control_->executeUpdateGameRoomList(socketTemp, thisPortStatus_);
					break;
				case 32:
					control_->executeCreateGameRoom(socketTemp, thisPortStatus_);
					break;
				case 33:
					control_->executeJoinGameRoom(socketTemp, thisPortStatus_);
					break;
				case 34:
					control_->executeMatchmaking(socketTemp, thisPortStatus_);
					break;
				case 35:
					control_->executeLeaveGameRoom(socketTemp, thisPortStatus_);
					break;
				case 41:
					control_->executeStartGame(socketTemp, thisPortStatus_);
					break;
				case 42:
					control_->executeSetReady(socketTemp, thisPortStatus_);
					break;
				case 44:
					control_->executeUpdateGameRoomInfo(socketTemp, thisPortStatus_);
					break;
				case 45:
					control_->executeUpdateGameRoomPlayerInfo(socketTemp, thisPortStatus_);
					break;
				case 50:
					control_->executeRejoinPreviousGame(socketTemp, thisPortStatus_);
					break;
				case 61:
					control_->executeDownloadMap(socketTemp, thisPortStatus_);
					break;
				case 62:
					control_->executeUploadMap(socketTemp, thisPortStatus_);
					break;
				default:
					break;
				}
			}
			else
			{
   				std::cout << "Verb refused: " << receivedVerb << " from IP: " << IPstr << "." << std::endl;
			}
		}
		catch (std::exception ex)
		{
			std::cout << "UNEXPECTED EXCEPTION." << ex.what() << std::endl;
			std::cout << "OCCURED WHEN HANDLING VERB: " << receivedVerb << " ON IP: " << IPstr << "." << std::endl;
		}
		thisPortStatus_->resetTimeout();

		// Nettoyage
		delete socketTemp;
	}
	return 0;
}
#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // Connection related
/// Initialize ServerSide Communications Ports and Threading
bool ServerControl::initializeCommunications()
{
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

	// Initialisation de Winsock
	//std::cout << ":::Initialisation du serveur:::" << std::endl;
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		std::cerr << "Error at WSAStartup()";
		return false;
	}
	// Création des sockets
	try {
		createSocketVector();
	}
	catch (...) {
		std::cout << "Erreur de connections lors de la creation des sockets. Abandon." << std::endl;
		system("pause");
		return false;
	}

	// Lancement des threads asynchrones de handling des utilisateurs
	threadList_.push_back(new std::thread(&MultiThreadConnectionHandling, TCPSocketList_[0], this));
	auto it = portStatus_.begin();
	for (int i = 1; i <= MAX_SOCKET_ALLOWED; i++)
	{
		threadList_.push_back(new std::thread(&MultiThreadUserHandling, TCPSocketList_[i], this, (*it)));
		++it;
	}
	for (auto thread : threadList_)
		thread->detach();
	//std::cout << "Connections etablies avec succes. Debut de l'ecoute." << std::endl;
	return true;
}
/// Initialize ServerSide Sockets
void ServerControl::createSocketVector()
{
	// Établi les connections des SOCKETS requis pour écouter sur les ports 
	// 5000 à 5050 et les retourne dans un vecteur
	for (int i = 0; i <= MAX_SOCKET_ALLOWED; i++)
	{
		// Création du socket
		AbstractSocket::TCPSocket* socket = new AbstractSocket::TCPSocket(5000 + i);
		// Ajout du socket à la liste
		TCPSocketList_.push_back(socket);
	}
}
/// Verb 69: Test communications
bool ServerControl::commsTest(AbstractSocket::TCPSocket* socketTCP, PortStatus* portStatus)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "COMMS TEST: Executing Comms Test" << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int in = -1;
	if (!AbstractSocket::ReceiveInt(socketTCP, in))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVEINT" << std::endl;
		closesocket(socketTCP->socket_);
		return false;
	}
	//std::cout << "COMMS TEST: INT RECEIVED: " << in << std::endl;

	int out = 55;
	if (!AbstractSocket::SendInt(socketTCP, out))
	{
		std::cout << "COMMS TEST FAIL AT SENDINT" << std::endl;
		closesocket(socketTCP->socket_);
		return false;
	}
	//std::cout << "COMMS TEST: INT SENT: " << out << std::endl;

	for (int i = 0; i < 10; i++)
	{
		std::string messagein;
		if (!AbstractSocket::ReceiveString(socketTCP, in, messagein))
		{
			std::cout << "COMMS TEST FAIL AT RECEIVESTRING" << std::endl;
			closesocket(socketTCP->socket_);
			return false;
		}
	//	std::cout << "COMMS TEST: STRING RECEIVED OF LENGTH: " << messagein.length() << "/" << in << std::endl << messagein << std::endl;

		std::string messageout(out, 'z' - i);
		if (!AbstractSocket::SendString(socketTCP, messageout))
		{
			std::cout << "COMMS TEST FAIL AT SENDSTRING" << std::endl;
			closesocket(socketTCP->socket_);
			return false;
		}
	//	std::cout << "COMMS TEST: STRING SENT OF LENGTH: " << messageout.length() << "/" << out << std::endl << messageout << std::endl;
	}

	std::string messagein;
	if (!AbstractSocket::ReceiveString(socketTCP, in, messagein))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVESTRING" << std::endl;
		closesocket(socketTCP->socket_);
		return false;
	}
	//std::cout << "COMMS TEST: STRING RECEIVED OF LENGTH: " << messagein.length() << std::endl << messagein << std::endl;

	std::string messageout(out, 'a');
	if (!AbstractSocket::SendString(socketTCP, messageout))
	{
		std::cout << "COMMS TEST FAIL AT SENDSTRING" << std::endl;
		closesocket(socketTCP->socket_);
		return false;
	}
	//std::cout << "COMMS TEST: STRING SENT OF LENGTH: " << messageout.length() << std::endl << messageout << std::endl;

	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socketTCP, packagein))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVESTRINGPACKAGE" << std::endl;
		closesocket(socketTCP->socket_);
		return false;
	}
	//std::cout << "COMMS TEST: STRING PACKAGE RECEIVED OF LENGTH: " << packagein.length() << std::endl << packagein << std::endl;

	std::string packageout = "le tabarouette de string";
	if (!AbstractSocket::SendStringPackage(socketTCP, packageout))
	{
		std::cout << "COMMS TEST FAIL AT SENDSTRINGPACKAGE" << std::endl;
		closesocket(socketTCP->socket_);
		return false;
	}
	//std::cout << "COMMS TEST: STRING PACKAGE SENT OF LENGTH: " << packageout.length() << std::endl << packageout << std::endl;

	std::vector<std::string> vectorin;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socketTCP, vectorin))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVEMULTIPLESTRINGPACKAGE" << std::endl;
		closesocket(socketTCP->socket_);
		return false;
	}
	//std::cout << "COMMS TEST: MULTIPLE STRING PACKAGE RECEIVED: " << vectorin.size() << std::endl;
	//for (std::string message : vectorin)
	//	std::cout << message << std::endl;

	std::vector<std::string> vectorout = { "un petit string", "un ben ben ben ben ben ben ben ben plus gros string", "un string pareil",
		"un autre string pareil", "un calisse de string avec un backslash n\n de calisse de marde" };
	if (!AbstractSocket::SendMultipleStringPackage(socketTCP, vectorout))
	{
		std::cout << "COMMS TEST FAIL AT SENDMULTIPLESTRINGPACKAGE" << std::endl;
		closesocket(socketTCP->socket_);
		return false;
	}
	//std::cout << "COMMS TEST: MULTIPLE STRING PACKAGE SENT OF SIZE: " << vectorout.size() << std::endl;
	//for (std::string message : vectorout)
	//	std::cout << message << std::endl;


	std::vector<int> intvectorin;
	if (!AbstractSocket::ReceiveMultipleIntPackage(socketTCP, intvectorin))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVEMULTIPLESTRINGPACKAGE" << std::endl;
		closesocket(socketTCP->socket_);
		return false;
	}
	//std::cout << "COMMS TEST: MULTIPLE STRING PACKAGE RECEIVED OF SIZE: " << intvectorin.size() << std::endl;
	//for (int message : intvectorin)
	//	std::cout << std::to_string(message) << std::endl;

	std::vector<int> intvectorout;
	for (int i = 0; i < 10; i++)
		intvectorout.push_back(i);
	if (!AbstractSocket::SendMultipleIntPackage(socketTCP, intvectorout))
	{
		std::cout << "COMMS TEST FAIL AT SENDMULTIPLEINTPACKAGE" << std::endl;
		closesocket(socketTCP->socket_);
		return false;
	}
	//std::cout << "COMMS TEST: MULTIPLE INT PACKAGE SENT OF SIZE: " << intvectorout.size() << std::endl;
	//for (int message : intvectorout)
	//	std::cout << std::to_string(message) << std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "COMMS TEST: All TCP Tests Succesfull" << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	AbstractSocket::UDPSocket* socketUDP = new AbstractSocket::UDPSocket(5036);
	IP* target = new IP();
	IP* sender = new IP();

	int in2 = -1;
	if (!AbstractSocket::ReceiveInt(socketUDP, in2, target))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVEINT" << std::endl;
		delete socketUDP;
		return false;
	}
	//std::cout << "COMMS TEST: INT RECEIVED: " << in << std::endl;

	if (!AbstractSocket::SendInt(socketUDP, out, target))
	{
		std::cout << "COMMS TEST FAIL AT SENDINT" << std::endl;
		delete socketUDP;
		return false;
	}
	//std::cout << "COMMS TEST: INT SENT: " << out << std::endl;

	for (int i = 0; i < 10; i++)
	{
		//std::string messagein;
		if (!AbstractSocket::ReceiveString(socketUDP, in, messagein, sender))
		{
			std::cout << "COMMS TEST FAIL AT RECEIVESTRING" << std::endl;
			delete socketUDP;
			return false;
		}
		//	std::cout << "COMMS TEST: STRING RECEIVED OF LENGTH: " << messagein.length() << "/" << in << std::endl << messagein << std::endl;

		std::string messageout(out, 'z');
		if (!AbstractSocket::SendString(socketUDP, messageout, target))
		{
			std::cout << "COMMS TEST FAIL AT SENDSTRING" << std::endl;
			delete socketUDP;
			return false;
		}
		//	std::cout << "COMMS TEST: STRING SENT OF LENGTH: " << messageout.length() << "/" << out << std::endl << messageout << std::endl;
	}

	messagein.clear();
	if (!AbstractSocket::ReceiveString(socketUDP, in, messagein, sender))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVESTRING" << std::endl;
		delete socketUDP;
		return false;
	}
	//std::cout << "COMMS TEST: STRING RECEIVED OF LENGTH: " << messagein.length() << std::endl << messagein << std::endl;

	if (!AbstractSocket::SendString(socketUDP, messageout, target))
	{
		std::cout << "COMMS TEST FAIL AT SENDSTRING" << std::endl;
		delete socketUDP;
		return false;
	}
	//std::cout << "COMMS TEST: STRING SENT OF LENGTH: " << messageout.length() << std::endl << messageout << std::endl;

	//packagein.clear();
	//if (!AbstractSocket::ReceiveStringPackage(socketUDP, packagein, sender))
	//{
	//	std::cout << "COMMS TEST FAIL AT RECEIVESTRINGPACKAGE UDP ONLY" << std::endl;
	//	delete socketUDP;
	//	return false;
	//}
	////std::cout << "COMMS TEST: STRING PACKAGE RECEIVED OF LENGTH: " << packagein.length() << std::endl << packagein << std::endl;

	//if (!AbstractSocket::SendStringPackage(socketUDP, packageout, target))
	//{
	//	std::cout << "COMMS TEST FAIL AT SENDSTRINGPACKAGE UDP ONLY" << std::endl;
	//	delete socketUDP;
	//	return false;
	//}
	//std::cout << "COMMS TEST: STRING PACKAGE SENT OF LENGTH: " << packageout.length() << std::endl << packageout << std::endl;

	packagein.clear();
	std::string longmessage = std::string(2000, '*');
	if (!AbstractSocket::ReceiveStringPackage(socketTCP, socketUDP, packagein, sender))
	{
		std::cout << "COMMS TEST FAIL AT RECEIVESTRINGPACKAGE UDP TCP" << std::endl;
		delete socketUDP;
		return false;
	}
	//std::cout << "COMMS TEST: STRING PACKAGE RECEIVED OF LENGTH: " << packagein.length() << std::endl << packagein << std::endl;

	if (!AbstractSocket::SendStringPackage(socketTCP, socketUDP, longmessage, target))
	{
		std::cout << "COMMS TEST FAIL AT SENDSTRINGPACKAGE UDP TCP" << std::endl;
		delete socketUDP;
		return false;
	}
	//std::cout << "COMMS TEST: STRING PACKAGE SENT OF LENGTH: " << packageout.length() << std::endl << packageout << std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "COMMS TEST: All UDP Tests Succesfull" << std::endl;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	delete socketUDP;

	return true;
}
/// Send Verb Response to Client query
bool ServerControl::executeSendVerbResponse(AbstractSocket::TCPSocket* socket, PortStatus* portStatus, bool requiresLogin, IP* remoteIP)
{
	// Retourne la réponse initiale au Verbe
	// ACK-VERB-F si l'utilisateur n'est pas connecté et qu'il devrait l'être
	bool ret = true;
	std::string packageout;
	if (portStatus->getRemoteIP()->getStringIP() != remoteIP->getStringIP())
	{
		packageout = "ACK-VERB-I";
	}
	else
	{
		if (!portStatus->isUsed())
		{
			packageout = "ACK-VERB-C";
		}
		else
		{
			if (requiresLogin)
			{
				if (portStatus->userIsLogged())
				{
					packageout = "ACK-VERB-S";
				}
				else
				{
					packageout = "ACK-VERB-F";
					std::cout << "User Not Logged In." << std::endl;
					ret = false;
				}
			}
			else
			{
				packageout = "ACK-VERB-S";
			}
		}
	}
	
	if (!AbstractSocket::SendStringPackage(socket, packageout))
	{
		
		return false;
	}
	return ret;
}
/// Verb 0: Abandon dedicated link to client
void ServerControl::executeAbandonSocket(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	std::cout << "Abandonning Socket: " << portStatus->getPortNumber() << std::endl;
	portStatus->markAbandonned();
	std::string packageout = "ACK-S";
	if (!AbstractSocket::SendStringPackage(socket, packageout))
	{
		
		return;
	}
}
/// Verb 1: Keep Alive sur le socket
void ServerControl::executeKeepAlive(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	std::string messagein; // HEART
	if (!AbstractSocket::ReceiveString(socket, 5, messagein))
	{
		
		return ;
	}

	std::string packageout = messagein == "HEART" ? "BEAT" : "DEAD";
	if (!AbstractSocket::SendString(socket, packageout))
	{
		
		return;
	}
}
#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // User Account Related
/// Verb 12: Création de compte Utilisateur
void ServerControl::executeCreateUserAccount(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	std::cout << "Creating New User Account" << std::endl;

	std::vector<std::string> vectorin;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socket, vectorin))
	{
		
		return ;
	}
	std::string username = vectorin[0];
	std::string pass = Utilitaire::encryptDecrypt(vectorin[1]);
	std::string email = vectorin[2];
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 12: Create User Account");
	//**************************//
	bool success = serverData_->userControl_->createUser(username, pass, email);

	/// Insertion dans la base de données
	if (success)
	{
		User* user = serverData_->userControl_->getUser(username);
		serverData_->userControl_->insertDatabase(*user);
	}

	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//
	std::string packageout = success ? "ACK-S" : "ACK-F";
	if (success)
		std::cout << "New User Account: " << username << std::endl;
	if (!AbstractSocket::SendStringPackage(socket, packageout))
	{
		
		return ;
	}
}
/// Verb 11: Login avec compte Utilisateur
void ServerControl::executeLogin(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	std::cout << "Logging in user with credentials" << std::endl;

	std::vector<std::string> vectorin;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socket, vectorin))
	{
		
		return;
	}
	std::string username = vectorin[0];
	std::string pass = Utilitaire::encryptDecrypt(vectorin[1]);
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 11: Login");
	//**************************//
	bool success = false;
	if (portStatus->userIsLogged())
	{
		std::cout << "User already logged in. Logging out user: " << portStatus->getUser()->getUserName() << std::endl;
		portStatus->logoutUser();
	}
	if (!portStatus->userIsLogged() && serverData_->userControl_->getUser(username) != nullptr)
	{
		success = serverData_->userControl_->loginUser(username, pass);
		if (!success)
		{
			std::cout << "User: " << username << " already logged in. Kicking previous user." << std::endl;
			disconnectUser(username);
			success = serverData_->userControl_->loginUser(username, pass);
		}
	}
	std::string packageout = success ? "ACK-S" : "ACK-F";
	if (success)
	{
		std::cout << "Logged user: " << username << std::endl;
		User* user = serverData_->userControl_->getUser(username);
		portStatus->addLoggedUser(user);
	}
	else
	{
		std::cout << "Failed to log user: " << username << std::endl;
	}
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//
	if (!AbstractSocket::SendStringPackage(socket, packageout))
	{
		
		return;
	}
}
/// Verb 10: Logout avec compte Utilisateur
void ServerControl::executeLogout(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	bool success = false;
	if (portStatus->userIsLogged())
	{
		std::string username = portStatus->getUser()->getUserName();
		std::cout << "Logging out user: " << username << std::endl;
		//**************************//
		ServerControl::getPointer()->obtainSecureLock("Verb 10: Logout");
		//**************************//
		success = serverData_->userControl_->logoutUser(username);
		//**************************//
		ServerControl::getPointer()->releaseSecureLock();
		//**************************//
		portStatus->setFirstMessageUpdate(true);
	}
	std::string packageout;
	if (success)
	{
		portStatus->logoutUser();
		packageout = "ACK-S";
	}
	else
		packageout = "ACK-F";
	if (!AbstractSocket::SendStringPackage(socket, packageout))
	{
		
		return;
	}
}
/// Verb 13: Obtenir les informations du compte Utilisateur
void ServerControl::executeGetUserAccountInfo(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{	
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 13: Get User Account Info");
	//**************************//
	User* user = portStatus->getUser();
	std::vector<std::string> vectorout1 = user->getBasicInfo();
	vectorout1[1] = Utilitaire::encryptDecrypt(vectorout1[1]);
	std::vector<std::string> vectorout2 = user->getMapInfo();
	std::vector<std::string> vectorout3 = user->getAchievementsInfo();
	std::vector<std::string> vectorout4 = user->getAvatarUnlocked();
	std::vector<std::string> vectorout5 = user->obtenirStatistique();
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//
	if (!AbstractSocket::SendMultipleStringPackage(socket, vectorout1))
	{
		
		return;
	}
	if (!AbstractSocket::SendMultipleStringPackage(socket, vectorout2))
	{
		
		return;
	}
	if (!AbstractSocket::SendMultipleStringPackage(socket, vectorout3))
	{
		
		return;
	}
	if (!AbstractSocket::SendMultipleStringPackage(socket, vectorout4))
	{
		
		return;
	}
	if (!AbstractSocket::SendMultipleStringPackage(socket, vectorout5))
	{
		
		return;
	}

	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socket, packagein))
	{
		
		return;
	}
	if (packagein != "ACK-S")
	{
		
		return;
	}
}
/// Verb 14: Mettre à jour les informations du compte Utilisateur
void ServerControl::executeUpdateUserAccountInfo(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	std::vector<std::string> vectorin1;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socket, vectorin1))
	{
		return ;
	}

	std::vector<std::string> vectorin2;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socket, vectorin2))
	{
		return ;
	}

	std::vector<std::string> vectorin3;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socket, vectorin3))
	{
		return ;
	}

	std::vector<std::string> vectorin4;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socket, vectorin4))
	{
		return ;
	}

	std::vector<std::string> vectorin5;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socket, vectorin5))
	{
		return ;
	}
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 14: Update User Account Info");
	//**************************//
	User* user = portStatus->getUser();
	vectorin1[1] = Utilitaire::encryptDecrypt(vectorin1[1]);
	bool res = user->setBasicInfo(vectorin1);
	res &= user->setMapInfo(vectorin2);
	res &= user->setAchievementsInfo(vectorin3);
	res &= user->setAvatarUnlocked(vectorin4);
	user->assignerStatistique(vectorin5);

	/// Mise a jour de la base de données
	if (res)
	{
		serverData_->userControl_->updateDatabase(*user);
	}

	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//

	std::string packageout = res ? "ACK-S" : "ACK-F";
	if (!AbstractSocket::SendStringPackage(socket, packageout))
	{
		
		return ;
	}
}
/// Verb 15: Reset password du compte Utilisateur
void ServerControl::executeResetUserAccountPassword(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	std::string packagein;
	if (!AbstractSocket::ReceiveStringPackage(socket, packagein))
	{
		
		return;
	}
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 15: Reset Password");
	//**************************//
	User* user = ServerControl::getPointer()->serverData_->userControl_->getUser(packagein);
	if (user != nullptr && !user->isLogged())
	{
		// Generate random alphanumerical password
		std::string password = "";
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		for (int i = 0; i < 10; ++i) {
			password += alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		std::string encryptedPassword = Utilitaire::encryptDecrypt(password);
		std::string command = "PasswordRecovery.exe " + password + " " + user->getEmail();
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		if (!CreateProcess(0,							// No module name (use command line)
			const_cast<char *>(command.c_str()),		// Command line
			NULL,										// Process handle not inheritable
			NULL,										// Thread handle not inheritable
			FALSE,										// Set handle inheritance to FALSE
			0,											// No creation flags
			NULL,										// Use parent's environment block
			NULL,										// Use parent's starting directory 
			&si,										// Pointer to STARTUPINFO structure
			&pi)										// Pointer to PROCESS_INFORMATION structure
			)
		{
			printf("CreateProcess failed (%d).\n", GetLastError());
			//					//
			ServerControl::getPointer()->releaseSecureLock();
			//					//
			std::string packageout = "ACK-F";
			if (!AbstractSocket::SendStringPackage(socket, packageout))
			{
				
				return;
			}
			return;
		}

		// Wait until child process exits.
		WaitForSingleObject(pi.hProcess, INFINITE);

		// Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		
		user->setPassword(encryptedPassword);
		ServerControl::getPointer()->serverData_->userControl_->updateDatabase(*user);
	}
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//
	std::string packageout;
	if (user != nullptr)
	{
		if (!user->isLogged())
			packageout = "ACK-S";
		else
			packageout = "ACK-F";
	}
	else
		packageout = "ACK-F";
	if (packageout == "ACK-S")
		std::cout << "PASSWORD RESET FOR USER: " << user->getUserName();
	if (!AbstractSocket::SendStringPackage(socket, packageout))
	{
		return;
	}
}
#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // Chat Related
/// Verb 21: Obtenir la liste des salles de chat
void ServerControl::executeUpdateChatRoomList(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	//std::cout << "Updating local user Chatroom list" << std::endl;

	if (!portStatus->userIsLogged())
	{
		std::vector<std::string> vectorout = { "ACK-F" };
		if (!AbstractSocket::SendMultipleStringPackage(socket, vectorout))
		{
			
			return;
		}
	}
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 21: Update Chat Room List");
	//**************************//
	User* user = portStatus->getUser();
	std::vector<std::string> vectorout = serverData_->chatControl_->getSubscribedChatRooms(user);
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//
	if (!AbstractSocket::SendMultipleStringPackage(socket, vectorout))
	{
		
		return ;
	}

}
/// Verb 22: Envoyer un nouveau message au chat
void ServerControl::executeSendNewChatMessage(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	//std::cout << "Sending new lobby message" << std::endl;

	std::vector<std::string> vectorin;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socket, vectorin))
	{
		
		return;
	}
	std::string message = vectorin[0];
	std::string roomName = vectorin[1];
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 22: Send New Chat Message");
	//**************************//
	ChatRoom* room = serverData_->chatControl_->getChatRoom(roomName);
	serverData_->chatControl_->parseNewMessage(portStatus->getUser(), message, room);
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//
}
/// Verb 23: Obtenir les nouveaux messages du chat
void ServerControl::executeRequestMessageHistoryUpdate(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	//std::cout << "Requesting Chatroom History" << std::endl;
	User* user = portStatus->getUser();
	std::vector<std::string> roomNames;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socket, roomNames))
	{
		
		return;
	}	
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 23: Request Message History");
	//**************************//
	for (std::string name : roomNames)
	{
		std::vector<std::string> messages;
		std::vector<ChatMessage*> messageList;
		if (portStatus->isFirstMessageUpdate())
		{
			messageList = serverData_->chatControl_->getChatRoom(name)->getAllMessages(user);
		}
		else
		{
			messageList = serverData_->chatControl_->getChatRoom(name)->getUnsentMessages(user);
		}
		for (ChatMessage* chatMessage : messageList)
			messages.push_back(chatMessage->getFormattedMessage());
		if (!AbstractSocket::SendMultipleStringPackage(socket, messages))
		{
			
			//**************************//
			ServerControl::getPointer()->releaseSecureLock();
			//**************************//
			return;
		}
	}
	portStatus->setFirstMessageUpdate(false);
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//
	return;
}
#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // Game Room Related
/// Verb 31: Obtenir la liste des salles de jeu
void ServerControl::executeUpdateGameRoomList(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 31: Update Game Room List");
	//**************************//
	std::vector<std::string> vectorout;
	vectorout = ServerControl::getPointer()->serverData_->gameControl_->getAllGames(portStatus->getUser());
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//

	if (!AbstractSocket::SendMultipleStringPackage(socket, vectorout))
	{
		
		return;
	}
}
/// Verb 32: Création d'une salle de jeu
void ServerControl::executeCreateGameRoom(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 32: Create Game Room");
	//**************************//
	User* host = portStatus->getUser();
	IP* hostIP = portStatus->getRemoteIP();
	bool res = ServerControl::getPointer()->serverData_->gameControl_->createNewGameRoom(host, hostIP);
	portStatus->setUserAsGameHost(true);
	ChatRoom* room = serverData_->chatControl_->getChatRoom("General");
	serverData_->chatControl_->parseNewMessage(portStatus->getUser(), "/create GameRoom:" + host->getUserName(), room);
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//

	std::string packageout = res ? "ACK-S" : "ACK-F";
	if (!AbstractSocket::SendStringPackage(socket, packageout))
	{
		return;
	}

}
/// Verb 33: Joindre une salle de jeu
void ServerControl::executeJoinGameRoom(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	std::vector<std::string> vectorin;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socket, vectorin))
	{
		return;
	}
	std::string hostname = vectorin[0];
	std::string password = vectorin[1];

	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 33: Join Game Room");
	//**************************//
	bool res = ServerControl::getPointer()->serverData_->gameControl_->joinGameRoom(portStatus->getUser(), hostname, password);
	ChatRoom* room = serverData_->chatControl_->getChatRoom("General");
	GameRoom* gameRoom = serverData_->gameControl_->getRoom(portStatus->getUser());
	serverData_->chatControl_->parseNewMessage(portStatus->getUser(), "/join GameRoom:" + gameRoom->getHostName(), room);
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//

	std::string packageout = res ? "ACK-S" : "ACK-F";
	if (!AbstractSocket::SendStringPackage(socket, packageout))
	{
		return;
	}
	if (packageout == "ACK-S")
	{
		//**************************//
		ServerControl::getPointer()->obtainSecureLock("Verb 33.2: Join Game Room");
		//**************************//
		User* user = ServerControl::getPointer()->serverData_->userControl_->getUser(hostname);
		GameRoom* room = ServerControl::getPointer()->serverData_->gameControl_->getRoom(user);
		std::string host;
		if (room != nullptr)
			host = room->getHostName();
		else
			host = "ACK-F";
		//**************************//
		ServerControl::getPointer()->releaseSecureLock();
		//**************************//
		if (!AbstractSocket::SendStringPackage(socket, host))
		{
			return;
		}
	}
}
/// Verb 34: Joindre automatiquement une salle de jeu
void ServerControl::executeMatchmaking(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 34: Matchmaking");
	//**************************//
	bool isHost = false;
	bool res = ServerControl::getPointer()->serverData_->gameControl_->matchmakingJoinRoom(portStatus->getUser(), isHost);
	if (!isHost)
	{
		ChatRoom* room = serverData_->chatControl_->getChatRoom("General");
		GameRoom* gameRoom = serverData_->gameControl_->getRoom(portStatus->getUser());
		serverData_->chatControl_->parseNewMessage(portStatus->getUser(), "/join ChatRoom:" + gameRoom->getHostName(), room);
	}
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//

	std::string packageout;
	if (isHost)
		packageout = "ACK-H";
	else
		if (res)
			packageout = "ACK-S";
		else
			packageout = "ACK-F";
	if (!AbstractSocket::SendStringPackage(socket, packageout))
	{
		
		return;
	}
	if (packageout == "ACK-S")
	{
		//**************************//
		ServerControl::getPointer()->obtainSecureLock("Verb 34.2: Matchmaking");
		//**************************//
		User* user = portStatus->getUser();
		GameRoom* room = ServerControl::getPointer()->serverData_->gameControl_->getRoom(user);
		std::string host;
		if (room != nullptr)
			host = room->getHostName();
		else
			host = "ACK-F";
		//**************************//
		ServerControl::getPointer()->releaseSecureLock();
		//**************************//
		if (!AbstractSocket::SendStringPackage(socket, host))
		{
			
			return;
		}
	}
}
/// Verb 35: Quitter une salle de jeu
void ServerControl::executeLeaveGameRoom(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 35: Leave Game Room");
	//**************************//

	// Receive final game status
	/*if (portStatus->userIsHost())
	{
		std::string packagein;
		if (!AbstractSocket::ReceiveString(socket, 5, packagein))
		{
			return;
		}
		if (packagein == "WON__")
			ServerControl::getPointer()->serverData_->gameControl_->setGameWon(portStatus->getUser());
	}*/

	bool res = ServerControl::getPointer()->serverData_->gameControl_->leaveGameRoom(portStatus->getUser());
	portStatus->setUserAsGameHost(false);
	if (res)
	{
		ChatRoom* room = serverData_->chatControl_->getChatRoom("General");
		GameRoom* gameRoom = serverData_->gameControl_->getRoom(portStatus->getUser());
		serverData_->chatControl_->parseNewMessage(portStatus->getUser(), "/leave GameRoom:" + gameRoom->getHostName(), room);
	}
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//

	std::string packageout = res ? "ACK-S" : "ACK-F";
	if (!AbstractSocket::SendStringPackage(socket, packageout))
	{
		
		return;
	}
}
/// Verb 41: Débuter une partie
void ServerControl::executeStartGame(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	bool res = false;
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 41: Start Game");
	//**************************//
	if (portStatus->userIsHost())
	{
		res = ServerControl::getPointer()->serverData_->gameControl_->startGame(portStatus->getUser());
		std::vector<User*> users = ServerControl::getPointer()->serverData_->gameControl_->getAllPlayersFromGame(portStatus->getUser());
		for (User* user : users)
			ServerControl::getPointer()->serverData_->userControl_->updateDatabase(*user);
	}
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//

	std::string packageout = res ? "ACK-S" : "ACK-F";
	if (!AbstractSocket::SendStringPackage(socket, packageout))
	{
		
		return;
	}
}
/// Verb 42: Change l'état d'un joueur
void ServerControl::executeSetReady(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	bool res = false;
	std::vector<std::string> packagein;
	if (!AbstractSocket::ReceiveMultipleStringPackage(socket, packagein))
	{
		
		return;
	}
	std::string host = packagein[0];
	bool state = packagein[1] == "1" ? true : false;
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 42: Set Ready");
	//**************************//
	res = ServerControl::getPointer()->serverData_->gameControl_->getRoom(portStatus->getUser())
			->setPlayerReady(portStatus->getUser(), state);
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//

}
/// Verb 44: Mettre à jour les informations de la salle de jeu actuelle
void ServerControl::executeUpdateGameRoomInfo(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	// If user is host, received updated informations
	if (portStatus->userIsHost())
	{
		std::vector<std::string> vectorin;
		if (!AbstractSocket::ReceiveMultipleStringPackage(socket, vectorin))
		{
			
			return;
		}
		std::string hostname = vectorin[0];
		std::string password = vectorin[1];
		std::string mapname = vectorin[2];
		std::string gametype = vectorin[3];
		std::string temps = vectorin[4];
		std::string instadeath = vectorin[5];
		// Update Game Room

		//**************************//
		ServerControl::getPointer()->obtainSecureLock("Verb 44: Update Game Room Info");
		//**************************//
		User* user = ServerControl::getPointer()->serverData_->userControl_->getUser(hostname);
		ServerControl::getPointer()->serverData_->gameControl_->updateGameInfo(user, password, mapname, 
			gametype, temps, instadeath);
		//**************************//
		ServerControl::getPointer()->releaseSecureLock();
		//**************************//
	}

	// Retrieve updated game room informations

	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 44.2: Update Game Room Info");
	//**************************//
	std::vector<std::string> vectorout = ServerControl::getPointer()->serverData_->gameControl_->getGameInfo(portStatus->getUser());
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//
	vectorout.push_back(portStatus->getRemoteIP()->getStringIP());
	if (!AbstractSocket::SendMultipleStringPackage(socket, vectorout))
	{
		
		return;
	}
}
/// Verb 45: Mettre à jour les informations des joueurs de la salle de jeu actuelle
void ServerControl::executeUpdateGameRoomPlayerInfo(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	//**************************//
	ServerControl::getPointer()->obtainSecureLock("Verb 45: Update Game Room Player Info");
	//**************************//
	std::vector<std::string> vectorout = ServerControl::getPointer()->serverData_->gameControl_->getGamePlayerInfo(portStatus->getUser());
	//**************************//
	ServerControl::getPointer()->releaseSecureLock();
	//**************************//
	if (!AbstractSocket::SendMultipleStringPackage(socket, vectorout))
	{
		
		return;
	}
}
/// Verb 50: Obtenir les informations pour se reconnecter à une partie pré-existante
void ServerControl::executeRejoinPreviousGame(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	// Unused. Unrequired.
}
#pragma endregion

////////////////////////////////////
// Client-Server Communication Actions
#pragma region // // // Game Map Related

/// Verb 61: Download toutes les cartes disponibles du serveur
void ServerControl::executeDownloadMap(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	std::cout << "Sending Local Files To Client" << std::endl;
	std::vector<std::string> names;
	std::vector<std::string> maps;
	std::vector<std::string> images;

	// Find all maps
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR szDir[MAX_PATH];
	DWORD dwError = 0;

	// Prepare string for use with FindFile functions. Copy the
	// string to a buffer.
	std::string path = "..\\..\\Database\\Map\\";
	StringCchCopy(szDir, MAX_PATH, (path + "*.xml").c_str());

	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		std::cout << "Fail: incapable de trouver le premier fichier" << std::endl;
		if (!AbstractSocket::SendInt(socket, -1))
		{
			return;
		}
		return;
	}

	// Load maps
	do
	{
		std::string tempshit = std::string(ffd.cFileName);
		names.push_back(std::string(tempshit, 0, tempshit.length() - 4));
		std::ifstream finxml(path + names.back() + ".xml", std::ios::binary);
		std::ostringstream ostrmxml;
		ostrmxml << finxml.rdbuf();
		maps.push_back(ostrmxml.str());
		std::ifstream finjpg(path + names.back() + ".jpg", std::ios::binary);
		std::ostringstream ostrmjpg;
		ostrmjpg << finjpg.rdbuf();
		images.push_back(ostrmjpg.str());

	} while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{
		std::cout << "Fail: incapable de trouver le premier fichier" << std::endl;
		return;
	}
	FindClose(hFind);

	// Send Number of Maps
	int numberOfFiles = (int)names.size();
	if (!AbstractSocket::SendInt(socket, numberOfFiles))
	{
		return;
	}

	// Send Map Names
	for (unsigned int i = 0; i < names.size(); i++)
		if (!AbstractSocket::SendStringPackage(socket, names[i]))
		{
			std::cout << "Failed When Sending Names" << std::endl;
			return;
		}
	std::cout << "    All Names Sent" << std::endl;

	// Send Map Data
	for (unsigned int i = 0; i < names.size(); i++)
		if (!AbstractSocket::SendStringPackage(socket, maps[i]))
		{
			std::cout << "Failed When Sending Map Data" << std::endl;
			return;
		}
	std::cout << "    All Map Data Sent" << std::endl;

	// Send Map Images
	AbstractSocket::UDPSocket* udpSocket = new AbstractSocket::UDPSocket(portStatus->getPortNumber());
	for (unsigned int i = 0; i < names.size(); i++)
		if (!AbstractSocket::SendStringPackage(socket, images[i]))
		//if (!AbstractSocket::SendStringPackage(socket, udpSocket, images[i], portStatus->getRemoteIP()))
		{
			std::cout << "Failed When Sending Images" << std::endl;
			return;
		}
	std::cout << "    All Map Images Sent" << std::endl;
	
	delete udpSocket;
	std::cout << "Successfully Sent " << numberOfFiles << " Files To Client" << std::endl;
}
/// Verb 62: Upload toutes les cartes modifiées au serveur
void ServerControl::executeUploadMap(AbstractSocket::TCPSocket* socket, PortStatus* portStatus)
{
	std::cout << "Receiving New Files From Client" << std::endl;
	std::vector<std::string> names;
	std::vector<std::string> maps;
	std::vector<std::string> images;

	// Receive Number of Maps
	int numberOfMaps = -1;
	if (!AbstractSocket::ReceiveInt(socket, numberOfMaps))
	{
		return;
	}
	if (numberOfMaps < 1)
		return;

	// Receive Map Names
	for (int i = 0; i < numberOfMaps; i++)
	{
		std::string thisName;
		if (!AbstractSocket::ReceiveStringPackage(socket, thisName))
		{
			std::cout << "Failed When Receiving Names" << std::endl;
			return;
		}
		names.push_back(thisName);
	}
	std::cout << "    All Names Received" << std::endl;

	// Receive Map Data
	for (int i = 0; i < numberOfMaps; i++)
	{
		std::string thisMap;
		if (!AbstractSocket::ReceiveStringPackage(socket, thisMap))
		{
			std::cout << "Failed When Receiving Map Data" << std::endl;
			return;
		}
		maps.push_back(thisMap);
	}
	std::cout << "    All Map Data Received" << std::endl;

	// Receive Map Images
	AbstractSocket::UDPSocket* udpSocket = new AbstractSocket::UDPSocket(portStatus->getPortNumber());
	for (int i = 0; i < numberOfMaps; i++)
	{
		std::string thisImage;
		IP* sender = new IP();
		if (!AbstractSocket::ReceiveStringPackage(socket, thisImage))
		//if (!AbstractSocket::ReceiveStringPackage(socket, udpSocket, thisImage, sender))
		{
			std::cout << "Failed When Receiving Images" << std::endl;
			return;
		}
		images.push_back(thisImage);
		delete sender;
	}
	std::cout << "    All Map Image Received" << std::endl;

	// Recreate Files
	while (!maps.empty())
	{
		std::string mapName = names.back();
		names.pop_back();
		std::string fileNameMap = "..\\..\\Database\\Map\\" + mapName + ".xml";
		std::string fileNameImage = "..\\..\\Database\\Map\\" + mapName + ".jpg";
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

	std::cout << "Successfully Received " << numberOfMaps << " New Files From Client" << std::endl;
	delete udpSocket;
}

#pragma endregion