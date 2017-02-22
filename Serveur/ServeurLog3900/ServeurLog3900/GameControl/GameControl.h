//////////////////////////////////////////////////////////////////////////////
/// @file GameControl.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_GAMECONTROL_H__
#define __SERVEUR_GAMECONTROL_H__

#include <string>
#include <map>
#include "../../../SharedFiles/GameRoom.h"
#include "../../../SharedFiles/User.h"
#include "../../../SharedFiles/IP.h"

////////////////////////////////////////////////////////////////////////////////
/// @class GameControl
/// @brief Classe qui gère les game rooms
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class GameControl
{
public:
	// Constructeur
	GameControl();

	// Destructeur
	~GameControl();

	// Obtenir une liste de toutes les parties rejoignables
	std::vector<std::string> getAllGames(User* user);

	// Obtenir les informations actuelles de la partie rejointe
	std::vector<std::string> getGameInfo(User* user);

	// Obtenir les informations actuelles de la partie rejointe
	std::vector<std::string> getGamePlayerInfo(User* user);

	// Créer une nouvelle partie de jeu
	bool createNewGameRoom(User* host, IP* hostIP);

	// Démarre une partie
	bool startGame(User* host);

	// Joindre automatiquement une partie de jeu
	bool matchmakingJoinRoom(User* player, bool &isNewHost);

	// Joindre une partie de jeu
	bool joinGameRoom(User* player, std::string hostName, std::string password);
	
	// Quitter une partie de jeu
	bool leaveGameRoom(User* player);

	// Mettre à jour une partie à partir d'informations fournies
	bool updateGameInfo(User* host, std::string password, std::string mapname, std::string gametype, std::string temps, std::string instadeath);

	// Obtenir les informations de la dernière partie rejointe
	std::vector<std::string> rejoinGameInfo(User* player);

	// Retourne la salle de l'hôte fourni
	GameRoom* getRoom(User* host);

	// Assigne la victoire a un lobby de jeu
	void setGameWon(User* user);

	// Retourne tout les joueurs de la partie
	std::vector<User*> getAllPlayersFromGame(User* host);

private:
	/// Liste des salles de jeu actives
	std::vector<GameRoom*> gameRoomList_;

	/// Liste des dernières parties rejointes par un utilisateur
	std::map<User*, GameRoom*> lastGameJoined_;
};

#endif //__SERVEUR_GAMECONTROL_H__