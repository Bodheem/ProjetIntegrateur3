//////////////////////////////////////////////////////////////////////////////
/// @file GameServerData.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_SERVERCONTROL_H__
#define __SERVEUR_SERVERCONTROL_H__

#include "GameServerData.h"
#include <mutex>
#include <WinSock2.h>
#include <vector>
#include <thread> 
#include <future>
#include <list>
#include <map>
	#ifndef SERVERTESTER
#include "../../../Serveur/SharedFiles/AbstractSocketV2.h"
#else
#include "../../../../../Serveur/SharedFiles/AbstractSocketV2.h"
#endif


////////////////////////////////////////////////////////////////////////////////
///
/// @class ServerControl
/// @brief Classe contrôllant les différents threads de communication
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class GameServerControl
{
public:
	////////////////////////////////////
	// Creation

	/// Constructeur
	GameServerControl();
	/// Destructeur
	~GameServerControl();
	/// Initialise le serveur de jeu
	void startServer(int numberOfPlayers, std::string mapName);

	////////////////////////////////////
	// Singleton

	/// Pointeur vers l'instance unique de GameServerControlPointer
	static GameServerControl* GameServerControlPointer;
	/// Obtenir le pointeur statique vers le GameServerData
	static GameServerControl* getPointer();
	/// Détruit l'instance unique de GameServerControl
	static void deletePointer();

	/// Completely reinitialize multiplayer server
	void resetGameServer();

	////////////////////////////////////
	// Multithreading safety

	/// Acquire safety mutex
	void obtainSecureLock(std::string lastCaller);
	/// Release safety mutex
	void releaseSecureLock();



	////////////////////////////////////
	// Multithreading

	// Thread de communication 1: TCP 5035
	// Communication passive qui attend une connexion
	// Gère l'état de la partie et permet de la débuter et d'envoyer des ordres de contrôles aux joueurs
	friend int MultiThreadCommunicationHandling(AbstractSocket::TCPSocket* sd_, GameServerControl* serverControl_); // TCP 5035
	// Thread de communication 2: UDP 5040
	// Communication active vers les joueurs
	// Envoie aux 50 ms un SnapShot de la map actuelle pour synchronisé
	// la partie avec les joueurs
	friend int MultiThreadSnapShotHandling(AbstractSocket::UDPSocket* sd_, GameServerControl* serverControl_); // UDP 5040
	// Thread de communication 3: TCP 5045
	// Communication passive qui attend une connexion
	// Recoit les connexions des utilisateurs (nouveaux ou reconnectant) 
	// et note leur adresse IP localement pour les autres threads
	friend int MultiThreadConnectionHandling(AbstractSocket::TCPSocket* sd_, GameServerControl* serverControl_); // TCP 5045
	// Thread de communication 4: UDP 5050
	// Communication passive qui attend un message
	// Recoit aux 10ms, par joueur, l'état de leurs boutons pour simuler la physique
	friend int MultiThreadStatusHandling(AbstractSocket::UDPSocket* sd_, GameServerControl* serverControl_); // UDP 5050
	/// Kill all threads
	void killAllThreads();

	////////////////////////////////////
	// Client-Server Communication Actions
	// // // Connection related

	// Prépare les communications
	bool initializeCommunications();
	// Initialise les sockets
	void createSocketVector();

	// Server Model Class
	GameServerData* serverData_;
private:
	// Maximum de sockets / joueurs connectés
	const int MAX_SOCKET_ALLOWED = 30;
	// Temps pour refresh la carte
	const int SNAPSHOT_REFRESH_TIME = 15;
	// Ordre pour terminer les threads de jeu
	bool GLOBAL_KILL_THREAD_ORDER = false;
	/// State of Connection Thread
	bool THREAD_CONNEC_DEAD = true;
	/// State of Communication Thread
	bool THREAD_COMMS_DEAD = true;
	/// State of Status Thread
	bool THREAD_STATUS_DEAD = true;
	/// State of SnapShot Thread
	bool THREAD_SNAPSHOT_DEAD = true;

	// Liste des sockets TCP multijoueur
	std::map<int, AbstractSocket::TCPSocket*> TCPSocketList_;
	// Liste des sockets UDP multijoueur
	std::map<int, AbstractSocket::UDPSocket*> UDPSocketList_;

	// Affiche un timestamp au ms dans la console avec le message
	void printTimestamp(std::string);

	// Rule of three
	GameServerControl(const GameServerControl& that);
	// Rule of three
	GameServerControl& operator=(const GameServerControl& that);
};

#endif // __SERVEUR_SERVERCONTROL_H__

