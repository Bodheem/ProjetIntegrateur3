using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Text;
using System;
using InterfaceGraphique.Fenetres;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class FonctionsNatives
    /// @brief Classe qui importe les fontions natives C++.
    /// @author Inconnu
    /// @date Inconnue
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    static class FonctionsNatives
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct Message
        {
            public IntPtr hWnd;
            public uint Msg;
            public IntPtr wParam;
            public IntPtr lParam;
            public uint Time;
            public System.Drawing.Point Point;
        }

        [DllImport(@"User32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool PeekMessage(out Message message, IntPtr hWnd, uint filterMin, uint filterMax, uint flags);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void libererModele();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void redimensionnerFenetre(int largeur, int hauteur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void translater(double deplacementX, double deplacementY);

        #region OpenGL

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserOpenGL(IntPtr handle);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void libererOpenGL();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void dessinerOpenGL();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animer(double temps);

        #endregion

        #region Sauvegarde et Initialisation

        [DllImport(@"Noyau.dll", EntryPoint = "obtenirPropriete", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string obtenirPropriete(StringBuilder nomFichier, int length);


        [DllImport(@"Noyau.dll", EntryPoint = "obtenirPropriete", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string obtenirPropriete();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string sauvegarderZone(StringBuilder path, int pathLength, StringBuilder proprietes, int proprietesLength);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void chargerZone(StringBuilder path, int pathLength);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int takeScreenShot(StringBuilder path, int taille, bool square = false, int maxSize = 0);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirDifficulte(StringBuilder path, int length);

        #endregion

        #region Configuration et Campagne

        [DllImport(@"Noyau.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string obtenirDerniereCampagne();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void creerFichierConfig(int[] config);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr chargerFichierConfiguration();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void creerFichierCampagne(StringBuilder listMaps, int length);


        #endregion

        #region Historique de modification

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void sauvegarderHistorique();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void annulerModifications();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void retablirModifications();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void viderHistorique();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool possedeSuivant();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool possedePrecedent();

        #endregion

        #region Zoom

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomIn();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomOut();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomInElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void zoomOutElastique(int xCoin1, int yCoin1, int xCoin2, int yCoin2);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double obtenirZoomCourant();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool resetZoom();

        #endregion

        #region Textes

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void afficherTextes(bool afficher = true);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void refreshText(int x, int y);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void creeTexte(StringBuilder text, int lengthT, StringBuilder font, int lengthF);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void updateText(StringBuilder textOld, int lengthO, StringBuilder textNew, int lengthN);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void suprimerAllText();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void resize(StringBuilder text, int length, int size);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void changerCouleurV(StringBuilder text, int length, float[] couleur);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void repositionner(StringBuilder text, int length, float x, float y);

        #endregion
        
        #region Sons

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserSon();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void jouerSon(StringBuilder name, int length, bool pause = false);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void mute(StringBuilder name, int length, bool mute);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void bouclerSon(StringBuilder name, int length, bool loop = true);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ajusterVolume(StringBuilder name, int length, float pourcentage);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void arreterToutSons();

        #endregion

        #region Edition

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int selectionMultiple(bool c);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deselectAll();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void selectAll();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void deplacerSelection(int x1, int y1, int x2, int y2, bool duplication);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void agrandirSelection(int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void dupliquerSelection(int i, int j);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void removeObject();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void creerMur(int originX, int originY, int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool duplicationEstHorsTable();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getPositionX();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getPositionY();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getAngle();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getScale();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool zoneValide();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void creerObjet(StringBuilder value, int length, bool isTwin = false, int colorShift = 0);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool creerObjetAvecTests(StringBuilder value, int length, bool isTwin, bool colorShift, int posX, int posY, int posZ, float angleX, float angleY, float angleZ);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int selectionnerObjetSousPointClique(int i, int j, int hauteur, int largeur, bool ctrlDown = false, bool gaucheEnfonce = false, bool sourisSurSelection = false);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void tournerSelectionSouris(int x1, int y1, int x2, int y2);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreSelection();

        #endregion

        #region Touches

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirTouchePGJ1();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirTouchePGJ2();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirTouchePDJ1();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirTouchePDJ2();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirToucheRessort();

        #endregion

        #region Joueur Virtuel

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void activerAI(bool actif, int joueur = 2);

        #endregion

        #region Reseau

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SendChatMessage(byte[] lobbyName, byte[] chatMessage);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string GetLobbies();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string GetMessages(StringBuilder lobbyName);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string GetAllMessages(StringBuilder lobbyName);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool LogIn(StringBuilder userName, StringBuilder password);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool isOnlineAccount();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool isCompetitiveGame();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool LogOff();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool DisconnectFromServer();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool GetChatHistoryUpdates();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool CreateAccount(StringBuilder userName, StringBuilder password, StringBuilder email);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool SendIP(StringBuilder ipAddress);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string InitializeOffline();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string getUserName();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string obtenirInfoCompte();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool updateInfoCompte(StringBuilder info);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool requestPasswordRecovery(StringBuilder userName);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool isGameStarted();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void leaveMultiplayerGame();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void fonctionTest();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void addShekels(int shekels);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void addAchievementPoints(int achPoints);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void prepareNextGame();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getCurrentGameIndex();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void executeDownloadMaps();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void executeUploadMaps();

        #endregion

        #region Reseau_Gameplay

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool createGame(StringBuilder mapName, StringBuilder password, bool instaDeath = false, int time = -5, int gametype = 1);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool startGame();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void resetMultiplayer();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setPlayerLost();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void asHostSetPlayerLost(int index);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void asHostSetPlayerWin(int index);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNumeroJoueur();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool playerIsReady(bool playerReady);


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool joinGame(StringBuilder hostName, StringBuilder mapName, StringBuilder password);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool leaveGame();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string GetAvailableGames();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string GetGameInfo();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string GetPlayersInfo();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string GetGameState();


        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int matchmaking();



        #endregion

        #region Camera

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void utiliserCameraOrbite(bool utiliseOrbite);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool cameraEstOrbite();

        #endregion

        #region Activation/Desactivation des palettes

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void activerPalettesGauches(int colorshift = 0);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void desactiverPalettesGauches(int colorshift = 0);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void activerPalettesDroites(int colorshift = 0);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void desactiverPalettesDroites(int colorshift = 0);

        #endregion

        #region Mode Jeu

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void compresserRessort(int colorshift = 0);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void relacherRessort(int colorshift = 0);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void animerJeu(bool animer);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreDePointsDePartie(int colorshift = 0);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void resetNombreDePointsDePartie();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreBillesCourante(int colorshift = 0);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirModeDoubleBille();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreDeBilles();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void resetNombreBillesCourantes();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirNombreBillesPerdus(int colorshift = 0);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string obtenirBonus();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string obtenirMalus();

        #endregion

        #region Rectangle elastique

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void rectangleElastique(int i, int j);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initialiserRectangleElastique(int i, int j);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void terminerRectangleElastique();

        #endregion

        #region Fonts

        [System.Runtime.InteropServices.DllImport("gdi32.dll")]
        public static extern IntPtr AddFontMemResourceEx(IntPtr pbFont, uint cbFont,
            IntPtr pdv, [System.Runtime.InteropServices.In] ref uint pcFonts);

        #endregion

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void obligerTransparence(bool transparence);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAsAttribute(UnmanagedType.I1)]
        public static extern bool setProprietesNoeud(int x, int y, int angle, double scale);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void supprimerBille();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void modePause(bool pause);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool spotLight(int lum, bool state);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int obtenirAffichageGlobal();

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void bloquerAffichageGlobal(int active);

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool sourisEstSurObjet(int i, int j, int hauteur, int largeur, out bool estSelectionne);

        public static void populateUsines()
        {
            Console.WriteLine("Creation de l'arbre de rendu...");
            Program.loadingBar.populateLoadingBar();
        }

        [DllImport(@"Noyau.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void preparerUsineArbre(StringBuilder text, int length);
    }
}
