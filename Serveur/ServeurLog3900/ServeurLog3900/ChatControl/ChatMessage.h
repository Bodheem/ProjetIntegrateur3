//////////////////////////////////////////////////////////////////////////////
/// @file ChatMessage.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_CHATMESSAGE_H__
#define __SERVEUR_CHATMESSAGE_H__

#include <string>
#include <ctime>

////////////////////////////////////////////////////////////////////////////////
///
/// @class ChatMessage
/// @brief Classe repr�sentant un message de chat
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class ChatMessage
{
public:
	/// Constructeur de nouveau message pour le serveur
	ChatMessage(std::string user, std::string message);

	/// Re-Constructeur d'un message par le Client
	ChatMessage(std::string user, std::string message, int h, int m, int s, int id);

	/// Retourne le message courant sous format pr�t � �tre affich�
	std::string getFormattedMessage();

private:
	// ID Unique du message
	int messageId_;

	// Timestamp de r�ception par le serveur
	int heure_;
	int minute_;
	int seconde_;

	std::string username_;
	std::string messageContent_;
};


#endif //  __SERVEUR_CHATMESSAGE_H__