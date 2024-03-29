////////////////////////////////////////////////
/// @file   VisiteurSuppression.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Visiteur
////////////////////////////////////////////////

#include "VisiteurSuppression.h"
#include "../Arbre/ArbreRenduINF2990.h"
#include "../Arbre/Noeuds/NoeudTable.h"


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::VisiteurSuppression()
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSuppression::VisiteurSuppression()
{

}


////////////////////////////////////////////////////////////////////////
///
/// @fn VisiteurSuppression::~VisiteurSuppression()
///
/// Desalloue la memoire de pointeurs
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
VisiteurSuppression::~VisiteurSuppression()
{
	delete arbreTemp;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSuppression::traiter(ArbreRenduINF2990* arbre)
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
bool VisiteurSuppression::traiter(ArbreRenduINF2990* arbre)
{
	arbreTemp = arbre;

	// Visiter les enfants de l'arbre
	for (unsigned int i = 0; i < arbre->obtenirNombreEnfants(); i++)
	{
		// Traiter les enfants de l'arbre de rendu
		arbre->getEnfant(i)->accepterVisiteur(this);
	}

	arbreTemp = nullptr;

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSuppression::traiter(NoeudTable* table)
///
/// Cette fonction traite la table de l'arbre de rendu. Cette fonction 
///	retourne true pour dire que l'operation s'est faite correctement.
///
/// @param[in] table : Le noeud de type Table a traiter.
///
/// @return Retourne toujours true
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSuppression::traiter(NoeudTable* table)
{
	// Traiter les enfants selectionnes de la table
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
	{
		// Traiter les enfants de la table
		table->getEnfant(i)->accepterVisiteur(this);
	}

	for (unsigned int i = 0; i < suppression.size(); i++)
	{
		arbreTemp->effacer(suppression[i]);
	}

	return true;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool VisiteurSuppression::traiter(NoeudAbstrait* noeud)
///
/// Cette fonction traite les enfants de l'arbre de rendu. Cette fonction 
///	retourne true pour dire que l'operation s'est faite correctement.
///
/// @param[in] noeud : Noeud de l'arbre a traiter.
///
/// @return Retourne toujours true.
///
////////////////////////////////////////////////////////////////////////
bool VisiteurSuppression::traiter(NoeudAbstrait* noeud)
{
	if (noeud->estSelectionne())
	{
		// Supprimer le jumeau du portail meme s'il n'est pas selectionne
		if ((noeud->obtenirType() == "portail") && (noeud->getTwin() != nullptr))
			suppression.push_back(noeud->getTwin());
			
		suppression.push_back(noeud);
	}

	return true;
}