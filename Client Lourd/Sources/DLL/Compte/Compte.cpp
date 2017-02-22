
#include <sstream>
#include <vector>

#include "Compte.h"
#include "Informations/InfoCompte.h"
#include "../../../../Serveur/SharedFiles/User.h"

////////////////////////////////////////////////////////////////////////
/// @fn Compte::Compte()
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
Compte::Compte(User* user)
{
	std::vector<std::string> info = user->getBasicInfo();
	std::vector<std::string> stat = user->obtenirStatistique();
	
	avatarUnlocked_ = user->getAvatarUnlocked();
	achievementUnlocked_ = user->getAchievementsInfo();
	mapUnlocked_ = user->getMapInfo();

	// Informations de compte
	username_ = info[0];
	password_ = info[1];
	courriel_ = info[2];
	name_ = info[3];
	surname_ = info[4];
	achievementPoint_ = std::stoi(info[9]);
	age_ = std::stoi(info[5]);
	shekels_ = std::stoi(info[6]);
	avatar_ = info[7];
	isPublic_ = (std::stoi(info[8]) == 1);

	// Statistiques
	partiesJoues_ = stoi(stat[0]);
	partiesGagnes_ = stoi(stat[1]);
	partiesCompetitifGagne = stoi(stat[2]);
	partiesCoopGagne = stoi(stat[3]);

	isOnline_ = true;
}


////////////////////////////////////////////////////////////////////////
/// @fn Compte::~Compte()
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
Compte::~Compte()
{
	
}


////////////////////////////////////////////////////////////////////////
/// @fn Compte::getAllInformations()
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
std::string Compte::getAllInformations() const
{
	std::stringstream ss;

	ss << InfoCompte::USERNAME << ":" << username_ << "\n";
	ss << InfoCompte::PASSWORD << ":" << password_ << "\n";
	ss << InfoCompte::COURRIEL << ":" << courriel_ << "\n";
	ss << InfoCompte::NAME << ":" << name_ << "\n";
	ss << InfoCompte::SURNAME << ":" << surname_ << "\n";
	ss << InfoCompte::AGE << ":" << age_ << "\n";
	ss << InfoCompte::AVATAR << ":" << avatar_ << "\n";
	ss << InfoCompte::IS_PUBLIC << ":" << isPublic_ << "\n";

	if (avatarUnlocked_.size() > 0)
	{
		ss << InfoCompte::AVATAR_UNLOCKED << ":" << avatarUnlocked_[0];

		for (unsigned int i = 1; i < avatarUnlocked_.size(); ++i)
			ss << "," << avatarUnlocked_[i];

		ss << "\n";
	}

	if(mapUnlocked_.size() > 0)
	{
		ss << InfoCompte::MAP_UNLOCKED << ":" << mapUnlocked_[0];

		for (unsigned int i = 1; i < mapUnlocked_.size(); ++i)
			ss << "," << mapUnlocked_[i];

		ss << "\n";
	}

	if (achievementUnlocked_.size() > 0)
	{
		ss << InfoCompte::ACHIEVEMENT_UNLOCKED << ":" << achievementUnlocked_[0];

		for (unsigned int i = 1; i < achievementUnlocked_.size(); ++i)
		{
			ss << "," << achievementUnlocked_[i];
		}

		ss << "\n";
	}
	
	ss << InfoCompte::GAMES_PLAYED << ":" << partiesJoues_ << "\n";
	ss << InfoCompte::GAMES_WON << ":" << partiesGagnes_ << "\n";
	ss << InfoCompte::GAMES_COMP_WON << ":" << partiesCompetitifGagne << "\n";
	ss << InfoCompte::GAMES_COOP_WON << ":" << partiesCoopGagne << "\n";


	ss << InfoCompte::SHEKELS << ":" << shekels_ << "\n";
	ss << InfoCompte::ACHIEVEMENT_POINT << ":" << achievementPoint_;

	return ss.str();
}


////////////////////////////////////////////////////////////////////////
/// @fn Compte::getAllInformations()
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
std::vector<std::string> Compte::getInformationsToVector() const
{
	std::vector<std::string> vec;
	vec.push_back(username_);
	vec.push_back(password_);
	vec.push_back(courriel_);
	vec.push_back(name_);
	vec.push_back(surname_);
	vec.push_back(std::to_string(age_));
	vec.push_back(std::to_string(shekels_));
	vec.push_back(avatar_);
	vec.push_back(std::to_string(isPublic_));
	vec.push_back(std::to_string(achievementPoint_));

	return vec;
}


