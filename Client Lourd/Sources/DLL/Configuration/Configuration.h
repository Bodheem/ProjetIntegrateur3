//////////////////////////////////////////////////////////////////////////////
/// @file Configuration.h
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
/// @ingroup Configuration
//////////////////////////////////////////////////////////////////////////////
#ifndef __CONFIGURATION_CONFIGURATION_H__
#define __CONFIGURATION_CONFIGURATION_H__

#include <string>
#include <map>

///////////////////////////////////////////////////////////////////////////
/// @class Configuration
/// @brief Les variables de configuration de la classe CScene.
/// @author The Ballers
/// @date 2015-02-25
///////////////////////////////////////////////////////////////////////////
class Configuration
{

public:

	// Constructeur
	Configuration();

	// Destructeur
	~Configuration();

	// Obtenir la liste des configurations comme une chaine de caratères
	std::string getConfigurationToString() const;

	// Assigner la liste des configurations à partir d'une string
	void setConfigurationFromString(std::string config);

	// Assigner une configuration à une valeur
	void setConfiguration(std::string config, std::string value);

	// Sauvegarder les configuration
	void sauvegarderConfiguration() const;

	// Remettre les configurations aux valeurs par défaut
	void reinitialiserConfigurationDefaut();


	// Obtenir la liste de dernière campagne comme une chaine de caratères
	std::string GetCampagneToString() const;

	// Assigner la liste des configurations
	void SetCampagneFromString(std::string campagne);

	// Sauvegarder les informations de campagne
	void sauvegarderCampagne() const;

private:

	// À la construction, lire les fichier et charger les configurations
	void chargerConfiguration();
	void chargerCampagne();

	const std::string fichierConfiguration = "config.txt";
	const std::string fichierCampagne = "campagne.txt";

	// Configurations possibles
	const std::string PaletteGaucheJ1 = "PaletteGaucheJ1";
	const std::string PaletteDroiteJ1 = "PaletteDroiteJ1";
	const std::string PaletteGaucheJ2 = "PaletteGaucheJ2";
	const std::string PaletteDroiteJ2 = "PaletteDroiteJ2";
	const std::string Ressort = "Ressort";
	const std::string BilleParPartie = "BilleParPartie";
	const std::string DoubleBille = "DoubleBille";
	const std::string ForceRebond = "ForceRebond";
	const std::string GenerationBille = "GenerationBille";
	const std::string VitesseApresCollision = "VitesseApresCollision";
	const std::string Eclairage = "Eclairage";
	const std::string AttractionPortail = "AttractionPortail";
	const std::string AffichageDebug = "AffichageDebug";

	std::map<std::string, std::string> configurations;

};


#endif // __CONFIGURATION_CONFIGURATION_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
