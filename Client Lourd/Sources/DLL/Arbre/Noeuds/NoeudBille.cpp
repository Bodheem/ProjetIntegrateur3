///////////////////////////////////////////////////////////////////////////
/// @file NoeudBille.cpp
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#include "NoeudBille.h"
#include "FacadeModele.h"
#include "../../Sound/ControleurSon.h"

#include <GL/gl.h>
#include <cmath>

#include "Modele3D.h"
#include "NoeudComposite.h"
#include "OpenGL_Storage/ModeleStorage_Liste.h"
#include "glm\gtx\norm.hpp"


////////////////////////////////////////////////////////////////////////
/// @fn NoeudBille::NoeudBille(const std::string& typeNoeud)
/// @brief Ce constructeur ne fait qu'appeler la version de la classe et base
///		   et donner des valeurs par defaut aux variables membres.
/// @param[in] typeNoeud :  le type du noeud a creer.
/// @return Aucune (constructeur).
////////////////////////////////////////////////////////////////////////
NoeudBille::NoeudBille(const std::string& typeNoeud)
	: NoeudComposite{ typeNoeud }
{
	vitesse_ = VITESSE_INITIALE_NORUD_BILLE;
	masse_ = MASSE_NOEUD_BILLE;
	constanteDeFrottement_ = FROTTEMENT_NOEUD_BILLE;
	//SoundControl->bouclerSon("rolling", true);
	FacadeModele::obtenirInstance()->obtenirControleurSon()->bouclerSon("rolling", true);
	posZinitial = 0;
	posZfinal = 0;
}


////////////////////////////////////////////////////////////////////////
/// @fn NoeudBille::~NoeudBille()
/// @brief Ce destructeur desallouee la liste d'affichage du noeud.
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
NoeudBille::~NoeudBille()
{
	auto soundController = FacadeModele::obtenirInstance()->obtenirControleurSon();

	soundController->jouerSon("rolling", true);
	soundController->ajusterVolume("rolling", 0);
	soundController->accelererSon("rolling", 0);
}


