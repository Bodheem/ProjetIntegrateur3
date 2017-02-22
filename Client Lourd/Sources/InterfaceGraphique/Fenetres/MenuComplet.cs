using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using InterfaceGraphique.Langages;
using System.Net.Mail;
using System.Speech.Synthesis;
using System.Text.RegularExpressions;
using System.Threading;
using InterfaceGraphique.Fenetres;
using System.Xml;

namespace InterfaceGraphique
{
    public partial class MenuComplet : Form
    {
        public Editeur modeEdit; ///< Form du mode edition
        public ModeJeu modeJeuMain;
        private const int MAXFAILTOTIMEOUT = 5;
        public int failCounter = 0;
        public int achievementCounter = 1;
        private bool succesLogIN = false;
        private bool loggedIN = false;
        bool duplicate = false;

        public PlayerInfo playerInfo = new PlayerInfo();

        Tutoriel tutorialGame = new Tutoriel();

        Dictionary<string,string> playerInfoValues = new Dictionary<string, string>();
        bool editPlayerInfo = false;
        bool togglePlayerInfo = false;

        private string ipAddress;
        private string avatarName;
        public ChatForm chat;
        Bitmap smallBorder;
        private bool m_connected = false;
        public bool connected
        {
            get { return m_connected; }
            set
            {
                m_connected = value;
                if (m_connected)
                {
                    ConnectBtn.Text = Langage.getCurrentLangage() == "fr" ? "Déconnecter" : "Log Out";
                    MarketplaceBtn.Enabled = true;
                    MultiPlayerBtn.Enabled = true;
                }
                else
                {
                    ConnectBtn.Text = Langage.getCurrentLangage() == "fr" ? "Connecter" : "Log In";
                    MarketplaceBtn.Enabled = false;
                    MultiPlayerBtn.Enabled = false;

                }
            }
        }

        StringBuilder bgm;
        bool bgmPlaying = false;

        public MenuComplet()
        {
            InitializeComponent();
            CreateAchievement();


            //var t = Task.Run(() =>
            //{
            //    FonctionsNatives.initialiserSon();
            //});
            //t.Wait();



            PlayerInfoPanel.BackgroundImage = OptionsMainPanel.BackgroundImage;
            PlayerOldPasswordTBox.Text = "";
            PlayerNewPasswordTBox.Text = "";
            AvatarBox.SizeMode = PictureBoxSizeMode.StretchImage;
            TestButton.Visible = false;
            LogibBtnLogin.Enabled = false;
            PasswordResetLink.Enabled = false;
            // Gestion des langues
            string lang = Langage.getCurrentLangage();
            if (lang == "fr")
            {
                btnFrench.FlatAppearance.BorderColor = Color.Gold;
                btnFrench.FlatAppearance.BorderSize = 2;
                btnEnglish.FlatAppearance.BorderSize = 0;
            }
            else if (lang == "en")
            {
                btnEnglish.FlatAppearance.BorderColor = Color.Gold;
                btnEnglish.FlatAppearance.BorderSize = 2;
                btnFrench.FlatAppearance.BorderSize = 0;
            }

           // Console.WriteLine("ORIGINAL SIZE: " + this.Size);
            this.ClientSize = Screen.PrimaryScreen.Bounds.Size;
          //  Console.WriteLine("MODIFIED SIZE: " + this.Size);

            // Background sauve en memoire
            Bitmap myImage = new Bitmap(Properties.Resources.GenericBackground);

            smallBorder = new Bitmap(InfoPanel.BackgroundImage);

            // Chaque Page obtient son background et sa taille est place a la taille
            // du parent ( pour la compatibilite avec plusieurs resolutions )
            foreach (TabPage myPage in tabControl1.TabPages)
            {
                myPage.BackgroundImage = myImage;
                myPage.BackgroundImageLayout = ImageLayout.Stretch;
                myPage.Size = tabControl1.Size;
            }
            // Redimension de la taille du Tab control 
            // +20,+30 tiennent compte de la taille des bordures + header 
            tabControl1.Size = new Size(Width + 30, Height + 50);

            // Place le tabControl au centre de l'ecran
            tabControl1.Location = new Point(
                this.ClientSize.Width / 2 - tabControl1.Size.Width / 2 - 5,
                this.ClientSize.Height / 2 - tabControl1.Size.Height / 2);
            tabControl1.Anchor = AnchorStyles.None;

            DownloadPanel.Location = new Point(
                this.ClientSize.Width / 2 - DownloadPanel.Size.Width / 2 - 5,
                this.ClientSize.Height / 2 - DownloadPanel.Size.Height / 2);
            DownloadPanel.Anchor = AnchorStyles.None;

            tutorialGame.initTutorial();
           

            // Fonction de SetUp des differents tabs   
            SetUpLogIn();
            SetUpOptionsMenu();
            SetUpPartieRapide();
            SetUpCampaign();
            SetSound();
            
        }

