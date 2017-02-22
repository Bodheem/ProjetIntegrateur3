//////////////////////////////////////////////////////////////////////////////
/// @file ModeJeu.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup ModeJeu
//////////////////////////////////////////////////////////////////////////////

#ifndef __MODEJEU_MODEJEU_H__
#define __MODEJEU_MODEJEU_H__

#include <string>

class ArbreRenduINF2990;

////////////////////////////////////////////////////////////////////////////////
/// @class ModeJeu
/// @brief Classe qui représente un mode de jeu
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class ModeJeu
{
public:

	/// Constructeur Serveur
	ModeJeu();

	/// Destructeur
	virtual ~ModeJeu();

	/// Initiliaser le mode de jeu
	virtual void initialiserMode();

protected:

	// Le nombre de joueur dans la partie
	int nombreJoueur_;

};

#endif // __MODEJEU_MODEJEU_H__