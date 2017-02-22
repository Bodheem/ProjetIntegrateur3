//////////////////////////////////////////////////////////////////////////////
/// @file ChatRoom.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include "ChatRoom.h"

// Constructeur
ChatRoom::ChatRoom(std::string name)
{
	// Assurance supplémentaire de limite à 20 charactères
	if (name.length() > 20)
		roomName_ = name.substr(0, 20);
	else
		roomName_ = name;
}

// Destructeur
ChatRoom::~ChatRoom()
{
	while (!messageList_.empty())
	{
		ChatMessage* message = messageList_.back();
		messageList_.pop_back();
		delete message;
	}
}


/// Ajouter un nouveau message à la salle de conversation
void ChatRoom::addNewMessage(ChatMessage* message)
{
	messageList_.push_back(message);
	unseenMessageList_.push_back(message);
}

/// Obtenir les 500 derniers messages de la salle
std::vector<std::string> ChatRoom::getAllMessages()
{
	unseenMessageList_.clear();
	std::list<std::string> notret;
	for (ChatMessage* message : messageList_)
		notret.push_back(message->getMessage());
	std::vector<std::string> ret{ std::begin(notret), std::end(notret) };
	
	return ret;

}

/// Obtenir les messages non affichés
std::vector<std::string> ChatRoom::getUnseenMessages()
{
	std::vector<std::string> ret;

	for (ChatMessage* message : unseenMessageList_)
		ret.push_back(message->getMessage());
	unseenMessageList_.clear();
	return ret;
}

/// Retourne le nom de la salle
std::string ChatRoom::getRoomName()
{
	return roomName_;
}
