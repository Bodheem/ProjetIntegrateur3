//////////////////////////////////////////////////////////////////////////////
/// @file ServerData.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_SERVERCONTROL_H__
#define __SERVEUR_SERVERCONTROL_H__

#include "ServerData.h"
#include <mutex>
#include <WinSock2.h>
#include <vector>
#include <thread> 
#include <future>
#include "../PortStatus/PortStatus.h"
#include "..\..\..\SharedFiles\AbstractSocketV2.h"


////////////////////////////////////////////////////////////////////////////////
///
/// @class ServerControl
/// @brief Classe contrôllant les différents threads de communication
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class ServerControl
{
public:
	////////////////////////////////////
	// Creation et contrôle
	/// Constructeur
	ServerControl();
	/// Destructeur
	~ServerControl();

	/// Thread principal du projet
	bool mainThreadLoop();

	/// Subclass: Données du serveur
	ServerData* serverData_;

	////////////////////////////////////
	/// Pointeur vers l'instance unique de ServerControlPointer
	static ServerControl* ServerControlPointer;
	// Obtenir le pointeur statique vers le ServerControl
	static ServerControl* getPointer();
	

	////////////////////////////////////
	// Multithreading safety
	/// Obtain Secure ServerData Lock
	void obtainSecureLock(std::string lastCaller);
	/// Release Secure ServerData Lock
	void releaseSecureLock();

	////////////////////////////////////
	// Multithreading
	/// Thread de communication 5000: Connection TCP et obtention de port unique
	friend int MultiThreadConnectionHandling(AbstractSocket::TCPSocket* sd_, ServerControl* control_);
	/// Thread de communication 5001-5050: Connection TCP et communication privée avec client
	friend int MultiThreadUserHandling(AbstractSocket::TCPSocket* sd_, ServerControl* control_, PortStatus* thisPortStatus_);
	

	////////////////////////////////////
	// Client-Server Communication Actions
	// // // Connection related
	/// Initialize ServerSide Communications Ports and Threading
	bool initializeCommunications(); 
	/// Initialize ServerSide Sockets
	void createSocketVector();
	/// Verb 69: Test communications
	bool commsTest(AbstractSocket::TCPSocket* socketTCP, PortStatus* portStatus);
	/// Send Verb Response to Client query
	bool executeSendVerbResponse(AbstractSocket::TCPSocket* socket, PortStatus* portStatus, bool requiresLogin, IP* remoteIP);
	/// Verb 0: Abandon dedicated link to client
	void executeAbandonSocket(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 1: Keep Alive sur le socket
	void executeKeepAlive(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);

	////////////////////////////////////
	// Client-Server Communication Actions
	// // // User Account Related
	/// Verb 12: Création de compte Utilisateur
	void executeCreateUserAccount(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 11: Login avec compte Utilisateur
	void executeLogin(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 10: Logout avec compte Utilisateur
	void executeLogout(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 13: Obtenir les informations du compte Utilisateur
	void executeGetUserAccountInfo(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 14: Mettre à jour les informations du compte Utilisateur
	void executeUpdateUserAccountInfo(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 15: Reset password du compte Utilisateur
	void executeResetUserAccountPassword(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);

	////////////////////////////////////
	// Client-Server Communication Actions
	// // // Chat Related
	/// Verb 21: Obtenir la liste des salles de chat
	void executeUpdateChatRoomList(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 22: Envoyer un nouveau message au chat
	void executeSendNewChatMessage(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 23: Obtenir les nouveaux messages du chat
	void executeRequestMessageHistoryUpdate(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);

	////////////////////////////////////
	// Client-Server Communication Actions
	// // // Game Room Related
	/// Verb 31: Obtenir la liste des salles de jeu
	void executeUpdateGameRoomList(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 32: Création d'une salle de jeu
	void executeCreateGameRoom(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 33: Joindre une salle de jeu
	void executeJoinGameRoom(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 34: Joindre automatiquement une salle de jeu
	void executeMatchmaking(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 35: Quitter une salle de jeu
	void executeLeaveGameRoom(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 41: Débuter une partie
	void executeStartGame(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 42: Change l'état d'un joueur
	void executeSetReady(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 44: Mettre à jour les informations de la salle de jeu actuelle
	void executeUpdateGameRoomInfo(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 45: Mettre à jour les informations des joueurs de la salle de jeu actuelle
	void executeUpdateGameRoomPlayerInfo(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 50: Obtenir les informations pour se reconnecter à une partie pré-existante
	void executeRejoinPreviousGame(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	
	////////////////////////////////////
	// Client-Server Communication Actions
	// // // Game Map Related
	/// Verb 61: Download toutes les cartes disponibles du serveur
	void executeDownloadMap(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);
	/// Verb 62: Upload toutes les cartes modifiées au serveur
	void executeUploadMap(AbstractSocket::TCPSocket* socket, PortStatus* portStatus);

private:
	/// Constante limitant le nombre de connexions au serveur
	const int MAX_SOCKET_ALLOWED = 30;
	/// Ordre de termination des communications
	bool GLOBAL_KILL_THREAD_ORDER = false;
	/// Permet de vérifier lorsque tout les threads sont morts 
	bool ALL_THREADS_ARE_DEAD = false;
	/// Liste des sockets utilisés pour la communication
	std::vector<AbstractSocket::TCPSocket*> TCPSocketList_;
	/// Liste des threads de communications asynchrones
	std::vector<std::thread*> threadList_;
	/// Liste des ports ouverts sur le serveur et le statut de leur connexion aux utilisateurs
	std::list<PortStatus*> portStatus_;
	/// IP du serveur
	IP* serverIP_ = nullptr;

	/// Print timestamp to console
	void printTimestamp(std::string);
	/// Disconnect everyone from the server
	void disconnectEveryone();
	/// Disconnect specific user from the server
	void disconnectUser(std::string username);
};

#endif // __SERVEUR_SERVERCONTROL_H__

