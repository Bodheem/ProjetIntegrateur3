#include "Database.h"
#include <iostream>


////////////////////////////////////////////////////////////////////////
/// @fn Database::Database()
/// @brief Constructeur
/// @return Aucun
////////////////////////////////////////////////////////////////////////
Database::Database()
{

}


////////////////////////////////////////////////////////////////////////
/// @fn Database::~Database()
/// @brief Destructeur
/// @return Aucun
////////////////////////////////////////////////////////////////////////
Database::~Database()
{

}


////////////////////////////////////////////////////////////////////////
/// @fn std::vector<std::vector<std::string>> Database::executeQuery(const char* query)
/// @brief	Retourne la réponse à une requete SQL standard. Peut etre n'importe quelle requête,
///			INSERT, DELETE, CREATE, SELECT
/// @return Une structure de donnée qui contient le résultat de la requête
////////////////////////////////////////////////////////////////////////
std::vector<std::vector<std::string> > Database::executeQuery(std::string fileName, const char* query)
{
	// Pointeur vers un objet SQLite3
	sqlite3* database = nullptr;
	sqlite3_open(fileName.c_str(), &database);

	sqlite3_stmt *statement;
	std::vector<std::vector<std::string> > results;

	if (sqlite3_prepare_v2(database, query, -1, &statement, nullptr) == SQLITE_OK)
	{
		// Récupérer les noms des colonnes voulues
		int cols = sqlite3_column_count(statement);
		std::vector<std::string> columnsName;
		for (int i = 0; i < cols; ++i)
		{
			const char* name = sqlite3_column_name(statement, i);
			columnsName.push_back(name);
		}
		results.push_back(columnsName);

		// Récupérer les résultats de la requête
		int result = 0;
		while (true)
		{
			result = sqlite3_step(statement);

			if (result == SQLITE_ROW)
			{
				std::vector<std::string> values;
				for (int col = 0; col < cols; col++)
					values.push_back(reinterpret_cast<const char*>(sqlite3_column_text(statement, col)));

				results.push_back(values);
			}
			else
			{
				break;
			}
		}
		sqlite3_finalize(statement);
	}

	std::string error = sqlite3_errmsg(database);
	if (error != "not an error")
		std::cout << query << " " << error << std::endl;

	sqlite3_close(database);

	return results;
}