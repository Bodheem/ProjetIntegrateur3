///////////////////////////////////////////////////////////////////////////////
/// @file FacadeJeu.cpp
/// @author The New Ballers
/// @date 2016-02-22
/// @version 1.0
/// @ingroup Application
///////////////////////////////////////////////////////////////////////////////

#include <ArbreRenduINF2990.h>
#include <Noeuds/NoeudRessort.h>
#include <Noeuds/NoeudPaletteD.h>
#include <Noeuds/NoeudPaletteG.h>

#include <FacadeJeu.h>
#include <FacadeModele.h>
#include <FacadeReseau.h>

#include "../Compte/IntelligenceArtificielle.h"
#include "../Compte/IntelligenceProbabiliste.h"
#include "../QuadTree/PhysicsManager.h"
#include "../Visiteurs/VisiteurPortail.h"
#include "../Visiteurs/VisiteurConstruireListes.h"
#include "../Visiteurs/VisiteurPalettes.h"
#include "../Sauvegarde/Snapshot.h"
#include "../Compte/Joueur.h"
#include "../ModeJeu/Competitif.h"
#include "../ModeJeu/Cooperatif.h"

/// Pointeur vers l'instance unique de la classe.
FacadeJeu* FacadeJeu::instance_{ nullptr };


////////////////////////////////////////////////////////////////////////
/// @fn FacadeJeu::FacadeJeu()
/// @brief 
/// @return Une instance de la classe
////////////////////////////////////////////////////////////////////////
FacadeJeu::FacadeJeu()
{
	physics_ = new PhysicsManager();
	secondPlayer_ = new IntelligenceArtificielle(1);
	thirdPlayer_ = nullptr;
	fourthPlayer_ = nullptr;
	modejeu_ = nullptr;

	// Instancier des joueurs virtuels supplémentaires si on est connecté 
	if(FacadeReseau::obtenirInstance()->obtenirCompte()->isOnlineAccount())
	{
		thirdPlayer_ = new IntelligenceArtificielle(2);
		fourthPlayer_ = new IntelligenceArtificielle(3);
	}

	inverserTouches = false;

	utiliserAI[0] = false; // N'existe pas de joueur 0
	utiliserAI[1] = false; // Le joueur 1 est le joueur courant
	utiliserAI[2] = false; // Joueur 2
	utiliserAI[3] = false; // Joueur 3
	utiliserAI[4] = false; // Joueur 4

	isPressed[0] = false;	// Palettes gauches
	isPressed[1] = false;	// Palettes droites
	isPressed[2] = false;	// Ressort
}


////////////////////////////////////////////////////////////////////////
/// @fn FacadeJeu* FacadeJeu::obtenirInstance()
/// @brief Cette fonction retourne un pointeur vers l'instance unique de la
///		   classe.  Si cette instance n'a pas ete creee, elle la cree.  Cette
///		   creation n'est toutefois pas necessairement "thread-safe", car
///		   aucun verrou n'est pris entre le test pour savoir si l'instance
///		   existe et le moment de sa creation.
/// @return Un pointeur vers l'instance unique de cette classe.
////////////////////////////////////////////////////////////////////////
FacadeJeu* FacadeJeu::obtenirInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new FacadeJeu();
	}
	return instance_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::libererInstance()
/// @brief Cette fonction libere l'instance unique de cette classe.
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void FacadeJeu::libererInstance()
{
	delete instance_;
	instance_ = nullptr;
}


