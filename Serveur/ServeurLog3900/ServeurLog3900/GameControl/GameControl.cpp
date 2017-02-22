//////////////////////////////////////////////////////////////////////////////
/// @file GameControl.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include "GameControl.h"
#include "../../../SharedFiles/GameRoom.h"
#include "sstream"

////////////////////////////////////////////////////////////////////////
/// @fn GameControl::GameControl()
/// @brief Constructeur
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
GameControl::GameControl()
{
}


////////////////////////////////////////////////////////////////////////
/// @fn GameControl::~GameControl()
/// @brief Destructeur
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
GameControl::~GameControl()
{
	while (!gameRoomList_.empty())
	{
		GameRoom* room = gameRoomList_.back();
		gameRoomList_.pop_back();
		delete room;
	}
}

// Obtenir une liste de toutes les parties rejoignables
std::vector<std::string> GameControl::getAllGames(User* user)
{
	std::vector<std::string> ret;
	for (auto room : gameRoomList_)
	{
		if (!room->isDead() && 
			(!room->isStarted() || (room->isStarted() && room->userIsPlayer(user)) )
			)
		{
			std::string info = "";
			info += room->getRoomName() + ":" + room->getMapName() + ":" + room->getGameType() 
				+ ":" + (room->isStarted() ? "G" : "L");
			ret.push_back(info);
		}
	}
	return ret;
}


// Obtenir les informations actuelles de la partie rejointe
std::vector<std::string> GameControl::getGameInfo(User* user)
{
	std::vector<std::string> ret;
	GameRoom* room = lastGameJoined_[user];
	if (room != nullptr)
	{
		ret = room->getRoomInfo();
	}
	return ret;
}

// Obtenir les informations actuelles de la partie rejointe
std::vector<std::string> GameControl::getGamePlayerInfo(User* user)
{
	std::vector<std::string> ret;
	GameRoom* room = lastGameJoined_[user];
	if (room != nullptr)
	{
		ret = room->getRoomPlayerInfo();
	}
	return ret;
}

// Mettre à jour une partie à partir d'informations fournies
bool GameControl::updateGameInfo(User* host, std::string password, 
	std::string mapname, std::string gametype, std::string temps, std::string instadeath)
{
	GameRoom* room = lastGameJoined_[host];
	if (room == nullptr)
		return false;
	try
	{
		bool insta = std::stoi(instadeath) == 1;
		room->setPassword(password);
		room->updateGameInfo(mapname, gametype, temps, insta);
		return true;
	}
	catch (std::exception ex)
	{
		return false;
	}
}

// Créer une nouvelle partie de jeu
bool GameControl::createNewGameRoom(User* host, IP* hostIP)
{
	GameRoom* room = new GameRoom(host);
	lastGameJoined_[host] = room;
	gameRoomList_.push_back(room);
	room->setHostIP(hostIP);
	return true;
}


// Démarre une partie
bool GameControl::startGame(User* host)
{
	GameRoom* room = lastGameJoined_[host];
	if (room != nullptr)
	{
		if (room->getHostName() == host->getUserName())
			return room->STARTGAME();
	}
	return false;
}

// Joindre automatiquement une partie de jeu
bool GameControl::matchmakingJoinRoom(User* player, bool &isNewHost)
{
	for (auto room : gameRoomList_)
	{
		if (room->checkPassword("") && !room->isDead())
		{
			if (room->joinRoom(player))
			{
				lastGameJoined_[player] = room;
				isNewHost = false;
				return true;
			}
		}
	}
	isNewHost = true;
	return true;
}

// Joindre une partie de jeu
bool GameControl::joinGameRoom(User* player, std::string hostName, std::string password)
{
	for (auto room : gameRoomList_)
	{
		if (room->getHostName() == hostName && room->checkPassword(password) && !room->isDead())
		{
			if (room->joinRoom(player))
			{
				lastGameJoined_[player] = room;
				return true;
			}
		}
	}
	return false;
}

// Quitter une partie de jeu
bool GameControl::leaveGameRoom(User* player)
{
	GameRoom* room = lastGameJoined_[player];
	if (room != nullptr)
	{
		return room->leaveRoom(player);
	}
	return false;
}

// Obtenir les informations de la dernière partie rejointe
std::vector<std::string> GameControl::rejoinGameInfo(User* player)
{
	std::vector<std::string> ret;
	GameRoom* room = lastGameJoined_[player];
	if (room != nullptr)
	{
		ret = room->getRoomInfo();
	}
	return ret;
}


// Retourne la salle de l'hôte fourni
GameRoom* GameControl::getRoom(User* host)
{
	GameRoom* room = lastGameJoined_[host];
	if (room != nullptr)
		return room;
	return nullptr;
}


// Assigne la victoire a un lobby de jeu
void GameControl::setGameWon(User* user)
{
	GameRoom* room = lastGameJoined_[user];
	if (room != nullptr)
		room->setGameWon();
}


// Retourne tout les joueurs de la partie
std::vector<User*> GameControl::getAllPlayersFromGame(User* host)
{
	GameRoom* room = lastGameJoined_[host];
	if (room != nullptr)
		return room->getAllUsers();
}