///////////////////////////////////////////////////////////////////////////////
/// @file Propriete.h
/// @author The New Ballers
/// @date 2016-01-13
/// @version 1.0
///
/// @ingroup Sauvegarde
///////////////////////////////////////////////////////////////////////////////
#ifndef __SAUVEGARDE_PROPRIETE_H__
#define __SAUVEGARDE_PROPRIETE_H__

#include <string>
#include <map>

///////////////////////////////////////////////////////////////////////////
/// @class Propriete
/// @brief Classe pour enregistrer les propriétés de la zone de jeu
///
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Sauvegarde
///////////////////////////////////////////////////////////////////////////
class Propriete
{
public:

	/// Constructeur par défaut
	Propriete();

	/// Destructeur
	~Propriete();

	/// Obtenir l'attribut proprietes_
	std::map<std::string, std::string> getPropriete() const;

	/// Obtenir la valeur d'une propriete
	std::string getProprieteValue(std::string prop) const;

	/// Assigner les proprietes à partir d'une chaine de caractère
	void setFromString(const std::string& prop);

	/// Retourner les proprietes comme chaine de caractère avec des \n
	std::string ToString() const;

	/// Assigner la valeur pour une propriete
	void setPropriete(std::string nomPropriete, std::string valeur);

	// Usages futures
	const std::string mapId = "ID";
	// Usages futures
	const std::string autheur = "Author";
	// Usages futures
	const std::string lastModificationBy = "LastModificationBy";
	// Usages futures
	const std::string version = "Version";
	// Usages futures
	const std::string cost = "Cout";

	// Proprietes SRS INF2990
	const std::string pointButoir = "PointsButoir";
	// Proprietes SRS INF2990
	const std::string pointTriangulaire = "PointsTriangulaire";
	// Proprietes SRS INF2990
	const std::string pointCible = "PointsCible";
	// Proprietes SRS INF2990
	const std::string pointVictoire = "PointsVictoire";
	// Proprietes SRS INF2990
	const std::string pointBilleGratuite = "PointsBilleGratuite";
	// Proprietes SRS INF2990
	const std::string difficulte = "Difficulte";

private:

	// Initialiser les proprietes par defaut
	void initialiserProprieteDefaut();

	/// Liste des proprietes et leurs valeurs
	std::map<std::string, std::string> proprietes_;
};

#endif //__SAUVEGARDE_PROPRIETE_H__