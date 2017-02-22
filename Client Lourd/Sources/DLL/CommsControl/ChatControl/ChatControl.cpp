//////////////////////////////////////////////////////////////////////////////
/// @file ChatControl.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include "ChatControl.h"

// Constructeur
ChatControl::ChatControl()
{
}

// Desctructeur
ChatControl::~ChatControl()
{
	while (!chatRoomList_.empty())
	{ 
		ChatRoom* room = chatRoomList_.back();
		chatRoomList_.pop_back();
		delete room;
	}
}



/// Retourne une liste des salles de conversation
std::list<ChatRoom*> ChatControl::getChatRooms()
{
	return chatRoomList_;
}

/// Recrée les salles de chat à partir d'un vecteur de noms de salles
void ChatControl::updateChatRoomList(std::vector<std::string> chatRoomNames)
{
	// Create new rooms
	for (std::string name : chatRoomNames)
	{
		bool roomExists = false;
		for (ChatRoom* room : chatRoomList_)
		{
			if (room->getRoomName() == name)
				roomExists = true;
		}
		if (!roomExists)
			chatRoomList_.push_back(new ChatRoom(name));
	}
	// Delete obsolete rooms
	for (auto it = chatRoomList_.begin(); it != chatRoomList_.end();) 
	{
		std::string roomName = (*it)->getRoomName();
		bool found = false;

		for (std::string name : chatRoomNames)
			if (roomName == name)
				found = true;

		if (!found)
		{
			ChatRoom* room = (*it);
			delete room;
			it = chatRoomList_.erase(it);

		}
		else
			++it;
	}
}

/// Ajoute des nouveaux messages à une salle de conversation
void ChatControl::updateChatRoomMessageLog(std::string chatRoomName, std::vector<std::string> messageList)
{
	for (ChatRoom* room : chatRoomList_)
		if (room->getRoomName() == chatRoomName)
			for (std::string message : messageList)
				room->addNewMessage(new ChatMessage(message));
}


/// Retourne un vecteur de tout les messages à afficher dans une salle de conversation
std::vector<std::string> ChatControl::getUnseenMessages(std::string name)
{
	std::vector<std::string> ret;
	for (ChatRoom* room : chatRoomList_)
		if (room->getRoomName() == name)
		{
			std::vector<std::string> messages = room->getUnseenMessages();
			ret.insert(ret.end(), messages.begin(), messages.end());
		}
	return ret;
}
