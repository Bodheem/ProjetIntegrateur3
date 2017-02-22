//////////////////////////////////////////////////////////////////////////////
/// @file FacadeJeu.h
/// @author The New Ballers
/// @date 2016-02-19
/// @version 1.0 
///
/// @ingroup Application
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_FACADEJEU_H__
#define __APPLICATION_FACADEJEU_H__

#include <string>
#include <vector>

class GlobalesPartie;
class PhysicsManager;
class IntelligenceArtificielle;
class NoeudPaletteG;
class NoeudPaletteD;
class NoeudAbstrait;
class ModeJeu;

///////////////////////////////////////////////////////////////////////////
/// @class FacadeJeu
/// @brief Classe qui constitue une interface (une facade) sur l'ensemble
///        du composante de jeu
///
/// @author The New Ballers
/// @date 2016-02-20
/// @ingroup Application
///////////////////////////////////////////////////////////////////////////
class FacadeJeu
{
public:

	/// Obtient l'instance unique de la classe.
	static FacadeJeu* obtenirInstance();

	/// Libere l'instance unique de la classe.
	static void libererInstance();

	/// Traiter les collisions entres les tous objets
	void traiterCollisions(float temps) const;
	
	/// Mettre a jour les forces externes
	void updateForcesExternes() const;

	/// Mettre a jour la liste des ressorts de la zone de jeu
	void mettreAJourListeRessorts();

	/// Mettre a jour la liste des noeuds de la zone de jeu
	void mettreAJourListeNoeuds() const;

	/// Mettre a jour la liste des billes de la zone de jeu
	void mettreAJourListeBillesEtNoeuds() const;

	/// Compresser un ressort
	void compresserRessort(int colorshift = 0);

	/// Relacher le ressort
	void relacherRessort(int colorshift = 0);

	/// Inverser les touches des palettes
	void inverserTouchesPalettes();

	/// Desactiver temporairement l'effet de tous les portails
	void desactiverTemporairementPortails() const;

	/// Desactiver temporairement l'effet de tous les portails
	void desactiverTemporairementPalettes() const;

	/// Construire des les 4 listes de palettes GJ1, DJ1, GJ2, DJ2
	void construireListesPalettes();

	/// Activer les palettes gauches
	void activerPalettesGauches(int colorshift = 0);

	/// Desactiver les palettes gauches
	void desactiverPalettesGauches(int colorshift = 0);

	/// Activer les palettes droites
	void activerPalettesDroites(int colorshift = 0);

	/// Desactiver les palettes droites
	void desactiverPalettesDroites(int colorshift = 0);

	/// Initialiser un niveau de difficulté de joueur virtuel
	void initializeLevelAI(std::string type);

	/// Activer le joueur virtuel
	void activerAI(bool activer, int joueur);

	/// Lorsque le joueur virtuel est activé
	void jouerAI(float temps) const;

	/// Créer un snapshot pour le jeu multijoueur
	static std::string createSnapshot();

	/// Appliquer les modifications à l'arbre de rendu
	static void applyModification(std::string data);

	/// Savoir si un bouton qui controle les palettes ou le ressor est appuyé
	bool obtenirEtatBouton(int bouton) const;

	/// Initialiser les palettes et les autres instances en mode compétitif
	void initialiserModeCompetitif();

	/// Initialiser les palettes et les autres instances en mode coopératif
	void initialiserModeCooperatif();

private:

	/// Constructeur.
	FacadeJeu();

	/// Destructeur.
	~FacadeJeu();

	/// Constructeur copie desactive.
	FacadeJeu(const FacadeJeu&) = delete;

	/// Operateur d'assignation desactive.
	FacadeJeu& operator=(const FacadeJeu&) = delete;

	/// Pointeur vers l'instance unique de la classe.
	static FacadeJeu* instance_;

	/// Classe qui controle le joueur virtuel du joueur 2
	IntelligenceArtificielle* secondPlayer_;

	/// Classe qui controle le joueur virtuel du joueur 3
	IntelligenceArtificielle* thirdPlayer_;

	/// Classe qui controle le joueur virtuel du joueur 4
	IntelligenceArtificielle* fourthPlayer_;

	/// Pour la gestion de la physique
	PhysicsManager* physics_;

	/// Pour la gestion des modes de jeu en multijoueur
	ModeJeu* modejeu_;

	/// La liste des ressorts de la zone de jeu
	std::vector<std::vector<NoeudAbstrait*>> listeRessorts_;

	/// Listes de palettes a activer pour chaque touche
	std::vector<std::vector<NoeudPaletteG*>> palettesGauches_; ///< Gauche joueur 1
	std::vector<std::vector<NoeudPaletteD*>> palettesDroites_; ///< Droite joueur 1

	/// Pour savoir si on inverse les touches associés aux palettes
	bool inverserTouches;

	/// Pour savoir lequel des joueurs virtuel il faut activer
	bool utiliserAI[5];

	/// Connaitre l'état des boutons qui controle les palettes et le ressort
	bool isPressed[3];
};

#endif // __APPLICATION_FACADEJEU_H__
