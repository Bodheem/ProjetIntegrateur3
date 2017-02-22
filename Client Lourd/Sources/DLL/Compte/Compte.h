///////////////////////////////////////////////////////////////////////////////
/// @file Compte.h
/// @author The New Ballers
/// @date 2016-01-13
/// @version 1.0
/// @ingroup Sauvegarde
///////////////////////////////////////////////////////////////////////////////
#ifndef __COMPTE_COMPTE_H__
#define __COMPTE_COMPTE_H__

#include "Joueur.h"

class InfoCompte;
class User;

///////////////////////////////////////////////////////////////////////////
/// @class Compte
/// @brief
/// @author The Ballers
/// @date 2015-02-02
/// @ingroup Sauvegarde
///////////////////////////////////////////////////////////////////////////
class Compte : public Joueur
{
public:

	/// Constructeur par défaut
	Compte(User* user);

	/// Destructeur
	virtual ~Compte();

	/// Retourner toutes les informations concernant le joueur
	std::string getAllInformations() const override;

	/// Retourner toutes les informations du joueur comme un vecteur
	std::vector<std::string> getInformationsToVector() const override;

	/// Assigner les informations selon le format
	void setInformationFromString(std::string info) override;

	/// Obtenir la liste des avatar débloqués
	std::vector<std::string> getAvatarUnlocked() const override;

	/// Avoir les achievements débloqués
	std::vector<std::string> getAchievementUnlocked() const override;

	/// Avoir les map débloqués
	std::vector<std::string> getMapUnlocked() const override;

	/// Obtenir une statistique
	std::vector<std::string> obtenirStatistique() const override;

	/// Assigner une statistique
	void assignerStatistique(std::vector<std::string> stats) override;

private:

	/// Assigner une valeur à une information
	void setInformation(std::string infoType, std::string value) override;

	/// Mot de passe de l'utilisateur
	std::string password_;

	/// Nom de l'utilisateur
	std::string name_;

	/// Courriel
	std::string courriel_;

	/// Surnom
	std::string surname_;

	/// Chemin d'acces vers l'avatar
	std::string avatar_;
	
	/// Liste des avatars débloqués
	std::vector<std::string> avatarUnlocked_;

	/// Liste des avatars débloqués
	std::vector<std::string> achievementUnlocked_;

	/// Liste des cartes débloqués
	std::vector<std::string> mapUnlocked_;

	/// Savoir si les informations du compte sont publiques
	bool isPublic_;

	/// Age de l'utilisateur
	unsigned int age_;

	/// Nombre de partie joués
	unsigned int partiesJoues_ = 0;

	/// Nombre de victoire
	unsigned int partiesGagnes_ = 0;

	/// Nombre de parties en compétitif gagnés
	unsigned int partiesCompetitifGagne = 0;

	/// Nombre de parties en compétitif gagnés
	unsigned int partiesCoopGagne = 0;

};

#endif //__COMPTE_COMPTE_H__

