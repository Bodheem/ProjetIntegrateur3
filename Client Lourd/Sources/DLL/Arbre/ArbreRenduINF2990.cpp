///////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduINF2990.cpp
/// @author Martin Bisson
/// @date 2007-03-23
/// @version 1.0
/// @ingroup Arbre
///////////////////////////////////////////////////////////////////////////
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"

#include "Usines/UsineNoeudButoirD.h"
#include "Usines/UsineNoeudButoirG.h"
#include "Usines/UsineNoeudButoirCirculaire.h"
#include "Usines/UsineNoeudCible.h"
#include "Usines/UsineNoeudBille.h"
#include "Usines/UsineNoeudGenerateurBille.h"
#include "Usines/UsineNoeudMur.h"
#include "Usines/UsineNoeudPaletteD.h"
#include "Usines/UsineNoeudPaletteG.h"
#include "Usines/UsineNoeudPortail.h"
#include "Usines/UsineNoeudPortailTorus.h"
#include "Usines/UsineNoeudRessort.h"
#include "Usines/UsineNoeudTrou.h"
#include "Usines/UsineNoeudVide.h"
#include "Usines/UsineNoeudCouvercle.h"
#include "Usines/UsineNoeudTable.h"
#include "Usines/UsineNoeudGate.h"
#include "Usines/UsineNoeudBonus.h"
#include "Usines/UsineNoeudMalus.h"

#include <iomanip>
#include <FreeImage.h>

const std::string ArbreRenduINF2990::NOM_BUTOIRD{ "butoird" };
const std::string ArbreRenduINF2990::NOM_BUTOIRG{ "butoirg" };
const std::string ArbreRenduINF2990::NOM_BUTOIRCIRCULAIRE{ "butoircirculaire" };
const std::string ArbreRenduINF2990::NOM_CIBLE{ "cible" };
const std::string ArbreRenduINF2990::NOM_BILLE{ "bille" };
const std::string ArbreRenduINF2990::NOM_GENERATEURBILLE{ "generateurbille" };
const std::string ArbreRenduINF2990::NOM_MUR{ "mur" };
const std::string ArbreRenduINF2990::NOM_PALETTED{ "paletted" };
const std::string ArbreRenduINF2990::NOM_PALETTEG{ "paletteg" };
const std::string ArbreRenduINF2990::NOM_PORTAIL{ "portail" };
const std::string ArbreRenduINF2990::NOM_PORTAILTORUS{ "portailtorus" };
const std::string ArbreRenduINF2990::NOM_RESSORT{ "ressort" };
const std::string ArbreRenduINF2990::NOM_TROU{ "trou" };
const std::string ArbreRenduINF2990::NOM_VIDE{ "vide" };
const std::string ArbreRenduINF2990::NOM_COUVERCLE{ "couvercle" };
const std::string ArbreRenduINF2990::NOM_TABLE{ "table" };
const std::string ArbreRenduINF2990::NOM_GATE{ "gate" };
const std::string ArbreRenduINF2990::NOM_BONUS{ "bonus" };
const std::string ArbreRenduINF2990::NOM_MALUS{ "malus" };

////////////////////////////////////////////////////////////////////////
/// @fn ArbreRenduINF2990::ArbreRenduINF2990()
/// @brief Ce constructeur cree toutes les usines qui seront utilisees par le
///		   projet de INF2990et les enregistre aupres de la classe de base.
///		   Il cree egalement la structure de base de l'arbre de rendu, c'est-a-dire
///		   avec les noeuds structurants.
/// @return Aucune (constructeur).
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::ArbreRenduINF2990() 
{
	// Définir le type du noeud
	type_ = "arbreRenduINF2990";
}


