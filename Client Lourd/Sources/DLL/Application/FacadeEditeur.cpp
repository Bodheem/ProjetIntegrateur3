///////////////////////////////////////////////////////////////////////////////
/// @file FacadeEditeur.cpp
/// @author The New Ballers
/// @date 2016-02-22
/// @version 1.0
/// @ingroup Application
///////////////////////////////////////////////////////////////////////////////

#include <OpenGL/aidegl.h>
#include <ArbreRenduINF2990.h>

#include "FacadeEditeur.h"
#include "FacadeReseau.h"
#include "FacadeModele.h"
#include "Vue.h"

#include "../Compte/Joueur.h"
#include "../Memento/Originator.h"
#include "../Sauvegarde/ParserXML.h"
#include "../Sauvegarde/Propriete.h"

#include "../Visiteurs/VisiteurDuplication.h"
#include "../Visiteurs/VisiteurSuppression.h"
#include "../Visiteurs/VisiteurSelectionMultiple.h"
#include "../Visiteurs/VisiteurSelectionInverseMultiple.h"
#include "../Visiteurs/VisiteurLimitesSelection.h"
#include "../Visiteurs/VisiteurCentreDeMasse.h"
#include "../Visiteurs/VisiteurDeplacement.h"
#include "../Visiteurs/VisiteurAgrandissement.h"
#include "../Visiteurs/VisiteurListeEnglobante.h"
#include "../Visiteurs/VisiteurRotationPoint.h"
#include "../Visiteurs/VisiteurSelection.h"
#include "../Visiteurs/VisiteurSelectionInverse.h"


/// Pointeur vers l'instance unique de la classe.
FacadeEditeur* FacadeEditeur::instance_{ nullptr };


////////////////////////////////////////////////////////////////////////
/// @fn FacadeEditeur::FacadeEditeur()
/// @brief 
/// @return Une instance de la classe
////////////////////////////////////////////////////////////////////////
FacadeEditeur::FacadeEditeur()
{
	originator_ = new Originator();
	propriete_ = new Propriete();
	duplicationHorsTable_ = false;

	// Récupérer l'arbre de la FacadeModele
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	if (arbre != nullptr)
		originator_->assignerArbre(arbre);
}


////////////////////////////////////////////////////////////////////////
/// @fn FacadeEditeur* FacadeEditeur::obtenirInstance()
/// @brief Cette fonction retourne un pointeur vers l'instance unique de la
///		   classe.  Si cette instance n'a pas ete creee, elle la cree.  Cette
///		   creation n'est toutefois pas necessairement "thread-safe", car
///		   aucun verrou n'est pris entre le test pour savoir si l'instance
///		   existe et le moment de sa creation.
/// @return Un pointeur vers l'instance unique de cette classe.
////////////////////////////////////////////////////////////////////////
FacadeEditeur* FacadeEditeur::obtenirInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new FacadeEditeur();
	}
	return instance_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::libererInstance()
/// @brief Cette fonction libere l'instance unique de cette classe.
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void FacadeEditeur::libererInstance()
{
	delete instance_;
	instance_ = nullptr;
}


