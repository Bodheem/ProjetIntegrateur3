//////////////////////////////////////////////////////////////////////////////
/// @file QuadTree.h
/// @author Maxime Gauthier-Farley
/// @date 2016-01-12
///
/// @ingroup QuadTree
//////////////////////////////////////////////////////////////////////////////
#ifndef __QUADTREE_QUADTREE_H__
#define __QUADTREE_QUADTREE_H__

#include "glm\glm.hpp"
#include "utilitaire.h"
#include "AideCollision.h"
#include <list>
#include <string>
#include <vector>

class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class QuadTree
/// @brief Classe qui regroupe les noeuds dans un arbre sous-divisé, qui permet
/// de réduire le nombre d'analyses de physique requises.
/// Inspiration majeure:
/// http://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374
///
/// @author Maxime Gauthier-Farley
/// @date 2016-01-12
///////////////////////////////////////////////////////////////////////////
class QuadTree
{
public:
	/// Constructeur
	QuadTree(double x, double y, double dx, double dy);
	/// Destructeur
	~QuadTree();
	/// Vide récursivement l'arbre
	void clear();
	/// Ajoute un nouvel objet
	void insererNoeud(NoeudAbstrait* noeud);
	/// Retourne les objets qui peuvent entrer en collision avec l'objet fourni
	std::list<NoeudAbstrait*> detecterCollision(NoeudAbstrait* noeud, std::vector<NoeudAbstrait*> listeBalles);

	/// Debugging: Affiche dans la console le QuadTree
	void afficherQuadTree();

private:
	/// Constructeur privé pour créer les sous-arbres
	QuadTree(int niveau, int index, double x, double y, double dx, double dy);
	/// Retourne l'index d'un noeud à ajouter
	int getIndex(NoeudAbstrait* noeud);
	/// Divise la feuille de l'arbre en 4 sous-feuilles
	void split();
	/// Detection interne récursive de collision
	void detecterCollision(NoeudAbstrait* noeud, std::list<NoeudAbstrait*>* liste);
	/// Méthode interne d'affichage de l'arbre
	void affichageInterne();

	/// Niveau de profondeur de la branche de l'arbre
	int niveau_;
	/// Index du quadrant de la feuille. -1 si le sommet de l'arbre
	int index_;
	/// Liste de noeuds contenus dans cette branche de l'arbre
	std::list<NoeudAbstrait*> listeNoeuds_;
	/// Bornes de la zone actuelle de l'arbre
	double x_, y_, dx_, dy_;
	/// Feuilles de la branche actuelle
	std::list<QuadTree*> feuilles_;
	/// Nombre maximal d'objets avant que le noeud se sépare
	int MAX_OBJECTS = 3;
	/// Nombre maximal de profondeur de l'arbre
	int MAX_LEVELS = 5;
};

#endif // __QUADTREE_QUADTREE_H__

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////