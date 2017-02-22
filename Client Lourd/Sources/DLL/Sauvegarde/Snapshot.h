//////////////////////////////////////////////////////////////////////////////
/// @file MapSnapShot.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SAUVEGARDE_SNAPSHOT_H__
#define __SAUVEGARDE_SNAPSHOT_H__

#include <string>

class ArbreRenduINF2990;

////////////////////////////////////////////////////////////////////////////////
/// @class MapSnapShot
/// @brief Classe représentant un snapshot de la carte de jeu actuelle
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class Snapshot
{
public:

	/// Constructeur Serveur
	Snapshot();

	/// Destructeur
	~Snapshot();

	/// Obtenir l'information formatée selon un format XML
	static std::string toString(ArbreRenduINF2990* arbre);

	/// Appliquer les informations formatées
	static void applySnapshot(std::string data, ArbreRenduINF2990* arbre);

	// Tick a envoyer
	static int tick_;

	// Dernier tick reçu
	static int receiveTick_;
};

#endif // __SAUVEGARDE_SNAPSHOT_H__