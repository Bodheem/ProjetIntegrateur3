//////////////////////////////////////////////////////////////////////////////
/// @file QuadTree.cpp
/// @author Maxime Gauthier-Farley
/// @date 2015-03-04
///	
/// @ingroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#include "QuadTree.h"
#include <iostream>
#include "AideGL.h"
#include "ArbreRenduINF2990.h"
#include "NoeudAbstrait.h"
#include "NoeudPortail.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn QuadTree::QuadTree(int niveau, int x, int y, int dx, int dy)
///
/// Constructeur
///
/// @param[in]  Paramètres fournis
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
QuadTree::QuadTree(double x, double y, double dx, double dy)
{
	niveau_ = 0;
	x_ = x;
	y_ = y;
	dx_ = dx;
	dy_ = dy;
	index_ = -1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn QuadTree::QuadTree(int niveau, int index, int x, int y, int dx, int dy)
///
/// Constructeur privé pour les feuilles
///
/// @param[in]  Paramètres fournis
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
QuadTree::QuadTree(int niveau, int index, double x, double y, double dx, double dy)
{
	niveau_ = niveau;
	x_ = x;
	y_ = y;
	dx_ = dx;
	dy_ = dy;
	index_ = index;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn QuadTree::~QuadTree()
///
/// Destructeur
///
/// @param[in]  Paramètres fournis
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
QuadTree::~QuadTree()
{
	clear();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::clear()
///
/// Vide récursivement l'arbre des noeuds et sous-branches
///
/// @param[in]  Aucun
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void QuadTree::clear()
{
	while (!feuilles_.empty())
	{
		QuadTree* feuille = feuilles_.back();
		feuille->clear();
		feuilles_.pop_back();
		delete feuille;
	}

	listeNoeuds_.clear();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::split()
///
/// Sépare l'arbre en quatre sous-régions
///
/// @param[in]  Aucun
///
/// @return Aucun
///
///				 2 | 3
///				-------	
///			   . 1 | 0	
///			   ^ x, y
///
////////////////////////////////////////////////////////////////////////
void QuadTree::split()
{
	double x = x_;
	double y = y_;
	double dx = dx_ / 2;
	double dy = dy_ / 2;
	feuilles_.push_back(new QuadTree(niveau_ + 1, 0, x + dx, y, dx, dy));
	feuilles_.push_back(new QuadTree(niveau_ + 1, 1, x, y, dx, dy));
	feuilles_.push_back(new QuadTree(niveau_ + 1, 2, x, y + dy, dx, dy));
	feuilles_.push_back(new QuadTree(niveau_ + 1, 3, x + dx, y + dy, dx, dy));
}


////////////////////////////////////////////////////////////////////////
///
/// @fn int QuadTree::getIndex(NoeudAbstrait* n)
///
/// Retourne l'index de la sous-section dans laquelle on peut insérer le noeud n
///
/// @param[in]  NoeudAbstrait* n : noeud à insérer présentement
///
/// @return index: l'index de la sous section
///				 2 | 3
///				-------			ou -1 si l'objet doit être
///				 1 | 0			dans la section parente
///
////////////////////////////////////////////////////////////////////////
int QuadTree::getIndex(NoeudAbstrait* n)
{
	// Index à retourner
	int index = -1;

	// Centre de la feuille actuelle
	double pointCentralX = x_ + dx_ / 2;
	double pointCentralY = y_ + dy_ / 2;

	// Centre de l'objet
	glm::dvec3 centreObjet = n->obtenirPositionRelative();

	// Calcul de la largeur maximale de l'objet
	glm::dvec3 xMin, xMax, yMin, yMax, zMin, zMax;
	utilitaire::obtenirPointsExtremes( n->obtenirModele()->obtenirNoeudRacine(), xMin, xMax, yMin, yMax, zMin, zMax);
	double largeurObjetMax = utilitaire::ABS((float)(xMin.x - xMax.x));
	double i = utilitaire::ABS((float)(yMin.y - yMax.y));
	if (i > largeurObjetMax)
		largeurObjetMax = i;
	i = utilitaire::ABS((float)(zMin.z - zMax.z));
	if (i > largeurObjetMax)
		largeurObjetMax = i;

	// On adapte la largeur selon l'echelle actuelle de l'objet
	glm::dvec3 agg = n->obtenirAgrandissement();
	largeurObjetMax *= (agg.x >= agg.y && agg.x >= agg.z) ? agg.x : ( (agg.y >= agg.x && agg.y >= agg.z) ? agg.y : agg.z);
	
	// Certains types d'objets ne sont pas centrés, peut être
	std::string type = n->obtenirType(); 
	/*
	if (type == ArbreRenduPinball::NOM_PALETTEDROITE_J1 ||
		type == ArbreRenduPinball::NOM_PALETTEDROITE_J2 ||
		type == ArbreRenduPinball::NOM_PALETTEGAUCHE_J1 ||
		type == ArbreRenduPinball::NOM_PALETTEGAUCHE_J2
		)
		largeurObjetMax;
	else
		largeurObjetMax /= 2;
		*/
	// Zone d'attraction d'un portail
	if (type == ArbreRenduINF2990::NOM_PORTAIL)
		largeurObjetMax *= 3;

	// On détermine si l'objet entre dans l'un des quadrants
	//				 2 | 3	
	//				---+---	
	//				 1 | 0	
	bool quadHaut = 
		centreObjet.y - largeurObjetMax > pointCentralY &&
		centreObjet.y + largeurObjetMax < pointCentralY + dy_ / 2;
	bool quadBas =
		centreObjet.y - largeurObjetMax > 0 &&
		centreObjet.y + largeurObjetMax < pointCentralY;
	bool quadDroit =
		centreObjet.x - largeurObjetMax > pointCentralX &&
		centreObjet.x + largeurObjetMax < pointCentralX + dx_ / 2;
	bool quadGauche =
		centreObjet.x - largeurObjetMax > 0 &&
		centreObjet.x + largeurObjetMax < pointCentralX;
	if (quadHaut)
	{
		if (quadDroit)
			index = 3;
		if (quadGauche)
			index = 0;
	}
	if (quadBas)
	{
		if (quadDroit)
			index = 0;
		if (quadGauche)
			index = 1;
	}
	return index;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::insererNoeud(NoeudAbstrait* n)
///
/// Permet d'insérer récursivement un nouveau noeud dans l'arbre
/// Il vérifie d'abbord s'il y a des sous-feuilles à la feuille actuelle
/// S'il y en a, il essaie récursivement de les insérer
/// Sinon, il les insere dans la feuille actuelle
/// Ensuite, il vérifie s'il peut se séparer en sous-feuilles et 
/// envoie ses noeuds dans les sous-feuilles où elles entrent.
///
/// @param[in]  NoeudAbstrait* n : noeud à insérer
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void QuadTree::insererNoeud(NoeudAbstrait* noeud)
{
	if (noeud->obtenirType() == ArbreRenduINF2990::NOM_VIDE)
		return;
	if (noeud->obtenirType() == ArbreRenduINF2990::NOM_PORTAILTORUS)
		return;
	if (noeud->obtenirType() == ArbreRenduINF2990::NOM_GENERATEURBILLE)
		return;
	// Si l'arbre est deja splité
	if (!feuilles_.empty())
	{
		int index = getIndex(noeud);
		// S'il entre dans un des sous-arbres
		if (index != -1)
		{
			auto it = feuilles_.begin();
			for (int i = 0; i < index; i++)
				it++;
			(*it)->insererNoeud(noeud);
			return ;
		}
	}

	// Insérer dans la feuille actuelle
	listeNoeuds_.push_back(noeud);

	if (listeNoeuds_.size() > MAX_OBJECTS && niveau_ < MAX_LEVELS)
	{
		if (feuilles_.empty())
		{
			split();
		}

		int i = (int)listeNoeuds_.size();
		while (i > 0)
		{
			NoeudAbstrait* n = listeNoeuds_.front();
			listeNoeuds_.pop_front();
			int index = getIndex(n);
			if (index != -1)
			{
				auto it = feuilles_.begin();
				for (int i = 0; i < index; i++)
					it++;
				(*it)->insererNoeud(n);
				return;
			}
			else
			{
				listeNoeuds_.push_back(n);
			}
			i--;
		}
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn std::list<PolygoneCollision*> QuadTree::detecterCollision(NoeudAbstrait* noeud, std::vector<NoeudAbstrait*> listeBalles)
///
/// Fonction d'appel externe de détection de la collision. Fournit un noeud
/// (une bille, en général), pour lequel on doit déterminer les objets avec lequels il
/// pourrait collisionner par leur position générale dans l'arbre et retourner
/// une liste de pointeurs d'objets de PolygoneCollision.
///
/// @param[in]  NoeudAbstrait* n : noeud (bille) pour lequel on regarde 
///									les collisions possibles
///				std::vector<NoeudAbstrait*> listeBalles : Liste de toutes les balles
///
/// @return std::list<PolygoneCollision*>
///
////////////////////////////////////////////////////////////////////////
std::list<NoeudAbstrait*> QuadTree::detecterCollision(NoeudAbstrait* noeud, std::vector<NoeudAbstrait*> listeBalles)
{
	std::list<NoeudAbstrait*>* liste = new std::list<NoeudAbstrait*>;

	for (NoeudAbstrait* bille : listeBalles)
		if (bille != noeud)
			liste->push_back(bille);

	detecterCollision(noeud, liste);

	return *liste;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::detecterCollision(NoeudAbstrait* noeud, std::list<NoeudAbstrait*>* liste)
///
/// Fonction d'appel interne récursive de détection de la collision. Fournit un noeud
/// (une bille, en général), pour lequel on doit déterminer les objets avec lequels il
/// pourrait collisionner par leur position générale dans le sous-arbre actuel ainsi
/// qu'un pointeur vers la liste auquel on ajoute les Polygones de collisions possibles
/// du sous-arbre actuel.
///
/// @param[in]  NoeudAbstrait* n :  noeud (bille) pour lequel on regarde 
///									les collisions possibles
/// @param[in] std::list<PolygoneCollision*>* liste: Pointeur vers la liste
///									des polygones de collision à retourner
///
/// @return rien (récursif, les ajouts sont fait dans le pointeur de liste passée
///				 en paramètre
///
////////////////////////////////////////////////////////////////////////
void QuadTree::detecterCollision(NoeudAbstrait* noeud, std::list<NoeudAbstrait*>* liste)
{
	int index = getIndex(noeud);
	if (index != -1 && !feuilles_.empty())
	{
		auto it = feuilles_.begin();
		for (int i = 0; i < index; i++)
			it++;
		(*it)->detecterCollision(noeud, liste);
	}

	if (listeNoeuds_.empty())
		return;

	auto it = listeNoeuds_.begin();
	for (; it != listeNoeuds_.end(); ++it)
	{
		NoeudAbstrait* n = (*it);

		liste->push_back(n);
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::afficherQuadTree()
///
/// Fonction externe pour l'affichage graphique (dans la console) du contenu
/// actuel du QuadTree
///
/// @param[in]  Aucun
///
/// @return Rien
///
////////////////////////////////////////////////////////////////////////
void QuadTree::afficherQuadTree()
{
	printf("::::AFFICHAGE DU QUADTREE::::\n");
	this->affichageInterne();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::afficherQuadTree()
///
/// Fonction interne récursive pour l'affichage graphique (dans la console)
/// du contenu actuel du QuadTree
///
/// @param[in]  Aucun
///
/// @return Rien
///
////////////////////////////////////////////////////////////////////////
void QuadTree::affichageInterne()
{
	for (int i = 0; i < niveau_; i++)
		std::cout << "====";
	std::cout << "::::AFFICHAGE DU NIVEAU " << niveau_ << "::::" << std::endl;
	auto it = listeNoeuds_.begin();
	for (; it != listeNoeuds_.end(); ++it)
	{
		std::string nom = (*it)->obtenirType();
		for (int j = 0; j < niveau_; j++)
			std::cout << "====";
		std::cout << "Objet de type: " + nom + "." << std::endl;
	}
	auto it2 = feuilles_.begin();
	for (; it2 != feuilles_.end(); ++it2)
	{
		(*it2)->affichageInterne();
	}
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////