//////////////////////////////////////////////////////////////////////////////
/// @file Program.cs
/// @author Inconnu
/// @date Inconnue
/// @version 1.0 
///
/// @ingroup InterfaceGraphique
//////////////////////////////////////////////////////////////////////////////

/**
*	@defgroup InterfaceGraphique InterfaceGraphique
*	@ingroup INF2990
*	Ce module contient le GUI de l'application et la logique de l'interface.
*/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Media;
using System.Windows.Forms;
using System.Text;
using System.Threading;
using InterfaceGraphique.Fenetres;
using InterfaceGraphique.Langages;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Program
    /// @brief Classe qui gere le demarrage de l'application.
    /// @author Inconnu
    /// @date Inconnue
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    static class Program
    {
        private const int NB_IMAGES_PAR_SECONDE = 60; ///< Frame rate de l'application
        public static Object unLock = new Object();
        public static bool peutAfficher = false;
        public static bool tempBool = false;
        public static String playerName;
        public static MainMenu mMenu; ///< Main Menu de l'application
        private static TimeSpan dernierTemps; ///< Dernier temps enregistre
        private static TimeSpan tempsAccumule; ///< Temps total accumule
        private static Stopwatch chrono = Stopwatch.StartNew(); ///< Chronometre
        private static int RAFRAICHISSEMENT = 10;
        private static TimeSpan tempsEcouleVoulu = TimeSpan.FromTicks(TimeSpan.TicksPerSecond / (NB_IMAGES_PAR_SECONDE * RAFRAICHISSEMENT)); ///< Temps avant le rafraichissement
        public static int compteurFrames;
        public static bool helpMenu = true;
        public static StringBuilder couvercle = new StringBuilder("stone");
        public static StringBuilder spooky = new StringBuilder("spooky");
        public static SoundPlayer player;
        public static List<string> playerNames = new List<string>(); 
        //FOR TESTS*****

        public static MenuComplet testMenu;
        public static LoadingBar loadingBar;
        public static bool TestMenuUse = true;

        

        ////////////////////////////////////////////////////////////////////////
        /// @fn static void Main(string[] args)
        /// @brief Le point d'entree de l'application.
        /// @param[in] args : argument passe a la compilation (permet de demarrer les tests)
        /// @return Aucune.
        ////////////////////////////////////////////////////////////////////////
        [STAThread]
        static void Main(string[] args)
        {
            /*
            if (args.Length != 0)
            {
                if (args[0] == "nowarnings")
                    DO_SOMETHING
            }
            */
            playerNames = new List<string>(4);
            chrono.Start();
            Application.Idle += ExecuterQuandInactif;
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
           
            if (TestMenuUse)
            {
                // Gestion des langues
                Langage.LoadLangagePreference();
                Thread.CurrentThread.CurrentCulture = Langage.getCultureInfo();
                Thread.CurrentThread.CurrentUICulture = Langage.getCultureInfo();

                testMenu = new MenuComplet();
                Application.Run(testMenu);
            }
            //else
            //{
            //    mMenu = new MainMenu();
            //    Application.Run(mMenu);
                
            //}

        }


        ////////////////////////////////////////////////////////////////////////
        /// @fn static void ExecuterQuandInactif(object sender, EventArgs e)
        /// @brief Operations executer lorsque l'application est inactive.
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ////////////////////////////////////////////////////////////////////////
        static void ExecuterQuandInactif(object sender, EventArgs e)
        {
            FonctionsNatives.Message message;

            while (!FonctionsNatives.PeekMessage(out message, IntPtr.Zero, 0, 0, 0))
            {
                TimeSpan currentTime = chrono.Elapsed;
                TimeSpan elapsedTime = currentTime - dernierTemps;
                dernierTemps = currentTime;

                tempsAccumule += elapsedTime;
                
                if (tempsAccumule >= tempsEcouleVoulu)
                {
                    lock (unLock)
                    {
                        double tempsInterAffichage = (double)tempsAccumule.Ticks / TimeSpan.TicksPerSecond;
                      
                        if (TestMenuUse)
                        {
                            if (testMenu.modeEdit != null && peutAfficher)
                            {
                                testMenu.modeEdit.MettreAJour(tempsInterAffichage);
                            }
                            else if (testMenu.modeJeuMain != null && peutAfficher)
                            {
                               testMenu.modeJeuMain.MettreAJour(tempsInterAffichage);
                            }    
                        }
                        //else
                        //{
                        //    if (mMenu.modeEdit != null && peutAfficher)
                        //    {
                        //        mMenu.modeEdit.MettreAJour(tempsInterAffichage);
                        //    }
                        //    else if (mMenu.modeJeuMain != null && peutAfficher)
                        //    {
                        //        mMenu.modeJeuMain.MettreAJour(tempsInterAffichage);
                        //    }
                        //}
                       
                        
                        compteurFrames++;
                        if (compteurFrames >= RAFRAICHISSEMENT)
                        {
                            compteurFrames = 0;
                        }
                    }
                    tempsAccumule = TimeSpan.Zero;
                }
            }
        }


        // Fonctions qui permettent de changer le Look&Feel des boutons
        // TODO: Faire des manipulations sur les fonts ( couleur / taille ) 

        public static void ButtonMouseOver(System.Windows.Forms.Button button)
        {
            button.BackgroundImage = Properties.Resources.buttonStock1h;
            player = new System.Media.SoundPlayer(Properties.Resources.button_29);
            player.Play();

        }

        public static void ButtonMouseLeave(System.Windows.Forms.Button button)
        {
            button.BackgroundImage = Properties.Resources.buttonStock1;
        }

        public static void ButtonMouseDown(System.Windows.Forms.Button button)
        {
            button.BackgroundImage = Properties.Resources.buttonStock1d;
        }

        public static void ButtonMouseUp(System.Windows.Forms.Button button)
        {
            button.BackgroundImage = Properties.Resources.buttonStock1;
        }

        public static void CheckBoxChecked(System.Windows.Forms.CheckBox checkBox,Bitmap bmap)
        {
            if (checkBox.Checked)
            {
                checkBox.BackgroundImage = Properties.Resources.buttonStock1h;
            }
            else
            {
                checkBox.BackgroundImage = bmap;
            }
        }

    }


    ///////////////////////////////////////////////////////////////////////////
    /// @class FullScreen
    /// @brief Gestion du mode Plein ecran.
    /// @author The Ballers
    /// @date 2015-01-13
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    class FullScreen
    {
        //////////////////////////////////////////////////////////////////////////////////////////
        /// @fn public void EnterFullScreenMode(Form targetForm)
        /// @brief Entre en mode Plein ecran.
        /// @param[in] targetForm : La form qui passe en mode Plein ecran.
        /// @return Aucune.
        //////////////////////////////////////////////////////////////////////////////////////////
        public void EnterFullScreenMode(Form targetForm)
        {
            targetForm.WindowState = FormWindowState.Normal;
            if (targetForm is ModeJeu)
            {
               targetForm.FormBorderStyle = FormBorderStyle.None;
            }
            targetForm.WindowState = FormWindowState.Maximized;
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        /// @fn public void LeaveFullScreenMode(Form targetForm)
        /// @brief Quitte le mode Plein ecran.
        /// @param[in] targetForm : La form qui quitte le mode Plein ecran.
        /// @return Aucune.
        //////////////////////////////////////////////////////////////////////////////////////////
        public void LeaveFullScreenMode(Form targetForm)
        {
            targetForm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Sizable;
            targetForm.WindowState = FormWindowState.Normal;
        }


        //////////////////////////////////////////////////////////////////////////////////////////
        /// @fn public bool IsFullScreen(Form targetForm)
        /// @brief Indique si une form est en mode Plein ecran.
        /// @param[in] targetForm : La form qui quitte le mode Plein ecran.
        /// @return True si la form est en Plein ecran, false sinon.
        //////////////////////////////////////////////////////////////////////////////////////////
        public bool IsFullScreen(Form targetForm)
        {
            return (targetForm.WindowState == FormWindowState.Maximized);
        }

    }


    ///////////////////////////////////////////////////////////////////////////
    /// @class Touches
    /// @brief Classe qui contient les touches pour les palettes
    /// @author Inconnu
    /// @date Inconnue
    /// @ingroup InterfaceGraphique
    ///////////////////////////////////////////////////////////////////////////
    public class Touches
    {
        public int PGJ1;
        public int PGJ2;
        public int PDJ1;
        public int PDJ2;
        public int Ressort;

        ////////////////////////////////////////////////////////////////////////
        /// @fn public Touches(int pgj1, int pgj2, int pdj1, int pdj2, int ressort)
        /// @brief Constructeur de la fenetre.
        /// @param[in] pgj1 : palette gauche joueur 1
        /// @param[in] pgj2 : palette gauche joueur 2
        /// @param[in] pdj1 : palette droite joueur 1
        /// @param[in] pdj2 : palette droite joueur 2
        /// @param[in] ressort : ressort
        /// @return Aucune (constructeur).
        ////////////////////////////////////////////////////////////////////////
        public Touches(int pgj1, int pgj2, int pdj1, int pdj2, int ressort)
        {
            PGJ1 = pgj1;
            PGJ2 = pgj2;
            PDJ1 = pdj1;
            PDJ2 = pdj2;
            Ressort = ressort;
        }

    }

}