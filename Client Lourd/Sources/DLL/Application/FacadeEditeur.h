//////////////////////////////////////////////////////////////////////////////
/// @file FacadeEditeur.h
/// @author The New Ballers
/// @date 2016-02-19
/// @version 1.0 
///
/// @ingroup Application
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_FACADEEDITEUR_H__
#define __APPLICATION_FACADEEDITEUR_H__

class Originator;
class Propriete;

///////////////////////////////////////////////////////////////////////////
/// @class FacadeEditeur
/// @brief Classe qui constitue une interface (une facade) sur l'ensemble
///        du composante de l'éditeur
///
/// @author The New Ballers
/// @date 2016-02-20
/// @ingroup Application
///////////////////////////////////////////////////////////////////////////
class FacadeEditeur
{
public:

	/// Obtient l'instance unique de la classe.
	static FacadeEditeur* obtenirInstance();

	/// Libere l'instance unique de la classe.
	static void libererInstance();

	/// Reinitialise la scene à la zone de jeu par défaut
	void reinitialiser() const;

	/// Ajouter un evenement dans l'historique de modifications
	void sauvegarderHistorique() const;

	/// Action du undo
	void annulerModifications() const;

	/// Action du redo
	void retablirModifications() const;

	/// Vider l'historique des modifications
	void viderHistorique() const;

	/// Regarde dans l'historique si la position courante possede une modification suivante
	bool possedeSuivant() const;

	/// Regarde dans l'historique si la position courante possede une modification précédente
	bool possedePrecedent() const;

	bool zoneValide();

	/// Sauvegarder une zone de jeu en format XML
	std::string sauvegarderZone(char* nomFichier, char* proprietes) const;

	/// Charger une zone de jeu a partir d'un fichier XML
	void chargerZone(std::string nomFichier) const;

	/// Obtenir les proprietes comme une suite de chaines de caractères séparée par un \n
	std::string obtenirPropriete() const;

	/// Pour le rectangle elastique
	void rectangleElastique(int i, int j);

	/// Initialisation du rectangle elastique
	void initialiserRectangleElastique(int i, int j);

	/// Fin du rectangle elastique
	void terminerRectangleElastique();

	/// Verifier si un point clique est dans la table 
	bool estDansTable(glm::dvec3 pointDuMonde);

	/// Verifier si un point clique est dans la table
	bool verifierCliqueDansTable(int x, int y);

	/// Verifier si la souris est situe sur un objet
	bool sourisEstSurObjet(int i, int j, int hauteur, int largeur, bool& estSelectionne) const;

	/// Obtient le nombre d'objets selectionnés 
	int obtenirNombreSelection();

	/// Selectionner les objets sous un point clique
	int selectionSimple(int i, int j, int hauteur, int largeur, bool ctrlDown = false, bool gaucheEnfonce = false, bool sourisSurSelection = false);

	/// Pour la selection multiple d'objets
	int selectionMultiple(bool inverse) const;

	/// Deplacement des noeuds selectionnes dans l'arbre de rendu.
	void deplacerSelection(int x1, int y1, int x2, int y2, bool duplication);

	/// Scale de la selection
	void agrandirSelection(int x1, int y1, int x2, int y2);

	/// Rotation des noeuds selectionnes
	void tournerSelection(int x1, int y1, int x2, int y2);

	/// Verifie si la selection est hors table lors de la duplication
	bool duplicationEstHorsTable() const;

	/// Pour la duplication d'objets selectionnes
	void dupliquerSelection(int i, int j);

	/// Pour la suppression des objets selectionnés
	void supprimerSelection() const;

	/// Position du mur
	void positionnerMur(int originX, int originY, int x1, int y1, int x2, int y2, NoeudAbstrait* noeud) const;

private:

	/// Constructeur.
	FacadeEditeur();

	/// Destructeur.
	~FacadeEditeur();

	/// Constructeur copie desactive.
	FacadeEditeur(const FacadeEditeur&) = delete;

	/// Operateur d'assignation desactive.
	FacadeEditeur& operator=(const FacadeEditeur&) = delete;

	/// Connaitre le ratio entre le trou et la taille de la bille
	double ratioBilleTrou() const;

	/// Pointeur vers l'instance unique de la classe.
	static FacadeEditeur* instance_;

	/// Pour le undo/redo
	Originator* originator_;

	/// Pour les propriétés de la zone de jeu
	Propriete* propriete_;

	/// Rectangle élastique
	glm::dvec3 selectionBasGauche_, selectionHautDroit_;
	glm::ivec2 pointInitial_, pointAvant_;

	/// Savoir si la duplication est en dehors de la table
	bool duplicationHorsTable_;
};

#endif // __APPLICATION_FACADEEDITEUR_H__
