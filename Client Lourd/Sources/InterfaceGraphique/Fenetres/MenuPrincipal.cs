//////////////////////////////////////////////////////////////////////////////
/// @file MenuPrincipal.cs
/// @author Ballers
/// @date 2015-01-18
/// @version 1.0 
///
/// @ingroup Fenetres
//////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Threading;
using System.Windows.Forms;

//<CAMERA> //TO DO: Put back for video
//<CAMERA> using AForge.Video;
//<CAMERA> using AForge.Video.DirectShow;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class MainMenu
    /// @brief Main Menu du jeu.
    ///
    /// @author The Ballers
    /// @date 2015-01-18
    /// 
    /// @ingroup Fenetres
    ///////////////////////////////////////////////////////////////////////////
    public partial class MainMenu : Form
    {
        System.Media.SoundPlayer player = new System.Media.SoundPlayer(Properties.Resources.button_29); ///< Sound player
        public Editeur modeEdit; ///< Form du mode edition
        private Thread myThread; ///< Une thread
        public Campagne campagne;
        public PartieRapide pRapide;
        private Configuration configuration;
        public ModeJeu modeJeuMain;
       


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public MainMenu()
        /// @brief Constructeur de la fenetre.
        /// 
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public MainMenu()
        {
            this.KeyPress += new KeyPressEventHandler(Form1_KeyPress);
            InitializeComponent();
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.Image = Properties.Resources.titleScreen;
            this.KeyPreview = true;
            StartPosition = FormStartPosition.CenterScreen;
            StringBuilder initSound = new StringBuilder("");
            configuration = new Configuration();
           
            this.Focus();
           
        }

       
        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_quit_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Quitter.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_quit_Click(object sender, EventArgs e)
        {
          
            this.Dispose();
            System.Environment.Exit(0);
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_edit_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Editeur.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_edit_Click(object sender, EventArgs e)
        {
            
            while (myThread.IsAlive)
            {
                Thread.Sleep(100);
            }
            this.Hide();
            modeEdit = new Editeur();
            modeEdit.ShowDialog(this);
            if (modeEdit != null)
            {
                modeEdit = null;
            }
            this.Show();

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_edit_MouseEnter(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur place la 
        ///        souris sur le bouton Editeur.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_edit_MouseEnter(object sender, EventArgs e)
        {
            bouton_edit.ForeColor = Color.Green;
            bouton_edit.FlatAppearance.BorderColor = Color.Black;
            bouton_edit.FlatAppearance.BorderSize = 1;
            player.Play();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_edit_MouseLeave(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur enleve la 
        ///        souris du bouton Editeur.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_edit_MouseLeave(object sender, EventArgs e)
        {
            bouton_edit.ForeColor = Color.Black;
            bouton_edit.FlatAppearance.BorderSize = 0;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_quit_MouseEnter(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur place la 
        ///        souris sur le bouton Quitter.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_quit_MouseEnter(object sender, EventArgs e)
        {
            bouton_quit.FlatAppearance.BorderSize = 1;
            bouton_quit.ForeColor = Color.Red;
            bouton_quit.FlatAppearance.BorderColor = Color.Black;
            player.Play();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_quit_MouseLeave(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur enleve la 
        ///        souris du bouton Quitter.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_quit_MouseLeave(object sender, EventArgs e)
        {
            bouton_quit.FlatAppearance.BorderSize = 0;
            bouton_quit.ForeColor = Color.Black;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MainMenu_Shown(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque le menu s'ouvre. La musique
        ///        joue sur un autre Thread.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MainMenu_Shown(object sender, EventArgs e)
        {
            myThread = new Thread(new ThreadStart(initDll));
            myThread.Start();
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void initDll()
        /// @brief Initialise la DLL
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void initDll()
        {
            InterfaceGraphique.FonctionsNatives.initialiserSon(); // Initialise le son
        }

        private void bouton_campagne_Click(object sender, EventArgs e)
        {
            
            campagne = new Campagne();
            this.Hide();
            campagne.ShowDialog(this);
            this.Show();
        }

        private void bouton_config_MouseEnter(object sender, EventArgs e)
        {
            bouton_config.ForeColor = Color.Green;
            bouton_config.FlatAppearance.BorderColor = Color.Black;
            bouton_config.FlatAppearance.BorderSize = 1;
            player.Play();
        }

        private void bouton_config_MouseLeave(object sender, EventArgs e)
        {
            bouton_config.FlatAppearance.BorderSize = 0;
            bouton_config.ForeColor = Color.Black;
        }

        private void bouton_campagne_MouseEnter(object sender, EventArgs e)
        {
            bouton_campagne.ForeColor = Color.Green;
            bouton_campagne.FlatAppearance.BorderColor = Color.Black;
            bouton_campagne.FlatAppearance.BorderSize = 1;
            player.Play();
        }

        private void bouton_campagne_MouseLeave(object sender, EventArgs e)
        {
            bouton_campagne.FlatAppearance.BorderSize = 0;
            bouton_campagne.ForeColor = Color.Black;
        }

        private void bouton_pRapide_MouseEnter(object sender, EventArgs e)
        {
            bouton_pRapide.ForeColor = Color.Green;
            bouton_pRapide.FlatAppearance.BorderColor = Color.Black;
            bouton_pRapide.FlatAppearance.BorderSize = 1;
            player.Play();
        }

        private void bouton_pRapide_MouseLeave(object sender, EventArgs e)
        {
            bouton_pRapide.FlatAppearance.BorderSize = 0;
            bouton_pRapide.ForeColor = Color.Black;
        }

        private void pictureBox1_MouseEnter(object sender, EventArgs e)
        {
            pictureBox1.Image = Properties.Resources.SaintTrinity;
                  
        }

        private void pictureBox1_MouseLeave(object sender, EventArgs e)
        {
            
            pictureBox1.Image = Properties.Resources.titleScreen;
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage; 
            player.Stream = Properties.Resources.button_29;
        }

        private void bouton_pRapide_Click(object sender, EventArgs e)
        {
            
            this.Hide();
            pRapide = new PartieRapide();
            pRapide.ShowDialog(this);
            this.Show();

        }

        private void bouton_config_Click(object sender, EventArgs e)
        {
          
            configuration.ShowDialog(this);
        }

        public void LancerModeJeu(List<string> zones, int playerType)
        {
            modeJeuMain = new ModeJeu(zones, playerType);
            modeJeuMain.Show(this);
            if (campagne != null)
            {
                campagne.Close();
                campagne = null;
            }
            else if (pRapide != null)
            {
                pRapide.Close();
                pRapide = null;
            }
            this.Show();
        }

        private void pictureBox1_Click_1(object sender, EventArgs e)
        {
           System.Diagnostics.Process.Start("http://tinyurl.com/dymbb3a");
        }


        private void MainMenu_FormClosing(object sender, FormClosingEventArgs e)
        {
            
            this.Dispose();
            System.Environment.Exit(0);
        }

        private void MainMenu_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData == Keys.F1)
            {
                Aide helpMenu = new Aide();
                helpMenu.ShowDialog(this);
            }
        }

        private void MainMenu_VisibleChanged(object sender, EventArgs e)
        {
            FonctionsNatives.arreterToutSons();
        }
    }
}