using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;

namespace InterfaceGraphique
{
    partial class MenuComplet
    {
      

        ///< Path des fichiers de zones
        ///string MultiplayerJoinFileNames;

        List<string> MultiplayerJoinZonesCampagne;

        int gameTime;
        string[] mapsToJoin;
        ///< Liste des zones de la campagne.
        StringBuilder MultiplayerJoinPathMap;

        /// <summary>
        /// player est Pret ou Non
        /// </summary>
        bool playerReady = false;

        bool stopCalling = false;
        // Fonction qui set up le paneau de multiplayer
        private void SetUpMultiplayerJoin()
        {

            playerReady = false;
            stopCalling = false;
            MPJoinReadyBtn.Text = "Pret";
            MPJoinReadyBtn.ForeColor = Color.Gold;
            MPJoinPanel.Location = new Point(
                MPJoinPanel.Parent.Width / 2 - MPJoinPanel.Size.Width / 2,
                MPJoinPanel.Parent.Height / 2 - MPJoinPanel.Size.Height / 2);
            MPJoinPanel.Anchor = AnchorStyles.None;

            MPJoinGameSelectPanel.Location = new Point(
               MPJoinGameSelectPanel.Parent.Width / 2 - MPJoinGameSelectPanel.Size.Width / 2,
               MPJoinGameSelectPanel.Parent.Height / 2 - MPJoinGameSelectPanel.Size.Height / 2);
            MPJoinGameSelectPanel.Anchor = AnchorStyles.None;
            MPJoinScreenShot.SizeMode = PictureBoxSizeMode.StretchImage;
            MPJoinGameView.Items.Clear();
            MPJoinGameView.SelectedItems.Clear();
            GameListView.Items.Clear();
            foreach (var item in GameListView.Items)
            {
                ((IDisposable)item).Dispose();
                
            }

          
            RefreshBtn.PerformClick();
        }

