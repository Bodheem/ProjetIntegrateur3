///////////////////////////////////////////////////////////////////////////
/// @file NoeudMalus.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudMalus.h"
#include "Utilitaire.h"
#include <ArbreRenduINF2990.h>

#include <GL/gl.h>
#include "Modele3D.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include <FacadeModele.h>
#include <FacadeJeu.h>
#include <FacadeReseau.h>
#include <stdlib.h>
#include <time.h>
#include "../Compte/Joueur.h"


////////////////////////////////////////////////////////////////////////
/// @fn NoeudMalus::NoeudMalus(const std::string& typeNoeud)
/// @param[in] typeNoeud :  le type du noeud a creer.
/// @brief Ce constructeur ne fait qu'appeler la version de la classe et base
///		   et donner des valeurs par defaut aux variables membres.
/// @return Aucune (constructeur).
////////////////////////////////////////////////////////////////////////
NoeudMalus::NoeudMalus(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	srand(static_cast<unsigned int>(time(nullptr)));

	effects_.push_back("VITESSE DE BILLE RALENTIE!");
	effects_.push_back("PALETTES BLOQUEES!");
	effects_.push_back("TOUCHES INVERSEES!");
	effects_.push_back("BILLE DETRUITE!");
}


////////////////////////////////////////////////////////////////////////
/// @fn NoeudMalus::~NoeudMalus()
/// @brief Ce destructeur desallouee la liste d'affichage du noeud.
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
NoeudMalus::~NoeudMalus()
{

}


////////////////////////////////////////////////////////////////////////
/// @fn void NoeudMalus::afficherConcret() const
/// Cette fonction effectue le veritable rendu de l'objet.
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void NoeudMalus::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	NoeudAbstrait::appliquerAfficher();
	liste_->dessiner();
	glPopAttrib();
	glPopMatrix();
	// Restauration de la matrice.
}


////////////////////////////////////////////////////////////////////////
/// @fn void NoeudMalus::animer(float temps)
/// @brief Cette fonction effectue l'animation du noeud pour un certain
///		   intervalle de temps. Pas d'animation pour ce type de noeud.
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void NoeudMalus::animer(float temps)
{
	std::clock_t time = std::clock();
	double diff = (time - lastDisapear_) / static_cast<double>(CLOCKS_PER_SEC);

	if (diff > 10)
	{
		assignerAffiche(true);
	}

	NoeudComposite::animer(temps);
}


////////////////////////////////////////////////////////////////////////
/// @fn bool NoeudMalus::accepterVisiteur(VisiteurAbstrait* vis)
/// @brief Cette fonction appelle la methode traiter du visiteur.
/// @param[in] vis Pointeur sur le visiteur a accepter
/// @return reussi (TRUE)
////////////////////////////////////////////////////////////////////////
bool NoeudMalus::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}


////////////////////////////////////////////////////////////////////////
/// @fn void NoeudMalus::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille)
/// @brief Cette fonction effectue la reaction a la collision de la bille sur 
///		   l'objet courant. Cette fonction est a reimplementer si on veut autre 
///		   chose qu'un rebondissement ordinaire.
/// @return aucun.
////////////////////////////////////////////////////////////////////////
void NoeudMalus::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float)
{
	if (bille->obtenirType() != "bille")
		return;

	/// Faire disparaitre le malus
	this->assignerAffiche(false);
	lastDisapear_ = std::clock();

	// Appliquer l'effet seulement par le Host si on est en mode multijoueur
	bool isOnline = FacadeReseau::obtenirInstance()->obtenirCompte()->isOnlineAccount();

	if (isOnline)
	{
		// Si on n'est pas le host, ne pas appliquer l'effet
		int numeroJoueur = FacadeReseau::obtenirInstance()->obtenirNumeroJoueur();
		if (numeroJoueur != 1 && numeroJoueur != -1)
			return;
	}

	int effect = rand() % 4;
	switch (effect)
	{
		// VITESSE DE BILLE RALENTIE!
		case 0: 
				bille->assignerVitesse(bille->obtenirVitesse() * 0.2);
				break;

		// PALETTES BLOQUEES!
		case 1: 
				FacadeJeu::obtenirInstance()->desactiverTemporairementPalettes();
				break;

		// TOUCHES INVERSEES!
		case 2:
				FacadeJeu::obtenirInstance()->inverserTouchesPalettes();
				break;

		// BILLE DETRUITE!
		case 3:
				FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->retirerBille();
				FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->effacer(bille);
				break;
	}

	// Assigner la string pour l'affichage et le temps
	FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->assignerMalusCourant(effects_[effect]);
	FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->assignerTempsAffichageMalus(std::clock());
}


////////////////////////////////////////////////////////////////////////
/// @fn void NoeudMalus::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille)
/// @brief Reimplementation de detecterCollisions pour le Bonus.  Si la Gate 
///		   a etee frappee elle disparait (affiche_  devient false).  Si la Gate
///		   est affichee, on fait le comportement par defaut donne dans NoeudAbstrait,
///		   sinon, or retourne un DetailCollisions avec type COLLISION_AUCUNE.
/// @return details contient l'information sur la collision de la bille avec *this.
////////////////////////////////////////////////////////////////////////
aidecollision::DetailsCollision NoeudMalus::detecterCollisions(NoeudAbstrait* bille)
{
	/* Traiter collision one way ici */
	aidecollision::DetailsCollision detailsAucune;
	detailsAucune.type = aidecollision::COLLISION_AUCUNE;
	if (affiche_)
		return NoeudAbstrait::detecterCollisions(bille);

	return detailsAucune;
}