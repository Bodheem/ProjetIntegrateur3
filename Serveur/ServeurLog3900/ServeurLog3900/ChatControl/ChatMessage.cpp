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
/// @param[in] username allant jusqu'à 20 charactères
/// @param[in] message allant jusqu'à 100 charactères
///
/// @remarks CONSTRUCTEUR UTILISÉ PAR LE SERVEUR UNIQUEMENT
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

	// Déjà assuré d'être 20 charactères
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
/// @param[in] username allant jusqu'à 20 charactères
/// @param[in] message allant jusqu'à 100 charactères
/// @param[in] h, m, s : timestamp
/// @param[in] id: ID unique du message
///
/// @remarks CONSTRUCTEUR UTILISÉ PAR LE CLIENT UNIQUEMENT
///
/// @return aucun.
///
////////////////////////////////////////////////////////////////////////
ChatMessage::ChatMessage(std::string user, std::string message, int h, int m, int s, int id)
{
	heure_ = h;
	minute_ = m;
	seconde_ = s;

	// Déjà assuré d'être 20 charactères
	username_ = user;

	// Assurance supplémentaire de limite à 100 charactères
	messageContent_ = message;

	// Obtenir un ID de message unique
	messageId_ = id;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn std::string ChatMessage::getFormattedMessage()
/// 
/// @brief Formatte le message à envoyer
/// 
/// @remark Le message retourné est toujours de 136 charactères
/// 
/// @return Le message formatté, toujours 136 charactères
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
	// Au total, le TimeStamp + Uername peut prendre jusqu'à 36 charactères

	// Add Message Content
	str += messageContent_ + "\n";
	return str;
}