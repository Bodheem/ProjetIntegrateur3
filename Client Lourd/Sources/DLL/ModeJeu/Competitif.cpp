//////////////////////////////////////////////////////////////////////////////
/// @file ModeJeu.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////


#include "Competitif.h"
#include "FacadeReseau.h"
#include "FacadeModele.h"
#include "ArbreRenduINF2990.h"
#include "NoeudAbstrait.h"

////////////////////////////////////////////////////////////////////////
/// @fn MapSnapShot::MapSnapShot(int tick)
/// @brief Constructeur qui initialise les attributs 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
Competitif::Competitif()
{
	nombreJoueur_ = 1;
}


////////////////////////////////////////////////////////////////////////
/// @fn Competitif::~Competitif()
/// @brief Destructeur
/// @return Aucun
////////////////////////////////////////////////////////////////////////
Competitif::~Competitif()
{

}


////////////////////////////////////////////////////////////////////////
/// @fn Competitif::initialiserMode()
/// @brief 
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void Competitif::initialiserMode()
{
	int nombreJoueur_ = FacadeReseau::obtenirInstance()->obtenirNombreJoueur();
	int numeroJoueur = FacadeReseau::obtenirInstance()->obtenirNumeroJoueur();

	// Creer des instances de palettes pour chacun des joueurs
	if (nombreJoueur_ != -1)
	{
		// Obtenir l'arbre de rendu
		ArbreRenduINF2990* arbre = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990();

		// Noeud courant
		NoeudAbstrait* node = nullptr;

		// Noeud cree
		NoeudAbstrait* created = nullptr;

		// Obtenir le nombre de noeuds originellemenet
		int nombreNoeuds = arbre->getEnfant(0)->obtenirNombreEnfants();

		// Trouver les palettes
		for (int i = 0; i < nombreNoeuds; ++i)
		{
			node = arbre->getEnfant(0)->getEnfant(i);

			// Si on trouve une palette originalement dans la map
			if (node->obtenirType() == "paletteg" || node->obtenirType() == "paletted" || node->obtenirType() == "ressort")
			{
				for (int j = 1; j < nombreJoueur_; ++j)
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
