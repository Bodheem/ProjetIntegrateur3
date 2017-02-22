//////////////////////////////////////////////////////////////////////////////
/// @file GameRoom.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////


#include "GameRoom.h"

// Constructeur
GameRoom::GameRoom(User* host)
{
	host_ = host;
}

// Constructeur pour client
GameRoom::GameRoom(bool isHost, User* host)
{
	if (isHost)
		host_ = host;
	else
		host_ = host;
}

// Destructeur
GameRoom::~GameRoom()
{
}

// Retourne le nom de l'hote
std::string GameRoom::getHostName()
{
	return host_->getUserName();
}


// Démarre une partie
bool GameRoom::STARTGAME()
{
	if (player2_ != nullptr && readyPlayer2_ || player2_ == nullptr)
		if (player3_ != nullptr && readyPlayer3_ || player3_ == nullptr)
			if (player4_ != nullptr && readyPlayer4_ || player4_ == nullptr)
				GAMESTARTED = true;
	if (GAMESTARTED)
	{
		host_->addPlayedGame();
		if (player2_ != nullptr)
			player2_->addPlayedGame();
		if (player3_ != nullptr)
			player3_->addPlayedGame();
		if (player4_ != nullptr)
			player4_->addPlayedGame();
	}
	return GAMESTARTED;
}


// Retourne l'état de la game
bool GameRoom::isDead()
{
	return GAMEDEAD;
}

// Retourne l'état de la game
bool GameRoom::isStarted()
{
	return GAMESTARTED;
}

// Ajout d'un joueur
bool GameRoom::joinRoom(User* player)
{
	if (GAMEDEAD)
		return false;
	if (GAMESTARTED && userIsPlayer(player))
		return true;
	if (GAMESTARTED && !userIsPlayer(player))
		return false;
	if (player2_ == nullptr || player2_ == player)
	{
		player2_ = player;
		return true;
	}
	if (player3_ == nullptr || player3_ == player)
	{
		player3_ = player;
		return true;
	}
	if (player4_ == nullptr || player4_ == player)
	{
		player4_ = player;
		return true;
	}
	return false;
}

// Retrait d'un joueur
bool GameRoom::leaveRoom(User* player)
{
	if (host_ == player)
	{
		GAMEDEAD = true;
		return true;
	}
	if (GAMESTARTED || GAMEDEAD)
		return true;
	if (player2_ == player)
	{
		readyPlayer2_ = readyPlayer3_;
		readyPlayer3_ = readyPlayer4_;
		readyPlayer4_ = false;
		player2_ = player3_;
		player3_ = player4_;
		player4_ = nullptr;
		return true;
	}
	if (player3_ == player)
	{
		readyPlayer3_ = readyPlayer4_;
		readyPlayer4_ = false;
		player3_ = player4_;
		player4_ = nullptr;
		return true;
	}
	if (player4_ == player)
	{
		readyPlayer4_ = false;
		player4_ = nullptr;
		return true;
	}
	return false;
}


// Modification du mot de passe
bool GameRoom::setPassword(std::string password)
{
	if (GAMESTARTED || GAMEDEAD)
		return false;
	password_ = password;
	return true;
}

// Verification du mot de passe
bool GameRoom::checkPassword(std::string password)
{
	if (GAMEDEAD)
		return false;
	return password == password_;
}


// Ajoute un joueur dans un slot, POUR LOCAL SEULEMENT
void GameRoom::addPlayerToSlot(User* user, int slot)
{
	switch (slot)
	{
	case 2:
		player2_ = user;
	case 3:
		player3_ = user;
	case 4:
		player4_ = user;
	default:
		;
	}
}

// Obtenir le nom de la salle de jeu
std::string GameRoom::getRoomName()
{
	return host_->getUserName();
}

// Obtenir le nom de la carte
std::string GameRoom::getMapName()
{
	return mapName_;
}

// Obtenir le type de jeu
std::string GameRoom::getGameType()
{
	return gameType_;
}

// Retourne le numéro d'un joueur
int GameRoom::getPlayerNumber(User* user)
{
	if (host_ == user)
		return 1;
	if (player2_ == user)
		return 2;
	if (player3_ == user)
		return 3;
	if (player4_ == user)
		return 4;
	return -1;
}

// Retourne le numéro d'un joueur
int GameRoom::getPlayerNumber(std::string user)
{
	if (host_->getUserName() == user)
		return 1;
	if (player2_->getUserName() == user)
		return 2;
	if (player3_->getUserName() == user)
		return 3;
	if (player4_->getUserName() == user)
		return 4;
	return -1;
}