        public void CreateAchievement()
        {

            AchievementMainPanel.BackColor = Color.Black;
            AchievementMainPanel.Controls.Clear();
            string pictureFile = "";
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load("Achievements.xml");
            XmlNodeList nodeList = xmlDoc.DocumentElement.SelectNodes("/Achievements/Achievement");
            foreach (XmlNode node in nodeList)
            {
                TableLayoutPanel achievementPanel = new TableLayoutPanel();
                achievementPanel.BackgroundImage = OptionsMainPanel.BackgroundImage;
                achievementPanel.BackgroundImageLayout = ImageLayout.Stretch;
                achievementPanel.RowCount = 2;
                achievementPanel.ColumnCount = 3;
                achievementPanel.Height = 75;
                achievementPanel.Width = 200;
                achievementPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
                achievementPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
                achievementPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
                achievementPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
                achievementPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 75F));

               

                Label title = new Label();
                title.Text = node.ChildNodes[0].Attributes["Valeur"].Value;
                title.TextAlign = ContentAlignment.TopRight;
                title.ForeColor = Color.Red;
                title.BackColor = Color.Transparent;
                achievementPanel.Controls.Add(title, 1, 0);

                Label achievPoints = new Label();
                achievPoints.Height = 50;
                achievPoints.Text = node.ChildNodes[1].Attributes["Valeur"].Value;
                achievPoints.Font = new Font(achievPoints.Font.FontFamily, 16);
                achievPoints.BackColor = Color.Transparent;
                achievPoints.TextAlign = ContentAlignment.MiddleCenter;
                achievPoints.ForeColor = Color.Green;
                achievementPanel.Controls.Add(achievPoints, 2, 0);
                achievementPanel.SetRowSpan(achievPoints, 2);



                Label description = new Label();
                description.Text = node.ChildNodes[2].Attributes["Valeur"].Value;
                description.AutoSize = true;
                description.ForeColor = Color.Red;
                description.BackColor = Color.Transparent;
                description.TextAlign = ContentAlignment.BottomCenter;
                achievementPanel.Controls.Add(description, 0, 1);

                PictureBox pb = new PictureBox();
                pb.Width = 75;
                pb.Height = 75;
                pictureFile = node.ChildNodes[3].Attributes["Valeur"].Value;
                //pb.Image = Image.FromFile(Application.StartupPath + @"\media\Achievements\" + pictureFile);
                pb.Image = Properties.Resources.Trophy;                
                pb.SizeMode = PictureBoxSizeMode.StretchImage;
                achievementPanel.Controls.Add(pb, 0, 0);
                achievementPanel.SetRowSpan(pb, 2);

                achievementPanel.Tag = node.Attributes["Valeur"].Value;

               // Outils.AchievementDictionary[achievementPanel.Tag.ToString()].points = Convert.ToInt32(achievPoints.Text);
               // Outils.AchievementDictionary[achievementPanel.Tag.ToString()].title = title.Text;
                // how the fuck this works, is beyond me
                Outils.AchievementDictionary[achievementPanel.Tag.ToString()] = new Achievement(title.Text, Convert.ToInt32(achievPoints.Text));


                AchievementMainPanel.Controls.Add(achievementPanel);
            }

            AchievementMainPanel.Location = new Point(
                  AchievementMainPanel.Parent.Width / 2 - AchievementMainPanel.Size.Width / 2,
              AchievementMainPanel.Parent.Height / 2 - AchievementMainPanel.Size.Height / 2);
            AchievementMainPanel.Anchor = AnchorStyles.None;

