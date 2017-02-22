//////////////////////////////////////////////////////////////////////////////
/// @file ChatControl.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include "ChatControl.h"
#include "../ServerControl/ServerControl.h"
#include <iostream>
#include "../SQL/Database.h"
#include <sstream>


ChatControl::ChatControl()
{
}


ChatControl::~ChatControl()
{
}


int ChatControl::getNextMessageID()
{
	return ++chatMessageIndex_;

}

/// Analyse une entrée de l'utilisateur
void ChatControl::parseNewMessage(User* user, std::string messageContent, ChatRoom* chatroom)
{
	std::string message = messageContent;
	
	// Analyse du message pour des commandes
	bool commandFound = false;
	if (message.at(0) == '/')
	{
		size_t s = message.find(" /");
		if (s != std::string::npos)
		{
			commandFound = true;
			message = "ERROR: Command failed: Command insertion is not allowed. Only use a single / at the beginning";
		}
		// Créer de salle de conversation
		s = message.find("/create");
		if (s != std::string::npos)
		{
			commandFound = true;
			std::string name = message.substr(8);
			int len = name.length();
			if (len > 40)
				message = "ERROR: Command failed: Name too long";
			else
			{
				if (createChatRoom(name))
				{
					message = "SUCCESS: Chat room \"" + name + "\" was created by " + user->getUserName() + ".";
					addUserToChatRoom(name, user);
				}
				else
				{
					message = "SUCCESS: Chat room \"" + name + "\" was joined by " + user->getUserName() + ".";
					addUserToChatRoom(name, user);
				}
			}
		}
		
		// Rejoindre une salle de conversation
		s = message.find("/join");
		if (s != std::string::npos && !commandFound)
		{
			commandFound = true;
			std::string name = message.substr(6);
			int len = name.length();
			if (len > 40)
				message = "ERROR: Command failed: Name too long";
			else
			{
				addUserToChatRoom(name, user);
				message = "SUCCESS: Chat room \"" + name + "\" was joined by " + user->getUserName() + ".";
			}
		}

		// Liste les commandes disponibles
		s = message.find("/listroom");
		if (s != std::string::npos && !commandFound)
		{
			commandFound = true;
			message = "Available Chat Rooms:\n";
			for (auto room : chatRoomList_)
			{
				if (!room->isEmpty())
					message += room->getRoomName() + "\n";
			}
		}

		// Liste les commandes disponibles
		s = message.find("/help");
		if (s != std::string::npos && !commandFound)
		{
			commandFound = true;
			message = "Availables text commands:\ncreate: Create new Chat Room\njoin: Join Chat Room"
				"\nleave: Leave Chat Room\nfriend: List Friend Status\naddfriend: Add New Friend to Friend List\nunfriend: Remove Friend From Friend List"
				"\nlistroom: List All Populated Chat Rooms";
		}

		// Quitter une salle de conversation
		s = message.find("/leave");
		if (s != std::string::npos && !commandFound)
		{
			commandFound = true;
			std::string name = message.substr(7);
			int len = name.length();
			if (len > 40)
				message = "ERROR: Command failed: Name too long";
			else
			{
				if (name == "General")
					message = "ERROR: Command failed: Cannot leave General Chat";
				else
				{
					if (!getChatRoom(name)->isEmpty())
					{
						removeUserFromChatRoom(name, user);
						message = "SUCCESS: Chat room \"" + name + "\" left by " + user->getUserName() + ".";
					}
					else
						message = "ERROR: Command failed: Unknown Chat Room";
				}
			}
		}

		// Ajouter un ami
		s = message.find("/addfriend");
		if (s != std::string::npos && !commandFound)
		{
			commandFound = true;
			std::string name = message.substr(11);
			User* newFriend = ServerControl::getPointer()->serverData_->userControl_->getUser(name);
			if (newFriend != nullptr && newFriend->getUserName() != user->getUserName())
			{
				bool userSuccess;
				bool userFriend;
				userSuccess = user->addFriend(newFriend->getUserName());
				userFriend = newFriend->addFriend(user->getUserName());
				if (userSuccess)
				{
					// Requête SELECT pour savoir si la ligne existe déjà
					std::string baseSelect = "SELECT* FROM FRIENDLIST WHERE USER_ID ='";
					std::stringstream select;
					select << baseSelect;
					select << user->getUserName() << "'" << " AND FRIEND_USER_ID = '" << newFriend->getUserName() << "';";
					std::vector<std::vector<std::string>> result;

					/// Execute select SQL
					result = Database::executeQuery("../../Database/PainBall.db", select.str().c_str());

					if (result.size() == 1)
					{
						// Requête INSERT
						std::string baseInsert = "INSERT INTO FRIENDLIST VALUES (";
						std::stringstream ss;
						ss << baseInsert;
						ss << "'" << user->getUserName() << "'" << ", " << "'" << newFriend->getUserName() << "');";

						/// Execute insert SQL
						Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());
					}
				}
				if (userFriend)
				{
					// Requête SELECT pour savoir si la ligne existe déjà
					std::string baseSelect = "SELECT* FROM FRIENDLIST WHERE USER_ID ='";
					std::stringstream select;
					select << baseSelect;
					select << newFriend->getUserName() << "'" << " AND FRIEND_USER_ID = '" << user->getUserName() << "';";
					std::vector<std::vector<std::string>> result;

					/// Execute select SQL
					result = Database::executeQuery("../../Database/PainBall.db", select.str().c_str());

					if (result.size() == 1)
					{
						// Requête INSERT
						std::string baseInsert = "INSERT INTO FRIENDLIST VALUES (";
						std::stringstream ss;
						ss << baseInsert;
						ss << "'" << newFriend->getUserName() << "'" << ", " << "'" << user->getUserName() << "');";

						/// Execute insert SQL
						Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());
					}
				}

				message = "SUCCESS: Added New Friend To Friend List";
			}
			else
			{
				if (newFriend != nullptr)
					if (newFriend->getUserName() == user->getUserName())
						message = "ERROR: Command failed: Can't friend yourself";
					else
						message = "ERROR: Command failed: Unknown User";
				else
					message = "ERROR: Command failed: Unknown User";
			}
		}

		// Enlever un ami
		s = message.find("/unfriend");
		if (s != std::string::npos && !commandFound)
		{
			commandFound = true;
			std::string name = message.substr(10);
			User* newFriend = ServerControl::getPointer()->serverData_->userControl_->getUser(name);
			if (newFriend != nullptr)
			{
				bool userSuccess = user->removeFriend(newFriend);
				bool friendSuccess = newFriend->removeFriend(user);

				if (userSuccess)
				{
					// Requête DELETE
					std::string baseDelete = "DELETE FROM FRIENDLIST WHERE USER_ID = '";
					std::stringstream ss;
					ss << baseDelete;
					ss << user->getUserName() << "'" << " AND FRIEND_USER_ID = '" << newFriend->getUserName() << "';";

					/// Execute delete SQL
					Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());

					message = "SUCCESS: Removed Friend To Friend List";
				}
				else
				{
					message = "ERROR: Command failed: Unknown User";
				}

				if (friendSuccess)
				{
					// Requête DELETE
					std::string baseDelete = "DELETE FROM FRIENDLIST WHERE USER_ID = '";
					std::stringstream ss;
					ss << baseDelete;
					ss << newFriend->getUserName() << "'" << " AND FRIEND_USER_ID = '" << user->getUserName() << "';";

					/// Execute delete SQL
					Database::executeQuery("../../Database/PainBall.db", ss.str().c_str());

					message = "SUCCESS: Removed Friend To Friend List";
				}
				else
				{
					message = "ERROR: Command failed: Unknown User";
				}
			}
			else
				message = "ERROR: Command failed: Unknown User";
		}

		// Obtenir une liste des amis
		s = message.find("/friend");
		if (s != std::string::npos && !commandFound)
		{
			commandFound = true;
			std::vector<std::string> friendList = user->getFriendList();
			message = "";
			for (auto u : friendList)
			{
				message += u + ": " + (ServerControl::getPointer()->serverData_->userControl_->getUser(u)->isLogged() ? "Online" : "Offline") + "\n";
			}
		}
	}

	// Ajouter le message à la salle de conversation
	ChatMessage* chatMessage = new ChatMessage(user->getUserName(), message);
	std::cout << chatMessage->getFormattedMessage() << std::endl;
	if (chatroom->isEmpty())
	{
		ChatRoom* general = getChatRoom("General");
		general->addNewMessage(chatMessage);
	}
	else
	{
		chatroom->addNewMessage(chatMessage);
	}

	deleteEmptyChatRoom();
}