////////////////////////////////////////////////////////////////////////
/// @fn Compte::getAllInformations()
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
std::vector<std::string> Compte::getAvatarUnlocked() const
{
	return avatarUnlocked_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void Compte::setInformation(std::string infoType) const
/// @brief
/// @return
////////////////////////////////////////////////////////////////////////
void Compte::setInformationFromString(std::string info)
{
	// Enlever le \n de la string
	std::string temp = info;
	std::string delimiter = "\r\n";
	std::vector<std::string> words;

	size_t pos = 0;
	std::string token;
	while ((pos = temp.find(delimiter)) != std::string::npos)
	{
		token = temp.substr(0, pos);
		words.push_back(token);
		temp.erase(0, pos + delimiter.length());
	}
	words.push_back(temp);


	// Extraire les données
	delimiter = ":";
	std::vector<std::string> details;

	for (unsigned int i = 0; i < words.size(); i++)
	{
		size_t position = 0;
		std::string detail;
		while ((position = words[i].find(delimiter)) != std::string::npos)
		{
			detail = words[i].substr(0, position);
			details.push_back(detail);
			words[i].erase(0, position + delimiter.length());
		}
		details.push_back(words[i]);


		setInformation(details[0], details[1]);
		details.clear();
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn Compte::setInformation(std::string infoType, std::string value)
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void Compte::setInformation(std::string infoType, std::string value)
{
	if (infoType == InfoCompte::COURRIEL)
		courriel_ = value;

	else if (infoType == InfoCompte::NAME)
		name_ = value;

	else if (infoType == InfoCompte::SURNAME)
		surname_ = value;

	else if (infoType == InfoCompte::PASSWORD)
		password_ = value;

	else if (infoType == InfoCompte::IS_PUBLIC)
		isPublic_ = (std::stoi(value) == 1);

	else if (infoType == InfoCompte::AGE)
		age_ = std::stoi(value);

	else if (infoType == InfoCompte::AVATAR)
		avatar_ = value;

	else if (infoType == InfoCompte::SHEKELS)
		shekels_ = std::stoi(value);

	else if (infoType == InfoCompte::AVATAR_UNLOCKED)
	{
		avatarUnlocked_.clear();
		std::stringstream ss(value); // Turn the string into a stream.
		std::string tok;
		while (std::getline(ss, tok, ',')) 
		{
			avatarUnlocked_.push_back(tok);
		}
	}

	else if (infoType == InfoCompte::ACHIEVEMENT_UNLOCKED)
	{
		achievementUnlocked_.clear();
		std::stringstream ss(value); // Turn the string into a stream.
		std::string tok;
		while (std::getline(ss, tok, ','))
		{
			achievementUnlocked_.push_back(tok);
		}
	}

	else if (infoType == InfoCompte::MAP_UNLOCKED)
	{
		mapUnlocked_.clear();
		std::stringstream ss(value); // Turn the string into a stream.
		std::string tok;
		while (std::getline(ss, tok, ','))
		{
			mapUnlocked_.push_back(tok);
		}
	}

	else if (infoType == InfoCompte::GAMES_PLAYED)
		partiesJoues_ = std::stoi(value);

	else if (infoType == InfoCompte::GAMES_WON)
		partiesGagnes_ = std::stoi(value);

	else if (infoType == InfoCompte::GAMES_COMP_WON)
		partiesCompetitifGagne = std::stoi(value);

	else if (infoType == InfoCompte::GAMES_COOP_WON)
		partiesCoopGagne = std::stoi(value);
}


////////////////////////////////////////////////////////////////////////
/// @fn Compte::()
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
std::vector<std::string> Compte::getAchievementUnlocked() const
{
	return achievementUnlocked_;
}


////////////////////////////////////////////////////////////////////////
/// @fn Compte::()
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
std::vector<std::string> Compte::getMapUnlocked() const
{
	return mapUnlocked_;
}


////////////////////////////////////////////////////////////////////////
/// @fn Compte::()
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
std::vector<std::string> Compte::obtenirStatistique() const
{
	std::vector<std::string> stats;

	stats.push_back(std::to_string(partiesJoues_));
	stats.push_back(std::to_string(partiesGagnes_));
	stats.push_back(std::to_string(partiesCompetitifGagne));
	stats.push_back(std::to_string(partiesCoopGagne));

	return stats;
}


////////////////////////////////////////////////////////////////////////
/// @fn Compte::()
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void Compte::assignerStatistique(std::vector<std::string> stats)
{
	partiesJoues_ = std::stoi(stats[0]);
	partiesGagnes_ = std::stoi(stats[1]);
	partiesCompetitifGagne = std::stoi(stats[2]);
	partiesCoopGagne = std::stoi(stats[3]);
}