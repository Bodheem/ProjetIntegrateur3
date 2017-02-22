//////////////////////////////////////////////////////////////////////////////
/// @file ChatRoom.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include "ChatRoom.h"
#include "..\ServerControl\ServerData.h"


ChatRoom::ChatRoom(std::string name)
{
	// Assurance supplémentaire de limite à 40 charactères
	if (name.length() > 40)
		roomName_ = name.substr(0, 40);
	else
		roomName_ = name;
}


ChatRoom::~ChatRoom()
{
}


/// Retourne le nom de la salle
std::string ChatRoom::getRoomName()
{
	return roomName_;
}


/// Retourne true si la salle est vide
bool ChatRoom::isEmpty()
{
	return subscribedUsersList_.empty();
}

/// Ajouter un nouveau message à la salle de conversation
void ChatRoom::addNewMessage(ChatMessage* message)
{
	messageList_.push_back(message);
	for (UserMessageQueue* user : unsentMessageQueuesList_)
	{
		user->addNewMessage(message);
	}
}

/// Obtenir les 500 derniers messages de la salle
std::vector<ChatMessage*> ChatRoom::getAllMessages(User* destinationUser)
{
	for (UserMessageQueue* user : unsentMessageQueuesList_)
		if (user->getDestination() == destinationUser->getUserName())
			user->clearList();
	
	
	std::vector<ChatMessage*> ret;
	for (ChatMessage* message : messageList_){
		ret.push_back(message);
	}
	
	return ret;
}

/// Obtenir les messages destinés à un utilisateur
std::vector<ChatMessage*> ChatRoom::getUnsentMessages(User* destinationUser)
{
	for (UserMessageQueue* user : unsentMessageQueuesList_)
		if (user->getDestination() == destinationUser->getUserName())
			return user->getMessageList();
	return std::vector<ChatMessage*>();
}

/// Ajouter un nouvel utilisateur à la salle de conversation
void ChatRoom::addNewUser(User* user)
{
	UserMessageQueue* queue = new UserMessageQueue(user->getUserName());

	for (ChatMessage* message : messageList_)
		queue->addNewMessage(message);

	unsentMessageQueuesList_.push_back(queue);

	subscribedUsersList_.push_back(user);
}

/// Ajouter un nouvel utilisateur à la salle de conversation
void ChatRoom::addNewUser(std::string user)
{
	UserMessageQueue* queue = new UserMessageQueue(user);

	for (ChatMessage* message : messageList_)
		queue->addNewMessage(message);

	unsentMessageQueuesList_.push_back(queue);
	User* userAcc = ServerData::getPointer()->userControl_->getUser(user);
	subscribedUsersList_.push_back(userAcc);
}

/// Déinscrit un utilisateur de la salle de conversation
void ChatRoom::removeUser(User* user)
{
	// Search for user in list
	for (auto it = subscribedUsersList_.begin(); it != subscribedUsersList_.end();) {
		if ((*it)->getUserName() == user->getUserName()) 
		{
			it = subscribedUsersList_.erase(it);
			// Search for user in unsent messages queue
			for (auto it2 = unsentMessageQueuesList_.begin(); it2 != unsentMessageQueuesList_.end();) 
			{
				if ((*it2)->getDestination() == user->getUserName()) 
				{
					it2 = unsentMessageQueuesList_.erase(it2);
					return;
				}
				else 
					++it2;
			}
		}
		else 
			++it;
	}
}


/// Retourne true si l'utilisateur est abonné à la salle
bool ChatRoom::isUserSubscribed(User* user)
{
	for (User* subbed : subscribedUsersList_)
		if (subbed->getUserName() == user->getUserName())
			return true;
	return false;
}
