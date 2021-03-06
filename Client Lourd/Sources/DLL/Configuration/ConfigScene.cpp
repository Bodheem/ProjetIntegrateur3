////////////////////////////////////////////////////////////////////////////////////
/// @file ConfigScene.cpp
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
/// @ingroup Configuration
////////////////////////////////////////////////////////////////////////////////////

#include "ConfigScene.h"
#include <fstream>
#include <sstream>

////////////////////////////////////////////////////////////////////////
/// @fn ConfigScene::ConfigScene()
/// @brief Assigne les valeurs par defaut des attributs de classe
/// @return Aucune (constructeur).
////////////////////////////////////////////////////////////////////////
ConfigScene::ConfigScene() : derniereConfiguration_("lastConfig.bin"), derniereCampagne_("lastCampaign.txt")
{
	config_ = new int[14];
	lireConfiguration();
	lireCampagne();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ConfigScene::~ConfigScene()
///
/// Detruit les informations internes relatives a la configuration
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ConfigScene::~ConfigScene()
{
	delete[] config_;
	listeCartes_.clear();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::sauvegarderConfiguration()
///
/// Cette fonction ecrit les valeurs de la configuration dans un fichier binaire.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::sauvegarderConfiguration()
{
	std::fstream fichier;
	fichier.open(derniereConfiguration_, std::ios::out | std::ios::binary);

	for (int i = 0; i < 14; i++)
		fichier.write((char*)&config_[i], sizeof(int));

	fichier.close();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::sauvegarderCampagne()
///
/// Cette fonction ecrit les valeurs de la derniere campagne dans un fichier texte.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::sauvegarderCampagne()
{
	std::ofstream fichier;
	fichier.open(derniereCampagne_);

	unsigned int i = 0;

	for (i = 0; i < listeCartes_.size(); i++)
		fichier << listeCartes_[i] << std::endl;

	fichier.close();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool ConfigScene::lireConfiguration()
///
/// Cette fonction lit les valeurs de la configuration de la derniere
/// configuration de jeu.
///
/// @return True pour indiquer que la lecture s'est bien faite. False autrement
///
////////////////////////////////////////////////////////////////////////
bool ConfigScene::lireConfiguration()
{
	//bool lectureOK = false;

	lireFichierBinaire();
	//lectureOK = true;
	
	return true; //lectureOK;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool ConfigScene::lireCampagne()
///
/// Cette fonction lit les valeurs de la configuration de la derniere
/// campagne.
///
/// @return True pour indiquer que la lecture s'est bien faite. False autrement
///
////////////////////////////////////////////////////////////////////////
bool ConfigScene::lireCampagne()
{
	bool lectureOK = false;
	std::ifstream lecture;
	std::string nomCarte;

	lecture.open(derniereCampagne_);

	if (!lecture.fail())
	{
		while (lecture >> nomCarte)
			listeCartes_.push_back(nomCarte);

		lectureOK = true;
	}
	
	return lectureOK;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::lireFichierBinaire()
///
/// Cette fonction lit les valeurs de la configuration a partir d'un fichier binaire.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::lireFichierBinaire()
{
	std::fstream fichier;
	fichier.open(derniereConfiguration_, std::ios::in | std::ios::binary);

	if (!fichier.fail())
	{
		for (int i = 0; i < 14; i++)
			fichier.read((char*)&config_[i], sizeof(int));

		fichier.close();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::modifierConfiguration(int config[14])
///
/// Cette fonction assigne les nouvelles configurations de zone de jeu.
///
/// @param[in] config : Un tableau contenant les informations de configuration
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::modifierConfiguration(int config[14])
{
	config_[0] = config[0];		// Palette gauche joueur 1
	config_[1] = config[1];		// Palette droite joueur 1
	config_[2] = config[2];		// Palette gauche joueur 2
	config_[3] = config[3];		// Palette droite joueur 2
	config_[4] = config[4];		// Ressort
	config_[5] = config[5];		// Nombre de billes par partie
	config_[6] = config[6];		// Mode double bille
	config_[7] = config[7];		// Mode force de rebond
	config_[8] = config[8];		// Generation d'une bille
	config_[9] = config[9];		// Vitesse apres collision
	config_[10] = config[10];	// Activation de l'eclairage
	config_[11] = config[11];	// Champ d'attraction de portail
	config_[12] = config[12];	// Interrupteur d'affichage de debug
	config_[13] = config[13];	// Intelligence artificielle
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ConfigScene::modifierCampagne(char* maps, int length)
///
/// Cette fonction assigne les nouvelles informations de derniere campagne jouee.
///
/// @param[in] maps : La liste des informations de derniere campagne
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ConfigScene::modifierCampagne(char* maps)
{
	std::string map(maps);
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	listeCartes_.clear();

	while ((pos = map.find(delimiter)) != std::string::npos) 
	{
		token = map.substr(0, pos);
		listeCartes_.push_back(token);

		map.erase(0, pos + delimiter.length());
	}

	listeCartes_.push_back(map);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn char* ConfigScene::obtenirCampagne() const
///
/// Cette fonction retourne les informations de derniere campagne
///
/// @return string, la liste des zones de jeu de derniere campagne
///
////////////////////////////////////////////////////////////////////////
std::string ConfigScene::obtenirCampagne() const 
{
	std::stringstream ss;

	for (unsigned int i = 0; i < listeCartes_.size(); i++)
	{
		ss << listeCartes_[i] << " ";
	}

	return ss.str();
}



///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
