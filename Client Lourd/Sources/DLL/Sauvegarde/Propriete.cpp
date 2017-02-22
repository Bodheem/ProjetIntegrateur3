////////////////////////////////////////////////
/// @file   Propriete.cpp
/// @author The New Ballers
/// @date   2016-01-12
/// @ingroup Sauvegarde
////////////////////////////////////////////////

#include "Propriete.h"
#include <sstream>
#include <vector>

////////////////////////////////////////////////////////////////////////
/// @fn Propriete::Propriete()
/// @brief Constructeur. Initialise les valeurs des propriétés par défaut
/// @return Aucun
////////////////////////////////////////////////////////////////////////
Propriete::Propriete()
{
	// Proprietes par défaut
	initialiserProprieteDefaut();
}


////////////////////////////////////////////////////////////////////////
/// @fn Propriete::~Propriete()
/// @brief Desctructeur
/// @return Aucun
////////////////////////////////////////////////////////////////////////
Propriete::~Propriete()
{
	proprietes_.clear();
}


////////////////////////////////////////////////////////////////////////
/// @fn void Propriete::initialiserProprieteDefaut()
/// @brief Met des valeurs par défaut dans la structure de donnée interne
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void Propriete::initialiserProprieteDefaut()
{
	proprietes_.insert(std::make_pair(mapId, ""));
	proprietes_.insert(std::make_pair(autheur, "HORS-LIGNE"));
	proprietes_.insert(std::make_pair(lastModificationBy, ""));

	proprietes_.insert(std::make_pair(pointButoir, "100"));
	proprietes_.insert(std::make_pair(pointTriangulaire, "100"));
	proprietes_.insert(std::make_pair(pointCible, "100"));
	proprietes_.insert(std::make_pair(pointVictoire, "1000"));
	proprietes_.insert(std::make_pair(pointBilleGratuite, "500"));
	proprietes_.insert(std::make_pair(difficulte, "1"));
}


////////////////////////////////////////////////////////////////////////
/// @fn std::map<std::string, std::string> Propriete::getPropriete()
/// @brief Retourne la structure de donnée interne
/// @return La structure de donnée qui contient les propriétés
////////////////////////////////////////////////////////////////////////
std::map<std::string, std::string> Propriete::getPropriete() const
{
	return proprietes_;
}

////////////////////////////////////////////////////////////////////////
/// @fn std::map<std::string, std::string> Propriete::getPropriete()
/// @brief Retourne la structure de donnée interne
/// @return La structure de donnée qui contient les propriétés
////////////////////////////////////////////////////////////////////////
std::string Propriete::getProprieteValue(std::string prop) const
{
	auto iter = proprietes_.find(prop);
	if (iter != proprietes_.end())
	{
		return iter->second;
	}
	return "";
}


////////////////////////////////////////////////////////////////////////
/// @fn std::string Propriete::ToString()
/// @brief Retourne les propriétés selon le format Prop1:Value1\nProp2:Value2
/// @return Une string qui représente la structure de donnée selon le format
////////////////////////////////////////////////////////////////////////
std::string Propriete::ToString() const
{
	std::stringstream ss;

	// S'assurer que la string ne finit pas par \n
	auto iter = proprietes_.begin();
	if (iter != proprietes_.end())
	{
		ss << iter->first << ":" << iter->second;
		++iter;

		while (iter != proprietes_.end())
		{
			ss << "\n" << iter->first << ":" << iter->second;
			++iter;
		}
	}
	else
	{
		ss.clear();
	}

	return ss.str();
}


////////////////////////////////////////////////////////////////////////
/// @fn void Propriete::setPropriete()
/// @brief Assigner une valeur à une propriété dans la structure donnée
/// @param[in] nomPropriete : Nom de la propriété
/// @param[in] valeur : Valeur à attribuer à la propriété
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void Propriete::setPropriete(std::string nomPropriete, std::string valeur)
{
	auto iter = proprietes_.find(nomPropriete);
	if (iter != proprietes_.end())
	{
		proprietes_[nomPropriete] = valeur;
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn std::string Propriete::setFromString()
/// @brief Assigne les propriétés avec une string selon le format Prop1:Value1\nProp2:Value2
/// @param[in] prop : les propriétés selon le format Prop1:Value1\nProp2:Value2
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void Propriete::setFromString(const std::string& prop)
{
	// Enlever le \n de la string
	std::string temp = prop;
	std::string delimiter = "\r\n";
	std::vector<std::string> words;

	size_t pos = 0;
	std::string token;
	while ((pos = temp.find(delimiter)) != std::string::npos)
	{
		token = temp.substr(0, pos);
		words.push_back(token);
		temp.erase(0, pos + delimiter.length());
	}
	words.push_back(temp);
	

	// Extraire les données
	delimiter = ":";
	std::vector<std::string> details;

	for (unsigned int i = 0; i < words.size(); i++)
	{
		size_t position = 0;
		std::string detail;
		while ((position = words[i].find(delimiter)) != std::string::npos)
		{
			detail = words[i].substr(0, position);
			details.push_back(detail);
			words[i].erase(0, position + delimiter.length());
		}
		details.push_back(words[i]);
		setPropriete(details[0], details[1]);
		details.clear();
	}
}