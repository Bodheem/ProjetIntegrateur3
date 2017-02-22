//////////////////////////////////////////////////////////////////////////////
/// @file AbstractSocketV2.h
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
/// @namespace AbstractSocket
/// @brief Namespace contrôllant des fonctions pour simplifier la communication par Winsock
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
namespace AbstractSocket
{
	/// Classe regroupant les fonctionalités Socket TCP
	class TCPSocket
	{
	public:
		// Constructeur
		TCPSocket(SOCKET socket, int intport);
		// Constructeur
		TCPSocket(int intport);
		// Destructeur
		~TCPSocket();

		// Socket internet Winsock
		SOCKET socket_;
		// Port utilisé
		unsigned short port_; 
		// Référence a la derniere erreure
		int lastError_ = 0;
	private:
		// Rule of three
		TCPSocket(const TCPSocket& that);
		// Rule of three
		TCPSocket& operator=(const TCPSocket& that);
	};
	/// Classe regroupant les fonctionalités Socket UDP
	class UDPSocket
	{
	public:
		// Constructeur
		UDPSocket(int intport);
		// Destructeur
		~UDPSocket();

		// Socket internet Winsock
		SOCKET socket_;
		// Port utilisé
		unsigned short port_;
		// Référence a la derniere erreure
		int lastError_ = 0;
	private:
		// Rule of three
		UDPSocket(const UDPSocket& that);
		// Rule of three
		UDPSocket& operator=(const UDPSocket& that);
	};

	/// Retourne l'addresse IP Locale
	IP* getLocalIP();

	////////////////////////////////////
	/// Fonctions TCP

	/// Initialise un socket fourni en paramètre à une connection à l'adresse:port
	bool CreateSocket(TCPSocket* socketConnection, std::string addresse, std::string port);
	/// Initialise le socket de communication et envoie le Verbe au serveur
	bool SendVerb(TCPSocket* socketConnection, std::string addresse, std::string port, int verb);

	/// Fonction primitive: envoie un string. Le destinataire doit connaître la taille du string
	bool SendString(TCPSocket* socket, std::string message);
	/// Fonction primitive: recoit un string de taille connue
	bool ReceiveString(TCPSocket* socket, int length, std::string &incoming);

	/// Envoie un entier signé sur 32 bit
	bool SendInt(TCPSocket* socket, int32_t message);
	/// Recoie un entier signé sur 32 bit
	bool ReceiveInt(TCPSocket* socket, int32_t &incoming);

	/// Envoie un tableau d'entiers signés sur 32 bit
	bool SendMultipleIntPackage(TCPSocket* socket, std::vector<int32_t> messagePackage);
	/// Recoie un tableau d'entiers signés sur 32 bit
	bool ReceiveMultipleIntPackage(TCPSocket* socket, std::vector<int32_t> &incomingPackage);

	/// Envoie un string. S'occupe du handling de la taille
	bool SendStringPackage(TCPSocket* socket, std::string message);
	/// Recoit un string. S'occupe du handling de la taille
	bool ReceiveStringPackage(TCPSocket* socket, std::string &incoming);

	/// Envoie un vecteur de string. S'occupe du handling individuel. Guarantit l'envoie de tout les strings
	bool SendMultipleStringPackage(TCPSocket* socket, std::vector<std::string> messagePackage);
	/// Recoit un vecteur de string. S'occupe du handling individuel. Guarantit la reception de tout les strings
	bool ReceiveMultipleStringPackage(TCPSocket* socket, std::vector<std::string> &incomingPackage);


	////////////////////////////////////
	/// Fonctions UDP

	/// Fonction primitive: envoie un string. Le destinataire doit connaître la taille du string
	bool SendString(UDPSocket* socket, std::string message, IP* address);
	/// Fonction primitive: recoit un string de taille connue
	bool ReceiveString(UDPSocket* socket, int length, std::string &incoming, IP* sender);

	/// Envoie un entier signé sur 32 bit
	bool SendInt(UDPSocket* socket, int32_t message, IP* address);
	/// Recoie un entier signé sur 32 bit
	bool ReceiveInt(UDPSocket* socket, int32_t &incoming, IP* sender);
	/// Envoie un string. S'occupe du handling de la taille. Arrivée non guarantie
	bool SendStringPackage(UDPSocket* socket, std::string message, IP* address);
	/// Recoit un string. S'occupe du handling de la taille. Arrivée non guarantie
	bool ReceiveStringPackage(UDPSocket* socket, std::string &incoming, IP* sender);
	/// Envoie un TRÈS GROS string. S'occupe du handling de la taille. Arrivée guarantie en 30min ou c'est gratuit
	bool SendStringPackage(TCPSocket* tcp, UDPSocket* udp, std::string message, IP* address);
	/// Recoit un TRÈS GROS string. S'occupe du handling de la taille. Arrivée guarantie en 30min ou c'est gratuit
	bool ReceiveStringPackage(TCPSocket* tcp, UDPSocket* udp, std::string &incoming, IP* sender);

};

#endif //__CLIENT_ABSTRACTSOCKET_H__
