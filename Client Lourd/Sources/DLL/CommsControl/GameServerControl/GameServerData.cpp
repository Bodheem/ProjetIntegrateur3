//////////////////////////////////////////////////////////////////////////////
/// @file GameServerData.cpp
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#include "GameServerData.h"
#include <iostream>
#include "../../Application/FacadeJeu.h"
#include <mutex>

// Initialize Static pointer
GameServerData* GameServerData::GameServerDataPointer = nullptr;

// Static function to obtain pointer to main form
GameServerData* GameServerData::getPointer()
{
	if (GameServerDataPointer == nullptr)
		GameServerDataPointer = new GameServerData();
	return GameServerDataPointer;
}

// Constructeur
GameServerData::GameServerData()
{
	GameServerDataPointer = this;
}

// Destructeur
GameServerData::~GameServerData()
{
	GameServerDataPointer = nullptr;
}

// Prépare la partie
void GameServerData::configureGame(int numberOfPlayers, std::string mapName)
{
	safetyMutex_.lock();
	numberOfPlayers_ = numberOfPlayers;
	mapName_ = mapName;

	switch (numberOfPlayers_)
	{
	case 1:
		etatPlayer2_ = etatJoueurABSENT;
	case 2:
		etatPlayer3_ = etatJoueurABSENT;
	case 3:
		etatPlayer4_ = etatJoueurABSENT;
	case 4:
	default:
		break;
	}
	safetyMutex_.unlock();
}

// Retourne l'état actuel de la partie pour le joueur fourni
// TOUJOURS sur 5 char
std::string GameServerData::getGameStatus(int player)
{
	if (etatPartie_ == etatPartieDEBUT)
		return etatPartie_;
	if (etatPartie_ == etatPartieSTART)
		return etatPartie_;
	if (etatPartie_ == etatPartieWIN)
		return etatPartie_;
	if (etatPartie_ == etatPartieLOSE)
		return etatPartie_;
	if (etatPartie_ == etatPartieGAME)
	{
		switch (player)
		{
		case 0:
			return etatPartie_;
		case 1:
			if (etatPlayer1_ == etatJoueurMORT)
				return etatJoueurMORT;
			break;
		case 2:
			if (etatPlayer2_ == etatJoueurMORT)
				return etatJoueurMORT;
			break;
		case 3:
			if (etatPlayer3_ == etatJoueurMORT)
				return etatJoueurMORT;
			break;
		case 4:
			if (etatPlayer4_ == etatJoueurMORT)
				return etatJoueurMORT;
			break;
		}
		return etatPartieGAME;
	}
	return etatPartieGAME;
}

/// assigne l'état actuel de la partie
void GameServerData::setGameStatus(std::string status)
{
	safetyMutex_.lock();
	etatPartie_ = status;
	safetyMutex_.unlock();
}

/// Retourne l'index de campaigne
int GameServerData::getCampaignIndex()
{
	return campaignIndex_;
}

/// Incrémente l'index de campaigne
void GameServerData::incrementCampaignIndex()
{
	campaignIndex_++;
}

// Retourne le nombre maximal de joueurs pour la carte
int GameServerData::getNumberOfPlayers()
{
	return numberOfPlayers_;
}

/// Assigne l'état actuel d'un joueur selon son IP
void GameServerData::setPlayerStatus(std::string status, IP* playerIP)
{
	safetyMutex_.lock();
	int playerIndex = getPlayerByIP(*playerIP);
	std::string detectedStatus = etatJoueurABSENT;
	if (status == etatJoueurABSENT)
		detectedStatus = etatJoueurABSENT;
	else if (status == etatJoueurCONNECTING)
		detectedStatus = etatJoueurCONNECTING;
	else if (status == etatJoueurDISCONNECT)
		detectedStatus = etatJoueurDISCONNECT;
	else if (status == etatJoueurMORT)
		detectedStatus = etatJoueurMORT;
	else if (status == etatJoueurNONPRET)
		detectedStatus = etatJoueurNONPRET;
	else if (status == etatJoueurPRET)
		detectedStatus = etatJoueurPRET;
	else
	{
		safetyMutex_.unlock();
		return;
	}

	switch (playerIndex)
	{
	case 1:
		etatPlayer1_ = detectedStatus;
	case 2:
		etatPlayer2_ = detectedStatus;
	case 3:
		etatPlayer3_ = detectedStatus;
	case 4:
		etatPlayer4_ = detectedStatus;
	case -1:
	default:
		break;
	}
	safetyMutex_.unlock();
}

