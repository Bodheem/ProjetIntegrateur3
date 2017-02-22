////////////////////////////////////////////////////////////////////////////////////
/// @file Configuration.cpp
/// @author The New Ballers
/// @date 2016-02-25
/// @version 1.0
/// @ingroup Configuration
////////////////////////////////////////////////////////////////////////////////////

#include "Configuration.h"
#include "fstream"
#include <vector>
#include <sstream>

////////////////////////////////////////////////////////////////////////
/// @fn Configuration::Configuration()
/// @brief Assigne les valeurs par defaut des attributs de classe
/// @return Aucune (constructeur).
////////////////////////////////////////////////////////////////////////
Configuration::Configuration()
{
	configurations.insert(std::make_pair(PaletteGaucheJ1, "65"));
	configurations.insert(std::make_pair(PaletteDroiteJ1, "83"));
	configurations.insert(std::make_pair(PaletteGaucheJ2, "52"));
	configurations.insert(std::make_pair(PaletteDroiteJ2, "53"));
	configurations.insert(std::make_pair(Ressort, "32"));
	configurations.insert(std::make_pair(BilleParPartie, "3"));
	configurations.insert(std::make_pair(DoubleBille, "0"));
	configurations.insert(std::make_pair(ForceRebond, "0"));
	configurations.insert(std::make_pair(GenerationBille, "0"));
	configurations.insert(std::make_pair(VitesseApresCollision, "0"));
	configurations.insert(std::make_pair(Eclairage, "0"));
	configurations.insert(std::make_pair(AttractionPortail, "0"));
	configurations.insert(std::make_pair(AffichageDebug, "0"));

	chargerConfiguration();

}


////////////////////////////////////////////////////////////////////////
/// @fn ConfigScene::~ConfigScene()
/// @brief Detruit les informations internes relatives a la configuration
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
Configuration::~Configuration()
{

}


////////////////////////////////////////////////////////////////////////
/// @fn ConfigScene::getConfigurationToString()
/// @brief Detruit les informations internes relatives a la configuration
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
std::string Configuration::getConfigurationToString() const
{
	std::stringstream ss;

	auto iter = configurations.begin();
	while (iter != configurations.end())
	{
		ss << iter->first << ":" << iter->second << "\n";
		++iter;
	}

	return ss.str();
}

////////////////////////////////////////////////////////////////////////
/// @fn ConfigScene::setConfigurationFromString()
/// @brief Detruit les informations internes relatives a la configuration
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
void Configuration::setConfigurationFromString(std::string config)
{
	// Enlever le \n de la string
	std::string temp = config;
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
		setConfiguration(details[0], details[1]);
		details.clear();
	}
}

////////////////////////////////////////////////////////////////////////
/// @fn ConfigScene:setConfiguration()
/// @brief Detruit les informations internes relatives a la configuration
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
void Configuration::setConfiguration(std::string config, std::string valeur)
{
	auto iter = configurations.find(config);
	if (iter != configurations.end())
	{
		configurations[config] = valeur;
	}
}

////////////////////////////////////////////////////////////////////////
/// @fn ConfigScene::sauvegarderConfiguration()
/// @brief Detruit les informations internes relatives a la configuration
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
void Configuration::sauvegarderConfiguration() const
{
	std::ofstream fichier;
	fichier.open(fichierConfiguration);
	fichier << getConfigurationToString();
	fichier.close();
}

////////////////////////////////////////////////////////////////////////
/// @fn ConfigScene::reinitialiserConfigurationDefaut()
/// @brief Detruit les informations internes relatives a la configuration
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
void Configuration::reinitialiserConfigurationDefaut()
{
	configurations[PaletteGaucheJ1] = "65";
	configurations[PaletteDroiteJ1] = "83";
	configurations[PaletteGaucheJ2] = "52";
	configurations[PaletteDroiteJ2] = "53";
	configurations[Ressort] = "32";
	configurations[BilleParPartie] = "3";
	configurations[DoubleBille] = "0";
	configurations[ForceRebond] = "0";
	configurations[GenerationBille] = "0";
	configurations[VitesseApresCollision] = "0";
	configurations[Eclairage] = "0";
	configurations[AttractionPortail] = "0";
	configurations[AffichageDebug] = "0";
}

////////////////////////////////////////////////////////////////////////
/// @fn ConfigScene::chargerConfiguration()
/// @brief Detruit les informations internes relatives a la configuration
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
void Configuration::chargerConfiguration()
{
	std::fstream fichier;
	fichier.open(fichierConfiguration);

	if (fichier.is_open())
	{
		std::string line = "";
		std::string delimiter = ":";
		std::vector<std::string> words(4);

		while (!fichier.eof())
		{
			std::getline(fichier, line);

			// Parser la string pour enlever le ":"
			size_t pos = 0;
			std::string token;
			while ((pos = line.find(delimiter)) != std::string::npos)
			{
				token = line.substr(0, pos);
				words.push_back(token);
				line.erase(0, pos + delimiter.length());
			}
			words.push_back(line);

			configurations[words[0]] = words[1];
			words.clear();
		}

		fichier.close();
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