        private void MultiplayerJoinPlayerStatus(Object source, ElapsedEventArgs e)
        {
            UpdatePlayersInfo();
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void DisplayScreenShot()
        /// @brief Fonction qui affiche la capture d'ecran du jeu choisi
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void quickJoin()
        {
            stopCalling = false;
            MPJoinReadyBtn.Text = "Pret";
            MPJoinReadyBtn.ForeColor = Color.Gold;
           GenerateGameInfo();
        }


        private void startJoinTimer()
        {
            playersTimer = new System.Timers.Timer(1000);
            playersTimer.SynchronizingObject = this;
            playersTimer.Elapsed += MultiplayerJoinPlayerStatus;
            playersTimer.AutoReset = true;
            playersTimer.Start();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MPJoinReturnBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui remet l'usager dans le menu principal
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MPJoinReturnBtn_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = MainTab;
            MainTab.Focus();
            MainPanel.Visible = false;
            MultiPlayerPanel.Visible = true;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MPJoinSelectBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui entre dans le jeu choisi et change le paneau visible
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MPJoinSelectBtn_Click(object sender, EventArgs e)
        {
            StringBuilder hostName = new StringBuilder(MPJoinGameView.SelectedItems[0].Text);
            StringBuilder mapName = new StringBuilder(MPJoinGameView.SelectedItems[0].SubItems[1].Text);
            StringBuilder joinPassword = new StringBuilder(MPJoinPasswordTBox.Text);

            if (FonctionsNatives.joinGame(hostName, mapName, joinPassword))
            {

              GenerateGameInfo();
              MPJoinPasswordTBox.Clear();

            }
            else
            {
                MPJoinErrorLabel.Text = "Probleme de connexion avec le serveur!";
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MPJoinBackBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui revient au menu de selection de jeu
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MPJoinBackBtn_Click(object sender, EventArgs e)
        {
         

            if (playersTimer.Enabled)
            {
                playersTimer.AutoReset = false;
                playersTimer.Stop();
                playersTimer.Dispose();
            }
            FonctionsNatives.leaveGame();
            GameListView.Items.Clear();
            foreach (var item in GameListView.Items)
            {
                ((IDisposable)item).Dispose();

            }
            
            MPJoinGameSelectPanel.Visible = true;
            MPJoinPanel.Visible = false;
            
            RefreshBtn.PerformClick();


        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void RefreshBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui rafraichit la liste des jeux disponibles
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void RefreshBtn_Click(object sender, EventArgs e)
        {
            // TODO: Refresh games list
            // structure des donnes : HOSTNAME: MAPNAME
            // de cette manier, nous avons une facon unique d'identifer les maps

            // Dispose of all previous items, cast to IDisposable to prevent memory leaks
            MPJoinGameView.Items.Clear();
            foreach (var item in MPJoinGameView.Items)
            {
                ((IDisposable)item).Dispose();
            }
            MPJoinSelectBtn.Enabled = false;
            string gamesList = FonctionsNatives.GetAvailableGames();
            if (gamesList == "false")
            {
                failCounter++;
                totalDisconnect();
                return;
            }
            else
            {
                failCounter = 0;
                
            }



            string[] separateGames = gamesList.Split('\n');
            string gameType;
            string gameStatus = ""; 
            string gameNumber;
            foreach (string tempString in separateGames)
            {
                if (!String.IsNullOrEmpty(tempString))
                {
                    string[] gameInfo = tempString.Split(':');
                    if (gameInfo[1].Split(';').Length > 1)
                    {
                        gameNumber = "Multiple";
                    }
                    else
                    {
                        gameNumber = gameInfo[1];
                    }
                    if (gameInfo[2] == "1")
                    {
                        gameType = "Cooperatif";
                    }
                    else
                    {
                        gameType = "Competitif";
                    }
                    
                    if (gameInfo[3] == "L")
                    {
                        gameStatus = "Lobby";
                    }
                    else if (gameInfo[3] == "G")
                    {
                        gameStatus = "Rejoindre";
                    }
                    var item = new ListViewItem(new[] { gameInfo[0], gameNumber, gameType, gameStatus, gameInfo[1] });
                    MPJoinGameView.Items.Add(item);
                }
                    
            }
        }



        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MPJoinReadyBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui dis au serveur que la personne est prette a joindre ou non la game
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MPJoinReadyBtn_Click(object sender, EventArgs e)
        {
            playerReady = !playerReady;
            FonctionsNatives.playerIsReady(playerReady);

            if (playerReady)
            {
                MPJoinReadyBtn.Text = "Pas Encore";
                MPJoinReadyBtn.ForeColor = Color.Red;
            }
            else
            {
                MPJoinReadyBtn.Text = "Pret";
                MPJoinReadyBtn.ForeColor = Color.Gold;
            }

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void UpdatePlayersInfo()
        /// @brief Fonction qui poll le serveur pour avoir le status de tous les joueurs
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void UpdatePlayersInfo()
        {
            MPJoinPlayersView.Items.Clear();
            foreach (var item in MPJoinPlayersView.Items)
            {
                ((IDisposable)item).Dispose();
            }
            if (FonctionsNatives.isGameStarted())
            {
               
                playersTimer.AutoReset = false;
                playersTimer.Stop();
                playersTimer.Dispose();
                if (!stopCalling)
                {
                stopCalling = true;
                LancerModeJeu(MultiplayerJoinZonesCampagne, typeJoueur, gameTime, MPJoinIDLabel.Enabled, true);                    
                }
            }
            else
            {
                string rawPlayersInfo = FonctionsNatives.GetPlayersInfo();
                if (rawPlayersInfo == "false")
                {
                    failCounter++;
                    totalDisconnect();
                    return;
                }
                else
                {
                    failCounter = 0 ;
                    
                }
                Dictionary<string, string> playersInfo = Outils.ProprieteStringToDictionnay(rawPlayersInfo);
                foreach (KeyValuePair<string, string> playerStatus in playersInfo)
                {
                    var item = new ListViewItem(new[] { playerStatus.Key, playerStatus.Value });
                    if (playerStatus.Key == "DEAD" && playerStatus.Value == "DEAD")
                    {
                        MPJoinBackBtn.PerformClick();
                    }
                    MPJoinPlayersView.Items.Add(item);
                }
                MPJoinPlayersView.Items[0].ForeColor = Color.AliceBlue;
                MPJoinPlayersView.Items[1].ForeColor = Color.Aqua;
                MPJoinPlayersView.Items[2].ForeColor = Color.Red;
                MPJoinPlayersView.Items[3].ForeColor = Color.Green;
                Program.playerNames.Clear();
                for (int i = 0; i < MPJoinPlayersView.Items.Count; i++)
                {
                    Program.playerNames.Add(MPJoinPlayersView.Items[i].Text);
                }
            }
            
        }

        private void GenerateGameInfo()
        {
            var rawGameInfo = FonctionsNatives.GetGameInfo();
            if (rawGameInfo == "false")
            {
                return;
            }
            string[] gameInfo = rawGameInfo.Split(':');
           // mapsToJoin = MPJoinGameView.SelectedItems[0].SubItems[4].Text.Split(';');
            if (gameInfo[0].Split(';').Length > 1)
            {
                mapsToJoin = gameInfo[0].Split(';');
            }
            else
            {
                mapsToJoin = new string[1];
                mapsToJoin[0] = gameInfo[0];
            }
            MPJoinMapName.Text = mapsToJoin[0];
          

            if (gameInfo[1] == "1")
            {
                MPJoinGameTypeLabel.Text = "Cooperatif";
            }
            else
            {
                MPJoinGameTypeLabel.Text = "Competitif";

            }
            if (gameInfo[3] == "1")
            {
                MPJoinIDLabel.Enabled = true;
            }
            else
            {
                MPJoinIDLabel.Enabled = false;
            }
            gameTime = Convert.ToInt32(gameInfo[2]);
            if (gameTime > 0)
            {
                MPJoinTimeLabel.Enabled = true;
                MPJoinTimeValue.Text = gameTime.ToString();
            }
            else
            {
                MPJoinTimeLabel.Enabled = false;
                MPJoinTimeValue.Text = "";
            }

            if (File.Exists(Application.StartupPath + @"\zones\" + mapsToJoin[0] + ".jpg") || File.Exists(Application.StartupPath + @"\zones\marketplace\" + mapsToJoin[0] + ".jpg"))
            {
                if (File.Exists(Application.StartupPath + @"\zones\" + mapsToJoin[0] + ".jpg"))
                    MPJoinScreenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\" + mapsToJoin[0] + ".jpg");
                else if (File.Exists(Application.StartupPath + @"\zones\marketplace\" + mapsToJoin[0] + ".jpg"))
                {
                    MPJoinScreenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\marketplace\" + mapsToJoin[0] + ".jpg");
                    
                }
                MultiplayerJoinZonesCampagne = new List<string>();
                int i = 0;
                foreach (string map in mapsToJoin)
                {
                    if (!String.IsNullOrEmpty(map))
                    {
                        if (File.Exists(Application.StartupPath + @"\zones\" + map + ".xml"))
                        {
                            MultiplayerJoinZonesCampagne.Insert(i, Application.StartupPath + @"\zones\" + map + ".xml");
                        }
                        else if (File.Exists(Application.StartupPath + @"\zones\marketplace\" + map + ".xml"))
                        {
                            MultiplayerJoinZonesCampagne.Insert(i, Application.StartupPath + @"\zones\marketplace\" + map + ".xml");

                        }
                        //MultiplayerJoinZonesCampagne.Insert(i, Application.StartupPath + @"\zones\" + map + ".xml");
                        i++;
                        var tempItemp = new ListViewItem(new[] { map });
                        GameListView.Items.Add(tempItemp);
                        GameListView.View = View.Details;

                    }

                }
                foreach (var a in GameListView.Items)
                {
                    Console.WriteLine(a);
                }
            }
            else
            {
                MPJoinScreenShot.Image = Properties.Resources.SaintTrinity;
            }

            MPJoinGameSelectPanel.Visible = false;
            MPJoinPanel.Visible = true;
            MPJoinErrorLabel.Text = "";

            startJoinTimer();
        }

        private void MPJoinPlayersView_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            e.Item.Selected = false;
        }

        private void GameListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (GameListView.SelectedIndices.Count <= 0) return;
            int index = GameListView.SelectedIndices[0];
            if (index >= 0)
            {
                string map = GameListView.Items[index].Text;
                MPJoinScreenShot.SizeMode = PictureBoxSizeMode.StretchImage;
                if (File.Exists(Application.StartupPath + @"\zones\" + map + ".jpg"))
                {
                    MPJoinScreenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\" + map + ".jpg");
                    MPJoinMapName.Text = map;
                }
                else if (File.Exists(Application.StartupPath + @"\zones\marketplace\" + map + ".jpg"))
                {
                    MPJoinScreenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\marketplace\" + map + ".jpg");
                    MPJoinMapName.Text = map;
                }
                else
                {
                    MPJoinScreenShot.Image = Properties.Resources.SaintTrinity;
                }
            }
        }

     
      

        private void MPJoinGameView_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            MPJoinSelectBtn.Enabled = true;
        }

        private void GenerateMapList()
        {
            
        }


    }
}
