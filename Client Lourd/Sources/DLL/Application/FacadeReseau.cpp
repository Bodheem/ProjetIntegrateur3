///////////////////////////////////////////////////////////////////////////////
/// @file FacadeReseau.cpp
/// @author The New Ballers
/// @date 2016-02-22
/// @version 1.0
/// @ingroup Application
///////////////////////////////////////////////////////////////////////////////

#include "FacadeReseau.h"
#include "../CommsControl/CommsControl.h"
#include "../Compte/Compte.h"
#include "../Compte/CompteOffline.h"
#include <iostream>
#include "Objbase.h"


/// Pointeur vers l'instance unique de la classe.
FacadeReseau* FacadeReseau::instance_{ nullptr };


////////////////////////////////////////////////////////////////////////
/// @fn FacadeReseau::FacadeReseau()
/// @brief 
/// @return Une instance de la classe
////////////////////////////////////////////////////////////////////////
FacadeReseau::FacadeReseau()
{
	commsControl_ = new CommsControl();
	compte_ = nullptr;
	isCompetitif_ = false;
}


////////////////////////////////////////////////////////////////////////
/// @fn FacadeReseau* FacadeReseau::obtenirInstance()
/// @brief Cette fonction retourne un pointeur vers l'instance unique de la
///		   classe.  Si cette instance n'a pas ete creee, elle la cree.  Cette
///		   creation n'est toutefois pas necessairement "thread-safe", car
///		   aucun verrou n'est pris entre le test pour savoir si l'instance
///		   existe et le moment de sa creation.
/// @return Un pointeur vers l'instance unique de cette classe.
////////////////////////////////////////////////////////////////////////
FacadeReseau* FacadeReseau::obtenirInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new FacadeReseau();
	}
	return instance_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeReseau::libererInstance()
/// @brief Cette fonction libere l'instance unique de cette classe.
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void FacadeReseau::libererInstance()
{
	delete instance_;
	instance_ = nullptr;
}


////////////////////////////////////////////////////////////////////////
/// @fn FacadeReseau::~FacadeReseau()
/// @brief Ce destructeur libere les objets du modele.
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
FacadeReseau::~FacadeReseau()
{
	delete commsControl_;
	delete compte_;
}


