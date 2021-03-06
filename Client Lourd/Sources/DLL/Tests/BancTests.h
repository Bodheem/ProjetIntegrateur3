/*
//////////////////////////////////////////////////////////////////////////////
/// @file BancTests.h
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @version 1.0
///
/// @ingroup Test
//////////////////////////////////////////////////////////////////////////////

/** @defgroup Test Test
*	@ingroup Noyau
* /

#ifndef _TESTS_BANCTESTS_H
#define _TESTS_BANCTESTS_H

#include "Singleton.h"

///////////////////////////////////////////////////////////////////////////
/// @class BancTests
/// @brief Banc de tests qui permet d'executer tous les tests unitaires.
///        C'est une classe singleton.
///
/// @author Julien Gascon-Samson
/// @date 2011-07-16
/// @ingroup Test
///////////////////////////////////////////////////////////////////////////
class BancTests : public Singleton<BancTests>
{
   SINGLETON_DECLARATION_CLASSE(BancTests);

public:
	/// Executer tous les tests unitaires
	bool executer();
};

#endif // _TESTS_BANCTESTS_H
*/