//////////////////////////////////////////////////////////////////////////////
/// @file ModeJeu.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////


#include "Cooperatif.h"
#include "FacadeReseau.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
#include "NoeudAbstrait.h"

////////////////////////////////////////////////////////////////////////
/// @fn Cooperatif::Cooperatif()
/// @brief Constructeur qui initialise les attributs 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
Cooperatif::Cooperatif()
{
	nombreJoueur_ = 1;
}


////////////////////////////////////////////////////////////////////////
/// @fn Cooperatif::~Cooperatif()
/// @brief Destructeur
/// @return Aucun
////////////////////////////////////////////////////////////////////////
Cooperatif::~Cooperatif()
{

}


////////////////////////////////////////////////////////////////////////
/// @fn Competitif::initialiserMode()
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void Cooperatif::initialiserMode()
{
	int nombreJoueur = FacadeReseau::obtenirInstance()->obtenirNombreJoueur();
	int numeroJoueur = FacadeReseau::obtenirInstance()->obtenirNumeroJoueur();
	
	// Savoir si la carte contient des palettes de type J1 et J2. Si oui, les stocker
	std::vector<NoeudAbstrait*> player1;
	std::vector<NoeudAbstrait*> player2;

	// Creer des instances de palettes pour chacun des joueurs supplémentaires
	if (nombreJoueur > 1)
	{
		// Obtenir l'arbre de rendu
		ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

		// Noeud courant
		NoeudAbstrait* node = nullptr;

		// Noeud cree
		NoeudAbstrait* created = nullptr;

		// Obtenir le nombre de noeuds originellemenet
		unsigned int nombreNoeuds = arbre->getEnfant(0)->obtenirNombreEnfants();

		// Trouver les palettes de type P1 et P2 s'ils existent
		for (unsigned int i = 0; i < nombreNoeuds; ++i)
		{
			node = arbre->getEnfant(0)->getEnfant(i);

			if (node->obtenirType() == "paletteg" || node->obtenirType() == "paletted")
			{
				if (node->getColorShift() == 0)
					player1.push_back(node);

				if (node->getColorShift() == 1)
					player2.push_back(node);
			}
			else if (node->obtenirType() == "ressort")
			{
				// Créer une instance de ressort pour chaque joueur
				for (int j = 1; j < nombreJoueur; ++j)
				{
					created = arbre->creerNoeud(node->obtenirType());
					created->setColorShift(j);

					if (j != numeroJoueur - 1)
						created->setTransparent(true);

					// Copie de la palette originale
					created->assignerPositionRelative(node->obtenirPositionRelative());
					created->assignerEchelle(node->obtenirAgrandissement());
					created->assignerRotationHard(node->obtenirRotation());
					arbre->getEnfant(0)->ajouter(created);

					created->assignerNumeroUnique(arbre->getEnfant(0)->obtenirNombreEnfants());
				}

				if (numeroJoueur != 1)
					node->setTransparent(true);
			}
		}
	
		// On a les deux types de palette sur la zone de jeu
		if (player1.size() > 0 && player2.size() > 0)
		{
			if (nombreJoueur >= 3)
			{
				initialiserTroisJoueurs(player1, player2);

				if (nombreJoueur == 4)
				{
					initialiserQuatreJoueurs(player1, player2);
				}
			}
		}

		// On a juste des palettes de type J1
		if (player1.size() > 0 && player2.size() == 0)
		{
			for (unsigned int i = 0; i < player1.size(); ++i)
			{
				node = player1[i];

				for (int j = 1; j < nombreJoueur; ++j)
				{
					created = arbre->creerNoeud(node->obtenirType());
					created->setColorShift(j);

					if (j != numeroJoueur - 1)
						created->setTransparent(true);

					// Copie de la palette originale
					created->assignerPositionRelative(node->obtenirPositionRelative());
					created->assignerEchelle(node->obtenirAgrandissement());
					created->assignerRotationHard(node->obtenirRotation());
					arbre->getEnfant(0)->ajouter(created);

					created->assignerNumeroUnique(arbre->getEnfant(0)->obtenirNombreEnfants());
				}

				if (numeroJoueur != 1)
					node->setTransparent(true);
			}
		}

		// On a juste des palettes de type J2
		if (player1.size() == 0 && player2.size() > 0)
		{
			for (unsigned int i = 0; i < player2.size(); ++i)
			{
				node = player2[i];

				for (int j = 1; j < nombreJoueur; ++j)
				{
					created = arbre->creerNoeud(node->obtenirType());
					created->setColorShift(j);

					if (j != numeroJoueur - 1)
						created->setTransparent(true);

					// Copie de la palette originale
					created->assignerPositionRelative(node->obtenirPositionRelative());
					created->assignerEchelle(node->obtenirAgrandissement());
					created->assignerRotationHard(node->obtenirRotation());
					arbre->getEnfant(0)->ajouter(created);

					created->assignerNumeroUnique(arbre->getEnfant(0)->obtenirNombreEnfants());
				}

				// Les palettes originales sont toujours au joueur 1, donc colorshift = 0
				node->setColorShift(0);

				if (numeroJoueur != 1)
					node->setTransparent(true);
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn Competitif::initialiserTroisJoueurs()
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////

void Cooperatif::initialiserTroisJoueurs(std::vector<NoeudAbstrait*>& player1, std::vector<NoeudAbstrait*>& player2)
{
	// Obtenir l'abre de rendu
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	NoeudAbstrait* node = nullptr;
	NoeudAbstrait* created = nullptr;

	for (unsigned int i = 0; i < player1.size(); ++i)
	{
		node = player1[i];

		// Colorshift du 3eme joueur est 2
		created = arbre->creerNoeud(node->obtenirType());
		created->setColorShift(2);
		created->setTransparent(true);

		// Copie de la palette originale
		created->assignerPositionRelative(node->obtenirPositionRelative());
		created->assignerEchelle(node->obtenirAgrandissement());
		created->assignerRotationHard(node->obtenirRotation());
		arbre->getEnfant(0)->ajouter(created);

		created->assignerNumeroUnique(arbre->getEnfant(0)->obtenirNombreEnfants());
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn Competitif::initialiserQuatreJoueurs()
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void Cooperatif::initialiserQuatreJoueurs(std::vector<NoeudAbstrait*>& player1, std::vector<NoeudAbstrait*>& player2)
{
	// Obtenir l'abre de rendu
	ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

	NoeudAbstrait* node = nullptr;
	NoeudAbstrait* created = nullptr;

	for (unsigned int j = 0; j < player2.size(); ++j)
	{
		node = player1[j];

		// Colorshift du 3eme joueur est 2
		created = arbre->creerNoeud(node->obtenirType());
		created->setColorShift(3);
		created->setTransparent(true);

		// Copie de la palette originale
		created->assignerPositionRelative(node->obtenirPositionRelative());
		created->assignerEchelle(node->obtenirAgrandissement());
		created->assignerRotationHard(node->obtenirRotation());
		arbre->getEnfant(0)->ajouter(created);

		created->assignerNumeroUnique(arbre->getEnfant(0)->obtenirNombreEnfants());
	}

}