////////////////////////////////////////////////////////////////////////
/// @fn ArbreRenduINF2990::preparerUsine(const std::string& usine)
/// @brief Ajouter une usine à l'arbre
/// @param[in] : usine, le nom de l'usine à ajouter
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::preparerUsine(const std::string& usine)
{
	if (usine == NOM_BUTOIRD)
		ajouterUsine(NOM_BUTOIRD, new UsineNoeudButoirD{ NOM_BUTOIRD });
	else if (usine == NOM_BUTOIRG)
		ajouterUsine(NOM_BUTOIRG, new UsineNoeudButoirG{ NOM_BUTOIRG });
	else if (usine == NOM_BUTOIRCIRCULAIRE)
		ajouterUsine(NOM_BUTOIRCIRCULAIRE, new UsineNoeudButoirCirculaire{ NOM_BUTOIRCIRCULAIRE });
	else if (usine == NOM_CIBLE)
		ajouterUsine(NOM_CIBLE, new UsineNoeudCible{ NOM_CIBLE });
	else if (usine == NOM_BILLE)
		ajouterUsine(NOM_BILLE, new UsineNoeudBille{ NOM_BILLE });
	else if (usine == NOM_GENERATEURBILLE)
		ajouterUsine(NOM_GENERATEURBILLE, new UsineNoeudGenerateurBille{ NOM_GENERATEURBILLE });
	else if (usine == NOM_MUR)
		ajouterUsine(NOM_MUR, new UsineNoeudMur{ NOM_MUR });
	else if (usine == NOM_PALETTED)
		ajouterUsine(NOM_PALETTED, new UsineNoeudPaletteD{ NOM_PALETTED });
	else if (usine == NOM_PALETTEG)
		ajouterUsine(NOM_PALETTEG, new UsineNoeudPaletteG{ NOM_PALETTEG });
	else if (usine == NOM_PORTAIL)
		ajouterUsine(NOM_PORTAIL, new UsineNoeudPortail{ NOM_PORTAIL });
	else if (usine == NOM_PORTAILTORUS)
		ajouterUsine(NOM_PORTAILTORUS, new UsineNoeudPortailTorus{ NOM_PORTAILTORUS });
	else if (usine == NOM_RESSORT)
		ajouterUsine(NOM_RESSORT, new UsineNoeudRessort{ NOM_RESSORT });
	else if (usine == NOM_TROU)
		ajouterUsine(NOM_TROU, new UsineNoeudTrou{ NOM_TROU });
	else if (usine == NOM_VIDE)
		ajouterUsine(NOM_VIDE, new UsineNoeudVide{ NOM_VIDE });
	else if (usine == NOM_COUVERCLE)
		ajouterUsine(NOM_COUVERCLE, new UsineNoeudCouvercle{ NOM_COUVERCLE });
	else if (usine == NOM_TABLE)
		ajouterUsine(NOM_TABLE, new UsineNoeudTable{ NOM_TABLE });
	else if (usine == NOM_GATE)
		ajouterUsine(NOM_GATE, new UsineNoeudGate{ NOM_GATE });
	else if (usine == NOM_BONUS)
		ajouterUsine(NOM_BONUS, new UsineNoeudBonus{ NOM_BONUS });
	else if (usine == NOM_MALUS)
		ajouterUsine(NOM_MALUS, new UsineNoeudMalus{ NOM_MALUS });
	else
	{
		std::string erreur = "Imposible d'ajouter l'usine " + usine + " car celle ci n'existe pas ou n'est pas encore implemente.";
		std::cerr << erreur;
		assert(false);
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn ArbreRenduINF2990::~ArbreRenduINF2990()
/// @brief Ce destructeur ne fait rien pour le moment.
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
ArbreRenduINF2990::~ArbreRenduINF2990()
{
	libererUsines();
	listeNoeuds_.clear();
}


////////////////////////////////////////////////////////////////////////
/// @fn void ArbreRenduINF2990::initialiser()
/// @brief Cette fonction cree la structure de base de l'arbre de rendu, c'est-a-dire
///		   avec les noeuds structurants (pour les objets, les murs, les billes,
///		   les parties statiques, etc.)
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::initialiser()
{
	// On vide l'arbre
	vider();
}


////////////////////////////////////////////////////////////////////////
/// @fn NoeudAbstrait* ArbreRenduINF2990::getEnfant(int position)
/// @brief Cette fonction retourne un NoeudAbstrait* qui correspond
///		   a l'enfant de la position passe en parametre.
/// @return NoeudAbstrait* L'enfant en question.
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* ArbreRenduINF2990::getEnfant(int position) const
{
	if (position > enfants_.size() || position < 0)
		return nullptr;

	if (enfants_.empty())
		return nullptr;

	return enfants_[position];
}


////////////////////////////////////////////////////////////////////////
/// @fn bool ArbreRenduINF2990::accepterVisiteur(VisiteurAbstrait* vis)
/// @brief Cette fonction appelle la methode traiter du visiteur.
/// @param[in] vis Pointeur sur le visiteur a accepter
/// @return operationReussie (TRUE)
////////////////////////////////////////////////////////////////////////
bool ArbreRenduINF2990::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool operationReussie = false;

	if (vis->traiter(this))
		operationReussie = true;

	return operationReussie;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool ArbreRenduINF2990::estDefaut()
/// @brief Cette fonction dit si les elements de l'arbre constituent la zone de jeu par defaut
/// @return TRUE : la zone est une zone par defaut. Autrement, FALSE
////////////////////////////////////////////////////////////////////////
bool ArbreRenduINF2990::estDefaut() const
{
	if (   posRessort == chercher("ressort")->obtenirPositionRelative()
		&& angleRessort == chercher("ressort")->obtenirRotation()
		&& scaleRessort == chercher("ressort")->obtenirAgrandissement()
		&& posTrou == chercher("trou")->obtenirPositionRelative()
		&& angleTrou == chercher("trou")->obtenirRotation()
		&& scaleTrou == chercher("trou")->obtenirAgrandissement()
		&& posGenerateur == chercher("generateurbille")->obtenirPositionRelative()
		&& angleGenerateur == chercher("generateurbille")->obtenirRotation()
		&& scaleGenerateur == chercher("generateurbille")->obtenirAgrandissement()
		)
		return true;

	return false;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool ArbreRenduINF2990::assignerDefaut()
/// @brief Cette fonction definit ce qu'est une zone de jeu par defaut
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::assignerDefaut()
{
	posRessort = chercher("ressort")->obtenirPositionRelative();
	angleRessort = chercher("ressort")->obtenirRotation();
	scaleRessort = chercher("ressort")->obtenirAgrandissement();
	posTrou = chercher("trou")->obtenirPositionRelative();
	angleTrou = chercher("trou")->obtenirRotation();
	scaleTrou = chercher("trou")->obtenirAgrandissement();
	posGenerateur = chercher("generateurbille")->obtenirPositionRelative();
	angleGenerateur = chercher("generateurbille")->obtenirRotation();
	scaleGenerateur = chercher("generateurbille")->obtenirAgrandissement();
}


////////////////////////////////////////////////////////////////////////
/// @fn void ArbreRenduINF2990::takeScreenShot(char* path, int width, int height, bool square, int maxSize)
/// @brief Cette fonction recoit un path vers le disque dur et renregistre l'ecran afficher
/// @param[in] path : le chemin ou enregistrer
/// @param[in] width : largeur de la fenetre
/// @param[in] height : hauteur de la fenetre
/// @param[in] maxSize : taille maximale (pixel) de l'image
/// @param[in] square : forme de l'image carre
/// @return : Aucun.
////////////////////////////////////////////////////////////////////////
void ArbreRenduINF2990::takeScreenShot(char* path, int width, int height, bool square, int maxSize)
{
	if (maxSize != 0 || square == true)
		width > height ? width = height : height = width;
	// Make the BYTE array, factor of 3 because it's RBG.
	// Facteur Debug ? sert a ne pas avoir de corruption de heap, dont ask.
	int FACTEUR_DEBUG = 2;
	BYTE* pixels = new BYTE[3 * FACTEUR_DEBUG * width * height];
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// On semble etre en BGR plus tot qu'en RGB
	glReadPixels(0, 0, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);

	// Convert to FreeImage format & save to file
	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height, ((((24 * width) + 31) / 32) * 4), 24,
		0x000000, 0x000000, 0x000000, false);
	// La couleur ici semble... useless (le 0x000000)

	// La on rescale a 100px*100px
	if (maxSize != 0)
		image = FreeImage_Rescale(image, maxSize, maxSize, FILTER_BOX);

	FreeImage_Save(FIF_JPEG, image, path, 0);

	// Free resources
	FreeImage_Unload(image);
	delete[] pixels;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool ArbreRenduINF2990::obtenirElementsTable()
/// @brief Retourne tous les elements de la table
/// @return vector<NoeudAbstrait*>, la liste des enfants de la table
////////////////////////////////////////////////////////////////////////
std::vector<NoeudAbstrait*> ArbreRenduINF2990::obtenirElementsTable()
{
	listeNoeuds_.clear();

	for (unsigned int i = 0; i < getEnfant(0)->obtenirNombreEnfants(); i++)
		listeNoeuds_.push_back(getEnfant(0)->getEnfant(i));

	return listeNoeuds_;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool ArbreRenduINF2990::obtenirNoeudSelonNumero()
/// @brief Retourne le noeuds selon le noeud passé en paramètre
/// @param[in] : numero, le numero cherché
/// @return NoeudAbstrait*, le noeud du numéro recherché
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* ArbreRenduINF2990::obtenirNoeudSelonNumero(int numero)
{
	std::vector<NoeudAbstrait*> temp = obtenirElementsTable();

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		if (temp[i]->getNumero() == numero)
			return temp[i];
	}

	return nullptr;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool ArbreRenduINF2990::obtenirNoeudSelonNumero()
/// @brief Retourne le noeuds selon le noeud passé en paramètre
/// @param[in] : numero, le numero cherché
/// @return NoeudAbstrait*, le noeud du numéro recherché
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* ArbreRenduINF2990::obtenirSelonNumeroUnique(int numero)
{
	int size = getEnfant(0)->obtenirNombreEnfants();

	for (int i = 0; i < size; i++)
	{
		if (getEnfant(0)->getEnfant(i)->obtenirNumeroUnique() == numero)
			return getEnfant(0)->getEnfant(i);
	}

	return nullptr;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool ArbreRenduINF2990::obtenirNombreSelectionne()
/// @brief Retourne le nombre de noeuds selectionnés
/// @return int, le nombre d'enfants selectionnés
////////////////////////////////////////////////////////////////////////
int ArbreRenduINF2990::obtenirNombreSelectionne() const
{
	int nombre = 0;

	for (unsigned int i = 0; i < getEnfant(0)->obtenirNombreEnfants(); i++)
	{
		if (getEnfant(0)->getEnfant(i)->estSelectionne())
			nombre++;
	}
	
	return nombre;
}