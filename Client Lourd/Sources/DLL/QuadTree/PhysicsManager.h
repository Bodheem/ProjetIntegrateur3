///////////////////////////////////////////////////////////////////////////////
/// @file PhysicsManager.h
/// @author The New Ballers
/// @date 2016-01-12
/// @version 1.0
///
/// @ingroup QuadTree
///////////////////////////////////////////////////////////////////////////////
#ifndef __QUADTREE_PHYSICSMANAGER_H__
#define __QUADTREE_PHYSICSMANAGER_H__

#include <vector>

class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class PhysicsManager
/// @brief Classe pour la gestion de la physique.
///
/// @author The New Ballers
/// @date 2016-01-13
/// @ingroup Sauvegarde
///////////////////////////////////////////////////////////////////////////
class PhysicsManager
{
public:

	/// Constructeur
	PhysicsManager();

	/// Destructeur
	~PhysicsManager();

	/// Traiter les collisions entres les tous objets
	void traiterCollisions(float temps);

	/// Mettre a jour les forces externes
	void updateForcesExternes();

	/// Mettre a jour la liste des noeuds de la zone de jeu
	void mettreAJourListeNoeuds();

	/// Mettre a jour la liste des billes de la zone de jeu
	void mettreAJourListeBillesEtNoeuds();

	/// Obtenir la liste des billes
	std::vector<NoeudAbstrait*> obtenirListeBilles() const;

private:

	/// La liste des billes dans la zone de jeu
	std::vector<NoeudAbstrait*> listeBilles_;

	/// La liste des portails dans la zone de jeu
	std::vector<NoeudAbstrait*> listePortails_;

	/// La liste des noeuds qu'on doit vérifier pour les collisions
	std::vector<NoeudAbstrait*> listeNoeuds_;
};

#endif //__QUADTREE_PHYSICSMANAGER_H__