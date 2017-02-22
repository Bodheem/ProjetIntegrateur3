///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeudMalus.h
/// @author The Ballers
/// @date 2015-01-24
/// @version 1.0
///
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_MALUS_H__
#define __ARBRE_USINES_MALUS_H__

#include "UsineNoeud.h"
#include "NoeudMalus.h"

///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeudMalus
/// @brief Classe qui represente une usine capable de creer des noeuds de type NoeudMalus.
/// @author The Ballers
/// @date 2015-01-24
/// @ingroup Usine
///////////////////////////////////////////////////////////////////////////
class UsineNoeudMalus : public UsineNoeud
{
public:
	/// Constructeur
	inline UsineNoeudMalus(const std::string& nom);

	/// Creation d'un noeud
	inline virtual NoeudAbstrait* creerNoeud() const;
};

////////////////////////////////////////////////////////////////////////
/// @fn inline UsineNoeudMalus::UsineNoeudMalus(const std::string& nom)
/// @brief Ce constructeur ne fait qu'appeler la version de la classe de base
///		   et donner des valeurs par defaut aux variables membres.
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
/// @return Aucune (constructeur).
////////////////////////////////////////////////////////////////////////
inline UsineNoeudMalus::UsineNoeudMalus(const std::string& nom)
	: UsineNoeud(nom, std::string("media/objets/Malus.obj"))
{

}


////////////////////////////////////////////////////////////////////////
/// @fn NoeudAbstrait* UsineNoeudMalus::creerNoeud() const
/// @brief Cette fonction retourne un noeud nouvellement cree du type produit
///		   par cette usine, soit un NoeudBille.
/// @return Le noeud nouvellement cree.
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudMalus::creerNoeud() const
{
	auto noeud = new NoeudMalus{ obtenirNom() };
	noeud->assignerObjetRendu(&modele_, &liste_);
	return noeud;
}

#endif // __ARBRE_USINES_MALUS_H__