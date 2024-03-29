///////////////////////////////////////////////////////////////////////////
/// @file NoeudTrou.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////

#ifndef  __ARBRE_NOEUDS_NOEUDTROU_H__
#define  __ARBRE_NOEUDS_NOEUDTROU_H__

#include "NoeudComposite.h"
#include "Gl/gl.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudTrou
/// @brief Classe qui represente un trou.
///
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Noeud
///////////////////////////////////////////////////////////////////////////
class NoeudTrou : public NoeudComposite
{
public:
	/// Constructeur
	NoeudTrou(const std::string& typeNoeud);

	/// Destructeur 
	~NoeudTrou();

	/// Surchage de la methode qui affiche l'objet.
	virtual void afficherConcret() const;

	/// Surchage de la methode qui anime l'objet.
	virtual void animer(float temps);

	/// Accepte un visiteur.
	virtual bool accepterVisiteur(VisiteurAbstrait* vis);

	/// Redefinition de boite englobante pour objet circulaire
	virtual std::vector<glm::dvec3> obtenirVecteursEnglobants();

	/// Pour le traitement logique des collisions
	virtual void traiterCollisions(aidecollision::DetailsCollision, NoeudAbstrait* bille, float facteurRebond = 1);
};

#endif // __ARBRE_NOEUDS_NOEUDTROU_H__