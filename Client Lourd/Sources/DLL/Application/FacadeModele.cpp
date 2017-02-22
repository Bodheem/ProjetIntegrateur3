///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @ingroup Application
///////////////////////////////////////////////////////////////////////////////

// Commentaire Doxygen mis sur la premiere page de la documentation Doxygen.
/**

@mainpage Projet integrateur de deuxieme annee -- INF2990

PAINBALL
<BR>
<BR>
Auteurs:<BR>
Aymen Djellal <BR>
Emilio Rivera <BR>
Kim Piche <BR>
Nikolay Radoev <BR>
Philippe Carpin <BR>
Samuel Millette <BR>
Yonni Chen <BR>

*/
#include<WS2tcpip.h> //include  this header first
#include <windows.h>
#include <cassert>
#include <iostream>

#include "FreeImage.h"
#include "FacadeModele.h"
#include "FacadeJeu.h"
#include "FacadeReseau.h"

#include "../Text/ControleurTexte.h"
#include "../Sound/ControleurSon.h"
#include "../Configuration/ConfigScene.h"
#include "../Visiteurs/VisiteurSelection.h"
#include "../Visiteurs/VisiteurCentreDeMasse.h"
#include "../Visiteurs/VisiteurLimitesSelection.h"
#include "../Visiteurs/VisiteurDebug.h"
#include "../Compte/Joueur.h"

#include "../Eclairage/ControleurNuanceurs.h"
#include "../Eclairage/ControleurLumieres.h"
#include "../../../Commun/Utilitaire/OpenGL/BoiteEnvironnement.h"

#include "VueOrtho.h"
#include "VuePerspective.h"
#include "Projection.h"
#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"

#include "tinyxml2.h"
#include "glm/gtc/type_ptr.hpp"


/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_{ nullptr };


////////////////////////////////////////////////////////////////////////
/// @fn FacadeModele::FacadeModele()
/// @brief Le constructeur (protected) de FacadeModele. Sert a initialiser
///		   les coins de la boite de la table; le reste de la classe est initialisee
///		   par defaut.
/// @return Une instance de la classe
////////////////////////////////////////////////////////////////////////
FacadeModele::FacadeModele()
{
	boiteTable_.coinMax = { 0, 0, 0 };
	boiteTable_.coinMin = { 0, 0, 0 };

	pause_ = false;
	isLoaded_ = false;
}


////////////////////////////////////////////////////////////////////////
/// @fn FacadeModele* FacadeModele::obtenirInstance()
/// @brief Cette fonction retourne un pointeur vers l'instance unique de la
///		   classe.  Si cette instance n'a pas ete creee, elle la cree.  Cette
///		   creation n'est toutefois pas necessairement "thread-safe", car
///		   aucun verrou n'est pris entre le test pour savoir si l'instance
///		   existe et le moment de sa creation.
/// @param console : True si on utilise la console a Aymen.
/// @return Un pointeur vers l'instance unique de cette classe.
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new FacadeModele();

		instance_->configuration_ = new ConfigScene();
		instance_->controleurLumieres_ = new ControleurLumieres();
		instance_->arbre_ = new ArbreRenduINF2990();
	}
	return instance_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::libererInstance()
/// @brief Cette fonction libere l'instance unique de cette classe.
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererInstance()
{
	delete instance_;
	instance_ = nullptr;
}