// Mettre le joueur à l'état pret
void GameServerData::setPlayerReady(int player, bool status)
{
	safetyMutex_.lock();
	switch (player)
	{
	case 1:
		if (etatPlayer1_ != etatJoueurABSENT)
		{
			if (status)
				etatPlayer1_ = etatJoueurPRET;
			else
				etatPlayer1_ = etatJoueurNONPRET;
		}
		break;
	case 2:
		if (etatPlayer2_ != etatJoueurABSENT)
		{
			if (status)
				etatPlayer2_ = etatJoueurPRET;
			else
				etatPlayer2_ = etatJoueurNONPRET;
		}
		break;
	case 3:
		if (etatPlayer3_ != etatJoueurABSENT)
		{
			if (status)
				etatPlayer3_ = etatJoueurPRET;
			else
				etatPlayer3_ = etatJoueurNONPRET;
		}
		break;
	case 4:
		if (etatPlayer4_ != etatJoueurABSENT)
		{
			if (status)
				etatPlayer4_ = etatJoueurPRET;
			else
				etatPlayer4_ = etatJoueurNONPRET;
		}
		break;
	}
	safetyMutex_.unlock();
}
/// Retourne true si tout les joueurs sont prets
bool GameServerData::allPlayersReady()
{
	if (etatPlayer1_ == etatJoueurPRET)
		if (etatPlayer2_ == etatJoueurPRET || etatPlayer2_ == etatJoueurABSENT || etatPlayer2_ == etatJoueurDISCONNECT)
			if (etatPlayer3_ == etatJoueurPRET || etatPlayer3_ == etatJoueurABSENT || etatPlayer3_ == etatJoueurDISCONNECT)
				if (etatPlayer4_ == etatJoueurPRET || etatPlayer4_ == etatJoueurABSENT || etatPlayer4_ == etatJoueurDISCONNECT)
					return true;
	return false;
}
/// Retourne true si tout les joueurs sont Gagnant
bool GameServerData::allPlayersWon()
{
	if (etatPlayer1_ == etatJoueurWIN)
		if (etatPlayer2_ == etatJoueurWIN || etatPlayer2_ == etatJoueurABSENT || etatPlayer2_ == etatJoueurDISCONNECT)
			if (etatPlayer3_ == etatJoueurWIN || etatPlayer3_ == etatJoueurABSENT || etatPlayer3_ == etatJoueurDISCONNECT)
				if (etatPlayer4_ == etatJoueurWIN || etatPlayer4_ == etatJoueurABSENT || etatPlayer4_ == etatJoueurDISCONNECT)
					return true;
	return false;
}
/// Retourne true si tout les joueurs sont Morts
bool GameServerData::allPlayersDead()
{
	if (etatPlayer1_ == etatJoueurMORT)
		if (etatPlayer2_ == etatJoueurMORT || etatPlayer2_ == etatJoueurABSENT || etatPlayer2_ == etatJoueurDISCONNECT)
			if (etatPlayer3_ == etatJoueurMORT || etatPlayer3_ == etatJoueurABSENT || etatPlayer3_ == etatJoueurDISCONNECT)
				if (etatPlayer4_ == etatJoueurMORT || etatPlayer4_ == etatJoueurABSENT || etatPlayer4_ == etatJoueurDISCONNECT)
					return true;
	return false;
}

// Mettre le joueur à l'état mort
void GameServerData::setPlayerDead(int player)
{
	safetyMutex_.lock();
	switch (player)
	{
	case 1:
		etatPlayer1_ = etatJoueurMORT;
		break;
	case 2:
		etatPlayer2_ = etatJoueurMORT;
		break;
	case 3:
		etatPlayer3_ = etatJoueurMORT;
		break;
	case 4:
		etatPlayer4_ = etatJoueurMORT;
		break;
	}
	safetyMutex_.unlock();
}


