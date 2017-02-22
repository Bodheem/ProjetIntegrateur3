//////////////////////////////////////////////////////////////////////////////
/// @file IP.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_IP_H__
#define __SERVEUR_IP_H__

#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
/// @class IP
/// @brief Classe représentant un utilisateur et ses informations de compte
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class IP
{
public:

	/// Constructeur
	IP(int a, int b, int c, int d);
	/// Constructeur
	IP(std::string ipString);
	/// Constructeur vide
	IP();

	/// Destructeur
	~IP();

	/// Modifie le record d'IP
	void changeTo(int a, int b, int c, int d);

	/// Obtenir le pseudonyme
	std::string getStringIP() const;

	int a_;
	int b_;
	int c_;
	int d_;
};

#endif // __SERVEUR_IP_H__