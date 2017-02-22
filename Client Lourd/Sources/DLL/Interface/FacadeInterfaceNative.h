////////////////////////////////////////////////
/// @file   FacadeInterfaceNative.h
/// @author INF2990
/// @date   2014-08-16
/// @ingroup Interface
////////////////////////////////////////////////

/** @defgroup Interface Interface
*	@ingroup Noyau
*/

#ifndef __FACADE_INTERFACE_NATIVE_H__
#define __FACADE_INTERFACE_NATIVE_H__

extern "C" {

	__declspec(dllexport) void libererModele();

	#pragma region OpenGL

	__declspec(dllexport) void initialiserOpenGL(int * handle);
	__declspec(dllexport) void libererOpenGL();
	__declspec(dllexport) void dessinerOpenGL();
	__declspec(dllexport) void animer(double temps);

	#pragma endregion 

	#pragma region Sauvegarde et initialisation

	__declspec(dllexport) char* obtenirPropriete();
	__declspec(dllexport) char* sauvegarderZone(char* nomFichier, int nomLength, char* proprietes, int proprietesLength);
	__declspec(dllexport) void chargerZone(char* nomFichier, int nomLength);
	__declspec(dllexport) void takeScreenShot(char* path, int length, bool square, int maxSize);
	__declspec(dllexport) int obtenirDiffulte(char* nomFichier, int length);

	#pragma endregion

	#pragma region Configuration et Campagne

	__declspec(dllexport) void creerFichierConfig(int config[14]);
	__declspec(dllexport) int* chargerFichierConfiguration();
	__declspec(dllexport) void creerFichierCampagne(char* nomFichier, int length);
	__declspec(dllexport) char* obtenirDerniereCampagne();

	#pragma endregion

	#pragma region Historique de modification

	__declspec(dllexport) void sauvegarderHistorique();
	__declspec(dllexport) void annulerModifications();
	__declspec(dllexport) void retablirModifications();
	__declspec(dllexport) void viderHistorique();
	__declspec(dllexport) bool possedeSuivant();
	__declspec(dllexport) bool possedePrecedent();

	#pragma endregion

	#pragma region Zoom

	__declspec(dllexport) void zoomInElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2);
	__declspec(dllexport) void zoomOutElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2);
	__declspec(dllexport) bool resetZoom(void);
	__declspec(dllexport) double obtenirZoomCourant(void);
	__declspec(dllexport) void zoomIn();
	__declspec(dllexport) void zoomOut();

	#pragma endregion 

	#pragma region Textes

	__declspec(dllexport) void afficherTextes(bool afficher = true);
	__declspec(dllexport) void refresh(int x, int y);
	__declspec(dllexport) void creeTexte(char* text, int lengthT, char* font, int lengthF);
	__declspec(dllexport) void updateText(char* oldText, int lengthO, char* newText, int lengthN);
	__declspec(dllexport) void resize(char* text, int length, int size);
	__declspec(dllexport) void changerCouleurV(char* text, int length, float couleur[3]);
	__declspec(dllexport) void repositionner(char* text, int length, float x, float y);
	__declspec(dllexport) void suprimerAllText();

	#pragma endregion 

	#pragma region Sons

	__declspec(dllexport) void initialiserSon();
	__declspec(dllexport) void jouerSon(char* value, int length, bool pause = false);
	__declspec(dllexport) void bouclerSon(char* value, int length, bool loop = true);
	__declspec(dllexport) void ajusterVolume(char* value, int length, float pourcentage);
	__declspec(dllexport) void mute(char* value, int, bool mute);
	__declspec(dllexport) void arreterToutSons();

	#pragma endregion 

	#pragma region Edition

	__declspec(dllexport) int selectionMultiple(bool c);
	__declspec(dllexport) void deselectAll(void);
	__declspec(dllexport) void selectAll(void);
	__declspec(dllexport) void deplacerSelection(int x1, int y1, int x2, int y2, bool duplication);
	__declspec(dllexport) void agrandirSelection(int x1, int y1, int x2, int y2);
	__declspec(dllexport) void dupliquerSelection(int i, int j);
	__declspec(dllexport) void removeObject(void);
	__declspec(dllexport) void creerMur(int originX, int originY, int x1, int y1, int x2, int y2);
	__declspec(dllexport) bool duplicationEstHorsTable();
	__declspec(dllexport) double getPositionX(void);
	__declspec(dllexport) double getPositionY(void);
	__declspec(dllexport) double getAngle(void);
	__declspec(dllexport) double getScale(void);
	__declspec(dllexport) bool zoneValide();

	#pragma endregion	

	#pragma region Touches

	__declspec(dllexport) int obtenirTouchePGJ1();
	__declspec(dllexport) int obtenirTouchePGJ2();
	__declspec(dllexport) int obtenirTouchePDJ1();
	__declspec(dllexport) int obtenirTouchePDJ2();
	__declspec(dllexport) int obtenirToucheRessort();

	#pragma endregion

	#pragma region Joueur Virtuel

	__declspec(dllexport) void activerAI(bool actif, int joueur = 2);

	#pragma endregion 

	#pragma region Reseau

	__declspec(dllexport) void SendChatMessage(const char* lobbyName, const char* chatMessage);
	__declspec(dllexport) char* GetLobbies();
	__declspec(dllexport) char* GetMessages(char* lobbyName);
	__declspec(dllexport) char* GetAllMessages(char* lobbyName);
	__declspec(dllexport) bool GetChatHistoryUpdates();
	__declspec(dllexport) bool LogIn(char* username, char* password);
	__declspec(dllexport) bool LogOff();
	__declspec(dllexport) bool DisconnectFromServer();
	__declspec(dllexport) bool CreateAccount(char* username, char* password, char* email);
	__declspec(dllexport) bool SendIP(char* ipAddress);
	__declspec(dllexport) char* obtenirInfoCompte();
	__declspec(dllexport) bool updateInfoCompte(char* info);
	__declspec(dllexport) bool requestPasswordRecovery(char* userName);
	__declspec(dllexport) void setPlayerLost();
	__declspec(dllexport) void asHostSetPlayerLost(int index);
	__declspec(dllexport) void asHostSetPlayerWin(int index);
	__declspec(dllexport) void addShekels(unsigned int shekels);
	__declspec(dllexport) void addAchievementPoints(unsigned int achPoints);
	__declspec(dllexport) void prepareNextGame();
	__declspec(dllexport) int getCurrentGameIndex();
	__declspec(dllexport) void executeUploadMaps();
	__declspec(dllexport) void executeDownloadMaps();


	__declspec(dllexport) bool isOnlineAccount();
	__declspec(dllexport) bool isCompetitiveGame();

	__declspec(dllexport) char* getUserName();
	__declspec(dllexport) char* obtenirBonus();
	__declspec(dllexport) char* obtenirMalus();





	#pragma endregion

	#pragma region Camera

	__declspec(dllexport) bool cameraEstOrbite();
	__declspec(dllexport) void utiliserCameraOrbite(bool utiliseOrbite);
	__declspec(dllexport) void orbite(double phi, double theta);

	#pragma endregion 

	#pragma region Activation/Desactivation des palettes

	__declspec(dllexport) void activerPalettesGauches(int colorshift);
	__declspec(dllexport) void desactiverPalettesGauches(int colorshift);
	__declspec(dllexport) void activerPalettesDroites(int colorshift);
	__declspec(dllexport) void desactiverPalettesDroites(int colorshift);
	__declspec(dllexport) void compresserRessort(int colorshift);
	__declspec(dllexport) void relacherRessort(int colorshift);

	#pragma endregion 

	#pragma region Mode Jeu

	__declspec(dllexport) void animerJeu(bool animer);
	__declspec(dllexport) int obtenirNombreDePointsDePartie(int colorshift = 0);
	__declspec(dllexport) void resetNombreDePointsDePartie();
	__declspec(dllexport) int  obtenirNombreBillesCourante(int colorshift = 0);
	__declspec(dllexport) int obtenirModeDoubleBille();
	__declspec(dllexport) int obtenirNombreDeBilles();
	__declspec(dllexport) void resetNombreBillesCourantes();

	#pragma endregion

	#pragma region Rectangle elastique

	__declspec(dllexport) void rectangleElastique(int i, int j);
	__declspec(dllexport) void initialiserRectangleElastique(int i, int j);
	__declspec(dllexport) void terminerRectangleElastique();

	#pragma endregion


	#pragma region Multiplayer

	__declspec(dllexport) bool createGame(char* mapName, char* password, bool instaDeath, int gameTime, int gameType);
	__declspec(dllexport) bool startGame();
	__declspec(dllexport) char* GetAvailableGames();
	__declspec(dllexport) bool joinGame(char * hostName, char* mapName, char* password);
	__declspec(dllexport) bool leaveGame();
	__declspec(dllexport) int matchmaking();
	__declspec(dllexport) char* GetGameInfo();
	__declspec(dllexport) bool playerIsReady(bool playerReady);
	__declspec(dllexport) char* GetPlayersInfo();
	__declspec(dllexport) char* GetGameState();
	__declspec(dllexport) bool isGameStarted();
	__declspec(dllexport) void resetMultiplayer();
	__declspec(dllexport) int obtenirNumeroJoueur();
	__declspec(dllexport) void fonctionTest();





	#pragma endregion



	__declspec(dllexport) void redimensionnerFenetre(int largeur, int hauteur);
	__declspec(dllexport) void translater(double deplacementX, double deplacementY);
	__declspec(dllexport) int  obtenirAffichagesParSeconde();
	__declspec(dllexport) int obtenirNombreSelection();
	__declspec(dllexport) void preparerUsineArbre(char* text, int length);
	__declspec(dllexport) void supprimerBille();
	__declspec(dllexport) bool spotLight(int lum, bool state);
	__declspec(dllexport) void creerObjet(char* value, int length, bool isTwin = false, int colorShift = 0);
	__declspec(dllexport) bool creerObjetAvecTests(char* value, int length, bool isTwin, bool colorShift, int posX, int posY, int posZ, float angleX, float angleY, float angleZ);
	__declspec(dllexport) void positionObjet(int x, int y, int z = 0);
	__declspec(dllexport) int selectionnerObjetSousPointClique(int i, int j, int largeur, int hauteur, bool ctrlDown = false, bool gaucheEnfonce = false, bool sourisSurSelection = false);
	__declspec(dllexport) void tournerSelectionSouris(int x1, int y1, int x2, int y2);
	__declspec(dllexport) bool verifierCliqueDansTable(int x, int y);
	__declspec(dllexport) void obligerTransparence(bool transparence);
	__declspec(dllexport) int obtenirCentreMasseX(void);
	__declspec(dllexport) int obtenirCentreMasseY(void);
	__declspec(dllexport) bool sourisEstSurObjet(int i, int j, int hauteur, int largeur, bool& estSelectionne);
	__declspec(dllexport) bool setProprietesNoeud(int x, int y, int angle, double scale);
	__declspec(dllexport) int obtenirNombreDeBillesPerdus();
	__declspec(dllexport) int obtenirAffichageGlobal();
	__declspec(dllexport) void bloquerAffichageGlobal(int active);
}

#endif // __FACADE_INTERFACE_NATIVE_H__
