///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudBonus.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_BONUS_H__
#define __ARBRE_USINES_BONUS_H__

#include "UsineNoeud.h"
#include "NoeudBonus.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudBonus
/// @brief Classe qui represente une usine capable de creer des noeuds de type NoeudBonus.
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudBonus : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudBonus(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

////////////////////////////////////////////////////////////////////////
/// @fn inline UsineNoeudBonus::UsineNoeudBonus(const std::string& nom)
/// @brief Ce constructeur ne fait qu'appeler la version de la classe de base
///		   et donner des valeurs par defaut aux variables membres.
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
/// @return Aucune (constructeur).
////////////////////////////////////////////////////////////////////////
inline UsineNoeudBonus::UsineNoeudBonus(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Bonus.obj"))
{

}


////////////////////////////////////////////////////////////////////////
/// @fn NoeudAbstrait* UsineNoeudBonus::creerNoeud() const
/// @brief Cette fonction retourne un noeud nouvellement cree du type produit
///		   par cette usine, soit un NoeudBille.
/// @return Le noeud nouvellement cree.
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudBonus::creerNoeud() const
{
	auto noeud = new NoeudBonus{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_BONUS_H__