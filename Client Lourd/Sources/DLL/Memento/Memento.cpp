////////////////////////////////////////////////////////////////////////////////////
/// @file Memento.cpp
/// @author The Ballers
/// @date 2015-02-25
/// @version 1.0
///
/// @ingroup Memento
////////////////////////////////////////////////////////////////////////////////////

#include "Memento.h"
#include <ArbreRenduINF2990.h>

////////////////////////////////////////////////////////////////////////
/// @fn Memento::Memento(ArbreRenduINF2990* arbre)
/// @brief Appelle la methode sauvegarder(ArbreRenduINF2990*)
/// @param[in] arbre : L'arbre que l'on veut sauvegarder
/// @return Aucune (constructeur).
////////////////////////////////////////////////////////////////////////
Memento::Memento(ArbreRenduINF2990* arbre)
{
	sauvegarder(arbre);
}


////////////////////////////////////////////////////////////////////////
/// @fn Memento::~Memento()
/// @brief Vide la structure de donnee contenant les informations de sauvegarde
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
Memento::~Memento()
{
	sauvegarde.clear();
}


////////////////////////////////////////////////////////////////////////
/// @fn void Memento::sauvegarder(ArbreRenduINF2990* arbre)
/// @brief Methode qui sauvegarde l'arbre de donnee dans une structure de donnees
/// @param[in] arbre : L'arbre que l'on veut sauvegarder
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void Memento::sauvegarder(ArbreRenduINF2990* arbre)
{
	std::vector<NoeudAbstrait*> temp = arbre->obtenirElementsTable();

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		NoeudAbstrait* noeud{ arbre->creerNoeud(temp[i]->obtenirType())};

		// Copier les informations
		noeud->assignerPositionRelative(temp[i]->obtenirPositionRelative());
		noeud->assignerEchelle(temp[i]->obtenirAgrandissement());
		noeud->assignerRotation(temp[i]->obtenirRotation());
		noeud->setColorShift(temp[i]->getColorShift());
		noeud->assignerSelection(temp[i]->estSelectionne());

		// Attribuer un numero arbitraire qui ne causera pas de problemes avec le stencil
		noeud->setNumero(1024);

		// Inserer la sauvegarde dans une structure de donnee
		sauvegarde.insert(std::make_pair(temp[i]->getNumero(), noeud));
	}
}