//////////////////////////////////////////////////////////////////////////////
/// @file Cooperatif.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup ModeJeu
//////////////////////////////////////////////////////////////////////////////

#ifndef __MODEJEU_COOPERATIF_H__
#define __MODEJEU_COOPERATIF_H__

#include "ModeJeu.h"
#include <vector>

class ArbreRenduINF2990;
class NoeudAbstrait;

////////////////////////////////////////////////////////////////////////////////
/// @class Cooperatif
/// @brief 
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class Cooperatif : public ModeJeu
{
public:

	/// Constructeur Serveur
	Cooperatif();

	/// Destructeur
	virtual ~Cooperatif();

	/// Initiliaser le mode de jeu
	virtual void initialiserMode();

private:

	// Initialiser la carte avec 3 joueurs
	void initialiserTroisJoueurs(std::vector<NoeudAbstrait*>& player1, std::vector<NoeudAbstrait*>& player2);

	// Initialiser la carte avec 4 joueurs
	void initialiserQuatreJoueurs(std::vector<NoeudAbstrait*>& player1, std::vector<NoeudAbstrait*>& player2);
};

#endif // __MODEJEU_COOPERATIF_H__