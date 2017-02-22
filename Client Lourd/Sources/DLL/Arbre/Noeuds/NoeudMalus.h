///////////////////////////////////////////////////////////////////////////
/// @file NoeudMalus.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef __ARBRES_NOEUDS_NOEUDMALUS_H__
#define __ARBRES_NOEUDS_NOEUDMALUS_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudMalus
/// @brief Classe qui represente un malus.
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudMalus : public NoeudComposite
{
public:
	/// Constructeur
	NoeudMalus(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudMalus();

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Pour le traitement logique des collisions
	virtual void traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille, float facteurRebond = 1);

	/// Pour la detections des collisions
	virtual aidecollision::DetailsCollision detecterCollisions(NoeudAbstrait* noeud);

private:

	// Liste des effets pour le malus
	std::vector<std::string> effects_;

	/// Angle de rotation.
	float angleRotation_{ 0.f };

	/// Pour savoir c'est quand la derniere fois qu'on a fait disparaitre l'objet
	std::clock_t lastDisapear_;
};

#endif // __ARBRES_NOEUDS_NOEUDMALUS_H__