using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;

namespace InterfaceGraphique
{
    partial class MenuComplet
    {
        private string currentAvatar = "";
        private string currentMap = "";
        private int currentMapPrice = 15;
        private int currentAvatarPrice = 15;
        private string[] marketplaceMaps;
        private List<string> marketplaceList; 
          // Fonction qui set up le paneau de multiplayer
        private void SetUpMarketPlace()
        {
           MarketplaceTab.Controls.Add(PlayerInfoPanel);
            BuyAvatarButton.Enabled = false;
           togglePlayerInfo = true;
           AvatarBox_Click(AvatarBox, null);
           AvatarBox.Click -= AvatarBox_Click;
            MarketPlacePanel.Location = new Point(
               MarketPlacePanel.Parent.Width / 2 - MarketPlacePanel.Size.Width / 2,
               MarketPlacePanel.Parent.Height / 2 - MarketPlacePanel.Size.Height / 2);
            MarketPlacePanel.Anchor = AnchorStyles.None;

            MarketPlaceMapPanel.Location = new Point(
               MarketPlaceMapPanel.Parent.Width / 2 - MarketPlaceMapPanel.Size.Width / 2,
               MarketPlaceMapPanel.Parent.Height / 2 - MarketPlaceMapPanel.Size.Height / 2);
            MarketPlaceMapPanel.Anchor = AnchorStyles.None;

            MarketPlaceReturnBtn.Location = new Point(
               MarketPlaceReturnBtn.Parent.Width - MarketPlaceReturnBtn.Size.Width - 15,
               MarketPlaceReturnBtn.Parent.Height - MarketPlaceReturnBtn.Size.Height - 25);
            MarketPlaceReturnBtn.Anchor = AnchorStyles.None;

            AvatarPanelButton.Location = new Point(
                MarketPlaceReturnBtn.Location.X,
                MarketPlaceReturnBtn.Location.Y - AvatarPanelButton.Height - 10
                );
            AvatarPanelButton.Anchor = AnchorStyles.None;

            MapPanelButton.Location = new Point(
               AvatarPanelButton.Location.X,
               AvatarPanelButton.Location.Y - MapPanelButton.Height - 10
               );
            MapPanelButton.Anchor = AnchorStyles.None;


            MarketPlaceAvatarPriceLabel.Text = "";

            MarketPlaceAvatarPriceLabel.Location = new Point(
              MarketPlaceAvatarPriceLabel.Parent.Width / 2 - MarketPlaceAvatarPriceLabel.Size.Width/2,
              MarketPlaceAvatarPriceLabel.Parent.Height - MarketPlaceAvatarPriceLabel.Size.Height);
            MarketPlaceReturnBtn.Anchor = AnchorStyles.None;


            // Initial Set-Up
            marketplaceMaps = Directory.GetFiles(Application.StartupPath + @"\zones\marketplace", "*.xml");
            marketplaceList = new List<string>();
            MarketPlaceView.Items.Clear();
            MarketPlaceView.Items.Clear();
            foreach (var item in MarketPlaceView.Items)
            {
                ((IDisposable)item).Dispose();
            }


            foreach (string s in marketplaceMaps)
            {
                
                string mapName = Path.GetFileNameWithoutExtension(s);
                var tempItemp = new ListViewItem(new[] { mapName, Outils.mapPrices[mapName].ToString() });
                MarketPlaceView.Items.Add(tempItemp);
            }




            MarketPlaceAvatarPanelPopulate();
        }


        // Retour dans le menu principal
        private void MarketPlaceReturnBtn_Click(object sender, EventArgs e)
        {
           // MarketplaceTab.Controls.Remove(PlayerInfoPanel);
            AvatarBox.Click += AvatarBox_Click;

            MainTab.Controls.Add(PlayerInfoPanel);
            tabControl1.SelectedTab = MainTab;
            MainTab.Focus();
        }

