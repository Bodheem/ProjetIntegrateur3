//////////////////////////////////////////////////////////////////////////////
/// @file GameServerData.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_SERVERDATA_H__
#define __SERVEUR_SERVERDATA_H__
#include <string>
#include <fstream>
#include <mutex>
	#ifndef SERVERTESTER	
#include "../../../Serveur/SharedFiles/User.h"
#include "../../../Serveur/SharedFiles/IP.h"
#else
#include "../../../../../Serveur/SharedFiles/User.h"
#include "../../../../../Serveur/SharedFiles/IP.h"
#endif


////////////////////////////////////////////////////////////////////////////////
///
/// @class GameServerData
/// @brief Classe représentant les données actuellement utilisées par le serveur
///			de façon threadsafe
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class GameServerData
{
	// Haha poor practices
	friend class GameServerControl;
public:

	/// Constructeur
	GameServerData();

	/// Destructeur
	~GameServerData();

	/// Pointeur vers l'instance unique de GameServerDataPointer
	static GameServerData* GameServerDataPointer;

	/// Obtenir le pointeur statique vers le GameServerData
	static GameServerData* getPointer();

	/// Prépare la partie
	void configureGame(int numberOfPlayers, std::string mapName);
	
	/// Assigne un joueur à un IP ou le reconnecte
	bool assignPlayerIP(IP ip, int index);

	/// Retourne le nombre maximal de joueurs pour la carte
	int getNumberOfPlayers();
	
	/// Assigne l'état actuel d'un joueur selon son IP
	void setPlayerStatus(std::string status, IP* playerIP);

	/// Mettre le joueur à l'état pret
	void setPlayerReady(int player, bool status);
	/// Retourne true si tout les joueurs sont prets
	bool allPlayersReady();
	/// Retourne true si tout les joueurs sont Gagnant
	bool allPlayersWon();
	/// Retourne true si tout les joueurs sont Morts
	bool allPlayersDead();

	/// Mettre le joueur à l'état Mort
	void setPlayerDead(int player);
	// Mettre le joueur à l'état gagnant
	void setPlayerWon(int player);
	/// Mettre le joueur à l'état Disconnected
	void setPlayerDisconnected(int player);

	/// Retourne l'état actuel de la partie
	/// TOUJOURS sur 5 char
	std::string getGameStatus(int player);
	
	/// assigne l'état actuel de la partie
	void setGameStatus(std::string status);

	/// Retourne l'index de campaigne
	int getCampaignIndex();
	/// Incrémente l'index de campaigne
	void incrementCampaignIndex();

	/// Retourne le numéro du joueur selon son IP
	int getPlayerByIP(IP);

	/// Retourne tout les joueurs présentement connectés
	std::vector<IP*> getAllPlayers();
	/// Met à jour l'état des connexions des joueurs
	void updatePlayerTimeouts(int timeDelta);
	/// Remet à zero le timeout du joueur
	void resetPlayerTimeout(int noJoueur);

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

private:
	/// Mutex de sécurité
	std::mutex safetyMutex_;
	/// True when mutex is locked, for debug purposes
	bool safetyMutexIsLocked_ = false;
	/// Last call that locked safety mutex
	std::string safetyMutexLastCaller = "";

	/// Adresses IP courantes des joueurs
	IP* IPPlayer2_ = new IP();
	/// Adresses IP courantes des joueurs
	IP* IPPlayer3_ = new IP();
	/// Adresses IP courantes des joueurs
	IP* IPPlayer4_ = new IP();
	/// Nombre de joueurs, tel que fourni par l'hôte ou serveur
	int numberOfPlayers_ = -1;
	/// Nom de la carte
	std::string mapName_ = "";
	/// Index de la campagne
	int campaignIndex_ = 0;
	
	/// État des joueurs
	std::string etatPlayer1_ = etatJoueurPRET;
	/// État des joueurs
	std::string etatPlayer2_ = etatJoueurCONNECTING;
	/// État des joueurs
	std::string etatPlayer3_ = etatJoueurCONNECTING;
	/// État des joueurs
	std::string etatPlayer4_ = etatJoueurCONNECTING;
	/// État de la partie
	std::string etatPartie_ = etatPartieDEBUT;

	/// Compteurs des timeouts aux joueurs
	float timeoutCounterPlayer2_ = 0;
	/// Compteurs des timeouts aux joueurs
	float timeoutCounterPlayer3_ = 0;
	/// Compteurs des timeouts aux joueurs
	float timeoutCounterPlayer4_ = 0;
	/// Valeur maximale pour timeout
	const float TIMEOUT_TO_DISCONNECT_IN_GAME = 8000;
	/// Valeur maximale pour timeout
	const float TIMEOUT_TO_DISCONNECT_IN_LOADING = 60000;
};

#endif // __SERVEUR_SERVERDATA_H__