////////////////////////////////////////////////////////////////////////
/// @fn std::string FacadeReseau::InitializeOffline()
///	@brief Initialise un compte de type Offline
/// @return Le nom du joueur
////////////////////////////////////////////////////////////////////////
char* FacadeReseau::InitializeOffline()
{
	if (compte_ != nullptr)
	{
		delete instance_->compte_;
		instance_->compte_ = nullptr;
	}
	
	compte_ = new CompteOffline();

	std::string name = compte_->getName();
	const char* value = name.c_str();
	size_t stSize = strlen(value) + sizeof(char);

	char* pszReturn = nullptr;

	pszReturn = static_cast<char*>(::CoTaskMemAlloc(stSize));
	// Copy the contents of test1
	// to the memory pointed to by pszReturn.
	strcpy_s(pszReturn, stSize, value);
	// Return pszReturn.
	return pszReturn;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeReseau::SendChatMessage(char* lobbyName, char* chatMessage)
/// @brief Envoie les messages entres par l'utilisateur du C#
/// @return bool, true si la souris se situe sur un objet deja selectionne.
///////////////////////////////////////////////////////////////////////////////
void FacadeReseau::SendChatMessage(const char* lobbyName, const char* chatMessage) const
{
	std::string myMessage(chatMessage);
	std::string lobbyRoom(lobbyName);
	commsControl_->executeSendNewChatMessage(myMessage, lobbyRoom);
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeReseau::GetLobbies()
/// @brief Va chercher les lobbies
/// @return char*, tous les lobbies
///////////////////////////////////////////////////////////////////////////////
char* FacadeReseau::GetLobbies() const
{
	std::vector<std::string> roomList;
	std::string str = "";
	commsControl_->executeUpdateChatRoomList(roomList);

	for each (std::string roomName in roomList)
	{
		str.append(roomName + "\n");
	}

	const char* value = str.c_str();
	size_t stSize = strlen(value) + sizeof(char);

	char* pszReturn = nullptr;

	pszReturn = (char*)::CoTaskMemAlloc(stSize);
	// Copy the contents of test1
	// to the memory pointed to by pszReturn.
	strcpy_s(pszReturn, stSize, value);
	// Return pszReturn.
	return pszReturn;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeReseau::GetMessages(char* lobbyName)
/// @brief Va chercher les messages recus par le client
/// @return char*, les messages du serveur
///////////////////////////////////////////////////////////////////////////////
char* FacadeReseau::GetMessages(char* lobbyName) const
{
	std::string nouveauxMessages = "";
	std::vector<std::string> messages;

	if (!commsControl_->RequestMessageHistoryUpdate(lobbyName, messages))
	{
		// Non bloquant: ne retournera pas de messages
	}
	else
	{
		for each (std::string message in messages)
		{
			nouveauxMessages.append(message);
		}
	}

	const char* value = nouveauxMessages.c_str();
	size_t stSize = strlen(value) + sizeof(char);

	char* pszReturn = NULL;

	pszReturn = (char*)::CoTaskMemAlloc(stSize);
	// Copy the contents of test1
	// to the memory pointed to by pszReturn.
	strcpy_s(pszReturn, stSize, value);
	// Return pszReturn.
	return pszReturn;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeReseau::GetAllMessages(char* lobbyName)
/// @brief Va chercher les tous les messages d'une room
/// @return aucun.
///////////////////////////////////////////////////////////////////////////////
char* FacadeReseau::GetAllMessages(char* lobbyName) const
{
	std::string nouveauxMessages = "";
	std::vector<std::string> messages;

	if (!commsControl_->RequestMessageHistoryComplete(lobbyName, messages))
	{
		// Non bloquant: ne retournera pas de messages
	}
	else
	{
		for each (std::string message in messages)
		{
			nouveauxMessages.append(message);
		}
	}

	const char* value = nouveauxMessages.c_str();
	size_t stSize = strlen(value) + sizeof(char);

	char* pszReturn = NULL;

	pszReturn = (char*)::CoTaskMemAlloc(stSize);
	// Copy the contents of test1
	// to the memory pointed to by pszReturn.
	strcpy_s(pszReturn, stSize, value);
	// Return pszReturn.
	return pszReturn;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeReseau::GetChatHistoryUpdates()
/// @brief Va chercher les messages recus par le client
/// @return aucun.
///////////////////////////////////////////////////////////////////////////////
bool FacadeReseau::GetChatHistoryUpdates() const
{
	if (commsControl_->getUser() != nullptr)
		return commsControl_->executeRequestMessageHistoryUpdate();
	else
		return false;
	
}



///////////////////////////////////////////////////////////////////////////////
/// @fn bool FacadeReseau::LogIn(char* username, char* password)
/// @brief Permet de se connecter au serveur.
/// @return bool, true si l'authentification est reussie
///////////////////////////////////////////////////////////////////////////////
bool FacadeReseau::LogIn(char* username, char* password)
{
	bool success = false;
	std::string _username(username);
	std::string _password(password);

	if (!commsControl_->executeLogin(_username, _password, success))
	{

	}

	if (success)
	{
		if (compte_ != nullptr)
		{
			delete compte_;
			compte_ = nullptr;
		}

		bool userInfo = false;
		userInfo &= commsControl_->executeGetUserAccountInfo(userInfo);
		compte_ = new Compte(commsControl_->getUser());
		std::vector<std::string> roomNames;
		commsControl_->executeUpdateChatRoomList(roomNames);
	}

	return success;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn bool FacadeReseau::LogOff()
/// @brief Permet de se deconnecter du compte utilisateur du serveur.
/// @return bool, true si la deconnexion est reussie
///////////////////////////////////////////////////////////////////////////////
bool FacadeReseau::LogOff()
{
	bool success = false;
	if (!commsControl_->executeLogout(success))
	{

	}

	if (success)
	{
		delete compte_;
		compte_ = nullptr;
	}

	return success;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn bool FacadeReseau::DisconnectFromServer()
/// @brief Permet de se deconnecter du serveur.
/// @return bool, true si la deconnexion est reussie
///////////////////////////////////////////////////////////////////////////////
bool FacadeReseau::DisconnectFromServer()
{
	bool success = false;
	success = commsControl_->executeAbandonSocket();
	delete commsControl_;
	commsControl_ = new CommsControl();
	return success;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn bool FacadeReseau::CreateAccount(char* userName, char* password, char* email)
/// @brief Permet de creer un compte.
/// @param[in] username : Le nom de l'utilisateur
/// @param[in] password : Le mot de passe de l'utilisateur
/// @param[in] email : Le courriel de l'utilisateur
/// @return bool, true si l'authentification est reussie
///////////////////////////////////////////////////////////////////////////////
bool FacadeReseau::CreateAccount(char* username, char* password, char* email) const
{
	bool success = false;
	std::string _username(username);
	std::string _password(password);
	std::string _email(email);

	if (!commsControl_->executeCreateUserAccount(username, password, email, success))
	{
		return false;
	}
	return success;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn bool FacadeReseau::SendIP(char* ipAddress)
/// @brief Permet d'obtenir l'addresse IP entree en c#
/// @param[in] ipAddress : L'addresse IP
/// @return bool, true si l'authentification est reussie
///////////////////////////////////////////////////////////////////////////////
bool FacadeReseau::SendIP(char* ipAddress) const
{
	std::string _ipAddress(ipAddress);
	std::cout << "IP ADDRESS : " + _ipAddress << std::endl;
	bool success = commsControl_->initializeCommunications(_ipAddress);
	return success;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool FacadeReseau::updateInfoCompte()
///	@brief 
/// @return 
////////////////////////////////////////////////////////////////////////
bool FacadeReseau::updateInfoCompte(std::string infos) const
{
	bool success = false;

	compte_->setInformationFromString(infos);
	std::vector<std::string> info = compte_->getInformationsToVector();

	commsControl_->getUser()->setBasicInfo(info);
	commsControl_->getUser()->setAvatarUnlocked(compte_->getAvatarUnlocked());
	commsControl_->getUser()->setAchievementsInfo(compte_->getAchievementUnlocked());
	commsControl_->getUser()->setMapInfo(compte_->getMapUnlocked());
	commsControl_->getUser()->assignerStatistique(compte_->obtenirStatistique());

	if (!commsControl_->executeUpdateUserAccountInfo(success))
		return false;
	return success;
}


////////////////////////////////////////////////////////////////////////
/// @fn std::string FacadeReseau::obtenirCompte()
///	@brief Retourne le compte
/// @return le compte
////////////////////////////////////////////////////////////////////////
Joueur* FacadeReseau::obtenirCompte() const
{
	return compte_;
}

/// Retourner les informations du compte selon le bon format
std::string FacadeReseau::obtenirInfoCompte() const
{
	bool userInfo;
	commsControl_->executeGetUserAccountInfo(userInfo);
	compte_->assignerStatistique(commsControl_->getUser()->obtenirStatistique());

	return compte_->getAllInformations();
}

// Ajoute des shekels au joueur en cours et met a jour le serveur
void FacadeReseau::addShekels(unsigned int shekels)
{

	compte_->addShekels(shekels);
	bool success = false;

	std::vector<std::string> info = compte_->getInformationsToVector();

	commsControl_->getUser()->setBasicInfo(info);
	commsControl_->executeUpdateUserAccountInfo(success) && success;
}

// Ajoute des achievements points au joueur en cours et met a jour le serveur
void FacadeReseau::addAchievementPoints(unsigned int achPoints)
{
	compte_->addAchievementPoints(achPoints);
}

// Initialise la reinitialisation des mots de passes sur le serveur
bool FacadeReseau::requestPasswordRecovery(char* userName)
{
	bool succes = false;
	return commsControl_->executeResetUserAccountPassword(userName, succes) && succes;
}


	#pragma region Multiplayer

///////////////////////////////////////////////////////////////////////////////
///
/// @fn  bool createGame(char* mapName, char* password, bool instaDeath, int gameTime)
/// @brief Fonction qui envoie au serveur l'information d'une partie MJ a creer
/// @return bool si operation reussie
///
///////////////////////////////////////////////////////////////////////////////
bool FacadeReseau::createGame(char* mapName, char* password, bool instaDeath, int gameTime,int gameType)
{
	std::string user = commsControl_->getUser()->getUserName();
	bool success = false;
	if (!commsControl_->executeCreateGameRoom(success) || !success)
	{
		// error handling
		return false;
	}
	std::vector<std::string> info, updatedInfo;
	info.push_back(user);
	info.push_back(password);
	info.push_back(mapName);
	info.push_back(std::to_string(gameType));
	info.push_back(std::to_string(gameTime));
	info.push_back(std::to_string(instaDeath));
	if (!commsControl_->executeUpdateGameRoomInfo(info, updatedInfo, success) || !success)
	{
		// more error handling
		return false;
	}
	return true;
}

// Débute la partie
bool FacadeReseau::startGame() 
{
	bool success = false;
	if (!commsControl_->executeStartGame(success) || !success)
	{
		// error handling
		return false;
	}
	return true;
}

// Retourne une liste des parties disponibles a joindre sur le serveur
std::string FacadeReseau::GetAvailableGames()
{
	std::vector<std::string> info;
	if (!commsControl_->executeUpdateGameRoomList(info))
	{
		// error handling
		return "false";
	}
	std::string infoFormat = "";
	for (auto inf : info)
		infoFormat += inf + "\n";
	return infoFormat;
}

// Rejoindre une partie MP en fournissant mot de passe et hostname
bool FacadeReseau::joinGame(char * hostName, char* mapName, char* password)
{
	bool success = false;
	if (!commsControl_->executeJoinGameRoom(hostName, password, success) || !success)
	{
		// error handling
		return false;
	}
	return true;
}

// Quite une partie en cours
bool FacadeReseau::leaveGame()
{
	bool success = false;
	if (!commsControl_->executeLeaveGameRoom(success) || !success)
	{
		// error handling
		return false;
	}
	return true;
}

// Automatiquement joindre ou creer une partie MP
int FacadeReseau::matchmaking()
{
	bool success = false;
	bool host = false;
	if (!commsControl_->executeMatchmaking(success,host))
	{
		// error handling
		return 0;
	}
	// User has joined a game
	if (success && !host)
	{
		
		return 1;
	}
	// User is a new host
	else if (success && host)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

// Obtenir les informations de la partie en cours
std::string FacadeReseau::GetGameInfo()
{
	// Format :	all info in 1 string, all data is separated by ":" 
	// info : MAPNAME, INSTADEATH_MODE ( bool), TIME( in minutes, return a negative value for no time limit )
	std::vector<std::string> info, updatedInfo;
	info.push_back("");
	info.push_back("");
	info.push_back("");
	info.push_back("");
	info.push_back("");
	info.push_back("");
	bool success = false;
	if (!commsControl_->executeUpdateGameRoomInfo(info, updatedInfo, success))
	{
		// more error handling
		return "false";
		//throw std::exception("Failure");
	}
	std::string instaDeath = updatedInfo.back();
	updatedInfo.pop_back();
	std::string gameTime = updatedInfo.back();
	updatedInfo.pop_back();
	std::string gameType = updatedInfo.back();
	updatedInfo.pop_back();
	std::string map = updatedInfo.back();
	updatedInfo.pop_back();
	std::string ret = "" + map + ":" + gameType + ":" + gameTime + ":" + instaDeath;
	isCompetitif_ = std::stoi(gameType) == 2;
	return ret;
}

// Retourne l'état d,un joueur
bool FacadeReseau::playerIsReady(bool playerReady) 
{
	bool success = false;
	if (!commsControl_->executeSetReady(playerReady, success))
	{
		return false;
	}
	return true;
}

// Obtenir les informations des joueurs
std::string FacadeReseau::GetPlayersInfo() 
{
	// Format suggere : PLAYERNAME1:STATUS(1 || 0 )\nPLAYERNAME2:STATUS
	// return temporaire pour des tests

	bool success = false;
	std::vector<std::string> updatedInfo;
	if (!commsControl_->executeUpdateGameRoomPlayerInfo(updatedInfo, success))
	{
		// more error handling
		return "false";
	}
	std::string p4 = updatedInfo.back();
	updatedInfo.pop_back();
	std::string p3 = updatedInfo.back();
	updatedInfo.pop_back();
	std::string p2 = updatedInfo.back();
	updatedInfo.pop_back();
	std::string h = updatedInfo.back();
	updatedInfo.pop_back();
	std::string ret = "" + h + "\n" + p2 + "\n" + p3 + "\n" + p4;
	return ret;
}

// Obtenir l'état de la partie en cours
std::string FacadeReseau::GetGameState()
{
	return commsControl_->getMPGameStatus();
}

// Retourne true si la partie est commencée
bool FacadeReseau::isGameStarted()
{
	return commsControl_->isGameStarted();
}

// Réinitialise la partie multijoueur
void FacadeReseau::resetMultiplayer()
{
	commsControl_->resetMultiplayer();
}

// Retourne true si la partie est en mode compétitive
bool FacadeReseau::isCompetitif() const
{
	if (commsControl_ == nullptr)
		return false;

	bool isMultiplayer = commsControl_->isGameOnline();
	return (isMultiplayer && isCompetitif_);
}

// Obtenir le nombre de joueur dans la partie
int FacadeReseau::obtenirNombreJoueur() const
{
	return commsControl_->gameControl_->getNumberOfPlayers();
}

// Obtenir l'index du joueur courant
int FacadeReseau::obtenirNumeroJoueur()
{
	return commsControl_->gameControl_->getPlayerNumber(commsControl_->getUser()->getUserName());
}

// Mettre un joueur perdant dans la partie
void FacadeReseau::setPlayerLost()
{
	commsControl_->asPlayerSetPlayerLost();
}

// Indiquer qu'un joueur a perdu
void FacadeReseau::asHostSetPlayerLost(int index)
{
	commsControl_->asHostSetPlayerLost(index);
}

// Indiquer qu'un joueur a gagné
void FacadeReseau::asHostSetPlayerWin(int index)
{
	commsControl_->asHostSetPlayerWin(index);
}

/// Fonction test
void FacadeReseau::fonctionTest()
{
		
	bool success = false;
	for (int i = 0; i < 29; i++) 
	//commsControl_->commsTest();
		executeUploadMaps();
	for (int i = 0; i < 29; i++)
		executeDownloadMaps();

	std::cout << "MMMDONE!";
}

// Telecharge toutes les cartes du serveur
void FacadeReseau::executeDownloadMaps()
{
	bool success = false;
	//while(!success)
		success &= commsControl_->executeDownloadMap(success);
}

// Televerse toutes les cartes au serveur
void FacadeReseau::executeUploadMaps()
{
	bool success = false;
	//while (!success)
		success &= commsControl_->executeUploadMap(success);
}

// Prepare la prochaine carte dans une campagne MP
void FacadeReseau::prepareNextGame()
{
	commsControl_->MPPrepareNextGame();
}

// Obtenir l'index courant d'une partie en campagne MP
int FacadeReseau::getCurrentGameIndex()
{
	return commsControl_->gameControl_->getCampaignIndex();
}

	#pragma endregion