        private void MarketPlaceAvatarPanelPopulate()
        {
            string[] avatars = new string[] { };
            avatars = Directory.GetFiles(Application.StartupPath + @"\media\avatars", "AV01*.jpg");
            MarketPlaceAvatarPanel.ColumnCount = (int)Math.Ceiling((double)avatars.Length / (double)2);


            // Clear dynamically allocated Controls
            MarketPlaceAvatarPanel.Controls.Clear();
            foreach (Control item in avatarPanel.Controls.OfType<PictureBox>())
            {
                MarketPlaceAvatarPanel.Controls.Remove(item);
            }

            // Populate the avatar Panel with avatars that are unlocked
            foreach (string file in avatars)
            {
                Button pb = new Button();
                pb.Width = 100;
                pb.Height = 100;
                pb.Margin = new Padding(10);
                pb.BackgroundImageLayout = ImageLayout.Stretch;
                pb.BackgroundImage = Image.FromFile(file);
                // Add name to tag to extract after
                pb.Tag = Path.GetFileNameWithoutExtension(file);
                pb.FlatAppearance.BorderColor = Color.Black;
                pb.FlatStyle = FlatStyle.Flat;
                pb.FlatAppearance.BorderSize = 2;
                // Grey out disabled avatars, fucking black magic
                //if (!playerInfo.unlockedAvatars.Contains(pb.Tag.ToString()))
                //{
                //    pb.Enabled = false;
                //    pb.Image = ToolStripRenderer.CreateDisabledImage(pb.Image);
                //}
                pb.Click += MarketPlaceSelectAvatar;
                MarketPlaceAvatarPanel.Controls.Add(pb);
            }
        }





        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MarketPlaceSelectAvatar(object sender, EventArgs e)
        /// @brief Fonction qui permet de selectionner l'avatar
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MarketPlaceSelectAvatar(object avatar, EventArgs e)
        {
            foreach (var pb in MarketPlaceAvatarPanel.Controls.OfType<Button>())
            {

                ((Button)pb).FlatAppearance.BorderColor = Color.Black;
            }
            currentAvatar = ((Button)avatar).Tag.ToString();
            ((Button)avatar).FlatAppearance.BorderColor = Color.Green;

            if (playerInfo.unlockedAvatars.Contains(currentAvatar))
            {
                MarketPlaceAvatarPriceLabel.Text = "Vous avez deja cet avatar.";
                BuyAvatarButton.Enabled = false;
            }
            else if (Outils.avatarPrices.ContainsKey(currentAvatar))
            {
                currentAvatarPrice = Outils.avatarPrices[currentAvatar];
                MarketPlaceAvatarPriceLabel.Text = "Prix : " + currentAvatarPrice;
                if (currentAvatarPrice > playerInfo.playerCurrency)
                {
                    MarketPlaceAvatarPriceLabel.Text += "\nVous n'avez pas assez de fonds.";

                }
                BuyAvatarButton.Enabled = (currentAvatarPrice <= playerInfo.playerCurrency);
            }


            MarketPlaceAvatarPriceLabel.Location = new Point(
             MarketPlaceAvatarPriceLabel.Parent.Width / 2 - MarketPlaceAvatarPriceLabel.Size.Width / 2,
             MarketPlaceAvatarPriceLabel.Parent.Height - MarketPlaceAvatarPriceLabel.Size.Height);
            MarketPlaceReturnBtn.Anchor = AnchorStyles.None;
        }

        // Acheter un avatar
        // TODO : logicl to buy an avatar
        private void BuyAvatarButton_Click(object sender, EventArgs e)
        {
            BuyAndUpdateUserProfile();
        }

