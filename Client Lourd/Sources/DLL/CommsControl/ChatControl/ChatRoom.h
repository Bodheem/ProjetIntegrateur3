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

////////////////////////////////////////////////////////////////////////////////
///
/// @class ChatMessage
/// @brief Classe repr�sentant une salle de conversation pour le client lourd
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

	/// Ajouter un nouveau message � la salle de conversation
	void addNewMessage(ChatMessage* message);
	/// Obtenir tout les messages de la salle
	std::vector<std::string> getAllMessages();
	/// Obtenir les messages non affich�s
	std::vector<std::string> getUnseenMessages();
	/// Retourne le nom de la salle
	std::string getRoomName();

private:
	/// Room name
	std::string roomName_;
	/// Message list
	std::vector<ChatMessage*> messageList_;
	/// Redundant message list for unseen message
	std::vector<ChatMessage*> unseenMessageList_;

};

#endif // __SERVEUR_CHATROOM_H__