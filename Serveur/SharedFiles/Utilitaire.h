#//////////////////////////////////////////////////////////////////////////////
/// @file Utilitaire.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Client
//////////////////////////////////////////////////////////////////////////////

#ifndef __CLIENT_UTILITAIRE_H__
#define __CLIENT_UTILITAIRE_H__
#include <Vector>
#include <string>

////////////////////////////////////////////////////////////////////////////////
///
/// @namespace Utilitaire
/// @brief Namespace contrôllant des fonctions utilitaires pour la communication
///
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
namespace Utilitaire
{
	/// Vérifie si une addresse IP est entrée dans un format IPv4 Légal
	bool addresseCorrecte(std::string addresse);

	/// Vérifie si un string contient un chiffre entre deux valeurs fournies
	bool stringBetween(std::string numeralString, int lowerBound, int upperBound);

	/// Sépare un string selon un charactère ou string de délimitation
	std::vector<std::string> stringSplit(std::string in, std::string delim);

	/// Demande à l'utilisateur d'entrer ses informations de connections dans la console
	void obtenirInformationsConnection(std::string& addresse, std::string& port);

	/// Encryption et decryption
	std::string encryptDecrypt(std::string toEncrypt);
};

#endif // __CLIENT_UTILITAIRE_H__
