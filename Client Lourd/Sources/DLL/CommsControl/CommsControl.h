//////////////////////////////////////////////////////////////////////////////
/// @file CommsControl.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Client
//////////////////////////////////////////////////////////////////////////////

#ifndef __CLIENT_COMMSCONTROL_H__
#define __CLIENT_COMMSCONTROL_H__

#undef UNICODE
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// link with Ws2_32.lib
#pragma comment( lib, "ws2_32.lib" )

#include <winsock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <string>
#include <mutex>
#include <future>
#include "ChatControl\ChatControl.h"
#include "GameControl\GameControl.h"
#include "GameServerControl\GameServerControl.h"
	#ifndef SERVERTESTER
#include "../../../Serveur/SharedFiles/User.h"
#include "../../../Serveur/SharedFiles/AbstractSocketV2.h"
#else
#include "../../../../Serveur/SharedFiles/User.h"
#include "../../../../Serveur/SharedFiles/AbstractSocketV2.h"
	#endif

////////////////////////////////////////////////////////////////////////////////
///
/// @class CommsControl
/// @brief Classe contrôllant la communication avec le serveur
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class CommsControl
{
public:
	////////////////////////////////////
	// Creation et accès

	/// Constructeur
	CommsControl();
	/// Destructeur
	~CommsControl();
	
	////////////////////////////////////
	// Client-Server Communication Actions
	// // // Connexion et tests

	/// Connection initiale au Server et obtention du port de communication dédié
	bool initializeCommunications(std::string ip);
	/// Verb 69: Test de communication réseau
	bool commsTest();
	/// Verb 0: Abandon du socket réservé. Requiert de refaire initializeCommunications par après
	bool executeAbandonSocket();
	/// Connection à l'hote multijoueur
	bool initializeMultiplayerGame();
	/// Connection initiale au Host et obtention des ports de communications
	bool initializeMultiplayerCommunications(std::string hostIP);
	/// Crée les vecteurs de sockets
	bool createMultiplayerSocketVector();

	////////////////////////////////////
	// // // Autres fonctions

	/// Récupérer le User
	User* getUser();
	/// Retourne true si la partie est commencée
	bool isGameStarted();
	/// Retourne true si le joueur est l'hote
	bool isHostMachine();
	/// En tant qu'Host, dire que la partie est gagnée
	void setGameWon();
	/// En tant qu'Host, dire que la partie est perdue
	void setGameLost();
	/// Informe le host que le joueur a perdu
	void asPlayerSetPlayerLost();
	/// Informe le host que le joueur a gagné
	void asPlayerSetPlayerWon();
	/// En tant qu'Host, dire à un joueur qu'il a perdu
	void asHostSetPlayerLost(int playerNumber);
	/// En tant qu'Host, dire à un joueur qu'il a gagné
	void asHostSetPlayerWin(int playerNumber);

	////////////////////////////////////
	// Multithreading

	// Thread de communication 1: TCP 5035
	// Communication active vers les joueurs
	// Gère l'état de la partie et permet de la débuter et d'envoyer des ordres de contrôles aux joueurs
	friend int MPMultiThreadCommunicationHandling(AbstractSocket::TCPSocket* sd_, CommsControl* control_); // TCP 5035
	// Thread de communication 2: UDP 5040
	// Communication active vers le serveur
	// Recoit aux 50 ms un SnapShot de la map actuelle pour synchroniser
	// la partie avec le serveur
	friend int MPMultiThreadSnapShotHandling(AbstractSocket::UDPSocket* sd_, CommsControl* control_); // UDP 5040
	// Thread de communication 3: UDP 5050
	// Communication passive qui attend un message
	// Envoie aux 10ms l'état des boutons pour simuler la physique coté serveur
	friend int MPMultiThreadStatusHandling(AbstractSocket::UDPSocket* sd_, CommsControl* control_); // UDP 5050

	////////////////////////////////////
	// Multiplayer

	/// Completely reinitialize multiplayer controls
	void resetMultiplayer();
	/// Kill all threads
	void killAllThreads();
	/// Returns the Multiplayer Game Status
	std::string getMPGameStatus();
	/// Return true if playing a game online
	bool isGameOnline();
	/// Prepare next game in campaign Mode
	void MPPrepareNextGame();

	////////////////////////////////////
	// Client-Server Communication Actions
	// // // Looped Actions

	/// Verb 1: Keep Alive sur le socket
	/// Garde la connection en vie avec le serveur distant
	bool executeKeepAlive();
	/// Actions exécutées en boucle par le client (Keep Alive)
	bool executeLoopingCommunicationActions();

	////////////////////////////////////
	// Client-Server Communication Actions
	// // // User Account Related

	/// Verb 12: Création de compte Utilisateur
	bool executeCreateUserAccount(std::string username, std::string password, std::string email, bool &accountCreated);
	/// Verb 11: Login avec compte Utilisateur
	bool executeLogin(std::string username, std::string password, bool &loginAccepted);
	/// Verb 10: Logout avec compte Utilisateur
	bool executeLogout(bool &logoutSuccessful);
	/// Verb 13: Obtenir les informations du compte Utilisateur
	/// Crée la classe User locale à partir des informations les plus récentes du serveur
	bool executeGetUserAccountInfo(bool &success);
	/// Verb 14: Mettre à jour les informations du compte Utilisateur
	/// Met à jour la classe user distante à partir des informations de la classe User locale
	bool executeUpdateUserAccountInfo(bool &success);
	/// Verb 15: Reset password du compte Utilisateur
	bool executeResetUserAccountPassword(std::string username, bool &success);

	////////////////////////////////////
	// Client-Server Communication Actions
	// // // Chat Related

	/// Verb 21: Obtenir la liste des salles de chat
	/// Met à jour la liste de ChatRoom locale et retourne un vecteur de leurs noms
	bool executeUpdateChatRoomList(std::vector<std::string>& listeChatRoom);
	/// Verb 22: Envoyer un nouveau message au chat
	bool executeSendNewChatMessage(std::string message, std::string chatRoomName);
	/// Verb 23: Obtenir les nouveaux messages du chat
	/// Met à jour l'historique local des messages de toutes les salles de conversation
	bool executeRequestMessageHistoryUpdate();
	/// Retourne les nouveaux messages de la salle passée en paramètre
	bool RequestMessageHistoryUpdate(std::string chatRoomName, std::vector<std::string> &messageList);
	/// Retourne tout les messages de la salle passée en paramètre
	bool RequestMessageHistoryComplete(std::string chatRoomName, std::vector<std::string> &messageList);

	////////////////////////////////////
	// Client-Server Communication Actions
	// // // Game Room Related

	/// Verb 31: Obtenir la liste des salles de jeu
	bool executeUpdateGameRoomList(std::vector<std::string>& listeGameRoom);
	/// Verb 32: Création d'une salle de jeu
	bool executeCreateGameRoom(bool &success);
	/// Verb 33: Joindre une salle de jeu
	bool executeJoinGameRoom(std::string chatRoomName, std::string password, bool &success);
	/// Verb 34: Joindre automatiquement une salle de jeu
	bool executeMatchmaking(bool &success, bool &host);
	/// Verb 35: Quitter une salle de jeu
	bool executeLeaveGameRoom(bool &success);
	/// Verb 41: Débuter une partie
	bool executeStartGame(bool &success);
	/// Verb 42: Se mettre comme prêt
	bool executeSetReady(bool status, bool &success);
	/// Verb 44: Mettre à jour les informations de la salle de jeu actuelle
	bool executeUpdateGameRoomInfo(std::vector<std::string> info, std::vector<std::string> &updatedInfo, bool &success);
	/// Verb 45: Mettre à jour les informations des joueurs de la salle de jeu actuelle
	bool executeUpdateGameRoomPlayerInfo(std::vector<std::string> &updatedInfo, bool &success);
	/// Verb 50: Obtenir les informations pour se reconnecter à une partie pré-existante
	bool executeRejoinPreviousGame(bool &success);

	////////////////////////////////////
	// Client-Server Communication Actions
	// // // Game Map Related

	/// Verb 61: Download toutes les cartes disponibles du serveur
	bool executeDownloadMap(bool &success);
	/// Verb 62: Upload toutes les cartes modifiées au serveur
	bool executeUploadMap(bool &success);

	/// Game Control Pointer
	GameControl* gameControl_ = nullptr;
	/// Game Server Control for Host
	GameServerControl* gameServer_ = nullptr;
private:
	// Temps pour refresh le statut du joueur
	const int STATUS_REFRESH_TIME = 15;
	// Temps pour refresh l'état de la partie
	const int COMMS_REFRESH_TIME = 500;
	////////////////////////////////////
	// Multithreading safety

	/// Acquire safety mutex
	void obtainSecureLock(std::string lastCaller);
	/// Release safety mutex
	void releaseSecureLock();
	/// Set to true to kill threads
	bool GLOBAL_KILL_THREAD_ORDER = false;
	/// State of Communication Thread
	bool THREAD_COMMS_DEAD = true;
	/// State of Status Thread
	bool THREAD_STATUS_DEAD = true;
	/// State of SnapShot Thread
	bool THREAD_SNAPSHOT_DEAD = true;
	
	/// CommsControl mutex for threadsafety
	std::mutex safetyMutex_;
	/// True when mutex is locked, for debug purposes
	bool safetyMutexIsLocked_ = false;
	/// Last call that locked safety mutex
	std::string safetyMutexLastCaller = "";

	/// Initial port 5000 communication socket
	AbstractSocket::TCPSocket* socketInitial_ = nullptr;
	/// Personal communication socket
	AbstractSocket::TCPSocket* socketCommunication_ = nullptr;
	/// Socket de communication vers l'hote
	AbstractSocket::TCPSocket* socketConnexionMultiplayer_ = nullptr;
	/// Server IP String
	std::string serverIPStr_ = "";
	/// Server IP Class
	IP* serverIPClass_ = nullptr;
	/// Server personal communication port
	std::string serverDedicatedPort_ = "";
	/// Server personal communication port
	int assignedPort_ = -1;

	/// Chat Control Pointer
	ChatControl* chatControl_ = nullptr;
	/// Local User-Account Reference
	User* user_ = nullptr;

	/// Multiplayer TCP Socket Map
	std::map<int, AbstractSocket::TCPSocket*> MPTCPSocketList_;
	/// Multiplayer UDP Socket Map
	std::map<int, AbstractSocket::UDPSocket*> MPUDPSocketList_;

	/// Print timestamp to console
	void printTimestamp(std::string);
};

#endif // __CLIENT_COMMSCONTROL_H__