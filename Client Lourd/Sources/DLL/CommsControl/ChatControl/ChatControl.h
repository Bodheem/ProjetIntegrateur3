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
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
///
/// @class ChatMessage
/// @brief Classe représentant une salle de conversation pour le client lourd
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class ChatControl
{
public:
	/// Constructeur
	ChatControl();
	/// Destructeur
	~ChatControl();
	
	/// Retourne une liste des salles de conversation
	std::list<ChatRoom*> getChatRooms();
	/// Recrée les salles de chat à partir d'un vecteur de noms de salles
	void updateChatRoomList(std::vector<std::string> chatRoomNames);
	/// Ajoute des nouveaux messages à une salle de conversation
	void updateChatRoomMessageLog(std::string chatRoomName, std::vector<std::string> messageList);
	/// Retourne un vecteur de tout les messages à afficher dans une salle de conversation
	std::vector<std::string> getUnseenMessages(std::string name);

private:
	/// Liste des salles de conversation
	std::list<ChatRoom*> chatRoomList_;
};

#endif //__SERVEUR_CHATCONTROL_H__