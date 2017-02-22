//////////////////////////////////////////////////////////////////////////////
/// @file Main.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "../../../Client Lourd/Sources/DLL/CommsControl/GameServerControl/GameServerControl.h"

int main()
{
	std::cout << ":::Serveur de Jeu LOG3900 - The New Ballers:::" << std::endl;
	// Instancier le serveur
	GameServerControl* control = new GameServerControl();

	control->startServer(4, "tits.xml");

	// Main loop, will exit when it receives the order to
	std::cout << ":::Serveur Actif. En attente de connexions:::" << std::endl;
	while (true)
	{

	}
	return 0;
}
