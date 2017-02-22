////////////////////////////////////////////////
/// @file   VisiteurPalettes.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#include "VisiteurPalettes.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include "../Arbre/Noeuds/NoeudPaletteG.h"
#include "../Arbre/Noeuds/NoeudPaletteD.h"


////////////////////////////////////////////////////////////////////////
/// @fn VisiteurPalettes::VisiteurPalettes()
/// @brief Constructeur qui initialise les variables membres de la classe.
/// @return Aucune (constructeur).
////////////////////////////////////////////////////////////////////////
VisiteurPalettes::VisiteurPalettes(std::clock_t time)
{
	time_ = time;
}


////////////////////////////////////////////////////////////////////////
/// @fn VisiteurPalettes::~VisiteurPalettes()
/// @brief Desalloue la memoire de pointeurs si utilisés
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
VisiteurPalettes::~VisiteurPalettes()
{

}


////////////////////////////////////////////////////////////////////////
/// @fn bool VisiteurPalettes::traiter(ArbreRenduINF2990* arbre)
///
/// @brief Cette fonction traite l'arbre de rendu pour supprimer ses enfants
///		   selectionnes. Cette fonction retourne true pour dire que l'operation s'est
///		   fait correctement, ou false si on ne permet pas la sauvegarde
/// @param[in] arbre : L'arbre a traiter.
/// @return Retourne toujours true
////////////////////////////////////////////////////////////////////////
bool VisiteurPalettes::traiter(ArbreRenduINF2990* arbre)
{
	// Visiter les enfants de l'arbre
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		// Traiter les enfants de l'arbre de rendu
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool VisiteurPalettes::traiter(NoeudTable* table)
/// @brief Cette fonction traite la table de l'arbre de rendu. Cette fonction 
///		   retourne true pour dire que l'operation s'est faite correctement.
/// @param[in] table : Le noeud de type Table a traiter.
/// @return Retourne toujours true
////////////////////////////////////////////////////////////////////////
bool VisiteurPalettes::traiter(NoeudTable* table)
{
	// Traiter les enfants selectionnes de la table
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		// Traiter les enfants de la table
		table->getEnfant(i)->accepterVisiteur(this);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool VisiteurPalettes::traiter(NoeudPaletteD* noeud)
/// @brief Cette fonction traite les enfants de l'arbre de rendu. Cette fonction 
///		   retourne true pour dire que l'operation s'est faite correctement.
/// @param[in] noeud : Noeud de l'arbre a traiter.
/// @return Retourne toujours true.
////////////////////////////////////////////////////////////////////////
bool VisiteurPalettes::traiter(NoeudPaletteD* noeud)
{
	noeud->setStartingDisable(time_);
	return true;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool VisiteurPalettes::traiter(NoeudPaletteG* noeud)
/// @brief Cette fonction traite les enfants de l'arbre de rendu. Cette fonction 
///		   retourne true pour dire que l'operation s'est faite correctement.
/// @param[in] noeud : Noeud de l'arbre a traiter.
/// @return Retourne toujours true.
////////////////////////////////////////////////////////////////////////
bool VisiteurPalettes::traiter(NoeudPaletteG* noeud)
{
	noeud->setStartingDisable(time_);
	return true;
}