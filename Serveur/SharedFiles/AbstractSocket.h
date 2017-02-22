//////////////////////////////////////////////////////////////////////////////
/// @file AbstractSocket.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Client
//////////////////////////////////////////////////////////////////////////////

#ifndef __CLIENT_ABSTRACTSOCKET_H__
#define __CLIENT_ABSTRACTSOCKET_H__

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <stdint.h>
#include <vector>
#include "IP.h"

////////////////////////////////////////////////////////////////////////////////
///
/// @namespace Utilitaire
/// @brief Namespace contrôllant des fonctions pour simplifier la communication par Winsock
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
namespace AbstractSocket
{
	/// Initialise un socket fourni en paramètre à une connection à l'adresse:port
	bool AS_TCP_CreateSocket(SOCKET& socketConnection, std::string addresse, std::string port);

	/// Initialise le socket de communication et envoie le Verbe au serveur
	bool AS_TCP_SendVerb(SOCKET& socketConnection, std::string addresse, std::string port, int verb);

	/// Fonction primitive: envoie un string. Le destinataire doit connaître la taille du string
	bool AS_TCP_SendString(SOCKET socket, std::string message);
	/// Fonction primitive: recoit un string de taille connue
	bool AS_TCP_ReceiveString(SOCKET socket, int length, std::string &incoming);

	/// Envoie un entier signé sur 32 bit
	bool AS_TCP_SendInt(SOCKET socket, int32_t message);
	/// Recoie un entier signé sur 32 bit
	bool AS_TCP_ReceiveInt(SOCKET socket, int32_t &incoming);

	/// Envoie un tableau d'entiers signés sur 32 bit
	bool AS_TCP_SendMultipleIntPackage(SOCKET socket, std::vector<int32_t> messagePackage);
	/// Recoie un tableau d'entiers signés sur 32 bit
	bool AS_TCP_ReceiveMultipleIntPackage(SOCKET socket, std::vector<int32_t> &incomingPackage);

	/// Envoie un string. S'occupe du handling de la taille
	bool AS_TCP_SendStringPackage(SOCKET socket, std::string message);
	/// Recoit un string. S'occupe du handling de la taille
	bool AS_TCP_ReceiveStringPackage(SOCKET socket, std::string &incoming);

	/// Envoie un vecteur de string. S'occupe du handling individuel. Guarantit l'envoie de tout les strings
	bool AS_TCP_SendMultipleStringPackage(SOCKET socket, std::vector<std::string> messagePackage);
	/// Recoit un vecteur de string. S'occupe du handling individuel. Guarantit la reception de tout les strings
	bool AS_TCP_ReceiveMultipleStringPackage(SOCKET socket, std::vector<std::string> &incomingPackage);

};

#endif //__CLIENT_ABSTRACTSOCKET_H__
