///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurPalettes.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURPALETTES_H__
#define __VISITEURS_VISITEURPALETTES_H__

#include "VisiteurAbstrait.h"
#include <ctime>

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurPalettes
/// @brief Classe pour desactiver temporairement l'effet des portails
///
///        Instancier cette classe. Ensuite, appeler la methode accepterVisiteur()
///		   de l'arbre de rendu et lui fournir CE visiteur en parametre
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurPalettes : public VisiteurAbstrait
{
public:

	/// Constructeur par defaut
	VisiteurPalettes(std::clock_t time);

	/// Destructeur
	~VisiteurPalettes();

	/// Traiter un arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudPaletteD* noeud);
	virtual bool traiter(NoeudPaletteG* noeud);

private:

	// Temps auquel on commence a desactiver les portails
	std::clock_t time_;
};

#endif //__VISITEURS_VISITEURPALETTES_H__