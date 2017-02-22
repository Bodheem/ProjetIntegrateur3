////////////////////////////////////////////////
/// @file   IntelligenceArtificielle.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Global
////////////////////////////////////////////////

#include "IntelligenceArtificielle.h"
#include "../Arbre/Noeuds/NoeudAbstrait.h"
#include "../Arbre/Noeuds/NoeudPaletteG.h"
#include "../Arbre/Noeuds/NoeudPaletteD.h"
#include <Gl/gl.h>
#include "../../Commun/Externe/glm/include/glm/gtx/Projection.hpp"
#include <FacadeJeu.h>
#include <iostream>


////////////////////////////////////////////////////////////////////////
/// @fn IntelligenceArtificielle::IntelligenceArtificielle()
/// @brief Constructeur par defaut
/// @return Aucune (constructeur).
////////////////////////////////////////////////////////////////////////
IntelligenceArtificielle::IntelligenceArtificielle(int colorshift)
{
	timerGauche_ = 0;
	timerDroit_ = 0;

	colorshift_ = colorshift;
}


////////////////////////////////////////////////////////////////////////
/// @fn IntelligenceArtificielle::~IntelligenceArtificielle()
/// @brief Destructeur.
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
IntelligenceArtificielle::~IntelligenceArtificielle()
{
	palettesDroite_.clear();
	palettesGauche_.clear();
}


////////////////////////////////////////////////////////////////////////
/// @fn IntelligenceArtificielle::jouer(std::vector<NoeudAbstrait*> listeBilles)
///	@brief Methode qui implemente la logique du comportement que doit adopter le joueur virtuel.
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void IntelligenceArtificielle::jouer(const std::vector<NoeudAbstrait*>& listeBilles, float temps)
{
	// Regarder pour toutes les billes
	for (unsigned int i = 0; i < listeBilles.size(); ++i)
	{
		/// Traiter les palettes gauches
		// Si le bouton n'est pas pese, faire la verification habituelle
		if (!boutonGauche_)
		{
			if (timerGauche_ > 0)
			{
				timerGauche_ -= temps;
			}
			else
			{
				for (NoeudPaletteG* paletteGauche : palettesGauche_)
				{
					if (paletteGauche == nullptr)
						continue;

					if (paletteGauche->estActiveeParBille(listeBilles[i]))
					{
						FacadeJeu::obtenirInstance()->activerPalettesGauches(colorshift_);
						timerGauche_ = 0.25;
						boutonGauche_ = true;
						break;
					}
				}
			}
		}
		else
		{
			// Si le bouton EST pese, compter du temps jusqu'a une certaine valeur et relacher le bouton apres cette valeur.
			if (timerGauche_ > 0)
			{
				timerGauche_ -= temps;
			}
			else
			{
				FacadeJeu::obtenirInstance()->desactiverPalettesGauches(colorshift_);
				timerGauche_ = 0.4f;
				boutonGauche_ = false;
			}
		}
		// Meme chose pour le bouton de droite.
		if (!boutonDroit_)
		{
			if (timerDroit_ > 0)
			{
				timerDroit_ -= temps;
			}
			else
			{
				for (NoeudPaletteD* paletteDroite : palettesDroite_)
				{
					if (paletteDroite == nullptr)
						continue;

					if (paletteDroite->estActiveeParBille(listeBilles[i]))
					{
						FacadeJeu::obtenirInstance()->activerPalettesDroites(colorshift_);
						timerDroit_ = 0.25;
						boutonDroit_ = true;
						break;
					}
				}
			}
		}
		else
		{
			if (timerDroit_ > 0)
			{
				timerDroit_ -= temps;
			}
			else
			{
				FacadeJeu::obtenirInstance()->desactiverPalettesDroites(colorshift_);
				timerDroit_ = 0.4f;
				boutonDroit_ = false;
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn bool IntelligenceArtificielle::assignerPalettes(std::set<NoeudPaletteG*>& gauche, const std::set<NoeudPaletteD*>& droite)
///	@brief Methode qui assigne au joueur virtuel sa liste de palette
/// @param[in] gauche, droite : ses palettes gauches et droites
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void IntelligenceArtificielle::assignerPalettes(std::vector<NoeudPaletteG*>& gauche, std::vector<NoeudPaletteD*>& droite)
{
	palettesGauche_ = gauche;
	palettesDroite_ = droite;
}