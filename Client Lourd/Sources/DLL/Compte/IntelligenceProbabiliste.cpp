////////////////////////////////////////////////
/// @file   IntelligenceProbabiliste.cpp
/// @author The Ballers
/// @date   2015-02-01
///
/// @ingroup Global
////////////////////////////////////////////////

#include "IntelligenceProbabiliste.h"
#include "../Arbre/Noeuds/NoeudAbstrait.h"
#include "../Arbre/Noeuds/NoeudPaletteG.h"
#include "../Arbre/Noeuds/NoeudPaletteD.h"
#include <Gl/gl.h>
#include "../../Commun/Externe/glm/include/glm/gtx/Projection.hpp"
#include <FacadeJeu.h>


////////////////////////////////////////////////////////////////////////
/// @fn IntelligenceProbabiliste::IntelligenceProbabiliste()
/// @brief Constructeur par defaut
/// @return Aucune (constructeur).
////////////////////////////////////////////////////////////////////////
IntelligenceProbabiliste::IntelligenceProbabiliste(int colorshift) : IntelligenceArtificielle(colorshift)
{
	timerGauche_ = 0;
	timerDroit_ = 0;
	colorshift_ = colorshift;

	probabilite_ = 590;
	srand(time(nullptr));
}


////////////////////////////////////////////////////////////////////////
/// @fn IntelligenceProbabiliste::~IntelligenceProbabiliste()
/// @brief Destructeur.
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
IntelligenceProbabiliste::~IntelligenceProbabiliste()
{
	palettesDroite_.clear();
	palettesGauche_.clear();
}


////////////////////////////////////////////////////////////////////////
/// @fn IntelligenceProbabiliste::jouer(std::vector<NoeudAbstrait*> listeBilles)
///	@brief Methode qui implemente la logique du comportement que doit adopter le joueur virtuel.
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void IntelligenceProbabiliste::jouer(const std::vector<NoeudAbstrait*>& listeBilles, float temps)
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
					if (paletteGauche->estActiveeParBille(listeBilles[i]))
					{
						int random = rand() % 601;
						if (random > probabilite_)
						{
							FacadeJeu::obtenirInstance()->activerPalettesGauches(paletteGauche->getColorShift());
							timerGauche_ = 0.25;
							boutonGauche_ = true;
							break;
						}
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
				FacadeJeu::obtenirInstance()->desactiverPalettesGauches(palettesGauche_[0]->getColorShift());
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
					int random = rand() % 601;
					if (random > probabilite_)
					{
						if (paletteDroite->estActiveeParBille(listeBilles[i]))
						{
							FacadeJeu::obtenirInstance()->activerPalettesDroites(paletteDroite->getColorShift());
							timerDroit_ = 0.25;
							boutonDroit_ = true;
							break;
						}
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
				FacadeJeu::obtenirInstance()->desactiverPalettesDroites(palettesDroite_[0]->getColorShift());
				timerDroit_ = 0.4f;
				boutonDroit_ = false;
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn bool IntelligenceProbabiliste::assignerPalettes(const std::set<NoeudPaletteG*>& gauche, const std::set<NoeudPaletteD*>& droite)
///	@brief Methode qui assigne au joueur virtuel sa liste de palette
/// @param[in] gauche, droite : ses palettes gauches et droites
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void IntelligenceProbabiliste::assignerPalettes(std::vector<NoeudPaletteG*>& gauche, std::vector<NoeudPaletteD*>& droite)
{
	palettesGauche_ = gauche;
	palettesDroite_ = droite;
}