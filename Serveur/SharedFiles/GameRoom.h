//////////////////////////////////////////////////////////////////////////////
/// @file GameRoom.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_GAMEROOM_H__
#define __SERVEUR_GAMEROOM_H__
#include "User.h"
#include "IP.h"
////////////////////////////////////////////////////////////////////////////////
///
/// @class GameRoom
/// @brief Classe représentant une salle de jeu
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class GameRoom
{
public:
	// Constructeur
	GameRoom(User* host);
	// Constructeur pour client
	GameRoom(bool isHost, User* host);
	// Destructeur
	~GameRoom();
	// Retourne le nom de l'hote
	std::string getHostName();
	// Démarre une partie
	bool STARTGAME();
	// Retourne l'état de la game
	bool isDead();
	// Retourne l'état de la game
	bool isStarted();
	// Ajout d'un joueur
	bool joinRoom(User* player);
	// Retrait d'un joueur
	bool leaveRoom(User* player);
	// Modification du mot de passe
	bool setPassword(std::string password);
	// Verification du mot de passe
	bool checkPassword(std::string password);
	// Ajoute un joueur dans un slot, POUR LOCAL SEULEMENT
	void addPlayerToSlot(User* user, int slot);
	// Obtenir le nom de la salle de jeu
	std::string getRoomName();
	// Obtenir le nom de la carte
	std::string getMapName();
	// Obtenir le type de jeu
	std::string getGameType();
	// Retourne le numéro d'un joueur
	int getPlayerNumber(User* user);
	// Retourne le numéro d'un joueur
	int getPlayerNumber(std::string user);
	// Obtenir les informations de la salle
	std::vector<std::string> getRoomInfo();
	// Obtenir les informations sur les joueurs de la salle
	std::vector<std::string> getRoomPlayerInfo();
	// Set le IP de l'hote
	void setHostIP(IP* hostIP);
	// Retourne l'IP de l'hote
	IP* getHostIP();
	// Retourne le nombre de joueurs dans la partie
	int getNumberOfPlayers();
	// Mise à jour des informations
	bool updateGameInfo(std::string map, std::string info, std::string temps, bool instadeath);
	// Met le joueur à l'état fourni
	bool setPlayerReady(User* user, bool state);
	// Retourne true si l'user est dans la partie
	bool userIsPlayer(User* user);
	// Donne une victoire aux joueurs
	void setGameWon();
	// Retourne tout les joueurs
	std::vector<User*> getAllUsers();

private:
	// Utilisé pour assuré le départ fiable de la partie
	bool GAMESTARTED = false;
	// Utilisé pour signifier une partie terminée
	bool GAMEDEAD = false;
	// Mot de passe de la salle
	std::string password_ = "";
	// Noms des cartes de la partie/campagne
	std::string mapName_ = "";
	// Type de partie
	std::string gameType_ = "";
	// Instadeath ou non
	bool instaDeath_ = false;
	// Time Death ou pas
	int temps_ = -1;
	// Pointer to host
	User* host_ = nullptr;
	// Host's IP
	IP* hostIP_ = nullptr;
	// Pointer to player User
	User* player2_ = nullptr;
	// Player status
	bool readyPlayer2_ = false;
	// Pointer to player User
	User* player3_ = nullptr;
	// Player status
	bool readyPlayer3_ = false;
	// Pointer to player User
	User* player4_ = nullptr;
	// Player status
	bool readyPlayer4_ = false;
};

#endif // __SERVEUR_GAMEROOM_H_