//////////////////////////////////////////////////////////////////////////////
/// @file Main.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include "ServerControl\ServerControl.h"
#include <iostream>


int main()
{
	std::cout << ":::Serveur LOG3900 - The New Ballers:::" << std::endl;
	// Instancier le serveur
	ServerControl* control = ServerControl::getPointer();

	
	std::cout << ":::Chargement en memoire des donnees:::" << std::endl;
	control->serverData_->loadMemory();

	// Main loop, will exit when it receives the order to
	std::cout << ":::Serveur Actif. En attente de connexions:::" << std::endl;
	bool quit = false;
	while (!quit)
	{
		quit = control->mainThreadLoop();
		delete control;
		control = ServerControl::getPointer();
	}

	return 0;
}
