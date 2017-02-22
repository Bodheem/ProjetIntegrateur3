//////////////////////////////////////////////////////////////////////////////
/// @file IP.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////


#include "IP.h"
#include "Utilitaire.h"

////////////////////////////////////////////////////////////////////////
/// @fn IP::IP(std::string IPname, std::string password, std::string email)
/// @brief Constructeur qui initialise les attributs a partir des paramètres
/// @return Aucun
////////////////////////////////////////////////////////////////////////
IP::IP(int a, int b, int c, int d)
{
	a_ = a;
	b_ = b;
	c_ = c;
	d_ = d;
}


/// Constructeur
IP::IP(std::string ipString)
{
	std::vector<std::string> ret = Utilitaire::stringSplit(ipString, ".");
	try
	{
		d_ = std::stoi(ret.back());
		ret.pop_back();
		c_ = std::stoi(ret.back());
		ret.pop_back();
		b_ = std::stoi(ret.back());
		ret.pop_back();
		a_ = std::stoi(ret.back());
		ret.pop_back();
	}
	catch (std::exception ex)
	{
		a_ = 0;
		b_ = 0;
		c_ = 0;
		d_ = 0;
	}
}


/// Constructeur vide
IP::IP()
{
	a_ = 0;
	b_ = 0;
	c_ = 0;
	d_ = 0;
}


////////////////////////////////////////////////////////////////////////
/// @fn IP::~IP()
/// @brief Destructeur
/// @return Aucun
////////////////////////////////////////////////////////////////////////
IP::~IP()
{

}

////////////////////////////////////////////////////////////////////////
/// @fn void IP::changeTo(int a, int b, int c, int d)
/// @brief Modifie le record d'IP
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void IP::changeTo(int a, int b, int c, int d)
{
	a_ = a;
	b_ = b;
	c_ = c;
	d_ = d;
}

////////////////////////////////////////////////////////////////////////
/// @fn std::string IP::getStringIP() const
/// @brief 
/// @return 
////////////////////////////////////////////////////////////////////////
std::string IP::getStringIP() const
{
	std::string str = "";
	str += std::to_string(a_) + ".";
	str += std::to_string(b_) + ".";
	str += std::to_string(c_) + ".";
	str += std::to_string(d_);
	return str;
}
