//////////////////////////////////////////////////////////////////////////////
/// @file UserControl.h
/// @author The Ballers
/// @date 2016-01-24
/// @version 1.0 
/// @ingroup Serveur
//////////////////////////////////////////////////////////////////////////////

#ifndef __SERVEUR_USERCONTROL_H__
#define __SERVEUR_USERCONTROL_H__

#include <string>
#include <map>
#include <vector>

class User;

////////////////////////////////////////////////////////////////////////////////
/// @class UserControl
/// @brief Classe qui g�re les objets de type User
/// @author The ballers
/// @date 2016-01-24
////////////////////////////////////////////////////////////////////////////////
class UserControl
{
public:

	// Constructeur
	UserControl();

	// Destructeur
	~UserControl();

	// Pour la cr�ation de compte
	bool createUser(std::string username, std::string password, std::string email);

	// Authentification de compte
	bool loginUser(std::string username, std::string pass);

	// Deconnexion de compte
	bool logoutUser(std::string username);

	// Obtenir un compte
	User* getUser(std::string username);

	// Retourne true si un compte existe
	bool userExists(std::string name);

	// Obtenir le prochain User ID
	int getNextUserID();

	/// Ajouter le nouveau User a la base de donn�es
	void insertDatabase(const User& user) const;

	/// Mettre a jour les informations sur la base de donn�es
	void updateDatabase(const User& user) const;

	/// Change tous les mots de passes des utilisateurs
	void resetAllPasswords(std::string password);

private:

	/// Ins�rer un nouvel utilisateur dans la base de donn�es
	void insertUserDatabase(const User& user) const;

	/// Ins�rer les informations de statistique dans la base de donn�es
	void insertStatistiqueDatabase(const User& user) const;

	/// Mise a jour des informations utilisateur dans la base de donnes
	void updateUserDatabase(const User& user) const;

	/// Mise a jour des informations concernant les avatars d�bloqu�s
	void updateAvatarDatabase(const User& user) const;

	/// Mise a jour des informations concernant les map d�bloqu�s
	void updateMapDatabase(const User& user) const;

	/// Mise a jour des informations concernant les achievements d�bloqu�s
	void updateAchievementDatabase(const User& user) const;

	/// Ajouter les avatars gratuits au joueur
	void updateFreeAvatar(User& user) const;

	/// Mise a jour des informations concernant les statistiques de jeu
	void updateStatistiqueDatabase(const User& user) const;

	/// Identificateur unique des messages de conversation
	int userIndex_ = 0;

	/// Liste des utilisateurs cr��s
	std::map<std::string, User*> userList_;

	/// Liste des noms d'utilisateurs interdits
	std::vector<std::string> forbiddenUsernames_;
};

#endif //__SERVEUR_USERCONTROL_H__