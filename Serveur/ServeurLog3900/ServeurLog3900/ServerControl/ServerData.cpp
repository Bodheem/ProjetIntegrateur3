//////////////////////////////////////////////////////////////////////////////
/// @file ServerData.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include <mutex>
#include "ServerData.h"
#include "../SQL/Database.h"
#include "../../../SharedFiles/Utilitaire.h"

// Initialize Static pointer
ServerData* ServerData::ServerDataPointer = nullptr;

// Static function to obtain pointer to main form
ServerData* ServerData::getPointer()
{
	if (ServerDataPointer == nullptr)
		ServerDataPointer = new ServerData();
	return ServerDataPointer;
}

/// Constructeur
ServerData::ServerData()
{
	chatControl_ = new ChatControl();
	userControl_ = new UserControl();
	gameControl_ = new GameControl();
	chatControl_->createChatRoom("General");
	ServerDataPointer = this;
}

/// Destructeur
ServerData::~ServerData()
{
	delete gameControl_;
	delete userControl_;
	delete chatControl_;
}

/// Retourne le prochain ID de message de chat
int ServerData::getNextMessageID() const
{
	return chatControl_->getNextMessageID();
}


/// Retourne le prochain ID d'utilisateur
int ServerData::getNextUserID() const
{
	return userControl_->getNextUserID();
}


/// Charge toutes les informations de la mémoire / DB
void ServerData::loadMemory() const
{
	retrieveUser();
	retrieveFriends();
	retrieveStats();
	retrieveAvatar();
	retrieveAchievement();
	retrieveMap();
}

////////////////////////////////////////////////////////////////////////
/// @fn void ServerData::retrieveUser()
/// @brief Récupère tous les utilisateurs de la base de données
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void ServerData::retrieveUser() const
{
	std::string fileName = "../../Database/PainBall.db";

	// Récupérer tous les utilisateurs de la base de données
	std::vector<std::vector<std::string> > result;
	char* select = "SELECT* FROM UTILISATEUR";
	result = Database::executeQuery(fileName, select);

	// La premiere ligne contient toujours les informations de colonnes
	for (unsigned int i = 1; i < result.size(); ++i)
	{
		/// Username, Password, E-Mail
		userControl_->createUser(result[i][0], result[i][1], result[i][2]);

		/// Assigner les autres informations du compte
		userControl_->getUser(result[i][0])->setBasicInfo(result[i]);
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn void ServerData::retrieveUser()
/// @brief Récupère tous les utilisateurs de la base de données
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void ServerData::retrieveFriends() const
{
	std::string fileName = "../../Database/PainBall.db";

	// Récupérer tous les avatar débloqués de la base de données
	char* request = "SELECT* FROM FRIENDLIST;";
	std::vector<std::vector<std::string> > friends;
	friends = Database::executeQuery(fileName, request);
	User* user = nullptr;

	for (unsigned int i = 1; i < friends.size(); ++i)
	{
		std::string username = friends[i][0];
		user = userControl_->getUser(username);

		if (user != nullptr)
		{
			std::string amis = friends[i][1];
			user->addFriend(amis);
		}
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn void ServerData::()
/// @brief Récupère tous les avatars débloqués de la base de données
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void ServerData::retrieveAvatar() const
{
	std::string fileName = "../../Database/PainBall.db";

	// Récupérer tous les avatar débloqués de la base de données
	char* request =  "SELECT* FROM AVATAR_UNLOCKED;";
	std::vector<std::vector<std::string> > avatarUnlocked;
	avatarUnlocked = Database::executeQuery(fileName, request);

	for (unsigned int i = 1; i < avatarUnlocked.size(); ++i)
	{
		std::string username = avatarUnlocked[i][1];
		userControl_->getUser(username)->addUnlockedAvatar(avatarUnlocked[i][0]);
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn void ServerData::()
/// @brief Récupère tous les avatars débloqués de la base de données
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void ServerData::retrieveAchievement() const
{
	std::string fileName = "../../Database/PainBall.db";

	// Récupérer tous les avatar débloqués de la base de données
	char* request = "SELECT* FROM ACHIEVEMENT_UNLOCKED;";
	std::vector<std::vector<std::string> > achievementUnlocked;
	achievementUnlocked = Database::executeQuery(fileName, request);
	User* user = nullptr;

	for (unsigned int i = 1; i < achievementUnlocked.size(); ++i)
	{
		std::string username = achievementUnlocked[i][1];
		user = userControl_->getUser(username);

		if (user != nullptr)
		{
			user->addAchievement(achievementUnlocked[i][0]);
		}
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn void ServerData::()
/// @brief Récupère tous les avatars débloqués de la base de données
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void ServerData::retrieveMap() const
{
	std::string fileName = "../../Database/PainBall.db";

	// Récupérer tous les avatar débloqués de la base de données
	char* request = "SELECT* FROM MAP_UNLOCKED;";
	std::vector<std::vector<std::string> > mapUnlocked;
	mapUnlocked = Database::executeQuery(fileName, request);
	User* user = nullptr;

	for (unsigned int i = 1; i < mapUnlocked.size(); ++i)
	{
		std::string username = mapUnlocked[i][1];
		user = userControl_->getUser(username);

		if (user != nullptr)
		{
			user->addUnlockedMap(mapUnlocked[i][0]);
		}
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn void ServerData::()
/// @brief Récupère tous les avatars débloqués de la base de données
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void ServerData::retrieveStats() const
{
	std::string fileName = "../../Database/PainBall.db";

	// Récupérer tous les avatar débloqués de la base de données
	char* request = "SELECT* FROM STATISTIQUES;";
	std::vector<std::vector<std::string> > stats;
	stats = Database::executeQuery(fileName, request);
	User* user = nullptr;

	for (unsigned int i = 1; i < stats.size(); ++i)
	{
		std::string username = stats[i][0];
		user = userControl_->getUser(username);

		if (user != nullptr)
		{
			std::vector<std::string> stat;
			stat.push_back(stats[i][1]);
			stat.push_back(stats[i][2]);
			stat.push_back(stats[i][3]);
			stat.push_back(stats[i][4]);

			user->assignerStatistique(stat, true);
		}
	}
}