// Obtenir les informations de la salle
std::vector<std::string> GameRoom::getRoomInfo()
{
	std::vector<std::string> ret;
	ret.push_back(host_->getUserName());
	ret.push_back(password_);
	ret.push_back(mapName_);
	ret.push_back(gameType_);
	ret.push_back(std::to_string(temps_));
	ret.push_back(std::to_string(instaDeath_));
	ret.push_back(GAMESTARTED ? "YES" : "NO");
	return ret;
}


// Retourne le nombre de joueurs dans la partie
int GameRoom::getNumberOfPlayers()
{
	int i = 1;
	if (player2_ != nullptr && player2_->getUserName() != "PLAYER2")
		i++;
	if (player3_ != nullptr && player3_->getUserName() != "PLAYER3")
		i++;
	if (player4_ != nullptr && player4_->getUserName() != "PLAYER4")
		i++;
	return i;
}

// Obtenir les informations de la salle
std::vector<std::string> GameRoom::getRoomPlayerInfo()
{
	std::vector<std::string> ret;
	std::string ret1 = (GAMEDEAD ? "DEAD" : host_->getUserName()) 
		+ ":" + (GAMEDEAD ? "DEAD" : "RDY");
	std::string ret2 = (player2_ != nullptr ? player2_->getUserName() : "PLAYER2") 
		+ ":" + (player2_ != nullptr ? (readyPlayer2_ ? "RDY" : "NOT") : "EMPTY");
	std::string ret3 = (player3_ != nullptr ? player3_->getUserName() : "PLAYER3") 
		+ ":" + (player3_ != nullptr ? (readyPlayer3_ ? "RDY" : "NOT") : "EMPTY");
	std::string ret4 = (player4_ != nullptr ? player4_->getUserName() : "PLAYER4") 
		+ ":" + (player4_ != nullptr ? (readyPlayer4_ ? "RDY" : "NOT") : "EMPTY");
	ret.push_back(ret1);
	ret.push_back(ret2);
	ret.push_back(ret3);
	ret.push_back(ret4);
	ret.push_back(GAMESTARTED ? "YES" : "NO");
	ret.push_back(hostIP_->getStringIP());
	return ret;
}


// Set le IP de l'hote
void GameRoom::setHostIP(IP* hostIP)
{
	delete hostIP_;	
	hostIP_ = hostIP;
}

// Retourne l'IP de l'hote
IP* GameRoom::getHostIP()
{
	return hostIP_;
}

// Mise à jour des informations
bool GameRoom::updateGameInfo(std::string map, std::string info, std::string temps, bool instadeath)
{
	if (GAMESTARTED || GAMEDEAD)
		return false;
	mapName_ = map;
	gameType_ = info;
	instaDeath_ = instadeath;
	try
	{
		temps_ = stoi(temps);
	}
	catch (std::exception ex)
	{
		temps_ = -1;
		return false;
	}
	return true;
}

// Met le joueur à l'état fourni
bool GameRoom::setPlayerReady(User* user, bool state)
{
	if (GAMESTARTED || GAMEDEAD)
		return false;
	if (player2_ == user)
	{
		readyPlayer2_ = state;
		return true;
	}
	if (player3_ == user)
	{
		readyPlayer3_ = state;
		return true;
	}
	if (player4_ == user)
	{
		readyPlayer4_ = state;
		return true;
	}
	return false;
}


// Retourne true si l'user est dans la partie
bool GameRoom::userIsPlayer(User* user)
{
	if (host_ == user)
	{
		return true;
	}
	if (player2_ == user)
	{
		return true;
	}
	if (player3_ == user)
	{
		return true;
	}
	if (player4_ == user)
	{
		return true;
	}
	return false;
}


// Donne une victoire aux joueurs
void GameRoom::setGameWon()
{
	bool competitif = gameType_ == "2" ? true : false;
	host_->addWonGame(competitif);
	if (player2_ != nullptr)
	{
		player2_->addWonGame(competitif);
	}
	if (player3_ != nullptr)
	{
		player2_->addWonGame(competitif);
	}
	if (player4_ != nullptr)
	{
		player2_->addWonGame(competitif);
	}

}


// Retourne tout les joueurs
std::vector<User*> GameRoom::getAllUsers()
{
	std::vector<User*> ret;
	ret.push_back(host_);
	if (player2_ != nullptr)
	{
		ret.push_back(player2_);
	}
	if (player3_ != nullptr)
	{
		ret.push_back(player3_);
	}
	if (player4_ != nullptr)
	{
		ret.push_back(player4_);
	}
	return ret;
}