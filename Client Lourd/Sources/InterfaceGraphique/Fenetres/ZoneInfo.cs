//////////////////////////////////////////////////////////////////////////////
/// @file ZoneInfo.cs
/// @author Ballers
/// @date 2015-03-12
/// @version 1.0 
///
/// @ingroup Fenetres
//////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class ZoneInfo
    /// @brief Classe d'interface de la fenetre d'info des zones de jeu.
    ///
    /// @author Ballers
    /// @date 2015-03-12
    /// 
    /// @ingroup Fenetres
    ///////////////////////////////////////////////////////////////////////////
    public partial class ZoneInfo : Form
    {
        int time;
        StringBuilder winSound = new StringBuilder("campagneWin");
        Dictionary<string, string> Propriete = new Dictionary<string, string>();

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public ZoneInfo(string nomZone, string difficulte, bool win)
        /// @brief Constructeur par parametre de la fenetre Partie Terminee.
        /// @param[in] nomZone : Nom de la zone affichee.
        /// @param[in] difficulte : difficulte de la zone de jeu
        /// @param[in] win : Indique si on a gagne la partie precedente.
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public ZoneInfo(string nomZone, string difficulte, bool win)
        {
            InitializeComponent();
            WindowState = FormWindowState.Maximized;
            this.FormBorderStyle = FormBorderStyle.None;
            this.Icon = Properties.Resources.Pinball;
            this.ClientSize = Screen.PrimaryScreen.Bounds.Size;
            prettyImage.Image = Properties.Resources.spookyGif;
            prettyImage.SizeMode = PictureBoxSizeMode.StretchImage;
            StringBuilder zoneProps = new StringBuilder(Application.StartupPath + @"\zones\" + nomZone + ".xml");
            
            string propString = FonctionsNatives.obtenirPropriete(zoneProps, zoneProps.Length);
            Propriete = Outils.ProprieteStringToDictionnay(propString);
            

            infoPanel.Location = new Point(
                 Width/ 3 - infoPanel.Width ,
                 Height / 2 - screenShot.Height / 2
                 );
            screenShot.Location = new Point(
                 Width / 2   +  screenShot.Width,
                 Height / 2 - screenShot.Height / 2
                 );
            timerPanel.Width = Width;
            tempRestant.Width = Width;
            timerPanel.Location = new Point(
               0,
                Height - timerPanel.Height - 10
                );
            prettyImage.Location = new Point(
                Width/2 - prettyImage.Width/2,
                20
                );


            if (win)
            {
                labelWin.Text = "Vous avez gagné!";
                FonctionsNatives.jouerSon(winSound,winSound.Length,false);
            }
            else
            {
                labelWin.Text = "Début de la partie";
            }
            time = 5;
            timer1.Enabled = true;
           
            timer1.Interval = 25;
            timer1.Tick += new EventHandler(DecrementProgressBar);
            label_Zone.Text = nomZone;
            label_Difficulte.Text = difficulte;
            label_Points.Text = Propriete[Proprietes.pointVictoire];
            label_Bille.Text = Propriete[Proprietes.pointBilleGratuite];
            screenShot.SizeMode = PictureBoxSizeMode.StretchImage;
            screenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\" + nomZone+ ".jpg");
        }

       

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ZoneInfo_KeyPress(object sender, EventArgs e)
        /// @brief Evenement lorsqu'on appuie et relache une touche sur la zone d'info.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ZoneInfo_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == ' ')
            {
               // this.Close();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ZoneInfo_KeyPress(object sender, EventArgs e)
        /// @brief Decrementation de la barre de progres (temps restant).
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void DecrementProgressBar(object sender, EventArgs e)
        {
            tempRestant.Value--;
            if (tempRestant.Value % 40 == 0)
            {
                time--;
               
                labelTimeLeft.Text = time.ToString();
            }
            if (tempRestant.Value == tempRestant.Minimum)
            {
                timer1.Stop();
                this.Close();
            }
        }

        private void labelWin_Click(object sender, EventArgs e)
        {

        }

        private void infoPanel_Paint(object sender, PaintEventArgs e)
        {

        }

        private void label_Nom_Click(object sender, EventArgs e)
        {

        }

        private void label_Zone_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void timerPanel_Paint(object sender, PaintEventArgs e)
        {

        }

      
    
    }
}
