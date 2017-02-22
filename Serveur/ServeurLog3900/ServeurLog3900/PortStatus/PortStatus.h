//////////////////////////////////////////////////////////////////////////////
/// @file PortStatus.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_PORTSTATUS_H__
#define __SERVEUR_PORTSTATUS_H__

#include "../../../SharedFiles/User.h"
#include "../ServerControl/ServerData.h"
#include "../../../SharedFiles/IP.h"
#include <chrono>
class PortStatus
{
public:
	PortStatus(int portNumber, ServerData* serverData);
	~PortStatus();

	int getPortNumber();
	User* getUser();

	bool isUsed();
	void markUsed();
	void markAbandonned();

	bool userIsLogged();
	void addLoggedUser(User* user);
	void setRemoteIP(IP* ip);
	IP* getRemoteIP();
	bool logoutUser(); 
	bool userIsHost();
	void userJoinsGame();
	void userLeftGame();
	void setUserAsGameHost(bool status);
	bool isFirstMessageUpdate(); 
	void setFirstMessageUpdate(bool status);
	
	bool checkTimeout();
	void resetTimeout();
private:

	int portNumber_ = -1;
	bool isUsed_ = false;
	User* loggedUser_ = nullptr;
	IP* remoteIP_ = new IP();
	bool userIsLogged_ = false;
	bool userIsHost_ = false;
	bool userIsInGame_ = false;
	bool isFirstMessageUpdate_ = true;
	double timeSinceLastComms_ = 0;
	ServerData* serverData_ = nullptr;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastTime_ = std::chrono::high_resolution_clock::now();
};

#endif // __SERVEUR_PORTSTATUS_H__