//////////////////////////////////////////////////////////////////////////////
/// @file AbstractSocketV2.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Client
//////////////////////////////////////////////////////////////////////////////
#define _SCL_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "AbstractSocketV2.h"
#include "Utilitaire.h"

#include <algorithm>
#include <sstream>
#include <iostream>
#include <stdint.h>
#include <map>
#include <vector>
#include <memory>
#include "IP.h"

////////////////////////////////////////////////////////////////////////////////
///
/// @namespace AbstractSocket
/// @brief Namespace contrôllant des fonctions pour simplifier la communication par Winsock
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
namespace AbstractSocket {

	/// Packet Size Limit
	const int MAX_BUFFER_SIZE_TCP = 450;
	const int MAX_BUFFER_SIZE_UDP = 1400;
	/// Timeout Limit
	const DWORD TIMEOUT_VALUE_TCP = 3000;
	/// Timeout Limit
	const DWORD TIMEOUT_VALUE_UDP = 100;	// Haha - 100 ms pour UDP pour pouvoir detecter qu'on a perdu des trucs
	/// Timeout Counter Limit
	const int MAX_TIMEOUT_TO_37 = 15;
	/// Buffer size
	const int BUFFER_SIZE = 50 * 1024 * 1024;	// 50 MB, git gud
	/// Message Delimiter
	const std::string MESSAGE_DELIMITER = "<rs>";

	/// Retourne l'addresse IP Locale
	IP* getLocalIP()
	{
		char ac[80];
		if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
			std::cout << "Error " << WSAGetLastError() <<
				" when getting local host name." << std::endl;
			return new IP();
		}
		std::cout << "Host name is " << ac << "." << std::endl;

