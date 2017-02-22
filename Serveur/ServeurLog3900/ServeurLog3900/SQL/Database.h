///////////////////////////////////////////////////////////////////////////////
/// @file Database.h
/// @author The New Ballers
/// @date 2016-01-13
/// @version 1.0
///
/// @ingroup SQL
///////////////////////////////////////////////////////////////////////////////

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <vector>
#include "sqlite3.h"

///////////////////////////////////////////////////////////////////////////
/// @class Database
/// @brief Classe pour interfacer les bases de données SQL
///
/// @author The Ballers
/// @date 2016-02-02
/// @ingroup SQL
///////////////////////////////////////////////////////////////////////////
class Database
{
public:

	// Constructeur
	Database();

	// Destructeur
	virtual ~Database() = 0;

	// Resultat d'une requête
	static std::vector<std::vector<std::string> > executeQuery(std::string fileName, const char* query);
};

#endif