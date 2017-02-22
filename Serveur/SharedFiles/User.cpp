//////////////////////////////////////////////////////////////////////////////
/// @file User.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include "User.h"
#include "Utilitaire.h"
#include "../ServeurLog3900/ServeurLog3900/SQL/Database.h"
#include <sstream>

////////////////////////////////////////////////////////////////////////
/// @fn User::User(std::string username, std::string password, std::string email)
/// @brief Constructeur qui initialise les attributs a partir des paramètres
/// @return Aucun
////////////////////////////////////////////////////////////////////////
User::User(std::string username, std::string password, std::string email)
{
	// Assurance supplémentaire de limite à 20 charactères
	if (username.length() > 20)
		userName_ = username.substr(0, 20);
	else
		userName_ = username;

	email_ = email;
	password_ = password;

	name_ = "";
	surname_ = "";
	avatar_ = "AV001";
	isPublic_ = false;
}


////////////////////////////////////////////////////////////////////////
/// @fn User::~User()
/// @brief Destructeur
/// @return Aucun
////////////////////////////////////////////////////////////////////////
User::~User()
{

}


////////////////////////////////////////////////////////////////////////
/// @fn std::string User::getUserName()
/// @brief 
/// @return 
////////////////////////////////////////////////////////////////////////
std::string User::getUserName() const
{
	return userName_;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool User::loginUser(std::string pass)
/// @brief 
/// @return 
////////////////////////////////////////////////////////////////////////
bool User::loginUser(std::string pass)
{
	if (isLogged_)
		return false;

	bool ret = (pass == password_);
	if (ret)
		isLogged_ = true;

	return ret;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool User::logoutUser()
/// @brief
/// @return
////////////////////////////////////////////////////////////////////////
bool User::logoutUser()
{
	bool ret = isLogged_;
	isLogged_ = false;
	return ret;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool User::isLogged()
/// @brief
/// @return
////////////////////////////////////////////////////////////////////////
bool User::isLogged() const
{
	return isLogged_;
}

/// Change le mot de passe de façon autoritaire
void User::setPassword(std::string pass)
{
	password_ = pass;
}

/// Retourne le couriel de l'utilisateur
std::string User::getEmail() const
{
	return email_;
}

/// Retourne les informations de base et supplémentaires
std::vector<std::string> User::getBasicInfo() const
{
	std::vector<std::string> vec;
	vec.push_back(userName_);
	vec.push_back(password_);
	vec.push_back(email_);
	vec.push_back(name_);
	vec.push_back(surname_);
	vec.push_back(std::to_string(userAge_));
	vec.push_back(std::to_string(shekels_));
	vec.push_back(avatar_);
	vec.push_back(std::to_string(isPublic_));
	vec.push_back(std::to_string(achievementPoint_));

	return vec;
}

/// Met à jour les informations de base et supplémentaires
bool User::setBasicInfo(std::vector<std::string> info)
{
	if (info.size() != 10)
		return false;

	if (info[0] == userName_)
	{
		password_ = info[1];
		email_ = info[2];
		name_ = info[3];
		surname_ = info[4];

		userAge_ = std::stoi(info[5]);
		shekels_ = std::stoi(info[6]);
		avatar_ = info[7];
		isPublic_ = (std::stoi(info[8]) == 1);
		achievementPoint_ = std::stoi(info[9]);

		return true;
	}
	return false;
}

/// Retourne la liste d'amis
std::vector<std::string> User::getFriendInfo() const
{
	return listeAmis_;
}

/// Met à jour la liste d'amis
bool User::setFriendInfo(std::vector<std::string> info)
{
	listeAmis_.clear();
	for (std::string i : info)
		listeAmis_.push_back(i);
	return true;
}

/// Retourne la liste de cartes
std::vector<std::string> User::getMapInfo() const
{
	return listeUnlockedMaps_;
}

/// Met à jour la liste de cartes
bool User::setMapInfo(std::vector<std::string> info)
{
	listeUnlockedMaps_.clear();
	for (std::string i : info)
		listeUnlockedMaps_.push_back(i);
	return true;
}

/// Ajouter un avatar débloqué
void User::addUnlockedMap(std::string map)
{
	bool isPresent = false;

	for (unsigned int i = 0; i < listeUnlockedMaps_.size(); ++i)
	{
		if (listeUnlockedMaps_[i] == map)
		{
			isPresent = true;
			break;
		}
	}

	if (!isPresent)
	{
		listeUnlockedMaps_.push_back(map);
	}
}

/// Retourne la liste de textures
std::vector<std::string> User::getAvatarUnlocked() const
{
	return listeUnlockedAvatar;
}

/// Met à jour la liste de textures
bool User::setAvatarUnlocked(std::vector<std::string> info)
{
	listeUnlockedAvatar.clear();
	listeUnlockedAvatar = info;

	return true;
}

/// Ajouter un avatar débloqué
void User::addUnlockedAvatar(std::string avatar)
{
	bool isPresent = false;

	for (unsigned int i = 0; i < listeUnlockedAvatar.size(); ++i)
	{
		if (listeUnlockedAvatar[i] == avatar)
		{
			isPresent = true;
			break;
		}
	}

	if (!isPresent)
	{
		listeUnlockedAvatar.push_back(avatar);
	}
}

/// Retourne la liste d'achievements
std::vector<std::string> User::getAchievementsInfo() const
{
	return listeAchievements_;
}

/// Met à jour la liste d'achievements
bool User::setAchievementsInfo(std::vector<std::string> info)
{
	listeAchievements_.clear();
	listeAchievements_ = info;
	return true;
}

/// Ajouter un avatar débloqué
void User::addAchievement(std::string achievement)
{
	bool isPresent = false;

	for (unsigned int i = 0; i < listeAchievements_.size(); ++i)
	{
		if (listeAchievements_[i] == achievement)
		{
			isPresent = true;
			break;
		}
	}

	if (!isPresent)
	{
		listeAchievements_.push_back(achievement);
	}
}

// Obtenir les statistiques
std::vector<std::string> User::obtenirStatistique() const
{
	std::vector<std::string> stats;

	stats.push_back(std::to_string(partiesJoues_));
	stats.push_back(std::to_string(partiesGagnes_));
	stats.push_back(std::to_string(partiesCompetitifGagne));
	stats.push_back(std::to_string(partiesCoopGagne));

	return stats;
}

/// Assigner une statistique
void User::assignerStatistique(std::vector<std::string> stats, bool writePlayedGames)
{
	if (writePlayedGames)
		partiesJoues_ = std::stoi(stats[0]);
	partiesGagnes_ = std::stoi(stats[1]);
	partiesCompetitifGagne = std::stoi(stats[2]);
	partiesCoopGagne = std::stoi(stats[3]);
}


/// Ajoute une partie jouée de plus
void User::addPlayedGame()
{
	partiesJoues_++;
}

// Ajoute une partie gagnée de plus
void User::addWonGame(bool competitif)
{
	partiesGagnes_++;
	if (competitif)
		partiesCompetitifGagne++;
	else
		partiesCoopGagne++;
}

/// Ajoute un ami selon la string. Ne fais aucune opération sur la BD
bool User::addFriend(std::string username)
{
	auto it = std::find(listeAmis_.begin(), listeAmis_.end(), username);
	if (it == listeAmis_.end())
	{
		listeAmis_.push_back(username);
		return true;
	}
	return false;
}

/// Enleve un ami
bool User::removeFriend(User* oldFriend)
{
	auto it = std::find(listeAmis_.begin(), listeAmis_.end(), oldFriend->getUserName());
	if (it != listeAmis_.end())
	{
		listeAmis_.erase(it);
		return true;
	}
	return false;
}

/// Retourne la liste des amis
std::vector<std::string> User::getFriendList() const
{
	return listeAmis_;
}