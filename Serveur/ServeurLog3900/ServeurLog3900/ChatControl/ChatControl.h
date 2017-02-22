//////////////////////////////////////////////////////////////////////////////
/// @file ChatControl.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_CHATCONTROL_H__
#define __SERVEUR_CHATCONTROL_H__

#include <list>
#include "ChatRoom.h"
#include "ChatMessage.h"
#include <string>
#include <vector>

class ChatControl
{
public:
	ChatControl();
	~ChatControl();
	
	/// Retourne le prochain ID unique de message
	int getNextMessageID();
	/// Analyse une entrée de l'utilisateur
	void parseNewMessage(User* user, std::string messageContent, ChatRoom* chatroom);
	/// Retourne un vecteur de tout les messages à envoyer à un utilisateur
	std::vector<ChatMessage*> getUnsentMessages(User* user);
	/// Crée une nouvelle salle de conversation
	bool createChatRoom(std::string name);
	/// Retourne la salle de conversation à partir d'un nom
	ChatRoom* getChatRoom(std::string name);
	/// Retourne une liste de salles de conversations auquel un utilisateur est abonné
	std::vector<std::string> getSubscribedChatRooms(User* user);
	/// Détruit des salles de conversation vide
	void deleteEmptyChatRoom();
	/// Rajoute un utilisateur à une salle de conversation
	void addUserToChatRoom(std::string chatRoomName, User* user);
	/// Rajoute un utilisateur à une salle de conversation
	void addUserToChatRoom(std::string chatRoomName, std::string user);
	/// Enlève un utilisateur d'une salle de conversation
	void removeUserFromChatRoom(std::string chatRoomName, User* user);

private:
	/// Identificateur unique des messages de conversation
	int chatMessageIndex_ = 0;
	/// Liste des salles de conversation
	std::list<ChatRoom*> chatRoomList_;
};

#endif //__SERVEUR_CHATCONTROL_H__