////////////////////////////////////////////////////////////////////////
/// @fn void NoeudBille::afficherConcret() const
/// @brief Cette fonction effectue le veritable rendu de l'objet.
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void NoeudBille::afficherConcret() const
{
	NoeudComposite::afficherConcret();
	// Sauvegarde de la matrice.
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	NoeudAbstrait::appliquerAfficher();
	glTranslatef(0.0, -10, 0.0); // Il faudrait changer le modele
	liste_->dessiner();
	glPopAttrib();
	glPopMatrix();
	// Restauration de la matrice.
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::animer(float temps)
///
/// Le travail fait dans cette methode est comme suit,
///  - Calculer la somme des forces agissant sur la bille 
///  - Calculer la nouvelle vitesse
///		- Calculer la vitesse apres la collision (presentement juste la detection)
///		- Calculer la nouvelle vitesse en appliquant les forces
///  - Calculer la nouvelle position a partir de la vitesse apres la collision.
///  - Changer l'oritentation de la bille pour faire comme si elle roule (TODO).
///
/// @param[in] temps : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::animer(float temps) // rajouter des parametres ou une fonction animerCollision(float temps, detailCollision detail)
{
	auto controleurSon = FacadeModele::obtenirInstance()->obtenirControleurSon();

	if (enCreation_ || !animer_ || timerMove_ < TIME_IDLE_NOEUD_BILLE || temps > EPSILON_ANIMATION_NOEUD_COMPOSITE)
		controleurSon->jouerSon("rolling", true);

	if (temps > EPSILON_ANIMATION_NOEUD_COMPOSITE)
	{
		return;
	}

	for (NoeudAbstrait * enfant : enfants_){
		enfant->animer(temps);
	}
	glm::dvec3 coinMinAvecScale = boite_.coinMin * scale_.z;

	if (positionRelative_.z >  abs(coinMinAvecScale.z))
		positionRelative_.z = HAUTEUR_TABLE_NOEUD_COMPOSITE + abs(coinMinAvecScale.z);

	if (timerMove_ < TIME_IDLE_NOEUD_BILLE)
	{
		glm::dvec3 positionRelative = positionRelative_;
		NoeudComposite::animer(temps);
		positionRelative_ = positionRelative;
	}

	if (enCreation_)
	{
		posZinitial = -abs(boite_.coinMax.z * scale_.z);
		posZfinal = 2 * abs(boite_.coinMax.z * scale_.z) + abs(boite_.coinMin.z * scale_.z) + HAUTEUR_TABLE_NOEUD_COMPOSITE;
		positionRelative_.z = posZinitial;
		enCreation_ = false;
	}

	if (!animer_)
		return;

	// Somme des forces agissant sur les particules.
	// =============================================

	if (obtenirParent()->obtenirParent()->getEnfant(1)->obtenirAnimer())
	{
		return;
	}

	if (timerMove_ < TIME_IDLE_NOEUD_BILLE)
	{
		positionRelative_.z += temps * posZfinal / (TIME_IDLE_NOEUD_BILLE);
		timerMove_ += temps;
		return;
	}

	glm::dvec3 forceFrottement{ 0, 0, 0 };
	if (glm::length(vitesse_) > utilitaire::EPSILON)
		forceFrottement = -constanteDeFrottement_ * glm::normalize(vitesse_);
	glm::dvec3 forceTotale = forceFrottement + GRAVITE_NOEUD_BILLE + forcesExternes_;
	forceTotale.z = 0;
	glm::dvec3 acceleration = forceTotale;
	forceTotale *= masse_;

	if (glm::length(vitesse_) > VITESSE_MAX_NOEUD_BILLE)
	{
		vitesse_ = VITESSE_MAX_NOEUD_BILLE * glm::normalize(vitesse_); // Meme direction, mais module ramene a VITESSE_MAX
	}

	// Calcul de la nouvelle position 
	// ==============================
	glm::dvec3 nouvellePosition = positionRelative_ + (double)temps * vitesse_;
	
	// Calcul de la nouvelle vitesse. 
	// =============================

	glm::dvec3 nouvelleVitesse = vitesse_ + (double)temps * acceleration;

	if (glm::length(nouvelleVitesse) > VITESSE_MAX_NOEUD_BILLE)
	{
		nouvelleVitesse = VITESSE_MAX_NOEUD_BILLE * glm::normalize(nouvelleVitesse);// Meme direction, mais module ramene a VITESSE_MAX
	}
	// Calcul de la rotation
	// =====================
	// C'est pas la bonne facon de calculer la rotation a appliquer a la boule,
	// C'est pas un bug, j'ai just pas encore trouve la bonne facon de le faire.
	double constanteACalculer{ 5 }; // Depend du rayon de la boule, mais avec 0.1, ca parait deja bien.
	glm::dvec3 rotation{ 0, 0, 0 };
	rotation.x = constanteACalculer * -vitesse_.y * temps;
	rotation.y = constanteACalculer * vitesse_.x * temps;

	// Assignation des nouvelles valeurs.
	assignerRotation(rotation);
	positionRelative_ = nouvellePosition;
	vitesse_ = nouvelleVitesse;

	if (positionRelative_.z >  abs(coinMinAvecScale.z))
		positionRelative_.z = abs(coinMinAvecScale.z);

	if (leSonJoue == false)
	{
		controleurSon->jouerSon("rolling");
		leSonJoue = true;
	}

	double vitesseSon = (SOUDN_SPEED_UP_MAX * abs(glm::length(vitesse_))) / VITESSE_MAX_NOEUD_BILLE;
	glm::length(vitesse_);

	//SoundControl->accelererSon("rolling", (float)vitesseSon);
	FacadeModele::obtenirInstance()->obtenirControleurSon()->accelererSon("rolling", static_cast<float>(vitesseSon));

	if (glm::length(rotation_) > 10)
		controleurSon->muteSound("rolling", true);
	else
		controleurSon->muteSound("rolling", false);
}


////////////////////////////////////////////////////////////////////////
/// @fn bool NoeudBille::accepterVisiteur(VisiteurAbstrait* vis)
/// @brief Cette fonction appelle la methode traiter du visiteur.
/// @param[in] vis : Le visiteur a traiter
/// @return reussi (TRUE)
////////////////////////////////////////////////////////////////////////
bool NoeudBille::accepterVisiteur(VisiteurAbstrait* vis)
{
	bool reussi = false;

	if (vis->traiter(this))
		reussi = true;

	return reussi;
}


////////////////////////////////////////////////////////////////////////
/// @fn void NoeudBille::setDebug(bool debug)
/// @brief Cette fonction change al valeur du mode debug
/// @param[in] debug : La valeur du mode debug a assigner
/// @return Aucun.
////////////////////////////////////////////////////////////////////////
void NoeudBille::setDebug(bool debug)
{
	debug_ = debug;
}


////////////////////////////////////////////////////////////////////////
/// @fn void NoeudBille::setSpotLight(bool debug)
/// @brief Cette fonction change la valeur du mode spotLight
/// @param[in] debug : La valeur du mode debug a assigner pour le spotLight
/// @return Aucun.
////////////////////////////////////////////////////////////////////////
void NoeudBille::setSpotLight(bool debug)
{
	spotLight_ = debug;
}


////////////////////////////////////////////////////////////////////////
/// @fn void NoeudBille::afficherVitesse(glm::dvec3 nouvelleVitesse)
/// @brief Affiche la nouvelle vitesse donnee a une bille apres une collision.
/// @param[in] nouvelleVitesse : La valeur de la vitesse a imprimer
/// @return aucun
////////////////////////////////////////////////////////////////////////
void NoeudBille::afficherVitesse(glm::dvec3 nouvelleVitesse) const
{
	if (debug_)
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		std::cout << std::fixed << std::setw(2) << std::setprecision(2) << time.wHour << ":"
			<< std::fixed << std::setfill('0') << std::setw(2) << std::setprecision(2) << time.wMinute << ":"
			<< std::fixed << std::setfill('0') << std::setw(2) << std::setprecision(2) << time.wSecond << ":"
			<< std::fixed << std::setfill('0') << std::setw(3) << std::setprecision(3) << time.wMilliseconds;

		std::cout << std::fixed << std::setfill('0') << std::setw(2) << " - Vitesse " << glm::length(nouvelleVitesse) << std::endl;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<glm::dvec3> NoeudBille::obtenirVecteursEnglobants()
///
/// La boite englobante d'un butoir circulaire, c'est un rayon.
/// Pour etre conforme avec les boites englobantes des autres noeuds, 
/// on retourne quand meme un vector<glm::dvec3> mais avec un seul element
/// dont le x contient le rayon.
///
/// @return Un vecteur<glm::dvec3> dont le seul element a le rayon de l'objet
/// comme premiere coordonnee.
/// 
////////////////////////////////////////////////////////////////////////
std::vector<glm::dvec3> NoeudBille::obtenirVecteursEnglobants()
{
	double rayonModele = (boite_.coinMax.x - boite_.coinMin.x) / 2.0;
	return{ glm::dvec3{ rayonModele * scale_.x, 0, 0 } };
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudBille::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float facteurRebond)
///
/// @brief Cette fonction effectue la reaction a la collision de la bille sur 
/// l'objet courant. Cette fonction est a reimplementer si on veut autre 
/// chose qu'un rebondissement ordinaire.
///
/// @param[in] details Objet contenant les details de la collision a traiter
/// @param bille Objet modifie par la collision
/// @param[in] facteurRebond Facteur par lequel la vitesse normale de la bille sera multipliee
///
/// @return details contient l'information sur la collision de la bille avec *this.
///
////////////////////////////////////////////////////////////////////////
void NoeudBille::traiterCollisions(aidecollision::DetailsCollision details, NoeudAbstrait* bille, float)
{

	// pour avoir l'ancien comportement exactement, simplement decommenter la ligne suivante
	// return NoeudAbstrait::traiterCollisions(details, bille, facteurRebond);

	// Pour alleger les formules, A == this et B == bille
	// vA, vB les vecteurs vitesse initiaux
	// vAn et vAt, les coefficients normaux et tangents respectivement
	// wAn et wAt, les coefficients apres la collision.
	glm::dvec3 vA = this->obtenirVitesse(); vA.z = 0;
	glm::dvec3 vB = bille->obtenirVitesse(); vB.z = 0;

	// Changer la masse selon le scale. 
	double mA = this->obtenirAgrandissement().x * MASSE_NOEUD_BILLE;
	double mB = bille->obtenirAgrandissement().x * MASSE_NOEUD_BILLE;

	glm::dvec3 N = glm::normalize(this->obtenirPositionRelative() - bille->obtenirPositionRelative());
	N.z = 0; // Juste pour etre sur
	glm::dvec3 T = glm::dvec3{ -N.y, N.x, 0 };

	// Composantes normales initiales
	double vAn = glm::dot(vA, N);
	double vBn = glm::dot(vB, N);

	// Composantes tangentielles intitiales (et finales)
	double vAt = glm::dot(vA, T);
	double vBt = glm::dot(vB, T);

	double wAn = (vAn * (mA - mB) + 2 * mB*vBn) / (mA + mB);
	double wBn = (vBn * (mB - mA) + 2 * mA*vAn) / (mA + mB);

	// wAt = vAt;
	// wBt = vBt;

	this->assignerVitesse(wAn * N + vAt * T); 
	bille->assignerVitesse(wBn * N + vBt * T);

	this->assignerPositionRelative(this->obtenirPositionRelative() - 0.6*details.enfoncement*details.direction);
	bille->assignerPositionRelative(bille->obtenirPositionRelative() + 0.6*details.enfoncement*details.direction);
}