////////////////////////////////////////////////////////////////////////
/// @fn FacadeModele::~FacadeModele()
/// @brief Ce destructeur libere les objets du modele.
/// @return Aucune (destructeur).
////////////////////////////////////////////////////////////////////////
FacadeModele::~FacadeModele()
{
	delete arbre_;
	delete vue_;
	delete configuration_;
	delete controleurLumieres_;
	delete controleurTexte_;
	delete controleurSon_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::initialiserOpenGL(HWND hWnd)
/// @brief Cette fonction permet d'initialiser le contexte OpenGL.  Elle cree
///		   un contexte OpenGL sur la fenetre passee en parametre, initialise
///		   FreeImage (utilisee par le chargeur de modeles) et assigne des 
///		   parametres du contexte OpenGL.
/// @param[in] hWnd : La poignee ("handle") vers la fenetre a utiliser.
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	hWnd_ = hWnd;
	bool succes{ aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_) };
	if (succes == false)
		assert(succes && "Le contexte OpenGL n'a pu etre cree.");

	// Initialisation des extensions de OpenGL
	glewInit();

	// FreeImage, utilisee par le chargeur, doit etre initialisee
	FreeImage_Initialise();

	// La couleur de fond
	glClearColor(0.7843f, 0.7843f, 0.7843f, 0.0f);

	// Initialiser le stencil a 0.
	glClearStencil(0);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP,GL_KEEP,  GL_REPLACE);

	// Les lumieres
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	/// Pour normaliser les normales dans le cas d'utilisation de glScale[fd]
	glEnable(GL_NORMALIZE);

	/// Initialisation des lumieres et du programme de nuanceurs.
	ControleurNuanceurs::obtenirInstance()->initialiser();
	controleurLumieres_->initialiserLumieres();

	/// Activation de GL_LIGHT0 pour le mode sans nuanceurs.
	glEnable(GL_LIGHT0);

	// Qualite
	glShadeModel(GL_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Profondeur
	glEnable(GL_DEPTH_TEST);

	// Le cull face
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	//	BoiteEnvironnement::BoiteEnvironnement(
	//		const std::string& fichierXpos, const std::string& fichierXneg,
	//		const std::string& fichierYpos, const std::string& fichierYneg,
	//		const std::string& fichierZpos, const std::string& fichierZneg
	//		)
	skybox_ = new utilitaire::BoiteEnvironnement(
		//"/skybox/left.jpg",
		//"/skybox/right.jpg",
		//"/skybox/top.jpg",
		//"/skybox/bottom.jpg",
		//"/skybox/front.jpg",
		//"/skybox/back.jpg"
		// "media/skybox/lf.jpg",
		// "media/skybox/rt.jpg",
		// "media/skybox/up.jpg",
		// "media/skybox/dn.jpg",
		// "media/skybox/ft.jpg",
		// "media/skybox/bk.jpg"
		// "media/skybox/left.jpg",	// << RIGHT
		// "media/skybox/right.jpg",	// << LEFT
		// "media/skybox/top.jpg",		// << BACK
		// "media/skybox/bottom.jpg",	// << FRONT
		// "media/skybox/front.jpg",	// << BOTTOM 
		// "media/skybox/back.jpg"		// << TOP
#if(0)
		"media/skybox/right.jpg",	// << RIGHT
		"media/skybox/left.jpg",	// << LEFT
		"media/skybox/back.jpg",		// << BACK
		"media/skybox/front.jpg",	// << FRONT
		"media/skybox/bottom.jpg",	// << BOTTOM 
		"media/skybox/top.jpg"		// << TOP
#else
		"media/skybox/rt.jpg",
		"media/skybox/lf.jpg",
		"media/skybox/bk.jpg",
		"media/skybox/ft.jpg",
		"media/skybox/dn.jpg",
		"media/skybox/up.jpg"
#endif
		);

	/*Creer une camera ortho*/
	vue_ = new vue::VueOrtho{
		vue::Camera{
			glm::dvec3(0, 0, 200), glm::dvec3(0, 0, 0),
			glm::dvec3(0, 1, 0), glm::dvec3(0, 1, 0),
			0.0, 0.0 },
			vue::ProjectionOrtho{
				0, 500, 0, 500,
				1, 5000, 50, 3000, 1.25,
				double(coinGaucheTableX), double(coinGaucheTableY),
				double(coinDroitTableX), double(coinDroitTableY) }
	};
	appliquerZoomInitial();
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::libererOpenGL()
/// @brief Cette fonction libere le contexte OpenGL et desinitialise FreeImage.
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	obtainSecureLock();

	arbre_->vider();
	isLoaded_ = false;

	controleurTexte_->afficherTextes(false);
	arbre_->libererUsines();
	
	utilitaire::CompteurAffichage::libererInstance();
	ControleurNuanceurs::libererInstance();
	bool succes{ aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_) };
	if (succes == false)
		assert(succes && "Le contexte OpenGL n'a pu etre detruit.");

	FreeImage_DeInitialise();

	releaseSecureLock();
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::afficher() const
/// @brief Cette fonction affiche le contenu de la scene.
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher()
{
	obtainSecureLock();

	// Efface l'ancien rendu
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	// Ne devrait pas etre necessaire
	vue_->appliquerProjection();

	// Positionne la camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ControleurNuanceurs::obtenirInstance()->activer();
	ControleurNuanceurs::obtenirInstance()->assignerSkybox(1);
	vue_->appliquerCamera();
	ControleurNuanceurs::obtenirInstance()->assignerSkybox(0);
	ControleurNuanceurs::obtenirInstance()->desactiver();
	// Afficher la scene
	afficherBase();

	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	if (pause_) 
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Black Background

		// noircir l'ecran
		glDrawBuffer(GL_BACK);
		glClear(GL_DEPTH_BUFFER_BIT);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0F, 0.0F, 0.0F, 0.7F);
		glRectd(-7000, -7000, 7000, 7000);

		glEnable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}
	else 
	{
		glClearColor(0.7843f, 0.7843f, 0.7843f, 0.0f);
	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	// echange les tampons pour que le resultat du rendu soit visible.
	::SwapBuffers(hDC_);

	releaseSecureLock();
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::afficherBase() const
/// @remark Cette fonction affiche la base du contenu de la scene, c'est-a-dire
/// \remark qu'elle met en place l'eclairage et affiche les objets.
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	// Positionner la lumiere.
	glm::vec4 position{ 0, 0, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(position));

	// Afficher la scene.
	controleurLumieres_->trackerLesBilles(static_cast<NoeudTable*>(arbre_->chercher(0)));
	controleurLumieres_->definirLumieres();
	ControleurNuanceurs::obtenirInstance()->activer();

	arbre_->afficher();
	ControleurNuanceurs::obtenirInstance()->desactiver();

	// On affiche le texte ici
	if (controleurTexte_ != nullptr)
		controleurTexte_->refreshAffichage();

	// fuck that shit... si je met cette ligne la dans le .h ca compile plus...
	// TODO bouger shit dans l'API et le C#, pis juste appeler afficherTexte();
	/* //Exemple d'affichage
	static bool oneTime = true;
	if(oneTime){
		char* myText;
		char* myFont;

		// le Texte a Ecrire
		myText = "Hello World";
		myFont = "arial.ttf"; // Ou encore Bloodthirsty.ttf
		// On specifie la font
		controleurTexte_->creeTexte(myText, myFont);

		// On specifie la taille (en 1/72 de pouce)
		controleurTexte_->resize(myText, 35);

		// On specifie une couleur RGB
		controleurTexte_->changerCouleur(myText, 0.5, 1, 1);
		// Ou encore
		controleurTexte_->changerCouleur(myText, COLOR_salmon);

		// On specifie la position
		controleurTexte_->repositionner(myText, 1, 1);

		// Voici un autre exemple
		myText = "Well This is easy";
		controleurTexte_->creeTexte(myText, myFont);
		controleurTexte_->resize(myText, 24);
		controleurTexte_->changerCouleur(myText, COLOR_red);
		controleurTexte_->repositionner(myText, 1, 1);

		// Voici un autre exemple
		myText = "Petite ligne 1 1";
		controleurTexte_->creeTexte(myText, myFont);
		controleurTexte_->resize(myText, 24);
		controleurTexte_->changerCouleur(myText, COLOR_blue);
		controleurTexte_->repositionner(myText, 1, 1);

		// Voici un autre exemple
		myText = "Random 0 1";
		controleurTexte_->creeTexte(myText, myFont);
		controleurTexte_->resize(myText, 24);
		controleurTexte_->changerCouleur(myText, COLOR_blue);
		controleurTexte_->repositionner(myText, 0, 1);

		// Voici un autre exemple
		myText = "2e Random 0 1";
		controleurTexte_->creeTexte(myText, myFont);
		controleurTexte_->resize(myText, 24);
		controleurTexte_->changerCouleur(myText, COLOR_black);
		controleurTexte_->repositionner(myText, 0, 1);

		// Voici un autre exemple
		myText = "3e shit weird ici en  0 1";
		controleurTexte_->creeTexte(myText, myFont);
		controleurTexte_->resize(myText, 24);
		controleurTexte_->changerCouleur(myText, COLOR_alice_blue);
		controleurTexte_->repositionner(myText, 0, 1);

		// Voici un autre exemple
		myText = "Test 1 0";
		controleurTexte_->creeTexte(myText, myFont);
		controleurTexte_->resize(myText, 42);
		controleurTexte_->changerCouleur(myText, COLOR_cadet_blue);
		controleurTexte_->repositionner(myText, 1, 0);

		// Voici un autre exemple
		myText = "Test --2-- 1 0";
		controleurTexte_->creeTexte(myText, myFont);
		controleurTexte_->resize(myText, 24);
		controleurTexte_->changerCouleur(myText, COLOR_magenta_fuchsia);
		controleurTexte_->repositionner(myText, 1, 0);

		// Voici un autre exemple
		myText = "Test --3-- 1 0";
		controleurTexte_->creeTexte(myText, myFont);
		controleurTexte_->resize(myText, 24);
		controleurTexte_->changerCouleur(myText, COLOR_Magenta_Fuchsia);
		controleurTexte_->repositionner(myText, 1, 0);

		// Voici un autre exemple
		myText = "Je sais pas pk je fais ca";
		controleurTexte_->creeTexte(myText, myFont);
		controleurTexte_->resize(myText, 24);
		controleurTexte_->changerCouleur(myText, COLOR_khaki);
		controleurTexte_->repositionner(myText, 0, 0);

		// Voici un autre exemple
		myText = "C'est genre meme pas beau";
		controleurTexte_->creeTexte(myText, myFont);
		controleurTexte_->resize(myText, 21);
		controleurTexte_->changerCouleur(myText, COLOR_azure);
		controleurTexte_->repositionner(myText, 0, 0);

		// Voici un autre exemple
		myText = "C'est probablement useless en plus";
		controleurTexte_->creeTexte(myText, myFont);
		controleurTexte_->resize(myText, 24);
		controleurTexte_->changerCouleur(myText, COLOR_beige);
		controleurTexte_->repositionner(myText, 0, 0);

		//oneTime = false;
	}
	*/
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::animer(float temps)
/// @remark Cette fonction effectue les differents calculs d'animations
/// \remark necessaires pour le mode jeu, tel que les differents calculs de
/// \remark physique du jeu.
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
/// @return Aucune.
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	obtainSecureLock();

	// Changer la vitesse des billes en fonction des collisions:
	// Si je commente la ligne suivante, rentrer et sortir du mode test fait crasher, 
	// il manque un appel pour quand on sort du mode test.
	FacadeJeu::obtenirInstance()->mettreAJourListeBillesEtNoeuds();

	/// Comportement du joueur virtuel
	FacadeJeu::obtenirInstance()->jouerAI(temps);

	/// Faire la somme des forces
	FacadeJeu::obtenirInstance()->updateForcesExternes();

	/// Traiter les collisions entre objets
	FacadeJeu::obtenirInstance()->traiterCollisions(temps);

	// Mettre a jour les billes
	if(FacadeReseau::obtenirInstance()->obtenirCompte()->isOnlineAccount() && FacadeReseau::obtenirInstance()->obtenirNumeroJoueur() == 1)
	{
		/// Mettre a jour le nombre de billes en fonction du nombre d'utilisateurs dans la room
		int nombreJoueur = FacadeReseau::obtenirInstance()->obtenirNombreJoueur();

		for (int i = 0; i < nombreJoueur; ++i)
			globalesPartie_.updateBilles(i);
	}
	else
	{
		// Ne mettre à jour que la bille du joueur 1
		globalesPartie_.updateBilles();
	}

	// Mettre a jour l'affichage du bonus/malus
	globalesPartie_.updateAffichageBonus();
	globalesPartie_.updateAffichageMalus();


	// Mise a jour des objets.
	arbre_->animer(temps);

	// Mise a jour de la vue.
	vue_->animer(temps);

	releaseSecureLock();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::sauvegarderConfiguration(int config[13])
/// @brief Sauvegarde des configurations de la partie.
/// @param[in] config : Valeurs de la configuration
/// @return True si la duplication est hors table
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::sauvegarderConfiguration(int config[14]) const
{
	configuration_->modifierConfiguration(config);
	configuration_->sauvegarderConfiguration();
	setDebug();

	// Activer le joueur virtuel intelligent
	if (config[13] == 1)
	{
		FacadeJeu::obtenirInstance()->initializeLevelAI("INTELLIGENT");
	}
	else if (config[13] == 0)
	{
		FacadeJeu::obtenirInstance()->initializeLevelAI("STUPIDE");
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @fn int* FacadeModele::obtenirConfiguration()
/// @brief Retourne la configuration de la partie.
/// @return Les valeurs de configuration.
///////////////////////////////////////////////////////////////////////////////
int* FacadeModele::obtenirConfiguration() const
{
	return configuration_->obtenirConfiguration();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn double FacadeModele::obtenirZoomCourant() const
/// @brief Obtient la valeur deu zoom applique.
/// @return La valeur du zoom courant
/// @remark : la comparaison est faite entre les dimensions de la cloture et celles de la fenetre courante
///////////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirZoomCourant() const
{
	double zoom = -1;
	glm::ivec2 dimClot = vue_->obtenirProjection().obtenirDimensionCloture();
	glm::ivec2 dimFenV = vue_->obtenirProjection().obtenirDimensionFenetreVirtuelle();
	double surfaceFen = dimFenV.x * dimFenV.y;
	if (surfaceFen != 0.0)
		zoom = (dimClot.x * dimClot.y) / surfaceFen;
	return zoom;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn bool FacadeModele::appliquerZoomInitial()
/// @brief Applique le zoom initial.
/// @return Le y du centre de masse
///////////////////////////////////////////////////////////////////////////////
bool FacadeModele::appliquerZoomInitial() const
{
	bool applique = false;
	if (obtenirInstance() != nullptr && vue_->obtenirProjection().estPerspective() == false)
	{
		vue_->zoomerInElastique(glm::dvec2(coinGaucheTableX, coinGaucheTableY), glm::ivec2(coinDroitTableX, coinDroitTableY));
		applique = true;
	}
	return applique;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn double FacadeModele::obtenirTailleFenetre();
/// @brief Obtient la taille de la fenetre courante
/// @return un vecteur de 2 int qui sont la taille de la fenetre courante
///////////////////////////////////////////////////////////////////////////////
glm::ivec2 FacadeModele::obtenirTailleFenetre() const
{
	return vue_->obtenirProjection().obtenirDimensionCloture();
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::utiliserCameraOrbite(bool utiliseOrbite)
/// @brief Cette fonction change la vision pour refleter une camera orbite ou non
/// @param[in] utiliseOrbite : Indique s'il faut utiliser une camera orbite ou non
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void FacadeModele::utiliserCameraOrbite(bool utiliseOrbite)
{
	// Si le mode desire n'est pas celui qui est deja presentement utilise
	if (utiliseOrbite != vueEstOrbite_)
	{
		/*Sauvegarde des mesures de la clôture */
		double clotMinX, clotMaxX, clotMinY, clotMaxY;
		vue_->obtenirProjection().obtenirCoordonneesCloture(clotMinX, clotMaxX, clotMinY, clotMaxY);

		double ratio = (clotMaxX - clotMinX) / (clotMaxY - clotMinY);

		delete vue_;

		if (utiliseOrbite)
		{
			vue_ = new vue::VuePerspective{
				vue::Camera{
					glm::dvec3((coinGaucheTableX + coinDroitTableX) / 2.0,
					(coinGaucheTableY + coinDroitTableY) / 2.0,
					289),
					glm::dvec3((coinGaucheTableX + coinDroitTableX) / 2.0,
					(coinGaucheTableY + coinDroitTableY) / 2.0,
					100), /* Le point vise*/
					glm::dvec3(0, 1, 0), glm::dvec3(0, 1, 0),
					0.0, 0.0 },
					vue::ProjectionPerspective{
						clotMinX, clotMaxX, clotMinY, clotMaxY,
						10.0, 2000, /* La valeur minimale et maximale en Z dans le volume de visualisation*/
						50, 1000,   /* La valeur minimal et maximale que l'on peut parcourir dans le jeu*/
						1.10,       /* L'increment de zoom*/
						ratio,      /* Le rapport d'aspect precedent*/
						60.0,       /* L'angle de vision */
					}
			};
			vue_->obtenirCamera().assignerPhi(utilitaire::DEG_TO_RAD(90.0));

			std::cout << "La vue est passee en orbite \n";
		}
		else
		{
			/*Creer une camera ortho*/
			vue_ = new vue::VueOrtho{
				vue::Camera{
					glm::dvec3(0, 0, 200), glm::dvec3(0, 0, 0),
					glm::dvec3(0, 1, 0), glm::dvec3(0, 1, 0),
					0.0, 0.0 },
					vue::ProjectionOrtho{
						clotMinX, clotMaxX, clotMinY, clotMaxY,
						1, 5000, 50, 3000, 1.25,
						double(coinGaucheTableX), double(coinGaucheTableY),
						double(coinDroitTableX), double(coinDroitTableY) }
			};
			appliquerZoomInitial();
			std::cout << "La vue est passee en orthographique \n";
		}

		// On change l'attribut pour refleter la vue courante
		vueEstOrbite_ = utiliseOrbite;
	}
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::cameraEstOrbite() const
/// @brief Indique si le mode de camera est orbite ou non
/// @return Si oui ou non la camera est en mode orbite
////////////////////////////////////////////////////////////////////////
bool FacadeModele::cameraEstOrbite() const
{
	return vueEstOrbite_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::dessinerSkybox() const
/// @brief Dessine la skybox
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void FacadeModele::dessinerSkybox(double demiLargeur, bool vueOrtho, glm::dvec3 pointMilieu) const
{
	if (!vueOrtho)
		skybox_->afficher(glm::dvec3{ static_cast<double>((coinDroitTableX + coinGaucheTableX) / 2.0),
							static_cast<double>((coinDroitTableY + coinGaucheTableY) / 2.0),
							0.0 },
							demiLargeur);
	else
		skybox_->afficher(pointMilieu, demiLargeur);
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::obtenircontroleurTexte()
/// @remark Cette fonction retourne la classe de controle du texte.
/// @return Le controleur de texte.
////////////////////////////////////////////////////////////////////////
ControleurTexte* FacadeModele::obtenircontroleurTexte()
{
	if (controleurTexte_ == nullptr)
		controleurTexte_ = new ControleurTexte();

	return controleurTexte_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::obtenirControleurSon()
/// @remark Cette fonction retourne la classe de controle du son.
/// @return Le controleur de son.
////////////////////////////////////////////////////////////////////////
ControleurSon* FacadeModele::obtenirControleurSon()
{
	if (controleurSon_ == nullptr)
		controleurSon_ = new ControleurSon();

	return controleurSon_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::setLight(int lum, bool state)
/// @remark Assigne un effet de lumière sur la bille
/// @return Aucun
////////////////////////////////////////////////////////////////////////
void FacadeModele::setLight(int lum, bool state) const
{
	switch (lum)
	{
		case 0:
			(state ? controleurLumieres_->activerAmbiante() : controleurLumieres_->desactiverAmbiante());
			break;
		case 1:
			(state ? controleurLumieres_->activerDirectionnelle() : controleurLumieres_->desactiverDirectionnelle());
			break;
		case 2:
			(state ? controleurLumieres_->activerSpot() : controleurLumieres_->desactiverSpot());
			break;
	}
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::setPause(bool pause)
/// @brief Parcours l'arbre et met les objets en mode pause.
/// @param[in]  pause : Etat du mode pause
/// @return Aucun
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::setPause(bool pause)
{	
	this->obtenirControleurSon()->pauseGlobal(pause);
	//ne pas afficher le generateur en mode pause
	NoeudAbstrait* table = arbre_->chercher(0);
	for (unsigned int i = 0; i < table->obtenirNombreEnfants(); i++)
		if (table->chercher(i)->obtenirType() == "generateurbille")
			table->chercher(i)->assignerAffiche(!pause);

	pause_ = pause;

	// remettre l'affichage a la normale
	if (!pause)
	{
		glDisable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glFlush();
		glDrawBuffer(GL_BACK);
	}
}

// Retourne l'état du mode pause de la partie en cours
bool FacadeModele::getPause()
{
	return pause_;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::obtainSecureLock()
/// @brief
/// @return Aucun
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::obtainSecureLock()
{
	mutex_.lock();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::releaseSecureLock()
/// @brief 
/// @return Aucun
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::releaseSecureLock()
{
	mutex_.unlock();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::setDebug(bool valeurSpotLight)
/// @param[in]  valeurSpotLight : valeur du mode debug pour le spotLight
/// @brief Met la valeur de debug de spotLight
/// @return Aucun
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::setDebug(bool valeurSpotLight) const
{
	if (obtenirInstance()->obtenirArbreRenduINF2990() == nullptr)
		return;

	bool valeurDebugBille = false;
	bool valeurDebugPortail = false;
	if (obtenirConfiguration()[12] == false)
	{
		valeurSpotLight = false;
	}
	else
	{
		valeurDebugBille = obtenirConfiguration()[9] == 1 ? true : false;
		valeurDebugPortail = obtenirConfiguration()[11] == 1 ? true : false;
	}

	VisiteurDebug* visiteur = new VisiteurDebug(valeurDebugBille, valeurDebugPortail, valeurSpotLight);
	arbre_->accepterVisiteur(visiteur);
	delete visiteur;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn int FacadeModele::obtenirCentreMasseX()
/// @brief Obtient le x du centre de masse des objets selectionnes
/// @return La composante en x du centre de masse
/// @remark Perte de precision lors de la convertion du centre de masse (double) en int.
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirCentreMasseX()
{
	int centreMasseX = 0;
	VisiteurCentreDeMasse* visiteur = new VisiteurCentreDeMasse();
	obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur);
	centreMasseX = (int) visiteur->obtenirCentreDeMasse().x;
	delete visiteur;
	return centreMasseX;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn int FacadeModele::obtenirCentreMasseY()
/// @brief Obtient le y du centre de masse des objets selectionnes
/// @return La composante en y du centre de masse
/// @remark Perte de precision lors de la convertion du centre de masse (double) en int.
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirCentreMasseY()
{
	int centreMasseY = 0;
	VisiteurCentreDeMasse* visiteur = new VisiteurCentreDeMasse();
	obtenirInstance()->obtenirArbreRenduINF2990()->accepterVisiteur(visiteur);
	centreMasseY = (int) visiteur->obtenirCentreDeMasse().y;
	return centreMasseY;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn int	FacadeModele::obtenirTouchePGJ1() const
/// @brief Retourne la touche associee a Palette Gauche Joueur 1.
/// @return La touche PGJ1.
///////////////////////////////////////////////////////////////////////////////
int	FacadeModele::obtenirTouchePGJ1() const{ 
	return configuration_->obtenirRaccourciPGJ1(); 
}


///////////////////////////////////////////////////////////////////////////////
/// @fn int	FacadeModele::obtenirTouchePGJ2() const
/// @brief Retourne la touche associee a Palette Gauche Joueur 2.
/// @return La touche PGJ2.
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirTouchePGJ2() const
{ 
	return configuration_->obtenirRaccourciPGJ2(); 
}


///////////////////////////////////////////////////////////////////////////////
/// @fn int	FacadeModele::obtenirTouchePDJ1() const
/// @brief Retourne la touche associee a Palette Droite Joueur 1.
/// @return La touche PDJ1.
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirTouchePDJ1() const
{ 
	return configuration_->obtenirRaccourciPDJ1(); 
}


///////////////////////////////////////////////////////////////////////////////
/// @fn int	FacadeModele::obtenirTouchePDJ2() const
/// @brief Retourne la touche associee a Palette Droite Joueur 2.
/// @return La touche PDJ2.
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirTouchePDJ2() const
{ 
	return configuration_->obtenirRaccourciPDJ2(); 
}


///////////////////////////////////////////////////////////////////////////////
/// @fn int	FacadeModele::obtenirToucheRessort() const
/// @brief Retourne la touche associee a l'activation du ressort.
/// @return La touche d'acitvation du ressort.
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirToucheRessort() const
{ 
	return configuration_->obtenirRaccourciRessort(); 
}


///////////////////////////////////////////////////////////////////////////////
/// @fn int	FacadeModele::obtenirAffichageGlobal() const
/// @brief Retourne le mode d'affichage global.
/// @return 1 si l'affichage galobal est active, 0 sinon.
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirAffichageGlobal() const
{ 
	return configuration_->obtenirAffichageGlobal(); 
}


///////////////////////////////////////////////////////////////////////////////
/// @fn int	FacadeModele::obtenirNombreDeBilles() const
/// @brief Retourne le nombre de billes.
/// @return Le nombre de billes.
///////////////////////////////////////////////////////////////////////////////
int	FacadeModele::obtenirNombreDeBilles() const
{ 
	return configuration_->obtenirNombreBilles(); 
}


///////////////////////////////////////////////////////////////////////////////
/// @fn int	FacadeModele::obtenirModeDoubleBille() const
/// @brief Le mode double bille.
/// @return 1 si le mode double bille est active, 0 sinon.
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirModeDoubleBille() const
{ 
	return configuration_->obtenirModeDoubleBille(); 
}


///////////////////////////////////////////////////////////////////////////////
/// @fn int	FacadeModele::obtenirModeForceRebond() const
/// @brief Le mode avec force dans les rebonds.
/// @return 1 si le mode est active, 0 sinon.
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirModeForceRebond() const
{ 
	return configuration_->obtenirModeForceRebond(); 
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::bloquerAffichageGlobal(int active)
/// @brief Active ou bloque l'affichage global.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::bloquerAffichageGlobal(int active) const
{
	configuration_->bloquerAffichageGlobal(active);
}


///////////////////////////////////////////////////////////////////////////////
/// @fn int FacadeModele::obtenirDifficulte(char* nomFichier)
/// @brief Retourne le niveau de difficulte de la zone de jeu.
/// @param[in] nomFichier : Le nom du fichier ou se trouve la zone.
/// @return Le niveau de difficulte.
///////////////////////////////////////////////////////////////////////////////
int FacadeModele::obtenirDifficulte(char* nomFichier)
{
	int niveau;
	tinyxml2::XMLDocument* fichierXML = new tinyxml2::XMLDocument();
	fichierXML->LoadFile(nomFichier);

	tinyxml2::XMLElement* root = fichierXML->FirstChildElement("root");
	tinyxml2::XMLElement* elementPropriete = root->FirstChildElement("Proprietes");
	tinyxml2::XMLElement* element = elementPropriete->LastChildElement("Difficulte");
	niveau = element->FirstAttribute()->IntValue();

	delete fichierXML;
	return niveau;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::sauvegarderCampagne(char* nomMap)
/// @param[in] nomMap : Le nom de la zone de jeu.
/// @brief Sauvegarde la zone de jeu dans la compagne en cours.
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::sauvegarderCampagne(char* nomMap) const
{
	configuration_->modifierCampagne(nomMap);
	configuration_->sauvegarderCampagne();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn std::string FacadeModele::obtenirDerniereCampagne()
/// @brief Retourne la derniere campagne choisie.
/// @return Le niveau de difficulte.
///////////////////////////////////////////////////////////////////////////////
std::string FacadeModele::obtenirDerniereCampagne() const
{
	return configuration_->obtenirCampagne();
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::supprimerBille()
/// @brief Supprime la bille sur la zone. 
/// @return Aucune.
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::supprimerBille() const
{
	arbre_->effacer(arbre_->chercher("bille"));
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::assignerAnimer(bool animer)
/// @param[in]  animer : la valeur de animer a assigner.
/// @param[in]  noeud : la noeud a animer
/// @return Aucune.
/// @remark : Assigner la valeur animer a un noeud et ses enfants
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerAnimer(bool animer)
{
	animer_ = animer;
	arbre_->assignerAnimer(animer_);
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::creeBille(glm::dvec3 position, glm::dvec3 echelle)
/// @brief Cette fonction genere une bille a la position voulue (avec l'echele voulue)
/// @param[in]  position : position de la bille generee
/// @param[in]  echelle : scale de la bille
/// @return Aucun.
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::creeBille(glm::dvec3 position, glm::dvec3 echelle, int colorShift)
{
	NoeudAbstrait* objet = arbre_->creerNoeud("bille");
	objet->assignerPositionRelative(position);
	objet->assignerEchelle(echelle);
	objet->setColorShift(colorShift);

	// Garder un numero unique pour la bille 
	objet->assignerNumeroUnique(GlobalesPartie::compteurNumeroBille);

	//HH:MM:SS:mmm – Nouvelle bille : x: POSX y: POSY
	// http://brian.pontarelli.com/2009/01/05/getting-the-current-system-time-in-milliseconds-with-c/
	if (obtenirConfiguration()[8] && obtenirConfiguration()[12]) 
	{
		printCurrentTime();
		std::cout << std::fixed << std::setprecision(2);
		std::cout << " - Nouvelle bille : x: " << objet->obtenirPositionRelative().x << " y: " << objet->obtenirPositionRelative().y << std::endl;;
	}

	arbre_->getEnfant(0)->ajouter(objet);
	FacadeJeu::obtenirInstance()->mettreAJourListeBillesEtNoeuds();
	setDebug();

	// Incrémenter le compteur pour la prochaine génération de bille
	GlobalesPartie::compteurNumeroBille++;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn bool FacadeModele::preparerBille()
/// @brief Cette fonction prepare la creation d'une bille
/// @return Reussite ou Echec.
///////////////////////////////////////////////////////////////////////////////
bool FacadeModele::preparerBille(int colorshift)
{
	std::vector<int> generateurs;
	int i = 0;
	int nbElements = arbre_->getEnfant(0)->obtenirNombreEnfants();
	NoeudAbstrait* noeudTable = arbre_->getEnfant(0);
	for (i = 0; i < nbElements; i++)
	{
		std::string typeNoeud = noeudTable->getEnfant(i)->obtenirType();

		if (typeNoeud == "generateurbille")
			generateurs.push_back(i);
	}
	if (generateurs.size() == 0)
	{
		// On met le nombre de bille en jeu a -1, pour dire impossible
		globalesPartie_.retirerBille(colorshift);
		return false;
	}

	int pos = rand() % generateurs.size();

	NoeudAbstrait* generateur = noeudTable->getEnfant(generateurs[pos]);
	glm::dvec3 scale = generateur->obtenirAgrandissement();
	glm::dvec3 position = generateur->obtenirPositionRelative();
	glm::dvec3 rotation = generateur->obtenirRotation();
	glm::dvec3 vecteur = { 0, -((30 * scale.x)), 0 };
	double angleEnRadian = -rotation[2] * utilitaire::PI_180;
	glm::dmat3 transform = glm::dmat3{ glm::dvec3{ cos(angleEnRadian), -sin(angleEnRadian), 0.0 },
		glm::dvec3{ sin(angleEnRadian), cos(angleEnRadian), 0.0f },
		glm::dvec3{ 0.0, 0.0, 1.0 } };

	globalesPartie_.spawnBille(position + transform * vecteur, scale, generateur, colorshift);
	return true;
}


///////////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::printCurrentTime()
/// @brief Cette fonction affiche le temps maintenant
/// @return Aucune
///////////////////////////////////////////////////////////////////////////////
void FacadeModele::printCurrentTime()
{
	SYSTEMTIME time;
	GetLocalTime(&time);
	std::cout << std::fixed << std::setw(2) << std::setprecision(2) << time.wHour << ":"
		<< std::fixed << std::setfill('0') << std::setw(2) << std::setprecision(2) << time.wMinute << ":"
		<< std::fixed << std::setfill('0') << std::setw(2) << std::setprecision(2) << time.wSecond << ":"
		<< std::fixed << std::setfill('0') << std::setw(3) << std::setprecision(3) << time.wMilliseconds;
}


////////////////////////////////////////////////////////////////////////
/// @fn bool FacadeModele::obtenirAnimation()
/// @brief Retourne un booleen determinant si l'animation est active.
/// @return Booleen representant si l'animation est active ou non.
////////////////////////////////////////////////////////////////////////
bool FacadeModele::obtenirAnimation() const
{
	return animer_;
}


////////////////////////////////////////////////////////////////////////
/// @fn void FacadeModele::setBoiteTable(utilitaire::BoiteEnglobante boiteTable)
/// @brief Cette assigne une nouvelle boite englobante a boiteTable_.
/// @return Aucune
////////////////////////////////////////////////////////////////////////
void FacadeModele::setBoiteTable(utilitaire::BoiteEnglobante boiteTable)
{
	boiteTable_ = boiteTable;
}


////////////////////////////////////////////////////////////////////////
/// @fn double FacadeModele::obtenirTableMaxX() const 
/// @return la position max X de la table
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirTableMaxX() const
{
	double position = boiteTable_.coinMax.x + TRANSLATE_X_NOEUD_TABLE;
	if (position == TRANSLATE_X_NOEUD_TABLE)
		position = -100;	// Random value
	return position;
}


////////////////////////////////////////////////////////////////////////
/// @fn double FacadeModele::obtenirTableMaxY() const 
/// @return la position max Y de la table
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirTableMaxY() const
{
	double position = boiteTable_.coinMax.y + TRANSLATE_Y_NOEUD_TABLE;
	if (position == TRANSLATE_X_NOEUD_TABLE)
		position = -100;	// Random value
	return position;
}


////////////////////////////////////////////////////////////////////////
/// @fn double FacadeModele::obtenirTableMinX() const 
/// @return la position min X de la table
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirTableMinX() const
{
	double position = boiteTable_.coinMin.x + TRANSLATE_X_NOEUD_TABLE;
	if (position == TRANSLATE_X_NOEUD_TABLE)
		position = 100;	// Random value
	return position;
}


////////////////////////////////////////////////////////////////////////
/// @fn double FacadeModele::obtenirTableMinY() const 
/// @return la position min Y de la table
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirTableMinY() const
{
	double position = boiteTable_.coinMin.y + TRANSLATE_Y_NOEUD_TABLE;
	if (position == TRANSLATE_Y_NOEUD_TABLE)
		position = 100;	// Random value
	return position;
}


////////////////////////////////////////////////////////////////////////
/// @fn double FacadeModele::obtenirTableMinZ() const 
/// @return la position z de la table
////////////////////////////////////////////////////////////////////////
double FacadeModele::obtenirTableMinZ() const
{
	double position = boiteTable_.coinMin.z;
	return position;
}


////////////////////////////////////////////////////////////////////////
/// @fn GlobalesPartie* FacadeModele::obtenirGlobalesPartie()
/// @return Un pointeur vers les globales de la partie.
////////////////////////////////////////////////////////////////////////
GlobalesPartie* FacadeModele::obtenirGlobalesPartie()
{
	return &globalesPartie_;
}


////////////////////////////////////////////////////////////////////////
/// @fn GlobalesPartie* FacadeModele::obtenirGlobalesPartie()
/// @return Un pointeur vers les globales de la partie.
////////////////////////////////////////////////////////////////////////
bool FacadeModele::obtenirSiArbreVide() const
{
	return isLoaded_;
}

////////////////////////////////////////////////////////////////////////
/// @fn GlobalesPartie* FacadeModele::obtenirGlobalesPartie()
/// @return Un pointeur vers les globales de la partie.
////////////////////////////////////////////////////////////////////////
void FacadeModele::assignerSiArbreVide(bool isLoaded)
{
	isLoaded_ = isLoaded;
}