// Mettre le joueur à l'état gagnant
void GameServerData::setPlayerWon(int player)
{
	safetyMutex_.lock();
	switch (player)
	{
	case 1:
		etatPlayer1_ = etatJoueurWIN;
		break;
	case 2:
		etatPlayer2_ = etatJoueurWIN;
		break;
	case 3:
		etatPlayer3_ = etatJoueurWIN;
		break;
	case 4:
		etatPlayer4_ = etatJoueurWIN;
		break;
	}
	safetyMutex_.unlock();
}



/// Mettre le joueur à l'état Disconnected
void GameServerData::setPlayerDisconnected(int player)
{
	safetyMutex_.lock();
	switch (player)
	{
	case 1:
		if (etatPlayer1_ != etatJoueurABSENT)
			etatPlayer1_ = etatJoueurDISCONNECT;
		break;
	case 2:
		if (etatPlayer1_ != etatJoueurABSENT)
			etatPlayer2_ = etatJoueurDISCONNECT;
		break;
	case 3:
		if (etatPlayer1_ != etatJoueurABSENT)
			etatPlayer3_ = etatJoueurDISCONNECT;
		break;
	case 4:
		if (etatPlayer1_ != etatJoueurABSENT)
			etatPlayer4_ = etatJoueurDISCONNECT;
		break;
	}
	safetyMutex_.unlock();
}

// Assigne un joueur à un IP ou le reconnecte
bool GameServerData::assignPlayerIP(IP ip, int index)
{
	safetyMutex_.lock();
	switch (index)
	{
	case 2:
		if (IPPlayer2_->getStringIP() == "0.0.0.0" ||
			IPPlayer2_->getStringIP() == ip.getStringIP())
		{
			// Joueur reconnectant
			if (IPPlayer2_->getStringIP() != "0.0.0.0")
				FacadeJeu::obtenirInstance()->activerAI(false, 2);
			else // Joueur accepté
				IPPlayer2_->changeTo(ip.a_, ip.b_, ip.c_, ip.d_);
			timeoutCounterPlayer2_ = 0;
			break;
		}
	case 3:
		if (IPPlayer3_->getStringIP() == "0.0.0.0" ||
			IPPlayer3_->getStringIP() == ip.getStringIP())
		{
			// Joueur reconnectant
			if (IPPlayer3_->getStringIP() != "0.0.0.0")
				FacadeJeu::obtenirInstance()->activerAI(false, 3);
			else // Joueur accepté
				IPPlayer3_->changeTo(ip.a_, ip.b_, ip.c_, ip.d_);
			timeoutCounterPlayer3_ = 0;
			break;
		}
	case 4:
		if (IPPlayer4_->getStringIP() == "0.0.0.0" ||
			IPPlayer4_->getStringIP() == ip.getStringIP())
		{
			// Joueur reconnectant
			if (IPPlayer4_->getStringIP() != "0.0.0.0")
				FacadeJeu::obtenirInstance()->activerAI(false, 4);
			else // Joueur accepté
				IPPlayer4_->changeTo(ip.a_, ip.b_, ip.c_, ip.d_);
			timeoutCounterPlayer4_ = 0;
			break;
		}
	default:
		safetyMutex_.unlock();
		return false;
	}

	safetyMutex_.unlock();
	return true;

}

// Retourne le numéro du joueur selon son IP
int GameServerData::getPlayerByIP(IP ip)
{
	if (IPPlayer2_->getStringIP() == ip.getStringIP())
		return 2;
	if (IPPlayer3_->getStringIP() == ip.getStringIP())
		return 3;
	if (IPPlayer4_->getStringIP() == ip.getStringIP())
		return 4;
	return -1;
}


