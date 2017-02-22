///////////////////////////////////////////////////////////////////////////
/// @file GlobalesPartie.cpp
/// @author The New Ballers
/// @date 2016-01-17
/// @version 1.0
///
/// @ingroup Global
///////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include <gl/GLU.h>
#include <gl/GL.h>

#include "GlobalesPartie.h"
#include "FacadeModele.h"
#include "NoeudAbstrait.h"
#include "../Text/ControleurTexte.h"

int GlobalesPartie::compteurNumeroBille = 0;


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::setPointsPartie(int pointsPartie)
/// @brief Assigne la valeur de pointsPartie a pointsPartie_.
/// @return Aucun
////////////////////////////////////////////////////////////////////////
GlobalesPartie::GlobalesPartie()
{
	for (int i = 0; i < 4; ++i)
	{
		pointJoueur_[i] = 0;
		billesCourantesJoueur_[i] = 0;
		billesPerduesJoueur_[i] = 0;
	}

	multiplicateur_ = 1;
	bonusCourant_ = "";

	startingAffichageBonus_ = std::clock();
	startingMalusAffichage_ = std::clock();
	startingMultiplicateurBonus_ = std::clock();
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::setPointsPartie(int pointsPartie)
/// @brief Assigne la valeur de pointsPartie a pointsPartie_.
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::setPointsJoueur(int pointsPartie, int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	pointJoueur_[colorshift] = pointsPartie;
}


////////////////////////////////////////////////////////////////////////
/// @fn int GlobalesPartie::getPointsPartie() const
/// @return Les points actuels dans la partie.
////////////////////////////////////////////////////////////////////////
int GlobalesPartie::getPointsJoueur(int colorshift) const
{
	if (colorshift < 0 || colorshift > 3)
		return -1;

	return pointJoueur_[colorshift];
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::collisionButoirCirculaire()
/// @brief Action rajoutant les points assignes aux butoirs circulaires aux
///		   points de la partie.
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::collisionButoirCirculaire(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	calculerMultiplicateur();

	pointJoueur_[colorshift] += multiplicateur_ * collisionPointsCirculaire_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::collisionButoirTriangulaire()
/// @brief Action rajoutant les points assignes aux butoirs triangulaires aux
///		   points de la partie.
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::collisionButoirTriangulaire(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	calculerMultiplicateur();

	pointJoueur_[colorshift] += multiplicateur_ * collisionPointsTriangulaire_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::collisionButoirCible()
/// @brief Action rajoutant les points assignes aux cibles aux
///		   points de la partie.
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::collisionButoirCible(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;
	
	calculerMultiplicateur();

	pointJoueur_[colorshift] +=  multiplicateur_ * collisionPointsCible_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::collisionBonus()
/// @brief Action rajoutant les points assignes aux bonus aux
///		   points de la partie.
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::collisionBonus(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	pointJoueur_[colorshift] += static_cast<int>(pointJoueur_[colorshift] * 0.1);
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::resetConfigurationCollision()
/// @brief Permet de mettre a jour les valeurs des points pour chaque collision
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::resetConfigurationCollision(int collisionPointsCirculaire,
	int collisionPointsTriangulaire,
	int collisionPointsCible,
	int collisionPointsPartieGagner,
	int collisionPointsNouvelleBille)
{
	collisionPointsCirculaire_ = collisionPointsCirculaire;
	collisionPointsTriangulaire_ = collisionPointsTriangulaire;
	collisionPointsCible_ = collisionPointsCible;
	collisionPointsPartieGagner_ = collisionPointsPartieGagner;
	collisionPointsNouvelleBille_ = collisionPointsNouvelleBille;

	for (int i = 0; i < 4; ++i)
	{
		pointJoueur_[i] = 0;
		billesCourantesJoueur_[i] = 0;
		billesPerduesJoueur_[i] = 0;
	}

	enCoursDeGeneration_ = 0;

	for (int i = 0; i < 4; ++i)
		launcheSequence_[i].clear();
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::retirerBille()
/// @brief Met a jour les valeurs des billes lors de perte de bille.
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::retirerBille(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	billesCourantesJoueur_[colorshift]--;
	billesPerduesJoueur_[colorshift]++;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::ajouterBille()
/// @brief Met a jour les valeurs des billes lors de rajout de bille.
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::ajouterBille(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	billesCourantesJoueur_[colorshift]++;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::afficherBille()
/// @brief Affiche la bille
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::afficherBille(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	glm::dvec3 position = launcheSequence_[colorshift].back().position_;
	glm::dvec3 scale = launcheSequence_[colorshift].back().echelle_;
	launcheSequence_[colorshift].pop_back();
	FacadeModele::obtenirInstance()->creeBille(position, scale, colorshift);
}


////////////////////////////////////////////////////////////////////////
/// @fn int GlobalesPartie::obtenirNombreBilleCourante() const
/// @brief Retourne le nombre de billes courantes.
/// @return Le nombre de billes courantes.
////////////////////////////////////////////////////////////////////////
int GlobalesPartie::obtenirNombreBilleCourante(int colorshift) const
{
	if (colorshift < 0 || colorshift > 3)
		return -1;

	return billesCourantesJoueur_[colorshift];
}


////////////////////////////////////////////////////////////////////////
/// @fn int GlobalesPartie::assignerBillesCourantes()
/// @brief 
/// @return
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::assignerBillesCourantes(int nombre, int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	billesCourantesJoueur_[colorshift] = nombre;
}


////////////////////////////////////////////////////////////////////////
/// @fn int GlobalesPartie::obtenirNombreDeBillesPerdues() const
/// @brief Retourne le nombre de billes perdues.
/// @return Le nombre de billes perdues.
////////////////////////////////////////////////////////////////////////
int GlobalesPartie::obtenirNombreDeBillesPerdues(int colorshift) const
{
	if (colorshift < 0 || colorshift > 3)
		return -1;

	return billesPerduesJoueur_[colorshift];
}


////////////////////////////////////////////////////////////////////////
/// @fn int GlobalesPartie::assignerBillesPerdues() const
/// @brief 
/// @return 
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::assignerBillesPerdues(int nombre, int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	billesPerduesJoueur_[colorshift] = nombre;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::resetBilles()
/// @brief Remet le nombre de billes courantes a 0.
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::resetBilles(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	billesCourantesJoueur_[colorshift] = 0;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::updateBilles()
/// @brief Met a jour le gestionaire de billes
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::updateBilles(int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	if (!enCoursDeGeneration_ && launcheSequence_[colorshift].size() > 0)
	{
		launcheSequence_[colorshift].back().portail_->genererBille();
		enCoursDeGeneration_ = true;
		afficherBille(colorshift);
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::spawnBille(glm::dvec3 position, glm::dvec3 echelle, NoeudAbstrait* portail)
/// @brief Gere le moment de creation d'une bille (pour respecter la regle des une secondes)
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::spawnBille(glm::dvec3 position, glm::dvec3 echelle, NoeudAbstrait* portail, int colorshift)
{
	if (colorshift < 0 || colorshift > 3)
		return;

	InfoBille info;
	info.position_ = position;
	info.echelle_ = echelle;
	info.portail_ = portail;

	launcheSequence_[colorshift].push_back(info);
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::finGeneration()
/// @brief Met a false le flag enCoursDeGeneration_ pour permettre la generation
///		   d'une nouvelle bille.
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::finGeneration()
{
	enCoursDeGeneration_ = false;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::assignerDebutMultiplicateur(std::clock_t time)
/// @brief 
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::assignerDebutMultiplicateur(std::clock_t time)
{
	startingMultiplicateurBonus_ = time;
	multiplicateur_ = 2;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::obtenirBonusCourant()
/// @brief 
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
std::string GlobalesPartie::obtenirBonusCourant() const
{
	return bonusCourant_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::assignerBonusCourant()
/// @brief 
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::assignerBonusCourant(std::string bonus)
{
	bonusCourant_ = bonus;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::obtenirBonusCourant()
/// @brief 
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
std::string GlobalesPartie::obtenirMalusCourant() const
{
	return malusCourant_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::assignerBonusCourant()
/// @brief 
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::assignerMalusCourant(std::string malus)
{
	malusCourant_ = malus;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::calculerMultiplicateur()
/// @brief 
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::calculerMultiplicateur()
{
	std::clock_t time = std::clock();
	double diff = (time - startingMultiplicateurBonus_) / static_cast<double>(CLOCKS_PER_SEC);

	if (diff > tempsBonus_)
	{
		multiplicateur_ = 1;
	}
	else
	{
		multiplicateur_ = 2;
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::calculerMultiplicateur()
/// @brief 
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::assignerTempsAffichageBonus(std::clock_t bonus)
{
	startingAffichageBonus_ = bonus;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::calculerMultiplicateur()
/// @brief 
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::assignerTempsAffichageMalus(std::clock_t malus)
{
	startingMalusAffichage_ = malus;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::calculerMultiplicateur()
/// @brief 
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::updateAffichageBonus()
{
	std::clock_t time = std::clock();
	int diff = (time - startingAffichageBonus_) / CLOCKS_PER_SEC;
	std::string timer = "";

	// Traiter le texte pour le bonus
	if (bonusCourant_ == "BONUS DE POINTS!" || bonusCourant_ == "BILLE GRATUITE!")
	{
		/// 3 secondes d'affichage
		if (diff > 1)
		{
			bonusCourant_ = "";
		}
	}
	else if (bonusCourant_ == "MULTIPLICATEUR DE POINTS!" || bonusCourant_ == "PORTAILS DESACTIVES!")
	{
		/// 10 secondes d'affichage
		if (diff > 10)
		{
			bonusCourant_ = "";
		}
		else
		{
			/// Récupérer le temps
			timer = " : " + std::to_string(tempsBonus_ - diff) + " secondes";
		}
	}
	else
	{
		bonusCourant_ = "";
	}

	static  std::string ancienText = "Bonus: ";
	std::string currentText = "Bonus: " + bonusCourant_ + timer;
	if (ancienText != currentText)
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->updateText(ancienText, currentText);
	ancienText = currentText;
}


////////////////////////////////////////////////////////////////////////
/// @fn void GlobalesPartie::calculerMultiplicateur()
/// @brief 
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void GlobalesPartie::updateAffichageMalus()
{
	std::clock_t time = std::clock();
	int diff = (time - startingMalusAffichage_) / CLOCKS_PER_SEC;
	std::string timer = "";

	// Traiter le texte pour le malus
	if (malusCourant_ == "VITESSE DE BILLE RALENTIE!" || malusCourant_ == "BILLE DETRUITE!" || malusCourant_ == "TOUCHES INVERSEES")
	{
		/// 3 secondes d'affichage
		if (diff > 1)
		{
			malusCourant_ = "";
		}
	}
	else if (malusCourant_ == "PALETTES BLOQUEES!")
	{
		/// 10 secondes d'affichage
		if (diff > 10)
		{
			malusCourant_ = "";
		}
		else
		{
			/// Récupérer le temps
			timer = " : " + std::to_string(tempsBonus_ - diff) + " secondes";
		}
	}
	else
	{
		malusCourant_ = "";
	}

	static  std::string ancienText = "Malus: ";
	std::string currentText = "Malus: " + malusCourant_ + timer;
	if (ancienText != currentText)
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->updateText(ancienText, currentText);
	ancienText = currentText;
}