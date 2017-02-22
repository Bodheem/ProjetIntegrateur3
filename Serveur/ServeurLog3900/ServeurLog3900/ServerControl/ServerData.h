//////////////////////////////////////////////////////////////////////////////
/// @file ServerData.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_SERVERDATA_H__
#define __SERVEUR_SERVERDATA_H__

#include "..\ChatControl\ChatRoom.h"
#include "../../../SharedFiles/GameRoom.h"
#include "..\ChatControl\ChatControl.h"
#include "..\UserControl\UserControl.h"
#include "../../../SharedFiles/User.h"
#include "../GameControl/GameControl.h"
#include <string>
#include <fstream>
#include <mutex>


////////////////////////////////////////////////////////////////////////////////
///
/// @class ServerData
/// @brief Classe représentant les données actuellement utilisées par le serveur
///			de façon threadsafe
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class ServerData
{
public:

	/// Constructeur
	ServerData();

	/// Destructeur
	~ServerData();

	/// Pointeur vers l'instance unique de ServerDataPointer
	static ServerData* ServerDataPointer;

	// Obtenir le pointeur statique vers le ServerData
	static ServerData* getPointer();

	/// Retourne le prochain ID de message de chat
	int getNextMessageID() const;

	/// Retourne le prochain ID d'utilisateur
	int getNextUserID() const;

	/// Subclass: Chat Controller
	ChatControl* chatControl_;

	/// Subclass: User Accounts Controller
	UserControl* userControl_;

	/// Subclass: Game Room Controller
	GameControl* gameControl_;

	/// Charge toutes les informations de la mémoire / DB
	void loadMemory() const;

	/// Tread Safety Mutex
	std::mutex safetyMutex_;
	/// True when mutex is locked, for debug purposes
	bool safetyMutexIsLocked_ = false;
	/// Last call that locked safety mutex
	std::string safetyMutexLastCaller = "";

private:

	/// Récupérer tous les utilisateurs de la base de données
	void retrieveUser() const;

	/// Récupérer la liste des amis de la base de données
	void retrieveFriends() const;

	/// Récupérer les statistiques des utilisateurs
	void retrieveStats() const;

	/// Récupérer les avatars débloqués par les utilisateurs
	void retrieveAvatar() const;

	/// Récupérer les achievement débloqués par les utilisateurs
	void retrieveAchievement() const;

	/// Récupérer les maps débloqués par les utilisateurs
	void retrieveMap() const;
};

#endif // __SERVEUR_SERVERDATA_H__