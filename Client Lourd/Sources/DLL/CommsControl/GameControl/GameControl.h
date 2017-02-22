//////////////////////////////////////////////////////////////////////////////
/// @file GameControl.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_GAMECONTROL_H__
#define __SERVEUR_GAMECONTROL_H__

#include <queue>
	#ifndef SERVERTESTER
#include "../../../Serveur/SharedFiles/GameRoom.h"
#include "../Sauvegarde/Snapshot.h"
	#else
#include "../../../../../Serveur/SharedFiles/GameRoom.h"
#include "../../Sauvegarde/Snapshot.h"
	#endif

////////////////////////////////////////////////////////////////////////////////
///
/// @class GameControl
/// @brief Classe représentant le modèle de jeu multijoueur
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class GameControl
{
public:
	/// Constructeur
	GameControl();
	/// Destructeur
	~GameControl();

	/// Réinitialise le modèle de jeu multijoueur
	void resetGameControl();
	
	// Crée une salle de jeu locale
	bool createGameRoom(bool isHost, User* user);

	// Quite une salle de jeu locale
	void leaveGameRoom();

	// Retourne un pointeur à la salle
	GameRoom* getRoom();

	/// Mettre le joueur à l'état Non Pret
	void setPlayerNotReady();

	/// Mettre le joueur à l'état pret
	void setPlayerReady();

	/// Mettre le joueur à l'état Mort
	void setPlayerDead();

	/// Mettre le joueur à l'état gagnant
	void setPlayerWon();

	/// Met à jour l'état de la partie
	void setGameStatus(std::string etat);

	/// Retourne l'addresse IP du host
	IP* getHostIP();

	/// Assigne l'addresse IP du host
	void setHostIP(IP* ip);

	/// Retourne l'état de la partie
	std::string getGameStatus();

	/// Retourne l'état du joueur
	std::string getPlayerStatus();

	/// Retourne le numéro du joueur fourni
	int getPlayerNumber(User* user);
	/// Retourne le numéro du joueur fourni
	int getPlayerNumber(std::string user);
	/// Retourne le nombre total de joueurs
	int getNumberOfPlayers();

	/// Met à jour le timeout
	void updateTimeout(int timeDelta);
	/// Reinitialise le timeout
	void resetTimeout();

	/// Incrémente l'index de campaigne
	void incrementCampaignIndex();
	/// Retourne l'état de campaigne
	int getCampaignIndex();
	/// Met à jour l'index de campaigne
	void setCampaignIndex(int index);

	/// État d'un joueur par default
	const std::string etatJoueurCONNECTING = "CONNE";
	/// État d'un joueur qui ne sera jamais connecté
	const std::string etatJoueurABSENT = "ABSEN";
	/// État d'un joueur connecté
	const std::string etatJoueurPRET = "READY";
	/// État d'un joueur connecté et non pret
	const std::string etatJoueurNONPRET = "NORDY";
	/// État d'un joueur qui a perdu
	const std::string etatJoueurMORT = "DEAD_";
	/// État d'un joueur qui a gagné
	const std::string etatJoueurWIN = "WIN__";
	/// État d'un joueur qui a perdu sa connexion
	const std::string etatJoueurDISCONNECT = "DISCO";

	/// État d'aucune partie en cours
	const std::string etatPartieNOTHING = "NOTHI";
	/// État de la partie en lobby
	const std::string etatPartieLOBBY = "LOBBY";
	/// État de la partie en chargement
	const std::string etatPartieDEBUT = "PREP_";
	/// État de la partie en pré-game
	const std::string etatPartieSTART = "START";
	/// État de la partie en cours
	const std::string etatPartieGAME = "GAME_";
	/// État d'une partie gagnée
	const std::string etatPartieWIN = "WIN__";
	/// État d'une partie perdue
	const std::string etatPartieLOSE = "LOSE_";
	/// État d'une partie où on a été déconnecté du Host
	const std::string etatPartieDISCONNECT = "DISCO";

private:
	/// Instance locale du lobby de jeu. Pas guaranti d'être 100% exact
	GameRoom* localGameRoom_ = nullptr;
	/// Index de la campaigne de jeu
	int campaignIndex_ = -1;
	/// État du joueur
	std::string etatPlayer_ = etatJoueurCONNECTING;
	/// État de la partie
	std::string etatPartie_ = etatPartieNOTHING;
	/// Utiliser pour calculer le timeout au Host.
	int timeoutToHostConnection = 0;
	/// Valeur maximale pour timeout
	const float TIMEOUT_TO_DISCONNECT = 8000;


	GameControl(const GameControl& that);
	GameControl& operator=(const GameControl& that);
};

#endif //__SERVEUR_GAMECONTROL_H__