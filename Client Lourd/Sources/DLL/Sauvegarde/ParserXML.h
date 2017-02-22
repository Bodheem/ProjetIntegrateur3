///////////////////////////////////////////////////////////////////////////////
/// @file ParserXML.h
/// @author The New Ballers
/// @date 2016-01-12
/// @version 1.0
///
/// @ingroup Sauvegarde
///////////////////////////////////////////////////////////////////////////////
#ifndef __SAUVEGARDE_PARSERXML_H__
#define __SAUVEGARDE_PARSERXML_H__

#include "tinyxml2.h"
#include <string>

class ArbreRenduINF2990;
class Propriete;

///////////////////////////////////////////////////////////////////////////
/// @class ParserXML
/// @brief Classe pour enregistrer l'information de la zone de jeu
///		   dans un fichier XML.
///
/// @author The New Ballers
/// @date 2016-01-13
/// @ingroup Sauvegarde
///////////////////////////////////////////////////////////////////////////
class ParserXML
{
public:

	/// Classe abstraite
	virtual ~ParserXML() = 0;

	/// Enregistre le fichier XML
	static void enregistrerXML(const std::string& nomFichier, const ArbreRenduINF2990& arbre, const Propriete& propriete);
	/// Lis le fichier XML
	static bool lireXML(const std::string& nomFichier, ArbreRenduINF2990& arbre, Propriete& propriete);

private:

	// Enregistre un nouvel arbre
	static void enregistrerArbre(tinyxml2::XMLDocument& document, tinyxml2::XMLElement& root, const ArbreRenduINF2990& arbre);
	// Enregistre les proprietes de la partie
	static void enregistrerPropriete(tinyxml2::XMLDocument& document, tinyxml2::XMLElement& root, const Propriete& propriete);

	// Lis un arbre et retrouene xml
	static void lireArbre(tinyxml2::XMLDocument& document, tinyxml2::XMLElement& root, ArbreRenduINF2990& arbre);
	// lis les proprietes de la partie
	static void lirePropriete(tinyxml2::XMLDocument& document, tinyxml2::XMLElement& root, Propriete& propriete);
};

#endif //__SAUVEGARDE_PARSERXML_H__