///////////////////////////////////////////////////////////////////////////////
/// @file InfoCompte.h
/// @author The New Ballers
/// @date 2016-01-13
/// @version 1.0
/// @ingroup Compte
///////////////////////////////////////////////////////////////////////////////
#ifndef __COMPTE_INFOCOMPTE_H__
#define __COMPTE_INFOCOMPTE_H__

#include <string>

///////////////////////////////////////////////////////////////////////////
/// @class CompteAbstrait
/// @brief 
/// @author The Ballers
/// @date 2016-01-25
/// @ingroup Compte
///////////////////////////////////////////////////////////////////////////
class InfoCompte
{
public:

	/// Constructeur par défaut
	InfoCompte();

	/// Destructeur
	virtual ~InfoCompte();

	/// Nom des informations associés au compte
	static std::string USERNAME;
	static std::string PASSWORD;
	static std::string COURRIEL;
	static std::string NAME;
	static std::string SURNAME;
	static std::string AGE;
	static std::string SHEKELS;
	static std::string AVATAR;
	static std::string IS_PUBLIC;

	static std::string AVATAR_UNLOCKED;
	static std::string ACHIEVEMENT_UNLOCKED;
	static std::string MAP_UNLOCKED;

	/// Statistiques
	static std::string GAMES_PLAYED;
	static std::string GAMES_WON;
	static std::string GAMES_COMP_WON;
	static std::string GAMES_COOP_WON;

	static std::string ACHIEVEMENT_POINT;
	static std::string FRIENDS;

};

#endif //__COMPTE_INFOCOMPTE_H__

