////////////////////////////////////////////////
/// @file FacadeInterfaceNative.cpp
/// @author INF2990
/// @date 2014-08-16
///
/// @ingroup Interface
////////////////////////////////////////////////

// pour que ca arrete de chialer que gl.h est included avant glew.h
// Ca leur tenter pas de faire include glew.h dans gl.h ???
#include "GL/glew.h"
#include <gl/GLU.h>
#include <gl/GL.h>

#include "FacadeInterfaceNative.h"
#include "FacadeModele.h"
#include "FacadeReseau.h"
#include "FacadeEditeur.h"
#include "FacadeJeu.h"

#include "../Sound/ControleurSon.h"
#include "../Text/ControleurTexte.h"
#include "../Compte/Joueur.h"

#include "glm\glm.hpp"
#include "AideGL.h"
#include "Vue.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"

#include <iomanip>
#include <iostream>

#include <ctime> // std::time
#include <cstdlib> // std::rand, std::srand
#include<WS2tcpip.h> //include  this header first
#include <windows.h>
#include "BancTests.h"


extern "C"
{
	// TO DO : SUPPRIMER CETTE VARIABLE QUAND PLUS NECESSAIRE
	// Nvm, c'est devenue une necesite, donc garder ces variables absolument
	static NoeudAbstrait* objet = new NoeudAbstrait();
	static NoeudAbstrait* objet_temp = new NoeudAbstrait();

	////////////////////////////////////////////////////////////////////////
	/// @fn void libererModele()
	/// @brief Cette fonction libère la mémoire des Facades
	/// @return Aucune.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererModele()
	{
		try
		{
			/// Desinitialisation des facades
			FacadeModele::libererInstance();
			FacadeReseau::libererInstance();
			FacadeEditeur::libererInstance();
			FacadeJeu::libererInstance();
		}
		catch (...)
		{

		}
	}

	#pragma region OpenGL

	////////////////////////////////////////////////////////////////////////
	/// @fn void initialiserOpenGL(int* handle)
	/// @param[in] handle : Le handle.
	/// @return Aucune.
	/// @remark : Cette fonction initialise un contexte OpenGL dans la fenetre
	/// \remark identifiee par le handle passe en parametre. Cette fonction doit
	/// \remark etre la premiere a etre appelee, car la creation de l'objet du modele
	/// \remark C++ s'attend a avoir un contexte OpenGL valide.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserOpenGL(int* handle)
	{
		if (handle == nullptr)
			return;

		std::cout << std::endl << "Initialisation de l'openGL en cours..." << std::endl;
		FacadeModele::obtenirInstance()->initialiserOpenGL((HWND)handle);
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void libererOpenGL()
	/// @return Aucune.
	/// @remark : Cette fonction libere le contexte OpenGL. 
	/// \remark Cette fonction doit etre la derniere a etre appelee,
	/// \remark car elle libere egalement l'objet du modele C++
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl libererOpenGL()
	{
		FacadeModele::obtenirInstance()->libererOpenGL();
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void dessinerOpenGL()
	/// @return Aucune.
	/// @remark : Cette fonction affiche la scene.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dessinerOpenGL()
	{
		// Affiche la scene.
		FacadeModele::obtenirInstance()->afficher();
		// Temporaire: pour detecter les erreurs OpenGL
		aidegl::verifierErreurOpenGL();
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void animer(double temps)
	/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
	/// @return Aucune.
	/// @remark : Cette fonction effectue les differents calculs d'animations
	/// \remark necessaires pour le mode jeu, tel que les differents calculs de
	/// \remark physique du jeu.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animer(double temps)
	{
		FacadeModele::obtenirInstance()->animer((float)temps);
	}


	#pragma endregion 


	////////////////////////////////////////////////////////////////////////
	/// @fn void redimensionnerFenetre(int largeur, int hauteur)
	/// @param[in] largeur : La nouvelle largeur de la fenetre.
	/// @param[in] hauteur : La nouvelle hauteur de la fenetre.
	/// @return Aucune.
	/// @remark : Cette fonction doit etre appelee lorsque la fenetre est redimensionnee
	/// \remark afin d'ajuster les parametres de la machine a etats
	/// \remark d'OpenGL pour correspondre aux nouvelles dimensions de la fenetre.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl redimensionnerFenetre(int largeur, int hauteur)
	{
		FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(
			glm::ivec2{ 0, 0 },
			glm::ivec2{ largeur, hauteur }
		);
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn int selectionnerObjetSousPointClique(int i, int j, int hauteur, int largeur, bool ctrlDown)
	/// @remark Cette fonction permet de selectionner un objet. La methode regarde la valeur
	/// \remark du stencil et la donne a un visiteurSelection qui compare cette valeur
	/// \remark aux numeros des noeuds et change les met selectionnes ou pas selon le resultat
	/// \remark de la comparaison et selon qu'on a clique avec CTRL.
	/// @param[in] i : Position souris i
	/// @param[in] j : Position souris j
	/// @param[in] hauteur : Hauteur de la fenetre
	/// @param[in] largeur : Largeur de la fenetre
	/// @param[in] ctrlDown : Si le bouton ctrl est appuie
	/// @return NoeudAbstrait.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl selectionnerObjetSousPointClique(int i, int j, int hauteur, int largeur, bool ctrlDown, bool gaucheEnfonce, bool sourisSurSelection)
	{
		return FacadeEditeur::obtenirInstance()->selectionSimple(i, j, hauteur, largeur, ctrlDown, gaucheEnfonce, sourisSurSelection);
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void zoomIn()
	/// @return Aucune.
	/// @remark : Cette fonction applique un zoom avant sur le present volume de vision.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomIn()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void zoomOut()
	/// @return Aucune.
	/// @remark : Cette fonction applique un zoom arriere sur le present volume de vision.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOut()
	{
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirAffichagesParSeconde()
	/// @return Le nombre d'affichage par seconde.
	/// @remark : Cette fonction permet d'obtenir le nombre d'affichages par seconde.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirAffichagesParSeconde()
	{
		return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void creerObjet(char* value, int, bool isTwin, bool colorShift)
	/// @param[in] value : Nom de l'objet
	/// @param[in] isTwin : si a un jumeau
	/// @param[in] colorShift : la couleur
	/// @return Aucun
	/// @remark : Cette fonction permet de cree un objet 3D
	///	\remark Cree un objet sans initialiser ses proprietes.La fonction C# qui
	/// \remark L'appelle est responsable d'attribuer des proprietes.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl creerObjet(char* value, int, bool isTwin, int colorShift)
	{
		std::string nomObjet(value);
		auto facadeModele = FacadeModele::obtenirInstance();
		if (nomObjet == "bille")
		{
			if(facadeModele->preparerBille(colorShift))
			{
				facadeModele->obtenirGlobalesPartie()->ajouterBille(colorShift);
			}
			
			return;
		}
		if (isTwin == true) 
		{
			if (objet == nullptr)
				return;
			objet_temp = facadeModele->obtenirArbreRenduINF2990()->creerNoeud(nomObjet);
			objet_temp->setColorShift(colorShift);
			objet_temp->setTwin(objet);
			objet->setTwin(objet_temp);
			objet->assignerSelection(true);
			objet->setTransparent(true);
			objet = objet_temp;
		}
		else 
		{
			objet = facadeModele->obtenirArbreRenduINF2990()->creerNoeud(nomObjet);
			if (objet == nullptr)
				return;
			objet->setColorShift(colorShift);

			if (nomObjet == "mur")
			{
				objet->assignerSelection(true);
			}
		}
		facadeModele->obtenirArbreRenduINF2990()->getEnfant(0)->ajouter(objet);
		FacadeJeu::obtenirInstance()->mettreAJourListeBillesEtNoeuds();
		FacadeJeu::obtenirInstance()->construireListesPalettes();
		facadeModele->setDebug();
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn bool creerObjetAvecTests(char* value, int, bool isTwin, bool colorShift, int posX, int posY, int, float angleX, float angleY, float angleZ)
	/// @param[in] value : Nom de l'objet
	/// @param[in] isTwin : si a un jumeau
	/// @param[in] colorShift : la couleur
	/// @param[in] posX : la position en X de l'objet a creer.
	/// @param[in] posY : la position en Y de l'objet a creer.
	/// @param[in] angleX : l'angle en X de l'objet a creer.
	/// @param[in] angleY : l'angle en Y de l'objet a creer.
	/// @param[in] angleZ : l'angle en Z de l'objet a creer.
	/// @return True si l'objet a ete cree, false si une des etapes de la creation a echoue.
	/// @remark : Cette fonction permet de cree un objet 3D.
	/// \remark Cette fonction contient toutes les etapes de la creation d'objet.
	/// \remark Premierement, on fait quelques assignations specifiques aux portails et 
	/// \remark aux murs. A la fin de ceci, l'objet est cree et on retient un pointeur
	/// \remark vers celui ci dans la variable statique NoeudAbstrait* objet.
	/// \remark 
	/// \remark Ensuite, avant d'ajouter l'objet a l'arbre de rendu, on verifie qu'il 
	/// \remark serait entierement dans la table en faisant un test sur les points
	/// \remark de sa boite englobante.
	/// \remark 
	/// \remark Si chaque point de la boite englobante passe le test, on ajoute l'objet
	/// \remark a l'arbre de rendu comme enfant de la table. Sinon, on l'efface.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl creerObjetAvecTests(char* value, int, bool isTwin, bool colorShift, 
															int posX, int posY, int, 
															float angleX, float angleY, float angleZ)
	{
		// Meme chose que dans creer objet, sauf que je test le nouvel objet avant de l'ajouter a l'arbre.
		// Pour pouvoir tester l'objet avant de l'ajouter, je dois setter ses proprietes

		// Comme avant
		// ============
		std::string nomObjet(value);
		if (isTwin == true) {
			objet_temp = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(nomObjet);
			objet_temp->setColorShift(colorShift);
			if (objet == nullptr)
				return false;
			objet_temp->setTwin(objet);
			objet->setTwin(objet_temp);
			objet->assignerSelection(false);
			objet->setTransparent(true);
			objet = objet_temp;
		}
		else
		{
			objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->creerNoeud(nomObjet);
			if (objet == nullptr)
				return false;
			objet->setColorShift(colorShift);
			if (nomObjet == "mur")
			{
				objet->assignerSelection(true);
			}
		}
		// Assigner les proprietes a l'objet
		// =================================
		
		// Assigner position et angles a l'objet.
		glm::dvec3 positionObjet;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(posX, posY, positionObjet);
		objet->assignerPositionRelative(positionObjet);

		// Voir la fonction rotate, c'est comme ca que les angles sont settes dans cette fonction.
		// if('Y') if (direction == 'y' || direction == 'Y' || direction == '1')
		// objet->assignerRotation({ angle, 0.0, 0.0 });
		// et en effet, si je mettais {angleX,angleY,angleZ} les palettes n'apparaiteraient pas.
		glm::dvec3 anglesObjet{ angleY, angleZ, angleX };
		objet->assignerRotation(anglesObjet);
		

		// Tester si l'objet est legal.
		// =============================
		bool objetEstLegal = true;
		/*glm::dvec3 boite[4];
		objet->obtenirVecteursBoite(boite[0], boite[1], boite[2], boite[3]);
		glm::dvec3 pointATester;
		for (int i = 0; i < 4; i++)
		{
			pointATester = positionObjet + boite[i];
			if (!FacadeModele::obtenirInstance()->estDansTable(pointATester))
			{
				objetEstLegal = false;
			}

		}*/

		// Ajouter l'objet s'il est legal
		// ==============================

		if (objetEstLegal)
		{
			// Si l'objet est legal, l'ajouter a la table, sinon, on le scrap
			FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->ajouter(objet);
			if (nomObjet == "portail")
				FacadeModele::obtenirInstance()->setDebug();

			objet->assignerSelection(true);

			return true;
		}
		else
		{
			// delete objet;
			// objet = nullptr;
			return false;
		}
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void positionObjet(int x, int y, int z)
	/// @param[in] x : La positon en x
	/// @param[in] y : La positon en y
	/// @param[in] z : La positon en z
	/// @return Aucune.
	/// @remark : Permet de deplacer un objet en x y et/ou z
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl positionObjet(int x, int y, int z)
	{
		if (objet == nullptr)
			return;

		glm::dvec3 maPosition;
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(x, y, maPosition);
		
		if (FacadeEditeur::obtenirInstance()->estDansTable(maPosition)) 
		{
			objet->assignerPositionRelative({ maPosition.x, maPosition.y, z });
		}
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void translateObjet(int x, int y, int z)
	/// @param[in] x : La positon en x
	/// @param[in] y : La positon en y
	/// @param[in] z : La positon en z
	/// @return Aucune.
	/// @remark : Permet de deplacer un objet en x y et/ou z
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl translateObjet(int x, int y, int)
	{
		if (objet == nullptr)
			return;

		glm::dvec3 maPositionPresente;
		maPositionPresente = objet->obtenirPositionRelative();
		objet->assignerPositionRelative({ maPositionPresente.x + x,
			maPositionPresente.y + y,
			0 });
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void scaleObjet(double scale)
	/// @param[in] scale : La multiplication en x
	/// @return Aucune.
	/// @remark : Permet de resize un objet uniformement
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl scaleObjet(double scale)
	{
		if (objet == nullptr)
			return;

		objet->assignerEchelle({ scale, scale, scale });
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void removeObject( void )
	/// Remet les donnees d'un objet a 0
	/// @return Aucune.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl removeObject( void )
	{
		FacadeEditeur::obtenirInstance()->supprimerSelection();
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void translater(double deplacementX, double deplacementY)
	/// @param[in] deplacementX : Deplacement en pourcentage de la largeur.
	/// @param[in] deplacementY : Deplacement en pourcentage de la hauteur.
	/// @return Aucune.
	/// @remark : Permet de faire un "plan" d'un certain pourcentage.
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl translater(double deplacementX, double deplacementY)
	{
		// Notez bien que cette valeur transmise est d'habitude de 10 depuis le C#

		/* Si la camera est orbite, on redirige la methode vers celle appropriee*/
		if (FacadeModele::obtenirInstance()->cameraEstOrbite())
		{
			orbite(deplacementX / 3.0, deplacementY / 3.0);
		}
		else
		{
			FacadeModele::obtenirInstance()->obtenirVue()->deplacerXY(deplacementX, deplacementY);
		}
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void takeScreenShot(char* path, int, bool square, int maxSize)
	/// @param[in] path : Nom du path
	/// @param[in] square : forme de l'image carre
	/// @param[in] maxSize : taille maximale (pixel) de l'image
	/// @return Aucun
	/// @remark : Prend un screenshot de la zone de jeu
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl takeScreenShot(char* path, int, bool square, int maxSize)
	{
		glm::ivec2 size = FacadeModele::obtenirInstance()->obtenirTailleFenetre();
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->takeScreenShot(path, size.x, size.y, square, maxSize);
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void orbite(double x, double y)
	/// @param[in] x :	Rotation x
	/// @param[in] y : Rotation Y
	/// @return Aucun
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl orbite(double x, double y)
	{
		// Habituellement la valeur de x et y est de 10 depuis le C#
		/// En theta, pour correspondre a une rotation dans le sens de la fleche il faut envoyer l'oppose
		FacadeModele::obtenirInstance()->obtenirVue()->rotaterXY( -1 * x, y);
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void zoomInElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
	/// @param[in] xCoin1 : Coin initial du zoom elastique en x
	/// @param[in] yCoin1 : Coin initial du zoom elastique en y
	/// @param[in] xCoin2 : Coin final du zoom elastique en x
	/// @param[in] yCoin2 : Coin final du zoom elastique en y
	/// @return Aucun
	/// @remark : Permet de centrer l'ecran sur la region definie par les points passes
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomInElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
	{
		glm::dvec3 positionSouris1(xCoin1, yCoin1, 0.0);
		glm::dvec3 positionSouris2(xCoin2, yCoin2, 0.0);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xCoin1, yCoin1, positionSouris1);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xCoin2, yCoin2, positionSouris2);

		glm::ivec2 coin1(positionSouris1.x, positionSouris1.y);
		glm::ivec2 coin2(positionSouris2.x, positionSouris2.y);
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerInElastique(coin1, coin2);
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void zoomOutElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
	/// @param[in] xCoin1 : Coin initial du zoom elastique en x
	/// @param[in] yCoin1 : Coin initial du zoom elastique en y
	/// @param[in] xCoin2 : Coin final du zoom elastique en x
	/// @param[in] yCoin2 : Coin final du zoom elastique en y
	/// Permet de centrer l'ecran sur la region definie par les points passes
	/// @return Aucun
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl zoomOutElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2)
	{
		glm::dvec3 positionSouris1(xCoin1, yCoin1, 0.0);
		glm::dvec3 positionSouris2(xCoin2, yCoin2, 0.0);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xCoin1, yCoin1, positionSouris1);
		FacadeModele::obtenirInstance()->obtenirVue()->convertirClotureAVirtuelle(xCoin2, yCoin2, positionSouris2);

		glm::dvec2 coin1(positionSouris1.x, positionSouris1.y);
		glm::dvec2 coin2(positionSouris2.x, positionSouris2.y);
		FacadeModele::obtenirInstance()->obtenirVue()->zoomerOutElastique(coin1, coin2);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void deplacerSelection(int x1, int y1, int x2, int y2)
	///	@brief Deplace les noeuds selectionnes d'un deplacement calcule en coordonnees du monde
	///		   a partir des points initiaux et terminaux dans les coordonnees d'affichage OpenGL
	/// @param[in] x1 : abcisse du point initial
	/// @param[in] y1 : ordonnee du point initial
	/// @param[in] x2 : abcisse du point initial
	/// @param[in] y2 : ordonnee du point initial
	/// @return Aucun
	/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deplacerSelection(int x1, int y1, int x2, int y2, bool duplication)
	{
		FacadeEditeur::obtenirInstance()->deplacerSelection(x1, y1, x2, y2, duplication);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void tournerSelectionSouris(int x1, int y1, int x2, int y2)
	/// @param[in] x1 : abcisse du point initial
	/// @param[in] y1 : ordonnee du point initial
	/// @param[in] x2 : abcisse du point initial
	/// @param[in] y2 : ordonnee du point initial
	/// @return Aucun
	/// @remark : L'angle de rotation est calcule a partir du deplacement. On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl tournerSelectionSouris(int x1, int y1, int x2, int y2)
	{
		FacadeEditeur::obtenirInstance()->tournerSelection(x1, y1, x2, y2);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void agrandirSelection(int x1, int y1, int x2, int y2)
	/// @param[in] x1 : abcisse du point initial
	/// @param[in] y1 : ordonnee du point initial
	/// @param[in] x2 : abcisse du point initial
	/// @param[in] y2 : ordonnee du point initial
	/// @return Aucun
	/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...). La focntion change l'echelle des objets selectionnes. Chaque deplacement de 1 pixel vers le haut multiplie l'echelle courrante par 1.003, et chaque deplacement vers le bas divise par 1.003.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl agrandirSelection(int x1, int y1, int x2, int y2)
	{
		FacadeEditeur::obtenirInstance()->agrandirSelection(x1, y1, x2, y2);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void rectangleElastique(int i, int j)
	/// @param[in] i : point suivant i de la souris
	/// @param[in] j : point suivant j de la souris
	/// @return Aucun
	/// @remark : Met a jour le rectangle elastique
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl rectangleElastique(int i, int j)
	{
		FacadeEditeur::obtenirInstance()->rectangleElastique(i, j);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int selectionMultiple(bool c)
	/// @param[in] c : Selection inverser ou non
	/// @return Aucun
	/// @remark : Active la selection multiple, cherche si les objets sont dans le rectangle elastique.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl selectionMultiple(bool c)
	{
		return FacadeEditeur::obtenirInstance()->selectionMultiple(c);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn bool verifierCliqueDansTable(int x, int y)
	/// @param[in] x : abcisse du point initial 
	/// @param[in] y : ordonnee du point initial
	/// @return true si le clic est dans la table, faux sinon.
	/// @remark : Verifie si un clic est dans la table. On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl verifierCliqueDansTable(int x, int y)
	{
		return FacadeEditeur::obtenirInstance()->verifierCliqueDansTable(x, y);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void deselectAll( void )
	/// @return Aucun
	/// @remark : Ca deselectionne tout
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl deselectAll( void )
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->deselectionnerTout();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void selectAll( void )
	/// @return Aucun
	/// @remark : Ca deselectionne tout
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl selectAll(void)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->selectionnerTout();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void dupliquerSelection(int i, int j)
	/// @param[in] i : point suivant i de la souris
	/// @param[in] j : point suivant j de la souris
	/// @return Aucun
	/// @remark : Permet duplique les objets selectionnes
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl dupliquerSelection(int i, int j)
	{
		FacadeEditeur::obtenirInstance()->dupliquerSelection(i, j);
		FacadeModele::obtenirInstance()->setDebug();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn getPositionX() 
	/// @return la position en X
	/// @remark : Retourne le x de la position du dernier objet selectionne qu'on a trouve dans l'arbre.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl getPositionX() 
	{
		double positionX = 0;
		if (objet == nullptr)
			return false;
		
		for (unsigned int j = 0; j < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants(); j++)
		{
			if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j)->estSelectionne()) 
			{
				objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j);
				positionX = objet->obtenirPositionRelative().x;
			}
		}
		return positionX;
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn double getPositionY()
	/// @return la position en Y
	/// @remark : Retourne le y de la position du dernier objet selectionne qu'on a trouve dans l'arbre.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl getPositionY()
	{
		double positionY = 0;
		if (objet == nullptr)
			return false;

		for (unsigned int j = 0; j < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants(); j++)
		{
			if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j)->estSelectionne()) 
			{
				objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j);
				positionY = objet->obtenirPositionRelative().y;
			}
		}
		return positionY;
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn double getAngle()
	/// @return l'angle de l'objet
	/// @remark : Retourne l'angleZ du dernier objet selectionne qu'on a trouve dans l'arbre.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getAngle()
	{
		if (objet == nullptr)
			return false;

		double angle=0;
		for (unsigned int j = 0; j < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants(); j++)
		{
			if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j)->estSelectionne()) 
			{
				objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j);
				angle = objet->obtenirRotation().z;
			}
		}
		return angle;
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn double getScale()
	/// @return la taille de l'objet (Retourne le scale du dernier objet selectionne qu'on a trouve dans l'arbre.)
	/// @remark : Le scale en y est representatif des objets normaux et des murs.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double getScale()
	{
		double scale =0;
		if (objet == nullptr)
			return false;

		for (unsigned int j = 0; j < FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->obtenirNombreEnfants(); j++)
		{
			if (FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j)->estSelectionne()) 
			{
				objet = FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->getEnfant(0)->chercher(j);
				scale = objet->obtenirAgrandissement().y;
			}
		}
		return scale;
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void jouerSon(char* value, int, bool pause)
	/// @param[in] value : Nom du son
	/// @param[in] pause : Arret du son
	/// @return Aucun
	/// @remark Cette fonction permet de jouer un son ou de l'arreter
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl jouerSon(char* value, int, bool pause)
	{
		FacadeModele::obtenirInstance()->obtenirControleurSon()->jouerSon(value, pause);
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void bouclerSon(char* value, int, bool loop)
	/// @param[in] value : Nom du son
	/// @param[in] loop : Faire boucler le son en continue ou non
	/// @return Aucun
	/// @remark Cette fonction permet de jouer un son en boucle
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl bouclerSon(char* value, int, bool loop)
	{
		FacadeModele::obtenirInstance()->obtenirControleurSon()->bouclerSon(value, loop);
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void arreterToutSons()
	/// @return Aucun
	/// @remark Permet d'arreter completement tout les sons (mais ne le detruit pas)
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl arreterToutSons()
	{
		FacadeModele::obtenirInstance()->obtenirControleurSon()->arreterSon();
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void ajusterVolume(char* value, int, float pourcentage)
	/// @param[in] value : Nom du son
	/// @param[in] pourcentage : Valeur entre 0 et 100 pour ajuster le volume
	/// @return Aucun
	/// @remark Cette fonction permet d'ajuster le volume d'un son precis
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl ajusterVolume(char* value, int, float pourcentage)
	{
		FacadeModele::obtenirInstance()->obtenirControleurSon()->ajusterVolume(value, pourcentage);
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void ajusterVolume(char* value, int, bool mute)
	/// @param[in] value : Nom du son
	/// @param[in] mute : Bloquer ou debloquer le son
	/// @return Aucun
	/// @remark Cette fonction permet de fermer/ ouvrir le son
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl mute(char* value, int, bool mute)
	{
		FacadeModele::obtenirInstance()->obtenirControleurSon()->muteSound(value, mute);
	}


	////////////////////////////////////////////////////////////////////////
	/// @fn void  initialiserSon();
	/// @return Aucun
	/// @remark Cette fonction permet d'initialiser les sons
	////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserSon()
	{
		std::cout << "Initialisation des sons ..." << std::endl;
		FacadeModele::obtenirInstance()->obtenirControleurSon();
		std::cout << "Sons initialiser." << std::endl;
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void obligerTransparence(bool transparence)
	/// @param[in] transparence : booleen de transparence
	/// @return Aucun
	/// @remark : On doit donner des x,y qui ont ete transformes par panel_GL.PointToClient(...)
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl obligerTransparence(bool transparence)
	{
		if (objet == nullptr)
			return;

		// Il faut faire un visiteur par contre
		objet->setTransparent(transparence);
		if (objet->getTwin() != nullptr)
		{
			objet->getTwin()->setTransparent(transparence);

			if (objet->getTwin() != nullptr)
				objet->getTwin()->getTwin()->setTransparent(transparence);
		}
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void initialiserRectangleElastique(int i, int j)
	/// @param[in] i : coordonnees i de la souris
	/// @param[in] j : coordonnees j de la souris
	/// @return Aucun
	/// @remark Initialise le rectangle elastique
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl initialiserRectangleElastique(int i, int j)
	{
		FacadeEditeur::obtenirInstance()->initialiserRectangleElastique(i, j);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void terminerRectangleElastique()
	/// @return Aucun
	/// @remark Suprime le rectangle elastique
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl terminerRectangleElastique()
	{
		FacadeEditeur::obtenirInstance()->terminerRectangleElastique();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void creerMur(int originX, int originY,int x1, int y1, int x2, int y2) 
	/// @param[in] originX : Position en X ou le bouton a ete appuye
	/// @param[in] originY : Position en Y ou le bouton a ete appuye
	/// @param[in] x1 : Position en X precedant un deplacement de la souris
	/// @param[in] y1 : Position en Y precedant un deplacement de la souris
	/// @param[in] x2 : Position en X apres un deplacement de la souris (position actuelle de la souris)
	/// @param[in] y2 : Position en X apres un deplacement de la souris (position actuelle de la souris)
	/// @return Aucun
	/// @remark : Cette fonction place un mur dont un bout est la ou le bouton gauche de la souris a ete appuye, et l'autre bout est sous le curseur de la souris.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl creerMur(int originX, int originY, int x1, int y1, int x2, int y2)
	{
		FacadeEditeur::obtenirInstance()->positionnerMur(originX, originY, x1, y1, x2, y2, objet);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn bool setProprietesNoeud(int x, int y, int angle, double scale)
	/// @param[in] x : X en coordonnees du monde qu'on veut donner a notre noeud.
	/// @param[in] y : Y en coordonnees du monde qu'on veut donner a notre noeud.
	/// @param[in]	angle : angle de rotation
	///	@param[in]	scale: scale de l'objet
	/// @return bool
	/// @remark : La fonction calcule la boite englobante de l'objet transforme, le calcul est differend pour les murs. Il manque quelque chose pour le calcul des boites englobantes transformees des objets de type mur.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl setProprietesNoeud(int x, int y, int angle, double scale)
	{
		// Calculer la position a assigner en coordonnees du monde. Elle est deja en
		// coordonnees du monde car ce qui est dans les textBox, c'est l'attribut position du noeud.
		glm::dvec3 nouvellePosition{ x, y, 0 };
		bool nouvellesProprietesSontLegales = true;
		glm::dvec3 boite[4];
		glm::dvec3 positionObjet = objet->obtenirPositionRelative();
		objet->obtenirBoiteModele(boite[0], boite[1], boite[2], boite[3]);

		glm::dmat3 echelle;
		glm::dvec3 scaleInitial = objet->obtenirAgrandissement();
		if (objet->obtenirType() == "mur")
		{
			echelle = glm::dmat3{	glm::dvec3{ scaleInitial.x,	0,		0.0 },
									glm::dvec3{		 0,			scale,	0.0f },
									glm::dvec3{		0.0,		0.0,	scaleInitial.z } };
		}
		else
			echelle = glm::dmat3{ glm::dvec3{ scale, 0, 0.0 },
									glm::dvec3{ 0, scale, 0.0f },
									glm::dvec3{ 0.0, 0.0, scale } };
		double angleRadian = angle * 2 * 3.14156 /360 ;

		glm::dmat3 rotation = glm::dmat3{	glm::dvec3{ cos(angleRadian), -sin(angleRadian), 0.0 },
											glm::dvec3{ sin(angleRadian), cos(angleRadian), 0.0f },
											glm::dvec3{		0.0,	0.0,		1.0 } };

		glm::dvec3 pointATester;
		for (int i = 0; i < 4; i++)
		{
			// Appliquer les nouvelles proprietes.
			pointATester = nouvellePosition + rotation * (echelle * boite[i]);
			// Tester
			if (!FacadeEditeur::obtenirInstance()->estDansTable(pointATester))
			{
				nouvellesProprietesSontLegales = false;
				//std::cout << "L'application des proprietes refusee, on sortirait de la table" << std::endl;
				return false;
			}
		}

		if (nouvellesProprietesSontLegales)
		{
			glm::dvec3 angles = objet->obtenirRotation();
			glm::dvec3 nouveauxAngles = glm::dvec3{ angles.x, angles.y, angle }; 
			objet->assignerPositionRelative(nouvellePosition);
			objet->assignerRotationHard(nouveauxAngles);

			// traiter le mur de facon speciale.
			if (objet->obtenirType() == "mur")
				objet->assignerEchelle(glm::dvec3{ scaleInitial.x, scale, scaleInitial.z });
			else
				objet->assignerEchelle(glm::dvec3{ scale, scale, scale });
		}
		return true;
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn obtenirZoomCourant()
	/// @return : valeur du zoom courant
	/// @remark La valeur du facteur de zoom appliquer sur la fenetre
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) double __cdecl obtenirZoomCourant()
	{
		if (FacadeModele::obtenirInstance() == nullptr)
			return -1;
		return FacadeModele::obtenirInstance()->obtenirZoomCourant();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirCentreMasseX( void )
	/// @return : int, le centre de masse en x
	/// @remark La valeur en X de centre de masse
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirCentreMasseX( void )
	{
		return FacadeModele::obtenirInstance()->obtenirCentreMasseX();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirCentreMasseY( void )
	/// @return le centre de masse en y
	/// @remark La valeur en Y de centre de masse
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirCentreMasseY( void )
	{
		return FacadeModele::obtenirInstance()->obtenirCentreMasseY();
	}
	

	///////////////////////////////////////////////////////////////////////////////
	/// @fn bool resetZoom()
	/// @return : booleen de reussite
	/// @remark Remet a 0 le centre du zoom
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl resetZoom()
	{
		return FacadeModele::obtenirInstance()->appliquerZoomInitial();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn bool duplicationEstHorsTable( void )
	/// @return bool d'etat si hors table
	/// @remark true si la souris la selection est hors table lors de la duplication
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl duplicationEstHorsTable( void )
	{
		return FacadeEditeur::obtenirInstance()->duplicationEstHorsTable();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void creerFichierConfig(int config[13])
	/// @brief Cree un fichier de sauvegarde de configuration.
	/// @param[in] config : Valeurs de la configuration de partie.
	/// @return Aucune
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl creerFichierConfig(int config[14])
	{
		FacadeModele::obtenirInstance()->sauvegarderConfiguration(config);
	}
	

	///////////////////////////////////////////////////////////////////////////////
	/// @fn int* chargerFichierConfiguration()
	/// @brief Charger un fichier de sauvegarde de configuration.
	/// @return Les valeurs de configuration.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int* __cdecl chargerFichierConfiguration()
	{
		return FacadeModele::obtenirInstance()->obtenirConfiguration();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirDifficulte(char* nomFichier, int)
	/// @brief Obtenir le niveau de difficulte de la zone.
	/// @param[in] nomFichier : Mom du fichier de la zone.
	/// @return Le niveau de difficulte de la zone.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirDifficulte(char* nomFichier, int)
	{
		return FacadeModele::obtenirInstance()->obtenirDifficulte(nomFichier);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn char* obtenirPropriete()
	/// @brief Obtenir les propriétés de la zone de jeu en format de chaine de caractère
	/// @param[in] Aucun
	/// @return Une chaine de caractère
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char* __cdecl obtenirPropriete()
	{
		std::string prop = FacadeEditeur::obtenirInstance()->obtenirPropriete();
		const char* value = prop.c_str();
		size_t stSize = strlen(value) + sizeof(char);

		char* pszReturn = nullptr;

		pszReturn = (char*)::CoTaskMemAlloc(stSize);
		// Copy the contents of test1
		// to the memory pointed to by pszReturn.
		strcpy_s(pszReturn, stSize, value);
		// Return pszReturn.
		return pszReturn;
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn char* sauvegarderZone(char*, int, char*, int)
	/// @brief Obtenir les propriétés de la zone de jeu en format de chaine de caractère
	/// @param[in] nomFichier: le nom du fichier
	/// @param[in] nomLength: la taille du nom
	/// @param[in] proprietes: les proprietes à sauvegarder
	/// @param[in] proprietesLength: la taille des proprietes
	/// @return Une chaine de caractère qui retourne le résultat de la sauvegarde
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char* __cdecl sauvegarderZone(char* nomFichier, int nomLength, char* proprietes, int proprietesLength)
	{
		std::string result = FacadeEditeur::obtenirInstance()->sauvegarderZone(nomFichier, proprietes);
		const char* value = result.c_str();
		size_t stSize = strlen(value) + sizeof(char);

		char* pszReturn = nullptr;

		pszReturn = (char*)::CoTaskMemAlloc(stSize);
		// Copy the contents of test1
		// to the memory pointed to by pszReturn.
		strcpy_s(pszReturn, stSize, value);
		// Return pszReturn.
		return pszReturn;
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn char* chargerZone(char*, int)
	/// @brief Obtenir les propriétés de la zone de jeu en format de chaine de caractère
	/// @param[in] nomFichier : nom du fichier à charger
	/// @param[in] nomLength : taille du nom de fichier
	/// @return Aucune
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl chargerZone(char* nomFichier, int nomLength)
	{
		FacadeEditeur::obtenirInstance()->chargerZone(std::string(nomFichier));
		FacadeModele::obtenirInstance()->setDebug();
		FacadeModele::obtenirInstance()->assignerSiArbreVide(true);

		bool isOnlineAccount = FacadeReseau::obtenirInstance()->obtenirCompte()->isOnlineAccount();

		if (isOnlineAccount)
		{
			bool isCompetitif = FacadeReseau::obtenirInstance()->isCompetitif();

			if (isCompetitif)
			{
				FacadeJeu::obtenirInstance()->initialiserModeCompetitif();
			}
			else
			{
				FacadeJeu::obtenirInstance()->initialiserModeCooperatif();
			}
		}

		FacadeJeu::obtenirInstance()->construireListesPalettes();
		FacadeJeu::obtenirInstance()->mettreAJourListeBillesEtNoeuds();
	}
	

	///////////////////////////////////////////////////////////////////////////////
	/// @fn void creerFichierCampagne(char* listMaps, int)
	/// @brief Creer un fichier contenant les zones de la campagne.
	/// @param[in] listMaps : Liste des zones de jeu.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl creerFichierCampagne(char* listMaps, int)
	{
		FacadeModele::obtenirInstance()->sauvegarderCampagne(listMaps);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirTouchePGJ1()
	/// @brief Retourne la touche associee a Palette Gauche J1.
	/// @return La touche associee.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirTouchePGJ1()
	{
		return FacadeModele::obtenirInstance()->obtenirTouchePGJ1(); 
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirTouchePGJ2()
	/// @brief Retourne la touche associee a Palette Gauche J2.
	/// @return La touche associee.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirTouchePGJ2()
	{
		return FacadeModele::obtenirInstance()->obtenirTouchePGJ2(); 
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirTouchePDJ1()
	/// @brief Retourne la touche associee a Palette Droite J1.
	/// @return La touche associee.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirTouchePDJ1()
	{
		return FacadeModele::obtenirInstance()->obtenirTouchePDJ1(); 
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirTouchePDJ2()
	/// @brief Retourne la touche associee a Palette Droite J2.
	/// @return La touche associee.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirTouchePDJ2()
	{
		return FacadeModele::obtenirInstance()->obtenirTouchePDJ2(); 
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirToucheRessort()
	/// @brief Retourne la touche associee au ressort.
	/// @return La touche associee.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirToucheRessort()
	{
		return FacadeModele::obtenirInstance()->obtenirToucheRessort(); 
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirNombreDeBilles()
	/// @brief Retourne le nombre de billes
	/// @return Le nombre de billes.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirNombreDeBilles()
	{
		return FacadeModele::obtenirInstance()->obtenirNombreDeBilles();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirNombreBillesPerdus()
	/// @brief Retourne le nombre de billes detruite
	/// @return Le nombre de billes.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirNombreBillesPerdus(int colorshift)
	{
		return FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->obtenirNombreDeBillesPerdues(colorshift);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirModeDoubleBille()
	/// @brief Retourne la valeur d'activation du mode correspondant.
	/// @return 1 si le mode double bille est actif, 0 sinon.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirModeDoubleBille()
	{
		return FacadeModele::obtenirInstance()->obtenirModeDoubleBille();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirNombreDeBilles()
	/// @brief Retourne la valeur d'activation du mode correspondant.
	/// @return 1 si l'affichage global est actif, 0 sinon.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirAffichageGlobal()
	{
		return FacadeModele::obtenirInstance()->obtenirAffichageGlobal();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void bloquerAffichageGlobal(int active)
	/// @brief Active ou desactive l'affichage global.
	/// @param[in] active : Valeur d'activation.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl bloquerAffichageGlobal(int active)
	{
		FacadeModele::obtenirInstance()->bloquerAffichageGlobal(active);
		FacadeModele::obtenirInstance()->setDebug();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void activerPalettesGJ1()
	/// @brief Active la Palette Gauche J1.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl activerPalettesGJ1(int colorshift)
	{
		FacadeJeu::obtenirInstance()->activerPalettesGauches(colorshift);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void desactiverPalettesGJ1()
	/// @brief Desactive la Palette Gauche J1.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl desactiverPalettesGJ1(int colorshift)
	{
		FacadeJeu::obtenirInstance()->desactiverPalettesGauches(colorshift);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void activerPalettesDJ1()
	/// @brief Active la Palette Droite J1.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl activerPalettesDJ1(int colorshift)
	{
		FacadeJeu::obtenirInstance()->activerPalettesDroites(colorshift);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void desactiverPalettesDJ1()
	/// @brief Desactive la Palette Droite J1.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl desactiverPalettesDJ1(int colorshift)
	{
		FacadeJeu::obtenirInstance()->desactiverPalettesDroites(colorshift);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void activerPalettesGJ2()
	/// @brief Active la Palette Gauche J2.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl activerPalettesGJ2(int colorshift)
	{
		FacadeJeu::obtenirInstance()->activerPalettesGauches(colorshift);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void desactiverPalettesGJ2()
	/// @brief Desactive la Palette Gauche J2.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl desactiverPalettesGJ2(int colorshift)
	{
		FacadeJeu::obtenirInstance()->desactiverPalettesGauches(colorshift);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void activerPalettesDJ2()
	/// @brief Active la Palette Droite J2.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl activerPalettesDJ2(int colorshift)
	{
		FacadeJeu::obtenirInstance()->activerPalettesDroites(colorshift);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void desactiverPalettesDJ2(int colorshift)
	/// @brief Desactive la Palette Droite J2.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl desactiverPalettesDJ2(int colorshift)
	{
		FacadeJeu::obtenirInstance()->desactiverPalettesDroites(colorshift);
	}



	///////////////////////////////////////////////////////////////////////////////
	/// @fn void activerPalettesDJ2()
	/// @brief Active la Palette Gauche J2.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void activerPalettesGauches(int colorshift)
	{
		FacadeJeu::obtenirInstance()->activerPalettesGauches(colorshift);
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @fn void activerPalettesDJ2()
	/// @brief Active la Palette Gauche J2.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void desactiverPalettesGauches(int colorshift)
	{
		FacadeJeu::obtenirInstance()->desactiverPalettesGauches(colorshift);
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @fn void activerPalettesDJ2()
	/// @brief Active la Palette Droite
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void activerPalettesDroites(int colorshift)
	{
		FacadeJeu::obtenirInstance()->activerPalettesDroites(colorshift);
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @fn void activerPalettesDJ2()
	/// @brief Active la Palette Droite
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void desactiverPalettesDroites(int colorshift)
	{
		FacadeJeu::obtenirInstance()->desactiverPalettesDroites(colorshift);
	}



	///////////////////////////////////////////////////////////////////////////////
	/// @fn char* obtenirDerniereCampagne()
	/// @brief Retourne les informations de dernière campagne de l'utilisateur
	/// @return Les zones de jeu précédemment joués
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char* __cdecl obtenirDerniereCampagne()
	{
		std::string result = FacadeModele::obtenirInstance()->obtenirDerniereCampagne();
		const char* value = result.c_str();
		size_t stSize = strlen(value) + sizeof(char);

		char* pszReturn = nullptr;

		pszReturn = (char*)::CoTaskMemAlloc(stSize);
		// Copy the contents of test1
		// to the memory pointed to by pszReturn.
		strcpy_s(pszReturn, stSize, value);
		// Return pszReturn.
		return pszReturn;
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @fn char* getUserName()
	/// @brief Retourne les informations du joueur connecté
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char* getUserName()
	{
		std::string result = FacadeReseau::obtenirInstance()->obtenirCompte()->getName();
		const char* value = result.c_str();
		size_t stSize = strlen(value) + sizeof(char);

		char* pszReturn = nullptr;

		pszReturn = (char*)::CoTaskMemAlloc(stSize);
		// Copy the contents of test1
		// to the memory pointed to by pszReturn.
		strcpy_s(pszReturn, stSize, value);
		// Return pszReturn.
		return pszReturn;

	}

	///////////////////////////////////////////////////////////////////////////////
	/// @fn char* obtenirBonus()
	/// @brief Retourne les informations des bonus
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char* obtenirBonus()
	{
		std::string result = FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->obtenirBonusCourant();
		const char* value = result.c_str();
		size_t stSize = strlen(value) + sizeof(char);

		char* pszReturn = nullptr;

		pszReturn = (char*)::CoTaskMemAlloc(stSize);
		// Copy the contents of test1
		// to the memory pointed to by pszReturn.
		strcpy_s(pszReturn, stSize, value);
		// Return pszReturn.
		return pszReturn;
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @fn char* obtenirMalus()
	/// @brief Retourne les informations des malus
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char* obtenirMalus()
	{
		std::string result = FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->obtenirMalusCourant();
		const char* value = result.c_str();
		size_t stSize = strlen(value) + sizeof(char);

		char* pszReturn = nullptr;

		pszReturn = (char*)::CoTaskMemAlloc(stSize);
		// Copy the contents of test1
		// to the memory pointed to by pszReturn.
		strcpy_s(pszReturn, stSize, value);
		// Return pszReturn.
		return pszReturn;

	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void supprimerBille()
	/// @brief Supprime la bille en jeu (mode test).
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl supprimerBille()
	{
		FacadeModele::obtenirInstance()->supprimerBille();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void modePause(bool pause)
	/// @brief Active ou desactive le mode pause.
	/// @param[in] pause : Activation ou desactivation.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl modePause(bool pause)
	{
		FacadeModele::obtenirInstance()->setPause(pause);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn bool spotLight(int lum, bool state)
	/// @brief Active ou desactive la lumiere
	/// @param[in] lum : Type de lumiere
	/// @param[in] state : Activation ou desactivation.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool __cdecl spotLight(int lum, bool state)
	{
		// See this for light:
		// http://www.gamedev.net/topic/564426-create-glow-with-gl_emission/
		bool debugLumiere = FacadeModele::obtenirInstance()->obtenirConfiguration()[12] && FacadeModele::obtenirInstance()->obtenirConfiguration()[10];

		if (lum > 2 || lum < 0)
			return false;
		if (debugLumiere) {
			FacadeModele::obtenirInstance()->printCurrentTime();
			std::cout << " - Lumiere(s) ";
		}
		
		if (debugLumiere)
		{
			if (state == true)
			{
				std::cout << "ouverte(s)" << std::endl;
			}
			else
			{
				std::cout << "fermee(s)" << std::endl;
			}
		}

		FacadeModele::obtenirInstance()->setLight(lum, state);

		return true;
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirNombreDePointsDePartie()
	/// @brief Retourne le nombre de points courant dans la partie.
	/// @return Le nombre de points courant dans la partie.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirNombreDePointsDePartie(int colorshift)
	{
		return FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->getPointsJoueur(colorshift);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void resetNombreDePointsDePartie()
	/// @brief Reinitialise le nombre de points dans la partie.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl resetNombreDePointsDePartie()
	{
		FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->setPointsJoueur(0);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn int obtenirNombreBillesCourante()
	/// @brief Retourne le nombre de billes courantes.
	/// @return Le nombre de billes courantes.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int __cdecl obtenirNombreBillesCourante(int colorshift)
	{
		return FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->obtenirNombreBilleCourante(colorshift);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void resetNombreBillesCourantes()
	/// @brief Reinitialise le nombre de billes courantes.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl resetNombreBillesCourantes()
	{
		FacadeModele::obtenirInstance()->obtenirGlobalesPartie()->resetBilles();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void compresserRessort()
	/// @brief Compresser le ressort.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl compresserRessort(int colorshift)
	{
		FacadeJeu::obtenirInstance()->compresserRessort(colorshift);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void relacherRessort()
	/// @brief Relacher le ressort.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl relacherRessort(int colorshift)
	{
		FacadeJeu::obtenirInstance()->relacherRessort(colorshift);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void animerJeu(bool animer)
	/// @brief Active ou desactive l'animation du jeu.
	/// @param[in] animer : Valeur d'ativation ou de desactivation.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl animerJeu(bool animer)
	{
		FacadeModele::obtenirInstance()->assignerAnimer(animer);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void activerAI(bool actif)
	/// @brief Active ou desactive le joueur virtuel (AI).
	/// @param[in] actif : Valeur d'ativation ou de desactivation.
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl activerAI(bool actif, int joueur)
	{
		FacadeJeu::obtenirInstance()->activerAI(actif, joueur);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void refreshText(int x, int y)
	/// @brief Rafraichit la position du texte
	/// @param[in] x : Taille max de la fenetre en x
	/// @param[in] y : Taille max de la fenetre en y
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl refreshText(int x, int y)
	{
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->refresh(x, y);
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @fn void suprimerAllText()
	/// @brief Supprime tous les textes
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl suprimerAllText()
	{
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->suprimerAllText();
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @fn void creeTexte(char* text, char* font)
	/// @brief Cree le texte
	/// @param[in] text : Le texte a modifier
	/// @param[in] font : La font a utiliser
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl creeTexte(char* text, int, char* font, int)
	{
		std::string myText = std::string(text);
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->creeTexte(myText, font);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void updateText(char* oldText, int, char* newText, int)
	/// @brief Modifie un texte existant
	/// @param[in] oldText : Le texte a modifier
	/// @param[in] newText : La texte apres modification
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl updateText(char* oldText, int, char* newText, int)
	{
		std::string myOldText = std::string(oldText);
		std::string myNewText = std::string(newText);
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->updateText(myOldText, myNewText);
	}
	

	///////////////////////////////////////////////////////////////////////////////
	/// @fn void resize(char* text, int, unsigned int size)
	/// @brief Modifie la taille du texte
	/// @param[in] text : Le texte a modifier
	/// @param[in] size : La taille a appliquer au text
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl resize(char* text, int, int size)
	{
			std::string myText = std::string(text);
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->resize(myText, (unsigned int)size);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void changerCouleurV(char* text, int, float couleur[3])
	/// @brief Change la couleur du texte
	/// @param[in] text : Le texte a modifier
	/// @param[in] couleur : La couleur a appliquer (en RGB)
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl changerCouleurV(char* text, int, float couleur[3])
	{
		std::string myText = std::string(text);
		glm::fvec3 couleurV(couleur[0], couleur[1], couleur[2]);
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->changerCouleurV(myText, couleurV);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void repositionner(char* text, int, int x, int y)
	/// @brief Modifie la position du texte
	/// @param[in] text : Le texte a modifier
	/// @param[in] x : La position du texte en x
	/// @param[in] y : La position du texte en y
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl repositionner(char* text, int, float x, float y)
	{
		std::string myText = std::string(text);
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->repositionner(myText, x, y);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void afficherTextes(bool afficher)
	/// @brief Affiche ou non tout les textes
	/// @param[in] afficher : L'etat d'affichage
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl afficherTextes(bool afficher)
	{
		FacadeModele::obtenirInstance()->obtenircontroleurTexte()->afficherTextes(afficher);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void preparerUsineArbre(char* text, int)
	/// @brief Cree une usine
	/// @param[in] text L'usine a cree
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void __cdecl preparerUsineArbre(char* text, int)
	{
		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->preparerUsine(std::string(text));
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void utiliserCameraOrbite(bool utiliseOrbite)
	/// @brief Change l'etat de la camera
	/// @param[in] utiliseOrbite : La valeur de l'etat a utiliser
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void utiliserCameraOrbite(bool utiliseOrbite)
	{
		FacadeModele::obtenirInstance()->utiliserCameraOrbite(utiliseOrbite);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void sauvegarderHistorique()
	/// @brief Sauvegarde l'etat de l'arbre de rendu
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void sauvegarderHistorique()
	{
		FacadeEditeur::obtenirInstance()->sauvegarderHistorique();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void annulerModifications()
	/// @brief Annule les modifications et restaure l'arbre de rendu
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void annulerModifications()
	{
		FacadeEditeur::obtenirInstance()->annulerModifications();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void retablirModifications()
	/// @brief Retablit les modifications et restaure l'arbre de rendu
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void retablirModifications()
	{
		FacadeEditeur::obtenirInstance()->retablirModifications();
	}
	

	///////////////////////////////////////////////////////////////////////////////
	/// @fn void viderHistorique()
	/// @brief Vide l'historique des dernieres modifications
	/// @return Aucune.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void viderHistorique()
	{
		FacadeEditeur::obtenirInstance()->viderHistorique();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void obtenirNombreSelection()
	/// @brief Retourne le nombre d'objets de l'arbre de rendu qui sont selectionnes
	/// @return int, le nombre d'objets selectiones.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int obtenirNombreSelection()
	{
		return FacadeEditeur::obtenirInstance()->obtenirNombreSelection();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn bool possedeSuivant()
	/// @brief Retourne vrai s'il existe une sauvegarde suivante dans l'historique
	/// @return bool, true s'il existe une sauvegarde suivante dans l'historique.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool possedeSuivant()
	{
		return FacadeEditeur::obtenirInstance()->possedeSuivant();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn bool possedePrecedent()
	/// @brief Retourne vrai s'il existe une sauvegarde precedente dans l'historique
	/// @return bool, true s'il existe une sauvegarde precedente dans l'historique.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool possedePrecedent()
	{
		return FacadeEditeur::obtenirInstance()->possedePrecedent();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn bool sourisEstSurObjet(int i, int j, int hauteur, int largeur, bool& estSelectionne)
	/// @brief Retourne vrai si la souris se situe sur un objet deja selectionne.
	/// @return bool, true si la souris se situe sur un objet deja selectionne.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool sourisEstSurObjet(int i, int j, int hauteur, int largeur, bool& estSelectionne)
	{
		return FacadeEditeur::obtenirInstance()->sourisEstSurObjet(i, j, hauteur, largeur, estSelectionne);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn bool cameraEstOrbite()
	/// @brief Retourne vrai si la ve est en perspective / la camera est orbite
	/// @return bool, true si la camera est en mode orbite
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool cameraEstOrbite()
	{
		return FacadeModele::obtenirInstance()->cameraEstOrbite();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void SendChatMessage(char* lobbyName, char* chatMessage)
	/// @brief Envoie les messages entres par l'utilisateur du C#
	/// @return bool, true si la souris se situe sur un objet deja selectionne.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void SendChatMessage(const char* lobbyName, const char* chatMessage)
	{
		std::string myMessage(chatMessage);
		std::string lobbyRoom(lobbyName);

		FacadeReseau::obtenirInstance()->SendChatMessage(lobbyName, chatMessage);	
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void GetLobbies()
	/// @brief Va chercher les lobbies
	/// @return char*, tous les lobbies
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char* GetLobbies()
	{
		return FacadeReseau::obtenirInstance()->GetLobbies();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void GetChatHistoryUpdates()
	/// @brief Va chercher les messages recus par le client
	/// @return aucun.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool GetChatHistoryUpdates()
	{
		return FacadeReseau::obtenirInstance()->GetChatHistoryUpdates();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void GetAllMessages(char* lobbyName)
	/// @brief Va chercher les tous les messages d'une room
	/// @return aucun.
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char* GetAllMessages(char* lobbyName)
	{
		return FacadeReseau::obtenirInstance()->GetAllMessages(lobbyName);
	}
	

	///////////////////////////////////////////////////////////////////////////////
	/// @fn void GetMessages(char* lobbyName)
	/// @brief Va chercher les messages recus par le client
	/// @return char*, les messages du serveur
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char* GetMessages(char* lobbyName)
	{
		return FacadeReseau::obtenirInstance()->GetMessages(lobbyName);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void bool LogIn(char* username, char* password)
	/// @brief Permet de se connecter au serveur.
	/// @return bool, true si l'authentification est reussie
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool LogIn(char* username, char* password)
	{
		return FacadeReseau::obtenirInstance()->LogIn(username, password);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void bool LogOff()
	/// @brief Permet de se deconnecter du compte utilisateur du serveur.
	/// @return bool, true si la deconnexion est reussie
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool LogOff()
	{
		return FacadeReseau::obtenirInstance()->LogOff();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void bool DisconnectFromServer()
	/// @brief Permet de se deconnecter du serveur.
	/// @return bool, true si la deconnexion est reussie
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool DisconnectFromServer()
	{
		return FacadeReseau::obtenirInstance()->DisconnectFromServer();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void bool CreateAccount(char* userName, char* password, char* email)
	/// @brief Permet de creer un compte.
	/// @param[in] username : Le nom de l'utilisateur
	/// @param[in] password : Le mot de passe de l'utilisateur
	/// @param[in] email : Le courriel de l'utilisateur
	/// @return bool, true si l'authentification est reussie
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool CreateAccount(char* username, char* password, char* email)
	{
		return FacadeReseau::obtenirInstance()->CreateAccount(username, password, email);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void bool SendIP(char* ipAddress)
	/// @brief Permet d'obtenir l'addresse IP entree en c#
	/// @param[in] ipAddress : L'addresse IP
	/// @return bool, true si l'authentification est reussie
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool SendIP(char* ipAddress)
	{
		return FacadeReseau::obtenirInstance()->SendIP(ipAddress);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void GetMessages(char* lobbyName)
	/// @brief Va chercher les messages recus par le client
	/// @return char*, les messages du serveur
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char* InitializeOffline()
	{
		return FacadeReseau::obtenirInstance()->InitializeOffline();
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void obtenirInfoCompte()
	/// @brief Va chercher les messages recus par le client
	/// @return char*, les messages du serveur
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char* obtenirInfoCompte()
	{
		std::string name = FacadeReseau::obtenirInstance()->obtenirInfoCompte();
		const char* value = name.c_str();
		size_t stSize = strlen(value) + sizeof(char);

		char* pszReturn = nullptr;

		pszReturn = static_cast<char*>(::CoTaskMemAlloc(stSize));
		// Copy the contents of test1
		// to the memory pointed to by pszReturn.
		strcpy_s(pszReturn, stSize, value);
		// Return pszReturn.
		return pszReturn;
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @fn void isOnlineAccount()
	/// @brief Retourne is on est connecté en ligne
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool isOnlineAccount()
	{
		return FacadeReseau::obtenirInstance()->obtenirCompte()->isOnlineAccount();
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @fn void isCompetitiveGame()
	/// @brief Retourne si on est dans une partie competitive
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool isCompetitiveGame()
	{
		return FacadeReseau::obtenirInstance()->isCompetitif();
	}

	///////////////////////////////////////////////////////////////////////////////
	/// @fn void updateInfoCompte()
	/// @brief Va chercher les messages recus par le client
	/// @return char*, les messages du serveur
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool updateInfoCompte(char* info)
	{
		return FacadeReseau::obtenirInstance()->updateInfoCompte(info);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void requestPasswordRecovery(char * userName)
	/// @brief Va chercher les messages recus par le client
	/// @return char*, les messages du serveur
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool requestPasswordRecovery(char* userName)
	{
		return FacadeReseau::obtenirInstance()->requestPasswordRecovery(userName);
	}


	///////////////////////////////////////////////////////////////////////////////
	/// @fn void zoneValide(char * userName)
	/// @brief Retourne vrai si la zone est valide
	/// @return char*, les messages du serveur
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool zoneValide()
	{
		return FacadeEditeur::obtenirInstance()->zoneValide();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn  bool createGame(char* mapName, char* password, bool instaDeath, int gameTime)
	/// @brief Fonction qui envoie au serveur l'information d'une partie MJ a creer
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool createGame(char* mapName, char* password, bool instaDeath, int gameTime, int gameType)
	{
		return FacadeReseau::obtenirInstance()->createGame(mapName, password, instaDeath, gameTime,gameType);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn  bool startGame()
	/// @brief Fonction qui envoie au serveur l'information d'une partie MJ a creer
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) bool startGame()
	{
		return FacadeReseau::obtenirInstance()->startGame();
	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn  char* GetAvailableGames()
	/// @brief Fonction qui renvoie du serveur tous les parties disponibles
	/// @return les parties disponibles
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char* GetAvailableGames() 
	{
		std::string games =  FacadeReseau::obtenirInstance()->GetAvailableGames();
		const char* value = games.c_str();
		size_t stSize = strlen(value) + sizeof(char);

		char* pszReturn = nullptr;

		pszReturn = static_cast<char*>(::CoTaskMemAlloc(stSize));
		// Copy the contents of test1
		// to the memory pointed to by pszReturn.
		strcpy_s(pszReturn, stSize, value);
		// Return pszReturn.
		return pszReturn;
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool joinGame(char * hostName, char* mapName, char* password) 
	/// @brief Fonction qui envoie au serveur l'information d'une partie a joindre
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) bool joinGame(char * hostName, char* mapName, char* password) 
	{

		return FacadeReseau::obtenirInstance()->joinGame(hostName, mapName, password);

	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool leaveGame() 
	/// @brief Fonction qui envoie au serveur l'information d'une partie a quitter
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) bool leaveGame()
	{

		return FacadeReseau::obtenirInstance()->leaveGame();

	}



	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool matchmaking() 
	/// @brief Fonction de matchmaking
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) int matchmaking()
	{

		return FacadeReseau::obtenirInstance()->matchmaking();

	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn  char* GGetGameInfo(char* hostName, char* mapName)
	/// @brief Fonction qui renvoie du serveur l'information sur une partie
	/// @return les parties disponibles
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) char* GetGameInfo()
	{
		std::string gamesInfo = FacadeReseau::obtenirInstance()->GetGameInfo();
		const char* value = gamesInfo.c_str();
		size_t stSize = strlen(value) + sizeof(char);

		char* pszReturn = nullptr;

		pszReturn = static_cast<char*>(::CoTaskMemAlloc(stSize));
		// Copy the contents of test1
		// to the memory pointed to by pszReturn.
		strcpy_s(pszReturn, stSize, value);
		// Return pszReturn.
		return pszReturn;
	}



	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool playerIsReady(bool playerReady)
	/// @brief Fonction qui envoie au serveur si le joueur est pret ou non
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) bool playerIsReady(bool playerReady)
	{

		return FacadeReseau::obtenirInstance()->playerIsReady(playerReady);

	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool isGameStarted()
	/// @brief Fonction qui check si la partie est debute
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) bool isGameStarted()
	{

		return FacadeReseau::obtenirInstance()->isGameStarted();

	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool resetMultiplayer()
	/// @brief Fonction qui reset la partie
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) void resetMultiplayer()
	{

		return FacadeReseau::obtenirInstance()->resetMultiplayer();

	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool isGameStarted()
	/// @brief Fonction qui check si la partie est debute
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) void fonctionTest()
	{

		FacadeReseau::obtenirInstance()->fonctionTest();

	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool obtenirNumeroJoueur()
	/// @brief Fonction qui retourne le numero du joeur
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) int obtenirNumeroJoueur()
	{

		return FacadeReseau::obtenirInstance()->obtenirNumeroJoueur();

	}



	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn char*  GetPlayersInfo()
	/// @brief Fonction qui envoie au serveur si le joueur est pret ou non
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) char* GetPlayersInfo()
	{

		std::string playersInfo = FacadeReseau::obtenirInstance()->GetPlayersInfo();
		const char* value = playersInfo.c_str();
		size_t stSize = strlen(value) + sizeof(char);

		char* pszReturn = nullptr;

		pszReturn = static_cast<char*>(::CoTaskMemAlloc(stSize));
		// Copy the contents of test1
		// to the memory pointed to by pszReturn.
		strcpy_s(pszReturn, stSize, value);
		// Return pszReturn.
		return pszReturn;

	}



	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn char*  GetGameState()
	/// @brief Fonction qui envoie au serveur l'etat de la game
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) char* GetGameState()
	{

		std::string playersInfo = FacadeReseau::obtenirInstance()->GetGameState();
		const char* value = playersInfo.c_str();
		size_t stSize = strlen(value) + sizeof(char);

		char* pszReturn = nullptr;

		pszReturn = static_cast<char*>(::CoTaskMemAlloc(stSize));
		// Copy the contents of test1
		// to the memory pointed to by pszReturn.
		strcpy_s(pszReturn, stSize, value);
		// Return pszReturn.
		return pszReturn;

	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn char*  setPlayerLost()
	/// @brief Fonction qui envoie au serveur que le joueur a perdu
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) void setPlayerLost()
	{

		FacadeReseau::obtenirInstance()->setPlayerLost();

	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn char*  asHostSetPlayerLost(int index)
	/// @brief Fonction qui envoie au serveur que le joueur a perdu
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) void asHostSetPlayerLost(int index)
	{

		FacadeReseau::obtenirInstance()->asHostSetPlayerLost(index);

	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn char*  asHostSetPlayerWin(int index)
	/// @brief Fonction qui envoie au serveur que le joueur a perdu
	/// @return bool si operation reussie
	///
	///////////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) void asHostSetPlayerWin(int index)
	{

		FacadeReseau::obtenirInstance()->asHostSetPlayerWin(index);

	}


	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn char*  addShekels(int index)
	/// @brief Fonction qui ajoute des shekels au joueur
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void addShekels(unsigned int shekels)
	{
		FacadeReseau::obtenirInstance()->addShekels(shekels);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn char*  addAchievementPoints(int index)
	/// @brief Fonction qui ajoute des points de reussite
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void addAchievementPoints(unsigned int achPoints)
	{
		FacadeReseau::obtenirInstance()->addAchievementPoints(achPoints);
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn char*  prepareNextGame()
	/// @brief Fonction qui prepare la prochaine partie 
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void prepareNextGame()
	{
		FacadeReseau::obtenirInstance()->prepareNextGame();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn int  getCurrentGameIndex( )
	/// @brief Fonction qui retourne l'index de carte courante
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) int getCurrentGameIndex()
	{
		return FacadeReseau::obtenirInstance()->getCurrentGameIndex();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn char*  executeUploadMaps( )
	/// @brief Fonction qui envoie au serveur les cartes 
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void executeUploadMaps()
	{
		FacadeReseau::obtenirInstance()->executeUploadMaps();
	}

	///////////////////////////////////////////////////////////////////////////////
	///
	/// @fn char*  executeDownloadMaps( )
	/// @brief Fonction qui recoie du serveur les cartes
	///
	///////////////////////////////////////////////////////////////////////////////
	__declspec(dllexport) void executeDownloadMaps()
	{
		FacadeReseau::obtenirInstance()->executeDownloadMaps();
	}


}// FIN DU extern "C"