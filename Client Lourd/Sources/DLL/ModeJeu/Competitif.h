//////////////////////////////////////////////////////////////////////////////
/// @file Competitif.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup ModeJeu
//////////////////////////////////////////////////////////////////////////////

#ifndef __MODEJEU_COMPETITIF_H__
#define __MODEJEU_COMPETITIF_H__

#include "ModeJeu.h"

class ArbreRenduINF2990;

////////////////////////////////////////////////////////////////////////////////
/// @class Competitif
/// @brief Classe représentant un snapshot de la carte de jeu actuelle
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class Competitif : public ModeJeu
{
public:

	/// Constructeur Serveur
	Competitif();

	/// Destructeur
	virtual ~Competitif();

	/// Initiliaser le mode de jeu
	virtual void initialiserMode();
};

#endif // __MODEJEU_COMPETITIF_H__