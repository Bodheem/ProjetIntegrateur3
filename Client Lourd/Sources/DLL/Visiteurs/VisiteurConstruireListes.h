///////////////////////////////////////////////////////////////////////////////
/// @file VisiteurDeselectionnerTout.h
/// @author The Ballers
/// @date 2015-02-01
/// @version 1.0
///
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////////
#ifndef __VISITEURS_VISITEURCONSTRUIRELISTES_H__
#define __VISITEURS_VISITEURCONSTRUIRELISTES_H__

#include "NoeudAbstrait.h"
#include "NoeudPaletteG.h"
#include "NoeudPaletteD.h"
#include "VisiteurAbstrait.h"

///////////////////////////////////////////////////////////////////////////
/// @class VisiteurDeselectionnerTout
/// @brief Classe pour deselectionner tous les objets de la table de rendu.
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Visiteur
///////////////////////////////////////////////////////////////////////////
class VisiteurConstruireListes : public VisiteurAbstrait
{
public:

	/// Constructeur par defaut
	VisiteurConstruireListes(std::vector<std::vector<NoeudPaletteG*>>& palettesGauches, 
							std::vector<std::vector<NoeudPaletteD*>>& palettesDroite);

	/// Destructeur
	~VisiteurConstruireListes();

	/// Traiter une operation sur l'arbre de rendu et ses enfants
	virtual bool traiter(ArbreRenduINF2990* arbre);
	virtual bool traiter(NoeudAbstrait* noeud);
	virtual bool traiter(NoeudTable* table);
	virtual bool traiter(NoeudPaletteG* noeud);
	virtual bool traiter(NoeudPaletteD* noeud);

private:
	
	// L'index du premier tableau correspond au colorshift
	std::vector<std::vector<NoeudPaletteG*>>* palettesGauches_;
	std::vector<std::vector<NoeudPaletteD*>>* palettesDroites_;
};

#endif //__VISITEURS_VISITEURCONSTRUIRELISTES_H__