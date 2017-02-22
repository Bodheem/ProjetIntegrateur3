///////////////////////////////////////////////////////////////////////////////
/// @file Joueur.h
/// @author The New Ballers
/// @date 2016-01-13
/// @version 1.0
/// @ingroup Compte
///////////////////////////////////////////////////////////////////////////////
#ifndef __COMPTE_JOUEUR_H__
#define __COMPTE_JOUEUR_H__

#include <string>
#include <vector>

///////////////////////////////////////////////////////////////////////////
/// @class CompteAbstrait
/// @brief 
/// @author The Ballers
/// @date 2016-01-25
/// @ingroup Compte
///////////////////////////////////////////////////////////////////////////
class Joueur
{
public:

	/// Constructeur par défaut
	Joueur();

	/// Destructeur
	virtual ~Joueur() = 0;

	/// Obtenir le nom
	virtual std::string getName() const;

	/// Obtenir le nombre de point d'achievements
	virtual unsigned int getAchievementPoint() const;

	/// Donner des points
	virtual void addAchievementPoints(unsigned int achPoints);

	/// Obtenir le nombre de point d'achievements
	virtual unsigned int getShekels() const;

	/// Donner des points au joueur
	virtual void addShekels(unsigned int shekels);

	/// Retourner toutes les informations concernant le joueur selon le bon format de string
	virtual std::string getAllInformations() const;

	/// Retourner toutes les informations du joueur comme un vecteur
	virtual std::vector<std::string> getInformationsToVector() const;

	/// Assigner les informations selon le format
	virtual void setInformationFromString(std::string info);

	/// Savoir si on a affaire a un compte online ou non
	virtual bool isOnlineAccount() const;

	/// Avoir les avatar débloqués
	virtual std::vector<std::string> getAvatarUnlocked() const;

	/// Avoir les achievements débloqués
	virtual std::vector<std::string> getAchievementUnlocked() const;

	/// Avoir les achievements débloqués
	virtual std::vector<std::string> getMapUnlocked() const;

	/// Obtenir une statistique
	virtual std::vector<std::string> obtenirStatistique() const;

	/// Assigner une statistique
	virtual void assignerStatistique(std::vector<std::string> stats);

protected:

	/// Assigner une valeur à une information
	virtual void setInformation(std::string infoType, std::string value);

	/// Nom d'usager
	std::string username_;

	/// Points des achievements
	unsigned int achievementPoint_;

	/// Argent du joueur
	unsigned int shekels_;

	/// Savoir si on a affaire a un compte online ou offline
	bool isOnline_;
};

#endif //__COMPTE_JOUEUR_H__

