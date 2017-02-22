//////////////////////////////////////////////////////////////////////////////
/// @file ModeJeu.cs
/// @author Ballers
/// @date 2015-03-10
/// @version 1.0 
/// @ingroup Fenetres
//////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Timers;
using System.Windows.Forms;
using InterfaceGraphique.Fenetres;
using InterfaceGraphique.Properties;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class ModeJeu
    /// @brief Classe d'interface du mode jeu.
    /// @author Ballers
    /// @date 2015-03-10
    /// @ingroup Fenetres
    ///////////////////////////////////////////////////////////////////////////
    public partial class ModeJeu : Form
    {
        private bool firstStart = true;
        private bool endGame = false;
        public PartieTerminee gameOver;     ///< Form de fin de partie
        public double currentZoom = -1;    ///< Zoom courant
        private Touches touches;            ///< Les touches pour le jeu
        private ZoneInfo zInfo;             ///< Form dinfo de prochaine zone
        private int currentZone = 0;        ///< la zone a laquelle on est rendue
        private int nbZones;                ///< nombre de Zones dans la campagne/Partie rapide
        private int nombreBillesInit = 0;   ///< Nombre de Billes initiales ( 3/5/7)
        private int nombreBillesMax;        ///< nombre maximal de billes en jeu
        List<string> myMaps;                ///< liste des zones a jouer
        StringBuilder map;                  ///< la zone en jeu
        StringBuilder nextMap;              ///< prochaine zone

        private FullScreen fullscreen = new FullScreen();
        static StringBuilder Points = new StringBuilder("Points : ");
        static StringBuilder Billes = new StringBuilder("Billes : ");
        static StringBuilder Temps = new StringBuilder("Temps: ");
        static StringBuilder Bonus = new StringBuilder("Bonus: ");
        static StringBuilder Malus = new StringBuilder("Malus: ");



        public bool multiPlayer = false;
        bool peutAnimer;
        bool boolTemp = true;               ///< bool pour ne pas spam FinDePartie
        private bool activateAmbiantLight = false; ///< Etat de la lumiere ambiante
        private bool activateDirectLight = false; ///< Etat de la lumiere directe
        private bool activateSpotLight = false; ///< Etat de la lumiere spot
        private EtatJeuAbstrait etat;

        private string GameState = "";


        public int playerColorShift = 0;
        private int pointsGagnerBille = 0;                  /// Nombre de Points pour gagner une nouvelle bille
        private int pointsGagnerPartie = 0;                 /// Nombre de Points pour gagner une zone
        private int[] pointsPartie = new int[4];            /// Nombre de points
        private int[] billesDisponibles = new int[4];       /// Billes dont le(s) joueur(s) disposent                             
        private int[] billesEnJeu = new int[4];             /// Billes qui sont sur la zone
        private int[] billesPerdus = new int[4];            /// Nombre de billes tombees dans le trou
        private int[] nombreDeBillesGagnes = new int[4];    /// Nombre de billes extras
        private int[] nombreDeZonesGagnes = new int[4];

        //private static StringBuilder informations = new StringBuilder("Appuyez sur 'h' pour afficher plus d'information");
        private static StringBuilder fontArial = new StringBuilder(@"arial.tff");
        private static StringBuilder bgm = new StringBuilder("birdsofsorrow");
        private static StringBuilder winSound = new StringBuilder("campagneWin");
        private static StringBuilder newBallSFX = new StringBuilder("newBall");

        private Dictionary<string, string> Propriete = new Dictionary<string,string>();


        // Game Modes : Timed
        private System.Timers.Timer gameTimer;
        private int initialTime;
        private int timeLeft;
        private bool timerOver = false;

        // Game Modes : Insta Death
        private bool instaDeath;

        public int panelHeight { get; set; } ///< Hauteur de la fenetre
        public int panelWidth  { get; set; }///< Largeur de la fenetre
        public Point previousP { get; set;}
        public Point currentP  { get; set;}
        
        // Modificateurs
        public void setVisibilityMenuStrip(bool vis) { menuStrip.Visible = vis; }
        public void setCurrentZoom(double val) { currentZoom = val; }
        public void setPeutAnimer(bool activation) { peutAnimer = activation; }
      


        // Accesseurs
        public double getCurrentZoom() { return currentZoom; }
        public Touches getTouches() { return touches; }
        public bool getAmbiantLight() { return activateAmbiantLight; }
        public bool getDirectLight() { return activateDirectLight; }
        public bool getSpotLight() { return activateSpotLight; }
  

        
        // Toggle des lumières
        public void toggleAmbiantLight() { activateAmbiantLight = !activateAmbiantLight; }
        public void toggleDirectLight() { activateDirectLight = !activateDirectLight; }
        public void toggleSpotLight() { activateSpotLight = !activateSpotLight; }

        // Méthodes de changement d'état
        public void pauseGame() { etat = new EtatJeuPause(this); }
        public void resumeGame() { etat = new EtatJeuJouer(this); }


        ///////////////////////////////////////////////////////////////////////////
        /// @class EtatJeuAbstrait
        /// @brief Classe interne (ModeJeu) d'etat abstrait
        /// @author Ballers
        /// @date 2015-3-10
        /// @ingroup Fenetres
        ///////////////////////////////////////////////////////////////////////////
        public partial class EtatJeuAbstrait
        {
            public EtatJeuAbstrait() { }
            public EtatJeuAbstrait(ModeJeu parent)
            {
                this.parent_ = parent;
            }
        }


        ////////////////////////////////////////////////////////////////////////
        /// @fn public ModeJeu(List<string> maps, int playerType)
        /// @brief Constructeur par parametre de la fenetre de mode jeu.
        /// @param[in] maps : Liste de zones a jouer.
        /// @param[in] playerType : Type de joueur (Solo, 2P, AI)
        /// @return Aucune (constructeur).
        ////////////////////////////////////////////////////////////////////////
        public ModeJeu(List<string> maps, int playerType, int time = -1, bool oneLife = false, bool multiplayer = false)
        {
            InitializeComponent();
            this.MouseWheel += new MouseEventHandler(panel_GL_MouseWheel);
          
            if (FonctionsNatives.obtenirModeDoubleBille() != 0)
            {
                nombreBillesMax = 2;
            }
            else
            {
                nombreBillesMax = 1;
            }


            multiPlayer = multiplayer;

            StopTimer();
            // Permet d'etablir le type de joueur
            if (multiPlayer)
            {
                QuitMPGameBtn.Visible = true;
                EtablirTouchesMultiplayer(FonctionsNatives.obtenirNumeroJoueur());
                Player1.Text = Program.playerNames[0];
                Player2.Text = Program.playerNames[1];
                if (Program.playerNames[2] == "PLAYER3")
                {
                    Player3.Visible = false;
                    points3.Visible = false;
                }
                else
                {
                    Player3.Visible = true;
                    points3.Visible = true;
                    Player3.Text = Program.playerNames[2];
                    
                }
                if (Program.playerNames[3] == "PLAYER4")
                {
                    Player4.Visible = false;
                    points4.Visible = false;
                }
                else
                {
                    Player4.Visible = true;
                    points4.Visible = true;
                    Player4.Text = Program.playerNames[3];

                }


            }
            else
            {
                EtablirTouchesEtAI(playerType);                
            }
            this.KeyDown += new KeyEventHandler(PartieRapide_KeyDown);
            this.KeyUp += new KeyEventHandler(PartieRapide_KeyUp);
            peutAnimer = true;
            Program.peutAfficher = true;
            InitialiserAnimation();
            InfoPanel.Location = new Point(
                  InfoPanel.Parent.Width / 2 - InfoPanel.Size.Width / 2,
              InfoPanel.Parent.Height / 2 - InfoPanel.Size.Height / 2);
            InfoPanel.Anchor = AnchorStyles.None;



            FonctionsNatives.resetZoom();
            currentZoom = -1;
            myMaps = new List<string>(maps);
            nbZones = maps.Count;
            if (multiplayer)
            {
                currentZone = FonctionsNatives.getCurrentGameIndex();
                if (currentZone < 0)
                    currentZone = 0;
            }
            map = new StringBuilder(myMaps[currentZone]);

            FonctionsNatives.chargerZone(map, map.Length);

            Propriete = Outils.ProprieteStringToDictionnay(FonctionsNatives.obtenirPropriete());

            resetConfig();
            FonctionsNatives.translater(-10, 0);

            //currentZone++;
            Program.tempBool = true;
            panel_GL.Focus();
            string nomMap = Path.GetFileNameWithoutExtension(map.ToString());
            label_Nom.Text = "Nom: " + nomMap;
            if (nbZones == 1)
                this.Text = "Partie Rapide: " + nomMap;
            if (nbZones > 1)
                this.Text = "Campagne: " + nomMap;
            etat = new EtatJeuDebutDePartie(this);
            // Il faut changer le mode car le traitement de début est fini
            etat = new EtatJeuJouer(this);
            FonctionsNatives.animerJeu(true);
            if (true)
            {
                StringBuilder myFont = new StringBuilder("Bloodthirsty.ttf");
                // On spécifie la font
                FonctionsNatives.creeTexte(Points, Points.Capacity, myFont, myFont.Capacity);
                FonctionsNatives.creeTexte(Billes, Billes.Capacity, myFont, myFont.Capacity);
                FonctionsNatives.creeTexte(Bonus, Bonus.Capacity, myFont, myFont.Capacity);
                FonctionsNatives.creeTexte(Malus, Malus.Capacity, myFont, myFont.Capacity);


                // On specifie la taille (en 1/72 de pouce)
                FonctionsNatives.resize(Points, Points.Capacity, 35);
                FonctionsNatives.resize(Billes, Billes.Capacity, 35);
                FonctionsNatives.resize(Bonus, Bonus.Capacity, 45);
                FonctionsNatives.resize(Malus, Malus.Capacity, 45);


                // On specifie une couleur RGB
                FonctionsNatives.changerCouleurV(Points, Points.Capacity, ColorList.COLOR_Green);
                FonctionsNatives.changerCouleurV(Billes, Billes.Capacity, ColorList.COLOR_White);
                FonctionsNatives.changerCouleurV(Bonus, Bonus.Capacity, ColorList.COLOR_Green);
                FonctionsNatives.changerCouleurV(Malus, Malus.Capacity, ColorList.COLOR_Red);



                // On specifie la position
                FonctionsNatives.repositionner(Points, Points.Capacity, 1, 1);
                FonctionsNatives.repositionner(Billes, Billes.Capacity, 1, 1);
                FonctionsNatives.repositionner(Bonus, Billes.Capacity, 1, 0);
                FonctionsNatives.repositionner(Malus, Billes.Capacity, 1, 0);




                // Mode TimeAttack
                if (time > 0)
                {
                    initialTime = time * 60;
                    timeLeft = time * 60;
                }
                if (initialTime > 0)
                {
                    FonctionsNatives.creeTexte(Temps, Temps.Capacity, myFont, myFont.Capacity);
                    FonctionsNatives.resize(Temps, Temps.Capacity, 35);
                    FonctionsNatives.changerCouleurV(Temps, Temps.Capacity, ColorList.COLOR_Yellow);
                    FonctionsNatives.repositionner(Temps, Temps.Capacity, 1, 0);
                    
                }

                // On demande d'afficher !
                FonctionsNatives.afficherTextes();
            }

            //Mode InstaDeath
            instaDeath = oneLife;

            panelHeight = panel_GL.Size.Height;
            panelWidth = panel_GL.Size.Width;


            //if (true)
            //{

            //    FonctionsNatives.creeTexte(informations, informations.Capacity, fontArial, fontArial.Capacity);
            //    FonctionsNatives.resize(informations, informations.Capacity, 12);
            //    FonctionsNatives.changerCouleurV(informations, informations.Capacity, ColorList.COLOR_dark_red);
            //    FonctionsNatives.repositionner(informations, informations.Capacity, 0, 1);
            //}

           fullscreen.EnterFullScreenMode(this);
           multiPlayerStop();

        }


        ////////////////////////////////////////////////////////////////////////
        /// @fn public void FullScreenChange()
        /// @brief Changement du mode de la fenetre( Plein Ecran ou Non).
        /// @return Aucune.
        ////////////////////////////////////////////////////////////////////////
        public void FullScreenChange()
        {
            if (fullscreen.IsFullScreen(this))
            {
                fullscreen.LeaveFullScreenMode(this);
            }
            else
            {
                fullscreen.EnterFullScreenMode(this);
            }
        }


        private void multiPlayerStop()
        {
            if (multiPlayer)
            {
                pauseGame();

            }
        }

        private void SetTimer()
        {
            if (timeLeft > 0) 
            { 
                // Create a timer with a two second interval.
                timeLeft = initialTime;
                timerOver = false;
                gameTimer = new System.Timers.Timer(1000);
                // Hook up the Elapsed event for the timer. 
                gameTimer.Elapsed += OnTimedEvent;
                gameTimer.AutoReset = true;
                gameTimer.Enabled = true;
                StringBuilder precentTemps = Temps;
                Temps = new StringBuilder("Temps : " + " ");
                FonctionsNatives.updateText(precentTemps, precentTemps.Capacity, Temps, Temps.Capacity);

            }
        }

        private void StopTimer()
        {
            if (gameTimer != null)
            {
                gameTimer.AutoReset = false;
                gameTimer.Enabled = false;
                gameTimer.Elapsed -= OnTimedEvent;
            }
        

        }

        private void OnTimedEvent(Object source, ElapsedEventArgs e)
        {
            timeLeft--;
            TimeSpan time = TimeSpan.FromSeconds(timeLeft);
            string formatedTime = string.Format("{0:D2}M:{1:D2}S",
                                 time.Minutes,
                                 time.Seconds);
            StringBuilder precentTemps = Temps;
            Temps = new StringBuilder("Temps : " + formatedTime);
            if ( timeLeft < 40)
            {
                FonctionsNatives.changerCouleurV(precentTemps, precentTemps.Capacity, ColorList.COLOR_dark_red);
                FonctionsNatives.resize(precentTemps, precentTemps.Capacity, 45);

            }
            if( timeLeft <= 0 )
            {
                StopTimer();
                timerOver = true;
            }
            FonctionsNatives.updateText(precentTemps, precentTemps.Capacity, Temps, Temps.Capacity);
        }

        ////////////////////////////////////////////////////////////////////////
        /// @fn protected void resetConfig()
        /// @brief Reset des points et aux configurations de partie.
        /// @return Aucune.
        ////////////////////////////////////////////////////////////////////////
        protected void resetConfig()
        {
            FonctionsNatives.resetNombreBillesCourantes();

            pointsGagnerPartie = Int32.Parse(Propriete[Proprietes.pointVictoire]);
            pointsGagnerBille = Int32.Parse(Propriete[Proprietes.pointBilleGratuite]);
            if (instaDeath)
            {
                nombreBillesInit = 1;
            }
            else if (multiPlayer)
            {
                nombreBillesInit = 5;
            }
            else
            {
                nombreBillesInit = FonctionsNatives.obtenirNombreDeBilles();
            }

            // Reinitialiser les données pour chaque joueur
            for (int i = 0; i < 4; ++i)
            {
                billesEnJeu[i] = 0;
                nombreDeBillesGagnes[i] = 0;
                pointsPartie[i] = 0;
                billesDisponibles[i] = nombreBillesInit;
            }

            FonctionsNatives.bouclerSon(bgm, bgm.Length);
            StringBuilder billeSound = new StringBuilder("rolling");
            FonctionsNatives.ajusterVolume(billeSound, billeSound.Length, 100);
            FonctionsNatives.jouerSon(bgm, bgm.Length);
            FonctionsNatives.ajusterVolume(bgm, bgm.Length, 60);
        }


        ////////////////////////////////////////////////////////////////////////
        /// @fn static public void InitialiserAnimation()
        /// @brief Initialise openGL et l'animation.
        /// @return Aucune.
        ////////////////////////////////////////////////////////////////////////
        public void InitialiserAnimation()
        {
            this.DoubleBuffered = false;
            this.StartPosition = FormStartPosition.WindowsDefaultBounds;
            FonctionsNatives.initialiserOpenGL(panel_GL.Handle);
            FonctionsNatives.populateUsines();
            FonctionsNatives.dessinerOpenGL();

        }


        ////////////////////////////////////////////////////////////////////////
        /// @fn public void MettreAJour(double tempsInterAffichage)
        /// @brief Mise a jour du panneau OpenGL.
        /// @param[in] tempsInterAffichage : Objet duquel provient un evenement.
        /// @return Aucune.
        ////////////////////////////////////////////////////////////////////////
        public void MettreAJour(double tempsInterAffichage)
        {
            try
            {
                this.Invoke((MethodInvoker)delegate
                {
                    FonctionsNatives.refreshText(panel_GL.Size.Width, panel_GL.Size.Height);
                    if (peutAnimer)
                    {
                        FonctionsNatives.animer(tempsInterAffichage);
                        if (Program.compteurFrames == 0)
                        {
                            // Chercher le nombre de points de tous les joueurs
                            for (int i = 0; i < 4; ++i)
                            {
                                pointsPartie[i] = FonctionsNatives.obtenirNombreDePointsDePartie(i);
                                                                
                            }
                            points1.Text = pointsPartie[0].ToString();
                            points2.Text = pointsPartie[1].ToString();
                            points3.Text = pointsPartie[2].ToString();
                            points4.Text = pointsPartie[3].ToString();



                            StringBuilder precedentText = Points;
                            if (multiPlayer)
                            {
                                playerColorShift = FonctionsNatives.obtenirNumeroJoueur() - 1;
                                Points =
                                    new StringBuilder("Points : " +
                                                      pointsPartie[playerColorShift].ToString());
                            }
                            else
                            {
                                Points = new StringBuilder("Points : " + pointsPartie[0].ToString());
                            }
                            FonctionsNatives.updateText(precedentText, precedentText.Capacity, Points, Points.Capacity);
                        }
                    }
                    if (Program.compteurFrames == 0)
                    {
                        FonctionsNatives.dessinerOpenGL();
                    }

                    if (multiPlayer)
                    {
                        GameState = FonctionsNatives.GetGameState();                        
                    }
                    //Console.WriteLine(GameState);
                    if (etat is EtatJeuPause && multiPlayer && (GameState == "GAME_"))
                    {
                        etat  = new EtatJeuJouer(this);
                        Console.WriteLine("STARTING GAME");
                        if (initialTime > 0)
                        {
                            SetTimer();
                        }
                    }
                    if (multiPlayer && (GameState == "LOSE_") && !endGame)
                    {
                        endGame = true;
                        Program.player = new System.Media.SoundPlayer(Properties.Resources.gOver);
                        Program.player.Play();
                        //MultiPlayerLabel.Text = "EVERYONE FUCKING LOST";
                        MultiPlayerLabel.Location = new Point(
                            Width / 2 - MultiPlayerLabel.Width / 2,
                            Height / 2 - MultiPlayerLabel.Height / 2);
                        AfficherInformations();
                        if (nbZones > 1)
                        {
                            FonctionsNatives.addShekels(20);
                        }
                        else
                        {
                            AddPoints();                            
                        }
                        etat = new EtatJeuPause(this);
                        //Thread.Sleep(2000);
                    }
                    if (multiPlayer && (GameState == "WIN__") && !endGame)
                    {
                        endGame = true;
                        Program.player = new System.Media.SoundPlayer(Properties.Resources.gOver);
                        Program.player.Play();
                        AfficherInformations();
                        if (nbZones > 1)
                        {
                            AddCampaignPoints();
                        }
                        etat = new EtatJeuPause(this);
                    }
                    if (GameState == "DISCO")
                    {
                        Console.WriteLine("ERROR 37");
                        MultiPlayerLabel.Text = "ERROR 37";
                        MultiPlayerLabel.Location = new Point(
                            Width / 2 - MultiPlayerLabel.Width / 2,
                            Height / 2 - MultiPlayerLabel.Height / 2);
                        //Thread.Sleep(2000);
                        mPrincipal_menu.PerformClick();
                    }

                    for (int i = 0; i < 4; ++i)
                    {
                        #region WhyTheFuckIsThisHere

                        billesEnJeu[i] = FonctionsNatives.obtenirNombreBillesCourante(i);
                        billesPerdus[i] = FonctionsNatives.obtenirNombreBillesPerdus(i);

                        if (instaDeath)
                        {
                            if (billesPerdus[i] < 0)
                            {
                                billesDisponibles[i] = 0;
                            }
                            else
                            {
                                 billesDisponibles[i] = 1 - billesPerdus[i];
                            }

                        }
                        else
                        {
                                billesDisponibles[i] = nombreBillesInit + nombreDeBillesGagnes[i] - billesPerdus[i] - billesEnJeu[i];
                        }





                        if (billesEnJeu[i] < nombreBillesMax && (billesDisponibles[i] > 0))
                        {
                            CreerBille(i);
                        }

                       

                        if (pointsPartie[i] >= nombreDeBillesGagnes[i] * pointsGagnerBille + pointsGagnerBille)
                        {
                            FonctionsNatives.jouerSon(newBallSFX, newBallSFX.Length);
                            nombreDeBillesGagnes[i]++;
                        }

                       

                        if (pointsPartie[i] >= pointsGagnerPartie && boolTemp && (nbZones > 1))
                        {
                            if (currentZone >= nbZones-1)
                            {
                                if (multiPlayer)
                                {
                                    if (!endGame)
                                    {

                                        if (playerColorShift == 0)
                                        {
                                            for (int j = 0; j < 4; j++)
                                            {
                                                FonctionsNatives.asHostSetPlayerWin(j + 1);
                                            }    
                                        }
                                        
                                    }
                                    else
                                    {
                                        // it should loop here until end of times
                                        //etat = new EtatJeuPause(this);
                                    }
                                    
                                }
                                else
                                {
                                    FinCampagne(true, -5);                                    
                                }
                            }
                            else
                            {
                                ProchainePartie();
                            }
                        }

                        if (playerColorShift == 0 && multiPlayer)
                        {
                            if (billesDisponibles[i] == 0 && boolTemp && billesEnJeu[i] == 0 || (boolTemp && timerOver))
                            {
                               FonctionsNatives.asHostSetPlayerLost(i + 1);       
                            } 
                        }

                        #endregion
                    }

                    if (currentZoom <= 0)
                    {
                        FonctionsNatives.resetZoom();
                        currentZoom = FonctionsNatives.obtenirZoomCourant();
                    }

                    #region BONUS_MALUS

                    //StringBuilder precedentBonus = Bonus;
                    //Bonus = new StringBuilder("Bonus : " + FonctionsNatives.obtenirBonus());
                    //if(Bonus != precedentBonus)
                    //    FonctionsNatives.updateText(precedentBonus, precedentBonus.Capacity, Bonus, Bonus.Capacity);
                    //StringBuilder precedentMalus = Malus;
                    //Malus = new StringBuilder("Malus : " + FonctionsNatives.obtenirMalus());
                    //if (Malus != precedentMalus)
                    //    FonctionsNatives.updateText(precedentMalus, precedentMalus.Capacity, Malus, Malus.Capacity);

                    #endregion

                    if (billesDisponibles[playerColorShift] >= 0)
                    {
                        StringBuilder precedentText = Billes;

                        if (multiPlayer)
                        {
                            Billes =
                                new StringBuilder("Billes : " +
                                                  billesDisponibles[playerColorShift].ToString());

                        }
                        else
                        {
                            Billes = new StringBuilder("Billes : " + billesDisponibles[0].ToString());


                        }
                        FonctionsNatives.updateText(precedentText, precedentText.Capacity, Billes, Billes.Capacity);
                    }

                    if (billesDisponibles[playerColorShift] == 0 && boolTemp && billesEnJeu[playerColorShift] == 0 || (boolTemp && timerOver))
                    {
                        if (multiPlayer)
                        {
                            if (!endGame)
                            {
                                MultiPlayerLabel.Text = "VOUS AVEZ PERDU "/* + playerColorShift*/;
                                MultiPlayerLabel.Location = new Point(
                                    Width / 2 - MultiPlayerLabel.Width / 2,
                                    Height / 2 - MultiPlayerLabel.Height / 2);
                                // en theorie disable les palettes
                                FonctionsNatives.setPlayerLost();                              
                                etat = new EtatJeuFinDePartie(this);
                                //endGame = true;
    
                            }
                        }
                        else
                        {
                            if (nbZones == 1)
                            {
                                FinCampagne(false, pointsPartie[playerColorShift]);
                            }
                            else
                            {
                                FinCampagne(false, -5);
                            }
                        }

                    }
                });
            }
            catch (Exception)
            {
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_FormClosing(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on ferme la form PartieRapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_FormClosing(object sender, FormClosingEventArgs e)
        {
            //FonctionsNatives.arreterToutSons();
            //lock (Program.unLock)
            //{
            //    Program.peutAfficher = false;
            //    FonctionsNatives.modePause(false);
            //    FonctionsNatives.libererOpenGL();
            //    Program.tempBool = false;
            //}
            //((MenuComplet)Owner).ShowBackForm();
            StopTimer();
            FonctionsNatives.suprimerAllText();
            ((MenuComplet)Owner).ShowBackForm();


        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void RecommencerPartie()
        /// @brief Recommence la partie.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void RecommencerPartie()
        {
            resetConfig();
            StopTimer();
            FonctionsNatives.chargerZone(map, map.Length);
            Propriete = Outils.ProprieteStringToDictionnay(FonctionsNatives.obtenirPropriete());

            FonctionsNatives.resetNombreBillesCourantes();
            if (initialTime > 0)
            {
                SetTimer();
            }
            multiPlayerStop();
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public void AfficherInformations()
        /// @brief Afficher les informations de la partie.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void AfficherInformations()
        {
            InfoPanel.Visible = !InfoPanel.Visible;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ProchainePartie()
        /// @brief Chargement de la prochaine partie.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ProchainePartie()
        {
            if (multiPlayer)
            {
                int maxWinner = pointsPartie.Max();
                for (int i = 0; i < 4; i++)
                {
                    if (pointsPartie[i] == maxWinner)
                    {
                        nombreDeZonesGagnes[i]++;
                        Console.WriteLine(i + "has won a game with " + maxWinner);

                    }
                }
            }
            FonctionsNatives.arreterToutSons();
            boolTemp = false;
            timerOver = false;
            StopTimer();
            peutAnimer = false;
            FonctionsNatives.prepareNextGame();

            if (multiPlayer)
            {
                currentZone = FonctionsNatives.getCurrentGameIndex();
            }
            else
            {
            }
            if(playerColorShift == 0)
                currentZone++;

            map = new StringBuilder(myMaps[currentZone]);
            nextMap = new StringBuilder(map.ToString());
            nextMap.Remove(nextMap.Length - 4, 4);
            System.Threading.Thread.Sleep(500);
            zInfo = new ZoneInfo(Path.GetFileName(nextMap.ToString()), FonctionsNatives.obtenirDifficulte(map, map.Capacity).ToString(), true);
            this.Hide();
            zInfo.ShowDialog();
            this.Show();
            if (Program.testMenu.modeJeuMain != null)
            {
                FonctionsNatives.arreterToutSons();
                Program.testMenu.modeJeuMain.Focus();
            }
            FonctionsNatives.chargerZone(map, map.Length);

            FonctionsNatives.resetNombreDePointsDePartie();
            FonctionsNatives.resetNombreBillesCourantes();
           
            peutAnimer = true;
            boolTemp = true;
            FonctionsNatives.bouclerSon(bgm, bgm.Length);
            FonctionsNatives.ajusterVolume(bgm, bgm.Length, 90);
            FonctionsNatives.jouerSon(bgm, bgm.Length);
            /// La création de l'état s'occupe d'appeler resetConfig
            etat = new EtatJeuDebutDePartie(this);
            // Il faut changer le mode car le traitement de début est fini
            etat = new EtatJeuJouer(this);
            label_Nom.Text = "Nom: " + Path.GetFileNameWithoutExtension(map.ToString());
            if (nbZones == 1)
                this.Text = "Partie Rapide: " + Path.GetFileNameWithoutExtension(map.ToString());
            if (nbZones > 1)
                this.Text = "Campagne: " + Path.GetFileNameWithoutExtension(map.ToString());
            if (initialTime > 0)
                SetTimer();
          
            multiPlayerStop();
            endGame = false;

        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void CreerBille()
        /// @brief Creation d'une nouvelle bille.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void CreerBille(int colorshift = 0)
        {
            StringBuilder bille = new StringBuilder("bille");
            FonctionsNatives.creerObjet(bille, bille.Capacity, false, colorshift);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void FinCampagne(bool active, nbPoints)
        /// @brief Desactivation d'options en fin de campagne.
        /// @param[in] active : valeur d'activation.
        /// @param[in] nbPoints : nombre de points gagne.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void FinCampagne(bool active, int nbPoints = -5)
        {
            if (active)
                FonctionsNatives.jouerSon(winSound, winSound.Length);

            StopTimer();
            if (FonctionsNatives.getUserName() != "HORS-LIGNE")
            {
                if (nbPoints >= 9000)
                {
                    ((MenuComplet)Owner).SendAchievement("AC13");
                }
                if (nbPoints >= 1000)
                {
                    ((MenuComplet)Owner).SendAchievement("AC12");


                }
                if (nbPoints >= 500)
                {
                    ((MenuComplet)Owner).SendAchievement("AC11");
                }
            }
            FonctionsNatives.arreterToutSons();
            peutAnimer = false;
            boolTemp = false;
            gameOver = new PartieTerminee(active, nbPoints);
            gameOver.ShowDialog(this);
            if (Program.testMenu.modeJeuMain != null)
            {
                Program.testMenu.modeJeuMain.Focus();
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_Load(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on charge le ModeJeu.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_Load(object sender, EventArgs e)
        {

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void EtablirTouchesEtAI(int playerType)
        /// @brief Etablit les touches de jeu et active ou non l'AI selon le mode choisi.
        /// @param[in] playerType : Type de joueur (Solo, 2P, AI).
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void EtablirTouchesEtAI(int playerType)
        {
            if (playerType == 1)
            {
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                    FonctionsNatives.obtenirTouchePGJ1(),
                    FonctionsNatives.obtenirTouchePDJ1(),
                    FonctionsNatives.obtenirTouchePDJ1(),
                    FonctionsNatives.obtenirToucheRessort());
                FonctionsNatives.activerAI(false);
            }
            else if (playerType == 2)
            {
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                    FonctionsNatives.obtenirTouchePGJ2(),
                    FonctionsNatives.obtenirTouchePDJ1(),
                    FonctionsNatives.obtenirTouchePDJ2(),
                    FonctionsNatives.obtenirToucheRessort());

                FonctionsNatives.activerAI(false);
            }
            else if (playerType == 3)
            {
                // Le 1337 est la pour rendre l'acces aux touches de joueur 2 invalide
                touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                    1337,
                    FonctionsNatives.obtenirTouchePDJ1(),
                    1337,
                    FonctionsNatives.obtenirToucheRessort());

                FonctionsNatives.activerAI(true);
            }

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void EtablirTouchesMultiplayer(int playerType)
        /// @brief Etablit les touches de jeu et active ou non l'AI selon le mode choisi.
        /// @param[in] playerType : 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void EtablirTouchesMultiplayer(int playerNumber)
        {
            //var rawGameInfo = FonctionsNatives.GetGameInfo();
            //if (rawGameInfo == "false")
            //{
            //    return;
            //}
            //string[] gameInfo = rawGameInfo.Split(':');
            //string gameType = gameInfo[1];
            //string gameType = "1";

            //if (gameType == "1")
            //{
            //    int playerType = playerNumber % 2;
            //    if (playerType == 0)
            //    {
            //        touches = new Touches(1337,
            //                         FonctionsNatives.obtenirTouchePGJ2(),
            //                        1337,
            //                         FonctionsNatives.obtenirTouchePDJ2(),
            //                         FonctionsNatives.obtenirToucheRessort());
            //    }

            //    else if (playerType == 1)
            //    {
            //        // Le 1337 est la pour rendre l'acces aux touches de joueur 2 invalide
            //        touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
            //                        1337,
            //                        FonctionsNatives.obtenirTouchePDJ1(),
            //                        1337,
            //                        FonctionsNatives.obtenirToucheRessort());
            //    }

            //    FonctionsNatives.activerAI(false);
            //}
            //else if (gameType == "2")
            //{
            //    touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
            //       FonctionsNatives.obtenirTouchePGJ1(),
            //       FonctionsNatives.obtenirTouchePDJ1(),
            //       FonctionsNatives.obtenirTouchePDJ1(),
            //       FonctionsNatives.obtenirToucheRessort());
            //}


          


            // Le 1337 est la pour rendre l'acces aux touches de joueur 2 invalide
            touches = new Touches(FonctionsNatives.obtenirTouchePGJ1(),
                            1337,
                            FonctionsNatives.obtenirTouchePDJ1(),
                            1337,
                            FonctionsNatives.obtenirToucheRessort());
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_KeyDown(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on appuie sur une touche en partie rapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_KeyDown(object sender, KeyEventArgs e)
        {
            etat.traiterKeyDown(sender, e);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_KeyUp(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on relache une touche en partie rapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_KeyUp(object sender, KeyEventArgs e)
        {
            etat.traiterKeyUp(sender, e);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_redimensionner(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on redimensionne la fenetre de partie rapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_redimensionner(object sender, EventArgs e)
        {
            FonctionsNatives.redimensionnerFenetre(panel_GL.Width == 0 ? 1 : panel_GL.Width, panel_GL.Height == 0 ? 1 : panel_GL.Height);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieRapide_KeyDown(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on appuie et relache une touche en partie rapide.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieRapide_KeyPress(object sender, KeyPressEventArgs e)
        {
            etat.traiterKeyPress(sender, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_MouseWheel(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on utilise la roulette de la souris sur le panel GL.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseWheel(object sender, MouseEventArgs e)
        {
            etat.traiterRoulette(sender, e);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void RecommencerTout()
        /// @brief Reinitialise la campagne ou la partie rapide lorsqu'on termine.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void RecommencerTout()
        {
            if (gameOver.Enabled)
            {
                gameOver.Hide();
            }
            StopTimer();
            Array.Clear(pointsPartie, 0, pointsPartie.Length);
            currentZone = 0;
            map = new StringBuilder(myMaps[0]);
            nextMap = new StringBuilder(map.ToString());
            nextMap.Remove(nextMap.Length - 4, 4);
            this.Hide();
            zInfo = new ZoneInfo(Path.GetFileName(nextMap.ToString()), FonctionsNatives.obtenirDifficulte(map, map.Capacity).ToString(), false);
            zInfo.ShowDialog();
            this.Show();
            if (Program.testMenu.modeJeuMain != null)
            {
                Program.testMenu.modeJeuMain.Focus();
            }
            FonctionsNatives.chargerZone(map, map.Length);

            FonctionsNatives.resetNombreDePointsDePartie();
            FonctionsNatives.resetNombreBillesCourantes();
            currentZone = 1;
            peutAnimer = true;
            boolTemp = true;
            timerOver = false;
            FonctionsNatives.jouerSon(bgm, bgm.Length);
            /// La création de l'état s'occupe d'appeler resetConfig
            etat = new EtatJeuDebutDePartie(this);
            // Il faut changer le mode car le traitement de début est fini
            etat = new EtatJeuJouer(this);

            gameOver.Dispose();
            if(initialTime > 0)
            SetTimer();
            multiPlayerStop();
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void mPrincipal_menu_Click(object sender, EventArgs e)
        /// @brief Retour au menu principal lorsqu'on clique sur l'option dans le menu.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void mPrincipal_menu_Click(object sender, EventArgs e)
        {
            FonctionsNatives.arreterToutSons();
            if (multiPlayer)
            {
                //FonctionsNatives.resetMultiplayer();
                FonctionsNatives.leaveGame();
                ((MenuComplet)Owner).UpdateGamesPlayed();

                ((MenuComplet)Owner).ExitMultiplayerGame();

            }
            for (int i = 0; i < 4; ++i)
            {
                FonctionsNatives.desactiverPalettesDroites(i);
                FonctionsNatives.desactiverPalettesGauches(i);
            }
            ((MenuComplet)Owner).zonesCampagne.Clear();
            lock (Program.unLock)
            {
                Program.peutAfficher = false;
                FonctionsNatives.modePause(false);
                FonctionsNatives.libererOpenGL();
                Program.tempBool = false;
            }
            Close();

        }

      

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ModeJeu_Shown(object sender, EventArgs e)
        /// @brief Affichage/Ajustement de la console custom si utilisee
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ModeJeu_Shown(object sender, EventArgs e)
        {
            var scrren = Screen.PrimaryScreen.Bounds.Height;
            this.Height = (scrren * 3) / 4;

            if (Program.testMenu.modeJeuMain != null)
                Program.testMenu.modeJeuMain.Focus();
            firstStart = false;
            if (((MenuComplet) Owner).chat != null)
            {
              ((MenuComplet)Owner).chat.Show();
              //  ((MenuComplet) Owner).chat.Visible = true;
                Focus();
            }
            Program.loadingBar.Close();
            if (initialTime > 0 && !multiPlayer)
            {
                SetTimer();                
            }

        }


        public void ShowChat()
        {
            if (  ((MenuComplet)Owner).chat != null  ) 
            {
                if (((MenuComplet)Owner).chat.Visible)
                {
                    ((MenuComplet)Owner).chat.Hide();
                    return;
                }
                else
                {
                    ((MenuComplet)Owner).chat.Show();
                    return;
                }
               // ((MenuComplet)Owner).chat.Visible = !((MenuComplet)Owner).chat.Visible;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ModeJeu_Deactivate(object sender, EventArgs e)
        /// @brief Desactiver les palettes lorsqu'on sort de la form
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ModeJeu_Deactivate(object sender, EventArgs e)
        {
           
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ModeJeu_VisibleChanged(object sender, EventArgs e)
        /// @brief Fonction qui fait de quoi lorsqu'on met le mode Jeu visible.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ModeJeu_VisibleChanged(object sender, EventArgs e)
        {
            if (this.Visible == true)
            {
                FonctionsNatives.jouerSon(Program.couvercle, Program.couvercle.Length);
                if (Program.testMenu.modeJeuMain != null)
                    Program.testMenu.modeJeuMain.Focus();
            }
            else
            {
               // FonctionsNatives.arreterToutSons();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_MouseDown(object sender, EventArgs e)
        /// @brief Fonction qui traite l'enfoncement de la souris.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseDown(object sender, MouseEventArgs e)
        {
            etat.traiterMouseDown(sender, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_MouseUp(object sender, EventArgs e)
        /// @brief Fonction qui traite le relachement de la souris.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseUp(object sender, MouseEventArgs e)
        {
            etat.traiterMouseUp(sender, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_MouseMove(object sender, EventArgs e)
        /// @brief Fonction qui traite le deplacement de la souris.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_MouseMove(object sender, MouseEventArgs e)
        {
            etat.traiterMouseMove(sender, e);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void panel_GL_SizeChanged(object sender, EventArgs e)
        /// @brief Fonction qui traite le changement de taille de la fenetre.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void panel_GL_SizeChanged(object sender, EventArgs e)
        {
            panelHeight = panel_GL.Size.Height;
            panelWidth = panel_GL.Size.Width;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Ortho_MenuItem_Click(object sender, EventArgs e)
        /// @brief Fonction qui change la Camera en Camera Orthographique.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Ortho_MenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.utiliserCameraOrbite(false);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Orbitale_MenuItem_Click(object sender, EventArgs e)
        /// @brief Fonction qui change la Camera en Camera Orbite.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Orbitale_MenuItem_Click(object sender, EventArgs e)
        {
            FonctionsNatives.utiliserCameraOrbite(true);
        }

        public void AddPoints()
        {
            int maxWinner = pointsPartie.Max();
            if (maxWinner == 0)
            {
                FonctionsNatives.addShekels(1);
            }
            else
            {
                if (maxWinner != 0 && pointsPartie[playerColorShift] == maxWinner)
                {
                    FonctionsNatives.addShekels(50);
                    AddGameTypeWin();
                }
                else
                {
                    FonctionsNatives.addShekels(20);
                    Program.player = new System.Media.SoundPlayer(Properties.Resources.gOver);
                    Program.player.Play();
                }
            }
            Console.WriteLine(maxWinner + "to" + playerColorShift);
        }



        public void AddCampaignPoints()
        {
            int maxWinner = nombreDeZonesGagnes.Max();
            Console.WriteLine(playerColorShift + " has won!with " + maxWinner);           
            if (maxWinner != 0 && nombreDeZonesGagnes[playerColorShift] == maxWinner)
            {
                FonctionsNatives.addShekels(50);
                AddGameTypeWin();
            }
            else
            {
                FonctionsNatives.addShekels(20);
            }
      
            
        }

        private void AddGameTypeWin()
        {

            Program.player = new System.Media.SoundPlayer(Properties.Resources.winSound);
            Program.player.Play();
            int victories = ++((MenuComplet) Owner).playerInfo.playerVictories;
            Console.WriteLine( ((MenuComplet) Owner).playerInfo.playerVictories++);
            if (FonctionsNatives.isCompetitiveGame())
            {
                int compVictories = ++((MenuComplet)Owner).playerInfo.playerCompVictories;
                Console.WriteLine("TODO : ADD COMPETITIVE WIN");
                StringBuilder newStatistics = new StringBuilder("GAMES_WON:" + victories +"\r\nGAMES_COMP_WON:" + compVictories);
                FonctionsNatives.updateInfoCompte(newStatistics);
            }
            else
            {
                int coopVictories = ++((MenuComplet) Owner).playerInfo.playerCoopVictories;
                Console.WriteLine("TODO: ADD COOPERATIVE WIN");
                StringBuilder newStatistics = new StringBuilder("GAMES_WON:" + victories + "\r\nGAMES_COOP_WON:" + coopVictories );
                FonctionsNatives.updateInfoCompte(newStatistics);
            }
            ((MenuComplet)Owner).UpdateStatistics();
        }

        /*
        * FONCTIONS GENERIQUES POUR AVOIR DES BEAUX BOUTONS
        * 
        */
        #region Boutons
        private void GenericButtonMouseEnter(object sender, EventArgs e)
        {
            Program.ButtonMouseOver((System.Windows.Forms.Button)sender);
        }

        private void GenericButtonMouseLeave(object sender, EventArgs e)
        {
            Program.ButtonMouseLeave((System.Windows.Forms.Button)sender);

        }

        private void GenericButtonMouseDown(object sender, MouseEventArgs e)
        {
            Program.ButtonMouseDown((System.Windows.Forms.Button)sender);

        }

        private void GenericButtonMouseUp(object sender, MouseEventArgs e)
        {
            Program.ButtonMouseUp((System.Windows.Forms.Button)sender);

        }

        #endregion

        private void QuitMPGameBtn_Click(object sender, EventArgs e)
        {
            mPrincipal_menu.PerformClick();
        }


    }
}