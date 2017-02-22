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
/// @brief Classe repr�sentant les donn�es actuellement utilis�es par le serveur
///			de fa�on threadsafe
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

	/// Pr�pare la partie
	void configureGame(int numberOfPlayers, std::string mapName);
	
	/// Assigne un joueur � un IP ou le reconnecte
	bool assignPlayerIP(IP ip, int index);

	/// Retourne le nombre maximal de joueurs pour la carte
	int getNumberOfPlayers();
	
	/// Assigne l'�tat actuel d'un joueur selon son IP
	void setPlayerStatus(std::string status, IP* playerIP);

	/// Mettre le joueur � l'�tat pret
	void setPlayerReady(int player, bool status);
	/// Retourne true si tout les joueurs sont prets
	bool allPlayersReady();
	/// Retourne true si tout les joueurs sont Gagnant
	bool allPlayersWon();
	/// Retourne true si tout les joueurs sont Morts
	bool allPlayersDead();

	/// Mettre le joueur � l'�tat Mort
	void setPlayerDead(int player);
	// Mettre le joueur � l'�tat gagnant
	void setPlayerWon(int player);
	/// Mettre le joueur � l'�tat Disconnected
	void setPlayerDisconnected(int player);

	/// Retourne l'�tat actuel de la partie
	/// TOUJOURS sur 5 char
	std::string getGameStatus(int player);
	
	/// assigne l'�tat actuel de la partie
	void setGameStatus(std::string status);

	/// Retourne l'index de campaigne
	int getCampaignIndex();
	/// Incr�mente l'index de campaigne
	void incrementCampaignIndex();

	/// Retourne le num�ro du joueur selon son IP
	int getPlayerByIP(IP);

	/// Retourne tout les joueurs pr�sentement connect�s
	std::vector<IP*> getAllPlayers();
	/// Met � jour l'�tat des connexions des joueurs
	void updatePlayerTimeouts(int timeDelta);
	/// Remet � zero le timeout du joueur
	void resetPlayerTimeout(int noJoueur);

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

private:
	/// Mutex de s�curit�
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
	/// Nombre de joueurs, tel que fourni par l'h�te ou serveur
	int numberOfPlayers_ = -1;
	/// Nom de la carte
	std::string mapName_ = "";
	/// Index de la campagne
	int campaignIndex_ = 0;
	
	/// �tat des joueurs
	std::string etatPlayer1_ = etatJoueurPRET;
	/// �tat des joueurs
	std::string etatPlayer2_ = etatJoueurCONNECTING;
	/// �tat des joueurs
	std::string etatPlayer3_ = etatJoueurCONNECTING;
	/// �tat des joueurs
	std::string etatPlayer4_ = etatJoueurCONNECTING;
	/// �tat de la partie
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