////////////////////////////////////////////////
/// @file   VisiteurPortail.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#include "VisiteurPortail.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"
#include "../Arbre/Noeuds/NoeudPortail.h"


////////////////////////////////////////////////////////////////////////
/// @fn VisiteurPortail::VisiteurPortail()
/// @brief Constructeur qui initialise les variables membres de la classe.
/// @return Aucune (constructeur).
////////////////////////////////////////////////////////////////////////
VisiteurPortail::VisiteurPortail(std::clock_t time)
{
	time_ = time;
}


////////////////////////////////////////////////////////////////////////
/// @fn VisiteurPortail::~VisiteurPortail()
/// Desalloue la memoire de pointeurs
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
VisiteurPortail::~VisiteurPortail()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurPortail::traiter(ArbreRenduINF2990* arbre)
///
/// Cette fonction traite l'arbre de rendu pour supprimer ses enfants
/// selectionnes. Cette fonction retourne true pour dire que l'operation s'est
/// fait correctement, ou false si on ne permet pas la sauvegarde
///
/// @param[in] arbre : L'arbre a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurPortail::traiter(ArbreRenduINF2990* arbre)
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
///
/// @fn bool VisiteurPortail::traiter(NoeudTable* table)
///
/// Cette fonction traite la table de l'arbre de rendu. Cette fonction 
///	retourne true pour dire que l'operation s'est faite correctement.
///
/// @param[in] table : Le noeud de type Table a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurPortail::traiter(NoeudTable* table)
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
/// @fn bool VisiteurSuppression::traiter(NoeudAbstrait* noeud)
/// @brief Cette fonction traite les enfants de l'arbre de rendu. Cette fonction 
///		   retourne true pour dire que l'operation s'est faite correctement.
/// @param[in] noeud : Noeud de l'arbre a traiter.
/// @return Retourne toujours true.
////////////////////////////////////////////////////////////////////////
bool VisiteurPortail::traiter(NoeudPortail* noeud)
{
	noeud->setStartingDisable(time_);
	return true;
}