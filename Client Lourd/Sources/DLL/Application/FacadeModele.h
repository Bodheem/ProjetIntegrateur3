//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @ingroup Application
//////////////////////////////////////////////////////////////////////////////

/**
*  @defgroup INF2990 INF2990
* Painball
*/

/**
*	@defgroup Noyau Noyau
*	@ingroup INF2990
*  Ce module contient le coeur de l'application.
*/

/** @defgroup Application Application
*	@ingroup Noyau
*/

#ifndef __APPLICATION_FACADEMODELE_H__
#define __APPLICATION_FACADEMODELE_H__

#include<WS2tcpip.h> //include  this header first
#include <windows.h>
#include <iostream>
#include <mutex>
#include "glm/glm.hpp"

#include "Utilitaire.h"
#include "../Global/GlobalesPartie.h"

namespace utilitaire{
	class BoiteEnvironnement;
}

class NoeudAbstrait;
class ArbreRenduINF2990;
class ConfigScene;
class ControleurLumieres;
class ControleurTexte;
class ControleurSon;

namespace vue 
{
   class Vue;
}

///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une facade) sur l'ensemble
///        du modele et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
/// @ingroup Application
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:

	/// Obtient l'instance unique de la classe.
	static FacadeModele* obtenirInstance();

	/// Libere l'instance unique de la classe.
	static void libererInstance();

	/// Prendre un lock sur le mutex
	void obtainSecureLock();

	/// Relacher le mutex
	void releaseSecureLock();

	/// Cree un contexte OpenGL et initialise celui-ci.
	void initialiserOpenGL(HWND hWnd);

	/// Libere le contexte OpenGL.
	void libererOpenGL();

	/// Affiche le contenu du modele.
	void afficher();

	/// Affiche la base du contenu du modele.
	void afficherBase() const;

	/// Anime la scene.
	void animer(float temps);

	/// Sauvegarde la derniere configuration valide et confirmee par l'usager
	void sauvegarderConfiguration(int config[14]) const;

	/// Obtenir les configurations du jeu
	int* obtenirConfiguration() const;

	/// Sauvegarder la derniere campagne jouee par l'usager
	void sauvegarderCampagne(char* nomFichier) const;

	/// Obtenir les informations de derniere campagne jouee par l'usager
	std::string obtenirDerniereCampagne() const;

	/// Obtenir le facteur de zoom applique
	double obtenirZoomCourant()  const;

	/// Appliquer le zoom initial
	bool appliquerZoomInitial() const;

	/// Obtenir la taille de la fenetre
	glm::ivec2 obtenirTailleFenetre() const;

	/// Assigne si oui ou non on utilise la caméra orbite
	void utiliserCameraOrbite(bool utiliseOrbite);

	/// Retourne si on est en mode caméra orbite ou non
	bool cameraEstOrbite() const;

	/// Dessiner le skybox
	void dessinerSkybox(double demiLargeur = 1000, bool vueOrtho = false, glm::dvec3 pointMilieu = { 0.0, 0.0, 0.0 }) const;

	/// Retourne la vue courante.
	inline vue::Vue* obtenirVue() const;

	/// Retourne l'arbre de rendu.
	inline const ArbreRenduINF2990* obtenirArbreRenduINF2990() const;

	/// Retourne l'arbre de rendu.
	inline ArbreRenduINF2990* obtenirArbreRenduINF2990();

	/// Retourner le controleur de texte
	ControleurTexte* obtenircontroleurTexte();

	/// Retourner le controleur de son
	ControleurSon* obtenirControleurSon();

	/// Pour transmettre les appels de lumiere du C# au controleur de Lumieres
	void setLight(int lum, bool state) const;

	/// Pour mettre le jeu en pause
	void setPause(bool pause);

	/// Get le bool pause
	bool getPause();

	/// Assigner la valeur de l'animation a tous les objets
	void assignerAnimer(bool animer);

	/// Cree une bille a la position et scale demande
	void creeBille(glm::dvec3 position, glm::dvec3 echelle, int colorShift = 0);

	/// Preare la creation de la bille (choisis le portail d'ou elle sera generee)
	bool preparerBille(int colorshift = 0);

	/// Retirer la bille de la zone de jeu
	void supprimerBille() const;

	/// Assigner une boite englobante a la table
	void setBoiteTable(utilitaire::BoiteEnglobante boiteTable);

	/// Obtenir la valeur maximale en x de la table
	double obtenirTableMaxX() const;

	/// Obtenir la valeur maximale en y de la table
	double obtenirTableMaxY() const;

	/// Obtenir la valeur minimale en x de la table
	double obtenirTableMinX() const;

	/// Obtenir la valeur minimale en y de la table
	double obtenirTableMinY() const;

	/// Obtenir la valeur minimale en z de la table
	double obtenirTableMinZ() const;

	/// Assigne les valeurs de debug
	void setDebug(bool valeurSpotLight = false) const;

	/// Imprime le temps courant
	static void printCurrentTime();

	/// Obtenir si oui ou non on doit animer
	bool obtenirAnimation() const;

	/// Obtenir les informations de points et collisions
	GlobalesPartie* obtenirGlobalesPartie();

	/// Obtenir le centre de masse en X
	static int obtenirCentreMasseX();

	/// Obtenir le centre de masse en Y
	static int obtenirCentreMasseY();

	/// Obtenir la difficulte du nom de la carte passe en parametre
	static int obtenirDifficulte(char* nomFichier);

	/// Obtenir les touches et les options de configuration
	int	obtenirTouchePGJ1() const;
	int  obtenirTouchePGJ2() const;
	int  obtenirTouchePDJ1() const;
	int  obtenirTouchePDJ2() const;
	int  obtenirToucheRessort() const;
	int  obtenirNombreDeBilles() const;
	int  obtenirModeDoubleBille() const;
	int  obtenirModeForceRebond() const;
	int  obtenirAffichageGlobal() const;

	/// Bloquer ou débloquer l'affichage de debug global
	void bloquerAffichageGlobal(int active) const;

	/// Savoir si l'arbre est vide ou vient de charger une zone de jeu
	bool obtenirSiArbreVide() const;

	/// Assigner pour savoir si l'arbre est vide ou vient de charger une zone de jeu
	void assignerSiArbreVide(bool isLoaded);

