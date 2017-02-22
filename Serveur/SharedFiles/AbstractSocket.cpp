//////////////////////////////////////////////////////////////////////////////
/// @file AbstractSocket.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Client
//////////////////////////////////////////////////////////////////////////////
#define _SCL_SECURE_NO_WARNINGS
#include "AbstractSocket.h"

#include <algorithm>
#include <iostream>
#include <stdint.h>
#include <map>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
///
/// @namespace Utilitaire
/// @brief Namespace contrôllant des fonctions pour simplifier la communication par Winsock
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
namespace AbstractSocket {

	/// Buffer size limit
	const int MAX_BUFFER_SIZE = 256;
	/// Time value limit
	const int TIMEOUT_VALUE = 8000; // todo temp change this back2000;

	/// Initialise un socket fourni en paramètre à une connection à l'adresse:port
	bool CreateSocket(SOCKET& socketConnection, std::string addresse, std::string port)
	{
		socketConnection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (socketConnection == INVALID_SOCKET)
		{
			auto error = WSAGetLastError();
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

		int connectionResult = connect(socketConnection, result->ai_addr, static_cast<int>(result->ai_addrlen));
		if (connectionResult == SOCKET_ERROR)
		{
			freeaddrinfo(result);
			return false;
		}
		
		int iRet = setsockopt(socketConnection,
			SOL_SOCKET,
			SO_RCVTIMEO,
			(const char *)&TIMEOUT_VALUE,
			sizeof(TIMEOUT_VALUE));
		iRet = setsockopt(socketConnection,
			SOL_SOCKET,
			SO_SNDTIMEO,
			(const char *)&TIMEOUT_VALUE,
			sizeof(TIMEOUT_VALUE));

		freeaddrinfo(result);
		return true;
	}
	/// Initialise le socket de communication et envoie le Verbe au serveur
	bool SendVerb(SOCKET& socketConnection, std::string addresse, std::string port, int verb)
	{
		// Se connecter au serveur sur le port fourni
		if (!AbstractSocket::CreateSocket(socketConnection, addresse, port))
		{
			std::cout << "Erreur de connection: " << WSAGetLastError() << std::endl;
			return false;
		}
		//std::cout << "Connection etablie!" << std::endl;

		// Envoyer le Verbe
		if (!AbstractSocket::SendInt(socketConnection, verb))
		{
			std::cout << "Erreur de connection: " << WSAGetLastError() << std::endl;
			return false;
		}

		// Réponse au Verbe du serveur
		std::string packagein;
		if (!AbstractSocket::ReceiveStringPackage(socketConnection, packagein))
		{
			std::cout << "Erreur de connection: " << WSAGetLastError() << std::endl;
			return false;
		}
		if (packagein == "ACK-VERB-F")
		{
			//std::cout << "Verbe refuse: " << std::endl;
			return false;
		}
		if (packagein == "ACK-VERB-S")
		{
			//std::cout << "Verbe accepte" << std::endl;
			return true;
		}
		else
		{
			std::cout << "Erreur de connection: " << WSAGetLastError() << std::endl;
			return false;
		}
	}

	/// Fonction primitive: envoie un string. Le destinataire doit connaître la taille du string
	bool SendString(SOCKET socket, std::string message)
	{
		// Allocated char* buffer for message
		char * data = new char[message.size()];
		std::copy(message.begin(), message.end(), data);
		//data[message.size()] = '\0';

		// Number of bytes to send
		int length = (int)message.size();
		int sentTotal = 0;

		while (length > 0)
		{
			int sendResult = send(socket, data, (length < MAX_BUFFER_SIZE ? length : MAX_BUFFER_SIZE), 0);
			if (sendResult == SOCKET_ERROR)
			{
				int err = WSAGetLastError();
				std::cout << "Erreur dans l'envoie d'un string!" << std::endl;
				std::cout << "Fermeture de la connection..." << std::endl;
				closesocket(socket);
				data -= sentTotal;
				delete data;
				return false;
			}
			length -= sendResult;
			sentTotal += sendResult;
			data += sendResult;
		}

		//delete data;
		return true;
	}
	/// Fonction primitive: recoit un string de taille connue
	bool ReceiveString(SOCKET socket, int length, std::string &incoming)
	{
		// New Message
		char* message = new char[length+1];
		// Received bytes so far
		int receivedLength = 0;
		// Until everything is received
		while (receivedLength < length)
		{
			int receivedSize = recv(socket, message, (length < MAX_BUFFER_SIZE ? length : MAX_BUFFER_SIZE), 0);
			if (receivedSize == SOCKET_ERROR)
			{
				message -= receivedLength;
				delete message;
				int err = WSAGetLastError();
				std::cout << "Erreur dans la reception d'un string!" << std::endl;
				std::cout << "Fermeture de la connection..." << std::endl;
				closesocket(socket);
				return false;
			}
			receivedLength += receivedSize;
			message += receivedSize;
		}
		message -= receivedLength;
		message[length] = '\0';
		incoming = std::string(message, length);
		return true;
	}

	/// Envoie un entier signé sur 32 bit
	bool SendInt(SOCKET socket, int32_t value)
	{
		int32_t networkValue = htonl(value);
		//std::string bytes = (char*)&networkValue;
		//SendString(socket, bytes);
		
		int sendResult = send(socket, (char*)&networkValue, sizeof(networkValue), 0);
		if (sendResult == SOCKET_ERROR || sendResult != sizeof(int32_t))
		{
			int err = WSAGetLastError();
			std::cout << "Erreur dans l'envoie d'un int!" << std::endl;
			std::cout << "Fermeture de la connection..." << std::endl;
			closesocket(socket);
			return false;
		}
		
		return true;
	}
	/// Recoie un entier signé sur 32 bit
	bool ReceiveInt(SOCKET socket, int32_t &incoming)
	{
		int32_t receivedInt;
		//std::string received;
		//ReceiveString(socket, sizeof(int32_t), received);
		
		int receivedSize = recv(socket, (char*)&receivedInt, sizeof(int32_t), MSG_WAITALL);
		if (receivedSize == SOCKET_ERROR || receivedSize != sizeof(int32_t))
		{
			int err = WSAGetLastError();
			std::cout << "Erreur dans la reception d'un int!" << std::endl;
			std::cout << "Fermeture de la connection..." << std::endl;
			closesocket(socket);
			return false;
		}
		incoming = (int32_t)ntohl(u_long(receivedInt));
		//incoming = (int32_t)ntohl(u_long(received.c_str()));
		return true;
	}

	/// Envoie un tableau d'entiers signés sur 32 bit
	bool SendMultipleIntPackage(SOCKET socket, std::vector<int32_t> messagePackage)
	{
		// Step 1: Send Package Length
		if (!SendInt(socket, (int32_t)messagePackage.size()))
			return false; // Failed

		// Step 2: Receive ACK-PL
		std::string ack_pl;
		if (!ReceiveString(socket, 6, ack_pl))
			return false; // Failed
		if (ack_pl != "ACK-PL")
			return false; // Failed

		// Step 3: Repeat: Send all strings using Package Method
		for (int32_t message : messagePackage)
		{
			// This part is less Fail-prone
			SendInt(socket, message);
		}
		// Step 4: Receive ACK-PS or ACK-PF
		// PS: Package String Received, DONE
		// PF: Package String Failure, wait for retransmit order
		std::string ack_ps;
		if (!ReceiveString(socket, 6, ack_ps))
			return false; // Failed
		if (ack_ps == "ACK-PS")
			return true; // All messages sent, function done
		if (ack_ps != "ACK-PF")
			return false; // Failed

		// Optional Steps: Received ACK-PF means some failed
		// Re-send loop

		// Step 5: Send ACK-PR
		if (!SendString(socket, "ACK-PR"))
			return false;

		// Step 6: Send asked message until ACK-PS received
		while (true)
		{
			ack_ps.clear();
			int index = -1;
			// Receive message index request
			if (!ReceiveInt(socket, index))
				return false; // Failed
			if (index == -1)
				return false; // Failed

			// Send string using Package Method
			SendInt(socket, messagePackage[index]);

			// Receive ACK-PS or ACK-PF
			if (!ReceiveString(socket, 6, ack_ps))
				return false; // Failed
			if (ack_ps == "ACK-PS")
				return true; // All messages sent, function done
			if (ack_ps != "ACK-PF")
				return false; // ACK-PF means messages remain to be resent
		}
	}
	/// Recoie un tableau d'entiers signés sur 32 bit
	bool ReceiveMultipleIntPackage(SOCKET socket, std::vector<int32_t> &incomingPackage)
	{
		std::map<int, int32_t> receivedPackage;
		std::vector<int> failedIndexes;
		// Step 1: Receive Package Length
		int totalPackage = -1;
		if (!ReceiveInt(socket, totalPackage))
			return false; // Failed
		if (totalPackage == -1)
			return false; // Failed

		// Step 2: Send ACK-PL
		if (!SendString(socket, "ACK-PL"))
			return false; // Failed

		// Step 3: Repeat: Receive all strings using Package Method
		for (int i = 0; i < totalPackage; i++)
		{
			int32_t message;
			// This part is less Fail-prone
			bool res = ReceiveInt(socket, message);
			if (res)
				receivedPackage[i] = message;
			else
				failedIndexes.push_back(i);
		}
		// Step 4: Send ACK-PS or ACK-PF
		// PS: Package String Received, DONE
		// PF: Package String Failure, wait for retransmit order
		std::string ack_ps;
		if (failedIndexes.empty())
			ack_ps = "ACK-PS";
		else
			ack_ps = "ACK-PF";
		if (!SendString(socket, ack_ps))
			return false; // Failed
		if (ack_ps == "ACK-PS")
		{
			// Done, all messages received
			for (int i = 0; i < totalPackage; i++)
				incomingPackage.push_back(receivedPackage[i]);
			return true;
		}

		// Optional Steps: Received ACK-PF means some failed
		// Re-get loop

		// Step 5: Receive ACK-PR
		std::string ack_pr;
		if (!ReceiveString(socket, 6, ack_pr))
			return false; // Failed
		if (ack_pr != "ACK-PR")
			return false; // Failed

		// Step 6: Ask and receive messages until map properly filled
		while (true)
		{
			ack_ps.clear();
			int index = failedIndexes.back();

			// Send message index request
			if (!SendInt(socket, index))
				return false; // Failed

			// Receive string using Package Method
			int32_t message;
			bool res = ReceiveInt(socket, message);
			if (res)
			{
				receivedPackage[index] = message;
				failedIndexes.pop_back();
			}

			// Send ACK-PS or ACK-PF
			if (failedIndexes.empty())
				ack_ps = "ACK-PS";
			else
				ack_ps = "ACK-PF";
			if (!SendString(socket, ack_ps))
				return false; // Failed
			if (ack_ps == "ACK-PS")
			{
				// Done, all messages received
				for (int i = 0; i < totalPackage; i++)
					incomingPackage.push_back(receivedPackage[i]);
				return true;
			}
		}
	}

	/// Envoie un string. S'occupe du handling de la taille
	bool SendStringPackage(SOCKET socket, std::string message)
	{
		// Step 1: Send length
		int length = (int)message.length();
		if (!SendInt(socket, length))
			return false; // Failed

		// Step 2: Receive "ACK-L"
		std::string ack_l;
		if (!ReceiveString(socket, 5, ack_l))
			return false; // Failed
		if (ack_l != "ACK-L")
			return false; // Failed

		// Step 3: Send string
		if (!SendString(socket, message))
			return false; // Failed

		// Step 4: Receive ACK-S
		std::string ack_s;
		if (!ReceiveString(socket, 5, ack_s))
			return false; // Failed
		if (ack_s != "ACK-S")
			return false; // Failed

		// Done
		return true;
	}
	/// Recoit un string. S'occupe du handling de la taille
	bool ReceiveStringPackage(SOCKET socket, std::string &incoming)
	{
		// Step 1: Receive length
		int length = -1;
		if (!ReceiveInt(socket, length))
			return false; // Failed
		if (length == -1)
			return false; // Failed

		// Step 2: Send ACK-L
		if (!SendString(socket, "ACK-L"))
			return false; // Failed

		// Step 3: Receive string
		if (!ReceiveString(socket, length, incoming))
			return false; // Failed

		// Step 4: Send ACK-S
		if (!SendString(socket, "ACK-S"))
			return false; // Failed

		// Done
		return true;
	}

	/// Envoie un vecteur de string. S'occupe du handling individuel. Guarantit l'envoie de tout les strings
	bool SendMultipleStringPackage(SOCKET socket, std::vector<std::string> messagePackage)
	{
		// Step 1: Send Package Length
		if (!SendInt(socket, (int32_t)messagePackage.size()))
			return false; // Failed

		// Step 2: Receive ACK-PL
		std::string ack_pl;
		if (!ReceiveString(socket, 6, ack_pl))
			return false; // Failed
		if (ack_pl != "ACK-PL")
			return false; // Failed

		// Step 3: Repeat: Send all strings using Package Method
		for (std::string message : messagePackage)
		{
			// This part is less Fail-prone
			SendStringPackage(socket, message);
		}
		// Step 4: Receive ACK-PS or ACK-PF
		// PS: Package String Received, DONE
		// PF: Package String Failure, wait for retransmit order
		std::string ack_ps;
		if (!ReceiveString(socket, 6, ack_ps))
			return false; // Failed
		if (ack_ps == "ACK-PS")
			return true; // All messages sent, function done
		if (ack_ps != "ACK-PF")
			return false; // Failed

		// Optional Steps: Received ACK-PF means some failed
		// Re-send loop

		// Step 5: Send ACK-PR
		if (!SendString(socket, "ACK-PR"))
			return false;

		// Step 6: Send asked message until ACK-PS received
		while (true)
		{
			ack_ps.clear();
			int index = -1;
			// Receive message index request
			if (!ReceiveInt(socket, index))
				return false; // Failed
			if (index == -1)
				return false; // Failed

			// Send string using Package Method
			SendStringPackage(socket, messagePackage[index]);

			// Receive ACK-PS or ACK-PF
			if (!ReceiveString(socket, 6, ack_ps))
				return false; // Failed
			if (ack_ps == "ACK-PS")
				return true; // All messages sent, function done
			if (ack_ps != "ACK-PF")
				return false; // ACK-PF means messages remain to be resent
		}
	}
	/// Recoit un vecteur de string. S'occupe du handling individuel. Guarantit la reception de tout les strings
	bool ReceiveMultipleStringPackage(SOCKET socket, std::vector<std::string> &incomingPackage)
	{
		std::map<int, std::string> receivedPackage;
		std::vector<int> failedIndexes;
		// Step 1: Receive Package Length
		int totalPackage = -1;
		if (!ReceiveInt(socket, totalPackage))
			return false; // Failed
		if (totalPackage == -1)
			return false; // Failed

		// Step 2: Send ACK-PL
		if (!SendString(socket, "ACK-PL"))
			return false; // Failed

		// Step 3: Repeat: Receive all strings using Package Method
		for (int i = 0; i < totalPackage; i++)
		{
			std::string message;
			// This part is less Fail-prone
			bool res = ReceiveStringPackage(socket, message);
			if (res)
				receivedPackage[i] = message;
			else
				failedIndexes.push_back(i);
		}
		// Step 4: Send ACK-PS or ACK-PF
		// PS: Package String Received, DONE
		// PF: Package String Failure, wait for retransmit order
		std::string ack_ps;
		if (failedIndexes.empty())
			ack_ps = "ACK-PS";
		else
			ack_ps = "ACK-PF";
		if (!SendString(socket, ack_ps))
			return false; // Failed
		if (ack_ps == "ACK-PS")
		{
			// Done, all messages received
			for (int i = 0; i < totalPackage; i++)
				incomingPackage.push_back(receivedPackage[i]);
			return true;
		}

		// Optional Steps: Received ACK-PF means some failed
		// Re-get loop

		// Step 5: Receive ACK-PR
		std::string ack_pr;
		if (!ReceiveString(socket, 6, ack_pr))
			return false; // Failed
		if (ack_pr != "ACK-PR")
			return false; // Failed

		// Step 6: Ask and receive messages until map properly filled
		while (true)
		{
			ack_ps.clear();
			int index = failedIndexes.back();

			// Send message index request
			if (!SendInt(socket, index))
				return false; // Failed

			// Receive string using Package Method
			std::string message;
			bool res = ReceiveStringPackage(socket, message);
			if (res)
			{
				receivedPackage[index] = message;
				failedIndexes.pop_back();
			}

			// Send ACK-PS or ACK-PF
			if (failedIndexes.empty())
				ack_ps = "ACK-PS";
			else
				ack_ps = "ACK-PF";
			if (!SendString(socket, ack_ps))
				return false; // Failed
			if (ack_ps == "ACK-PS")
			{
				// Done, all messages received
				for (int i = 0; i < totalPackage; i++)
					incomingPackage.push_back(receivedPackage[i]);
				return true;
			}
		}
	}

	


}