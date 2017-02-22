using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using InterfaceGraphique.Fenetres;

namespace InterfaceGraphique
{
    partial class MenuComplet
    {
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void QGameBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet de quitter l'application.
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void QGameBtn_Click(object sender, EventArgs e)
        {
            if (chat != null && connected)
            {
                //  chat.messageThread.Abort();
                //  chat.messageThread.Join();
                //   chat.displayThread.Abort();
                //   chat.displayThread.Join();
                chat.connected = false;
                chat.messageThread.Join();
                chat.Close();
                chat = null;
                bool success = FonctionsNatives.LogOff();
                MultiPlayerBtn.Enabled = false;
                if (!success)
                {
                    Console.WriteLine("DEBUG : LOGOFF FAILED!");
                }

            }
            connected = false;
            Close();
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void 
        /// _Click(object sender, EventArgs e)
        /// @brief Fonction qui permet d'ouvrir l'Editeur
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void EditeurBtn_Click(object sender, EventArgs e)
        {
            if (FonctionsNatives.getUserName() != "HORS-LIGNE")
            {
                Task mytask = Task.Run(() =>
                {
                    SetDownloadText("Telechargement des cartes....");
                    FonctionsNatives.executeDownloadMaps();
                    SetDownloadText("done");


                });
            }
           
            Program.loadingBar = new LoadingBar();
            Program.loadingBar.Show(this);
            this.Hide();


            modeEdit = new Editeur();
            modeEdit.Show(this);

        }


        /// <summary>
        ///  Return function after quitting game
        /// </summary>
        public void ExitMultiplayerGame()
        {
            tabControl1.SelectedTab = MainTab;
            MainTab.Focus();
            startedGame = false;
            MainPanel.Visible = false;
            MPJoinGameSelectPanel.Visible = true;
            MPJoinPanel.Visible = false;
            MultiPlayerPanel.Visible = true;
            ShekelAchievementTest();
            playerInfo.UpdatePlayerInfo(Outils.ProprieteStringToDictionnay(FonctionsNatives.obtenirInfoCompte()));
            CurrencyLabel.Text = playerInfo.playerCurrency.ToString();
            //UGLY FUCKING HACK
            if (chat != null)
            {
                chat.connected = false;
                //chat.messageThread.Join();
                chat.messageThread.Abort();
                chat.Close();
                chat = null;
            }
            FonctionsNatives.LogOff();
          
            FonctionsNatives.DisconnectFromServer();
            StringBuilder ipAddress = new StringBuilder(IPAddressBox.Text);
            FonctionsNatives.SendIP(ipAddress);
            StringBuilder username = new StringBuilder(UsernameBox.Text);
            StringBuilder password = new StringBuilder(PasswordBox.Text);
            succesLogIN = FonctionsNatives.LogIn(username, password);
            chat = new ChatForm();
            chat.Show(this);
        }


        public void ShowBackForm()
        {

            if (modeEdit != null)
            {
                modeEdit = null;
            }
            if (modeJeuMain != null)
            {
                modeJeuMain = null;
            }

            this.Show();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ConnectBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet de Connect/Deconnecter l'utilisateur
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ConnectBtn_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = LoginTab;
            bool success = false;
            LoginTab.Focus();

            if (chat != null && connected)
            {
              //  chat.messageThread.Abort();
              //  chat.messageThread.Join();
             //   chat.displayThread.Abort();
             //   chat.displayThread.Join();
                chat.connected = false;
                chat.messageThread.Join();
                chat.Close();
                chat = null;
                success = FonctionsNatives.LogOff();
                FonctionsNatives.DisconnectFromServer();
                ServerConnectBtn.Enabled = true;
                LogibBtnLogin.Enabled = false;
                PasswordResetLink.Enabled = false;
                AchievementMainPanel.Visible = false;
                MultiPlayerBtn.Enabled = false;
                MultiPlayerPanel.Visible = false;
                MainPanel.Visible = true;
                if (!success)
                {
                    Console.WriteLine("DEBUG : LOGOFF FAILED!");
                }
                
            }
            connected = false;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void OptionsBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet d'ouvrir le paneau Options
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void OptionsBtn_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = OptionsTab;

            OptionsTab.Focus();
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MarketplaceBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet d'ouvrir le paneau MarketPlace
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MarketplaceBtn_Click(object sender, EventArgs e)
        {
            SetUpMarketPlace();
            tabControl1.SelectedTab = MarketplaceTab;
            MarketplaceTab.Focus();
        }

       

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void SoloBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet de changer le paneau MainPanel et SinglePlayerPanel
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void SoloBtn_Click(object sender, EventArgs e)
        {
            SinglePlayerPanel.Visible = true;
            MainPanel.Visible = false;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MultiPlayerBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet de changer le paneau MainPanel et MultiPlayerPanel
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MultiPlayerBtn_Click(object sender, EventArgs e)
        {

            Task mytask = Task.Run(() =>
            {
                SetDownloadText("Telechargement des cartes....");
                FonctionsNatives.executeDownloadMaps();
                SetDownloadText("done");


            });

            MultiPlayerPanel.Visible = true;
            MainPanel.Visible = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void RetourSPBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet de changer le paneau SinglePlayerPanel et MainPanel
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void RetourSPBtn_Click(object sender, EventArgs e)
        {
            SinglePlayerPanel.Visible = false;
            MainPanel.Visible = true;
        }



        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void RetourMPBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet de changer le paneau MultiPlayerPanel et MainPanel
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void RetourMPBtn_Click(object sender, EventArgs e)
        {
            MultiPlayerPanel.Visible = false;
            MainPanel.Visible = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PRapideBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet d'ouvrir le paneau Partie Rapide
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PRapideBtn_Click(object sender, EventArgs e)
        {
            SetUpPartieRapide();
            tabControl1.SelectedTab = QuickGameTab;
            SinglePlayerPanel.Visible = false;
            MainPanel.Visible = true;
            QuickGameTab.Focus();
            // Reload la liste des maps
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void CampagneBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet d'ouvrir le paneau  Campagne
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void CampagneBtn_Click(object sender, EventArgs e)
        {
            SetUpCampaign();
            tabControl1.SelectedTab = CampaignTab;
            SinglePlayerPanel.Visible = false;
            MainPanel.Visible = true;
            CampaignTab.Focus();
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Populate_avatarPanel()
        /// @brief Fonction qui permet de generer le paneau d'Avatars
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Populate_avatarPanel()
        {
            string[] avatars = new string[] { };
            avatars = Directory.GetFiles(Application.StartupPath + @"\media\avatars", "*.jpg");
            avatarPanel.ColumnCount = (int)Math.Ceiling((double)avatars.Length / (double)2);

           
            // Clear dynamically allocated Controls
            avatarPanel.Controls.Clear();
            foreach (Control item in avatarPanel.Controls.OfType<PictureBox>())
            {
                avatarPanel.Controls.Remove(item);
            }
            
            // Populate the avatar Panel with avatars that are unlocked
            foreach (string file in avatars)
            {
                PictureBox pb = new PictureBox();
                pb.Width = 50;
                pb.Height = 50;
                pb.Image = Image.FromFile(file );
                // Add name to tag to extract after
                pb.Tag = Path.GetFileNameWithoutExtension(file);
                // Grey out disabled avatars, fucking black magic
                if (!playerInfo.unlockedAvatars.Contains(pb.Tag.ToString()))
                {
                    pb.Enabled = false;
                    pb.Image =  ToolStripRenderer.CreateDisabledImage(pb.Image);
                }
                pb.SizeMode = PictureBoxSizeMode.StretchImage;
                pb.Click += SelectAvatar;
                avatarPanel.Controls.Add(pb);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void CampagneBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet de selectionner l'avatar
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void SelectAvatar(object avatarBox, EventArgs e)
        {
            // because casting stuff to PictureBox doesn't work....
            PictureBox pBox = avatarBox as PictureBox;
            AvatarBox.Image = pBox.Image;
            avatarName = pBox.Tag.ToString();
        }




        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void CreateBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet d'ouvrir le paneau  Creation de jeu Multiplayer
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void CreateBtn_Click(object sender, EventArgs e)
        {
            SetUpMultiplayerCreate();
            tabControl1.SelectedTab = LobbyTab;
            MultiPlayerPanel.Visible = false;
            MainPanel.Visible = true;
            LobbyTab.Focus();
            // Reload la liste des maps
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void JoinBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet d'ouvrir le paneau  Join de jeu Multiplayer
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void JoinBtn_Click(object sender, EventArgs e)
        {
            SetUpMultiplayerJoin();
            tabControl1.SelectedTab = MPGameSelectTab;
            MultiPlayerPanel.Visible = false;
            MainPanel.Visible = true;
            LobbyTab.Focus();
            // Reload la liste des maps
            RefreshBtn.PerformClick();
        }

      


    }
}
