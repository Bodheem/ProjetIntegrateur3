//////////////////////////////////////////////////////////////////////////////
/// @file ChatRoom.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_CHATROOM_H__
#define __SERVEUR_CHATROOM_H__

#include <string>
#include <list>
#include <vector>
#include "ChatMessage.h"
#include "UserMessageQueue.h"

class User;

////////////////////////////////////////////////////////////////////////////////
///
/// @class ChatMessage
/// @brief Classe représentant une salle de conversation
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class ChatRoom
{
public:
	/// Constructeur
	ChatRoom(std::string name);
	/// Destructeur
	~ChatRoom();

	/// Ajouter un nouveau message à la salle de conversation
	void addNewMessage(ChatMessage* message);
	/// Ajouter un nouvel utilisateur à la salle de conversation
	void addNewUser(User* user);
	/// Ajouter un nouvel utilisateur à la salle de conversation
	void addNewUser(std::string user);
	/// Déinscrit un utilisateur de la salle de conversation
	void removeUser(User* user);
	/// Obtenir les 500 derniers messages de la salle
	std::vector<ChatMessage*> getAllMessages(User* destinationUser);
	/// Obtenir les messages destinés à un utilisateur
	std::vector<ChatMessage*> getUnsentMessages(User* destinationUser);
	/// Retourne le nom de la salle
	std::string getRoomName();
	/// Retourne true si la salle est vide
	bool isEmpty();
	/// Retourne true si l'utilisateur est abonné à la salle
	bool isUserSubscribed(User* user);

private:
	std::string roomName_;
	std::list<ChatMessage*> messageList_;
	std::list<UserMessageQueue*> unsentMessageQueuesList_;
	std::list<User*> subscribedUsersList_;

};

#endif // __SERVEUR_CHATROOM_H__