        // Acheter une map
        private void BuyMapButton_Click(object sender, EventArgs e)
        {
            playerInfo.playerCurrency -= currentMapPrice;
            // TODO: GET THE FUCKING MAPS
            if (playerInfo.unlockedMaps.Length >= 1)
            {
                playerInfo.unSplitMaps += ("," + currentMap);

            }
            else
            {
                playerInfo.unSplitMaps += (currentMap);
                
            }
            StringBuilder sb = new StringBuilder();
            sb.Append("SHEKELS:" + playerInfo.playerCurrency);
            sb.AppendLine();
            sb.Append("MAP_UNLOCKED:" + playerInfo.unSplitMaps);

            FonctionsNatives.updateInfoCompte(sb);
            if (NomLabel.Text != "HORS-LIGNE")
            {
                playerInfo.UpdatePlayerInfo(Outils.ProprieteStringToDictionnay(FonctionsNatives.obtenirInfoCompte()));
                CurrencyLabel.Text = playerInfo.playerCurrency.ToString();
            }
            if (playerInfo.unlockedMaps.Length >= 10)
            {
                SendAchievement("AC63");
            }
            if (playerInfo.unlockedMaps.Length >= 5)
            {
                SendAchievement("AC62");
            }
            if (playerInfo.unlockedMaps.Length >= 1)
            {
                SendAchievement("AC61");
            }
            
            BuyMapButton.Enabled = false;
            MapErrorLabel.Text = "Merci pour l'achat";
        }


        private void BuyAndUpdateUserProfile()
        {
            playerInfo.playerCurrency -= currentAvatarPrice;
            playerInfo.unSplitAvatars += ("," + currentAvatar);
            StringBuilder sb = new StringBuilder("SHEKELS:" + playerInfo.playerCurrency + "'\r\n" + "AVATAR_UNLOCKED:" + playerInfo.unSplitAvatars);
            FonctionsNatives.updateInfoCompte(sb);
            if (NomLabel.Text != "HORS-LIGNE")
            {
                playerInfo.UpdatePlayerInfo(Outils.ProprieteStringToDictionnay(FonctionsNatives.obtenirInfoCompte()));
                CurrencyLabel.Text = playerInfo.playerCurrency.ToString();
                Populate_avatarPanel();
            }
            if (playerInfo.unlockedAvatars.Contains("AV001") &&
                    playerInfo.unlockedAvatars.Contains("AV011") &&
                    playerInfo.unlockedAvatars.Contains("AV016") &&
                    playerInfo.unlockedAvatars.Contains("AV020"))
            {
                SendAchievement("AC52");
            }
            if (!playerInfo.unlockedAchievements.Contains("AC51"))
            {
                SendAchievement("AC51");
            }
            if (playerInfo.unlockedAvatars.Length > 19)
            {
                SendAchievement("AC53");
            }
            BuyAvatarButton.Enabled = false;
            MarketPlaceAvatarPriceLabel.Text = "Merci pour l'achat";
        }



        private void AvatarPanelButton_Click(object sender, EventArgs e)
        {
            MarketPlaceMapPanel.Visible = false;
            MarketPlaceAvatarPanel.Visible = true;
        }

        private void MapPanelButton_Click(object sender, EventArgs e)
        {
            MarketPlaceAvatarPanel.Visible = false;
            MarketPlaceMapPanel.Visible = true;
        }


        private void MarketPlaceView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (MarketPlaceView.SelectedIndices.Count <= 0) return;
            int index = MarketPlaceView.SelectedIndices[0];
            if (index >= 0)
            {
                var mapName = MarketPlaceView.Items[index].Text;
                MarketPlacePicture.SizeMode = PictureBoxSizeMode.StretchImage;
                if (File.Exists(Application.StartupPath + @"\zones\marketplace\" + mapName + ".jpg"))
                {
                    MarketPlacePicture.Image = Image.FromFile(Application.StartupPath + @"\zones\marketplace\" + mapName + ".jpg");
                    currentMap = mapName;
                    currentMapPrice = Convert.ToInt32( MarketPlaceView.Items[index].SubItems[1].Text );
                    if (currentMapPrice > playerInfo.playerCurrency)
                    {
                        MapErrorLabel.Text = "Vous n'avez pas assez de fonds. ";
                        BuyMapButton.Enabled = false;

                    }
                    else if (playerInfo.unlockedMaps.Contains(mapName))
                    {
                        MapErrorLabel.Text = "Vous avez deja cette zone ";
                        BuyMapButton.Enabled = false;
                    }
                    else
                    {
                        MapErrorLabel.Text = "";
                        BuyMapButton.Enabled = true;                        
                    }

                }
                else
                {
                    MarketPlacePicture.Image = Properties.Resources.SaintTrinity;
                }
            }
        }

     

    }
}
