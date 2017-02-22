///////////////////////////////////////////////////////////////////////////////
/// @file CompteAbstrait.h
/// @author The New Ballers
/// @date 2016-01-13
/// @version 1.0
/// @ingroup Compte
///////////////////////////////////////////////////////////////////////////////
#ifndef __COMPTE_COMPTEABSTRAIT_H__
#define __COMPTE_COMPTEABSTRAIT_H__

#include <string>
#include "../Configuration/Configuration.h"
#include "../Sauvegarde/Propriete.h"

///////////////////////////////////////////////////////////////////////////
/// @class CompteAbstrait
/// @brief 
/// @author The Ballers
/// @date 2016-01-25
/// @ingroup Compte
///////////////////////////////////////////////////////////////////////////
class CompteAbstrait
{
public:

	/// Constructeur par défaut
	CompteAbstrait() { };

	/// Destructeur
	virtual ~CompteAbstrait() = 0 { };

	/// Obtenir le nom
	virtual std::string getName() const { return ""; };

protected:

	// Nom de l'objet courant
	std::string name;
};

#endif //__COMPTE_COMPTEABSTRAIT_H__