////////////////////////////////////////////////////////////////////////
/// @fn FacadeEditeur::~FacadeEditeur()
/// @brief Ce destructeur libere les objets du modele.
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
FacadeEditeur::~FacadeEditeur()
{
	delete originator_;
	delete propriete_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::reinitialiser()
/// @remark Cette fonction reinitialise la scene à la zone de jeu par défaut
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void FacadeEditeur::reinitialiser() const
{
	chargerZone("zones/default.xml");
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::sauvegarderHistorique()
/// @remark Cette fonction prend un screenshot de l'etat de l'arbre de rendu
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void FacadeEditeur::sauvegarderHistorique() const
{
	originator_->sauvegarder();
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::annulerModifications()
/// @remark Cette fonction implemente la feature "undo"
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void FacadeEditeur::annulerModifications() const
{
	originator_->annuler();
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::retablirModifications()
/// @remark Cette fonction implemente la feature "redo"
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void FacadeEditeur::retablirModifications() const
{
	originator_->retablir();
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::sauvegarderHistorique()
/// @remark Cette fonction vide l'historique de modifications
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void FacadeEditeur::viderHistorique() const
{
	originator_->viderHistorique();
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::possedeSuivant()
/// @remark Cette fonction retourne vrai s'il existe une sauvegarde suivante dans 
///			l'historique des modifications
/// @return True pour dire qu'il existe une sauvegarde suivante
////////////////////////////////////////////////////////////////////////
bool FacadeEditeur::possedeSuivant() const
{
	return originator_->possedeSuivant();
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::possedePrecedent()
/// @remark Cette fonction retourne vrai s'il existe une sauvegarde precedente dans 
///			l'historique des modifications
/// @return True pour dire qu'il existe une sauvegarde precedente
////////////////////////////////////////////////////////////////////////
bool FacadeEditeur::possedePrecedent() const
{
	return originator_->possedePrecedent();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn string FacadeEditeur::sauvegarderZone(char* nomFichier)
/// @brief Sauvegarde une zone de jeu en format XML
/// @param[in] nomFichier : Nom du fichier de la zone.
/// @param[in] proprietes : les propriétés de la zone de jeu.
/// @return string, le resultat de la sauvegarde
///////////////////////////////////////////////////////////////////////////////
std::string FacadeEditeur::sauvegarderZone(char* nomFichier, char* proprietes) const
{
	// Récupérer l'arbre de rendu de la FacadeModele
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	if (strcmp(nomFichier, "zones/zoneTemp.bin") == 0) 
	{
		ParserXML::enregistrerXML(std::string(nomFichier), *arbre, *propriete_);
		return "SUCCESS";
	}
	// Au moins 3 objets sur la scène
	if (arbre->getEnfant(0)->obtenirNombreEnfants() < 3)
	{
		return "ERROR_MINIMUM_3_OBJECTS" + arbre->getEnfant(0)->obtenirNombreEnfants();
	}

	if (!(propriete_->getProprieteValue(propriete_->autheur) == FacadeReseau::obtenirInstance()->obtenirCompte()->getName() ||
		  propriete_->getProprieteValue(propriete_->autheur) == "HORS-LIGNE")
		  )
	{
		return "ERROR_COPYRIGHT";
	}
	// Traiter si c'est la zone de jeu par défaut
	/*if (arbre->estDefaut())
	{
		return "ERROR_SAVE_DEFAULT";
	}*/
	
	// Traiter le rapport de taille du générateur/trou
	if (ratioBilleTrou() < 0)
	{
		return "ERROR_HOLE_SAME_SIZE";
	}
	
	if (arbre->getEnfant(0)->chercher("generateurbille")
		&& arbre->getEnfant(0)->chercher("trou")
		&& arbre->getEnfant(0)->chercher("ressort")
		&& arbre->getEnfant(0)->obtenirNombreEnfants() >= 3
		&& !arbre->estDefaut())
	{
		propriete_->setFromString(std::string(proprietes));

		std::string nomCompte = FacadeReseau::obtenirInstance()->obtenirCompte()->getName();
		propriete_->setPropriete(propriete_->lastModificationBy, nomCompte);

		if (propriete_->getProprieteValue(propriete_->autheur) == "HORS-LIGNE" || propriete_->getProprieteValue(propriete_->autheur) == "")
			propriete_->setPropriete(propriete_->autheur, nomCompte);

		ParserXML::enregistrerXML(std::string(nomFichier), *arbre, *propriete_);
		return "SUCCESS";
	}
	
	return "ERROR";
}

// Retourne true si la zone crée est valide
bool FacadeEditeur::zoneValide()
{
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	if (arbre->getEnfant(0)->chercher("generateurbille")
		&& arbre->getEnfant(0)->chercher("trou")
		&& arbre->getEnfant(0)->chercher("ressort")
		&& arbre->getEnfant(0)->obtenirNombreEnfants() > 3)
		return true;
	else
		return false;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::chargerZone(string nomFichier)
/// @brief Charge une zone de jeu a partir d'un nom de fichier XML
/// @param[in] nomFichier : Nom du fichier de la zone.
/// @return Aucun
///////////////////////////////////////////////////////////////////////////////
void FacadeEditeur::chargerZone(std::string nomFichier) const
{
	// Récupérer l'arbre de rendu de la FacadeModele
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	ParserXML::lireXML(nomFichier, *arbre, *propriete_);
	std::map<std::string, std::string> temp = propriete_->getPropriete();

	int collisionPointsCirculaire = std::stoi(temp[propriete_->pointButoir]);
	int collisionPointsTriangulaire = std::stoi(temp[propriete_->pointTriangulaire]);
	int collisionPointsCible = std::stoi(temp[propriete_->pointCible]);
	int collisionPointsPartieGagner = std::stoi(temp[propriete_->pointVictoire]);
	int collisionPointsNouvelleBille = std::stoi(temp[propriete_->pointBilleGratuite]);

	FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->resetConfigurationCollision(collisionPointsCirculaire, collisionPointsTriangulaire,
		collisionPointsCible, collisionPointsPartieGagner, collisionPointsNouvelleBille);

	// Pour le compteur des numeros unique de la bille
	GlobalesPartie::compteurNumeroBille = arbre->getEnfant(0)->obtenirNombreEnfants() * 5;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn string FacadeEditeur::obtenirPropriete()
/// @brief Retourne les proprietes de jeu de la zone selon un certain format
/// @return Les prorietes de jeu.
///////////////////////////////////////////////////////////////////////////////
std::string FacadeEditeur::obtenirPropriete() const
{
	return propriete_->ToString();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn double FacadeEditeur::ratioBilleTrou()
/// @brief Cette fonction retourne le scale min du trou/max du generateur
/// @return Scale min/max
///////////////////////////////////////////////////////////////////////////////
double FacadeEditeur::ratioBilleTrou() const
{
	// Récupérer l'arbre de rendu de la FacadeModele
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	glm::dvec3 scaleMax = { 0, 0, 0 };
	glm::dvec3 scaleMin = { 0, 0, 0 };

	int i = 0;
	int nbElements = arbre->getEnfant(0)->obtenirNombreEnfants();
	NoeudAbstrait* noeudTable = arbre->getEnfant(0);
	for (i = 0; i < nbElements; i++)
	{
		std::string typeNoeud = noeudTable->getEnfant(i)->obtenirType();

		if (typeNoeud == "generateurbille")
		{
			glm::dvec3 scaleGen = noeudTable->getEnfant(i)->obtenirAgrandissement();
			if (scaleMax.x < scaleGen.x && scaleMax.y < scaleGen.y && scaleMax.z < scaleGen.z)
			{
				scaleMax = scaleGen;
			}
		}
	}

	scaleMin = scaleMax;

	for (i = 0; i < nbElements; i++)
	{
		std::string typeNoeud = noeudTable->getEnfant(i)->obtenirType();

		if (typeNoeud == "trou")
		{
			glm::dvec3 scaleGen = noeudTable->getEnfant(i)->obtenirAgrandissement();
			if (scaleMin.x > scaleGen.x && scaleMin.y > scaleGen.y && scaleMin.z > scaleGen.z)
			{
				scaleMax = scaleGen;
			}
		}
	}

	return glm::length(scaleMax) - glm::length(scaleMin);
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::rectangleElastique(int i, int j)
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeEditeur::rectangleElastique(int i, int j)
{
	glm::ivec2 pointApres(i, j);
	aidegl::mettreAJourRectangleElastique(pointInitial_, pointAvant_, pointApres);
	pointAvant_.x = pointApres.x;
	pointAvant_.y = pointApres.y;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::initialiserRectangleElastique(int i, int j)
///	@remark Initialise un rectangle elastique
/// @param[in]  i : 
/// @param[in]  j : 
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeEditeur::initialiserRectangleElastique(int i, int j)
{
	pointInitial_.x = i;
	pointInitial_.y = j;
	pointAvant_.x = i;
	pointAvant_.y = j;
	aidegl::initialiserRectangleElastique(pointAvant_, 0x3333, 5);
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::terminerRectangleElastique()
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeEditeur::terminerRectangleElastique()
{
	// Obtenir la vue de la FacadeModele
	vue::Vue* vue_ = FacadeModele::obtenirInstance()->obtenirVue();

	aidegl::terminerRectangleElastique(pointInitial_, pointAvant_);

	glm::dvec3 positionInitiale, positionActuelle;
	vue_->convertirClotureAVirtuelle(pointInitial_.x, pointInitial_.y, positionInitiale);
	vue_->convertirClotureAVirtuelle(pointAvant_.x, pointAvant_.y, positionActuelle);

	if (positionInitiale.x < positionActuelle.x && positionInitiale.y < positionActuelle.y)
	{
		selectionBasGauche_ = positionInitiale;
		selectionHautDroit_ = positionActuelle;
	}
	else if (positionInitiale.x > positionActuelle.x && positionInitiale.y > positionActuelle.y)
	{
		selectionBasGauche_ = positionActuelle;
		selectionHautDroit_ = positionInitiale;
	}
	else if (positionInitiale.x < positionActuelle.x && positionInitiale.y > positionActuelle.y)
	{
		selectionBasGauche_.x = positionInitiale.x;
		selectionBasGauche_.y = positionActuelle.y;
		selectionHautDroit_.x = positionActuelle.x;
		selectionHautDroit_.y = positionInitiale.y;
	}
	else if (positionInitiale.x > positionActuelle.x && positionInitiale.y < positionActuelle.y)
	{
		selectionBasGauche_.x = positionActuelle.x;
		selectionBasGauche_.y = positionInitiale.y;
		selectionHautDroit_.x = positionInitiale.x;
		selectionHautDroit_.y = positionActuelle.y;
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn int FacadeEditeur::selectionnerObjetSousPointClique(int i, int j, int hauteur, int, bool ctrlDown, bool gaucheEnfonce, bool sourisSurSelection)
/// @remark Cette fonction permet de selectionner un objet. La methode regarde la valeur
/// \remark du stencil et la donne a un visiteurSelection qui compare cette valeur
/// \remark aux numeros des noeuds et change les met selectionnes ou pas selon le resultat
/// \remark de la comparaison et selon qu'on a clique avec CTRL.
/// @param[in] i : Position souris i
/// @param[in] j : Position souris j
/// @param[in] hauteur : Hauteur de la fenetre
/// @param[in] largeur : Largeur de la fenetre
/// @param[in] ctrlDown : Si le bouton ctrl est appuie
/// @param[in] gaucheEnfonce : Si le bouton gauche est appuier
/// @param[in] sourisSurSelection : Si la souris est sur l'element selectionne
/// @return NoeudAbstrait.
////////////////////////////////////////////////////////////////////////
int FacadeEditeur::selectionSimple(int i, int j, int hauteur, int, bool ctrlDown, bool gaucheEnfonce, bool sourisSurSelection)
{
	// Recuperer la vue et l'arbre de rendu
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();
	vue::Vue* vue = FacadeModele::obtenirInstance()->obtenirVue();

	glm::dvec3 pointDansLeMonde;
	vue->convertirClotureAVirtuelle(i, j, pointDansLeMonde);

	int valeurStencil = 0;
	glReadPixels(i, hauteur - j, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &valeurStencil);

	// Merci de laisser le cout pour que je puisse le decommenter au besoin
	//std::cout << "Valeur du stencil sous le curseur " << valeurStencil << std::endl

	// Merci de laisser le cout pour que je puisse le decommenter au besoin
	//std::cout << "Valeur du stencil sous le curseur " << valeurStencil << std::endl

	//	<< "============= Visite des noeuds ========================" << std::endl;
	if (!ctrlDown)
	{
		VisiteurSelection visSel(pointDansLeMonde, valeurStencil, gaucheEnfonce, sourisSurSelection);
		arbre->accepterVisiteur(&visSel);

		// Demander au visiteur ce qu'il a trouve et faire quelque chose en consequence
		return visSel.obtenirNbObjetsSelectionne();
	}
	else
	{
		VisiteurSelectionInverse visSelInverse(pointDansLeMonde, valeurStencil, gaucheEnfonce, sourisSurSelection);
		arbre->accepterVisiteur(&visSelInverse);

		// Demander au visiteur ce qu'il a trouve et faire quelque chose en consequence
		return visSelInverse.obtenirNbObjetsSelectionne();
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::selectionMultiple(bool c)
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
int FacadeEditeur::selectionMultiple(bool inverse) const
{
	// Récupérer l'arbre de rendu de la FacadeModele
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	if (inverse)
	{
		VisiteurSelectionInverseMultiple visSelInvMul(selectionBasGauche_, selectionHautDroit_);
		arbre->accepterVisiteur(&visSelInvMul);

		return visSelInvMul.obtenirNbObjetsSelectionne();
	}

	VisiteurSelectionMultiple visSelMul(selectionBasGauche_, selectionHautDroit_);
	arbre->accepterVisiteur(&visSelMul);

	return visSelMul.obtenirNbObjetsSelectionne();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn bool FacadeEditeur::duplicationEstHorsTable() const
/// @brief Indique si la Duplication se produit hors table.
/// @return true si la duplication est hors table
///////////////////////////////////////////////////////////////////////////////
bool FacadeEditeur::duplicationEstHorsTable() const
{
	return duplicationHorsTable_;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::dupliquerSelection(int i, int j)
/// @param[in]  i : Cordonees du centre de duplication en i de la souris
/// @param[in]  j : Cordonees du centre de duplication en j de la souris
/// @return Aucune.
/// @remark : Duplique les objets selectionnes.
///////////////////////////////////////////////////////////////////////////////
void FacadeEditeur::dupliquerSelection(int i, int j)
{
	// Récupérer l'arbre de rendu de la FacadeModele
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	// Visiter l'arbre et faire la duplication.
	VisiteurDuplication* visiteur = new VisiteurDuplication();
	arbre->accepterVisiteur(visiteur);
	duplicationHorsTable_ = false;
	delete visiteur;
	deplacerSelection(i, j, i, j, true);
}


///////////////////////////////////////////////////////////////////////////////
/// @fn bool FacadeModele::supprimer()
/// @brief Parcours l'arbre et supprime les objets selectionnes.
/// @return La valeur du zoom courant
///////////////////////////////////////////////////////////////////////////////
void FacadeEditeur::supprimerSelection() const
{
	// Récupérer l'arbre de rendu de la FacadeModele
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	VisiteurSuppression* visiteur = new VisiteurSuppression();
	arbre->accepterVisiteur(visiteur);
	delete visiteur;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::deplacerSelection(int x1, int y1, int x2, int y2, bool duplication)
///	@remark deplace les noeuds selectionnes d'un deplacement calcule en coordonnees du monde
///	\remark a partir des points initiaux et terminaux dans les coordonnees d'affichage OpenGL
/// @param[in]  x1 : abcisse du point initial
/// @param[in]  y1 : ordonnee du point initial
/// @param[in]  x2 : abcisse du point initial
/// @param[in]  y2 : ordonnee du point initial
/// @param[in]  duplication : Logique de deplacement lors de l'etat de duplication
/// @return Aucune.
/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
///////////////////////////////////////////////////////////////////////////////
void FacadeEditeur::deplacerSelection(int x1, int y1, int x2, int y2, bool duplication)
{
	// Récupérer l'arbre de rendu de la FacadeModele
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	// Obtenir la vue de la FacadeModele
	vue::Vue* vue_ = FacadeModele::obtenirInstance()->obtenirVue();

	glm::dvec3 positionInitiale, positionFinale;
	vue_->convertirClotureAVirtuelle(x1, y1, positionInitiale);
	vue_->convertirClotureAVirtuelle(x2, y2, positionFinale);

	// Visiter l'arbre pour trouver les limites d'une boite
	// minX, minY, maxX, maxY
	VisiteurLimitesSelection VisLimSel;
	arbre->accepterVisiteur(&VisLimSel);
	glm::dvec3 pointMax{ VisLimSel.getXMax(), VisLimSel.getYMax(), 0 };
	glm::dvec3 pointMin{ VisLimSel.getXMin(), VisLimSel.getYMin(), 0 };

	// Logique de deplacement lors de l'etat de duplication
	if (duplication)
	{
		// Trouver le centre de masse de la selection
		VisiteurCentreDeMasse visCM;
		arbre->accepterVisiteur(&visCM);
		glm::dvec3 centreMasse = visCM.obtenirCentreDeMasse();

		// Calculer le delta des limites de la boite englobant la selection par rapport au centre de masse
		glm::dvec3 pointMaxDelta{ pointMax.x - centreMasse.x, pointMax.y - centreMasse.y, 0 };
		glm::dvec3 pointMinDelta{ pointMin.x - centreMasse.x, pointMin.y - centreMasse.y, 0 };

		// La selection suit le curseur de la souris en tout temps, mais s'affiche en rouge lorsqu'a 
		// l'exterieur de la table
		glm::dvec3 deplacement{ positionFinale - centreMasse };
		VisiteurDeplacement visDep(deplacement);
		visDep.setEstDuplication(true);

		if (estDansTable(positionFinale + pointMaxDelta) && estDansTable(positionFinale + pointMinDelta))
		{
			visDep.setEstDansLaTable(true);
			duplicationHorsTable_ = false;
		}
		else
			duplicationHorsTable_ = true;

		arbre->accepterVisiteur(&visDep);
	}

	//Logique de deplacement lors de l'etat de deplacement
	else
	{
		//calculer le deplacement
		glm::dvec3 deplacement{ positionFinale - positionInitiale };

		//le deplacement s'applique s'il ne fait pas sortir la selection en dehors de la table
		if (estDansTable(pointMax + deplacement) && estDansTable(pointMin + deplacement))
		{
			VisiteurDeplacement visDep(deplacement);
			arbre->accepterVisiteur(&visDep);
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @fn bool FacadeEditeur::estDansTable(glm::dvec3 pointDuMonde)
/// @param[in]  pointDuMonde : Point dont on veut verifier qu'il est dans la table
/// @return Aucune.
/// @remark : Verifie si le point du monde est dans la table.
///////////////////////////////////////////////////////////////////////////////
bool FacadeEditeur::estDansTable(glm::dvec3 pointDuMonde)
{
	if (interieurGaucheTableX < pointDuMonde.x && pointDuMonde.x < interieurDroitTableX
		&& interieurGaucheTableY < pointDuMonde.y && pointDuMonde.y <interieurDroitTableY)
		return true;

	return false;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::agrandirSelection(int x1, int y1, int x2, int y2)
///	@remark 	Fait un agrandissement des objets selectionnes.
///	\remark 	L'agrandissement est calcule en fonction du deplacement de (x1, y1) a (x2, y2)
/// @param[in]  x1 : abcisse du point initial
/// @param[in]  y1 : ordonnee du point initial
/// @param[in]  x2 : abcisse du point initial
/// @param[in]  y2 : ordonnee du point initial
/// @return Aucune.
/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
///////////////////////////////////////////////////////////////////////////////
void FacadeEditeur::agrandirSelection(int, int y1, int, int y2)
{
	// Récupérer l'arbre de rendu de la FacadeModele
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	double scale = glm::exp((y1 - y2) * glm::log(1.003)); // exp(b log(a)) = a^b
	// Pour agrandir on multiplie le scale courrant par 1.003 et ce une fois pour chaque deplacement en y
	// donc on multiplie par 1.003^(y1-y2).
	// Si (y1-y2) est negatif, ceci va nous faire diviser par 1.003, donc l'objet va rapetisser.

	// Au final, on multiplie le scale courrant par 1.003 une fois pour chaque deplacement elementaire vers le haut,
	// On divise par 1.003 pour chaque deplacement elementaire vers le bas.
	double distanceConstante = 1.0;
	double correctionZ = (1 - scale) * distanceConstante;

	VisiteurListeEnglobante visLE;
	arbre->accepterVisiteur(&visLE);

	for (const conteneur_boite_englobante& boite : visLE.obtenirListeEnglobante())
	{
		std::vector<glm::dvec3> pointsTransformes;
		glm::dvec3 position = boite.second->obtenirPositionRelative();
		if (boite.first.size() == 1)
		{
			double rayon = boite.first[0].x;

			pointsTransformes.push_back(position + scale *glm::dvec3{ rayon, 0, 0 });
			pointsTransformes.push_back(position + scale *glm::dvec3{ -rayon, 0, 0 });
			pointsTransformes.push_back(position + scale *glm::dvec3{ 0, rayon, 0 });
			pointsTransformes.push_back(position + scale *glm::dvec3{ 0, -rayon, 0 });
		}
		else
		{
			for (glm::dvec3 vecteur : boite.first)
			{
				pointsTransformes.push_back(position + scale * vecteur);
			}
		}
		for (glm::dvec3 point : pointsTransformes)
		{
			if (!estDansTable(point))
				return;
		}
	}

	VisiteurAgrandissement visAgr(glm::dvec3{ scale, scale, scale });
	arbre->accepterVisiteur(&visAgr);

	VisiteurDeplacement visDep(glm::dvec3{ 0, 0, correctionZ });
	arbre->accepterVisiteur(&visDep);
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::tournerSelectionSouris(int x1, int y1, int x2, int y2)
/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
///	@remark 	Fait une rotation des objets selectionnes autour de leur centre de masse.
///	\remark  	L'angle est calcule en fonction du deplacement de (x1, y1) a (x2, y2):
///	\remark 	Presentement, l'angle est proportionnel a (y1 - y2).
///	\remark 	Pour tester si la rotation est faisable, on prend tous les points des boites
///	\remark 	englobantes.  Si un seul de ces points, une fois transforme, n'est pas dans la 
///	\remark 	table, on ne fait pas la rotation.
/// @param[in]  x1 : abcisse du point initial
/// @param[in]  y1 : ordonnee du point initial
/// @param[in]  x2 : abcisse du point initial
/// @param[in]  y2 : ordonnee du point initial
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeEditeur::tournerSelection(int, int y1, int, int y2)
{
	// Récupérer l'arbre de rendu de la FacadeModele
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	// Visiter l'arbre pour trouver le centre de masse des noeuds selectionnes
	VisiteurCentreDeMasse visCM;
	arbre->accepterVisiteur(&visCM);
	glm::dvec3 centreRotation = visCM.obtenirCentreDeMasse();

	// On calcule l'angle de la rotation:
	double angle = (y2 - y1) / 3.0;
	double angleEnRadian = angle * utilitaire::PI_180;
	glm::dmat3 transform = glm::dmat3{ glm::dvec3{ cos(-angleEnRadian), -sin(-angleEnRadian), 0 },
		glm::dvec3{ sin(-angleEnRadian), cos(-angleEnRadian), 0 },
		glm::dvec3{ 0, 0, 1 } };

	// On decide si la rotation peut se faire
	bool onTourne = true;

	// Obtenir une liste des points englobants des noeud selectionnes
	VisiteurListeEnglobante visLE;
	arbre->accepterVisiteur(&visLE);

	for (const conteneur_boite_englobante& boite : visLE.obtenirListeEnglobante())
	{
		std::vector<glm::dvec3> pointsTransformes;
		glm::dvec3 nouvellePosition = centreRotation + transform * (boite.second->obtenirPositionRelative() - centreRotation);
		if (boite.first.size() == 1)
		{
			double rayon = boite.first[0].x;

			pointsTransformes.push_back(nouvellePosition + glm::dvec3{ rayon, 0, 0 });
			pointsTransformes.push_back(nouvellePosition + glm::dvec3{ -rayon, 0, 0 });
			pointsTransformes.push_back(nouvellePosition + glm::dvec3{ 0, rayon, 0 });
			pointsTransformes.push_back(nouvellePosition + glm::dvec3{ 0, -rayon, 0 });
		}
		else
		{
			for (glm::dvec3 vecteur : boite.first)
			{
				pointsTransformes.push_back(nouvellePosition + transform * vecteur);
			}
		}
		for (glm::dvec3 point : pointsTransformes)
		{
			if (!estDansTable(point))
				return;
		}
	}

	// Visiter l'arbre et faire la rotation.
	if (onTourne)
	{
		VisiteurRotationPoint visSP(glm::dvec3{ 0, 0, angle }, centreRotation);
		arbre->accepterVisiteur(&visSP);
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::positionnerMur(int originX, int originY,int x1, int y1, int x2, int y2, NoeudAbstrait* noeud)
/// @param[in]  originX : Position en X ou le bouton a ete appuye
/// @param[in]  originY : Position en Y ou le bouton a ete appuye
/// @param[in]  x1 : Position en X precedant un deplacement de la souris
/// @param[in]  y1 : Position en Y precedant un deplacement de la souris
/// @param[in]  x2 : Position en X apres un deplacement de la souris (position actuelle de la souris)
/// @param[in]  y2 : Position en X apres un deplacement de la souris (position actuelle de la souris)
/// @param[in]  noeud : Noeud sur le quel appliquer les transformations
/// @return Aucune.
///	@remark	Positionne un mur pour qu'il soit une ligne entre ou on a appuye le bouton de gauche de la 
///	\remark	souris et la position actuelle de la souris.
///	\remark	La methode verifie aussi la boite englobante du mur pour ne pas qu'il depasse de la table.
///////////////////////////////////////////////////////////////////////////////
void FacadeEditeur::positionnerMur(int originX, int originY, int, int, int x2, int y2, NoeudAbstrait* noeud) const
{
	// Obtenir la vue de la FacadeModele
	vue::Vue* vue_ = FacadeModele::obtenirInstance()->obtenirVue();

	glm::dvec3 positionOriginale;
	glm::dvec3 positionFinale;

	vue_->convertirClotureAVirtuelle(originX, originY, positionOriginale);
	vue_->convertirClotureAVirtuelle(x2, y2, positionFinale);

	glm::dvec3 vecteur = positionFinale - positionOriginale;

	// Proprietes a appliquer:
	glm::dvec3 scaleFinal{ 1, 1, 1 };
	glm::dvec3 angles{ 0, 0, 0 };
	glm::dvec3 position = positionOriginale;

	double angleRadian = 0.0;

	// Les calculs sont fait seulement si la souris est assez loin de ou on a cree le noeud.
	if (glm::length(vecteur) > 0.1)
	{
		// CALCUL DE L'ANGLE
		// =================
		glm::dvec3 axe{ 0, 1, 0 }; // On va travailler avec l'angle entre le vecteur allant de origin a la position du curseur, et l'axe Y.
		glm::dvec3 produitVectoriel = glm::cross(axe, vecteur);
		double sinAngle = glm::length(produitVectoriel) / glm::length(axe) / glm::length(vecteur);
		angleRadian = produitVectoriel.z > 0 ? asin(sinAngle) : -asin(sinAngle);

		// Prendre l'angle complementaire si on est en dessous de l'axe X.
		if (vecteur.y < 0)
			angleRadian = utilitaire::PI - angleRadian;// A passer en parametre a assignerRotation

		angles = glm::dvec3{ 0, 0, 360.0 / 2.0 / utilitaire::PI * angleRadian };
	}
	// Calcul de la translation
	// ========================
	// position = positionOriginale + vecteur / 2.0; // Le centre du mur est a mi-chemin entre origin et le point du curseur. 
	if (glm::length(vecteur) > .1)
		position = positionOriginale + vecteur / 2.0;
	else if (glm::length(vecteur) != 0)
		position = positionOriginale + 8.0 *glm::normalize(vecteur); // 

	glm::dvec3 boite[4];
	noeud->obtenirBoiteModele(boite[0], boite[1], boite[2], boite[3]);
	double longueurMur = boite[2].x - boite[0].x;
	if (glm::length(vecteur) > 0.1)
	{
		// Calcul du scale
		// ===============
		double scale = glm::length(vecteur) / longueurMur; //  16.0 est la longueur originale du mur. 
		scaleFinal = glm::dvec3{ 1, scale, 1 };
	}
	else
		scaleFinal = glm::dvec3{ 1, 0.1, 1 };


	// Tester la transformation
	// ========================
	glm::dmat3 echelle = glm::dmat3{ glm::dvec3{ 1, 0, 0.0 },
		glm::dvec3{ 0, scaleFinal.y, 0.0f },
		glm::dvec3{ 0.0, 0.0, 1 } };

	glm::dmat3 rotation = glm::dmat3{ glm::dvec3{ cos(angleRadian), sin(angleRadian), 0.0 },
		glm::dvec3{ -sin(angleRadian), cos(angleRadian), 0.0f },
		glm::dvec3{ 0.0, 0.0, 1.0 } };
	glm::dvec3 pointATester;
	for (int i = 0; i < 4; i++)
	{
		pointATester = position + rotation * (echelle * boite[i]);
		if (!obtenirInstance()->estDansTable(pointATester))
		{
			return;
		}
	}

	// Si on s'est rendu ici, c'est qu'on peut faire l'assignation des proprietes.
	noeud->assignerEchelle(scaleFinal);
	noeud->assignerRotationHard(angles);
	noeud->assignerPositionRelative(position);
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::sourisEstSurObjet(int i, int j, int hauteur, int, bool& estSelectionne)
/// @brief Cette fonction verifie si la souris est situe sur un objet
/// @param[in] i : Position souris i
/// @param[in] j : Position souris j
/// @param[in] hauteur : Hauteur de la fenetre
/// @param[in] largeur : Largeur de la fenetre
/// @param[in] estSelectionne : Si l'element est selectionne
/// @return bool, true si la souris est situe sur un objet
////////////////////////////////////////////////////////////////////////
bool FacadeEditeur::sourisEstSurObjet(int i, int j, int hauteur, int, bool& estSelectionne) const
{
	// Obtenir la vue de la FacadeModele
	vue::Vue* vue = FacadeModele::obtenirInstance()->obtenirVue();

	// Obtenir la vue de la FacadeModele
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	glm::dvec3 pointDansLeMonde;
	vue->convertirClotureAVirtuelle(i, j, pointDansLeMonde);

	int valeurStencil = 0;
	glReadPixels(i, hauteur - j, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &valeurStencil);

	bool estSurObjet = false;
	NoeudAbstrait* table = arbre->chercher(0);
	for (unsigned int counter = 0; counter < table->obtenirNombreEnfants(); counter++)
	{
		NoeudAbstrait* noeud = table->chercher(counter);
		if (noeud->getNumero() == valeurStencil)
		{
			if (noeud->estSelectionne())
				estSelectionne = true;
			else
				estSelectionne = false;

			estSurObjet = true;

			break;
		}
	}

	return estSurObjet;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn bool FacadeEditeur::verifierCliqueDansTable(int x, int y)
///	@remark 	Verifie si le point du monde correspondant a (x,y) est dans la table de
///	\remark 	facon empirique ou heuristique.
/// @param[in]  x : abcisse du point clique
/// @param[in]  y : ordonnee du point clique
/// @return Aucune.
/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
///////////////////////////////////////////////////////////////////////////////
bool FacadeEditeur::verifierCliqueDansTable(int x, int y)
{
	glm::dvec3 positionDansLeMonde;

	// Obtenir la vue de la FacadeModele
	vue::Vue* vue_ = FacadeModele::obtenirInstance()->obtenirVue();

	vue_->convertirClotureAVirtuelle(x, y, positionDansLeMonde);
	if (interieurGaucheTableX < positionDansLeMonde.x && positionDansLeMonde.x < interieurDroitTableX
		&& interieurGaucheTableY < positionDansLeMonde.y && positionDansLeMonde.y < interieurDroitTableY)
		return true;

	return false;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeEditeur::obtenirNombreSelection()
/// @remark Cette fonction retourne le nombre d'objets selectionnés
/// @return int, le nombre de noeuds qui sont selectionnes
////////////////////////////////////////////////////////////////////////
int FacadeEditeur::obtenirNombreSelection()
{
	/// Récupérer l'arbre de rendu
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	return arbre->obtenirNombreSelectionne();
}