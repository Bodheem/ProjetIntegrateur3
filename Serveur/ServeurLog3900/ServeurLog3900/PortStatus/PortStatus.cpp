//////////////////////////////////////////////////////////////////////////////
/// @file PortStatus.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////


#include "PortStatus.h"
#include <iostream>

/// Port timeout in seconds
const double PORT_TIMEOUT_VALUE = 600;
PortStatus::PortStatus(int portNumber, ServerData* serverData)
{
	portNumber_ = portNumber;
	serverData_ = serverData;
}

PortStatus::~PortStatus()
{
}

bool PortStatus::isUsed()
{
	return isUsed_;
}

int PortStatus::getPortNumber()
{
	return portNumber_;
}

User* PortStatus::getUser()
{
	timeSinceLastComms_ = 0;
	return loggedUser_;
}

void PortStatus::markUsed()
{
	timeSinceLastComms_ = 0;
	isUsed_ = true;
}

void PortStatus::markAbandonned()
{
	timeSinceLastComms_ = 0;
	isUsed_ = false;
	std::cout << "Port lapsed: " << portNumber_ << std::endl;
	if (userIsHost_)
	{
		serverData_->gameControl_->leaveGameRoom(loggedUser_);
		userIsInGame_ = false;
	}
	if (userIsInGame_)
	{
		serverData_->gameControl_->leaveGameRoom(loggedUser_);
		userIsInGame_ = false;
	}
	if (userIsLogged_ && loggedUser_ != nullptr)
	{
		std::string username = getUser()->getUserName();
		std::cout << "Also logging out user: " << username << std::endl;
		std::string packageout;
		bool success = serverData_->userControl_->logoutUser(username);
	}
	userIsLogged_ = false;
	userIsHost_ = false;
	userIsInGame_ = false;
	loggedUser_ = nullptr;
	remoteIP_->changeTo(0, 0, 0, 0);
	isFirstMessageUpdate_ = true;
}

void PortStatus::addLoggedUser(User* user)
{
	timeSinceLastComms_ = 0;
	loggedUser_ = user;
	userIsLogged_ = true;
}

void PortStatus::setRemoteIP(IP* ip)
{
	remoteIP_->changeTo(ip->a_, ip->b_, ip->c_, ip->d_);
}

IP* PortStatus::getRemoteIP()
{
	return remoteIP_;
}

bool PortStatus::userIsHost()
{
	return userIsHost_;
}

void PortStatus::userJoinsGame()
{
	userIsInGame_ = true;
}

void PortStatus::userLeftGame()
{
	userIsInGame_ = false;
}

void PortStatus::setUserAsGameHost(bool status)
{
	timeSinceLastComms_ = 0;
	userIsHost_ = status;
}

bool PortStatus::logoutUser()
{
	timeSinceLastComms_ = 0;
	userIsLogged_ = false;
	if (userIsHost_)
	{
		serverData_->gameControl_->leaveGameRoom(loggedUser_);
		userIsInGame_ = false;
	}
	if (userIsInGame_)
	{
		serverData_->gameControl_->leaveGameRoom(loggedUser_);
		userIsInGame_ = false;
	}
	userIsHost_ = false;
	if (loggedUser_ == nullptr)
		return false;
	loggedUser_->logoutUser();
	loggedUser_ = nullptr;
	return true;
}

bool PortStatus::isFirstMessageUpdate()
{
	return isFirstMessageUpdate_;
}

void PortStatus::setFirstMessageUpdate(bool status)
{
	timeSinceLastComms_ = 0;
	isFirstMessageUpdate_ = status;
}

bool PortStatus::userIsLogged()
{
	return userIsLogged_;
}

bool PortStatus::checkTimeout()
{
	if (!isUsed_)
		return false;
	
	auto time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = time - lastTime_;
	timeSinceLastComms_ += diff.count();
	lastTime_ = time;
	return (timeSinceLastComms_ > PORT_TIMEOUT_VALUE);
}

void PortStatus::resetTimeout()
{
	timeSinceLastComms_ = 0;
}