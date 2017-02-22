//////////////////////////////////////////////////////////////////////////////
/// @file UserControl.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include "UserControl.h"
#include "../ServerControl/ServerData.h"
#include "../../../SharedFiles/User.h"
#include "../../../SharedFiles/Utilitaire.h"
#include "sstream"
#include "../SQL/Database.h"

////////////////////////////////////////////////////////////////////////
/// @fn UserControl::UserControl()
/// @brief Constructeur
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
UserControl::UserControl()
{
	forbiddenUsernames_ = {
		"Hors-Ligne", "Admin", "Hitler", "root", "Root", "admin", "Painball"
	};
}


////////////////////////////////////////////////////////////////////////
/// @fn UserControl::~UserControl()
/// @brief Destructeur
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
UserControl::~UserControl()
{
	userList_.clear();
}


////////////////////////////////////////////////////////////////////////
/// @fn int UserControl::getNextUserID()
/// @brief Retourne le prochain user id
/// @return int.
////////////////////////////////////////////////////////////////////////
int UserControl::getNextUserID()
{
	return ++userIndex_;
}


////////////////////////////////////////////////////////////////////////
/// @fn int UserControl::createUser(std::string username, std::string password, std::string email)
/// @brief 
/// @return 
////////////////////////////////////////////////////////////////////////
bool UserControl::createUser(std::string username, std::string password, std::string email)
{
	if (std::find(forbiddenUsernames_.begin(), forbiddenUsernames_.end(), username) != forbiddenUsernames_.end())
		return false;
	auto iter = userList_.find(username);
	if (iter == userList_.end())
	{
		User* user = new User(username, password, email);
		updateFreeAvatar(*user);

		userList_.insert(std::make_pair(username, user));

		ServerData::getPointer()->chatControl_->addUserToChatRoom("General", username);
		return true;
	}

	return false;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool UserControl::loginUser(std::string username, std::string pass)
/// @brief 
/// @return 
////////////////////////////////////////////////////////////////////////
bool UserControl::loginUser(std::string username, std::string pass)
{
	auto iter = userList_.find(username);
	if (iter != userList_.end())
	{
		return userList_[username]->loginUser(pass);
	}

	return false;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool logoutUser::logoutUser(std::string username)
/// @brief 
/// @return
////////////////////////////////////////////////////////////////////////
bool UserControl::logoutUser(std::string username)
{
	auto iter = userList_.find(username);
	if (iter != userList_.end())
	{
		return userList_[username]->logoutUser();
	}

	return false;
}


////////////////////////////////////////////////////////////////////////
/// @fn User* UserControl::getUser()
/// @brief
/// @return
////////////////////////////////////////////////////////////////////////
User* UserControl::getUser(std::string username)
{
	auto iter = userList_.find(username);
	if (iter != userList_.end())
	{
		return userList_[username];
	}

	return nullptr;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool UserControl::userExists(std::string name)
/// @brief
/// @return
////////////////////////////////////////////////////////////////////////
bool UserControl::userExists(std::string name)
{
	auto iter = userList_.find(name);
	if (iter != userList_.end())
	{
		return true;
	}
	return false;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool UserControl::resetAllPasswords(std::string name)
/// @brief
/// @return
////////////////////////////////////////////////////////////////////////
void UserControl::resetAllPasswords(std::string password)
{
	for (auto user : userList_)
	{
		user.second->setPassword(password);
		updateDatabase(*(user.second));
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn User* UserControl::insertDatabase(const User& user)
/// @brief Insère une nouvelle ligne dans la table UTILISATEUR
///	@param[in] : l'objet User que l'on veut insérer
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void UserControl::insertDatabase(const User& user) const
{
	insertUserDatabase(user);
	insertStatistiqueDatabase(user);
}


////////////////////////////////////////////////////////////////////////
/// @fn User* UserControl::updateDatabase(const User& user)
/// @brief Met a jour les données de la base de données
///	@param[in] : l'objet User que l'on veut enregistrer
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void UserControl::updateDatabase(const User& user) const
{
	updateUserDatabase(user);
	updateAvatarDatabase(user);
	updateMapDatabase(user);
	updateAchievementDatabase(user);
	updateStatistiqueDatabase(user);
}


////////////////////////////////////////////////////////////////////////
/// @fn User* UserControl::updateDatabase(const User& user)
/// @brief Met a jour les données de la base de données
///	@param[in] : l'objet User que l'on veut enregistrer
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void UserControl::updateUserDatabase(const User& user) const
{
	std::vector<std::string> info = user.getBasicInfo();
	std::string baseUpdate = "UPDATE UTILISATEUR SET ";
	std::string where = " WHERE USERNAME = '";

	std::stringstream ss;

	ss << baseUpdate;

	ss << "PASSWORD = " << "'" << info[1] << "'" << ", ";
	ss << "COURRIEL = " << "'" << info[2] << "'" << ", ";
	ss << "NAME = " << "'" << info[3] << "'" << ", ";
	ss << "SURNAME = " << "'" << info[4] << "'" << ", ";
	ss << "AGE = " << info[5] << ", ";
	ss << "CASH = " << info[6] << ", ";
	ss << "AVATAR_ID = " << "'" << info[7] << "'" << ", ";
	ss << "IS_PUBLIC = " << info[8] << ", ";
	ss << "ACHIEVEMENT_POINT = " << info[9] << "";

	ss << where << info[0] << "';";

	Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());
}


////////////////////////////////////////////////////////////////////////
/// @fn User* UserControl::updateDatabase(const User& user)
/// @brief Met a jour les données de la base de données
///	@param[in] : l'objet User que l'on veut enregistrer
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void UserControl::updateAvatarDatabase(const User& user) const
{
	std::vector<std::string> avatar = user.getAvatarUnlocked();
	std::string baseSelect = "SELECT* FROM AVATAR_UNLOCKED";
	std::string where = " WHERE USER_ID = '";

	std::stringstream ss;
	ss << baseSelect << where << user.getUserName() << "';";
	std::vector<std::vector<std::string>> result;
	result = Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());

	// Garder les avatars qu'il faudra insérer dans la BD
	std::vector<std::string> avatarToInsert;
	bool isFound;

	// Regarder parmi les avatar unlocked, ceux qui ne sont pas présents dans la base de données
	for (unsigned int i = 0; i < avatar.size(); ++i)
	{
		isFound = false;
		for (unsigned int j = 1; j < result.size(); ++j)
		{
			// L'index 0 correspond au AVATAR_ID
			if (avatar[i] == result[j][0])
			{
				isFound = true;
			}
		}
		if (!isFound)
		{
			avatarToInsert.push_back(avatar[i]);
		}
	}

	// Insertion
	std::string baseInsert = "INSERT INTO AVATAR_UNLOCKED VALUES (";
	for (unsigned int k = 0; k < avatarToInsert.size(); ++k)
	{
		ss.str(std::string());
		ss.clear();
		ss << baseInsert << "'" << avatarToInsert[k] << "', " << "'" << user.getUserName() << "');";
		Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn User* UserControl::updateDatabase(const User& user)
/// @brief Met a jour les données de la base de données
///	@param[in] : l'objet User que l'on veut enregistrer
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void UserControl::updateMapDatabase(const User& user) const
{
	std::vector<std::string> map = user.getMapInfo();
	std::string baseSelect = "SELECT* FROM MAP_UNLOCKED";
	std::string where = " WHERE USER_ID = '";

	std::stringstream ss;
	ss << baseSelect << where << user.getUserName() << "';";
	std::vector<std::vector<std::string>> result;
	result = Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());

	// Garder les avatars qu'il faudra insérer dans la BD
	std::vector<std::string> mapToInsert;
	bool isFound;

	// Regarder parmi les avatar unlocked, ceux qui ne sont pas présents dans la base de données
	for (unsigned int i = 0; i < map.size(); ++i)
	{
		isFound = false;
		for (unsigned int j = 1; j < result.size(); ++j)
		{
			// L'index 0 correspond au ACHIEVEMENT_ID
			if (map[i] == result[j][0])
			{
				isFound = true;
			}
		}
		if (!isFound)
		{
			mapToInsert.push_back(map[i]);
		}
	}

	// Insertion
	std::string baseInsert = "INSERT INTO MAP_UNLOCKED VALUES (";
	for (unsigned int k = 0; k < mapToInsert.size(); ++k)
	{
		ss.str(std::string());
		ss.clear();

		ss << baseInsert << "'" << mapToInsert[k] << "', " << "'" << user.getUserName() << "');";
		Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn User* UserControl::updateDatabase(const User& user)
/// @brief Met a jour les données de la base de données
///	@param[in] : l'objet User que l'on veut enregistrer
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void UserControl::updateAchievementDatabase(const User& user) const
{
	std::vector<std::string> achievement = user.getAchievementsInfo();
	std::string baseSelect = "SELECT* FROM ACHIEVEMENT_UNLOCKED";
	std::string where = " WHERE USER_ID = '";

	std::stringstream ss;
	ss << baseSelect << where << user.getUserName() << "';";
	std::vector<std::vector<std::string>> result;
	result = Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());

	// Garder les avatars qu'il faudra insérer dans la BD
	std::vector<std::string> achievementToInsert;
	bool isFound;

	// Regarder parmi les avatar unlocked, ceux qui ne sont pas présents dans la base de données
	for (unsigned int i = 0; i < achievement.size(); ++i)
	{
		isFound = false;
		for (unsigned int j = 1; j < result.size(); ++j)
		{
			// L'index 0 correspond au ACHIEVEMENT_ID
			if (achievement[i] == result[j][0])
			{
				isFound = true;
			}
		}
		if (!isFound)
		{
			achievementToInsert.push_back(achievement[i]);
		}
	}

	// Insertion
	std::string baseInsert = "INSERT INTO ACHIEVEMENT_UNLOCKED VALUES (";
	for (unsigned int k = 0; k < achievementToInsert.size(); ++k)
	{
		ss.str(std::string());
		ss.clear();

		ss << baseInsert << "'" << achievementToInsert[k] << "', " << "'" << user.getUserName() << "');";
		Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn User* UserControl::updateFreeAvatar(const User& user)
/// @brief 
///	@param[in] : l'objet User que l'on veut enregistrer
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void UserControl::updateFreeAvatar(User& user) const
{
	// Récupérer les avatar gratuits
	std::string baseSelect = "SELECT ID FROM AVATAR WHERE VALUE = 0;";
	std::stringstream ss;
	ss << baseSelect;

	std::vector<std::vector<std::string>> result;
	result = Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());

	// Ajouter les avatars au compte
	for (unsigned int i = 1; i < result.size(); ++i)
	{
		user.addUnlockedAvatar(result[i][0]);
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn User* UserControl::updateFreeAvatar(const User& user)
/// @brief 
///	@param[in] : l'objet User que l'on veut enregistrer
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void  UserControl::updateStatistiqueDatabase(const User& user) const
{
	std::vector<std::string> stats = user.obtenirStatistique();
	std::string baseUpdate = "UPDATE STATISTIQUES SET ";
	std::string where = " WHERE USER_ID = '";

	std::stringstream ss;

	ss << baseUpdate;

	ss << "GAMES_PLAYED = " << stats[0] << ", ";
	ss << "GAMES_WON = " << stats[1] << ", ";
	ss << "GAMES_COMP_WON = " << stats[2] << ", ";
	ss << "GAMES_COOP_WON = " << stats[3];

	ss << where << user.getUserName() << "';";

	Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());
}


////////////////////////////////////////////////////////////////////////
/// @fn User* UserControl::insertUserDatabase(const User& user)
/// @brief 
///	@param[in] : l'objet User que l'on veut enregistrer
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void UserControl::insertUserDatabase(const User& user) const
{
	std::vector<std::string> info = user.getBasicInfo();
	std::string baseInsert = "INSERT INTO UTILISATEUR VALUES (";
	std::stringstream ss;

	ss << baseInsert;

	/// Username, password et courriel
	ss << "'" << info[0] << "'" << ", " << "'" << info[1] << "'" << ", " << "'" << info[2] << "'" << ", ";

	// Name, peut etre vide
	if (info[3] == "")
		ss << "''" << ", ";
	else
		ss << "'" << info[3] << "'" << ", ";

	/// Surname, peut être vide
	if (info[4] == "")
		ss << "''" << ", ";
	else
		ss << "'" << info[4] << "'" << ", ";

	/// Age et shekels
	ss << info[5] << ", " << info[6] << ", ";

	/// Avatar, public
	ss << "'" << info[7] << "'" << ", " << info[8] << ", " << info[9] << ");";

	/// Execute insert SQL
	Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());
}


////////////////////////////////////////////////////////////////////////
/// @fn User* UserControl::insertStatistiqueDatabase(const User& user)
/// @brief 
///	@param[in] : l'objet User que l'on veut enregistrer
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void UserControl::insertStatistiqueDatabase(const User& user) const
{
	std::vector<std::string> stat = user.obtenirStatistique();
	std::string baseInsert = "INSERT INTO STATISTIQUES VALUES (";
	std::stringstream ss;

	ss << baseInsert;

	/// Username, password et courriel
	ss << "'" << user.getUserName() << "'" << stat[0] << ", " << stat[1] << ", " << stat[2] << ", " << stat[3] << "); ";

	/// Execute insert SQL
	Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());
}