/// Crée une nouvelle salle de conversation
bool ChatControl::createChatRoom(std::string name)
{
	for (ChatRoom* room : chatRoomList_)
	{
		if (room->getRoomName() == name)
			return false;
	}
	chatRoomList_.push_back(new ChatRoom(name));
	return true;
}

/// Retourne la salle de conversation à partir d'un nom
/// Retourne une nouvelle salle si elle n'existe pas
ChatRoom* ChatControl::getChatRoom(std::string name)
{
	for (ChatRoom* room : chatRoomList_)
	{
		if (room->getRoomName() == name)
			return room;
	}
	ChatRoom* room = new ChatRoom(name);
	chatRoomList_.push_back(room);
	return room;
}


/// Retourne une liste de salles de conversations auquel un utilisateur est abonné
std::vector<std::string> ChatControl::getSubscribedChatRooms(User* user)
{
	std::vector<std::string> chatRooms;
	for (ChatRoom* room : chatRoomList_)
	{
		if (room->isUserSubscribed(user))
			chatRooms.push_back(room->getRoomName());
	}
	return chatRooms;
}

/// Détruit des salles de conversation vide
void ChatControl::deleteEmptyChatRoom()
{
	for (auto it = chatRoomList_.begin(); it != chatRoomList_.end();) 
	{
		if ((*it)->isEmpty()) 
		{
			it = chatRoomList_.erase(it);
		}
		else 
		{
			++it;
		}
	}
}

/// Rajoute un utilisateur à une salle de conversation
void ChatControl::addUserToChatRoom(std::string chatRoomName, User* user)
{
	getChatRoom(chatRoomName)->addNewUser(user);
}


/// Rajoute un utilisateur à une salle de conversation
void ChatControl::addUserToChatRoom(std::string chatRoomName, std::string user)
{
	getChatRoom(chatRoomName)->addNewUser(user);
}

/// Enlève un utilisateur d'une salle de conversation
void ChatControl::removeUserFromChatRoom(std::string chatRoomName, User* user)
{
	getChatRoom(chatRoomName)->removeUser(user);
}


/// Retourne un vecteur de tout les messages à envoyer à un utilisateur
std::vector<ChatMessage*> ChatControl::getUnsentMessages(User* user)
{
	std::vector<ChatMessage*> ret;
	for (ChatRoom* room : chatRoomList_)
	{
		std::vector<ChatMessage*> vec = room->getUnsentMessages(user);
		if (!vec.empty())
			ret.insert(ret.end(), vec.begin(), vec.end());
	}
	return ret;
}