///////////////////////////////////////////////////////////////////////////////
/// @file IntelligenceProbabiliste.h
/// @author The Ballers
/// @date 2015-01-26
/// @version 1.0
/// @ingroup Comte
///////////////////////////////////////////////////////////////////////////////

/* @defgroup Global
*	@ingroup Noyau
*/

#ifndef __INTELLIGENCEPROBABILISTE_H__
#define __INTELLIGENCEPROBABILISTE_H__

#include "IntelligenceArtificielle.h"
#include <vector>
#include <set>

class NoeudAbstrait;
class NoeudPaletteG;
class NoeudPaletteD;

///////////////////////////////////////////////////////////////////////////
/// @class IntelligenceProbabiliste
///
/// @brief Cette classe est issu du patron Visiteur. Elle represente le 
///		   concept d'intelligence artificielle pour le 2eme joueur
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Global
///////////////////////////////////////////////////////////////////////////
class IntelligenceProbabiliste : public IntelligenceArtificielle
{
public:

	/// Constructeur par defaut
	IntelligenceProbabiliste(int colorshift);

	/// Destructeur
	virtual ~IntelligenceProbabiliste();

	/// Comportement du joueur virtuel
	virtual void jouer(const std::vector<NoeudAbstrait*>& listeBilles, float temps);

	/// Assigner les palettes du joueur virtuel
	virtual void assignerPalettes(std::vector<NoeudPaletteG*>& gauche, std::vector<NoeudPaletteD*>& droite);

private:

	/// Ce que le joueur virtuel doit connaitre pour prendre ses decisions
	std::vector<NoeudPaletteG*> palettesGauche_;
	std::vector<NoeudPaletteD*> palettesDroite_;

	float timerGauche_, timerDroit_;
	bool boutonGauche_{ false }, boutonDroit_{ false };

	// Probabilité d'activer la palette
	int probabilite_;

	// Savoir quel colorshift de palette le joueur controle
	int colorshift_;
};


#endif // __INTELLIGENCEPROBABILISTE_H__