////////////////////////////////////////////////////////////////////////
/// @fn FacadeJeu::~FacadeJeu()
/// @brief Ce destructeur libere les objets du modele.
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
FacadeJeu::~FacadeJeu()
{
	delete physics_;
	delete secondPlayer_;
	delete thirdPlayer_;
	delete fourthPlayer_;
	delete modejeu_;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::traiterCollisions(float temps)
/// @brief Effectue la detection et reaction pour les collisions entre tous les noeuds.
/// @remark Les listes doivent etre construites et la liste de billes doit etre tenue a jour.
/// @param[in] temps : temps entre les calculs de physique.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::traiterCollisions(float temps) const
{
	physics_->traiterCollisions(temps);
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::updateForcesExternes() const
/// @brief Pour chaque bille, calcule la somme des forces exercees par les portails 
///		   sur celle-ci. Si la distance entre la bille et le portail est plus grande
///		   qu'une certaine valeur, la force de ce portail n'est pas comptee.
///		   Cette fonction considere aussi si un bille vien de sortir d'un portail.
///		   Tant que la bille ne s'est pas assez eloignee du portail d'ou elle est 
///		   apparue, ce portail de l'affectera pas.
/// @remark Les listes doivent etre construites et la liste de billes doit etre tenue a jour.
///		   (Pour l'instant elles sont mises a jour a chaque frame donc pas de problemes ici.)
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::updateForcesExternes() const
{
	physics_->updateForcesExternes();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::compresserRessort()
/// @brief Declenche l'animation de compression de ressort.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::compresserRessort(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	for (NoeudAbstrait* ressort : listeRessorts_[colorshift])
		static_cast<NoeudRessort*>(ressort)->compresser();

	isPressed[2] = true;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::relacherRessort()
/// @brief Declenche l'animation de decompression de ressort.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::relacherRessort(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	for (NoeudAbstrait* ressort : listeRessorts_[colorshift])
		static_cast<NoeudRessort*>(ressort)->relacher();

	isPressed[2] = false;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::inverserTouchesPalettes()
///	@brief Inverse les touches associées aux palettes du joueur 1
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void FacadeJeu::inverserTouchesPalettes()
{
	inverserTouches = !inverserTouches;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::desactiverTemporairementPortails()
///	@brief Désactive temporairement la téléportation des portails
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void FacadeJeu::desactiverTemporairementPortails() const
{
	// Récupérer l'arbre de rendu
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	std::clock_t  start;
	start = std::clock();

	VisiteurAbstrait* visiteur = new VisiteurPortail(start);
	arbre->accepterVisiteur(visiteur);

	delete visiteur;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::desactiverTemporairementPalettes()
///	@brief Désactive temporairement les palettes
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void FacadeJeu::desactiverTemporairementPalettes() const
{
	// Récupérer l'arbre de rendu
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	std::clock_t  start;
	start = std::clock();

	VisiteurAbstrait* visiteur = new VisiteurPalettes(start);
	arbre->accepterVisiteur(visiteur);

	delete visiteur;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::mettreAJourListeRessorts()
/// @brief Met a jour la liste des ressorts pour le controle par la touche du clavier.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::mettreAJourListeRessorts()
{
	if (listeRessorts_.size() == 0)
	{
		std::vector<NoeudAbstrait*> ressort;
		listeRessorts_.push_back(ressort);
		listeRessorts_.push_back(ressort);
		listeRessorts_.push_back(ressort);
		listeRessorts_.push_back(ressort);
	}

	// Récupérer l'arbre de rendu
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	// Pour toutes les palettes de tous les colorshift
	for (int i = 0; i < 4; ++i)
	{
		listeRessorts_[i].clear();
	}

	// Mettre a jour les ressorts
	for (unsigned int j = 0; j < arbre->getEnfant(0)->obtenirNombreEnfants(); j++)
	{
		NoeudAbstrait* noeud = arbre->getEnfant(0)->getEnfant(j);
		if (noeud->obtenirType() == "ressort")
		{
			listeRessorts_[noeud->getColorShift()].push_back(noeud);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::construireListesPalettes()
/// @brief Visite l'arbre et ajoute chaque palette a la bonne liste.  
///		   Utilise l'attribut colorShift_ pour distinguer les palettes du 
///		   joueur1 et du joueur 2.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::construireListesPalettes()
{
	FacadeModele::obtenirInstance()->obtainSecureLock();

	// Récupérer l'arbre de rendu
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	VisiteurConstruireListes visCL(palettesGauches_, palettesDroites_);
	arbre->accepterVisiteur(&visCL);
	mettreAJourListeRessorts();

	if (secondPlayer_ != nullptr)
		secondPlayer_->assignerPalettes(palettesGauches_[1], palettesDroites_[1]);

	if (thirdPlayer_ != nullptr)
		thirdPlayer_->assignerPalettes(palettesGauches_[2], palettesDroites_[2]);

	if (fourthPlayer_ != nullptr)
		fourthPlayer_->assignerPalettes(palettesGauches_[3], palettesDroites_[3]);

	FacadeModele::obtenirInstance()->releaseSecureLock();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::activerPalettesGJ1() const
/// @brief Active les palettes gauches du joueur 1.
/// @remark Les listes de palettes doivent avoir etes construites.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::activerPalettesGauches(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	if (inverserTouches)
	{
		for (NoeudPaletteD* palette : palettesDroites_[colorshift])
			if (palette != nullptr)
				palette->activer();
	}
	else
	{
		for (NoeudPaletteG* palette : palettesGauches_[colorshift])
			if (palette != nullptr)
				palette->activer();
	}

	isPressed[0] = true;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::desactiverPalettesGJ1() const
/// @brief Desactive les palettes gauches du joueur 1. 
/// @remark Les listes de palettes doivent avoir etes construites.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::desactiverPalettesGauches(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	if (inverserTouches)
	{
		for (NoeudPaletteD* palette : palettesDroites_[colorshift])
			if (palette != nullptr)
				palette->desactiver();
	}
	else
	{
		for (NoeudPaletteG* palette : palettesGauches_[colorshift])
			if (palette != nullptr)
				palette->desactiver();
	}

	isPressed[0] = false;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::activerPalettesGJ1() const
/// @brief Active les palettes gauches du joueur 1.
/// @remark Les listes de palettes doivent avoir etes construites.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::activerPalettesDroites(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	if (inverserTouches)
	{
		for (NoeudPaletteG* palette : palettesGauches_[colorshift])
			if (palette != nullptr)
				palette->activer();
	}
	else
	{
		for (NoeudPaletteD* palette : palettesDroites_[colorshift])
			if (palette != nullptr)
				palette->activer();
	}

	isPressed[1] = true;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::desactiverPalettesGJ1() const
/// @brief Desactive les palettes gauches du joueur 1. 
/// @remark Les listes de palettes doivent avoir etes construites.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::desactiverPalettesDroites(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	if (inverserTouches)
	{
		for (NoeudPaletteG* palette : palettesGauches_[colorshift])
			if (palette != nullptr)
				palette->desactiver();
	}
	else
	{
		for (NoeudPaletteD* palette : palettesDroites_[colorshift])
			if (palette != nullptr)
				palette->desactiver();
	}

	isPressed[1] = false;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::mettreAJourListeNoeuds()
/// @brief Met a jour la liste des noeuds a verifier pour les collisions.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::mettreAJourListeNoeuds() const
{
	physics_->mettreAJourListeNoeuds();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::mettreAJourListeBillesEtNoeuds()
/// @brief Met a jour la liste des billes
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::mettreAJourListeBillesEtNoeuds() const
{
	physics_->mettreAJourListeBillesEtNoeuds();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::initializeLevelAI(std::string type)
/// @brief Cette fonction active un niveau de AI
/// @param[in]  type, le type de l'AI
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::initializeLevelAI(std::string type)
{
	if (type == "INTELLIGENT")
	{
		delete secondPlayer_;
		secondPlayer_ = nullptr;

		secondPlayer_ = new IntelligenceArtificielle(1);
	}
	else if(type == "STUPIDE")
	{
		delete secondPlayer_;
		secondPlayer_ = nullptr;

		secondPlayer_ = new IntelligenceProbabiliste(1);
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::assignerAI(bool actif)
/// @brief Cette fonction active ou desactive l'utilisation du joueur AI.
/// @param[in]  actif : la valeur d'utilisation de l'AI a assigner
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::activerAI(bool actif, int joueur)
{
	if (joueur < 1 || joueur > 4)
		return;

	utiliserAI[joueur] = actif;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::jouerAI()
/// @brief Fais jouer le joueur virtuel
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::jouerAI(float temps) const
{
	auto listeBilles_ = physics_->obtenirListeBilles();

	// Joueur 2
	if (utiliserAI[2])
	{
		secondPlayer_->jouer(listeBilles_, temps);
	}

	// Joueur 3
	if (utiliserAI[3])
	{
		thirdPlayer_->jouer(listeBilles_, temps);
	}

	// Joueur 4
	if (utiliserAI[4])
	{
		fourthPlayer_->jouer(listeBilles_, temps);
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::createSnapshot()
/// @brief 
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
std::string FacadeJeu::createSnapshot()
{
	// Prendre un lock sur la FacadeModele
	FacadeModele::obtenirInstance()->obtainSecureLock();

	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	std::string s = Snapshot::toString(arbre);

	// Relacher le lock
	FacadeModele::obtenirInstance()->releaseSecureLock();

	return s;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::applyModification()
/// @brief 
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::applyModification(std::string data)
{
	// Prendre un lock sur la FacadeModele
	FacadeModele::obtenirInstance()->obtainSecureLock();

	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	bool isLoaded = FacadeModele::obtenirInstance()->obtenirSiArbreVide();

	if (isLoaded)
	{
		Snapshot::applySnapshot(data, arbre);
	}

	// Relacher le lock
	FacadeModele::obtenirInstance()->releaseSecureLock();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::obtenirEtatBouton()
/// @brief 
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
bool FacadeJeu::obtenirEtatBouton(int bouton) const
{
	if (bouton < 0 || bouton > 2)
		return false;

	return isPressed[bouton];
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::initialiserModeCompetitif()
/// @brief 
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::initialiserModeCompetitif()
{
	delete modejeu_;
	modejeu_ = new Competitif();

	modejeu_->initialiserMode();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeJeu::initialiserModeCompetitif()
/// @brief 
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeJeu::initialiserModeCooperatif()
{
	delete modejeu_;
	modejeu_ = new Cooperatif();

	modejeu_->initialiserMode();
}

