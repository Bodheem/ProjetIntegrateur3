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
/// @brief Classe repr�sentant un utilisateur et ses informations de compte
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

	/// Retourne true si le compte est connect�
	bool isLogged() const;

	/// Change le mot de passe de fa�on autoritaire
	void setPassword(std::string pass);

	/// Retourne le couriel de l'utilisateur
	std::string getEmail() const;

	/// Retourne les informations de base et suppl�mentaires
	std::vector<std::string> getBasicInfo() const;

	/// Met � jour les informations de base et suppl�mentaires
	bool setBasicInfo(std::vector<std::string> info);

	/// Retourne la liste d'amis
	std::vector<std::string> getFriendInfo() const;

	/// Met � jour la liste d'amis
	bool setFriendInfo(std::vector<std::string> info);

	/// Retourne la liste de cartes
	std::vector<std::string> getMapInfo() const;

	/// Met � jour la liste de cartes
	bool setMapInfo(std::vector<std::string> info);

	/// Ajouter un avatar d�bloqu�
	void addUnlockedMap(std::string map);

	/// Retourne la liste de textures
	std::vector<std::string> getAvatarUnlocked() const;

	/// Met � jour la liste de textures
	bool setAvatarUnlocked(std::vector<std::string> info);

	/// Ajouter un avatar d�bloqu�
	void addUnlockedAvatar(std::string avatar);

	/// Retourne la liste d'achievements
	std::vector<std::string> getAchievementsInfo() const;

	/// Met � jour la liste d'achievements
	bool setAchievementsInfo(std::vector<std::string> info);

	/// Ajouter un achievement d�bloqu�
	void addAchievement(std::string achievement);

	/// Obtenir une statistique
	std::vector<std::string> obtenirStatistique() const;

	/// Assigner une statistique
	void assignerStatistique(std::vector<std::string> stats, bool writePlayedGames = false);

	/// Ajoute une partie jou�e de plus
	void addPlayedGame();

	/// Ajoute une partie gagn�e de plus
	void addWonGame(bool competitif);

	/// Ajoute un ami selon la string. Ne fais aucune op�ration sur la BD
	bool addFriend(std::string username);

	/// Enleve un ami
	bool removeFriend(User* oldFriend);

	/// Retourne la liste des amis
	std::vector<std::string> getFriendList() const;

private:

	/// Informations de base
	
	/// Nom du compte
	std::string userName_;

	/// Email reli� au compte
	std::string email_;

	/// Mot de passe du compte
	std::string password_;

	/// Informations suppl�mentaires

	/// Nom de l'utilisateur
	std::string name_;

	/// Pr�nom de l'utilisateur
	std::string surname_;

	/// Savoir si le profil est public
	bool isPublic_;

	/// Age de l'utilisateur
	unsigned int userAge_ = 0;

	/// Argent en jeu de l'utilisateur
	unsigned int shekels_ = 0;

	/// Les points d'achievement
	unsigned int achievementPoint_ = 0;

	/// Nombre de partie jou�s
	unsigned int partiesJoues_ = 0;

	/// Nombre de victoire
	unsigned int partiesGagnes_ = 0;

	/// Nombre de parties en comp�titif gagn�s
	unsigned int partiesCompetitifGagne = 0;

	/// Nombre de parties en comp�titif gagn�s
	unsigned int partiesCoopGagne = 0;

	/// Pour l'avatar
	std::string avatar_;

	/// Informations de jeu

	/// Liste d'amis
	std::vector<std::string> listeAmis_;

	/// Liste des textures optionnelles d�bloqu�es sur le march�
	std::vector<std::string> listeUnlockedAvatar;

	/// Liste des noms de cartes d�bloqu�es sur le serveur
	std::vector<std::string> listeUnlockedMaps_;

	/// Vector de son avancement dans les diff�rents accomplissements
	std::vector<std::string> listeAchievements_;
	
	/// True si le compte est connect� quelque part
	bool isLogged_ = false;
};

#endif // __SERVEUR_USER_H__