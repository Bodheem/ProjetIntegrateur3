////////////////////////////////////////////////
/// @file   GlobalesPartie.h
/// @author The New Ballers
/// @date   2016-01-17
///
/// @ingroup GlobalesPartie
////////////////////////////////////////////////

#ifndef __GLOBAL_GLOBALESPARTIE_H__
#define __GLOBAL_GLOBALESPARTIE_H__

#include <vector>
#include "glm/glm.hpp"
#include <ctime>

class NoeudAbstrait;

///////////////////////////////////////////////////////////////////////////
/// @class GlobalesPartie
/// @brief Classe servant a garder en memoire les variables globales ayant
/// rapport a la partie en cours. Cette classe ne doit qu'etre instanciee
/// en tant que membre de la classe FacadeModele.
///
/// @author The New Ballers
/// @date 2016-01-17
///////////////////////////////////////////////////////////////////////////
class GlobalesPartie
{

public:

	// Constructeur
	GlobalesPartie();

	// Assigner les points d'un certain joueur
	void setPointsJoueur(int pointsPartie, int colorshift = 0);

	// Obtenir les points d'un certain joueur
	int getPointsJoueur(int colorshift = 0) const;

	// Ajouter les points lors d'une collision avec un butoir circulaire
	void collisionButoirCirculaire(int colorshift = 0);

	// Ajouter les points lors d'une collision avec un butoir triangulaire
	void collisionButoirTriangulaire(int colorshift = 0);

	// Ajouter les points lors d'une collision avec une cible
	void collisionButoirCible(int colorshift = 0);

	// Ajouter les points lors d'une collision avec un bonus
	void collisionBonus(int colorshift = 0);

	// Réassigner le nombre de points pour chaque collision
	void resetConfigurationCollision(int pointsCirculaire, int pointsTriangulaire, int pointsCible,
									int pointsPartieGagner, int pointsNouvelleBille);

	// Retirer au compteur de bille
	void retirerBille(int colorshift = 0);

	// Ajouter au compteur de bille
	void ajouterBille(int colorshift = 0);

	// Afficher les billes
	void afficherBille(int colorshift = 0);

	// Obtenir le nombre de bille courante d'un certain joueur
	int obtenirNombreBilleCourante(int colorshift = 0) const;

	// En mode multiplayer, changer le nombre de billes courantes
	void assignerBillesCourantes(int nombre, int colorshift = 0);

	// Obtenir le nombre de billes perdues d'un certain joueur
	int obtenirNombreDeBillesPerdues(int colorshift = 0) const;

	// En mode multiplayer, changer le nombre de billes perdues
	void assignerBillesPerdues(int nombre, int colorshift = 0);

	// Reinitialiser le nombre de billes courantes à 0
	void resetBilles(int colorshift = 0);

	// Mettre a jour les billes
	void updateBilles(int colorshift = 0);

	// Empiler la génération des billes dans le bon générateur
	void spawnBille(glm::dvec3 position, glm::dvec3 echelle, NoeudAbstrait* portail, int colorshift = 0);

	// Mettre fin à la génération
	void finGeneration();

	// Pour le multiplicateur de points (bonus)
	void assignerDebutMultiplicateur(std::clock_t time);

	// Sert a synchroniser les billes. On garde un numero unique pour chaque bille
	static int compteurNumeroBille;

	/// Obtenir le bonus courant
	std::string obtenirBonusCourant() const;

	/// Assigner le bonus courant
	void assignerBonusCourant(std::string bonus);

	/// Obtenir le bonus courant
	std::string obtenirMalusCourant() const;

	/// Obtenir le bonus courant
	void assignerMalusCourant(std::string bonus);

	/// Connaitre le temps d'affichage 
	void assignerTempsAffichageBonus(std::clock_t bonus);

	/// Connaitre le temps d'affichage 
	void assignerTempsAffichageMalus(std::clock_t malus);

	/// Mettre a jour l'affichage du bonus obtenu
	void updateAffichageBonus();

	/// Mettre a jour l'affichage du malus obtenu
	void updateAffichageMalus();

private:

	/// Calculer si on a affaire a un multiplicateur de bonus
	void calculerMultiplicateur();

	// Pour savoir le bonus et malus courant
	std::string bonusCourant_;
	std::string malusCourant_;

	// Le temps pendant lequel on affiche l'information du bonus/malus
	std::clock_t startingAffichageBonus_;
	std::clock_t startingMalusAffichage_;

	// Données de jeu
	int pointJoueur_[4];
	int billesCourantesJoueur_[4];
	int billesPerduesJoueur_[4];

	// Gestion des points des collisions entre les différents objets
	int collisionPointsCirculaire_{ 0 };
	int collisionPointsTriangulaire_{ 0 };
	int collisionPointsCible_{ 0 };
	int collisionPointsPartieGagner_{ 0 };
	int collisionPointsNouvelleBille_{ 0 };

	// Pour les informations de génération de bille
	class InfoBille
	{
	public :
		glm::dvec3 position_;
		glm::dvec3 echelle_;
		NoeudAbstrait* portail_;
	};

	bool enCoursDeGeneration_{ false };
	std::vector<InfoBille> launcheSequence_[4];

	// Le temps ou on débute l'activation du multiplicateur de point
	std::clock_t startingMultiplicateurBonus_;
	int multiplicateur_;
	int tempsBonus_ = 10;
};

#endif //__GLOBAL_GLOBALESPARTIE_H__