private:

	/// Constructeur.
	FacadeModele();

	/// Destructeur.
	~FacadeModele();

	/// Constructeur copie desactive.
	FacadeModele(const FacadeModele&) = delete;

	/// Operateur d'assignation desactive.
	FacadeModele& operator =(const FacadeModele&) = delete;

	/// Pointeur vers l'instance unique de la classe.
	static FacadeModele* instance_;

	/// Poignee ("handle") vers la fenetre ou l'affichage se fait.
	HWND  hWnd_{ nullptr };

	/// Poignee ("handle") vers le contexte OpenGL.
	HGLRC hGLRC_{ nullptr };

	/// Poignee ("handle") vers le "device context"
	HDC   hDC_{ nullptr };

	/// Pour l'affichage du texte directement par l'OpenGL
	ControleurTexte* controleurTexte_{ nullptr };

	/// Pour la gestion des sons
	ControleurSon* controleurSon_{ nullptr };

	/// Pour la gestion des lumières
	ControleurLumieres* controleurLumieres_{ nullptr };

	/// Vue courante de la scene.
	vue::Vue* vue_{ nullptr };	

	/// Arbre de rendu contenant les differents objets de la scene.
	ArbreRenduINF2990* arbre_{ nullptr };	

	/// Savoir si l'arbre a été chargé ou a été vidé
	bool isLoaded_;

	/// Contient les configurations de partie comme les touches et les options usagers
	ConfigScene* configuration_{ nullptr };

	/// Pour l'état de la vue
	bool vueEstOrbite_{ false };

	/// Pour la skybox de l'environnement OpenGL
	utilitaire::BoiteEnvironnement* skybox_{ nullptr };

	/// Boite englobante de la table
	utilitaire::BoiteEnglobante boiteTable_;

	/// Mutex pour la gestion de la concurrence
	std::mutex mutex_;

	/// Savoir si on est en mode pause
	bool pause_;

	/// Savoir si on doit animer les objets de la scène
	bool animer_{ false };
				
	/// Informations des points de partie
	GlobalesPartie globalesPartie_;
};


////////////////////////////////////////////////////////////////////////
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
/// @brief Cette fonction retourne la vue qui est presentement utilisee pour voir la scene.
/// @return La vue courante.
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue() const
{
   return vue_;
}


////////////////////////////////////////////////////////////////////////
/// @fn inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
/// @brief Cette fonction retourne l'arbre de rendu de la scene (version constante
///		   de la fonction).
/// @return L'arbre de rendu de la scene.
////////////////////////////////////////////////////////////////////////
inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_;
}


////////////////////////////////////////////////////////////////////////
/// @fn inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
/// @brief Cette fonction retourne l'arbre de rendu de la scene (version non constante
///		   de la fonction).
/// @return L'arbre de rendu de la scene.
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}


#endif // __APPLICATION_FACADEMODELE_H__
