//////////////////////////////////////////////////////////////////////////////
/// @file Main.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "../../../Client Lourd/Sources/DLL/CommsControl/CommsControl.h"



int main()
{
	std::cout << ":::Serveur de Jeu LOG3900 - The New Ballers:::" << std::endl;
	// Instancier le serveur
	CommsControl* test = new CommsControl();
	test->initializeCommunications("132.207.245.235");
	//test->initializeCommunications("127.0.0.1");
	if (!test->commsTest())
	{
		std::cout << "HOLY FUCKING BATMAN SHIT GOT REKT";
	}

	/*WSADATA wsaData;
	int wsaStartupResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsaStartupResult != 0)
	{
		std::cout << "Erreur de WSAStartup: " << wsaStartupResult << std::endl;
		return false;
	}*/
	//test->initializeMultiplayerGame();


	// Main loop, will exit when it receives the order to
	std::cout << ":::Serveur Actif. En attente de connexions:::" << std::endl;
	int in;
	std::cin >> in;
	WSACleanup();
	return 0;
}
