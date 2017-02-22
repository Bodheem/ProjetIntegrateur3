using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    partial class MenuComplet
    {
        string[] MutliPlayerFilePaths; ///< Path des fichiers de zones
        string MultiplayerFileNames;
        List<string> MultiplayerZonesCampagne; ///< Liste des zones de la campagne.
        StringBuilder MultiplayerPathMap;
        public System.Timers.Timer playersTimer;
        private bool startedGame = false;
        private bool mpTutorial = false;
        // Fonction qui set up le paneau de multiplayer
        private void SetUpMultiplayerCreate(bool isTutorial = false)
        {

            MPZonesDisponibles.Visible = true;
            AddMPGameBtn.Enabled = false;
            RemoveMPGameBtn.Enabled = false;
            EmptyMPGameBtn.Enabled = false;
            mpTutorial = isTutorial;
            startedGame = false;
            time = 0;
            // Center Panel
            MPCreateRoomBtn.Enabled = false;
            MPCreateStartBtn.Enabled = false;
            MPCreatePanel.Location = new Point(
                  MPCreatePanel.Parent.Width / 2 - MPCreatePanel.Size.Width / 2,
              MPCreatePanel.Parent.Height / 2 - MPCreatePanel.Size.Height / 2);
            MPCreatePanel.Anchor = AnchorStyles.None;

            // Initial Set-Up
            MutliPlayerFilePaths = Directory.GetFiles(Application.StartupPath + @"\zones", "*.xml");
            MultiplayerZonesCampagne = new List<string>();
            MPZonesDisponibles.Items.Clear();
            joinedPlayerView.Items.Clear();
            MPGameSelected.Items.Clear();
            foreach (var item in joinedPlayerView.Items)
            {
                ((IDisposable)item).Dispose();
            }
            foreach (var item in MPGameSelected.Items)
            {
                ((IDisposable)item).Dispose();
            }

            foreach (string s in MutliPlayerFilePaths)
            {
                MultiplayerPathMap = new StringBuilder(s);
                diff = FonctionsNatives.obtenirDifficulte(MultiplayerPathMap, MultiplayerPathMap.Capacity);
                MultiplayerFileNames = Path.GetFileNameWithoutExtension(s);
                var tempItemp = new ListViewItem(new[] { MultiplayerFileNames, diff.ToString() });
                MPZonesDisponibles.Items.Add(tempItemp);
            }
            Array.Clear(MutliPlayerFilePaths, 0, MutliPlayerFilePaths.Length);
            MutliPlayerFilePaths = Directory.GetFiles(Application.StartupPath + @"\zones\marketplace", "*.xml");
            foreach (string s in MutliPlayerFilePaths)
            {
                MultiplayerPathMap = new StringBuilder(s);
                diff = FonctionsNatives.obtenirDifficulte(MultiplayerPathMap, MultiplayerPathMap.Capacity);
                MultiplayerFileNames = Path.GetFileNameWithoutExtension(s);
                if (playerInfo.unlockedMaps.Contains(MultiplayerFileNames))
                {
                    var tempItemp = new ListViewItem(new[] { MultiplayerFileNames, diff.ToString() });
                    MPZonesDisponibles.Items.Add(tempItemp);
                }
              
            }


            MPZonesDisponibles.Visible = true;
            MPPasswordTBox.Enabled = true;
            MPCreateCBoxTime.Enabled = true;
            MPCreateCBoxTime.Checked = false;
            MPCreateCBoxID.Enabled = true;
            SetUpMultiplayerTimeButtons(false);
            MPTimerLabel.Enabled = true;
            MpInstaDeathLabel.Enabled = true;
            MPCreateGModeCBox.Enabled = true;
            MPCreateGModeLabel.Enabled = true;


            MPZonesDisponiblesLabel.Visible = true;
            MPCreateRoomBtn.Enabled = false;
            RemoveMPGameBtn.Enabled = false;
            EmptyMPGameBtn.Enabled = false;
            AddMPGameBtn.Enabled = false;
            if (mpTutorial)
            {
                int x = MPCreatePanel.Location.X - GameTutoPanel.Size.Width;
                int y = MPCreatePanel.Location.Y;
                GameTutoPanel.Location = new Point(x, y);
                GameTutoLabel.Text = tutorialGame.initTutorialGame();
                GameTutoPanel.Show();
                MPZonesDisponibles.Visible = false;
                AddMPGameBtn.Visible = false;
                MPGameSelected.Visible = false;
                RemoveMPGameBtn.Visible = false;
                EmptyMPGameBtn.Visible = false;
                MPCreateCancelBtn.Enabled = false;
            }

        }

        private void startTimer()
        {
            playersTimer = new System.Timers.Timer(1000);
            playersTimer.SynchronizingObject = this;
            playersTimer.Elapsed += OnTimedEvent;
            playersTimer.AutoReset = true;
            playersTimer.Start();

            
        }

        private void OnTimedEvent(Object source, ElapsedEventArgs e)
        {
            UpdatePlayerInfoCreateGame();
        }




        ////////////////////////////////////////////////////////////////////////
        /// @fn private void MPZonesDisponibles_SelectedIndexChanged(object sender, EventArgs e)
        /// @brief Affichage de l'image lorsqu'on clique sur un zone disponible dans la liste.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ////////////////////////////////////////////////////////////////////////
        private void MPZonesDisponibles_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (MPZonesDisponibles.SelectedIndices.Count <= 0) return;
            int index = MPZonesDisponibles.SelectedIndices[0];
            if (index >= 0)
            {
                MultiplayerFileNames = MPZonesDisponibles.Items[index].Text;
                MPScreenShot.SizeMode = PictureBoxSizeMode.StretchImage;
                if (File.Exists(Application.StartupPath + @"\zones\" + MultiplayerFileNames + ".jpg"))
                {
                    MPScreenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\" + MultiplayerFileNames + ".jpg");
                }
                else if (File.Exists(Application.StartupPath + @"\zones\marketplace\" + MultiplayerFileNames + ".xml"))
                    {
                        MPScreenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\marketplace\" + MultiplayerFileNames + ".jpg");


                    }
                else {
                    MPScreenShot.Image = Properties.Resources.SaintTrinity;
                }
                AddMPGameBtn.Enabled = true;
            }
        }




        private void AddMPGameBtn_Click(object sender, EventArgs e)
        {
            int index = MPZonesDisponibles.SelectedIndices[0];
            if (index >= 0)
            {

                var item1 = new ListViewItem(new[] { MPZonesDisponibles.Items[index].SubItems[0].Text, MPZonesDisponibles.Items[index].SubItems[1].Text });

                MPGameSelected.Items.Add(item1);
                MPCreateRoomBtn.Enabled = true;
                EmptyMPGameBtn.Enabled = true;
                if (mpTutorial && tutorialGame.CurrentMessageGame == 3)
                {
                    GameTutoNext.Enabled = true;
                    GameTutoNext.PerformClick();
                }
                
            }
            
        }

        private void EmptyMPGameBtn_Click(object sender, EventArgs e)
        {
           
            MPGameSelected.Items.Clear();
            foreach (var item in MPGameSelected.Items)
            {
                ((IDisposable)item).Dispose();
            }
            EmptyMPGameBtn.Enabled = false;
            RemoveMPGameBtn.Enabled = false;
            MPCreateRoomBtn.Enabled = false;


        }


        private void RemoveMPGameBtn_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem eachItem in MPGameSelected.SelectedItems)
            {
                MPGameSelected.Items.Remove(eachItem);
            }
            if (MPGameSelected.Items.Count == 0)
            {
                EmptyMPGameBtn.Enabled = false;
                MPCreateRoomBtn.Enabled = false;
            }
            RemoveMPGameBtn.Enabled = false;

        }


        private void MPGameSelected_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (MPGameSelected.SelectedIndices.Count <= 0) return;
            int index = MPGameSelected.SelectedIndices[0];
            if (index >= 0)
            {
                MultiplayerFileNames = MPGameSelected.Items[index].Text;
                MPScreenShot.SizeMode = PictureBoxSizeMode.StretchImage;
                if (File.Exists(Application.StartupPath + @"\zones\" + MultiplayerFileNames + ".jpg"))
                {
                    MPScreenShot.Image =
                        Image.FromFile(Application.StartupPath + @"\zones\" + MultiplayerFileNames + ".jpg");
                }
                else
                {
                    MPScreenShot.Image = Properties.Resources.SaintTrinity;
                }
                if (MPZonesDisponiblesLabel.Visible)
                {
                    RemoveMPGameBtn.Enabled = true;
                }
            }
            else
            {
                RemoveMPGameBtn.Enabled = false;
            }
        }



        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MPCreateStartBtn_Click(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on clique sur le bouton OK.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MPCreateStartBtn_Click(object sender, EventArgs e)
        {
            if (MPZonesDisponibles.SelectedItems.Count != 0)
            {
               // MultiplayerZonesCampagne.Clear();
               // MultiplayerZonesCampagne.Insert(0, Application.StartupPath + @"\zones\" + MPZonesDisponibles.SelectedItems[0].Text + ".xml");
                if (MPCreateCBoxTime.Checked)
                {
                    time = Convert.ToInt32(MPtimeLabel.Text);
                }

                // TODO: NOT YET
                if (FonctionsNatives.startGame())
                {
                  
                    startedGame = true;
                    playersTimer.AutoReset = false;
                    playersTimer.Stop();
                    playersTimer.Dispose();
                    FonctionsNatives.GetGameInfo();
                    LancerModeJeu(MultiplayerZonesCampagne, typeJoueur, time, MPCreateCBoxID.Checked,true);
                    Console.WriteLine("NIGGAZ READY, EVERYTHING WORKED");
                }
                else
                {
                    startedGame = false;
                    Console.WriteLine("NIGGAZ AINT READY OR SOMETHING HAPPENED");

                }
            }
            else
            {
                MessageBox.Show("Selectionnez une zone pour commencer la partie", "ERREUR DE LANCEMENT",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }



        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MPCreateCancelBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui revenir au menu SinglePlayer
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MPCreateCancelBtn_Click(object sender, EventArgs e)
        {
            if ( playersTimer != null && playersTimer.Enabled)
            {
                playersTimer.AutoReset = false;
                playersTimer.Stop();
                playersTimer.Dispose();
            }
            tabControl1.SelectedTab = MainTab;
            if (startedGame)
            {
                FonctionsNatives.leaveGame();
                Console.WriteLine("LEAVING GAME");
            }
            MultiplayerZonesCampagne.Clear();
            MPZonesDisponibles.Enabled = true;
            MainTab.Focus();
            startedGame = false;
            MainPanel.Visible = false;
            if (mpTutorial)
            {
                MainPanel.Visible = true;
            }
            else
            {
                MultiPlayerPanel.Visible = true;
            }
        }



        ///////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MPCreateRoomBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui affiche la partie sur le serveur
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MPCreateRoomBtn_Click(object sender, EventArgs e)
        {

            // TODO: LOGIQUE DE L"AFFICHAGE DE LA PARTIE
            // On envoie le nom, le password au C++, le hostname est obtenu a partir du C++
            StringBuilder password = new StringBuilder( MPPasswordTBox.Text );
            StringBuilder mapName =  new StringBuilder( "");
            int i = 0;
            MultiplayerZonesCampagne.Clear();
            if (MPGameSelected.Items.Count > 1)
            {
                foreach (ListViewItem eachItem in MPGameSelected.Items)
                {
                    mapName.Append(eachItem.Text + ";");
                    if (File.Exists(Application.StartupPath + @"\zones\" + eachItem.Text + ".xml"))
                    {
                        MultiplayerZonesCampagne.Insert(i, Application.StartupPath + @"\zones\" + eachItem.Text + ".xml");
                    }
                    else if (File.Exists(Application.StartupPath + @"\zones\marketplace\" + eachItem.Text + ".xml"))
                    {
                        MultiplayerZonesCampagne.Insert(i, Application.StartupPath + @"\zones\marketplace\" + eachItem.Text + ".xml");
                        
                    }
                    i++;
                }
            }
            else
            {
                mapName.Append(MPGameSelected.Items[0].Text);
                if (File.Exists(Application.StartupPath + @"\zones\" + mapName + ".xml"))
                {
                    MultiplayerZonesCampagne.Insert(i, Application.StartupPath + @"\zones\" + mapName + ".xml");
                }
                else if (File.Exists(Application.StartupPath + @"\zones\marketplace\" + mapName + ".xml"))
                {
                    MultiplayerZonesCampagne.Insert(i, Application.StartupPath + @"\zones\marketplace\" + mapName + ".xml");

                }
            }
          
            bool instaDeath = MPCreateCBoxID.Checked;
            int gameTime = -5;
            if(MPCreateCBoxTime.Checked)
            {
                gameTime = Convert.ToInt32(MPtimeLabel.Text);
            }
            else
            {
                gameTime = -5;
            }
            int gameType;
            if (MPCreateGModeCBox.Checked)
            {
                gameType = 2;
            }
            else
            {
                gameType = 1;
            }

            if (!mpTutorial)
            {
                if (FonctionsNatives.createGame(mapName, password, instaDeath, gameTime, gameType))
                {
                    
                }
                startedGame = true;
               
                startTimer();  
            }
            else
            {
                //TODO NICOLAS
            }
            // TODO : OPTIONAL IMPLEMENTATION <- BLOCK THE GAME SELECTION, THE HOST CHOSES THE GAME AND DOESN'T GET TO PICK A NEW MAP ANYMORE
            // SIMPLIFIES ALL THE LOGIC FROM NOW ONE
            MPCreateStartBtn.Enabled = false;
            MPZonesDisponibles.Visible = false;
            MPPasswordTBox.Enabled = false;
            MPCreateCBoxTime.Enabled = false;
            MPCreateCBoxID.Enabled = false;
            SetUpMultiplayerTimeButtons(false);
            MPTimerLabel.Enabled = false;
            MpInstaDeathLabel.Enabled = false;
            MPCreateGModeCBox.Enabled = false;
            MPCreateGModeLabel.Enabled = false;

            MPZonesDisponiblesLabel.Visible = false;
            MPCreateRoomBtn.Enabled = false;
            RemoveMPGameBtn.Enabled = false;
            EmptyMPGameBtn.Enabled = false;
            AddMPGameBtn.Enabled = false;


        }

        private void GameTutoCancel_Click(object sender, EventArgs e)
        {
            MPCreateCancelBtn.Enabled = true;
            tutorialGame.initTutorialGame();
            GameTutoNext.Enabled = true;
            MPCreateCancelBtn.PerformClick();
        }

        private void GameTutoNext_Click(object sender, EventArgs e)
        {
            if (tutorialGame.CurrentMessageGame == 8)
                GameTutoCancel.PerformClick();
            else
                GameTutoLabel.Text = tutorialGame.updateMessageGame();
            if (/*tutorialGame.CurrentMessageGame >= 3 && tutorialGame.CurrentMessageGame <= 6*/ true)
            {
                switch (tutorialGame.CurrentMessageGame)
                {
                    case 2:
                        GameTutoNext.Enabled = true;

                        break;
                    case 3: 
                        
                        MPZonesDisponibles.Visible = true;
                        AddMPGameBtn.Visible = true;
                        MPGameSelected.Visible = true;
                        RemoveMPGameBtn.Visible = true;
                        EmptyMPGameBtn.Visible = true;
                        MPZonesDisponiblesLabel.ForeColor = Color.Cyan;
                        break;
                    case 4:
                        MPZonesDisponiblesLabel.ForeColor = Color.Gold;
                        MPCreateGModeLabel.ForeColor = Color.Cyan;
                        break;
                    case 5:
                        MpInstaDeathLabel.ForeColor = Color.Cyan;
                        MPCreateGModeLabel.ForeColor = Color.Gold;
                        break;
                    case 6:
                        MPTimerLabel.ForeColor = Color.Cyan;
                        MpInstaDeathLabel.ForeColor = Color.Gold;
                        break;
                    case 7:
                        MPTimerLabel.ForeColor = Color.Gold;
                        break;


                }
                if (tutorialGame.CurrentMessageGame >= 3 && tutorialGame.CurrentMessageGame <= 6)
                    GameTutoNext.Enabled = false;
                
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void UpdatePlayerInfoCreateGame()
        /// @brief Fonction qui poll le serveur pour avoir le status de tous les joueurs
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void UpdatePlayerInfoCreateGame()
        {
            joinedPlayerView.Items.Clear();
            foreach (var item in joinedPlayerView.Items)
            {
                ((IDisposable)item).Dispose();
            }

            string rawPlayersInfo = FonctionsNatives.GetPlayersInfo();
            if (rawPlayersInfo == "false")
            {
                failCounter++;
                totalDisconnect();
                return;
            }
            else
            {
                failCounter = 0;
                
            }
            Dictionary<string, string> playersInfo = Outils.ProprieteStringToDictionnay(rawPlayersInfo);
            MPCreateStartBtn.Enabled = true;

            foreach (KeyValuePair<string, string> playerStatus in playersInfo)
            {
                var item = new ListViewItem(new[] { playerStatus.Key, playerStatus.Value });
                joinedPlayerView.Items.Add(item);
                if (playerStatus.Value == "NOT")
                {
                    MPCreateStartBtn.Enabled = false;
                }
            }
            // can't start the game if you're the only person in the game
            if (joinedPlayerView.Items[1].Text =="PLAYER2" &&
                joinedPlayerView.Items[2].Text =="PLAYER3" &&
                joinedPlayerView.Items[3].Text =="PLAYER4")
            {
                MPCreateStartBtn.Enabled = false;
            }

            Program.playerNames.Clear();
            for (int i = 0; i < joinedPlayerView.Items.Count; i++)
            {
                Program.playerNames.Add(joinedPlayerView.Items[i].Text);
            }
            if (joinedPlayerView.Items.Count > 3)
            {
                joinedPlayerView.Items[0].ForeColor = Color.AliceBlue;
                joinedPlayerView.Items[1].ForeColor = Color.Aqua;
                joinedPlayerView.Items[2].ForeColor = Color.Red;
                joinedPlayerView.Items[3].ForeColor = Color.Green;

            }
           


        }



        #region GameModes

        private void MPCreateGModeCBox_CheckedChanged(object sender, EventArgs e)
        {
            if (MPCreateGModeCBox.Checked)
            {
                MPCreateGModeCBox.BackgroundImage = Properties.Resources.buttonStock1h;
                MPCreateGModeLabel.Text = "COMPETITIF";
                MPCreateGModeLabel.ForeColor = Color.Red;
                if (mpTutorial && tutorialGame.CurrentMessageGame == 4)
                {
                    GameTutoNext.Enabled = true;
                    GameTutoNext.PerformClick();
                }
            }
            else
            {
                MPCreateGModeCBox.BackgroundImage = smallBorder;
                MPCreateGModeLabel.Text = "COOPERATIF";
                MPCreateGModeLabel.ForeColor = Color.Gold;

            }
        }
     


        private void MPCreateCBoxID_CheckedChanged(object sender, EventArgs e)
        {
            if (MPCreateCBoxID.Checked)
            {
                MPCreateCBoxID.BackgroundImage = Properties.Resources.buttonStock1h;
                MPCreateCBoxID.Text = "✓";
                if (mpTutorial && tutorialGame.CurrentMessageGame == 5)
                {
                    GameTutoNext.Enabled = true;
                    GameTutoNext.PerformClick();
                }
            }
            else
            {
                MPCreateCBoxID.Text = "";
                MPCreateCBoxID.BackgroundImage = smallBorder;

            }
        }


        private void MPCreateCBoxTime_CheckedChanged(object sender, EventArgs e)
        {
            if (MPCreateCBoxTime.Checked)
            {
                MPCreateCBoxTime.BackgroundImage = Properties.Resources.buttonStock1h;
                MPCreateCBoxTime.Text = "✓";
                SetUpMultiplayerTimeButtons(true);
                if (mpTutorial && tutorialGame.CurrentMessageGame == 6)
                {
                    GameTutoNext.Enabled = true;
                    GameTutoNext.PerformClick();
                }
            }
            else
            {
                MPCreateCBoxTime.Text = "";
                MPCreateCBoxTime.BackgroundImage = smallBorder;
                SetUpMultiplayerTimeButtons(false);
            }
        }


        private void MPCreateMinus_Click(object sender, EventArgs e)
        {
            time = Convert.ToInt32(MPtimeLabel.Text);
            if (time > 1)
            {
                time--;
                if (time == 1)
                {
                    MPCreateMinus.Enabled = false;
                }
                MPCreatePlusBtn.Enabled = true;
                MPtimeLabel.Text = time.ToString();
            }
        }

        private void MPCreatePlusBtn_Click(object sender, EventArgs e)
        {
            time = Convert.ToInt32(MPtimeLabel.Text);
            if (time < 10)
            {
                time++;
                if (time == 10)
                {
                    MPCreatePlusBtn.Enabled = false;
                }
                MPCreateMinus.Enabled = true;
                MPtimeLabel.Text = time.ToString();
            }
        }



        private void SetUpMultiplayerTimeButtons(bool activate)
        {
            MPCreateMinus.Enabled = activate;
            MPCreatePlusBtn.Enabled = activate;
            MPtimeLabel.Enabled = activate;
            MPTimeLimitLabel.Enabled = activate;
        }


        #endregion


        #region Misc

        private void joinedPlayerView_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            e.Item.Selected = false;
        }

      

        #endregion
    }





}