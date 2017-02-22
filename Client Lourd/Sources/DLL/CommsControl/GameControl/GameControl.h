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
/// @brief Classe repr�sentant le mod�le de jeu multijoueur
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

	/// R�initialise le mod�le de jeu multijoueur
	void resetGameControl();
	
	// Cr�e une salle de jeu locale
	bool createGameRoom(bool isHost, User* user);

	// Quite une salle de jeu locale
	void leaveGameRoom();

	// Retourne un pointeur � la salle
	GameRoom* getRoom();

	/// Mettre le joueur � l'�tat Non Pret
	void setPlayerNotReady();

	/// Mettre le joueur � l'�tat pret
	void setPlayerReady();

	/// Mettre le joueur � l'�tat Mort
	void setPlayerDead();

	/// Mettre le joueur � l'�tat gagnant
	void setPlayerWon();

	/// Met � jour l'�tat de la partie
	void setGameStatus(std::string etat);

	/// Retourne l'addresse IP du host
	IP* getHostIP();

	/// Assigne l'addresse IP du host
	void setHostIP(IP* ip);

	/// Retourne l'�tat de la partie
	std::string getGameStatus();

	/// Retourne l'�tat du joueur
	std::string getPlayerStatus();

	/// Retourne le num�ro du joueur fourni
	int getPlayerNumber(User* user);
	/// Retourne le num�ro du joueur fourni
	int getPlayerNumber(std::string user);
	/// Retourne le nombre total de joueurs
	int getNumberOfPlayers();

	/// Met � jour le timeout
	void updateTimeout(int timeDelta);
	/// Reinitialise le timeout
	void resetTimeout();

	/// Incr�mente l'index de campaigne
	void incrementCampaignIndex();
	/// Retourne l'�tat de campaigne
	int getCampaignIndex();
	/// Met � jour l'index de campaigne
	void setCampaignIndex(int index);

	/// �tat d'un joueur par default
	const std::string etatJoueurCONNECTING = "CONNE";
	/// �tat d'un joueur qui ne sera jamais connect�
	const std::string etatJoueurABSENT = "ABSEN";
	/// �tat d'un joueur connect�
	const std::string etatJoueurPRET = "READY";
	/// �tat d'un joueur connect� et non pret
	const std::string etatJoueurNONPRET = "NORDY";
	/// �tat d'un joueur qui a perdu
	const std::string etatJoueurMORT = "DEAD_";
	/// �tat d'un joueur qui a gagn�
	const std::string etatJoueurWIN = "WIN__";
	/// �tat d'un joueur qui a perdu sa connexion
	const std::string etatJoueurDISCONNECT = "DISCO";

	/// �tat d'aucune partie en cours
	const std::string etatPartieNOTHING = "NOTHI";
	/// �tat de la partie en lobby
	const std::string etatPartieLOBBY = "LOBBY";
	/// �tat de la partie en chargement
	const std::string etatPartieDEBUT = "PREP_";
	/// �tat de la partie en pr�-game
	const std::string etatPartieSTART = "START";
	/// �tat de la partie en cours
	const std::string etatPartieGAME = "GAME_";
	/// �tat d'une partie gagn�e
	const std::string etatPartieWIN = "WIN__";
	/// �tat d'une partie perdue
	const std::string etatPartieLOSE = "LOSE_";
	/// �tat d'une partie o� on a �t� d�connect� du Host
	const std::string etatPartieDISCONNECT = "DISCO";

private:
	/// Instance locale du lobby de jeu. Pas guaranti d'�tre 100% exact
	GameRoom* localGameRoom_ = nullptr;
	/// Index de la campaigne de jeu
	int campaignIndex_ = -1;
	/// �tat du joueur
	std::string etatPlayer_ = etatJoueurCONNECTING;
	/// �tat de la partie
	std::string etatPartie_ = etatPartieNOTHING;
	/// Utiliser pour calculer le timeout au Host.
	int timeoutToHostConnection = 0;
	/// Valeur maximale pour timeout
	const float TIMEOUT_TO_DISCONNECT = 8000;


	GameControl(const GameControl& that);
	GameControl& operator=(const GameControl& that);
};

#endif //__SERVEUR_GAMECONTROL_H__