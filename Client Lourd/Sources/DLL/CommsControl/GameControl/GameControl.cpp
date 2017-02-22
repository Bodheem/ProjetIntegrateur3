//////////////////////////////////////////////////////////////////////////////
/// @file GameControl.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include "GameControl.h"
#include <iostream>
#ifndef SERVERTESTER
#include "../../../Serveur/SharedFiles/IP.h"
#else
#include "../../../../../Serveur/SharedFiles/IP.h"
#endif

// Constructeur
GameControl::GameControl()
{
}

// Desctructeur
GameControl::~GameControl()
{
	delete localGameRoom_;
}

/// R�initialise le mod�le de jeu multijoueur
void GameControl::resetGameControl()
{
	delete localGameRoom_;
	localGameRoom_ = nullptr;
	etatPlayer_ = etatJoueurCONNECTING;
	etatPartie_ = etatPartieNOTHING;
	timeoutToHostConnection = 0;
}

// Obtiens la salle
GameRoom* GameControl::getRoom()
{
	return localGameRoom_;
}


// Cr�e une salle de jeu locale
bool GameControl::createGameRoom(bool isHost, User* user)
{
	etatPartie_ = etatPartieLOBBY;
	delete localGameRoom_;
	localGameRoom_ = new GameRoom(isHost, user);
	return true;
}

// Quite une salle de jeu locale
void GameControl::leaveGameRoom()
{
	etatPartie_ = etatPartieNOTHING;
	delete localGameRoom_;
	localGameRoom_ = nullptr;
}


/// Retourne l'addresse IP du host
IP* GameControl::getHostIP()
{
	return localGameRoom_->getHostIP();
}

/// Assigne l'addresse IP du host
void GameControl::setHostIP(IP* ip)
{
	localGameRoom_->setHostIP(ip);
}

/// Mettre le joueur � l'�tat Non Pret
void GameControl::setPlayerNotReady()
{
	etatPlayer_ = etatJoueurCONNECTING;
}
/// Mettre le joueur � l'�tat pret
void GameControl::setPlayerReady()
{
	etatPlayer_ = etatJoueurPRET;
}

/// Mettre le joueur � l'�tat Mort
void GameControl::setPlayerDead()
{
	etatPlayer_ = etatJoueurMORT;
}

/// Mettre le joueur � l'�tat Gagn�
void GameControl::setPlayerWon()
{
	etatPlayer_ = etatJoueurWIN;
}

/// Met � jour l'�tat de la partie
void GameControl::setGameStatus(std::string etat)
{
	etatPartie_ = etat;
	if (etat == etatPartieDEBUT)
	{
		// Map should still be loading
		
	}
	else if (etat == etatPartieSTART)
	{
		// Game starting
		etatPlayer_ = etatJoueurPRET;
	}
	else if (etat == etatPartieGAME)
	{
		// Game is actually running
	}
	else if (etat == etatPartieWIN)
	{
		// handle winning
		etatPlayer_ = etatJoueurWIN;
	}
	else if (etat == etatPartieLOSE)
	{
		etatPlayer_ = etatJoueurMORT;
	}
}

/// Retourne l'�tat de la partie
std::string GameControl::getGameStatus()
{
	return etatPartie_;
}

/// Retourne l'�tat du joueur
std::string GameControl::getPlayerStatus()
{
	return etatPlayer_;
}

/// Retourne le num�ro du joueur fourni
int GameControl::getPlayerNumber(User* user)
{
	if (localGameRoom_ == nullptr)
		return -1;

	return localGameRoom_->getPlayerNumber(user);
}

/// Retourne le num�ro du joueur fourni
int GameControl::getPlayerNumber(std::string user)
{
	if (localGameRoom_ == nullptr)
		return -1;

	return localGameRoom_->getPlayerNumber(user);
}

/// Retourne le num�ro du joueur fourni
int GameControl::getNumberOfPlayers()
{
	if (localGameRoom_ == nullptr)
		return -1;

	return localGameRoom_->getNumberOfPlayers();
}


/// Met � jour le timeout
void GameControl::updateTimeout(int timeDelta)
{
	timeoutToHostConnection += timeDelta;
	if (timeoutToHostConnection > TIMEOUT_TO_DISCONNECT &&
		etatPartie_ != etatPartieWIN &&
		etatPartie_ != etatPartieLOSE)
	{
		std::cout << "PLAYER TIMEOUT FROM HOST" << std::endl;
		etatPartie_ = etatPartieDISCONNECT;
	}
}

// Reinitialise le timeout du joueur
void GameControl::resetTimeout()
{
	timeoutToHostConnection = 0;
}


/// Incr�mente l'index de campaigne
void GameControl::incrementCampaignIndex()
{
	campaignIndex_++;
}
/// Retourne l'�tat de campaigne
int GameControl::getCampaignIndex()
{
	return campaignIndex_;
}
/// Met � jour l'index de campaigne
void GameControl::setCampaignIndex(int index)
{
	campaignIndex_ = index;
}