            //foreach (KeyValuePair<string, int> kvp in Outils.AchievementDictionary)
            //{
            //    //textBox3.Text += ("Key = {0}, Value = {1}", kvp.Key, kvp.Value);
            //    Console.WriteLine("Key = {0}, Value = {1}", kvp.Key, kvp.Value);
            //}
           
        }


        // Fonction qui passe a travers tous les achievements et grise ceux qui sont pas unlocked
        // rendre l'image grise, c'est vraiment couteux, donc je le skip pour le moment
        public void PopulateAchievement()
        {

            foreach (var control in AchievementMainPanel.Controls.OfType<TableLayoutPanel>())
            {
                if (!playerInfo.unlockedAchievements.Contains(control.Tag))
                {
                    control.Enabled = false;
                    foreach (var pb in control.Controls.OfType<PictureBox>())
                    {
                        //pb.Image = ToolStripRenderer.CreateDisabledImage(pb.Image);

                    }
                }
                else
                {
                    control.Enabled = true;
                }
            }
            

        }
     
        public void SetSound()
        {
            bgm = new StringBuilder("Quiet-Tension");
            bgmPlaying = true;
            FonctionsNatives.bouclerSon(bgm, bgm.Length, true);
            FonctionsNatives.jouerSon(bgm, bgm.Length);
            FonctionsNatives.ajusterVolume(bgm, bgm.Length, 0.7f);

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn protected override CreateParams CreateParams
        /// @brief Fonction qui permet d'activer le double buffering.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams cp = base.CreateParams;
                cp.ExStyle |= 0x02000000;
                //cp.Style &= ~0x02000000;  // Turn off WS_CLIPCHILDREN <- Unstable as FUCK

                return cp;
            }
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

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MenuComplet_KeyDown(object sender, EventArgs e)
        /// @brief Fonction qui permet de changer de paneau
        ///        TESTING ONLY!!!!!!!!!!!!!!!!!!
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MenuComplet_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Alt && e.KeyValue > '0' && e.KeyValue <= '9')
            {
                tabControl1.SelectTab((int)e.KeyValue - '1');
                e.Handled = true;
            }
           
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void CAccountBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet d'aller au paneau de creation de compte.
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void CAccountBtn_Click(object sender, EventArgs e)
        {
            LogInPanel.Visible = false;
            CreateAccountPanel.Visible = true;


        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void LogInPress(object sender, EventArgs e)
        /// @brief Fonction qui permet de se connecter avec la touche ENTER
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void LogInPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.Return)
            {
                LogibBtnLogin_Click(sender, e);
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void LancerModeJeu(List<string> zones, int playerType)
        /// @brief Fonction qui permet de lancer le mode jeu
        /// @param[in] zones : Liste avec les noms des zones
        /// @param[in] playerType : type de joueur ( 1 = solo, 2= 2 players , 3 = AI )
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void LancerModeJeu(List<string> zones, int playerType, int time = -1, bool instaDeath = false,bool multiplayer = false)
        {
            Program.loadingBar = new LoadingBar();
            Program.loadingBar.Show(this);
            Hide();
            modeJeuMain = new ModeJeu(zones, playerType,time,instaDeath,multiplayer);
            //modeJeuMain.ShowDialog(this);
            modeJeuMain.Show(this);
            //UpdateGamesPlayed();
            
            //this.Show();
        }

       



        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn delegate void SetTextCallback(string text);
        /// @brief Fonction de delegate pour communication inter threads
        /// @param[in] text : le texte a afficher sur le paneau
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        delegate void SetTextCallback(string text);


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void SetText(string text)
        /// @brief Fonction de delegate pour communication inter threads
        /// @param[in] text : le texte a afficher sur le paneau
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void SetText(string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (LoginTab.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                ErrorPanel.Visible = true;
                ErrorLabel.Text = text;
                LogInPanel.Visible = false;
                CAccountBtn.Enabled = true;
                CreateAccountPanel.Enabled = false;
                if (loggedIN)
                {
                    ServerConnectBtn.Enabled = false;
                    IPAddressBox.Enabled = false;
                    LogibBtnLogin.Enabled = true;
                    PasswordResetLink.Enabled = true;
                }
            }
        }



        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void SetText(string text)
        /// @brief Fonction de delegate pour communication inter threads
        /// @param[in] text : le texte a afficher sur le paneau
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void SetDownloadText(string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (LoginTab.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetDownloadText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                if(text != "done")
                {
                    DownloadPanel.Visible = true;
                    DownloadLabel.Text = text;
                    EditeurBtn.Enabled = false;
                    CreateBtn.Enabled = false;
                    JoinBtn.Enabled = false;
                    MPQuickGameBtn.Enabled = false;
                }
                else
                {
                    DownloadPanel.Visible = false;
                    EditeurBtn.Enabled = true;
                    CreateBtn.Enabled = true;
                    JoinBtn.Enabled = true;
                    MPQuickGameBtn.Enabled = true;
                }
              
               
            }
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ServerConnectBtn_Click(object sender, EventArgs e)
        /// @brief Bouton qui permet de se connecter au serveur avec le IP fourni
        ///        Lance un nouveau thread pour la connexion.
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ServerConnectBtn_Click(object sender, EventArgs e)
        {
            Task mytask = Task.Run(() =>
            {
                StringBuilder ipAddress = new StringBuilder(IPAddressBox.Text);
                SetText("Connecting....");
                loggedIN = FonctionsNatives.SendIP(ipAddress);
                if (loggedIN)
                {
                    SetText("LOG IN SUCCESSFUL");
                    File.WriteAllText(@"lastuser.yonni", UsernameBox.Text + " " + IPAddressBox.Text);
                }
                else
                {
                    SetText("LOG IN FAILED");
                }
            });
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void MenuComplet_FormClosing(object sender, EventArgs e)
        /// @brief Fonction qui est lance a la fin de la forme.
        ///        Si une personne est logged, elle se fait LogOff
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void MenuComplet_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                if (connected)
                {
                    FonctionsNatives.LogOff();
                    FonctionsNatives.DisconnectFromServer();
                }

                FonctionsNatives.libererModele();
            }
            catch (Exception)
            {

            }
            //Environment.Exit(0);

        }


        public void totalDisconnect()
        {
            if (failCounter >= MAXFAILTOTIMEOUT)
            {
                failCounter = 0;
                loggedIN = false;
                if (chat != null)
                {
                    chat.connected = false;
                    //chat.messageThread.Join();
                    chat.messageThread.Abort();
                    chat.Close();
                    chat = null;
                }
               
                MultiPlayerBtn.Enabled = false;
                MultiPlayerPanel.Visible = false;
                MainPanel.Visible = true;
                connected = false;
                // THIS TAKES FUCKING FOREVER
                FonctionsNatives.DisconnectFromServer();
                ServerConnectBtn.Enabled = true;
                tabControl1.SelectedTab = LoginTab;
                LoginTab.Focus();
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void CreateAccountPanel_VisibleChanged(object sender, EventArgs e)
        /// @brief Fonction qui permet de changer l'etat du paneau de creation.
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void CreateAccountPanel_VisibleChanged(object sender, EventArgs e)
        {
            if (CreateAccountPanel.Visible)
            {
                CAccountBtn.Visible = false;
            }
            else
            {
                CAccountBtn.Visible = true;
            }
        }

        private void PasswordResetLink_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            StringBuilder name = new StringBuilder(UsernameBox.Text);
            FonctionsNatives.requestPasswordRecovery(name);
        }


        #region PlayerProfile
        private void AvatarBox_Click(object sender, EventArgs e)
        {
           if (connected)
           {
                if (togglePlayerInfo == false)
                {
                    togglePlayerInfo = true;
                    PlayerInfoPanel.Height = 360;
                    ConnectBtn.Location = new Point(ConnectBtn.Location.X, 365);
                    AchievBtn.Location = new Point(AchievBtn.Location.X, 300);
                }
                else
                {
                    togglePlayerInfo = false;
                    PlayerEditAnnulerBtn_Click(sender, e);
                    PlayerInfoPanel.Height = 110;
                    ConnectBtn.Location = new Point(ConnectBtn.Location.X, 115);
                }
            }
        }

        private void EnablePlayerEdit(bool enable)
        {
                PlayerAgeTBox.ReadOnly = !enable;
                PlayerNameTBox.ReadOnly = !enable;
                PlayerSurnameTBox.ReadOnly = !enable;
                PlayerEmailTBox.ReadOnly = !enable;
            if (enable)
            {
                PlayerAgeTBox.BorderStyle = BorderStyle.Fixed3D;
                PlayerNameTBox.BorderStyle = BorderStyle.Fixed3D;
                PlayerSurnameTBox.BorderStyle = BorderStyle.Fixed3D;
                PlayerEmailTBox.BorderStyle = BorderStyle.Fixed3D;
                PlayerOldPasswordTBox.BorderStyle = BorderStyle.Fixed3D;
                PlayerNewPasswordTBox.BorderStyle = BorderStyle.Fixed3D;
            }
            else
            {
                PlayerAgeTBox.BorderStyle = BorderStyle.None;
                PlayerNameTBox.BorderStyle = BorderStyle.None;
                PlayerSurnameTBox.BorderStyle = BorderStyle.None;
                PlayerEmailTBox.BorderStyle = BorderStyle.None;
                PlayerOldPasswordTBox.BorderStyle = BorderStyle.None;
                PlayerNewPasswordTBox.BorderStyle = BorderStyle.None;
            }
        }

        private void PlayerEditBtn_Click(object sender, EventArgs e)
        {
            if (!editPlayerInfo)
            {
                editPlayerInfo = true;
                EnablePlayerEdit(true);
                PlayerEditAcceptBtn.Location = new Point(20,350);
                PlayerEditAcceptBtn.Visible = true;
                PlayerEditAnnulerBtn.Location = new Point(160,350);
                PlayerEditAnnulerBtn.Visible = true;
                PlayerInfoPanel.Height = 400;
                ConnectBtn.Location = new Point(ConnectBtn.Location.X, PlayerInfoPanel.Height + 5);


                PlayerOldPasswordLabel.Visible = true;
                PlayerOldPasswordTBox.Visible = true;
                PlayerNewPasswordLabel.Visible = true;
                PlayerNewPasswordTBox.Visible = true;
                PlayerInfoPrivateLabel.Visible = true;
                PlayerInfoPrivateProfile.Visible = true;
                AchievBtn.Visible = false;
                avatarBtn.Visible = true;
                Console.Write(PlayerOldPasswordTBox.Text);
                Console.Write(PlayerNewPasswordTBox.Text);



                PlayerEditBtn.Visible = false;
            }
           
        }

        private void PlayerEditAnnulerBtn_Click(object sender, EventArgs e)
        {
            PlayerNameTBox.Text = playerInfo.playerName;
            PlayerSurnameTBox.Text = playerInfo.playerSurname;
            PlayerAgeTBox.Text = playerInfo.playerAge.ToString();
            PlayerEmailTBox.Text = playerInfo.playerEmail;
            CancelEdit();
           
        }

        private void PlayerEditAcceptBtn_Click(object sender, EventArgs e)
        {
            PlayerInfoErrorLabel.Text = "";
            if (VerifyInformation())
            {
                SendUpdatedPlayerInfo();
                CancelEdit();
            }
        }

        private void CancelEdit()
        {
            AchievBtn.Visible = true;
            avatarBtn.Visible = false;
            avatarPanel.Visible = false;
            EnablePlayerEdit(false);
            PlayerEditBtn.Visible = true;
            editPlayerInfo = false;
            PlayerOldPasswordLabel.Visible = false;
            PlayerOldPasswordTBox.Visible = false;
            PlayerNewPasswordLabel.Visible = false;
            PlayerNewPasswordTBox.Visible = false;
            PlayerEditAcceptBtn.Visible = false;
            PlayerEditAnnulerBtn.Visible = false;
            PlayerInfoPrivateLabel.Visible = false;
            PlayerInfoPrivateProfile.Visible = false;
            PlayerInfoPanel.Height = 360;
            ConnectBtn.Location = new Point(ConnectBtn.Location.X, PlayerInfoPanel.Height + 5);
            PlayerInfoErrorLabel.Text = "";
            PlayerOldPasswordTBox.Text = "";
            PlayerNewPasswordTBox.Text = "";

            if (File.Exists(Application.StartupPath + @"\media\avatars\" + playerInfo.playerAvatar + ".jpg"))
            {
                AvatarBox.Image =
              Image.FromFile(Application.StartupPath + @"\media\avatars\" + playerInfo.playerAvatar + ".jpg");

            }

        }

        private bool VerifyInformation()
        {
            bool okPassword = true;

            if (PlayerEmailTBox.Text.Contains("@") && PlayerEmailTBox.Text.Split('.').Last() != string.Empty)
            {
                okPassword = true;
            }
            else
            {
                PlayerInfoErrorLabel.Text += "!!Courriel Invalide.!!\n";
                okPassword = false;
            }
            if (PlayerOldPasswordTBox.Text.Length > 0 || PlayerNewPasswordTBox.Text.Length > 0)
            {
                if (PlayerOldPasswordTBox.Text != playerInfo.playerPassword)
                {
                   // Console.WriteLine("OLD PASS : " + playerInfo.playerPassword);
                    PlayerInfoErrorLabel.Text += "!!Ancien mot de passe invalide.!!\n";
                    okPassword = false;
                }
                if (PlayerOldPasswordTBox.Text == PlayerNewPasswordTBox.Text)
                {
                    PlayerInfoErrorLabel.Text += "!!Mot de passe ne peux pas etre \nle meme que l'ancien!!\n";
                    okPassword = false;
                }
                else if (!Regex.IsMatch(PlayerNewPasswordTBox.Text, "^[a-zA-Z0-9]*$") ||
                         PlayerNewPasswordTBox.Text.Length < 5 || PlayerNewPasswordTBox.Text.Length > 20)
                {
                    PlayerInfoErrorLabel.Text +=
                        "!!Mot de passe doit contenir entre \n5 et 20 caractères \nalphanumériques.!!\n";
                    okPassword = false;

                }
            }
            return okPassword;
        }
      
        private void SetUpPlayerInfo()
        {
            playerInfo.UpdatePlayerInfo(Outils.ProprieteStringToDictionnay(FonctionsNatives.obtenirInfoCompte()));
            PlayerInfoPanel.Height = 110;
            ConnectBtn.Location = new Point(ConnectBtn.Location.X, PlayerInfoPanel.Height + 5);
            NomLabel.Text = playerInfo.userName;
            APointsLabel.Text = playerInfo.playerAchievementPoints.ToString();
            CurrencyLabel.Text = playerInfo.playerCurrency.ToString();
            PlayerNameTBox.Text = playerInfo.playerName;
            PlayerSurnameTBox.Text = playerInfo.playerSurname;
            PlayerAgeTBox.Text = playerInfo.playerAge.ToString();
            PlayerEmailTBox.Text = playerInfo.playerEmail;
            PlayerInfoPrivateProfile.Checked = playerInfo.playerPublicProfile;

            Populate_avatarPanel();
            PopulateAchievement();
            ShekelAchievementTest();
            if (File.Exists(Application.StartupPath + @"\media\avatars\" + playerInfo.playerAvatar + ".jpg"))
            {
                AvatarBox.Image =
              Image.FromFile(Application.StartupPath + @"\media\avatars\" + playerInfo.playerAvatar + ".jpg");
          
            }
            else
            {
                AvatarBox.Image = Properties.Resources.Trophy;
            }
            switchProfileCheck();
            PlayerInfoVictoriesLabel.Text = "Victoires: " + playerInfo.playerVictories;
            PlayerInfoGamePlayedLabel.Text = "Parties jouées: " + playerInfo.playerPlayedGames;
            PlayerCoopVictoriesLabel.Text = "Victoires coop: " + playerInfo.playerCoopVictories;
            PlayerCompVictoriesLabel.Text = "Victoires comp: " + playerInfo.playerCompVictories;


        }

        public void ShekelAchievementTest()
        {
            if (playerInfo.playerCurrency > 10000 && !playerInfo.unlockedAchievements.Contains("AC33"))
            {
                SendAchievement("AC33");
            }
            else if (playerInfo.playerCurrency > 1000 && !playerInfo.unlockedAchievements.Contains("AC32"))
            {
                SendAchievement("AC32");
            }
            else if (playerInfo.playerCurrency > 1 && !playerInfo.unlockedAchievements.Contains("AC31"))
            {
                SendAchievement("AC31");
            }
        }
        private void SendUpdatedPlayerInfo()
        {
            playerInfoValues["NAME"] = PlayerNameTBox.Text;
            playerInfoValues["SURNAME"] = PlayerSurnameTBox.Text;
            playerInfoValues["AGE"] = PlayerAgeTBox.Text;
            playerInfoValues["COURRIEL"] = PlayerEmailTBox.Text;
            if( PlayerNewPasswordTBox.Text.Length > 0 )
                playerInfoValues["PASSWORD"] = PlayerNewPasswordTBox.Text;
            if (PlayerInfoPrivateProfile.Checked)
            {
                playerInfoValues["IS_PUBLIC"] = "1";                
            }
            else
            {
                playerInfoValues["IS_PUBLIC"] = "0";
            }
            playerInfoValues["AVATAR"] = avatarName;
            StringBuilder sb = new StringBuilder(Outils.ProprieteDictionnaryToString(playerInfoValues));
            FonctionsNatives.updateInfoCompte(sb);
            if(NomLabel.Text !="HORS-LIGNE")
                playerInfo.UpdatePlayerInfo(playerInfoValues);
        }

        private void PlayerInfoPrivateProfile_CheckedChanged(object sender, EventArgs e)
        {
            switchProfileCheck();
        }


        // Function to handle the check on the event. Can be used outside of the event for 
        // initial setup
        private void switchProfileCheck()
        {
            if (PlayerInfoPrivateProfile.Checked)
            {
                PlayerInfoPrivateProfile.BackgroundImage = Properties.Resources.buttonStock1h;
                PlayerInfoPrivateProfile.Text = "✓";
            }
            else
            {
                PlayerInfoPrivateProfile.Text = "";
                PlayerInfoPrivateProfile.BackgroundImage = smallBorder;

            }
            
        }


        #endregion

        private void MenuComplet_VisibleChanged(object sender, EventArgs e)
        {
            if (Visible == false)
            {
                if(chat != null)
                chat.Hide();
                FonctionsNatives.arreterToutSons();
            }
            else
            {
                if(chat != null && chat.Visible == false)
                    chat.Show(this);
               SetSound();
            }
        }

        private void MenuComplet_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == '`' || e.KeyChar == '`')
            {
                if (bgmPlaying)
                {
                    FonctionsNatives.mute(bgm, bgm.Length, bgmPlaying);
                    bgmPlaying = false;
                }
                else
                {
                    FonctionsNatives.mute(bgm, bgm.Length, bgmPlaying);
                    bgmPlaying = true;
                }
            }
        }

        private void avatarBtn_Click(object sender, EventArgs e)
        {
            avatarPanel.Visible = (!avatarPanel.Visible);
        }


        // Permet d'afficher et cacher le bloc des achievements
        private void AchievBtn_Click(object sender, EventArgs e)
        {
            AchievementMainPanel.Visible = !AchievementMainPanel.Visible;
        }

        private void MPQuickGameBtn_Click(object sender, EventArgs e)
        {
            int matchmakingResult = FonctionsNatives.matchmaking();
            if (matchmakingResult == 1)
            {
                tabControl1.SelectedTab = MPGameSelectTab;
                MultiPlayerPanel.Visible = false;
                MainPanel.Visible = true;
                LobbyTab.Focus();
                // Reload la liste des maps
                SetUpMultiplayerJoin();
                quickJoin();
            }
            if (matchmakingResult == 2)
            {
                CreateBtn.PerformClick();
            }
        }

        private void MenuComplet_Load(object sender, EventArgs e)
        {

        }

        private void TestButton_Click(object sender, EventArgs e)
        {
            //FonctionsNatives.fonctionTest();
            //StringBuilder testString = new StringBuilder("GAMES_PLAYED:10\r\nGAMES_WON:5\r\nGAMES_COMP_WON:3\r\nGAMES_COOP_WON:2");
            //FonctionsNatives.updateInfoCompte(testString);
            //playerInfo.UpdatePlayerInfo(Outils.ProprieteStringToDictionnay(FonctionsNatives.obtenirInfoCompte()));
            //PlayerInfoVictoriesLabel.Text = "Victoires: " + playerInfo.playerVictories;
            //PlayerInfoGamePlayedLabel.Text = "Parties jouées: " + playerInfo.playerPlayedGames;
            //PlayerCoopVictoriesLabel.Text = "Victoires coop: " + playerInfo.playerCoopVictories;
            //PlayerCompVictoriesLabel.Text = "Victoires comp: " + playerInfo.playerCompVictories;

        }

        public void UpdateGamesPlayed()
        {
            playerInfo.UpdatePlayerInfo(Outils.ProprieteStringToDictionnay(FonctionsNatives.obtenirInfoCompte()));
            PlayerInfoVictoriesLabel.Text = "Victoires: " + playerInfo.playerVictories;
            PlayerInfoGamePlayedLabel.Text = "Parties jouées: " + playerInfo.playerPlayedGames;
        }

        public void UpdateStatistics()
        {
            playerInfo.UpdatePlayerInfo(Outils.ProprieteStringToDictionnay(FonctionsNatives.obtenirInfoCompte()));
            PlayerInfoVictoriesLabel.Text = "Victoires: " + playerInfo.playerVictories;
            PlayerInfoGamePlayedLabel.Text = "Parties jouées: " + playerInfo.playerPlayedGames;
            PlayerCoopVictoriesLabel.Text = "Victoires coop: " + playerInfo.playerCoopVictories;
            PlayerCompVictoriesLabel.Text = "Victoires comp: " + playerInfo.playerCompVictories;

            if (playerInfo.playerCoopVictories >= 20 && !playerInfo.unlockedAchievements.Contains("AC23"))
            {
                SendAchievement("AC23");
            }
            else if (playerInfo.playerCoopVictories >= 5 && !playerInfo.unlockedAchievements.Contains("AC22"))
            {
                SendAchievement("AC22");
            }
            else if (playerInfo.playerCoopVictories >= 1 && !playerInfo.unlockedAchievements.Contains("AC21"))
            {
                SendAchievement("AC21");
            }

            if (playerInfo.playerVictories >= 20 && !playerInfo.unlockedAchievements.Contains("AC43"))
            {
                SendAchievement("AC43");
            }
            else if (playerInfo.playerVictories >= 5 && !playerInfo.unlockedAchievements.Contains("AC42"))
            {
                SendAchievement("AC42");
            }
            else if (playerInfo.playerVictories >= 1 && !playerInfo.unlockedAchievements.Contains("AC41"))
            {
                SendAchievement("AC41");
            }


        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void SendAchievement(string achievementToUnlock)
        /// @brief Fonction qui permet d'ajouter un achievement
        /// @param[in] achievementToUnlock : nom du achiev
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public void SendAchievement(string achievementToUnlock)
        {
            if (Outils.AchievementDictionary.ContainsKey(achievementToUnlock) && !playerInfo.unlockedAchievements.Contains(achievementToUnlock))
            {
                
                FonctionsNatives.addAchievementPoints(Outils.AchievementDictionary[achievementToUnlock].points);
                if (playerInfo.unSplitAchievements.Length > 1)
                {
                    playerInfo.unSplitAchievements += ("," + achievementToUnlock);
                }
                else
                {
                    playerInfo.unSplitAchievements += (achievementToUnlock);                    
                    
                }
                StringBuilder sb = new StringBuilder("ACHIEVEMENT_UNLOCKED:" + playerInfo.unSplitAchievements);
                AchievementForm testAch = new AchievementForm(Outils.AchievementDictionary[achievementToUnlock].title, Outils.AchievementDictionary[achievementToUnlock].points,achievementCounter);
                testAch.Show(this);
                achievementCounter++;
                FonctionsNatives.updateInfoCompte(sb);
               
            }
            else
            {
                Console.WriteLine("wtf is this achievement?");
            }
            if (NomLabel.Text != "HORS-LIGNE")
            {
                playerInfo.UpdatePlayerInfo(Outils.ProprieteStringToDictionnay(FonctionsNatives.obtenirInfoCompte()));
                APointsLabel.Text = playerInfo.playerAchievementPoints.ToString();
                PopulateAchievement();

            }
        }

        private void TutorialBtn_Click(object sender, EventArgs e)
        {
            //TODO : NICOLAS

            tabControl1.SelectedTab = LobbyTab;
            MultiPlayerPanel.Visible = false;
            MainPanel.Visible = true;
            LobbyTab.Focus();

            // Reload la liste des maps
            SetUpMultiplayerCreate(true);
        }










        /* public void TutorialManager()
         {
             switch (tutorialGame.CurrentMessageGame)
             {
                 case 2:
                     //Suivant_tuto_bouton.Enabled = false;
                     break;
                 case 3:
                     //Suivant_tuto_bouton.Enabled = false;
                     break;
                 case 4:
                     //Suivant_tuto_bouton.Enabled = false;
                     break;
                 case 5:
                     //Suivant_tuto_bouton.Enabled = false;
                     break;
                 case 6:
                     //Suivant_tuto_bouton.Enabled = false;
                     break;
                 case 7:
                     //Suivant_tuto_bouton.Enabled = false;
                     break;
                 case 8:
                     break;
             }
         }*/

    }


}