/// Retourne tout les joueurs présentement connectés
std::vector<IP*> GameServerData::getAllPlayers()
{
	std::vector<IP*> ret;
	if (IPPlayer2_->getStringIP() != "0.0.0.0")
		ret.push_back(IPPlayer2_);
	if (IPPlayer3_->getStringIP() != "0.0.0.0")
		ret.push_back(IPPlayer3_);
	if (IPPlayer4_->getStringIP() != "0.0.0.0")
		ret.push_back(IPPlayer4_);
	return ret;
}


/// Met à jour l'état des connexions des joueurs
void GameServerData::updatePlayerTimeouts(int timeDelta)
{
	timeoutCounterPlayer2_ += timeDelta;
	timeoutCounterPlayer3_ += timeDelta;
	timeoutCounterPlayer4_ += timeDelta;

	if (((etatPartie_ == etatPartieDEBUT || etatPartie_ == etatPartieSTART) && timeoutCounterPlayer2_ > TIMEOUT_TO_DISCONNECT_IN_LOADING)
		||
		(etatPartie_ == etatPartieGAME && timeoutCounterPlayer2_ > TIMEOUT_TO_DISCONNECT_IN_GAME))
	{
		if (etatPlayer2_ != etatJoueurDISCONNECT && etatPlayer2_ != etatJoueurABSENT)
		{
			std::cout << "HOST TIMEOUT FROM PLAYER 2" << std::endl;
			setPlayerDisconnected(2);
			FacadeJeu::obtenirInstance()->activerAI(true, 2);
		}
	}
	else
	{
		if (etatPlayer2_ == etatJoueurDISCONNECT)
		{
			std::cout << "HOST PLAYER 2 RECONNECTED" << std::endl;
			etatPlayer2_ = etatJoueurPRET;
			FacadeJeu::obtenirInstance()->activerAI(false, 2);
		}
	}

	if (((etatPartie_ == etatPartieDEBUT || etatPartie_ == etatPartieSTART) && timeoutCounterPlayer3_ > TIMEOUT_TO_DISCONNECT_IN_LOADING)
		||
		(etatPartie_ == etatPartieGAME && timeoutCounterPlayer3_ > TIMEOUT_TO_DISCONNECT_IN_GAME))
	{
		if (etatPlayer3_ != etatJoueurDISCONNECT && etatPlayer3_ != etatJoueurABSENT)
		{
			std::cout << "HOST TIMEOUT FROM PLAYER 3" << std::endl;
			setPlayerDisconnected(3);
			FacadeJeu::obtenirInstance()->activerAI(true, 3);
		}
	}
	else
	{
		if (etatPlayer3_ == etatJoueurDISCONNECT)
		{
			std::cout << "HOST PLAYER 3 RECONNECTED" << std::endl;
			etatPlayer3_ = etatJoueurPRET;
			FacadeJeu::obtenirInstance()->activerAI(false, 3);
		}
	}

	if (((etatPartie_ == etatPartieDEBUT || etatPartie_ == etatPartieSTART) && timeoutCounterPlayer4_ > TIMEOUT_TO_DISCONNECT_IN_LOADING)
		||
		(etatPartie_ == etatPartieGAME && timeoutCounterPlayer4_ > TIMEOUT_TO_DISCONNECT_IN_GAME))
	{
		if (etatPlayer4_ != etatJoueurDISCONNECT && etatPlayer4_ != etatJoueurABSENT)
		{
			std::cout << "HOST TIMEOUT FROM PLAYER 4" << std::endl;
			setPlayerDisconnected(4);
			FacadeJeu::obtenirInstance()->activerAI(true, 4);
		}
	}
	else
	{
		if (etatPlayer4_ == etatJoueurDISCONNECT)
		{
			std::cout << "HOST PLAYER 4 RECONNECTED" << std::endl;
			etatPlayer4_ = etatJoueurPRET;
			FacadeJeu::obtenirInstance()->activerAI(false, 4);
		}
	}
}


/// Remet à zero le timeout du joueur
void GameServerData::resetPlayerTimeout(int noJoueur)
{
	switch (noJoueur)
	{
	case 2:
		timeoutCounterPlayer2_ = 0;
	case 3:
		timeoutCounterPlayer3_ = 0;
	case 4:
		timeoutCounterPlayer4_ = 0;
	default:
		break;
	}
}
