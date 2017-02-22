//////////////////////////////////////////////////////////////////////////////
/// @file FacadeReseau.h
/// @author The New Ballers
/// @date 2016-02-19
/// @version 1.0 
///
/// @ingroup Application
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_FACADERESEAU_H__
#define __APPLICATION_FACADERESEAU_H__
#include <string>

class Joueur;
class CommsControl;

///////////////////////////////////////////////////////////////////////////
/// @class FacadeReseau
/// @brief Classe qui constitue une interface (une facade) sur l'ensemble
///        du composante de reseau.
///
/// @author The New Ballers
/// @date 2016-02-20
/// @ingroup Application
///////////////////////////////////////////////////////////////////////////
class FacadeReseau
{
public:

	/// Obtient l'instance unique de la classe.
	static FacadeReseau* obtenirInstance();

	/// Libere l'instance unique de la classe.
	static void libererInstance();

	/// Initialiser un compte hors-ligne
	char* InitializeOffline();

	/// Envoyer un message
	void SendChatMessage(const char* lobbyName, const char* chatMessage) const;

	/// Obtenir la liste des "ChatRoom"
	char* GetLobbies() const;

	/// Obtenir les messages d'un "ChatRoom"
	char* GetMessages(char* lobbyName) const;

	/// Obtenir tous les messages d'un "ChatRoom"
	char* GetAllMessages(char* lobbyName) const;

	/// Mettre a jour l'historique des messages
	bool GetChatHistoryUpdates() const;

	/// Authentification utilisateur
	bool LogIn(char* username, char* password);

	/// Deconnexion de l'utilisateur
	bool LogOff();

	/// Deconnexion finale du serveur
	bool DisconnectFromServer();

	/// Creation de compte utilisateur
	bool CreateAccount(char* username, char* password, char* email) const;

	/// Mettre a jour les informations usagers
	bool updateInfoCompte(std::string infos) const;

	/// Retourner les informations du compte selon le bon format
	std::string obtenirInfoCompte() const;

	/// Donner des points
	void addShekels(unsigned int shekels);
	/// Donner des achievement points
	void addAchievementPoints(unsigned int achPoints);

	/// Pour l'adresse IP du serveur
	bool SendIP(char* ipAddress) const;

	/// Obtenir le compte
	Joueur* obtenirCompte() const;

	///Password recovery
	bool requestPasswordRecovery(char* userName);

	/// Creer une partie multijoueur
	bool createGame(char* mapName, char* password, bool instaDeath, int gameTime,int gameType);

	/// Debuter une partie
	bool startGame();

	/// Obtenir les parties disponibles
	std::string GetAvailableGames();

	/// Joindre une partie
	bool joinGame(char * hostName, char* mapName, char* password);

	/// Quitter un lobby de jeu
	bool leaveGame();

	/// Matchmaking
	int matchmaking();

	/// Obtenir l'information sur la partie
	std::string GetGameInfo();

	/// ResetMultiplayer
	void resetMultiplayer();

	/// Obtenir l'etat du jeu
	std::string GetGameState();

	/// Dire au serveur que le joueur est pret
	bool playerIsReady(bool playerReady);

	/// Obtenir l'information sur le statut des joueurs
	std::string GetPlayersInfo();

	/// Savoir si le jeu est commence
	bool isGameStarted();

	/// Savoir si on est en mode compétitif
	bool isCompetitif() const;

	/// Obtenir le nombre de joueur dans la game
	int obtenirNombreJoueur() const;

	/// Obtenir le numero du joueur
	int obtenirNumeroJoueur();

	/// Montrer qu'un joueur a perdu
	void setPlayerLost();

	/// Host dit que le player a lost
	void asHostSetPlayerLost(int index);

	/// Host dit que le player a win
	void asHostSetPlayerWin(int index);

	/// Fonction test
	void fonctionTest();
	
	// Preparer prochaine zone
	void prepareNextGame();

	/// obtenir l'index de la game
	int getCurrentGameIndex();

	void executeDownloadMaps();
	void executeUploadMaps();

private:

	/// Constructeur.
	FacadeReseau();

	/// Destructeur.
	~FacadeReseau();

	/// Constructeur copie desactive.
	FacadeReseau(const FacadeReseau&) = delete;

	/// Operateur d'assignation desactive.
	FacadeReseau& operator=(const FacadeReseau&) = delete;

	/// Pointeur vers l'instance unique de la classe.
	static FacadeReseau* instance_;

	/// Pointeur vers un compte
	Joueur* compte_;

	/// Pointeur vers le CommsControl
	CommsControl* commsControl_;

	/// Type de partie
	bool isCompetitif_;

};

#endif // __APPLICATION_FACADEMODELE_H__