		struct hostent *phe = gethostbyname(ac);
		if (phe == 0) {
			std::cerr << "Yow! Bad host lookup." << std::endl;
			return new IP();
		}
		IP* ip = new IP();
		for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
			struct in_addr addr;
			memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
			std::cout << "Local Address " << i << ": " << inet_ntoa(addr) << std::endl;
			ip->changeTo(addr.S_un.S_un_b.s_b1, addr.S_un.S_un_b.s_b2, addr.S_un.S_un_b.s_b3, addr.S_un.S_un_b.s_b4);
		}
		return ip;
	}

	////////////////////////////////////
	/// Fonctions TCP

	/// Initialise un socket fourni en paramètre à une connection à l'adresse:port
	bool CreateSocket(TCPSocket* socketConnection, std::string addresse, std::string port)
	{
		socketConnection->socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		socketConnection->port_ = (unsigned short)std::stoi(port);
		if (socketConnection->socket_ == INVALID_SOCKET)
		{
			std::cout << "Erreur de creation de socket: " << WSAGetLastError() << std::endl;
			return false;
		}

		addrinfo* result = nullptr;
		addrinfo hints;
		memset(&hints, 0, sizeof(hints));

		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		int addrInfoResult = getaddrinfo(addresse.c_str(), port.c_str(), &hints, &result);
		if (addrInfoResult != 0)
			return false;

		while ((result != nullptr) && (result->ai_family != AF_INET))
			result = result->ai_next;

		if ((result == nullptr) || (result->ai_family != AF_INET))
		{
			freeaddrinfo(result);
			result = nullptr;
			return false;
		}

		char* option = "1";
		setsockopt(socketConnection->socket_, SOL_SOCKET, SO_REUSEADDR, option, sizeof(option));
		setsockopt(socketConnection->socket_, SOL_SOCKET, SO_RCVBUF, (char*)&BUFFER_SIZE, sizeof(BUFFER_SIZE));
		setsockopt(socketConnection->socket_, SOL_SOCKET, SO_SNDBUF, (char*)&BUFFER_SIZE, sizeof(BUFFER_SIZE));
		setsockopt(socketConnection->socket_, SOL_SOCKET, SO_RCVTIMEO, (const char *)&TIMEOUT_VALUE_TCP, sizeof(TIMEOUT_VALUE_TCP));
		setsockopt(socketConnection->socket_, SOL_SOCKET, SO_SNDTIMEO, (const char *)&TIMEOUT_VALUE_TCP, sizeof(TIMEOUT_VALUE_TCP));

		int connectionResult = connect(socketConnection->socket_, result->ai_addr, static_cast<int>(result->ai_addrlen));
		if (connectionResult == SOCKET_ERROR)
		{
			freeaddrinfo(result);
			int err = WSAGetLastError();
			std::cout << "Erreur dans la connexion initiale! Connect err no: " << err << std::endl;
			return false;
		}



		freeaddrinfo(result);
		return true;
	}
	/// Initialise le socket de communication et envoie le Verbe au serveur
	bool SendVerb(TCPSocket* socketConnection, std::string addresse, std::string port, int verb)
	{
		// Étape 1: Se connecter au serveur sur le port fourni
		if (!AbstractSocket::CreateSocket(socketConnection, addresse, port))
		{
			return false;
		}
		//std::cout << "Connection etablie!" << std::endl;

		// Étape 2: Envoyer le Verbe
		if (!AbstractSocket::SendInt(socketConnection, verb))
		{
			return false;
		}

		// Étape 3: Réponse au Verbe du serveur
		std::string packagein;
		if (!AbstractSocket::ReceiveStringPackage(socketConnection, packagein))
		{
			return false;
		}
		if (packagein == "ACK-VERB-C")
		{
			std::cout << "Verbe Refused: Port not assigned as used" << std::endl;
			return false;
		}
		if (packagein == "ACK-VERB-I")
		{
			std::cout << "Verbe Refused: Port not assigned to this IP" << std::endl;
			return false;
		}
		if (packagein == "ACK-VERB-F")
		{
			std::cout << "Verbe refused: User not logged in" << std::endl;
			return false;
		}
		if (packagein == "ACK-VERB-S")
		{
			//std::cout << "Verbe accepte" << std::endl;
			return true;
		}
		return false;
	}

	/// Fonction primitive: envoie un string. Le destinataire doit connaître la taille du string
	bool SendString(TCPSocket* socket, std::string message)
	{
		if (message.length() > MAX_BUFFER_SIZE_TCP)
		{
			socket->lastError_ = 69;
			std::cout << "Erreur dans l'envoi TCP d'un string! Err no: " << socket->lastError_ << std::endl;
			std::cout << "Fermeture de la connection..." << std::endl;
			closesocket(socket->socket_);
			return false;
		}
		// Allocated char* buffer for message
		char * data = new char[message.size()];
		std::copy(message.begin(), message.end(), data);
		char * dataPointer = data;

		// Number of bytes to send
		int length = (int)message.size();
		int sentTotal = 0;

		while (length > sentTotal)
		{
			int sizeToSend = (length - sentTotal < MAX_BUFFER_SIZE_TCP ? length - sentTotal : MAX_BUFFER_SIZE_TCP);
			int sendResult = send(
				socket->socket_,		// SOCKET
				dataPointer,			// DATA
				sizeToSend,				// LENGTH
				0						// FLAGS
				);
			if (sendResult == SOCKET_ERROR)
			{
				socket->lastError_ = WSAGetLastError();
				std::cout << "Erreur dans l'envoi TCP d'un string! Err no: " << socket->lastError_ << std::endl;
				std::cout << "Fermeture de la connection..." << std::endl;
				closesocket(socket->socket_);
				delete data;
				return false;
			}
			sentTotal += sendResult;
			dataPointer += sendResult;
		}

		delete data;
		return true;
	}
	/// Fonction primitive: recoit un string de taille connue
	bool ReceiveString(TCPSocket* socket, int length, std::string &incoming)
	{
		if (length > MAX_BUFFER_SIZE_TCP)
		{
			socket->lastError_ = 69;
			std::cout << "Erreur dans la reception TCP d'un string! Err no: " << socket->lastError_ << std::endl;
			std::cout << "Fermeture de la connection..." << std::endl;
			closesocket(socket->socket_);
			return false;
		}
		// New Message
		char* buff = new char[length+1];
		// Received bytes so far
		int receivedLength = 0;
		// Until everything is received
		int timeoutCounter = 0;
		while (receivedLength < length)
		{
			// Ask for limited info
			int sizeToAskFor = (length - receivedLength <= MAX_BUFFER_SIZE_TCP ? length - receivedLength : MAX_BUFFER_SIZE_TCP);
			// Receive things
			int receivedSize = recv(	
				socket->socket_,			// SOCKET
				buff,						// DATA
				sizeToAskFor,				// LENGTH
				0							// FLAGS
				);
			if (receivedSize == SOCKET_ERROR)
			{
				socket->lastError_ = WSAGetLastError();
				if (socket->lastError_ == 10060 && timeoutCounter < MAX_TIMEOUT_TO_37)
					timeoutCounter++;
				else
				{
					buff -= receivedLength;
					delete buff;
					std::cout << "Erreur dans la reception TCP d'un string! Err no: " << socket->lastError_ << std::endl;
					std::cout << "Fermeture de la connection..." << std::endl;
					closesocket(socket->socket_);
					return false;
				}
			}
			else
			{
				receivedLength += receivedSize;
				buff += receivedSize;
			}
		}
		buff -= receivedLength;
		buff[receivedLength] = '\0';
		incoming = std::string(buff, length);
		return true;
	}

	/// Envoie un entier signé sur 32 bit
	bool SendInt(TCPSocket* socket, int32_t value)
	{
		int32_t networkValue = htonl(value);
		char* networkArray = new char[4];
		networkArray = (char*)(&networkValue);
		std::string message(networkArray, 4);
		if (!SendString(socket, message))
		{
			std::cout << "Erreur dans l'envoi TCP d'un int!" << std::endl;
			return false;
		}
		return true;
	}
	/// Recoie un entier signé sur 32 bit
	bool ReceiveInt(TCPSocket* socket, int32_t &incoming)
	{
		std::string networkMessage;
		if (!AbstractSocket::ReceiveString(socket, 4, networkMessage))
		{
			std::cout << "Erreur dans la reception TCP d'un int!" << std::endl;
			return false;
		}

		unsigned char* buff = new unsigned char[4];
		std::copy(networkMessage.begin(), networkMessage.end(), buff);
		int32_t networkInt = (buff[3] << 24) | (buff[2] << 16) | (buff[1] << 8) | (buff[0]);
		delete buff;
		//int32_t networkInt = *(int32_t*)(&buff);
		incoming = (int32_t)ntohl(u_long(networkInt));
		return true;
	}

	/// Envoie un tableau d'entiers signés sur 32 bit
	bool SendMultipleIntPackage(TCPSocket* socket, std::vector<int32_t> messagePackage)
	{
		// Step 1: Prepare Message as String
		std::string message = "";
		for (int32_t m : messagePackage)
			message += std::to_string(m) + ";";

		// Step 2: Send Message using Package Method
		SendStringPackage(socket, message);
		
		return true; // All messages sent, function done
	}
	/// Recoie un tableau d'entiers signés sur 32 bit
	bool ReceiveMultipleIntPackage(TCPSocket* socket, std::vector<int32_t> &incomingPackage)
	{
		// Step 1: Receive Message using Package Method
		std::string message = "";
		if (!ReceiveStringPackage(socket, message))
			return false; // Failed
			
		// Step 2: Separate string into int32_t vector
		std::vector<std::string> split = Utilitaire::stringSplit(message, ";");
		for (std::string subMess : split)
			incomingPackage.push_back((int32_t)std::stoi(subMess));

		return true;
	}

	/// Envoie un string. S'occupe du handling de la taille
	bool SendStringPackage(TCPSocket* socket, std::string message)
	{
		// Step 1: Send length
		int length = (int)message.length();
		if (!SendInt(socket, length))
			return false; // Failed

		// Step 2: Split into packets, if needed
		std::vector<std::string> packets;
		for (unsigned int i = 0; i < message.length(); i += MAX_BUFFER_SIZE_TCP)
		{
			if (i + MAX_BUFFER_SIZE_TCP > message.length())
				packets.push_back(std::string(message, i, message.length() - i));
			else
				packets.push_back(std::string(message, i, MAX_BUFFER_SIZE_TCP));
		}

		// Step 3: Send packets using SendString method
		for (std::string pack : packets)
		{
			if (!SendString(socket, pack))
				return false; // Failed
		}

		return true; // All messages sent, function done
	}
	/// Recoit un string. S'occupe du handling de la taille
	bool ReceiveStringPackage(TCPSocket* socket, std::string &incoming)
	{
		// Step 1: Receive length
		int packageLength = -1;
		if (!ReceiveInt(socket, packageLength))
			return false; // Failed
		if (packageLength == -1)
			return false; // Failed

		// Step 2: Receive packets using ReceiveString method
		std::string completeMessage = "";
		for (int i = 0; i < packageLength; i += MAX_BUFFER_SIZE_TCP)
		{
			std::string message;
			if (i + MAX_BUFFER_SIZE_TCP > packageLength)
			{
				if (!ReceiveString(socket, packageLength - i, message))
					return false; // Failed
			}
			else
			{
				if (!ReceiveString(socket, MAX_BUFFER_SIZE_TCP, message))
					return false; // Failed
			}
			completeMessage += message;
		}
		incoming = completeMessage;
		// Done
		return true;
	}

	/// Envoie un vecteur de string. S'occupe du handling individuel. Guarantit l'envoie de tout les strings
	bool SendMultipleStringPackage(TCPSocket* socket, std::vector<std::string> messagePackage)
	{
		// Step 1: Send Package Length
		int length = 0;
		for (std::string message : messagePackage)
			length += (int)message.length() + (int)MESSAGE_DELIMITER.length();
		if (!SendInt(socket, length))
			return false; // Failed
		
		// Step 2: Create message to send
		std::string longMessage = "";
		for (std::string message : messagePackage)
		{
			longMessage += message + MESSAGE_DELIMITER;
		}
		
		// Step 3: Split into packets, if needed
		std::vector<std::string> packets;
		for (unsigned int i = 0; i < longMessage.length(); i += MAX_BUFFER_SIZE_TCP)
		{
			if (i + MAX_BUFFER_SIZE_TCP > longMessage.length())
				packets.push_back(std::string(longMessage, i, longMessage.length() - i));
			else
				packets.push_back(std::string(longMessage, i, MAX_BUFFER_SIZE_TCP));
		}
		
		// Step 4: Send packets using SendString method
		for (std::string message : packets)
		{
			if (!SendString(socket, message))
				return false; // Failed
		}
		
		return true; // All messages sent, function done
	}
	/// Recoit un vecteur de string. S'occupe du handling individuel. Guarantit la reception de tout les strings
	bool ReceiveMultipleStringPackage(TCPSocket* socket, std::vector<std::string> &incomingPackage)
	{
		// Step 1: Receive Package Length
		int packageLength = -1;
		if (!ReceiveInt(socket, packageLength))
			return false; // Failed
		if (packageLength == -1)
			return false; // Failed

		// Step 2: Receive packets using ReceiveString method
		std::string completeMessage = "";
		for (int i = 0; i < packageLength; i += MAX_BUFFER_SIZE_TCP)
		{
			std::string message;
			if (i + MAX_BUFFER_SIZE_TCP > packageLength)
			{
				if (!ReceiveString(socket, packageLength - i, message))
					return false; // Failed
			}
			else
			{
				if (!ReceiveString(socket, MAX_BUFFER_SIZE_TCP, message))
					return false; // Failed
			}
			completeMessage += message;
		}
		
		// Step 3: Split packets into vector
		std::vector<std::string> vec;
		size_t pos = 0;
		std::string token;
		while ((pos = completeMessage.find(MESSAGE_DELIMITER)) != std::string::npos) 
		{
			token = completeMessage.substr(0, pos);
			vec.push_back(token);
			completeMessage.erase(0, pos + MESSAGE_DELIMITER.length());
		}
		for (std::string mess : vec)
			incomingPackage.push_back(mess);
		
		return true;
	}



	////////////////////////////////////
	/// Fonctions UDP

	/// Fonction primitive: envoie un string. Le destinataire doit connaître la taille du string
	bool SendString(UDPSocket* socket, std::string message, IP* address)
	{
		if (message.length() > MAX_BUFFER_SIZE_UDP)
		{
			socket->lastError_ = 69;
			std::cout << "Erreur dans l'envoi UDP d'un string! Err no: " << socket->lastError_ << std::endl;
			closesocket(socket->socket_);
			return false;
		}
		// Allocated char* buffer for message
		char * data = new char[message.size()];
		std::copy(message.begin(), message.end(), data);
		char *dataPointer = data;

		// Recipient's Address
		sockaddr_in add;
		add.sin_family = AF_INET;
		add.sin_addr.s_addr = inet_addr(address->getStringIP().c_str());
		add.sin_port = htons(socket->port_);
		memset(&add.sin_zero, 0, sizeof(add.sin_zero));

		// Number of bytes to send
		int length = (int)message.size();
		int sentTotal = 0;
		
		while (length > sentTotal)
		{
			int sizeToSend = (length - sentTotal < MAX_BUFFER_SIZE_UDP ? length - sentTotal : MAX_BUFFER_SIZE_UDP);
			int sendResult = sendto(
				socket->socket_,							// SOCKET
				dataPointer,								// DATA
				sizeToSend,									// LENGTH
				0,											// FLAGS
				reinterpret_cast<SOCKADDR *>(&add),			// DEST ADDRESS
				sizeof(add)									// ADDRESS LENGTH
				);
			if (sendResult == SOCKET_ERROR)
			{
				socket->lastError_ = WSAGetLastError();
				std::cout << "Erreur dans l'envoi UDP d'un string! Err no: " << socket->lastError_ << std::endl;
				std::cout << "Fermeture de la connection..." << std::endl;
				delete data;
				closesocket(socket->socket_);
				return false;
			}
			sentTotal += sendResult;
			dataPointer += sendResult;
		}

		delete data;
		return true;
	}
	/// Fonction primitive: recoit un string de taille connue
	bool ReceiveString(UDPSocket* socket, int length, std::string &incoming, IP* sender)
	{
		if (length > MAX_BUFFER_SIZE_UDP)
		{
			socket->lastError_ = 69;
			std::cout << "Erreur dans la reception UDP d'un string! Err no: " << socket->lastError_ << std::endl;
			closesocket(socket->socket_);
			return false;
		}
		int timeOutCounter = 0;
		// New Message
		char* buff = new char[length + 1];
		char *buffPointer = buff;
		// Received bytes so far
		int receivedLength = 0;
		// Until everything is received
		while (receivedLength < length)
		{
			sockaddr_in from;
			int size = sizeof(from);
			// Ask for limited info
			int sizeToAskFor = (length - receivedLength <= MAX_BUFFER_SIZE_UDP ? length - receivedLength : MAX_BUFFER_SIZE_UDP);

			int receivedSize = recvfrom(
				socket->socket_,							// SOCKET
				buffPointer,								// DATA
				sizeToAskFor,								// LENGTH
				0,											// FLAGS
				reinterpret_cast<SOCKADDR *>(&from),		// SENDER ADDRESS
				&size										// ADDRESS LENGTH
				);
			if (receivedSize == SOCKET_ERROR)
			{
				socket->lastError_ = WSAGetLastError();
				if (socket->lastError_ == 10060 && timeOutCounter < MAX_TIMEOUT_TO_37)
					timeOutCounter++;
				else
				{
					delete buff;
					std::cout << "Erreur dans la reception UDP d'un string! Err no: " << socket->lastError_ << std::endl;
					if (socket->lastError_ != 10060)
					{
						std::cout << "Fermeture de la connection..." << std::endl;
						closesocket(socket->socket_);
					}
					return false;
				}
			}
			else
			{
				receivedLength += receivedSize;
				buffPointer += receivedSize;
			}

			// Acquire information on sender
			std::string IPstr = inet_ntoa(from.sin_addr);
			int a = from.sin_addr.S_un.S_un_b.s_b1;
			int b = from.sin_addr.S_un.S_un_b.s_b2;
			int c = from.sin_addr.S_un.S_un_b.s_b3;
			int d = from.sin_addr.S_un.S_un_b.s_b4;
			sender->changeTo(a, b, c, d);
		}

		buff[length] = '\0';
		incoming = std::string(buff, length);
		return true;
	}

	/// Envoie un entier signé sur 32 bit
	bool SendInt(UDPSocket* socket, int32_t value, IP* address)
	{
		int32_t networkValue = htonl(value);
		char* networkArray = new char[4];
		networkArray = (char*)(&networkValue);
		std::string message(networkArray, 4);
		if (!SendString(socket, message, address))
		{
			std::cout << "Erreur dans l'envoi UDP d'un int!" << std::endl;
			return false;
		}
		return true;
	}
	/// Recoie un entier signé sur 32 bit
	bool ReceiveInt(UDPSocket* socket, int32_t &incoming, IP* sender)
	{
		//int32_t receivedInt;

		std::string networkMessage;
		if (!ReceiveString(socket, 4, networkMessage, sender))
		{
			std::cout << "Erreur dans la reception UDP d'un int!" << std::endl;
			return false;
		}

		char* buff = new char[4];
		std::copy(networkMessage.begin(), networkMessage.end(), buff);
		int32_t networkInt = (buff[3] << 24) | (buff[2] << 16) | (buff[1] << 8) | (buff[0]);
		incoming = (int32_t)ntohl(u_long(networkInt));
		
		return true;
	}
	
	/// Envoie un string. S'occupe du handling de la taille. Arrivée non guarantie
	bool SendStringPackage(UDPSocket* socket, std::string message, IP* address)
	{
		// Step 1: Send length
		int length = (int)message.length();
		if (!SendInt(socket, length, address))
			return false; // Failed

		// Step 2: Split into packets, if needed
		std::vector<std::string> packets;
		for (unsigned int i = 0; i < message.length(); i += MAX_BUFFER_SIZE_UDP)
		{
			if (i + MAX_BUFFER_SIZE_UDP > message.length())
				packets.push_back(std::string(message, i, message.length() - i));
			else
				packets.push_back(std::string(message, i, MAX_BUFFER_SIZE_UDP));
		}

		// Step 3: Send packets using SendString method
		for (std::string pack : packets)
		{
			if (!SendString(socket, pack, address))
				return false; // Failed
		}

		return true; // All messages sent, function done
	}
	/// Recoit un string. S'occupe du handling de la taille. Arrivée non guarantie
	bool ReceiveStringPackage(UDPSocket* socket, std::string &incoming, IP* sender)
	{
		// Step 1: Receive length
		int packageLength = -1;
		if (!ReceiveInt(socket, packageLength, sender))
			return false; // Failed
		if (packageLength == -1)
			return false; // Failed

		// Step 2: Receive packets using ReceiveString method
		std::string completeMessage = "";
		for (int i = 0; i < packageLength; i += MAX_BUFFER_SIZE_UDP)
		{
			std::string message;
			if (i + MAX_BUFFER_SIZE_UDP > packageLength)
			{
				if (!ReceiveString(socket, packageLength - i, message, sender))
					return false; // Failed
			}
			else
			{
				if (!ReceiveString(socket, MAX_BUFFER_SIZE_UDP, message, sender))
					return false; // Failed
			}
			completeMessage += message;
		}
		incoming = completeMessage;
		// Done
		return true;
	}

	/// Envoie un TRÈS GROS string. S'occupe du handling de la taille. Arrivée guarantie en 30min ou c'est gratuit
	bool SendStringPackage(TCPSocket* tcp, UDPSocket* udp, std::string message, IP* address)
	{
		// Step 1: Split into packets, with 10 byte of numbering
		std::vector<std::string> packets;
		int32_t totalLength = 0;
		int32_t paddingLength = 0;
		int SUBMESSAGELENGTH = MAX_BUFFER_SIZE_UDP - 10;
		int packetIndex = 0;
		for (unsigned int i = 0; i < message.length(); i += SUBMESSAGELENGTH)
		{
			// Extract submessage
			std::string submessage;
			int sizeToSend;
			if (i + SUBMESSAGELENGTH > message.length())
				sizeToSend = (int)message.length() - i;
			else
				sizeToSend = SUBMESSAGELENGTH;

			submessage = std::string(message, i, sizeToSend);
			// Prepare index
			std::string index = std::to_string(packetIndex++);
			// Pad index
			for (int j = (int)index.length(); j < 10; j++)
				index += " ";
			// Pad to MAX_BUFFER_SIZE
			std::string padding(SUBMESSAGELENGTH - sizeToSend, '_');
			paddingLength = (int32_t)padding.length();
			// Create and push packet
			packets.push_back(index + submessage + padding);
		}
		// Step 2: Send length (TCP)
		for (auto packet : packets)
			totalLength += (int32_t)packet.length();
		if (!SendInt(tcp, totalLength))
			return false; // Failed

		// Step 3: Send padding length (TCP)
		if (!SendInt(tcp, paddingLength))
			return false; // Failed

		// Step 4: Iterate: Send packets (UDP)
		for (auto packet : packets)
		{
			if (!SendString(udp, packet, address))
				return false; // Failed
		}

		// Step 5: Iterate for lost packets:
		int maximumTimeoutCounter = 0;
		for (;;)
		{
			std::vector<int32_t> packagesToSend;
			// 5.1: Receive packet number (TCP) (-1 confirms all done)
			if (!ReceiveMultipleIntPackage(tcp, packagesToSend))
			{
				/*if (tcp->lastError_ == 37 || tcp->lastError_ == 10060)
				{
					if (++maximumTimeoutCounter > 10)
						return false;
					else
						continue;
				}
				else*/
					return false; // Failed
			}
			if (packagesToSend[0] == -1)
				break;
			// 5.2: Send Packet (UDP)
			for (auto i : packagesToSend)
				if (!SendString(udp, packets[i], address))
					return false; // Failed

			maximumTimeoutCounter = 0;
		}

		// Done
		return true;
	}
	/// Recoit un TRÈS GROS string. S'occupe du handling de la taille. Arrivée guarantie en 30min ou c'est gratuit
	bool ReceiveStringPackage(TCPSocket* tcp, UDPSocket* udp, std::string &incoming, IP* sender)
	{
		// Step 1: Receive Length (TCP)
		int totalLength = -1;
		if (!ReceiveInt(tcp, totalLength))
			return false; // Failed
		if (totalLength == -1)
			return false;

		// Step 2: Receive Padding Length (TCP)
		int paddingLength = -1;
		if (!ReceiveInt(tcp, paddingLength))
			return false; // Failed
		if (totalLength == -1)
			return false;

		// Step 3: Iterate: Receive packets
		std::map<int32_t, std::string> packets;
		int expectedPackets = totalLength / MAX_BUFFER_SIZE_UDP;
		for (int i = 0; i < expectedPackets; i++)
		{
			std::string packet;
			// Receive packet
			if (!ReceiveString(udp, MAX_BUFFER_SIZE_UDP, packet, sender))
			{
				if (udp->lastError_ == 37 || udp->lastError_ == 10060)
					break;	// On a un packet perdu - on ira le chercher et tous les prochains plus tard
				else
					return false; // Failed
			}
			
			// Unpack
			std::string subIndex = packet.substr(0, 10);
			std::string subMessage = packet.substr(10);
			packets[std::stoi(subIndex)] = subMessage;
		}

		// Step 4: Iterate for lost packets until everything received
		int maximumTimeoutCounter = 0;
		for (;;)
		{
			std::vector<int32_t> unreceivedPackets;
			// 4.1: Send all unreceived packets indexes
			for (int32_t i = 0; i < expectedPackets; i++)
			{
				if (packets.find(i) == packets.end())
					unreceivedPackets.push_back(i);
			}

			// Check to break out
			if (unreceivedPackets.empty())
				break;

			// Send requested indexes
			if (!SendMultipleIntPackage(tcp, unreceivedPackets))
				return false; // Failed

			// 4.2: Receive lost packets
			for (unsigned int i = 0; i < unreceivedPackets.size(); i++)
			{
				std::string packet;
				// Receive packet
				if (!ReceiveString(udp, MAX_BUFFER_SIZE_UDP, packet, sender))
				{
					if (udp->lastError_ == 37 || udp->lastError_ == 10060)
					{
						if (++maximumTimeoutCounter > 10)
							return false;
						else
							break;	// See above
					}
					else
						return false; // Failed
				}

				// Unpack
				std::string subIndex = packet.substr(0, 10);
				std::string subMessage = packet.substr(10);
				packets[std::stoi(subIndex)] = subMessage;

			}
		}

		// Step 5: Send -1 to confirm receipt
		std::vector<int32_t> finalMess = { -1 };
		if (!SendMultipleIntPackage(tcp, finalMess))
			return false; // Failed

		// Step 6: Rebuild
		std::string finalMessage = "";
		for (unsigned int i = 0; i < packets.size(); i++)
			finalMessage += packets[i];

		if (finalMessage.length() + expectedPackets * 10 != totalLength)
			return false; // Something failed

		incoming = finalMessage.substr(0, totalLength - paddingLength);

		// Done
		return true;
	}

	TCPSocket::TCPSocket(SOCKET socket, int intport)
	{
		socket_ = socket;
		port_ = (unsigned short)intport;
	}

	TCPSocket::TCPSocket(int intport)
	{
		unsigned short port = (unsigned short)intport;
		// Préparation du SOCKET
		socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (socket_ == INVALID_SOCKET)
		{
			printf("Server: socket() failed! Error: %ld.\n", WSAGetLastError());
			//WSACleanup();
			throw std::exception("Socket Error");
		}
		char* option = "1";
		setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, option, sizeof(option));
		setsockopt(socket_, SOL_SOCKET, SO_RCVBUF, (char*)&BUFFER_SIZE, sizeof(BUFFER_SIZE));
		setsockopt(socket_, SOL_SOCKET, SO_SNDBUF, (char*)&BUFFER_SIZE, sizeof(BUFFER_SIZE));
		setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO, (const char *)&TIMEOUT_VALUE_TCP, sizeof(TIMEOUT_VALUE_TCP));
		setsockopt(socket_, SOL_SOCKET, SO_SNDTIMEO, (const char *)&TIMEOUT_VALUE_TCP, sizeof(TIMEOUT_VALUE_TCP));

		// Préparations de l'adresse d'écoute
		port_ = port;
		sockaddr_in service;
		service.sin_family = AF_INET;
		service.sin_addr.s_addr = INADDR_ANY;
		service.sin_port = htons(port_);
		memset(&service.sin_zero, 0, sizeof(service.sin_zero));

		// Assignation de l'adresse IP et du port au socket
		int iRes = bind(socket_, (SOCKADDR*)&service, sizeof(service));
		if (iRes == SOCKET_ERROR)
		{
			printf("Server: bind() failed! Error: %ld.\n", WSAGetLastError());
			closesocket(socket_);
			//WSACleanup();
			throw std::exception("Socket Error");
		}

		// Établissement de l'écoute sur le SOCKET
		if (listen(socket_, SOMAXCONN) == SOCKET_ERROR)
		{
			printf("Server: listen() failed! Error: %ld.\n", WSAGetLastError());
			closesocket(socket_);
			//WSACleanup();
			throw std::exception("Socket Error");
		}
	}

	TCPSocket::~TCPSocket()
	{
		closesocket(socket_);
	}

	UDPSocket::UDPSocket(int intport)
	{
		unsigned short port = (unsigned short)intport;
		port_ = port;
		socket_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (socket_ == INVALID_SOCKET)
		{
			printf("Server: socket() failed! Error: %ld.\n", WSAGetLastError());
			//WSACleanup();
			throw std::exception("Socket Error");
		}
		char* option = "1";
		setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, option, sizeof(option));
		setsockopt(socket_, SOL_SOCKET, SO_RCVBUF, (char*)&BUFFER_SIZE, sizeof(BUFFER_SIZE));
		setsockopt(socket_, SOL_SOCKET, SO_SNDBUF, (char*)&BUFFER_SIZE, sizeof(BUFFER_SIZE));
		setsockopt(socket_, SOL_SOCKET, SO_RCVTIMEO, (const char *)&TIMEOUT_VALUE_UDP, sizeof(TIMEOUT_VALUE_UDP));
		setsockopt(socket_, SOL_SOCKET, SO_SNDTIMEO, (const char *)&TIMEOUT_VALUE_UDP, sizeof(TIMEOUT_VALUE_UDP));

		sockaddr_in add;
		add.sin_family = AF_INET;
		add.sin_addr.s_addr = htonl(INADDR_ANY);
		add.sin_port = htons(port_);
		memset(&add.sin_zero, 0, sizeof(add.sin_zero));

		int iRes = bind(socket_, reinterpret_cast<SOCKADDR *>(&add), sizeof(add));
		if (iRes == SOCKET_ERROR)
		{
			printf("Server: bind() failed! Error: %ld.\n", WSAGetLastError());
			closesocket(socket_);
			//WSACleanup();
			throw std::exception("Socket Error");
		}
	}

	UDPSocket::~UDPSocket()
	{
		closesocket(socket_);
	}

}