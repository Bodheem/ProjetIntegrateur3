//////////////////////////////////////////////////////////////////////////////
/// @file UserMessageQueue.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_USERMESSAGEQUEUE_H__
#define __SERVEUR_USERMESSAGEQUEUE_H__

#include "ChatMessage.h"
#include "../../../SharedFiles/User.h"
#include <vector>
#include <list>

////////////////////////////////////////////////////////////////////////////////
///
/// @class UserMessageQueue
/// @brief Classe repr�sentant une queue de messages destin�s � un utilisateur
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class UserMessageQueue
{
public:
	/// Constructeur
	UserMessageQueue(std::string username);
	/// Destructeur
	~UserMessageQueue() { }

	/// Ajoute un message � envoyer � la liste
	void addNewMessage(ChatMessage* message);
	/// Accesseur de l'utilisateur de destination
	std::string getDestination();
	/// Accesseur de la liste de messages � envoyer
	std::vector<ChatMessage*> UserMessageQueue::getMessageList();
	/// Vide la liste des messages � envoyer
	void clearList();
private:
	/// Utilisateur auquel le message est destin�
	std::string destinationUserName_;
	/// Liste de messages � envoyer au destinataire
	std::list<ChatMessage*> unsentMessageList_;

};

#endif // __SERVEUR_USERMESSAGEQUEUE_H__