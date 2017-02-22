//////////////////////////////////////////////////////////////////////////////
/// @file PartieTerminee.cs
/// @author Ballers
/// @date 2015-03-16
/// @version 1.0 
///
/// @ingroup Fenetres
//////////////////////////////////////////////////////////////////////////////

using System;
using System.Drawing;
using System.Drawing.Text;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class PartieTerminee
    /// @brief Classe d'interface de la fenetre Partie Terminee
    ///
    /// @author Ballers
    /// @date 2015-03-16
    /// 
    /// @ingroup Fenetres
    ///////////////////////////////////////////////////////////////////////////
    public partial class PartieTerminee : Form
    {
        System.Media.SoundPlayer player; ///< Sound Player.
        private PrivateFontCollection fonts = new PrivateFontCollection();
        Font myFont;

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public PartieTerminee(bool victoire, int nbPoints)
        /// @brief Constructeur par parametre de la fenetre Partie Terminee.
        /// @param[in] victoire : Indique si la partie a ete gagnee ou perdue.
        /// @param[in] nbPoints : Indique le nombre de points lors de la fin de la partie.
        /// @return Aucune (constructeur).
        ///
        ////////////////////////////////////////////////////////////////////////
        public PartieTerminee(bool victoire, int nbPoints)
        {
            InitializeComponent();
            victoryImage.SizeMode = PictureBoxSizeMode.StretchImage;
            WindowState = FormWindowState.Maximized;            
            SetFont();
            this.ClientSize = Screen.PrimaryScreen.Bounds.Size;
            // Background sauve en memoire
            //Bitmap myImage = new Bitmap(Properties.Resources.GenericBackground);
            //partieTerminePanel.BackgroundImage = myImage;
            //partieTerminePanel.BackgroundImageLayout = ImageLayout.Stretch;
            AllowTransparency = true;
            StartPosition = FormStartPosition.CenterScreen;
           SetLabel();
            victoryImage.Location = new Point(
                partieTerminePanel.Width/2 - victoryImage.Width/2,
                partieTerminePanel.Height/2 + EndLabel.Height/2);
            boutonRecommencer.Location = new Point(
                partieTerminePanel.Width/2 - boutonRecommencer.Width -10,
                partieTerminePanel.Height - boutonRecommencer.Height);
            boutonMenuP.Location = new Point(
                partieTerminePanel.Width / 2 + 10,
                partieTerminePanel.Height - boutonMenuP.Height);
            StartPosition = FormStartPosition.CenterScreen;
            if (nbPoints > 0)
            {
                player = new System.Media.SoundPlayer(Properties.Resources.AIRPORN);
                EndLabel.Text = "VICTORY ACHIEVED! " + nbPoints;
                SetLabel();
               

            }
            else
            {
                if (victoire == false)
                {
                    player = new System.Media.SoundPlayer(Properties.Resources.gOver);

                    EndLabel.Text = "YOU LOST!";
                    SetLabel();

                }
                else
                {
                    EndLabel.Text = "VICTORY ACHIEVED! ";
                    SetLabel();

                    player = new System.Media.SoundPlayer(Properties.Resources.AIRPORN);
                }
            }

        }

        private void SetFont()
        {
            byte[] fontData = Properties.Resources.diablo_h;
            IntPtr fontPtr = System.Runtime.InteropServices.Marshal.AllocCoTaskMem(fontData.Length);
            System.Runtime.InteropServices.Marshal.Copy(fontData, 0, fontPtr, fontData.Length);
            uint dummy = 0;
            fonts.AddMemoryFont(fontPtr, Properties.Resources.diablo_h.Length);
            FonctionsNatives.AddFontMemResourceEx(fontPtr, (uint)Properties.Resources.diablo_h.Length, IntPtr.Zero, ref dummy);
            System.Runtime.InteropServices.Marshal.FreeCoTaskMem(fontPtr);

            myFont = new Font(fonts.Families[0], 60.0F);
            EndLabel.Font = myFont;
        }

        private void SetLabel()
        {
            EndLabel.Location = new Point(
                partieTerminePanel.Width/2 - EndLabel.Width/2, 
                partieTerminePanel.Height / 2 - EndLabel.Height / 2);
            victoryImage.Location = new Point(
              partieTerminePanel.Width / 2 - victoryImage.Width / 2,
              partieTerminePanel.Height / 2 + EndLabel.Height / 2);
        }
        
        
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieTerminee_Shown(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on ouvre la fenetre Partie Terminee.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieTerminee_Shown(object sender, EventArgs e)
        {
            player.Play();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void boutonMenuP_Click(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on clique sur le bouton Menu Principal.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void boutonMenuP_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void boutonRecommencer_Click(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on clique sur le bouton Recommencer.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void boutonRecommencer_Click(object sender, EventArgs e)
        {
            ((ModeJeu)this.Owner).RecommencerTout();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PartieTerminee_FormClosing(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on ferme la fenetre Partie Terminee.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PartieTerminee_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.None)
            {
                this.Close();
            }
            else if (e.CloseReason == CloseReason.UserClosing)
            {
                ((ModeJeu)this.Owner).Close();
            }
            player.Stop();
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



    }
}
