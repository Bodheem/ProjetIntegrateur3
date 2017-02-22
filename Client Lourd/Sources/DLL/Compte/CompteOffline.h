///////////////////////////////////////////////////////////////////////////////
/// @file CompteOffline.h
/// @author The New Ballers
/// @date 2016-01-13
/// @version 1.0
/// @ingroup Sauvegarde
///////////////////////////////////////////////////////////////////////////////
#ifndef __COMPTE_COMPTEOFFLINE_H__
#define __COMPTE_COMPTEOFFLINE_H__

#include "Joueur.h"

///////////////////////////////////////////////////////////////////////////
/// @class CompteOffline
/// @brief
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Sauvegarde
///////////////////////////////////////////////////////////////////////////
class CompteOffline : public Joueur
{
public:

	/// Constructeur par défaut
	CompteOffline();

	/// Destructeur
	virtual ~CompteOffline();

	/// Avoir les informations du compte
	std::string getAllInformations() const override;
};

#endif //__COMPTE_COMPTEOFFLINE_H__

