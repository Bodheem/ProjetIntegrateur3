//////////////////////////////////////////////////////////////////////////////
/// @file ChatMessage.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include "ChatMessage.h"
#include "..\ServerControl\ServerData.h"
#include <ctime>
#include <string>

////////////////////////////////////////////////////////////////////////
///
/// @fn ChatMessage::ChatMessage(std::string user, std::string message)
///
/// @brief Construit un objet ChatMessage
///
/// @param[in] username allant jusqu'� 20 charact�res
/// @param[in] message allant jusqu'� 100 charact�res
///
/// @remarks CONSTRUCTEUR UTILIS� PAR LE SERVEUR UNIQUEMENT
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
ChatMessage::ChatMessage(std::string user, std::string message)
{
	// Obtenir un timestamp 
	time_t timestamp;
	time(&timestamp);
	struct tm now;
	localtime_s(&now, &timestamp);
	heure_ = now.tm_hour;
	minute_ = now.tm_min;
	seconde_ = now.tm_sec;

	// D�j� assur� d'�tre 20 charact�res
	username_ = user;

	messageContent_ = message;

	// Obtenir un ID de message unique
	messageId_ = ServerData::getPointer()->getNextMessageID();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn ChatMessage::ChatMessage(std::string user, std::string message, int h, int m, int s, int id)
///
/// @brief Reconstruit un objet ChatMessage obtenu du serveur
///
/// @param[in] username allant jusqu'� 20 charact�res
/// @param[in] message allant jusqu'� 100 charact�res
/// @param[in] h, m, s : timestamp
/// @param[in] id: ID unique du message
///
/// @remarks CONSTRUCTEUR UTILIS� PAR LE CLIENT UNIQUEMENT
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
ChatMessage::ChatMessage(std::string user, std::string message, int h, int m, int s, int id)
{
	heure_ = h;
	minute_ = m;
	seconde_ = s;

	// D�j� assur� d'�tre 20 charact�res
	username_ = user;

	// Assurance suppl�mentaire de limite � 100 charact�res
	messageContent_ = message;

	// Obtenir un ID de message unique
	messageId_ = id;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn std::string ChatMessage::getFormattedMessage()
/// 
/// @brief Formatte le message � envoyer
/// 
/// @remark Le message retourn� est toujours de 136 charact�res
/// 
/// @return Le message formatt�, toujours 136 charact�res
///
////////////////////////////////////////////////////////////////////////
std::string ChatMessage::getFormattedMessage()
{
	std::string str = "";
	std::string spacers = "";

	// Write Timestamp
	str += spacers + std::to_string(heure_) + "h." + std::to_string(minute_) 
		+ "m." + std::to_string(seconde_) + "s.";
	spacers += ( (heure_ < 10)   ? " " : "" );
	spacers += ( (minute_ < 10)  ? " " : "" );
	spacers += ( (seconde_ < 10) ? " " : "" );
	str += spacers + " ";

	// Add Username : 
	str += username_;
	str += ": ";
	// Au total, le TimeStamp + Uername peut prendre jusqu'� 36 charact�res

	// Add Message Content
	str += messageContent_ + "\n";
	return str;
}