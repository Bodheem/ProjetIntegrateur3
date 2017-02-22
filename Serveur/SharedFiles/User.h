//////////////////////////////////////////////////////////////////////////////
/// @file User.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
///
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_USER_H__
#define __SERVEUR_USER_H__

#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
/// @class User
/// @brief Classe représentant un utilisateur et ses informations de compte
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class User
{
public:

	/// Constructeur
	User(std::string username, std::string password, std::string email);

	/// Destructeur
	~User();

	/// Obtenir le pseudonyme
	std::string getUserName() const;

	/// Authentification de compte
	bool loginUser(std::string pass);

	/// Deconnexion de compte
	bool logoutUser();

	/// Retourne true si le compte est connecté
	bool isLogged() const;

	/// Change le mot de passe de façon autoritaire
	void setPassword(std::string pass);

	/// Retourne le couriel de l'utilisateur
	std::string getEmail() const;

	/// Retourne les informations de base et supplémentaires
	std::vector<std::string> getBasicInfo() const;

	/// Met à jour les informations de base et supplémentaires
	bool setBasicInfo(std::vector<std::string> info);

	/// Retourne la liste d'amis
	std::vector<std::string> getFriendInfo() const;

	/// Met à jour la liste d'amis
	bool setFriendInfo(std::vector<std::string> info);

	/// Retourne la liste de cartes
	std::vector<std::string> getMapInfo() const;

	/// Met à jour la liste de cartes
	bool setMapInfo(std::vector<std::string> info);

	/// Ajouter un avatar débloqué
	void addUnlockedMap(std::string map);

	/// Retourne la liste de textures
	std::vector<std::string> getAvatarUnlocked() const;

	/// Met à jour la liste de textures
	bool setAvatarUnlocked(std::vector<std::string> info);

	/// Ajouter un avatar débloqué
	void addUnlockedAvatar(std::string avatar);

	/// Retourne la liste d'achievements
	std::vector<std::string> getAchievementsInfo() const;

	/// Met à jour la liste d'achievements
	bool setAchievementsInfo(std::vector<std::string> info);

	/// Ajouter un achievement débloqué
	void addAchievement(std::string achievement);

	/// Obtenir une statistique
	std::vector<std::string> obtenirStatistique() const;

	/// Assigner une statistique
	void assignerStatistique(std::vector<std::string> stats, bool writePlayedGames = false);

	/// Ajoute une partie jouée de plus
	void addPlayedGame();

	/// Ajoute une partie gagnée de plus
	void addWonGame(bool competitif);

	/// Ajoute un ami selon la string. Ne fais aucune opération sur la BD
	bool addFriend(std::string username);

	/// Enleve un ami
	bool removeFriend(User* oldFriend);

	/// Retourne la liste des amis
	std::vector<std::string> getFriendList() const;

private:

	/// Informations de base
	
	/// Nom du compte
	std::string userName_;

	/// Email relié au compte
	std::string email_;

	/// Mot de passe du compte
	std::string password_;

	/// Informations supplémentaires

	/// Nom de l'utilisateur
	std::string name_;

	/// Prénom de l'utilisateur
	std::string surname_;

	/// Savoir si le profil est public
	bool isPublic_;

	/// Age de l'utilisateur
	unsigned int userAge_ = 0;

	/// Argent en jeu de l'utilisateur
	unsigned int shekels_ = 0;

	/// Les points d'achievement
	unsigned int achievementPoint_ = 0;

	/// Nombre de partie joués
	unsigned int partiesJoues_ = 0;

	/// Nombre de victoire
	unsigned int partiesGagnes_ = 0;

	/// Nombre de parties en compétitif gagnés
	unsigned int partiesCompetitifGagne = 0;

	/// Nombre de parties en compétitif gagnés
	unsigned int partiesCoopGagne = 0;

	/// Pour l'avatar
	std::string avatar_;

	/// Informations de jeu

	/// Liste d'amis
	std::vector<std::string> listeAmis_;

	/// Liste des textures optionnelles débloquées sur le marché
	std::vector<std::string> listeUnlockedAvatar;

	/// Liste des noms de cartes débloquées sur le serveur
	std::vector<std::string> listeUnlockedMaps_;

	/// Vector de son avancement dans les différents accomplissements
	std::vector<std::string> listeAchievements_;
	
	/// True si le compte est connecté quelque part
	bool isLogged_ = false;
};

#endif // __SERVEUR_USER_H__