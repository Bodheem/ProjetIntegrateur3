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
/// @brief Classe représentant un message de chat pour le client lourd
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class ChatMessage
{
public:
	/// Constructeur de nouveau message recu du serveur
	ChatMessage(std::string message);

	/// Retourne le message courant sous format prêt à être affiché
	std::string getMessage();

private:
	/// Contenu du message
	std::string messageContent_;
};


#endif //  __SERVEUR_CHATMESSAGE_H__