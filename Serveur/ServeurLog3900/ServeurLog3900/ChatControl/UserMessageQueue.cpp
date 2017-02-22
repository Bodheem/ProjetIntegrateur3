//////////////////////////////////////////////////////////////////////////////
/// @file UserMessageQueue.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include "UserMessageQueue.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn UserMessageQueue::UserMessageQueue(std::string username)
///
/// @brief Construit un objet UserMessageQueue avec un utilisateur destinataire
///
/// @param[in] usager destinataire
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
UserMessageQueue::UserMessageQueue(std::string username)
{
	destinationUserName_ = username;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::string UserMessageQueue::getDestination()
///
/// @brief Cette fonction retourne l'utilisateur destinataire du message
///
/// @return Nom de l'utilisateur destinataire
///
////////////////////////////////////////////////////////////////////////
std::string UserMessageQueue::getDestination()
{
	return destinationUserName_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UserMessageQueue::addNewMessage(ChatMessage* message)
///
/// @brief Cette fonction Ajoute un message à envoyer à la liste
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void UserMessageQueue::addNewMessage(ChatMessage* message)
{
	unsentMessageList_.push_back(message);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<ChatMessage*> UserMessageQueue::getMessageList()
///
/// @brief Cette fonction retourne un vecteur de messages à envoyer
///
/// @return Message à envoyer
///
////////////////////////////////////////////////////////////////////////
std::vector<ChatMessage*> UserMessageQueue::getMessageList()
{
	std::vector<ChatMessage*> ret;
	while (!unsentMessageList_.empty())
	{
		ret.push_back(unsentMessageList_.front());
		unsentMessageList_.pop_front();
	}
	return ret;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void UserMessageQueue::clearList()
///
/// @brief Vide la liste des messages à envoyer
///
/// @return rien
///
////////////////////////////////////////////////////////////////////////
void UserMessageQueue::clearList()
{
	while (!unsentMessageList_.empty())
	{
		unsentMessageList_.pop_back();
	}
}