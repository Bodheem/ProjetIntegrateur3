using System.Reflection;
using System.Resources;

namespace InterfaceGraphique
{
    partial class MenuComplet
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MenuComplet));
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.LoginTab = new System.Windows.Forms.TabPage();
            this.ErrorPanel = new System.Windows.Forms.Panel();
            this.ErrorBtn = new System.Windows.Forms.Button();
            this.ErrorLabel = new System.Windows.Forms.Label();
            this.CreateAccountPanel = new System.Windows.Forms.Panel();
            this.CAInfoPanel = new System.Windows.Forms.Panel();
            this.CAEmailLabel = new System.Windows.Forms.Label();
            this.CAAgeLabel = new System.Windows.Forms.Label();
            this.CAEmailBox = new System.Windows.Forms.TextBox();
            this.CAAgeBox = new System.Windows.Forms.TextBox();
            this.PseudoPanel = new System.Windows.Forms.Panel();
            this.CAPseudoLabel = new System.Windows.Forms.Label();
            this.CAPasswordLabel = new System.Windows.Forms.Label();
            this.CAPseudoBox = new System.Windows.Forms.TextBox();
            this.CAPasswordBox = new System.Windows.Forms.TextBox();
            this.CancelBtn = new System.Windows.Forms.Button();
            this.CreateAccBtn = new System.Windows.Forms.Button();
            this.CAccountBtn = new System.Windows.Forms.Button();
            this.QGameBtn = new System.Windows.Forms.Button();
            this.LogInPanel = new System.Windows.Forms.Panel();
            this.ServerConnectBtn = new System.Windows.Forms.Button();
            this.IPAddressBox = new System.Windows.Forms.TextBox();
            this.InfoPanel = new System.Windows.Forms.Panel();
            this.UsernameLabelLogin = new System.Windows.Forms.Label();
            this.PasswordLabel = new System.Windows.Forms.Label();
            this.UsernameBox = new System.Windows.Forms.TextBox();
            this.PasswordBox = new System.Windows.Forms.TextBox();
            this.PasswordResetLink = new System.Windows.Forms.LinkLabel();
            this.PlayOfflineBtn = new System.Windows.Forms.Button();
            this.LogibBtnLogin = new System.Windows.Forms.Button();
            this.MainTab = new System.Windows.Forms.TabPage();
            this.DownloadPanel = new System.Windows.Forms.Panel();
            this.DownloadLabel = new System.Windows.Forms.Label();
            this.TestButton = new System.Windows.Forms.Button();
            this.AchievementMainPanel = new System.Windows.Forms.TableLayoutPanel();
            this.avatarPanel = new System.Windows.Forms.TableLayoutPanel();
            this.PlayerInfoPanel = new System.Windows.Forms.Panel();
            this.PlayerCompVictoriesLabel = new System.Windows.Forms.Label();
            this.avatarBtn = new System.Windows.Forms.Button();
            this.PlayerInfoErrorLabel = new System.Windows.Forms.Label();
            this.PlayerInfoPrivateLabel = new System.Windows.Forms.Label();
            this.PlayerInfoPrivateProfile = new System.Windows.Forms.CheckBox();
            this.PlayerCoopVictoriesLabel = new System.Windows.Forms.Label();
            this.PlayerInfoVictoriesLabel = new System.Windows.Forms.Label();
            this.PlayerInfoGamePlayedLabel = new System.Windows.Forms.Label();
            this.PlayerNewPasswordLabel = new System.Windows.Forms.Label();
            this.PlayerNewPasswordTBox = new System.Windows.Forms.TextBox();
            this.PlayerOldPasswordLabel = new System.Windows.Forms.Label();
            this.PlayerOldPasswordTBox = new System.Windows.Forms.TextBox();
            this.PlayerEditAnnulerBtn = new System.Windows.Forms.Button();
            this.PlayerEditAcceptBtn = new System.Windows.Forms.Button();
            this.PlayerEditBtn = new System.Windows.Forms.Button();
            this.AchievBtn = new System.Windows.Forms.Button();
            this.PlayerAgeLabel = new System.Windows.Forms.Label();
            this.PlayerAgeTBox = new System.Windows.Forms.TextBox();
            this.PlayerEmailLabel = new System.Windows.Forms.Label();
            this.PlayerEmailTBox = new System.Windows.Forms.TextBox();
            this.PlayerSurnameLabel = new System.Windows.Forms.Label();
            this.PlayerSurnameTBox = new System.Windows.Forms.TextBox();
            this.PlayerNameLabel = new System.Windows.Forms.Label();
            this.PlayerNameTBox = new System.Windows.Forms.TextBox();
            this.APointsLabel = new System.Windows.Forms.Label();
            this.CurrencyLabel = new System.Windows.Forms.Label();
            this.AvatarBox = new System.Windows.Forms.PictureBox();
            this.NomLabel = new System.Windows.Forms.Label();
            this.MultiPlayerPanel = new System.Windows.Forms.Panel();
            this.MPQuickGameBtn = new System.Windows.Forms.Button();
            this.RetourMPBtn = new System.Windows.Forms.Button();
            this.JoinBtn = new System.Windows.Forms.Button();
            this.CreateBtn = new System.Windows.Forms.Button();
            this.SinglePlayerPanel = new System.Windows.Forms.Panel();
            this.RetourSPBtn = new System.Windows.Forms.Button();
            this.CampagneBtn = new System.Windows.Forms.Button();
            this.PRapideBtn = new System.Windows.Forms.Button();
            this.ConnectBtn = new System.Windows.Forms.Button();
            this.MainPanel = new System.Windows.Forms.Panel();
            this.TutorialBtn = new System.Windows.Forms.Button();
            this.QuitBtn = new System.Windows.Forms.Button();
            this.MarketplaceBtn = new System.Windows.Forms.Button();
            this.OptionsBtn = new System.Windows.Forms.Button();
            this.EditeurBtn = new System.Windows.Forms.Button();
            this.MultiPlayerBtn = new System.Windows.Forms.Button();
            this.SoloBtn = new System.Windows.Forms.Button();
            this.CampaignTab = new System.Windows.Forms.TabPage();
            this.CampaignPanel = new System.Windows.Forms.Panel();
            this.CtimeLimitLabel = new System.Windows.Forms.Label();
            this.CplusBtn = new System.Windows.Forms.Button();
            this.CminusBtn = new System.Windows.Forms.Button();
            this.CtimeLabel = new System.Windows.Forms.Label();
            this.CtimeAttackLabel = new System.Windows.Forms.Label();
            this.CtimeAttackCBox = new System.Windows.Forms.CheckBox();
            this.CinstaDeathLabel = new System.Windows.Forms.Label();
            this.CinstaDeathCBox = new System.Windows.Forms.CheckBox();
            this.CampaignEmptyBtn = new System.Windows.Forms.Button();
            this.CampaignRemoveItemBtn = new System.Windows.Forms.Button();
            this.CampaignAddBtn = new System.Windows.Forms.Button();
            this.CampaignSelectedListView = new System.Windows.Forms.ListView();
            this.columnHeader5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader6 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.CampaignChoiceLabel = new System.Windows.Forms.Label();
            this.CampaignPlayerTypePanel = new System.Windows.Forms.Panel();
            this.checkBoxCAI = new System.Windows.Forms.CheckBox();
            this.checkBoxC2 = new System.Windows.Forms.CheckBox();
            this.checkBoxCSolo = new System.Windows.Forms.CheckBox();
            this.CampaignPlayerTypeLabel = new System.Windows.Forms.Label();
            this.campaignCancelBtn = new System.Windows.Forms.Button();
            this.CampaignZonesListView = new System.Windows.Forms.ListView();
            this.columnHeader3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.CampaignScreenShotBox = new System.Windows.Forms.PictureBox();
            this.campaignStartBtn = new System.Windows.Forms.Button();
            this.CampaignZonesLabel = new System.Windows.Forms.Label();
            this.QuickGameTab = new System.Windows.Forms.TabPage();
            this.QGamePanel = new System.Windows.Forms.Panel();
            this.timeLimitLabel = new System.Windows.Forms.Label();
            this.plusBtn = new System.Windows.Forms.Button();
            this.minusBtn = new System.Windows.Forms.Button();
            this.timeLabel = new System.Windows.Forms.Label();
            this.timeAttackLabel = new System.Windows.Forms.Label();
            this.timeAttackCBox = new System.Windows.Forms.CheckBox();
            this.instaDeathLabel = new System.Windows.Forms.Label();
            this.instaDeathCBox = new System.Windows.Forms.CheckBox();
            this.PlayerTimePanel = new System.Windows.Forms.Panel();
            this.checkBoxAI = new System.Windows.Forms.CheckBox();
            this.checkBox2Player = new System.Windows.Forms.CheckBox();
            this.checkBoxSolo = new System.Windows.Forms.CheckBox();
            this.PlayerTypeLabel = new System.Windows.Forms.Label();
            this.bouton_Cancel = new System.Windows.Forms.Button();
            this.ZonesDisponibles = new System.Windows.Forms.ListView();
            this.columnHeader1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.screenShot = new System.Windows.Forms.PictureBox();
            this.bouton_OK = new System.Windows.Forms.Button();
            this.label_ZJDisp = new System.Windows.Forms.Label();
            this.LobbyTab = new System.Windows.Forms.TabPage();
            this.GameTutoPanel = new System.Windows.Forms.Panel();
            this.GameTutoNext = new System.Windows.Forms.Button();
            this.GameTutoCancel = new System.Windows.Forms.Button();
            this.GameTutoLabel = new System.Windows.Forms.Label();
            this.MPCreatePanel = new System.Windows.Forms.Panel();
            this.PlayerTitleLabel = new System.Windows.Forms.Label();
            this.EmptyMPGameBtn = new System.Windows.Forms.Button();
            this.RemoveMPGameBtn = new System.Windows.Forms.Button();
            this.AddMPGameBtn = new System.Windows.Forms.Button();
            this.ChosenGamesLabel = new System.Windows.Forms.Label();
            this.MPGameSelected = new System.Windows.Forms.ListView();
            this.columnHeader11 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader12 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.MPCreateGModeLabel = new System.Windows.Forms.Label();
            this.MPCreateGModeCBox = new System.Windows.Forms.CheckBox();
            this.joinedPlayerView = new System.Windows.Forms.ListView();
            this.columnHeader9 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader10 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.MPTimeLimitLabel = new System.Windows.Forms.Label();
            this.MPCreatePlusBtn = new System.Windows.Forms.Button();
            this.MPCreateMinus = new System.Windows.Forms.Button();
            this.MPtimeLabel = new System.Windows.Forms.Label();
            this.MPTimerLabel = new System.Windows.Forms.Label();
            this.MPCreateCBoxTime = new System.Windows.Forms.CheckBox();
            this.MpInstaDeathLabel = new System.Windows.Forms.Label();
            this.MPCreateCBoxID = new System.Windows.Forms.CheckBox();
            this.MPInfoPanel = new System.Windows.Forms.Panel();
            this.MPCreateRoomBtn = new System.Windows.Forms.Button();
            this.MPPasswordTBox = new System.Windows.Forms.TextBox();
            this.MPPasswordLabel = new System.Windows.Forms.Label();
            this.MPCreateCancelBtn = new System.Windows.Forms.Button();
            this.MPZonesDisponibles = new System.Windows.Forms.ListView();
            this.columnHeader7 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader8 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.MPScreenShot = new System.Windows.Forms.PictureBox();
            this.MPCreateStartBtn = new System.Windows.Forms.Button();
            this.MPZonesDisponiblesLabel = new System.Windows.Forms.Label();
            this.MPGameSelectTab = new System.Windows.Forms.TabPage();
            this.MPJoinGameSelectPanel = new System.Windows.Forms.Panel();
            this.MPJoinErrorLabel = new System.Windows.Forms.Label();
            this.MPJoinPasswordTBox = new System.Windows.Forms.TextBox();
            this.MPJoinPasswordLabel = new System.Windows.Forms.Label();
            this.RefreshBtn = new System.Windows.Forms.Button();
            this.MPJoinGameView = new System.Windows.Forms.ListView();
            this.HostName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.MapName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.gameType = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.LobbyOrGame = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.hiddenGames = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.panel2 = new System.Windows.Forms.Panel();
            this.MPJoinAvailableGamesLabel = new System.Windows.Forms.Label();
            this.MPJoinReturnBtn = new System.Windows.Forms.Button();
            this.MPJoinSelectBtn = new System.Windows.Forms.Button();
            this.MPJoinPanel = new System.Windows.Forms.Panel();
            this.ZoneJoinLabel = new System.Windows.Forms.Label();
            this.GameListView = new System.Windows.Forms.ListView();
            this.JoinedGames = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.JoinPlayerTitleLabel = new System.Windows.Forms.Label();
            this.MPJoinPlayersView = new System.Windows.Forms.ListView();
            this.PlayerName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PlayerStatus = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.MPJoinInfo = new System.Windows.Forms.Panel();
            this.MPJoinGameTypeLabel = new System.Windows.Forms.Label();
            this.MPJoinMapName = new System.Windows.Forms.Label();
            this.MPJoinTimeValue = new System.Windows.Forms.Label();
            this.MPJoinTimeLabel = new System.Windows.Forms.Label();
            this.MPJoinIDLabel = new System.Windows.Forms.Label();
            this.MPJoinBackBtn = new System.Windows.Forms.Button();
            this.MPJoinScreenShot = new System.Windows.Forms.PictureBox();
            this.MPJoinReadyBtn = new System.Windows.Forms.Button();
            this.OptionsTab = new System.Windows.Forms.TabPage();
            this.OptionsMainPanel = new System.Windows.Forms.Panel();
            this.lblLangue = new System.Windows.Forms.Label();
            this.labelLangage = new System.Windows.Forms.Label();
            this.btnEnglish = new System.Windows.Forms.Button();
            this.btnFrench = new System.Windows.Forms.Button();
            this.ReturnBtn = new System.Windows.Forms.Button();
            this.AcceptBtn = new System.Windows.Forms.Button();
            this.OptionsTitlePanel = new System.Windows.Forms.Panel();
            this.OptionsLabel = new System.Windows.Forms.Label();
            this.OptionPanel2 = new System.Windows.Forms.Panel();
            this.NBillesPanel = new System.Windows.Forms.Panel();
            this.Billes7CBox = new System.Windows.Forms.CheckBox();
            this.Billes5CBox = new System.Windows.Forms.CheckBox();
            this.Billes3CBox = new System.Windows.Forms.CheckBox();
            this.NBillesLabel = new System.Windows.Forms.Label();
            this.DebufConfigPanel = new System.Windows.Forms.Panel();
            this.DebugCBox = new System.Windows.Forms.CheckBox();
            this.DebugEnableLabel = new System.Windows.Forms.Label();
            this.PortailsLabel = new System.Windows.Forms.Label();
            this.PortailsCBox = new System.Windows.Forms.CheckBox();
            this.EclairageCBox = new System.Windows.Forms.CheckBox();
            this.EclairageLabel = new System.Windows.Forms.Label();
            this.VitesseLabel = new System.Windows.Forms.Label();
            this.VitesseCBox = new System.Windows.Forms.CheckBox();
            this.GBilleCBox = new System.Windows.Forms.CheckBox();
            this.GBilleLabel = new System.Windows.Forms.Label();
            this.ConfigPanel = new System.Windows.Forms.Panel();
            this.smartAICBox = new System.Windows.Forms.CheckBox();
            this.AISmartLabel = new System.Windows.Forms.Label();
            this.FSPLabel = new System.Windows.Forms.Label();
            this.FSPCBox = new System.Windows.Forms.CheckBox();
            this.MDBCBox = new System.Windows.Forms.CheckBox();
            this.MDBLabel = new System.Windows.Forms.Label();
            this.OptionPanel1 = new System.Windows.Forms.Panel();
            this.label_Rebind = new System.Windows.Forms.Label();
            this.Ressort_bouton = new System.Windows.Forms.Button();
            this.PDJ2_bouton = new System.Windows.Forms.Button();
            this.PGJ2_bouton = new System.Windows.Forms.Button();
            this.PDJ1_bouton = new System.Windows.Forms.Button();
            this.PGJ1_bouton = new System.Windows.Forms.Button();
            this.Default_bouton = new System.Windows.Forms.Button();
            this.label_Ressort = new System.Windows.Forms.Label();
            this.label_PDJ2 = new System.Windows.Forms.Label();
            this.label_PGJ2 = new System.Windows.Forms.Label();
            this.label_PDJ1 = new System.Windows.Forms.Label();
            this.Label_PGJ1 = new System.Windows.Forms.Label();
            this.MarketplaceTab = new System.Windows.Forms.TabPage();
            this.AvatarPanelButton = new System.Windows.Forms.Button();
            this.MapPanelButton = new System.Windows.Forms.Button();
            this.MarketPlaceMapPanel = new System.Windows.Forms.Panel();
            this.MapErrorLabel = new System.Windows.Forms.Label();
            this.MarketPlaceTitle = new System.Windows.Forms.Label();
            this.MarketPlaceView = new System.Windows.Forms.ListView();
            this.columnHeader13 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHeader14 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.MarketPlacePicture = new System.Windows.Forms.PictureBox();
            this.BuyMapButton = new System.Windows.Forms.Button();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.MarketPlaceReturnBtn = new System.Windows.Forms.Button();
            this.MarketPlacePanel = new System.Windows.Forms.Panel();
            this.BuyAvatarButton = new System.Windows.Forms.Button();
            this.MarketPlaceAvatarPriceLabel = new System.Windows.Forms.Label();
            this.MarketPlaceAvatarPanel = new System.Windows.Forms.TableLayoutPanel();
            this.tabControl1.SuspendLayout();
            this.LoginTab.SuspendLayout();
            this.ErrorPanel.SuspendLayout();
            this.CreateAccountPanel.SuspendLayout();
            this.CAInfoPanel.SuspendLayout();
            this.PseudoPanel.SuspendLayout();
            this.LogInPanel.SuspendLayout();
            this.InfoPanel.SuspendLayout();
            this.MainTab.SuspendLayout();
            this.DownloadPanel.SuspendLayout();
            this.PlayerInfoPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.AvatarBox)).BeginInit();
            this.MultiPlayerPanel.SuspendLayout();
            this.SinglePlayerPanel.SuspendLayout();
            this.MainPanel.SuspendLayout();
            this.CampaignTab.SuspendLayout();
            this.CampaignPanel.SuspendLayout();
            this.CampaignPlayerTypePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.CampaignScreenShotBox)).BeginInit();
            this.QuickGameTab.SuspendLayout();
            this.QGamePanel.SuspendLayout();
            this.PlayerTimePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.screenShot)).BeginInit();
            this.LobbyTab.SuspendLayout();
            this.GameTutoPanel.SuspendLayout();
            this.MPCreatePanel.SuspendLayout();
            this.MPInfoPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MPScreenShot)).BeginInit();
            this.MPGameSelectTab.SuspendLayout();
            this.MPJoinGameSelectPanel.SuspendLayout();
            this.panel2.SuspendLayout();
            this.MPJoinPanel.SuspendLayout();
            this.MPJoinInfo.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MPJoinScreenShot)).BeginInit();
            this.OptionsTab.SuspendLayout();
            this.OptionsMainPanel.SuspendLayout();
            this.OptionsTitlePanel.SuspendLayout();
            this.OptionPanel2.SuspendLayout();
            this.NBillesPanel.SuspendLayout();
            this.DebufConfigPanel.SuspendLayout();
            this.ConfigPanel.SuspendLayout();
            this.OptionPanel1.SuspendLayout();
            this.MarketplaceTab.SuspendLayout();
            this.MarketPlaceMapPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MarketPlacePicture)).BeginInit();
            this.MarketPlacePanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.LoginTab);
            this.tabControl1.Controls.Add(this.MainTab);
            this.tabControl1.Controls.Add(this.CampaignTab);
            this.tabControl1.Controls.Add(this.QuickGameTab);
            this.tabControl1.Controls.Add(this.LobbyTab);
            this.tabControl1.Controls.Add(this.MPGameSelectTab);
            this.tabControl1.Controls.Add(this.OptionsTab);
            this.tabControl1.Controls.Add(this.MarketplaceTab);
            resources.ApplyResources(this.tabControl1, "tabControl1");
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            // 
            // LoginTab
            // 
            this.LoginTab.BackColor = System.Drawing.Color.DarkGray;
            this.LoginTab.Controls.Add(this.ErrorPanel);
            this.LoginTab.Controls.Add(this.CreateAccountPanel);
            this.LoginTab.Controls.Add(this.CAccountBtn);
            this.LoginTab.Controls.Add(this.QGameBtn);
            this.LoginTab.Controls.Add(this.LogInPanel);
            resources.ApplyResources(this.LoginTab, "LoginTab");
            this.LoginTab.Name = "LoginTab";
            // 
            // ErrorPanel
            // 
            this.ErrorPanel.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.ErrorPanel, "ErrorPanel");
            this.ErrorPanel.Controls.Add(this.ErrorBtn);
            this.ErrorPanel.Controls.Add(this.ErrorLabel);
            this.ErrorPanel.Name = "ErrorPanel";
            // 
            // ErrorBtn
            // 
            this.ErrorBtn.BackgroundImage = global::InterfaceGraphique.Properties.Resources.buttonStock1;
            resources.ApplyResources(this.ErrorBtn, "ErrorBtn");
            this.ErrorBtn.FlatAppearance.BorderSize = 0;
            this.ErrorBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.ErrorBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.ErrorBtn.ForeColor = System.Drawing.Color.Gold;
            this.ErrorBtn.Name = "ErrorBtn";
            this.ErrorBtn.UseVisualStyleBackColor = true;
            this.ErrorBtn.Click += new System.EventHandler(this.ErroBtn_Click);
            this.ErrorBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.ErrorBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.ErrorBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.ErrorBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // ErrorLabel
            // 
            resources.ApplyResources(this.ErrorLabel, "ErrorLabel");
            this.ErrorLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.ErrorLabel.Name = "ErrorLabel";
            // 
            // CreateAccountPanel
            // 
            resources.ApplyResources(this.CreateAccountPanel, "CreateAccountPanel");
            this.CreateAccountPanel.BackColor = System.Drawing.Color.Transparent;
            this.CreateAccountPanel.Controls.Add(this.CAInfoPanel);
            this.CreateAccountPanel.Controls.Add(this.PseudoPanel);
            this.CreateAccountPanel.Controls.Add(this.CancelBtn);
            this.CreateAccountPanel.Controls.Add(this.CreateAccBtn);
            this.CreateAccountPanel.Name = "CreateAccountPanel";
            this.CreateAccountPanel.VisibleChanged += new System.EventHandler(this.CreateAccountPanel_VisibleChanged);
            // 
            // CAInfoPanel
            // 
            resources.ApplyResources(this.CAInfoPanel, "CAInfoPanel");
            this.CAInfoPanel.Controls.Add(this.CAEmailLabel);
            this.CAInfoPanel.Controls.Add(this.CAAgeLabel);
            this.CAInfoPanel.Controls.Add(this.CAEmailBox);
            this.CAInfoPanel.Controls.Add(this.CAAgeBox);
            this.CAInfoPanel.Name = "CAInfoPanel";
            // 
            // CAEmailLabel
            // 
            resources.ApplyResources(this.CAEmailLabel, "CAEmailLabel");
            this.CAEmailLabel.ForeColor = System.Drawing.Color.Yellow;
            this.CAEmailLabel.Name = "CAEmailLabel";
            // 
            // CAAgeLabel
            // 
            resources.ApplyResources(this.CAAgeLabel, "CAAgeLabel");
            this.CAAgeLabel.ForeColor = System.Drawing.Color.Yellow;
            this.CAAgeLabel.Name = "CAAgeLabel";
            // 
            // CAEmailBox
            // 
            this.CAEmailBox.BackColor = System.Drawing.SystemColors.InfoText;
            this.CAEmailBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            resources.ApplyResources(this.CAEmailBox, "CAEmailBox");
            this.CAEmailBox.ForeColor = System.Drawing.Color.Red;
            this.CAEmailBox.Name = "CAEmailBox";
            // 
            // CAAgeBox
            // 
            this.CAAgeBox.BackColor = System.Drawing.SystemColors.InfoText;
            this.CAAgeBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            resources.ApplyResources(this.CAAgeBox, "CAAgeBox");
            this.CAAgeBox.ForeColor = System.Drawing.Color.Red;
            this.CAAgeBox.Name = "CAAgeBox";
            // 
            // PseudoPanel
            // 
            resources.ApplyResources(this.PseudoPanel, "PseudoPanel");
            this.PseudoPanel.Controls.Add(this.CAPseudoLabel);
            this.PseudoPanel.Controls.Add(this.CAPasswordLabel);
            this.PseudoPanel.Controls.Add(this.CAPseudoBox);
            this.PseudoPanel.Controls.Add(this.CAPasswordBox);
            this.PseudoPanel.Name = "PseudoPanel";
            // 
            // CAPseudoLabel
            // 
            resources.ApplyResources(this.CAPseudoLabel, "CAPseudoLabel");
            this.CAPseudoLabel.ForeColor = System.Drawing.Color.Yellow;
            this.CAPseudoLabel.Name = "CAPseudoLabel";
            // 
            // CAPasswordLabel
            // 
            resources.ApplyResources(this.CAPasswordLabel, "CAPasswordLabel");
            this.CAPasswordLabel.ForeColor = System.Drawing.Color.Yellow;
            this.CAPasswordLabel.Name = "CAPasswordLabel";
            // 
            // CAPseudoBox
            // 
            this.CAPseudoBox.BackColor = System.Drawing.SystemColors.InfoText;
            this.CAPseudoBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            resources.ApplyResources(this.CAPseudoBox, "CAPseudoBox");
            this.CAPseudoBox.ForeColor = System.Drawing.Color.Red;
            this.CAPseudoBox.Name = "CAPseudoBox";
            // 
            // CAPasswordBox
            // 
            this.CAPasswordBox.BackColor = System.Drawing.SystemColors.InfoText;
            this.CAPasswordBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            resources.ApplyResources(this.CAPasswordBox, "CAPasswordBox");
            this.CAPasswordBox.ForeColor = System.Drawing.Color.Red;
            this.CAPasswordBox.Name = "CAPasswordBox";
            // 
            // CancelBtn
            // 
            resources.ApplyResources(this.CancelBtn, "CancelBtn");
            this.CancelBtn.BackColor = System.Drawing.Color.Transparent;
            this.CancelBtn.FlatAppearance.BorderSize = 0;
            this.CancelBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.CancelBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.CancelBtn.ForeColor = System.Drawing.Color.Gold;
            this.CancelBtn.Name = "CancelBtn";
            this.CancelBtn.TabStop = false;
            this.CancelBtn.UseVisualStyleBackColor = false;
            this.CancelBtn.Click += new System.EventHandler(this.CancelBtn_Click);
            this.CancelBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.CancelBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.CancelBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.CancelBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // CreateAccBtn
            // 
            resources.ApplyResources(this.CreateAccBtn, "CreateAccBtn");
            this.CreateAccBtn.BackColor = System.Drawing.Color.Transparent;
            this.CreateAccBtn.FlatAppearance.BorderSize = 0;
            this.CreateAccBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.CreateAccBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.CreateAccBtn.ForeColor = System.Drawing.Color.Gold;
            this.CreateAccBtn.Name = "CreateAccBtn";
            this.CreateAccBtn.TabStop = false;
            this.CreateAccBtn.UseVisualStyleBackColor = false;
            this.CreateAccBtn.Click += new System.EventHandler(this.CreateAccBtn_Click);
            this.CreateAccBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.CreateAccBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.CreateAccBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.CreateAccBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // CAccountBtn
            // 
            this.CAccountBtn.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.CAccountBtn, "CAccountBtn");
            this.CAccountBtn.FlatAppearance.BorderSize = 0;
            this.CAccountBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.CAccountBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.CAccountBtn.ForeColor = System.Drawing.Color.Gold;
            this.CAccountBtn.Name = "CAccountBtn";
            this.CAccountBtn.TabStop = false;
            this.CAccountBtn.UseVisualStyleBackColor = false;
            this.CAccountBtn.Click += new System.EventHandler(this.CAccountBtn_Click);
            this.CAccountBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.CAccountBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.CAccountBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.CAccountBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // QGameBtn
            // 
            this.QGameBtn.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.QGameBtn, "QGameBtn");
            this.QGameBtn.FlatAppearance.BorderSize = 0;
            this.QGameBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.QGameBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.QGameBtn.ForeColor = System.Drawing.Color.Gold;
            this.QGameBtn.Name = "QGameBtn";
            this.QGameBtn.TabStop = false;
            this.QGameBtn.UseVisualStyleBackColor = false;
            this.QGameBtn.Click += new System.EventHandler(this.QGameBtn_Click);
            this.QGameBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.QGameBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.QGameBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.QGameBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // LogInPanel
            // 
            resources.ApplyResources(this.LogInPanel, "LogInPanel");
            this.LogInPanel.BackColor = System.Drawing.Color.Transparent;
            this.LogInPanel.Controls.Add(this.ServerConnectBtn);
            this.LogInPanel.Controls.Add(this.IPAddressBox);
            this.LogInPanel.Controls.Add(this.InfoPanel);
            this.LogInPanel.Controls.Add(this.PasswordResetLink);
            this.LogInPanel.Controls.Add(this.PlayOfflineBtn);
            this.LogInPanel.Controls.Add(this.LogibBtnLogin);
            this.LogInPanel.Name = "LogInPanel";
            // 
            // ServerConnectBtn
            // 
            this.ServerConnectBtn.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.ServerConnectBtn, "ServerConnectBtn");
            this.ServerConnectBtn.FlatAppearance.BorderSize = 0;
            this.ServerConnectBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.ServerConnectBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.ServerConnectBtn.ForeColor = System.Drawing.Color.Gold;
            this.ServerConnectBtn.Name = "ServerConnectBtn";
            this.ServerConnectBtn.TabStop = false;
            this.ServerConnectBtn.UseVisualStyleBackColor = false;
            this.ServerConnectBtn.Click += new System.EventHandler(this.ServerConnectBtn_Click);
            this.ServerConnectBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.ServerConnectBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.ServerConnectBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.ServerConnectBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // IPAddressBox
            // 
            this.IPAddressBox.ForeColor = System.Drawing.Color.Red;
            resources.ApplyResources(this.IPAddressBox, "IPAddressBox");
            this.IPAddressBox.Name = "IPAddressBox";
            // 
            // InfoPanel
            // 
            resources.ApplyResources(this.InfoPanel, "InfoPanel");
            this.InfoPanel.Controls.Add(this.UsernameLabelLogin);
            this.InfoPanel.Controls.Add(this.PasswordLabel);
            this.InfoPanel.Controls.Add(this.UsernameBox);
            this.InfoPanel.Controls.Add(this.PasswordBox);
            this.InfoPanel.Name = "InfoPanel";
            // 
            // UsernameLabelLogin
            // 
            resources.ApplyResources(this.UsernameLabelLogin, "UsernameLabelLogin");
            this.UsernameLabelLogin.ForeColor = System.Drawing.Color.Yellow;
            this.UsernameLabelLogin.Name = "UsernameLabelLogin";
            // 
            // PasswordLabel
            // 
            resources.ApplyResources(this.PasswordLabel, "PasswordLabel");
            this.PasswordLabel.ForeColor = System.Drawing.Color.Yellow;
            this.PasswordLabel.Name = "PasswordLabel";
            // 
            // UsernameBox
            // 
            this.UsernameBox.BackColor = System.Drawing.SystemColors.InfoText;
            this.UsernameBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            resources.ApplyResources(this.UsernameBox, "UsernameBox");
            this.UsernameBox.ForeColor = System.Drawing.Color.Red;
            this.UsernameBox.Name = "UsernameBox";
            this.UsernameBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.LogInPress);
            // 
            // PasswordBox
            // 
            this.PasswordBox.BackColor = System.Drawing.SystemColors.InfoText;
            this.PasswordBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            resources.ApplyResources(this.PasswordBox, "PasswordBox");
            this.PasswordBox.ForeColor = System.Drawing.Color.Red;
            this.PasswordBox.Name = "PasswordBox";
            this.PasswordBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.LogInPress);
            // 
            // PasswordResetLink
            // 
            resources.ApplyResources(this.PasswordResetLink, "PasswordResetLink");
            this.PasswordResetLink.BackColor = System.Drawing.Color.Transparent;
            this.PasswordResetLink.LinkColor = System.Drawing.Color.Gold;
            this.PasswordResetLink.Name = "PasswordResetLink";
            this.PasswordResetLink.TabStop = true;
            this.PasswordResetLink.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.PasswordResetLink_LinkClicked);
            // 
            // PlayOfflineBtn
            // 
            resources.ApplyResources(this.PlayOfflineBtn, "PlayOfflineBtn");
            this.PlayOfflineBtn.BackColor = System.Drawing.Color.Transparent;
            this.PlayOfflineBtn.FlatAppearance.BorderSize = 0;
            this.PlayOfflineBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PlayOfflineBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PlayOfflineBtn.ForeColor = System.Drawing.Color.Gold;
            this.PlayOfflineBtn.Name = "PlayOfflineBtn";
            this.PlayOfflineBtn.TabStop = false;
            this.PlayOfflineBtn.UseVisualStyleBackColor = false;
            this.PlayOfflineBtn.Click += new System.EventHandler(this.PlayOfflineBtn_Click);
            this.PlayOfflineBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.PlayOfflineBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.PlayOfflineBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.PlayOfflineBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // LogibBtnLogin
            // 
            resources.ApplyResources(this.LogibBtnLogin, "LogibBtnLogin");
            this.LogibBtnLogin.BackColor = System.Drawing.Color.Transparent;
            this.LogibBtnLogin.FlatAppearance.BorderSize = 0;
            this.LogibBtnLogin.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.LogibBtnLogin.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.LogibBtnLogin.ForeColor = System.Drawing.Color.Gold;
            this.LogibBtnLogin.Name = "LogibBtnLogin";
            this.LogibBtnLogin.TabStop = false;
            this.LogibBtnLogin.UseVisualStyleBackColor = false;
            this.LogibBtnLogin.Click += new System.EventHandler(this.LogibBtnLogin_Click);
            this.LogibBtnLogin.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.LogibBtnLogin.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.LogibBtnLogin.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.LogibBtnLogin.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MainTab
            // 
            this.MainTab.BackColor = System.Drawing.Color.Transparent;
            this.MainTab.Controls.Add(this.DownloadPanel);
            this.MainTab.Controls.Add(this.TestButton);
            this.MainTab.Controls.Add(this.AchievementMainPanel);
            this.MainTab.Controls.Add(this.avatarPanel);
            this.MainTab.Controls.Add(this.PlayerInfoPanel);
            this.MainTab.Controls.Add(this.MultiPlayerPanel);
            this.MainTab.Controls.Add(this.SinglePlayerPanel);
            this.MainTab.Controls.Add(this.ConnectBtn);
            this.MainTab.Controls.Add(this.MainPanel);
            resources.ApplyResources(this.MainTab, "MainTab");
            this.MainTab.Name = "MainTab";
            // 
            // DownloadPanel
            // 
            this.DownloadPanel.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.DownloadPanel, "DownloadPanel");
            this.DownloadPanel.Controls.Add(this.DownloadLabel);
            this.DownloadPanel.Name = "DownloadPanel";
            // 
            // DownloadLabel
            // 
            resources.ApplyResources(this.DownloadLabel, "DownloadLabel");
            this.DownloadLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.DownloadLabel.Name = "DownloadLabel";
            // 
            // TestButton
            // 
            this.TestButton.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.TestButton, "TestButton");
            this.TestButton.FlatAppearance.BorderSize = 0;
            this.TestButton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.TestButton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.TestButton.ForeColor = System.Drawing.Color.Gold;
            this.TestButton.Name = "TestButton";
            this.TestButton.UseVisualStyleBackColor = false;
            this.TestButton.Click += new System.EventHandler(this.TestButton_Click);
            this.TestButton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.TestButton.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.TestButton.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.TestButton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // AchievementMainPanel
            // 
            resources.ApplyResources(this.AchievementMainPanel, "AchievementMainPanel");
            this.AchievementMainPanel.Name = "AchievementMainPanel";
            // 
            // avatarPanel
            // 
            resources.ApplyResources(this.avatarPanel, "avatarPanel");
            this.avatarPanel.BackColor = System.Drawing.Color.Black;
            this.avatarPanel.Name = "avatarPanel";
            // 
            // PlayerInfoPanel
            // 
            resources.ApplyResources(this.PlayerInfoPanel, "PlayerInfoPanel");
            this.PlayerInfoPanel.Controls.Add(this.PlayerCompVictoriesLabel);
            this.PlayerInfoPanel.Controls.Add(this.avatarBtn);
            this.PlayerInfoPanel.Controls.Add(this.PlayerInfoErrorLabel);
            this.PlayerInfoPanel.Controls.Add(this.PlayerInfoPrivateLabel);
            this.PlayerInfoPanel.Controls.Add(this.PlayerInfoPrivateProfile);
            this.PlayerInfoPanel.Controls.Add(this.PlayerCoopVictoriesLabel);
            this.PlayerInfoPanel.Controls.Add(this.PlayerInfoVictoriesLabel);
            this.PlayerInfoPanel.Controls.Add(this.PlayerInfoGamePlayedLabel);
            this.PlayerInfoPanel.Controls.Add(this.PlayerNewPasswordLabel);
            this.PlayerInfoPanel.Controls.Add(this.PlayerNewPasswordTBox);
            this.PlayerInfoPanel.Controls.Add(this.PlayerOldPasswordLabel);
            this.PlayerInfoPanel.Controls.Add(this.PlayerOldPasswordTBox);
            this.PlayerInfoPanel.Controls.Add(this.PlayerEditAnnulerBtn);
            this.PlayerInfoPanel.Controls.Add(this.PlayerEditAcceptBtn);
            this.PlayerInfoPanel.Controls.Add(this.PlayerEditBtn);
            this.PlayerInfoPanel.Controls.Add(this.AchievBtn);
            this.PlayerInfoPanel.Controls.Add(this.PlayerAgeLabel);
            this.PlayerInfoPanel.Controls.Add(this.PlayerAgeTBox);
            this.PlayerInfoPanel.Controls.Add(this.PlayerEmailLabel);
            this.PlayerInfoPanel.Controls.Add(this.PlayerEmailTBox);
            this.PlayerInfoPanel.Controls.Add(this.PlayerSurnameLabel);
            this.PlayerInfoPanel.Controls.Add(this.PlayerSurnameTBox);
            this.PlayerInfoPanel.Controls.Add(this.PlayerNameLabel);
            this.PlayerInfoPanel.Controls.Add(this.PlayerNameTBox);
            this.PlayerInfoPanel.Controls.Add(this.APointsLabel);
            this.PlayerInfoPanel.Controls.Add(this.CurrencyLabel);
            this.PlayerInfoPanel.Controls.Add(this.AvatarBox);
            this.PlayerInfoPanel.Controls.Add(this.NomLabel);
            this.PlayerInfoPanel.Name = "PlayerInfoPanel";
            // 
            // PlayerCompVictoriesLabel
            // 
            resources.ApplyResources(this.PlayerCompVictoriesLabel, "PlayerCompVictoriesLabel");
            this.PlayerCompVictoriesLabel.ForeColor = System.Drawing.Color.Gold;
            this.PlayerCompVictoriesLabel.Name = "PlayerCompVictoriesLabel";
            // 
            // avatarBtn
            // 
            this.avatarBtn.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.avatarBtn, "avatarBtn");
            this.avatarBtn.FlatAppearance.BorderSize = 0;
            this.avatarBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.avatarBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.avatarBtn.ForeColor = System.Drawing.Color.Gold;
            this.avatarBtn.Name = "avatarBtn";
            this.avatarBtn.UseVisualStyleBackColor = false;
            this.avatarBtn.Click += new System.EventHandler(this.avatarBtn_Click);
            // 
            // PlayerInfoErrorLabel
            // 
            resources.ApplyResources(this.PlayerInfoErrorLabel, "PlayerInfoErrorLabel");
            this.PlayerInfoErrorLabel.ForeColor = System.Drawing.Color.Red;
            this.PlayerInfoErrorLabel.Name = "PlayerInfoErrorLabel";
            // 
            // PlayerInfoPrivateLabel
            // 
            resources.ApplyResources(this.PlayerInfoPrivateLabel, "PlayerInfoPrivateLabel");
            this.PlayerInfoPrivateLabel.ForeColor = System.Drawing.Color.Gold;
            this.PlayerInfoPrivateLabel.Name = "PlayerInfoPrivateLabel";
            // 
            // PlayerInfoPrivateProfile
            // 
            resources.ApplyResources(this.PlayerInfoPrivateProfile, "PlayerInfoPrivateProfile");
            this.PlayerInfoPrivateProfile.BackgroundImage = global::InterfaceGraphique.Properties.Resources.borderStock;
            this.PlayerInfoPrivateProfile.Checked = true;
            this.PlayerInfoPrivateProfile.CheckState = System.Windows.Forms.CheckState.Checked;
            this.PlayerInfoPrivateProfile.FlatAppearance.BorderSize = 0;
            this.PlayerInfoPrivateProfile.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.PlayerInfoPrivateProfile.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PlayerInfoPrivateProfile.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PlayerInfoPrivateProfile.ForeColor = System.Drawing.Color.Gold;
            this.PlayerInfoPrivateProfile.Name = "PlayerInfoPrivateProfile";
            this.PlayerInfoPrivateProfile.UseVisualStyleBackColor = true;
            this.PlayerInfoPrivateProfile.CheckedChanged += new System.EventHandler(this.PlayerInfoPrivateProfile_CheckedChanged);
            // 
            // PlayerCoopVictoriesLabel
            // 
            resources.ApplyResources(this.PlayerCoopVictoriesLabel, "PlayerCoopVictoriesLabel");
            this.PlayerCoopVictoriesLabel.ForeColor = System.Drawing.Color.Gold;
            this.PlayerCoopVictoriesLabel.Name = "PlayerCoopVictoriesLabel";
            // 
            // PlayerInfoVictoriesLabel
            // 
            resources.ApplyResources(this.PlayerInfoVictoriesLabel, "PlayerInfoVictoriesLabel");
            this.PlayerInfoVictoriesLabel.ForeColor = System.Drawing.Color.Gold;
            this.PlayerInfoVictoriesLabel.Name = "PlayerInfoVictoriesLabel";
            // 
            // PlayerInfoGamePlayedLabel
            // 
            resources.ApplyResources(this.PlayerInfoGamePlayedLabel, "PlayerInfoGamePlayedLabel");
            this.PlayerInfoGamePlayedLabel.ForeColor = System.Drawing.Color.Gold;
            this.PlayerInfoGamePlayedLabel.Name = "PlayerInfoGamePlayedLabel";
            // 
            // PlayerNewPasswordLabel
            // 
            resources.ApplyResources(this.PlayerNewPasswordLabel, "PlayerNewPasswordLabel");
            this.PlayerNewPasswordLabel.ForeColor = System.Drawing.Color.Gold;
            this.PlayerNewPasswordLabel.Name = "PlayerNewPasswordLabel";
            // 
            // PlayerNewPasswordTBox
            // 
            this.PlayerNewPasswordTBox.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.PlayerNewPasswordTBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.PlayerNewPasswordTBox.ForeColor = System.Drawing.Color.Gold;
            resources.ApplyResources(this.PlayerNewPasswordTBox, "PlayerNewPasswordTBox");
            this.PlayerNewPasswordTBox.Name = "PlayerNewPasswordTBox";
            // 
            // PlayerOldPasswordLabel
            // 
            resources.ApplyResources(this.PlayerOldPasswordLabel, "PlayerOldPasswordLabel");
            this.PlayerOldPasswordLabel.ForeColor = System.Drawing.Color.Gold;
            this.PlayerOldPasswordLabel.Name = "PlayerOldPasswordLabel";
            // 
            // PlayerOldPasswordTBox
            // 
            this.PlayerOldPasswordTBox.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.PlayerOldPasswordTBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.PlayerOldPasswordTBox.ForeColor = System.Drawing.Color.Gold;
            resources.ApplyResources(this.PlayerOldPasswordTBox, "PlayerOldPasswordTBox");
            this.PlayerOldPasswordTBox.Name = "PlayerOldPasswordTBox";
            // 
            // PlayerEditAnnulerBtn
            // 
            resources.ApplyResources(this.PlayerEditAnnulerBtn, "PlayerEditAnnulerBtn");
            this.PlayerEditAnnulerBtn.BackColor = System.Drawing.Color.Transparent;
            this.PlayerEditAnnulerBtn.FlatAppearance.BorderSize = 0;
            this.PlayerEditAnnulerBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PlayerEditAnnulerBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PlayerEditAnnulerBtn.ForeColor = System.Drawing.Color.Gold;
            this.PlayerEditAnnulerBtn.Name = "PlayerEditAnnulerBtn";
            this.PlayerEditAnnulerBtn.UseVisualStyleBackColor = false;
            this.PlayerEditAnnulerBtn.Click += new System.EventHandler(this.PlayerEditAnnulerBtn_Click);
            this.PlayerEditAnnulerBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.PlayerEditAnnulerBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.PlayerEditAnnulerBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.PlayerEditAnnulerBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // PlayerEditAcceptBtn
            // 
            resources.ApplyResources(this.PlayerEditAcceptBtn, "PlayerEditAcceptBtn");
            this.PlayerEditAcceptBtn.BackColor = System.Drawing.Color.Transparent;
            this.PlayerEditAcceptBtn.FlatAppearance.BorderSize = 0;
            this.PlayerEditAcceptBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PlayerEditAcceptBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PlayerEditAcceptBtn.ForeColor = System.Drawing.Color.Gold;
            this.PlayerEditAcceptBtn.Name = "PlayerEditAcceptBtn";
            this.PlayerEditAcceptBtn.UseVisualStyleBackColor = false;
            this.PlayerEditAcceptBtn.Click += new System.EventHandler(this.PlayerEditAcceptBtn_Click);
            this.PlayerEditAcceptBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.PlayerEditAcceptBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.PlayerEditAcceptBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.PlayerEditAcceptBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // PlayerEditBtn
            // 
            this.PlayerEditBtn.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.PlayerEditBtn, "PlayerEditBtn");
            this.PlayerEditBtn.FlatAppearance.BorderSize = 0;
            this.PlayerEditBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PlayerEditBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PlayerEditBtn.ForeColor = System.Drawing.Color.Gold;
            this.PlayerEditBtn.Name = "PlayerEditBtn";
            this.PlayerEditBtn.UseVisualStyleBackColor = false;
            this.PlayerEditBtn.Click += new System.EventHandler(this.PlayerEditBtn_Click);
            this.PlayerEditBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.PlayerEditBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.PlayerEditBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.PlayerEditBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // AchievBtn
            // 
            resources.ApplyResources(this.AchievBtn, "AchievBtn");
            this.AchievBtn.BackColor = System.Drawing.Color.Transparent;
            this.AchievBtn.FlatAppearance.BorderSize = 0;
            this.AchievBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.AchievBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.AchievBtn.ForeColor = System.Drawing.Color.Gold;
            this.AchievBtn.Name = "AchievBtn";
            this.AchievBtn.UseVisualStyleBackColor = false;
            this.AchievBtn.Click += new System.EventHandler(this.AchievBtn_Click);
            this.AchievBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.AchievBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.AchievBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.AchievBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // PlayerAgeLabel
            // 
            resources.ApplyResources(this.PlayerAgeLabel, "PlayerAgeLabel");
            this.PlayerAgeLabel.ForeColor = System.Drawing.Color.Gold;
            this.PlayerAgeLabel.Name = "PlayerAgeLabel";
            // 
            // PlayerAgeTBox
            // 
            this.PlayerAgeTBox.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.PlayerAgeTBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.PlayerAgeTBox.ForeColor = System.Drawing.Color.Gold;
            resources.ApplyResources(this.PlayerAgeTBox, "PlayerAgeTBox");
            this.PlayerAgeTBox.Name = "PlayerAgeTBox";
            this.PlayerAgeTBox.ReadOnly = true;
            // 
            // PlayerEmailLabel
            // 
            resources.ApplyResources(this.PlayerEmailLabel, "PlayerEmailLabel");
            this.PlayerEmailLabel.ForeColor = System.Drawing.Color.Gold;
            this.PlayerEmailLabel.Name = "PlayerEmailLabel";
            // 
            // PlayerEmailTBox
            // 
            this.PlayerEmailTBox.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.PlayerEmailTBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.PlayerEmailTBox.ForeColor = System.Drawing.Color.Gold;
            resources.ApplyResources(this.PlayerEmailTBox, "PlayerEmailTBox");
            this.PlayerEmailTBox.Name = "PlayerEmailTBox";
            this.PlayerEmailTBox.ReadOnly = true;
            // 
            // PlayerSurnameLabel
            // 
            resources.ApplyResources(this.PlayerSurnameLabel, "PlayerSurnameLabel");
            this.PlayerSurnameLabel.ForeColor = System.Drawing.Color.Gold;
            this.PlayerSurnameLabel.Name = "PlayerSurnameLabel";
            // 
            // PlayerSurnameTBox
            // 
            this.PlayerSurnameTBox.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.PlayerSurnameTBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.PlayerSurnameTBox.ForeColor = System.Drawing.Color.Gold;
            resources.ApplyResources(this.PlayerSurnameTBox, "PlayerSurnameTBox");
            this.PlayerSurnameTBox.Name = "PlayerSurnameTBox";
            this.PlayerSurnameTBox.ReadOnly = true;
            // 
            // PlayerNameLabel
            // 
            resources.ApplyResources(this.PlayerNameLabel, "PlayerNameLabel");
            this.PlayerNameLabel.ForeColor = System.Drawing.Color.Gold;
            this.PlayerNameLabel.Name = "PlayerNameLabel";
            // 
            // PlayerNameTBox
            // 
            this.PlayerNameTBox.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.PlayerNameTBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.PlayerNameTBox.ForeColor = System.Drawing.Color.Gold;
            resources.ApplyResources(this.PlayerNameTBox, "PlayerNameTBox");
            this.PlayerNameTBox.Name = "PlayerNameTBox";
            this.PlayerNameTBox.ReadOnly = true;
            // 
            // APointsLabel
            // 
            resources.ApplyResources(this.APointsLabel, "APointsLabel");
            this.APointsLabel.ForeColor = System.Drawing.Color.Lime;
            this.APointsLabel.Name = "APointsLabel";
            // 
            // CurrencyLabel
            // 
            resources.ApplyResources(this.CurrencyLabel, "CurrencyLabel");
            this.CurrencyLabel.ForeColor = System.Drawing.Color.Gold;
            this.CurrencyLabel.Name = "CurrencyLabel";
            // 
            // AvatarBox
            // 
            this.AvatarBox.BackColor = System.Drawing.Color.LawnGreen;
            this.AvatarBox.BackgroundImage = global::InterfaceGraphique.Properties.Resources.Trophy;
            resources.ApplyResources(this.AvatarBox, "AvatarBox");
            this.AvatarBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.AvatarBox.Name = "AvatarBox";
            this.AvatarBox.TabStop = false;
            this.AvatarBox.Click += new System.EventHandler(this.AvatarBox_Click);
            // 
            // NomLabel
            // 
            resources.ApplyResources(this.NomLabel, "NomLabel");
            this.NomLabel.ForeColor = System.Drawing.Color.Red;
            this.NomLabel.Name = "NomLabel";
            // 
            // MultiPlayerPanel
            // 
            this.MultiPlayerPanel.Controls.Add(this.MPQuickGameBtn);
            this.MultiPlayerPanel.Controls.Add(this.RetourMPBtn);
            this.MultiPlayerPanel.Controls.Add(this.JoinBtn);
            this.MultiPlayerPanel.Controls.Add(this.CreateBtn);
            resources.ApplyResources(this.MultiPlayerPanel, "MultiPlayerPanel");
            this.MultiPlayerPanel.Name = "MultiPlayerPanel";
            // 
            // MPQuickGameBtn
            // 
            resources.ApplyResources(this.MPQuickGameBtn, "MPQuickGameBtn");
            this.MPQuickGameBtn.BackColor = System.Drawing.Color.Transparent;
            this.MPQuickGameBtn.FlatAppearance.BorderSize = 0;
            this.MPQuickGameBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MPQuickGameBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MPQuickGameBtn.ForeColor = System.Drawing.Color.Gold;
            this.MPQuickGameBtn.Name = "MPQuickGameBtn";
            this.MPQuickGameBtn.UseVisualStyleBackColor = false;
            this.MPQuickGameBtn.Click += new System.EventHandler(this.MPQuickGameBtn_Click);
            this.MPQuickGameBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MPQuickGameBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MPQuickGameBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MPQuickGameBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // RetourMPBtn
            // 
            resources.ApplyResources(this.RetourMPBtn, "RetourMPBtn");
            this.RetourMPBtn.BackColor = System.Drawing.Color.Transparent;
            this.RetourMPBtn.FlatAppearance.BorderSize = 0;
            this.RetourMPBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.RetourMPBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.RetourMPBtn.ForeColor = System.Drawing.Color.Gold;
            this.RetourMPBtn.Name = "RetourMPBtn";
            this.RetourMPBtn.UseVisualStyleBackColor = false;
            this.RetourMPBtn.Click += new System.EventHandler(this.RetourMPBtn_Click);
            this.RetourMPBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.RetourMPBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.RetourMPBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.RetourMPBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // JoinBtn
            // 
            resources.ApplyResources(this.JoinBtn, "JoinBtn");
            this.JoinBtn.BackColor = System.Drawing.Color.Transparent;
            this.JoinBtn.FlatAppearance.BorderSize = 0;
            this.JoinBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.JoinBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.JoinBtn.ForeColor = System.Drawing.Color.Gold;
            this.JoinBtn.Name = "JoinBtn";
            this.JoinBtn.UseVisualStyleBackColor = false;
            this.JoinBtn.Click += new System.EventHandler(this.JoinBtn_Click);
            this.JoinBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.JoinBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.JoinBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.JoinBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // CreateBtn
            // 
            resources.ApplyResources(this.CreateBtn, "CreateBtn");
            this.CreateBtn.BackColor = System.Drawing.Color.Transparent;
            this.CreateBtn.FlatAppearance.BorderSize = 0;
            this.CreateBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.CreateBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.CreateBtn.ForeColor = System.Drawing.Color.Gold;
            this.CreateBtn.Name = "CreateBtn";
            this.CreateBtn.UseVisualStyleBackColor = false;
            this.CreateBtn.Click += new System.EventHandler(this.CreateBtn_Click);
            this.CreateBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.CreateBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.CreateBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.CreateBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // SinglePlayerPanel
            // 
            this.SinglePlayerPanel.Controls.Add(this.RetourSPBtn);
            this.SinglePlayerPanel.Controls.Add(this.CampagneBtn);
            this.SinglePlayerPanel.Controls.Add(this.PRapideBtn);
            resources.ApplyResources(this.SinglePlayerPanel, "SinglePlayerPanel");
            this.SinglePlayerPanel.Name = "SinglePlayerPanel";
            // 
            // RetourSPBtn
            // 
            resources.ApplyResources(this.RetourSPBtn, "RetourSPBtn");
            this.RetourSPBtn.BackColor = System.Drawing.Color.Transparent;
            this.RetourSPBtn.FlatAppearance.BorderSize = 0;
            this.RetourSPBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.RetourSPBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.RetourSPBtn.ForeColor = System.Drawing.Color.Gold;
            this.RetourSPBtn.Name = "RetourSPBtn";
            this.RetourSPBtn.UseVisualStyleBackColor = false;
            this.RetourSPBtn.Click += new System.EventHandler(this.RetourSPBtn_Click);
            this.RetourSPBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.RetourSPBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.RetourSPBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.RetourSPBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // CampagneBtn
            // 
            resources.ApplyResources(this.CampagneBtn, "CampagneBtn");
            this.CampagneBtn.BackColor = System.Drawing.Color.Transparent;
            this.CampagneBtn.FlatAppearance.BorderSize = 0;
            this.CampagneBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.CampagneBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.CampagneBtn.ForeColor = System.Drawing.Color.Gold;
            this.CampagneBtn.Name = "CampagneBtn";
            this.CampagneBtn.UseVisualStyleBackColor = false;
            this.CampagneBtn.Click += new System.EventHandler(this.CampagneBtn_Click);
            this.CampagneBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.CampagneBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.CampagneBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.CampagneBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // PRapideBtn
            // 
            resources.ApplyResources(this.PRapideBtn, "PRapideBtn");
            this.PRapideBtn.BackColor = System.Drawing.Color.Transparent;
            this.PRapideBtn.FlatAppearance.BorderSize = 0;
            this.PRapideBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PRapideBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PRapideBtn.ForeColor = System.Drawing.Color.Gold;
            this.PRapideBtn.Name = "PRapideBtn";
            this.PRapideBtn.UseVisualStyleBackColor = false;
            this.PRapideBtn.Click += new System.EventHandler(this.PRapideBtn_Click);
            this.PRapideBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.PRapideBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.PRapideBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.PRapideBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // ConnectBtn
            // 
            this.ConnectBtn.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.ConnectBtn, "ConnectBtn");
            this.ConnectBtn.FlatAppearance.BorderSize = 0;
            this.ConnectBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.ConnectBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.ConnectBtn.ForeColor = System.Drawing.Color.Gold;
            this.ConnectBtn.Name = "ConnectBtn";
            this.ConnectBtn.UseVisualStyleBackColor = false;
            this.ConnectBtn.Click += new System.EventHandler(this.ConnectBtn_Click);
            this.ConnectBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.ConnectBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.ConnectBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.ConnectBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MainPanel
            // 
            this.MainPanel.BackColor = System.Drawing.Color.Transparent;
            this.MainPanel.Controls.Add(this.TutorialBtn);
            this.MainPanel.Controls.Add(this.QuitBtn);
            this.MainPanel.Controls.Add(this.MarketplaceBtn);
            this.MainPanel.Controls.Add(this.OptionsBtn);
            this.MainPanel.Controls.Add(this.EditeurBtn);
            this.MainPanel.Controls.Add(this.MultiPlayerBtn);
            this.MainPanel.Controls.Add(this.SoloBtn);
            resources.ApplyResources(this.MainPanel, "MainPanel");
            this.MainPanel.Name = "MainPanel";
            // 
            // TutorialBtn
            // 
            resources.ApplyResources(this.TutorialBtn, "TutorialBtn");
            this.TutorialBtn.BackColor = System.Drawing.Color.Transparent;
            this.TutorialBtn.FlatAppearance.BorderSize = 0;
            this.TutorialBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.TutorialBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.TutorialBtn.ForeColor = System.Drawing.Color.Gold;
            this.TutorialBtn.Name = "TutorialBtn";
            this.TutorialBtn.UseVisualStyleBackColor = false;
            this.TutorialBtn.Click += new System.EventHandler(this.TutorialBtn_Click);
            this.TutorialBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.TutorialBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.TutorialBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.TutorialBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // QuitBtn
            // 
            resources.ApplyResources(this.QuitBtn, "QuitBtn");
            this.QuitBtn.BackColor = System.Drawing.Color.Transparent;
            this.QuitBtn.FlatAppearance.BorderSize = 0;
            this.QuitBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.QuitBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.QuitBtn.ForeColor = System.Drawing.Color.Gold;
            this.QuitBtn.Name = "QuitBtn";
            this.QuitBtn.UseVisualStyleBackColor = false;
            this.QuitBtn.Click += new System.EventHandler(this.QGameBtn_Click);
            this.QuitBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.QuitBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.QuitBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.QuitBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MarketplaceBtn
            // 
            resources.ApplyResources(this.MarketplaceBtn, "MarketplaceBtn");
            this.MarketplaceBtn.BackColor = System.Drawing.Color.Transparent;
            this.MarketplaceBtn.FlatAppearance.BorderSize = 0;
            this.MarketplaceBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MarketplaceBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MarketplaceBtn.ForeColor = System.Drawing.Color.Gold;
            this.MarketplaceBtn.Name = "MarketplaceBtn";
            this.MarketplaceBtn.UseVisualStyleBackColor = false;
            this.MarketplaceBtn.Click += new System.EventHandler(this.MarketplaceBtn_Click);
            this.MarketplaceBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MarketplaceBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MarketplaceBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MarketplaceBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // OptionsBtn
            // 
            resources.ApplyResources(this.OptionsBtn, "OptionsBtn");
            this.OptionsBtn.BackColor = System.Drawing.Color.Transparent;
            this.OptionsBtn.FlatAppearance.BorderSize = 0;
            this.OptionsBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.OptionsBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.OptionsBtn.ForeColor = System.Drawing.Color.Gold;
            this.OptionsBtn.Name = "OptionsBtn";
            this.OptionsBtn.UseVisualStyleBackColor = false;
            this.OptionsBtn.Click += new System.EventHandler(this.OptionsBtn_Click);
            this.OptionsBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.OptionsBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.OptionsBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.OptionsBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // EditeurBtn
            // 
            resources.ApplyResources(this.EditeurBtn, "EditeurBtn");
            this.EditeurBtn.BackColor = System.Drawing.Color.Transparent;
            this.EditeurBtn.FlatAppearance.BorderSize = 0;
            this.EditeurBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.EditeurBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.EditeurBtn.ForeColor = System.Drawing.Color.Gold;
            this.EditeurBtn.Name = "EditeurBtn";
            this.EditeurBtn.UseVisualStyleBackColor = false;
            this.EditeurBtn.Click += new System.EventHandler(this.EditeurBtn_Click);
            this.EditeurBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.EditeurBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.EditeurBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.EditeurBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MultiPlayerBtn
            // 
            resources.ApplyResources(this.MultiPlayerBtn, "MultiPlayerBtn");
            this.MultiPlayerBtn.BackColor = System.Drawing.Color.Transparent;
            this.MultiPlayerBtn.FlatAppearance.BorderSize = 0;
            this.MultiPlayerBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MultiPlayerBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MultiPlayerBtn.ForeColor = System.Drawing.Color.Gold;
            this.MultiPlayerBtn.Name = "MultiPlayerBtn";
            this.MultiPlayerBtn.UseVisualStyleBackColor = false;
            this.MultiPlayerBtn.Click += new System.EventHandler(this.MultiPlayerBtn_Click);
            this.MultiPlayerBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MultiPlayerBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MultiPlayerBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MultiPlayerBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // SoloBtn
            // 
            resources.ApplyResources(this.SoloBtn, "SoloBtn");
            this.SoloBtn.BackColor = System.Drawing.Color.Transparent;
            this.SoloBtn.FlatAppearance.BorderSize = 0;
            this.SoloBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.SoloBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.SoloBtn.ForeColor = System.Drawing.Color.Gold;
            this.SoloBtn.Name = "SoloBtn";
            this.SoloBtn.UseVisualStyleBackColor = false;
            this.SoloBtn.Click += new System.EventHandler(this.SoloBtn_Click);
            this.SoloBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.SoloBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.SoloBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.SoloBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // CampaignTab
            // 
            this.CampaignTab.Controls.Add(this.CampaignPanel);
            resources.ApplyResources(this.CampaignTab, "CampaignTab");
            this.CampaignTab.Name = "CampaignTab";
            this.CampaignTab.UseVisualStyleBackColor = true;
            // 
            // CampaignPanel
            // 
            resources.ApplyResources(this.CampaignPanel, "CampaignPanel");
            this.CampaignPanel.Controls.Add(this.CtimeLimitLabel);
            this.CampaignPanel.Controls.Add(this.CplusBtn);
            this.CampaignPanel.Controls.Add(this.CminusBtn);
            this.CampaignPanel.Controls.Add(this.CtimeLabel);
            this.CampaignPanel.Controls.Add(this.CtimeAttackLabel);
            this.CampaignPanel.Controls.Add(this.CtimeAttackCBox);
            this.CampaignPanel.Controls.Add(this.CinstaDeathLabel);
            this.CampaignPanel.Controls.Add(this.CinstaDeathCBox);
            this.CampaignPanel.Controls.Add(this.CampaignEmptyBtn);
            this.CampaignPanel.Controls.Add(this.CampaignRemoveItemBtn);
            this.CampaignPanel.Controls.Add(this.CampaignAddBtn);
            this.CampaignPanel.Controls.Add(this.CampaignSelectedListView);
            this.CampaignPanel.Controls.Add(this.CampaignChoiceLabel);
            this.CampaignPanel.Controls.Add(this.CampaignPlayerTypePanel);
            this.CampaignPanel.Controls.Add(this.campaignCancelBtn);
            this.CampaignPanel.Controls.Add(this.CampaignZonesListView);
            this.CampaignPanel.Controls.Add(this.CampaignScreenShotBox);
            this.CampaignPanel.Controls.Add(this.campaignStartBtn);
            this.CampaignPanel.Controls.Add(this.CampaignZonesLabel);
            this.CampaignPanel.Name = "CampaignPanel";
            // 
            // CtimeLimitLabel
            // 
            resources.ApplyResources(this.CtimeLimitLabel, "CtimeLimitLabel");
            this.CtimeLimitLabel.ForeColor = System.Drawing.Color.Gold;
            this.CtimeLimitLabel.Name = "CtimeLimitLabel";
            // 
            // CplusBtn
            // 
            resources.ApplyResources(this.CplusBtn, "CplusBtn");
            this.CplusBtn.FlatAppearance.BorderSize = 0;
            this.CplusBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.CplusBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.CplusBtn.ForeColor = System.Drawing.Color.Gold;
            this.CplusBtn.Name = "CplusBtn";
            this.CplusBtn.UseVisualStyleBackColor = true;
            this.CplusBtn.Click += new System.EventHandler(this.CplusBtn_Click);
            // 
            // CminusBtn
            // 
            resources.ApplyResources(this.CminusBtn, "CminusBtn");
            this.CminusBtn.FlatAppearance.BorderSize = 0;
            this.CminusBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.CminusBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.CminusBtn.ForeColor = System.Drawing.Color.Gold;
            this.CminusBtn.Name = "CminusBtn";
            this.CminusBtn.UseVisualStyleBackColor = true;
            this.CminusBtn.Click += new System.EventHandler(this.CminusBtn_Click);
            // 
            // CtimeLabel
            // 
            resources.ApplyResources(this.CtimeLabel, "CtimeLabel");
            this.CtimeLabel.ForeColor = System.Drawing.Color.Gold;
            this.CtimeLabel.Name = "CtimeLabel";
            // 
            // CtimeAttackLabel
            // 
            resources.ApplyResources(this.CtimeAttackLabel, "CtimeAttackLabel");
            this.CtimeAttackLabel.ForeColor = System.Drawing.Color.Gold;
            this.CtimeAttackLabel.Name = "CtimeAttackLabel";
            // 
            // CtimeAttackCBox
            // 
            resources.ApplyResources(this.CtimeAttackCBox, "CtimeAttackCBox");
            this.CtimeAttackCBox.BackgroundImage = global::InterfaceGraphique.Properties.Resources.borderStock;
            this.CtimeAttackCBox.FlatAppearance.BorderSize = 0;
            this.CtimeAttackCBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.CtimeAttackCBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.CtimeAttackCBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.CtimeAttackCBox.ForeColor = System.Drawing.Color.Gold;
            this.CtimeAttackCBox.Name = "CtimeAttackCBox";
            this.CtimeAttackCBox.UseVisualStyleBackColor = true;
            this.CtimeAttackCBox.CheckedChanged += new System.EventHandler(this.CtimeAttackCBox_CheckedChanged);
            // 
            // CinstaDeathLabel
            // 
            resources.ApplyResources(this.CinstaDeathLabel, "CinstaDeathLabel");
            this.CinstaDeathLabel.ForeColor = System.Drawing.Color.Gold;
            this.CinstaDeathLabel.Name = "CinstaDeathLabel";
            // 
            // CinstaDeathCBox
            // 
            resources.ApplyResources(this.CinstaDeathCBox, "CinstaDeathCBox");
            this.CinstaDeathCBox.BackgroundImage = global::InterfaceGraphique.Properties.Resources.borderStock;
            this.CinstaDeathCBox.FlatAppearance.BorderSize = 0;
            this.CinstaDeathCBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.CinstaDeathCBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.CinstaDeathCBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.CinstaDeathCBox.ForeColor = System.Drawing.Color.Gold;
            this.CinstaDeathCBox.Name = "CinstaDeathCBox";
            this.CinstaDeathCBox.UseVisualStyleBackColor = true;
            this.CinstaDeathCBox.CheckStateChanged += new System.EventHandler(this.CinstaDeathCBox_CheckedChanged);
            // 
            // CampaignEmptyBtn
            // 
            resources.ApplyResources(this.CampaignEmptyBtn, "CampaignEmptyBtn");
            this.CampaignEmptyBtn.FlatAppearance.BorderSize = 0;
            this.CampaignEmptyBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.CampaignEmptyBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.CampaignEmptyBtn.ForeColor = System.Drawing.Color.Gold;
            this.CampaignEmptyBtn.Name = "CampaignEmptyBtn";
            this.CampaignEmptyBtn.UseVisualStyleBackColor = true;
            this.CampaignEmptyBtn.Click += new System.EventHandler(this.CampaignEmptyBtn_Click);
            this.CampaignEmptyBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.CampaignEmptyBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.CampaignEmptyBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.CampaignEmptyBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // CampaignRemoveItemBtn
            // 
            resources.ApplyResources(this.CampaignRemoveItemBtn, "CampaignRemoveItemBtn");
            this.CampaignRemoveItemBtn.FlatAppearance.BorderSize = 0;
            this.CampaignRemoveItemBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.CampaignRemoveItemBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.CampaignRemoveItemBtn.ForeColor = System.Drawing.Color.Gold;
            this.CampaignRemoveItemBtn.Name = "CampaignRemoveItemBtn";
            this.CampaignRemoveItemBtn.UseVisualStyleBackColor = true;
            this.CampaignRemoveItemBtn.Click += new System.EventHandler(this.CampaignRemoveItemBtn_Click);
            this.CampaignRemoveItemBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.CampaignRemoveItemBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.CampaignRemoveItemBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.CampaignRemoveItemBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // CampaignAddBtn
            // 
            resources.ApplyResources(this.CampaignAddBtn, "CampaignAddBtn");
            this.CampaignAddBtn.FlatAppearance.BorderSize = 0;
            this.CampaignAddBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.CampaignAddBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.CampaignAddBtn.ForeColor = System.Drawing.Color.Gold;
            this.CampaignAddBtn.Name = "CampaignAddBtn";
            this.CampaignAddBtn.UseVisualStyleBackColor = true;
            this.CampaignAddBtn.Click += new System.EventHandler(this.CampaignAddBtn_Click);
            this.CampaignAddBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.CampaignAddBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.CampaignAddBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.CampaignAddBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // CampaignSelectedListView
            // 
            this.CampaignSelectedListView.BackColor = System.Drawing.SystemColors.InfoText;
            this.CampaignSelectedListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader5,
            this.columnHeader6});
            this.CampaignSelectedListView.ForeColor = System.Drawing.Color.Red;
            this.CampaignSelectedListView.FullRowSelect = true;
            this.CampaignSelectedListView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            resources.ApplyResources(this.CampaignSelectedListView, "CampaignSelectedListView");
            this.CampaignSelectedListView.MultiSelect = false;
            this.CampaignSelectedListView.Name = "CampaignSelectedListView";
            this.CampaignSelectedListView.UseCompatibleStateImageBehavior = false;
            this.CampaignSelectedListView.View = System.Windows.Forms.View.Details;
            this.CampaignSelectedListView.SelectedIndexChanged += new System.EventHandler(this.CampaignSelectedListView_SelectedIndexChanged);
            // 
            // columnHeader5
            // 
            resources.ApplyResources(this.columnHeader5, "columnHeader5");
            // 
            // columnHeader6
            // 
            resources.ApplyResources(this.columnHeader6, "columnHeader6");
            // 
            // CampaignChoiceLabel
            // 
            resources.ApplyResources(this.CampaignChoiceLabel, "CampaignChoiceLabel");
            this.CampaignChoiceLabel.ForeColor = System.Drawing.Color.Gold;
            this.CampaignChoiceLabel.Name = "CampaignChoiceLabel";
            // 
            // CampaignPlayerTypePanel
            // 
            this.CampaignPlayerTypePanel.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.CampaignPlayerTypePanel, "CampaignPlayerTypePanel");
            this.CampaignPlayerTypePanel.Controls.Add(this.checkBoxCAI);
            this.CampaignPlayerTypePanel.Controls.Add(this.checkBoxC2);
            this.CampaignPlayerTypePanel.Controls.Add(this.checkBoxCSolo);
            this.CampaignPlayerTypePanel.Controls.Add(this.CampaignPlayerTypeLabel);
            this.CampaignPlayerTypePanel.Name = "CampaignPlayerTypePanel";
            // 
            // checkBoxCAI
            // 
            resources.ApplyResources(this.checkBoxCAI, "checkBoxCAI");
            this.checkBoxCAI.FlatAppearance.BorderSize = 0;
            this.checkBoxCAI.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.checkBoxCAI.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.checkBoxCAI.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.checkBoxCAI.ForeColor = System.Drawing.Color.Gold;
            this.checkBoxCAI.Name = "checkBoxCAI";
            this.checkBoxCAI.UseVisualStyleBackColor = true;
            this.checkBoxCAI.Click += new System.EventHandler(this.checkBoxCSolo_Click);
            // 
            // checkBoxC2
            // 
            resources.ApplyResources(this.checkBoxC2, "checkBoxC2");
            this.checkBoxC2.FlatAppearance.BorderSize = 0;
            this.checkBoxC2.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.checkBoxC2.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.checkBoxC2.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.checkBoxC2.ForeColor = System.Drawing.Color.Gold;
            this.checkBoxC2.Name = "checkBoxC2";
            this.checkBoxC2.UseVisualStyleBackColor = true;
            this.checkBoxC2.Click += new System.EventHandler(this.checkBoxCSolo_Click);
            // 
            // checkBoxCSolo
            // 
            resources.ApplyResources(this.checkBoxCSolo, "checkBoxCSolo");
            this.checkBoxCSolo.Checked = true;
            this.checkBoxCSolo.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxCSolo.FlatAppearance.BorderSize = 0;
            this.checkBoxCSolo.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.checkBoxCSolo.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.checkBoxCSolo.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.checkBoxCSolo.ForeColor = System.Drawing.Color.Gold;
            this.checkBoxCSolo.Name = "checkBoxCSolo";
            this.checkBoxCSolo.UseVisualStyleBackColor = true;
            this.checkBoxCSolo.Click += new System.EventHandler(this.checkBoxCSolo_Click);
            // 
            // CampaignPlayerTypeLabel
            // 
            resources.ApplyResources(this.CampaignPlayerTypeLabel, "CampaignPlayerTypeLabel");
            this.CampaignPlayerTypeLabel.ForeColor = System.Drawing.Color.Gold;
            this.CampaignPlayerTypeLabel.Name = "CampaignPlayerTypeLabel";
            // 
            // campaignCancelBtn
            // 
            resources.ApplyResources(this.campaignCancelBtn, "campaignCancelBtn");
            this.campaignCancelBtn.FlatAppearance.BorderSize = 0;
            this.campaignCancelBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.campaignCancelBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.campaignCancelBtn.ForeColor = System.Drawing.Color.Gold;
            this.campaignCancelBtn.Name = "campaignCancelBtn";
            this.campaignCancelBtn.UseVisualStyleBackColor = true;
            this.campaignCancelBtn.Click += new System.EventHandler(this.campaignCancelBtn_Click);
            this.campaignCancelBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.campaignCancelBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.campaignCancelBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.campaignCancelBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // CampaignZonesListView
            // 
            this.CampaignZonesListView.BackColor = System.Drawing.SystemColors.InfoText;
            this.CampaignZonesListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader3,
            this.columnHeader4});
            this.CampaignZonesListView.ForeColor = System.Drawing.Color.Red;
            this.CampaignZonesListView.FullRowSelect = true;
            this.CampaignZonesListView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            resources.ApplyResources(this.CampaignZonesListView, "CampaignZonesListView");
            this.CampaignZonesListView.MultiSelect = false;
            this.CampaignZonesListView.Name = "CampaignZonesListView";
            this.CampaignZonesListView.UseCompatibleStateImageBehavior = false;
            this.CampaignZonesListView.View = System.Windows.Forms.View.Details;
            this.CampaignZonesListView.SelectedIndexChanged += new System.EventHandler(this.CampaignZonesListView_SelectedIndexChanged);
            // 
            // columnHeader3
            // 
            resources.ApplyResources(this.columnHeader3, "columnHeader3");
            // 
            // columnHeader4
            // 
            resources.ApplyResources(this.columnHeader4, "columnHeader4");
            // 
            // CampaignScreenShotBox
            // 
            this.CampaignScreenShotBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            resources.ApplyResources(this.CampaignScreenShotBox, "CampaignScreenShotBox");
            this.CampaignScreenShotBox.Name = "CampaignScreenShotBox";
            this.CampaignScreenShotBox.TabStop = false;
            // 
            // campaignStartBtn
            // 
            resources.ApplyResources(this.campaignStartBtn, "campaignStartBtn");
            this.campaignStartBtn.FlatAppearance.BorderSize = 0;
            this.campaignStartBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.campaignStartBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.campaignStartBtn.ForeColor = System.Drawing.Color.Gold;
            this.campaignStartBtn.Name = "campaignStartBtn";
            this.campaignStartBtn.UseVisualStyleBackColor = true;
            this.campaignStartBtn.Click += new System.EventHandler(this.campaignStartBtn_Click);
            this.campaignStartBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.campaignStartBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.campaignStartBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.campaignStartBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // CampaignZonesLabel
            // 
            resources.ApplyResources(this.CampaignZonesLabel, "CampaignZonesLabel");
            this.CampaignZonesLabel.ForeColor = System.Drawing.Color.Gold;
            this.CampaignZonesLabel.Name = "CampaignZonesLabel";
            // 
            // QuickGameTab
            // 
            this.QuickGameTab.Controls.Add(this.QGamePanel);
            resources.ApplyResources(this.QuickGameTab, "QuickGameTab");
            this.QuickGameTab.Name = "QuickGameTab";
            this.QuickGameTab.UseVisualStyleBackColor = true;
            // 
            // QGamePanel
            // 
            resources.ApplyResources(this.QGamePanel, "QGamePanel");
            this.QGamePanel.Controls.Add(this.timeLimitLabel);
            this.QGamePanel.Controls.Add(this.plusBtn);
            this.QGamePanel.Controls.Add(this.minusBtn);
            this.QGamePanel.Controls.Add(this.timeLabel);
            this.QGamePanel.Controls.Add(this.timeAttackLabel);
            this.QGamePanel.Controls.Add(this.timeAttackCBox);
            this.QGamePanel.Controls.Add(this.instaDeathLabel);
            this.QGamePanel.Controls.Add(this.instaDeathCBox);
            this.QGamePanel.Controls.Add(this.PlayerTimePanel);
            this.QGamePanel.Controls.Add(this.bouton_Cancel);
            this.QGamePanel.Controls.Add(this.ZonesDisponibles);
            this.QGamePanel.Controls.Add(this.screenShot);
            this.QGamePanel.Controls.Add(this.bouton_OK);
            this.QGamePanel.Controls.Add(this.label_ZJDisp);
            this.QGamePanel.Name = "QGamePanel";
            // 
            // timeLimitLabel
            // 
            resources.ApplyResources(this.timeLimitLabel, "timeLimitLabel");
            this.timeLimitLabel.ForeColor = System.Drawing.Color.Gold;
            this.timeLimitLabel.Name = "timeLimitLabel";
            // 
            // plusBtn
            // 
            resources.ApplyResources(this.plusBtn, "plusBtn");
            this.plusBtn.FlatAppearance.BorderSize = 0;
            this.plusBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.plusBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.plusBtn.ForeColor = System.Drawing.Color.Gold;
            this.plusBtn.Name = "plusBtn";
            this.plusBtn.UseVisualStyleBackColor = true;
            this.plusBtn.Click += new System.EventHandler(this.plusBtn_Click);
            this.plusBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.plusBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.plusBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.plusBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // minusBtn
            // 
            resources.ApplyResources(this.minusBtn, "minusBtn");
            this.minusBtn.FlatAppearance.BorderSize = 0;
            this.minusBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.minusBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.minusBtn.ForeColor = System.Drawing.Color.Gold;
            this.minusBtn.Name = "minusBtn";
            this.minusBtn.UseVisualStyleBackColor = true;
            this.minusBtn.Click += new System.EventHandler(this.minusBtn_Click);
            this.minusBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.minusBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.minusBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.minusBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // timeLabel
            // 
            resources.ApplyResources(this.timeLabel, "timeLabel");
            this.timeLabel.ForeColor = System.Drawing.Color.Gold;
            this.timeLabel.Name = "timeLabel";
            // 
            // timeAttackLabel
            // 
            resources.ApplyResources(this.timeAttackLabel, "timeAttackLabel");
            this.timeAttackLabel.ForeColor = System.Drawing.Color.Gold;
            this.timeAttackLabel.Name = "timeAttackLabel";
            // 
            // timeAttackCBox
            // 
            resources.ApplyResources(this.timeAttackCBox, "timeAttackCBox");
            this.timeAttackCBox.BackgroundImage = global::InterfaceGraphique.Properties.Resources.borderStock;
            this.timeAttackCBox.FlatAppearance.BorderSize = 0;
            this.timeAttackCBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.timeAttackCBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.timeAttackCBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.timeAttackCBox.ForeColor = System.Drawing.Color.Gold;
            this.timeAttackCBox.Name = "timeAttackCBox";
            this.timeAttackCBox.UseVisualStyleBackColor = true;
            this.timeAttackCBox.CheckedChanged += new System.EventHandler(this.timeAttackCBox_CheckedChanged);
            // 
            // instaDeathLabel
            // 
            resources.ApplyResources(this.instaDeathLabel, "instaDeathLabel");
            this.instaDeathLabel.ForeColor = System.Drawing.Color.Gold;
            this.instaDeathLabel.Name = "instaDeathLabel";
            // 
            // instaDeathCBox
            // 
            resources.ApplyResources(this.instaDeathCBox, "instaDeathCBox");
            this.instaDeathCBox.BackgroundImage = global::InterfaceGraphique.Properties.Resources.borderStock;
            this.instaDeathCBox.FlatAppearance.BorderSize = 0;
            this.instaDeathCBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.instaDeathCBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.instaDeathCBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.instaDeathCBox.ForeColor = System.Drawing.Color.Gold;
            this.instaDeathCBox.Name = "instaDeathCBox";
            this.instaDeathCBox.UseVisualStyleBackColor = true;
            this.instaDeathCBox.CheckedChanged += new System.EventHandler(this.instaDeathCBox_CheckedChanged);
            // 
            // PlayerTimePanel
            // 
            this.PlayerTimePanel.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.PlayerTimePanel, "PlayerTimePanel");
            this.PlayerTimePanel.Controls.Add(this.checkBoxAI);
            this.PlayerTimePanel.Controls.Add(this.checkBox2Player);
            this.PlayerTimePanel.Controls.Add(this.checkBoxSolo);
            this.PlayerTimePanel.Controls.Add(this.PlayerTypeLabel);
            this.PlayerTimePanel.Name = "PlayerTimePanel";
            // 
            // checkBoxAI
            // 
            resources.ApplyResources(this.checkBoxAI, "checkBoxAI");
            this.checkBoxAI.FlatAppearance.BorderSize = 0;
            this.checkBoxAI.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.checkBoxAI.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.checkBoxAI.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.checkBoxAI.ForeColor = System.Drawing.Color.Gold;
            this.checkBoxAI.Name = "checkBoxAI";
            this.checkBoxAI.UseVisualStyleBackColor = true;
            this.checkBoxAI.Click += new System.EventHandler(this.PlayerTimeChanged);
            // 
            // checkBox2Player
            // 
            resources.ApplyResources(this.checkBox2Player, "checkBox2Player");
            this.checkBox2Player.FlatAppearance.BorderSize = 0;
            this.checkBox2Player.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.checkBox2Player.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.checkBox2Player.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.checkBox2Player.ForeColor = System.Drawing.Color.Gold;
            this.checkBox2Player.Name = "checkBox2Player";
            this.checkBox2Player.UseVisualStyleBackColor = true;
            this.checkBox2Player.Click += new System.EventHandler(this.PlayerTimeChanged);
            // 
            // checkBoxSolo
            // 
            resources.ApplyResources(this.checkBoxSolo, "checkBoxSolo");
            this.checkBoxSolo.Checked = true;
            this.checkBoxSolo.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxSolo.FlatAppearance.BorderSize = 0;
            this.checkBoxSolo.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.checkBoxSolo.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.checkBoxSolo.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.checkBoxSolo.ForeColor = System.Drawing.Color.Gold;
            this.checkBoxSolo.Name = "checkBoxSolo";
            this.checkBoxSolo.UseVisualStyleBackColor = true;
            this.checkBoxSolo.Click += new System.EventHandler(this.PlayerTimeChanged);
            // 
            // PlayerTypeLabel
            // 
            resources.ApplyResources(this.PlayerTypeLabel, "PlayerTypeLabel");
            this.PlayerTypeLabel.ForeColor = System.Drawing.Color.Gold;
            this.PlayerTypeLabel.Name = "PlayerTypeLabel";
            // 
            // bouton_Cancel
            // 
            resources.ApplyResources(this.bouton_Cancel, "bouton_Cancel");
            this.bouton_Cancel.FlatAppearance.BorderSize = 0;
            this.bouton_Cancel.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.bouton_Cancel.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.bouton_Cancel.ForeColor = System.Drawing.Color.Gold;
            this.bouton_Cancel.Name = "bouton_Cancel";
            this.bouton_Cancel.UseVisualStyleBackColor = true;
            this.bouton_Cancel.Click += new System.EventHandler(this.bouton_Cancel_Click);
            this.bouton_Cancel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.bouton_Cancel.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.bouton_Cancel.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.bouton_Cancel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // ZonesDisponibles
            // 
            this.ZonesDisponibles.BackColor = System.Drawing.SystemColors.InfoText;
            this.ZonesDisponibles.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1,
            this.columnHeader2});
            this.ZonesDisponibles.ForeColor = System.Drawing.Color.Red;
            this.ZonesDisponibles.FullRowSelect = true;
            this.ZonesDisponibles.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            resources.ApplyResources(this.ZonesDisponibles, "ZonesDisponibles");
            this.ZonesDisponibles.MultiSelect = false;
            this.ZonesDisponibles.Name = "ZonesDisponibles";
            this.ZonesDisponibles.UseCompatibleStateImageBehavior = false;
            this.ZonesDisponibles.View = System.Windows.Forms.View.Details;
            this.ZonesDisponibles.SelectedIndexChanged += new System.EventHandler(this.ZonesDisponibles_SelectedIndexChanged);
            // 
            // columnHeader1
            // 
            resources.ApplyResources(this.columnHeader1, "columnHeader1");
            // 
            // columnHeader2
            // 
            resources.ApplyResources(this.columnHeader2, "columnHeader2");
            // 
            // screenShot
            // 
            this.screenShot.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            resources.ApplyResources(this.screenShot, "screenShot");
            this.screenShot.Name = "screenShot";
            this.screenShot.TabStop = false;
            // 
            // bouton_OK
            // 
            resources.ApplyResources(this.bouton_OK, "bouton_OK");
            this.bouton_OK.FlatAppearance.BorderSize = 0;
            this.bouton_OK.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.bouton_OK.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.bouton_OK.ForeColor = System.Drawing.Color.Gold;
            this.bouton_OK.Name = "bouton_OK";
            this.bouton_OK.UseVisualStyleBackColor = true;
            this.bouton_OK.Click += new System.EventHandler(this.bouton_OK_Click);
            this.bouton_OK.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.bouton_OK.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.bouton_OK.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.bouton_OK.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // label_ZJDisp
            // 
            resources.ApplyResources(this.label_ZJDisp, "label_ZJDisp");
            this.label_ZJDisp.ForeColor = System.Drawing.Color.Gold;
            this.label_ZJDisp.Name = "label_ZJDisp";
            // 
            // LobbyTab
            // 
            this.LobbyTab.Controls.Add(this.GameTutoPanel);
            this.LobbyTab.Controls.Add(this.MPCreatePanel);
            resources.ApplyResources(this.LobbyTab, "LobbyTab");
            this.LobbyTab.Name = "LobbyTab";
            this.LobbyTab.UseVisualStyleBackColor = true;
            // 
            // GameTutoPanel
            // 
            this.GameTutoPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(35)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.GameTutoPanel.Controls.Add(this.GameTutoNext);
            this.GameTutoPanel.Controls.Add(this.GameTutoCancel);
            this.GameTutoPanel.Controls.Add(this.GameTutoLabel);
            resources.ApplyResources(this.GameTutoPanel, "GameTutoPanel");
            this.GameTutoPanel.Name = "GameTutoPanel";
            // 
            // GameTutoNext
            // 
            resources.ApplyResources(this.GameTutoNext, "GameTutoNext");
            this.GameTutoNext.FlatAppearance.BorderSize = 0;
            this.GameTutoNext.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.GameTutoNext.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.GameTutoNext.ForeColor = System.Drawing.Color.Gold;
            this.GameTutoNext.Name = "GameTutoNext";
            this.GameTutoNext.UseVisualStyleBackColor = true;
            this.GameTutoNext.Click += new System.EventHandler(this.GameTutoNext_Click);
            this.GameTutoNext.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.GameTutoNext.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.GameTutoNext.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.GameTutoNext.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // GameTutoCancel
            // 
            resources.ApplyResources(this.GameTutoCancel, "GameTutoCancel");
            this.GameTutoCancel.FlatAppearance.BorderSize = 0;
            this.GameTutoCancel.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.GameTutoCancel.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.GameTutoCancel.ForeColor = System.Drawing.Color.Gold;
            this.GameTutoCancel.Name = "GameTutoCancel";
            this.GameTutoCancel.UseVisualStyleBackColor = true;
            this.GameTutoCancel.Click += new System.EventHandler(this.GameTutoCancel_Click);
            this.GameTutoCancel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.GameTutoCancel.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.GameTutoCancel.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.GameTutoCancel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // GameTutoLabel
            // 
            resources.ApplyResources(this.GameTutoLabel, "GameTutoLabel");
            this.GameTutoLabel.ForeColor = System.Drawing.Color.Gold;
            this.GameTutoLabel.Name = "GameTutoLabel";
            // 
            // MPCreatePanel
            // 
            resources.ApplyResources(this.MPCreatePanel, "MPCreatePanel");
            this.MPCreatePanel.Controls.Add(this.PlayerTitleLabel);
            this.MPCreatePanel.Controls.Add(this.EmptyMPGameBtn);
            this.MPCreatePanel.Controls.Add(this.RemoveMPGameBtn);
            this.MPCreatePanel.Controls.Add(this.AddMPGameBtn);
            this.MPCreatePanel.Controls.Add(this.ChosenGamesLabel);
            this.MPCreatePanel.Controls.Add(this.MPGameSelected);
            this.MPCreatePanel.Controls.Add(this.MPCreateGModeLabel);
            this.MPCreatePanel.Controls.Add(this.MPCreateGModeCBox);
            this.MPCreatePanel.Controls.Add(this.joinedPlayerView);
            this.MPCreatePanel.Controls.Add(this.MPTimeLimitLabel);
            this.MPCreatePanel.Controls.Add(this.MPCreatePlusBtn);
            this.MPCreatePanel.Controls.Add(this.MPCreateMinus);
            this.MPCreatePanel.Controls.Add(this.MPtimeLabel);
            this.MPCreatePanel.Controls.Add(this.MPTimerLabel);
            this.MPCreatePanel.Controls.Add(this.MPCreateCBoxTime);
            this.MPCreatePanel.Controls.Add(this.MpInstaDeathLabel);
            this.MPCreatePanel.Controls.Add(this.MPCreateCBoxID);
            this.MPCreatePanel.Controls.Add(this.MPInfoPanel);
            this.MPCreatePanel.Controls.Add(this.MPCreateCancelBtn);
            this.MPCreatePanel.Controls.Add(this.MPZonesDisponibles);
            this.MPCreatePanel.Controls.Add(this.MPScreenShot);
            this.MPCreatePanel.Controls.Add(this.MPCreateStartBtn);
            this.MPCreatePanel.Controls.Add(this.MPZonesDisponiblesLabel);
            this.MPCreatePanel.Name = "MPCreatePanel";
            // 
            // PlayerTitleLabel
            // 
            resources.ApplyResources(this.PlayerTitleLabel, "PlayerTitleLabel");
            this.PlayerTitleLabel.ForeColor = System.Drawing.Color.Gold;
            this.PlayerTitleLabel.Name = "PlayerTitleLabel";
            // 
            // EmptyMPGameBtn
            // 
            resources.ApplyResources(this.EmptyMPGameBtn, "EmptyMPGameBtn");
            this.EmptyMPGameBtn.FlatAppearance.BorderSize = 0;
            this.EmptyMPGameBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.EmptyMPGameBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.EmptyMPGameBtn.ForeColor = System.Drawing.Color.Gold;
            this.EmptyMPGameBtn.Name = "EmptyMPGameBtn";
            this.EmptyMPGameBtn.UseVisualStyleBackColor = true;
            this.EmptyMPGameBtn.Click += new System.EventHandler(this.EmptyMPGameBtn_Click);
            this.EmptyMPGameBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.EmptyMPGameBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.EmptyMPGameBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.EmptyMPGameBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // RemoveMPGameBtn
            // 
            resources.ApplyResources(this.RemoveMPGameBtn, "RemoveMPGameBtn");
            this.RemoveMPGameBtn.FlatAppearance.BorderSize = 0;
            this.RemoveMPGameBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.RemoveMPGameBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.RemoveMPGameBtn.ForeColor = System.Drawing.Color.Gold;
            this.RemoveMPGameBtn.Name = "RemoveMPGameBtn";
            this.RemoveMPGameBtn.UseVisualStyleBackColor = true;
            this.RemoveMPGameBtn.Click += new System.EventHandler(this.RemoveMPGameBtn_Click);
            this.RemoveMPGameBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.RemoveMPGameBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.RemoveMPGameBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.RemoveMPGameBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // AddMPGameBtn
            // 
            resources.ApplyResources(this.AddMPGameBtn, "AddMPGameBtn");
            this.AddMPGameBtn.FlatAppearance.BorderSize = 0;
            this.AddMPGameBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.AddMPGameBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.AddMPGameBtn.ForeColor = System.Drawing.Color.Gold;
            this.AddMPGameBtn.Name = "AddMPGameBtn";
            this.AddMPGameBtn.UseVisualStyleBackColor = true;
            this.AddMPGameBtn.Click += new System.EventHandler(this.AddMPGameBtn_Click);
            this.AddMPGameBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.AddMPGameBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.AddMPGameBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.AddMPGameBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // ChosenGamesLabel
            // 
            resources.ApplyResources(this.ChosenGamesLabel, "ChosenGamesLabel");
            this.ChosenGamesLabel.ForeColor = System.Drawing.Color.Gold;
            this.ChosenGamesLabel.Name = "ChosenGamesLabel";
            // 
            // MPGameSelected
            // 
            this.MPGameSelected.BackColor = System.Drawing.SystemColors.InfoText;
            this.MPGameSelected.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.MPGameSelected.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader11,
            this.columnHeader12});
            this.MPGameSelected.ForeColor = System.Drawing.Color.Red;
            this.MPGameSelected.FullRowSelect = true;
            this.MPGameSelected.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            resources.ApplyResources(this.MPGameSelected, "MPGameSelected");
            this.MPGameSelected.Name = "MPGameSelected";
            this.MPGameSelected.UseCompatibleStateImageBehavior = false;
            this.MPGameSelected.View = System.Windows.Forms.View.Details;
            this.MPGameSelected.SelectedIndexChanged += new System.EventHandler(this.MPGameSelected_SelectedIndexChanged);
            // 
            // columnHeader11
            // 
            resources.ApplyResources(this.columnHeader11, "columnHeader11");
            // 
            // columnHeader12
            // 
            resources.ApplyResources(this.columnHeader12, "columnHeader12");
            // 
            // MPCreateGModeLabel
            // 
            resources.ApplyResources(this.MPCreateGModeLabel, "MPCreateGModeLabel");
            this.MPCreateGModeLabel.ForeColor = System.Drawing.Color.Gold;
            this.MPCreateGModeLabel.Name = "MPCreateGModeLabel";
            // 
            // MPCreateGModeCBox
            // 
            resources.ApplyResources(this.MPCreateGModeCBox, "MPCreateGModeCBox");
            this.MPCreateGModeCBox.BackgroundImage = global::InterfaceGraphique.Properties.Resources.borderStock;
            this.MPCreateGModeCBox.FlatAppearance.BorderSize = 0;
            this.MPCreateGModeCBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.MPCreateGModeCBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MPCreateGModeCBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MPCreateGModeCBox.ForeColor = System.Drawing.Color.Gold;
            this.MPCreateGModeCBox.Name = "MPCreateGModeCBox";
            this.MPCreateGModeCBox.UseVisualStyleBackColor = true;
            this.MPCreateGModeCBox.CheckedChanged += new System.EventHandler(this.MPCreateGModeCBox_CheckedChanged);
            // 
            // joinedPlayerView
            // 
            this.joinedPlayerView.BackColor = System.Drawing.SystemColors.InfoText;
            this.joinedPlayerView.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.joinedPlayerView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader9,
            this.columnHeader10});
            this.joinedPlayerView.ForeColor = System.Drawing.Color.Red;
            this.joinedPlayerView.FullRowSelect = true;
            this.joinedPlayerView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            resources.ApplyResources(this.joinedPlayerView, "joinedPlayerView");
            this.joinedPlayerView.MultiSelect = false;
            this.joinedPlayerView.Name = "joinedPlayerView";
            this.joinedPlayerView.UseCompatibleStateImageBehavior = false;
            this.joinedPlayerView.View = System.Windows.Forms.View.Details;
            this.joinedPlayerView.ItemSelectionChanged += new System.Windows.Forms.ListViewItemSelectionChangedEventHandler(this.joinedPlayerView_ItemSelectionChanged);
            // 
            // columnHeader9
            // 
            resources.ApplyResources(this.columnHeader9, "columnHeader9");
            // 
            // columnHeader10
            // 
            resources.ApplyResources(this.columnHeader10, "columnHeader10");
            // 
            // MPTimeLimitLabel
            // 
            resources.ApplyResources(this.MPTimeLimitLabel, "MPTimeLimitLabel");
            this.MPTimeLimitLabel.ForeColor = System.Drawing.Color.Gold;
            this.MPTimeLimitLabel.Name = "MPTimeLimitLabel";
            // 
            // MPCreatePlusBtn
            // 
            resources.ApplyResources(this.MPCreatePlusBtn, "MPCreatePlusBtn");
            this.MPCreatePlusBtn.FlatAppearance.BorderSize = 0;
            this.MPCreatePlusBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MPCreatePlusBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MPCreatePlusBtn.ForeColor = System.Drawing.Color.Gold;
            this.MPCreatePlusBtn.Name = "MPCreatePlusBtn";
            this.MPCreatePlusBtn.UseVisualStyleBackColor = true;
            this.MPCreatePlusBtn.Click += new System.EventHandler(this.MPCreatePlusBtn_Click);
            this.MPCreatePlusBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MPCreatePlusBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MPCreatePlusBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MPCreatePlusBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MPCreateMinus
            // 
            resources.ApplyResources(this.MPCreateMinus, "MPCreateMinus");
            this.MPCreateMinus.FlatAppearance.BorderSize = 0;
            this.MPCreateMinus.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MPCreateMinus.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MPCreateMinus.ForeColor = System.Drawing.Color.Gold;
            this.MPCreateMinus.Name = "MPCreateMinus";
            this.MPCreateMinus.UseVisualStyleBackColor = true;
            this.MPCreateMinus.Click += new System.EventHandler(this.MPCreateMinus_Click);
            this.MPCreateMinus.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MPCreateMinus.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MPCreateMinus.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MPCreateMinus.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MPtimeLabel
            // 
            resources.ApplyResources(this.MPtimeLabel, "MPtimeLabel");
            this.MPtimeLabel.ForeColor = System.Drawing.Color.Gold;
            this.MPtimeLabel.Name = "MPtimeLabel";
            // 
            // MPTimerLabel
            // 
            resources.ApplyResources(this.MPTimerLabel, "MPTimerLabel");
            this.MPTimerLabel.ForeColor = System.Drawing.Color.Gold;
            this.MPTimerLabel.Name = "MPTimerLabel";
            // 
            // MPCreateCBoxTime
            // 
            resources.ApplyResources(this.MPCreateCBoxTime, "MPCreateCBoxTime");
            this.MPCreateCBoxTime.BackgroundImage = global::InterfaceGraphique.Properties.Resources.borderStock;
            this.MPCreateCBoxTime.FlatAppearance.BorderSize = 0;
            this.MPCreateCBoxTime.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.MPCreateCBoxTime.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MPCreateCBoxTime.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MPCreateCBoxTime.ForeColor = System.Drawing.Color.Gold;
            this.MPCreateCBoxTime.Name = "MPCreateCBoxTime";
            this.MPCreateCBoxTime.UseVisualStyleBackColor = true;
            this.MPCreateCBoxTime.CheckedChanged += new System.EventHandler(this.MPCreateCBoxTime_CheckedChanged);
            // 
            // MpInstaDeathLabel
            // 
            resources.ApplyResources(this.MpInstaDeathLabel, "MpInstaDeathLabel");
            this.MpInstaDeathLabel.ForeColor = System.Drawing.Color.Gold;
            this.MpInstaDeathLabel.Name = "MpInstaDeathLabel";
            // 
            // MPCreateCBoxID
            // 
            resources.ApplyResources(this.MPCreateCBoxID, "MPCreateCBoxID");
            this.MPCreateCBoxID.BackgroundImage = global::InterfaceGraphique.Properties.Resources.borderStock;
            this.MPCreateCBoxID.FlatAppearance.BorderSize = 0;
            this.MPCreateCBoxID.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.MPCreateCBoxID.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MPCreateCBoxID.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MPCreateCBoxID.ForeColor = System.Drawing.Color.Gold;
            this.MPCreateCBoxID.Name = "MPCreateCBoxID";
            this.MPCreateCBoxID.UseVisualStyleBackColor = true;
            this.MPCreateCBoxID.CheckedChanged += new System.EventHandler(this.MPCreateCBoxID_CheckedChanged);
            // 
            // MPInfoPanel
            // 
            this.MPInfoPanel.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.MPInfoPanel, "MPInfoPanel");
            this.MPInfoPanel.Controls.Add(this.MPCreateRoomBtn);
            this.MPInfoPanel.Controls.Add(this.MPPasswordTBox);
            this.MPInfoPanel.Controls.Add(this.MPPasswordLabel);
            this.MPInfoPanel.Name = "MPInfoPanel";
            // 
            // MPCreateRoomBtn
            // 
            resources.ApplyResources(this.MPCreateRoomBtn, "MPCreateRoomBtn");
            this.MPCreateRoomBtn.FlatAppearance.BorderSize = 0;
            this.MPCreateRoomBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MPCreateRoomBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MPCreateRoomBtn.ForeColor = System.Drawing.Color.Gold;
            this.MPCreateRoomBtn.Name = "MPCreateRoomBtn";
            this.MPCreateRoomBtn.UseVisualStyleBackColor = true;
            this.MPCreateRoomBtn.Click += new System.EventHandler(this.MPCreateRoomBtn_Click);
            this.MPCreateRoomBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MPCreateRoomBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MPCreateRoomBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MPCreateRoomBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MPPasswordTBox
            // 
            this.MPPasswordTBox.BackColor = System.Drawing.SystemColors.InfoText;
            this.MPPasswordTBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            resources.ApplyResources(this.MPPasswordTBox, "MPPasswordTBox");
            this.MPPasswordTBox.ForeColor = System.Drawing.Color.Red;
            this.MPPasswordTBox.Name = "MPPasswordTBox";
            // 
            // MPPasswordLabel
            // 
            resources.ApplyResources(this.MPPasswordLabel, "MPPasswordLabel");
            this.MPPasswordLabel.ForeColor = System.Drawing.Color.Gold;
            this.MPPasswordLabel.Name = "MPPasswordLabel";
            // 
            // MPCreateCancelBtn
            // 
            resources.ApplyResources(this.MPCreateCancelBtn, "MPCreateCancelBtn");
            this.MPCreateCancelBtn.FlatAppearance.BorderSize = 0;
            this.MPCreateCancelBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MPCreateCancelBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MPCreateCancelBtn.ForeColor = System.Drawing.Color.Gold;
            this.MPCreateCancelBtn.Name = "MPCreateCancelBtn";
            this.MPCreateCancelBtn.UseVisualStyleBackColor = true;
            this.MPCreateCancelBtn.Click += new System.EventHandler(this.MPCreateCancelBtn_Click);
            this.MPCreateCancelBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MPCreateCancelBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MPCreateCancelBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MPCreateCancelBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MPZonesDisponibles
            // 
            this.MPZonesDisponibles.BackColor = System.Drawing.SystemColors.InfoText;
            this.MPZonesDisponibles.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.MPZonesDisponibles.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader7,
            this.columnHeader8});
            this.MPZonesDisponibles.ForeColor = System.Drawing.Color.Red;
            this.MPZonesDisponibles.FullRowSelect = true;
            this.MPZonesDisponibles.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            resources.ApplyResources(this.MPZonesDisponibles, "MPZonesDisponibles");
            this.MPZonesDisponibles.MultiSelect = false;
            this.MPZonesDisponibles.Name = "MPZonesDisponibles";
            this.MPZonesDisponibles.UseCompatibleStateImageBehavior = false;
            this.MPZonesDisponibles.View = System.Windows.Forms.View.Details;
            this.MPZonesDisponibles.SelectedIndexChanged += new System.EventHandler(this.MPZonesDisponibles_SelectedIndexChanged);
            // 
            // columnHeader7
            // 
            resources.ApplyResources(this.columnHeader7, "columnHeader7");
            // 
            // columnHeader8
            // 
            resources.ApplyResources(this.columnHeader8, "columnHeader8");
            // 
            // MPScreenShot
            // 
            resources.ApplyResources(this.MPScreenShot, "MPScreenShot");
            this.MPScreenShot.Name = "MPScreenShot";
            this.MPScreenShot.TabStop = false;
            // 
            // MPCreateStartBtn
            // 
            resources.ApplyResources(this.MPCreateStartBtn, "MPCreateStartBtn");
            this.MPCreateStartBtn.FlatAppearance.BorderSize = 0;
            this.MPCreateStartBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MPCreateStartBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MPCreateStartBtn.ForeColor = System.Drawing.Color.Gold;
            this.MPCreateStartBtn.Name = "MPCreateStartBtn";
            this.MPCreateStartBtn.UseVisualStyleBackColor = true;
            this.MPCreateStartBtn.Click += new System.EventHandler(this.MPCreateStartBtn_Click);
            this.MPCreateStartBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MPCreateStartBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MPCreateStartBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MPCreateStartBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MPZonesDisponiblesLabel
            // 
            resources.ApplyResources(this.MPZonesDisponiblesLabel, "MPZonesDisponiblesLabel");
            this.MPZonesDisponiblesLabel.ForeColor = System.Drawing.Color.Gold;
            this.MPZonesDisponiblesLabel.Name = "MPZonesDisponiblesLabel";
            // 
            // MPGameSelectTab
            // 
            this.MPGameSelectTab.Controls.Add(this.MPJoinGameSelectPanel);
            this.MPGameSelectTab.Controls.Add(this.MPJoinPanel);
            resources.ApplyResources(this.MPGameSelectTab, "MPGameSelectTab");
            this.MPGameSelectTab.Name = "MPGameSelectTab";
            this.MPGameSelectTab.UseVisualStyleBackColor = true;
            // 
            // MPJoinGameSelectPanel
            // 
            resources.ApplyResources(this.MPJoinGameSelectPanel, "MPJoinGameSelectPanel");
            this.MPJoinGameSelectPanel.Controls.Add(this.MPJoinErrorLabel);
            this.MPJoinGameSelectPanel.Controls.Add(this.MPJoinPasswordTBox);
            this.MPJoinGameSelectPanel.Controls.Add(this.MPJoinPasswordLabel);
            this.MPJoinGameSelectPanel.Controls.Add(this.RefreshBtn);
            this.MPJoinGameSelectPanel.Controls.Add(this.MPJoinGameView);
            this.MPJoinGameSelectPanel.Controls.Add(this.panel2);
            this.MPJoinGameSelectPanel.Controls.Add(this.MPJoinReturnBtn);
            this.MPJoinGameSelectPanel.Controls.Add(this.MPJoinSelectBtn);
            this.MPJoinGameSelectPanel.Name = "MPJoinGameSelectPanel";
            // 
            // MPJoinErrorLabel
            // 
            resources.ApplyResources(this.MPJoinErrorLabel, "MPJoinErrorLabel");
            this.MPJoinErrorLabel.ForeColor = System.Drawing.Color.Chartreuse;
            this.MPJoinErrorLabel.Name = "MPJoinErrorLabel";
            // 
            // MPJoinPasswordTBox
            // 
            this.MPJoinPasswordTBox.BackColor = System.Drawing.SystemColors.InfoText;
            this.MPJoinPasswordTBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.MPJoinPasswordTBox.ForeColor = System.Drawing.Color.Gold;
            resources.ApplyResources(this.MPJoinPasswordTBox, "MPJoinPasswordTBox");
            this.MPJoinPasswordTBox.Name = "MPJoinPasswordTBox";
            // 
            // MPJoinPasswordLabel
            // 
            resources.ApplyResources(this.MPJoinPasswordLabel, "MPJoinPasswordLabel");
            this.MPJoinPasswordLabel.ForeColor = System.Drawing.Color.Gold;
            this.MPJoinPasswordLabel.Name = "MPJoinPasswordLabel";
            // 
            // RefreshBtn
            // 
            resources.ApplyResources(this.RefreshBtn, "RefreshBtn");
            this.RefreshBtn.FlatAppearance.BorderSize = 0;
            this.RefreshBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.RefreshBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.RefreshBtn.ForeColor = System.Drawing.Color.Gold;
            this.RefreshBtn.Name = "RefreshBtn";
            this.RefreshBtn.UseVisualStyleBackColor = true;
            this.RefreshBtn.Click += new System.EventHandler(this.RefreshBtn_Click);
            this.RefreshBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.RefreshBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.RefreshBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.RefreshBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MPJoinGameView
            // 
            this.MPJoinGameView.BackColor = System.Drawing.SystemColors.InfoText;
            this.MPJoinGameView.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.MPJoinGameView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.HostName,
            this.MapName,
            this.gameType,
            this.LobbyOrGame,
            this.hiddenGames});
            this.MPJoinGameView.ForeColor = System.Drawing.Color.Red;
            this.MPJoinGameView.FullRowSelect = true;
            this.MPJoinGameView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            this.MPJoinGameView.HideSelection = false;
            resources.ApplyResources(this.MPJoinGameView, "MPJoinGameView");
            this.MPJoinGameView.MultiSelect = false;
            this.MPJoinGameView.Name = "MPJoinGameView";
            this.MPJoinGameView.UseCompatibleStateImageBehavior = false;
            this.MPJoinGameView.View = System.Windows.Forms.View.Details;
            this.MPJoinGameView.ItemSelectionChanged += new System.Windows.Forms.ListViewItemSelectionChangedEventHandler(this.MPJoinGameView_ItemSelectionChanged);
            // 
            // HostName
            // 
            resources.ApplyResources(this.HostName, "HostName");
            // 
            // MapName
            // 
            resources.ApplyResources(this.MapName, "MapName");
            // 
            // gameType
            // 
            resources.ApplyResources(this.gameType, "gameType");
            // 
            // LobbyOrGame
            // 
            resources.ApplyResources(this.LobbyOrGame, "LobbyOrGame");
            // 
            // hiddenGames
            // 
            resources.ApplyResources(this.hiddenGames, "hiddenGames");
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.panel2, "panel2");
            this.panel2.Controls.Add(this.MPJoinAvailableGamesLabel);
            this.panel2.Name = "panel2";
            // 
            // MPJoinAvailableGamesLabel
            // 
            resources.ApplyResources(this.MPJoinAvailableGamesLabel, "MPJoinAvailableGamesLabel");
            this.MPJoinAvailableGamesLabel.ForeColor = System.Drawing.Color.Gold;
            this.MPJoinAvailableGamesLabel.Name = "MPJoinAvailableGamesLabel";
            // 
            // MPJoinReturnBtn
            // 
            resources.ApplyResources(this.MPJoinReturnBtn, "MPJoinReturnBtn");
            this.MPJoinReturnBtn.FlatAppearance.BorderSize = 0;
            this.MPJoinReturnBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MPJoinReturnBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MPJoinReturnBtn.ForeColor = System.Drawing.Color.Gold;
            this.MPJoinReturnBtn.Name = "MPJoinReturnBtn";
            this.MPJoinReturnBtn.UseVisualStyleBackColor = true;
            this.MPJoinReturnBtn.Click += new System.EventHandler(this.MPJoinReturnBtn_Click);
            this.MPJoinReturnBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MPJoinReturnBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MPJoinReturnBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MPJoinReturnBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MPJoinSelectBtn
            // 
            resources.ApplyResources(this.MPJoinSelectBtn, "MPJoinSelectBtn");
            this.MPJoinSelectBtn.FlatAppearance.BorderSize = 0;
            this.MPJoinSelectBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MPJoinSelectBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MPJoinSelectBtn.ForeColor = System.Drawing.Color.Gold;
            this.MPJoinSelectBtn.Name = "MPJoinSelectBtn";
            this.MPJoinSelectBtn.UseVisualStyleBackColor = true;
            this.MPJoinSelectBtn.Click += new System.EventHandler(this.MPJoinSelectBtn_Click);
            this.MPJoinSelectBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MPJoinSelectBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MPJoinSelectBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MPJoinSelectBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MPJoinPanel
            // 
            resources.ApplyResources(this.MPJoinPanel, "MPJoinPanel");
            this.MPJoinPanel.Controls.Add(this.ZoneJoinLabel);
            this.MPJoinPanel.Controls.Add(this.GameListView);
            this.MPJoinPanel.Controls.Add(this.JoinPlayerTitleLabel);
            this.MPJoinPanel.Controls.Add(this.MPJoinPlayersView);
            this.MPJoinPanel.Controls.Add(this.MPJoinInfo);
            this.MPJoinPanel.Controls.Add(this.MPJoinBackBtn);
            this.MPJoinPanel.Controls.Add(this.MPJoinScreenShot);
            this.MPJoinPanel.Controls.Add(this.MPJoinReadyBtn);
            this.MPJoinPanel.Name = "MPJoinPanel";
            // 
            // ZoneJoinLabel
            // 
            resources.ApplyResources(this.ZoneJoinLabel, "ZoneJoinLabel");
            this.ZoneJoinLabel.ForeColor = System.Drawing.Color.Gold;
            this.ZoneJoinLabel.Name = "ZoneJoinLabel";
            // 
            // GameListView
            // 
            this.GameListView.BackColor = System.Drawing.SystemColors.InfoText;
            this.GameListView.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.GameListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.JoinedGames});
            this.GameListView.ForeColor = System.Drawing.Color.Gold;
            this.GameListView.FullRowSelect = true;
            this.GameListView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            resources.ApplyResources(this.GameListView, "GameListView");
            this.GameListView.MultiSelect = false;
            this.GameListView.Name = "GameListView";
            this.GameListView.UseCompatibleStateImageBehavior = false;
            this.GameListView.View = System.Windows.Forms.View.Details;
            this.GameListView.SelectedIndexChanged += new System.EventHandler(this.GameListView_SelectedIndexChanged);
            // 
            // JoinedGames
            // 
            resources.ApplyResources(this.JoinedGames, "JoinedGames");
            // 
            // JoinPlayerTitleLabel
            // 
            resources.ApplyResources(this.JoinPlayerTitleLabel, "JoinPlayerTitleLabel");
            this.JoinPlayerTitleLabel.ForeColor = System.Drawing.Color.Gold;
            this.JoinPlayerTitleLabel.Name = "JoinPlayerTitleLabel";
            // 
            // MPJoinPlayersView
            // 
            this.MPJoinPlayersView.BackColor = System.Drawing.SystemColors.InfoText;
            this.MPJoinPlayersView.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.MPJoinPlayersView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.PlayerName,
            this.PlayerStatus});
            this.MPJoinPlayersView.ForeColor = System.Drawing.Color.Red;
            this.MPJoinPlayersView.FullRowSelect = true;
            this.MPJoinPlayersView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            resources.ApplyResources(this.MPJoinPlayersView, "MPJoinPlayersView");
            this.MPJoinPlayersView.MultiSelect = false;
            this.MPJoinPlayersView.Name = "MPJoinPlayersView";
            this.MPJoinPlayersView.UseCompatibleStateImageBehavior = false;
            this.MPJoinPlayersView.View = System.Windows.Forms.View.Details;
            this.MPJoinPlayersView.ItemSelectionChanged += new System.Windows.Forms.ListViewItemSelectionChangedEventHandler(this.MPJoinPlayersView_ItemSelectionChanged);
            // 
            // PlayerName
            // 
            resources.ApplyResources(this.PlayerName, "PlayerName");
            // 
            // PlayerStatus
            // 
            resources.ApplyResources(this.PlayerStatus, "PlayerStatus");
            // 
            // MPJoinInfo
            // 
            this.MPJoinInfo.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.MPJoinInfo, "MPJoinInfo");
            this.MPJoinInfo.Controls.Add(this.MPJoinGameTypeLabel);
            this.MPJoinInfo.Controls.Add(this.MPJoinMapName);
            this.MPJoinInfo.Controls.Add(this.MPJoinTimeValue);
            this.MPJoinInfo.Controls.Add(this.MPJoinTimeLabel);
            this.MPJoinInfo.Controls.Add(this.MPJoinIDLabel);
            this.MPJoinInfo.Name = "MPJoinInfo";
            // 
            // MPJoinGameTypeLabel
            // 
            resources.ApplyResources(this.MPJoinGameTypeLabel, "MPJoinGameTypeLabel");
            this.MPJoinGameTypeLabel.ForeColor = System.Drawing.Color.Gold;
            this.MPJoinGameTypeLabel.Name = "MPJoinGameTypeLabel";
            // 
            // MPJoinMapName
            // 
            resources.ApplyResources(this.MPJoinMapName, "MPJoinMapName");
            this.MPJoinMapName.ForeColor = System.Drawing.Color.Gold;
            this.MPJoinMapName.Name = "MPJoinMapName";
            // 
            // MPJoinTimeValue
            // 
            resources.ApplyResources(this.MPJoinTimeValue, "MPJoinTimeValue");
            this.MPJoinTimeValue.ForeColor = System.Drawing.Color.Gold;
            this.MPJoinTimeValue.Name = "MPJoinTimeValue";
            // 
            // MPJoinTimeLabel
            // 
            resources.ApplyResources(this.MPJoinTimeLabel, "MPJoinTimeLabel");
            this.MPJoinTimeLabel.ForeColor = System.Drawing.Color.Gold;
            this.MPJoinTimeLabel.Name = "MPJoinTimeLabel";
            // 
            // MPJoinIDLabel
            // 
            resources.ApplyResources(this.MPJoinIDLabel, "MPJoinIDLabel");
            this.MPJoinIDLabel.ForeColor = System.Drawing.Color.Gold;
            this.MPJoinIDLabel.Name = "MPJoinIDLabel";
            // 
            // MPJoinBackBtn
            // 
            resources.ApplyResources(this.MPJoinBackBtn, "MPJoinBackBtn");
            this.MPJoinBackBtn.FlatAppearance.BorderSize = 0;
            this.MPJoinBackBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MPJoinBackBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MPJoinBackBtn.ForeColor = System.Drawing.Color.Gold;
            this.MPJoinBackBtn.Name = "MPJoinBackBtn";
            this.MPJoinBackBtn.UseVisualStyleBackColor = true;
            this.MPJoinBackBtn.Click += new System.EventHandler(this.MPJoinBackBtn_Click);
            this.MPJoinBackBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MPJoinBackBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MPJoinBackBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MPJoinBackBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MPJoinScreenShot
            // 
            resources.ApplyResources(this.MPJoinScreenShot, "MPJoinScreenShot");
            this.MPJoinScreenShot.Name = "MPJoinScreenShot";
            this.MPJoinScreenShot.TabStop = false;
            // 
            // MPJoinReadyBtn
            // 
            resources.ApplyResources(this.MPJoinReadyBtn, "MPJoinReadyBtn");
            this.MPJoinReadyBtn.FlatAppearance.BorderSize = 0;
            this.MPJoinReadyBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MPJoinReadyBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MPJoinReadyBtn.ForeColor = System.Drawing.Color.Gold;
            this.MPJoinReadyBtn.Name = "MPJoinReadyBtn";
            this.MPJoinReadyBtn.UseVisualStyleBackColor = true;
            this.MPJoinReadyBtn.Click += new System.EventHandler(this.MPJoinReadyBtn_Click);
            this.MPJoinReadyBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MPJoinReadyBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MPJoinReadyBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MPJoinReadyBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // OptionsTab
            // 
            this.OptionsTab.Controls.Add(this.OptionsMainPanel);
            resources.ApplyResources(this.OptionsTab, "OptionsTab");
            this.OptionsTab.Name = "OptionsTab";
            this.OptionsTab.UseVisualStyleBackColor = true;
            // 
            // OptionsMainPanel
            // 
            this.OptionsMainPanel.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.OptionsMainPanel, "OptionsMainPanel");
            this.OptionsMainPanel.Controls.Add(this.lblLangue);
            this.OptionsMainPanel.Controls.Add(this.labelLangage);
            this.OptionsMainPanel.Controls.Add(this.btnEnglish);
            this.OptionsMainPanel.Controls.Add(this.btnFrench);
            this.OptionsMainPanel.Controls.Add(this.ReturnBtn);
            this.OptionsMainPanel.Controls.Add(this.AcceptBtn);
            this.OptionsMainPanel.Controls.Add(this.OptionsTitlePanel);
            this.OptionsMainPanel.Controls.Add(this.OptionPanel2);
            this.OptionsMainPanel.Controls.Add(this.OptionPanel1);
            this.OptionsMainPanel.Name = "OptionsMainPanel";
            // 
            // lblLangue
            // 
            resources.ApplyResources(this.lblLangue, "lblLangue");
            this.lblLangue.BackColor = System.Drawing.Color.Transparent;
            this.lblLangue.ForeColor = System.Drawing.Color.Gold;
            this.lblLangue.Name = "lblLangue";
            // 
            // labelLangage
            // 
            resources.ApplyResources(this.labelLangage, "labelLangage");
            this.labelLangage.BackColor = System.Drawing.Color.Transparent;
            this.labelLangage.ForeColor = System.Drawing.Color.Gold;
            this.labelLangage.Name = "labelLangage";
            // 
            // btnEnglish
            // 
            this.btnEnglish.BackgroundImage = global::InterfaceGraphique.Properties.Resources.english_flag;
            resources.ApplyResources(this.btnEnglish, "btnEnglish");
            this.btnEnglish.Name = "btnEnglish";
            this.btnEnglish.UseVisualStyleBackColor = true;
            this.btnEnglish.Click += new System.EventHandler(this.btnEnglish_Click);
            // 
            // btnFrench
            // 
            resources.ApplyResources(this.btnFrench, "btnFrench");
            this.btnFrench.Name = "btnFrench";
            this.btnFrench.UseVisualStyleBackColor = true;
            this.btnFrench.Click += new System.EventHandler(this.btnFrench_Click);
            // 
            // ReturnBtn
            // 
            resources.ApplyResources(this.ReturnBtn, "ReturnBtn");
            this.ReturnBtn.BackColor = System.Drawing.Color.Transparent;
            this.ReturnBtn.FlatAppearance.BorderSize = 0;
            this.ReturnBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.ReturnBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.ReturnBtn.ForeColor = System.Drawing.Color.Gold;
            this.ReturnBtn.Name = "ReturnBtn";
            this.ReturnBtn.UseVisualStyleBackColor = false;
            this.ReturnBtn.Click += new System.EventHandler(this.ReturnBtn_Click);
            this.ReturnBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.ReturnBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.ReturnBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.ReturnBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // AcceptBtn
            // 
            resources.ApplyResources(this.AcceptBtn, "AcceptBtn");
            this.AcceptBtn.BackColor = System.Drawing.Color.Transparent;
            this.AcceptBtn.FlatAppearance.BorderSize = 0;
            this.AcceptBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.AcceptBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.AcceptBtn.ForeColor = System.Drawing.Color.Gold;
            this.AcceptBtn.Name = "AcceptBtn";
            this.AcceptBtn.UseVisualStyleBackColor = false;
            this.AcceptBtn.Click += new System.EventHandler(this.AcceptBtn_Click);
            this.AcceptBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.AcceptBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.AcceptBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.AcceptBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // OptionsTitlePanel
            // 
            this.OptionsTitlePanel.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.OptionsTitlePanel, "OptionsTitlePanel");
            this.OptionsTitlePanel.Controls.Add(this.OptionsLabel);
            this.OptionsTitlePanel.Name = "OptionsTitlePanel";
            // 
            // OptionsLabel
            // 
            resources.ApplyResources(this.OptionsLabel, "OptionsLabel");
            this.OptionsLabel.ForeColor = System.Drawing.Color.Gold;
            this.OptionsLabel.Name = "OptionsLabel";
            // 
            // OptionPanel2
            // 
            resources.ApplyResources(this.OptionPanel2, "OptionPanel2");
            this.OptionPanel2.BackColor = System.Drawing.Color.Transparent;
            this.OptionPanel2.Controls.Add(this.NBillesPanel);
            this.OptionPanel2.Controls.Add(this.DebufConfigPanel);
            this.OptionPanel2.Controls.Add(this.ConfigPanel);
            this.OptionPanel2.Name = "OptionPanel2";
            // 
            // NBillesPanel
            // 
            this.NBillesPanel.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.NBillesPanel, "NBillesPanel");
            this.NBillesPanel.Controls.Add(this.Billes7CBox);
            this.NBillesPanel.Controls.Add(this.Billes5CBox);
            this.NBillesPanel.Controls.Add(this.Billes3CBox);
            this.NBillesPanel.Controls.Add(this.NBillesLabel);
            this.NBillesPanel.Name = "NBillesPanel";
            // 
            // Billes7CBox
            // 
            resources.ApplyResources(this.Billes7CBox, "Billes7CBox");
            this.Billes7CBox.FlatAppearance.BorderSize = 0;
            this.Billes7CBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.Billes7CBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.Billes7CBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.Billes7CBox.ForeColor = System.Drawing.Color.Gold;
            this.Billes7CBox.Name = "Billes7CBox";
            this.Billes7CBox.UseVisualStyleBackColor = true;
            this.Billes7CBox.Click += new System.EventHandler(this.NBillesCBoxChanged);
            // 
            // Billes5CBox
            // 
            resources.ApplyResources(this.Billes5CBox, "Billes5CBox");
            this.Billes5CBox.FlatAppearance.BorderSize = 0;
            this.Billes5CBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.Billes5CBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.Billes5CBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.Billes5CBox.ForeColor = System.Drawing.Color.Gold;
            this.Billes5CBox.Name = "Billes5CBox";
            this.Billes5CBox.UseVisualStyleBackColor = true;
            this.Billes5CBox.Click += new System.EventHandler(this.NBillesCBoxChanged);
            // 
            // Billes3CBox
            // 
            resources.ApplyResources(this.Billes3CBox, "Billes3CBox");
            this.Billes3CBox.Checked = true;
            this.Billes3CBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.Billes3CBox.FlatAppearance.BorderSize = 0;
            this.Billes3CBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.Billes3CBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.Billes3CBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.Billes3CBox.ForeColor = System.Drawing.Color.Gold;
            this.Billes3CBox.Name = "Billes3CBox";
            this.Billes3CBox.UseVisualStyleBackColor = true;
            this.Billes3CBox.Click += new System.EventHandler(this.NBillesCBoxChanged);
            // 
            // NBillesLabel
            // 
            resources.ApplyResources(this.NBillesLabel, "NBillesLabel");
            this.NBillesLabel.ForeColor = System.Drawing.Color.Gold;
            this.NBillesLabel.Name = "NBillesLabel";
            // 
            // DebufConfigPanel
            // 
            this.DebufConfigPanel.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.DebufConfigPanel, "DebufConfigPanel");
            this.DebufConfigPanel.Controls.Add(this.DebugCBox);
            this.DebufConfigPanel.Controls.Add(this.DebugEnableLabel);
            this.DebufConfigPanel.Controls.Add(this.PortailsLabel);
            this.DebufConfigPanel.Controls.Add(this.PortailsCBox);
            this.DebufConfigPanel.Controls.Add(this.EclairageCBox);
            this.DebufConfigPanel.Controls.Add(this.EclairageLabel);
            this.DebufConfigPanel.Controls.Add(this.VitesseLabel);
            this.DebufConfigPanel.Controls.Add(this.VitesseCBox);
            this.DebufConfigPanel.Controls.Add(this.GBilleCBox);
            this.DebufConfigPanel.Controls.Add(this.GBilleLabel);
            this.DebufConfigPanel.Name = "DebufConfigPanel";
            // 
            // DebugCBox
            // 
            resources.ApplyResources(this.DebugCBox, "DebugCBox");
            this.DebugCBox.Checked = true;
            this.DebugCBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.DebugCBox.FlatAppearance.BorderSize = 0;
            this.DebugCBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.DebugCBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.DebugCBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.DebugCBox.ForeColor = System.Drawing.Color.Gold;
            this.DebugCBox.Name = "DebugCBox";
            this.DebugCBox.UseVisualStyleBackColor = true;
            this.DebugCBox.CheckedChanged += new System.EventHandler(this.CheckBox_CheckChanged);
            // 
            // DebugEnableLabel
            // 
            resources.ApplyResources(this.DebugEnableLabel, "DebugEnableLabel");
            this.DebugEnableLabel.ForeColor = System.Drawing.Color.Gold;
            this.DebugEnableLabel.Name = "DebugEnableLabel";
            // 
            // PortailsLabel
            // 
            resources.ApplyResources(this.PortailsLabel, "PortailsLabel");
            this.PortailsLabel.ForeColor = System.Drawing.Color.Gold;
            this.PortailsLabel.Name = "PortailsLabel";
            // 
            // PortailsCBox
            // 
            resources.ApplyResources(this.PortailsCBox, "PortailsCBox");
            this.PortailsCBox.FlatAppearance.BorderSize = 0;
            this.PortailsCBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.PortailsCBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PortailsCBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PortailsCBox.ForeColor = System.Drawing.Color.Gold;
            this.PortailsCBox.Name = "PortailsCBox";
            this.PortailsCBox.UseVisualStyleBackColor = true;
            this.PortailsCBox.CheckStateChanged += new System.EventHandler(this.CheckBox_CheckChanged);
            // 
            // EclairageCBox
            // 
            resources.ApplyResources(this.EclairageCBox, "EclairageCBox");
            this.EclairageCBox.FlatAppearance.BorderSize = 0;
            this.EclairageCBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.EclairageCBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.EclairageCBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.EclairageCBox.ForeColor = System.Drawing.Color.Gold;
            this.EclairageCBox.Name = "EclairageCBox";
            this.EclairageCBox.UseVisualStyleBackColor = true;
            this.EclairageCBox.CheckStateChanged += new System.EventHandler(this.CheckBox_CheckChanged);
            // 
            // EclairageLabel
            // 
            resources.ApplyResources(this.EclairageLabel, "EclairageLabel");
            this.EclairageLabel.ForeColor = System.Drawing.Color.Gold;
            this.EclairageLabel.Name = "EclairageLabel";
            // 
            // VitesseLabel
            // 
            resources.ApplyResources(this.VitesseLabel, "VitesseLabel");
            this.VitesseLabel.ForeColor = System.Drawing.Color.Gold;
            this.VitesseLabel.Name = "VitesseLabel";
            // 
            // VitesseCBox
            // 
            resources.ApplyResources(this.VitesseCBox, "VitesseCBox");
            this.VitesseCBox.FlatAppearance.BorderSize = 0;
            this.VitesseCBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.VitesseCBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.VitesseCBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.VitesseCBox.ForeColor = System.Drawing.Color.Gold;
            this.VitesseCBox.Name = "VitesseCBox";
            this.VitesseCBox.UseVisualStyleBackColor = true;
            this.VitesseCBox.CheckStateChanged += new System.EventHandler(this.CheckBox_CheckChanged);
            // 
            // GBilleCBox
            // 
            resources.ApplyResources(this.GBilleCBox, "GBilleCBox");
            this.GBilleCBox.FlatAppearance.BorderSize = 0;
            this.GBilleCBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.GBilleCBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.GBilleCBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.GBilleCBox.ForeColor = System.Drawing.Color.Gold;
            this.GBilleCBox.Name = "GBilleCBox";
            this.GBilleCBox.UseVisualStyleBackColor = true;
            this.GBilleCBox.CheckStateChanged += new System.EventHandler(this.CheckBox_CheckChanged);
            // 
            // GBilleLabel
            // 
            resources.ApplyResources(this.GBilleLabel, "GBilleLabel");
            this.GBilleLabel.ForeColor = System.Drawing.Color.Gold;
            this.GBilleLabel.Name = "GBilleLabel";
            // 
            // ConfigPanel
            // 
            this.ConfigPanel.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.ConfigPanel, "ConfigPanel");
            this.ConfigPanel.Controls.Add(this.smartAICBox);
            this.ConfigPanel.Controls.Add(this.AISmartLabel);
            this.ConfigPanel.Controls.Add(this.FSPLabel);
            this.ConfigPanel.Controls.Add(this.FSPCBox);
            this.ConfigPanel.Controls.Add(this.MDBCBox);
            this.ConfigPanel.Controls.Add(this.MDBLabel);
            this.ConfigPanel.Name = "ConfigPanel";
            // 
            // smartAICBox
            // 
            resources.ApplyResources(this.smartAICBox, "smartAICBox");
            this.smartAICBox.FlatAppearance.BorderSize = 0;
            this.smartAICBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.smartAICBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.smartAICBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.smartAICBox.ForeColor = System.Drawing.Color.Gold;
            this.smartAICBox.Name = "smartAICBox";
            this.smartAICBox.UseVisualStyleBackColor = true;
            this.smartAICBox.CheckedChanged += new System.EventHandler(this.CheckBox_CheckChanged);
            // 
            // AISmartLabel
            // 
            resources.ApplyResources(this.AISmartLabel, "AISmartLabel");
            this.AISmartLabel.ForeColor = System.Drawing.Color.Gold;
            this.AISmartLabel.Name = "AISmartLabel";
            // 
            // FSPLabel
            // 
            resources.ApplyResources(this.FSPLabel, "FSPLabel");
            this.FSPLabel.ForeColor = System.Drawing.Color.Gold;
            this.FSPLabel.Name = "FSPLabel";
            // 
            // FSPCBox
            // 
            resources.ApplyResources(this.FSPCBox, "FSPCBox");
            this.FSPCBox.FlatAppearance.BorderSize = 0;
            this.FSPCBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.FSPCBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.FSPCBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.FSPCBox.ForeColor = System.Drawing.Color.Gold;
            this.FSPCBox.Name = "FSPCBox";
            this.FSPCBox.UseVisualStyleBackColor = true;
            this.FSPCBox.CheckedChanged += new System.EventHandler(this.CheckBox_CheckChanged);
            // 
            // MDBCBox
            // 
            resources.ApplyResources(this.MDBCBox, "MDBCBox");
            this.MDBCBox.FlatAppearance.BorderSize = 0;
            this.MDBCBox.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.MDBCBox.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MDBCBox.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MDBCBox.ForeColor = System.Drawing.Color.Gold;
            this.MDBCBox.Name = "MDBCBox";
            this.MDBCBox.UseVisualStyleBackColor = true;
            this.MDBCBox.CheckedChanged += new System.EventHandler(this.CheckBox_CheckChanged);
            // 
            // MDBLabel
            // 
            resources.ApplyResources(this.MDBLabel, "MDBLabel");
            this.MDBLabel.ForeColor = System.Drawing.Color.Gold;
            this.MDBLabel.Name = "MDBLabel";
            // 
            // OptionPanel1
            // 
            resources.ApplyResources(this.OptionPanel1, "OptionPanel1");
            this.OptionPanel1.BackColor = System.Drawing.Color.Transparent;
            this.OptionPanel1.Controls.Add(this.label_Rebind);
            this.OptionPanel1.Controls.Add(this.Ressort_bouton);
            this.OptionPanel1.Controls.Add(this.PDJ2_bouton);
            this.OptionPanel1.Controls.Add(this.PGJ2_bouton);
            this.OptionPanel1.Controls.Add(this.PDJ1_bouton);
            this.OptionPanel1.Controls.Add(this.PGJ1_bouton);
            this.OptionPanel1.Controls.Add(this.Default_bouton);
            this.OptionPanel1.Controls.Add(this.label_Ressort);
            this.OptionPanel1.Controls.Add(this.label_PDJ2);
            this.OptionPanel1.Controls.Add(this.label_PGJ2);
            this.OptionPanel1.Controls.Add(this.label_PDJ1);
            this.OptionPanel1.Controls.Add(this.Label_PGJ1);
            this.OptionPanel1.Name = "OptionPanel1";
            // 
            // label_Rebind
            // 
            resources.ApplyResources(this.label_Rebind, "label_Rebind");
            this.label_Rebind.ForeColor = System.Drawing.Color.DarkRed;
            this.label_Rebind.Name = "label_Rebind";
            // 
            // Ressort_bouton
            // 
            resources.ApplyResources(this.Ressort_bouton, "Ressort_bouton");
            this.Ressort_bouton.FlatAppearance.BorderSize = 0;
            this.Ressort_bouton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.Ressort_bouton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.Ressort_bouton.ForeColor = System.Drawing.Color.Gold;
            this.Ressort_bouton.Name = "Ressort_bouton";
            this.Ressort_bouton.UseVisualStyleBackColor = true;
            this.Ressort_bouton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Ressort_bouton_KeyDown);
            this.Ressort_bouton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.Ressort_bouton.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.Ressort_bouton.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.Ressort_bouton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // PDJ2_bouton
            // 
            resources.ApplyResources(this.PDJ2_bouton, "PDJ2_bouton");
            this.PDJ2_bouton.FlatAppearance.BorderSize = 0;
            this.PDJ2_bouton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PDJ2_bouton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PDJ2_bouton.ForeColor = System.Drawing.Color.Gold;
            this.PDJ2_bouton.Name = "PDJ2_bouton";
            this.PDJ2_bouton.UseVisualStyleBackColor = true;
            this.PDJ2_bouton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.PDJ2_bouton_KeyDown);
            this.PDJ2_bouton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.PDJ2_bouton.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.PDJ2_bouton.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.PDJ2_bouton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // PGJ2_bouton
            // 
            resources.ApplyResources(this.PGJ2_bouton, "PGJ2_bouton");
            this.PGJ2_bouton.FlatAppearance.BorderSize = 0;
            this.PGJ2_bouton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PGJ2_bouton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PGJ2_bouton.ForeColor = System.Drawing.Color.Gold;
            this.PGJ2_bouton.Name = "PGJ2_bouton";
            this.PGJ2_bouton.UseVisualStyleBackColor = true;
            this.PGJ2_bouton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.PGJ2_bouton_KeyDown);
            this.PGJ2_bouton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.PGJ2_bouton.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.PGJ2_bouton.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.PGJ2_bouton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // PDJ1_bouton
            // 
            resources.ApplyResources(this.PDJ1_bouton, "PDJ1_bouton");
            this.PDJ1_bouton.FlatAppearance.BorderSize = 0;
            this.PDJ1_bouton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PDJ1_bouton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PDJ1_bouton.ForeColor = System.Drawing.Color.Gold;
            this.PDJ1_bouton.Name = "PDJ1_bouton";
            this.PDJ1_bouton.UseVisualStyleBackColor = true;
            this.PDJ1_bouton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.PDJ1_bouton_KeyDown);
            this.PDJ1_bouton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.PDJ1_bouton.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.PDJ1_bouton.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.PDJ1_bouton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // PGJ1_bouton
            // 
            resources.ApplyResources(this.PGJ1_bouton, "PGJ1_bouton");
            this.PGJ1_bouton.FlatAppearance.BorderSize = 0;
            this.PGJ1_bouton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.PGJ1_bouton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.PGJ1_bouton.ForeColor = System.Drawing.Color.Gold;
            this.PGJ1_bouton.Name = "PGJ1_bouton";
            this.PGJ1_bouton.UseVisualStyleBackColor = true;
            this.PGJ1_bouton.KeyDown += new System.Windows.Forms.KeyEventHandler(this.PGJ1_bouton_KeyDown);
            this.PGJ1_bouton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.PGJ1_bouton.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.PGJ1_bouton.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.PGJ1_bouton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // Default_bouton
            // 
            resources.ApplyResources(this.Default_bouton, "Default_bouton");
            this.Default_bouton.FlatAppearance.BorderSize = 0;
            this.Default_bouton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.Default_bouton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.Default_bouton.ForeColor = System.Drawing.Color.Gold;
            this.Default_bouton.Name = "Default_bouton";
            this.Default_bouton.UseVisualStyleBackColor = true;
            this.Default_bouton.Click += new System.EventHandler(this.Default_bouton_Click);
            this.Default_bouton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.Default_bouton.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.Default_bouton.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.Default_bouton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // label_Ressort
            // 
            this.label_Ressort.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.label_Ressort.ForeColor = System.Drawing.Color.Gold;
            resources.ApplyResources(this.label_Ressort, "label_Ressort");
            this.label_Ressort.Name = "label_Ressort";
            // 
            // label_PDJ2
            // 
            this.label_PDJ2.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.label_PDJ2.ForeColor = System.Drawing.Color.Gold;
            resources.ApplyResources(this.label_PDJ2, "label_PDJ2");
            this.label_PDJ2.Name = "label_PDJ2";
            // 
            // label_PGJ2
            // 
            this.label_PGJ2.BackColor = System.Drawing.Color.Transparent;
            this.label_PGJ2.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.label_PGJ2.ForeColor = System.Drawing.Color.Gold;
            resources.ApplyResources(this.label_PGJ2, "label_PGJ2");
            this.label_PGJ2.Name = "label_PGJ2";
            // 
            // label_PDJ1
            // 
            this.label_PDJ1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.label_PDJ1.ForeColor = System.Drawing.Color.Gold;
            resources.ApplyResources(this.label_PDJ1, "label_PDJ1");
            this.label_PDJ1.Name = "label_PDJ1";
            // 
            // Label_PGJ1
            // 
            this.Label_PGJ1.BackColor = System.Drawing.Color.Transparent;
            this.Label_PGJ1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.Label_PGJ1.ForeColor = System.Drawing.Color.Gold;
            resources.ApplyResources(this.Label_PGJ1, "Label_PGJ1");
            this.Label_PGJ1.Name = "Label_PGJ1";
            // 
            // MarketplaceTab
            // 
            this.MarketplaceTab.Controls.Add(this.AvatarPanelButton);
            this.MarketplaceTab.Controls.Add(this.MapPanelButton);
            this.MarketplaceTab.Controls.Add(this.MarketPlaceMapPanel);
            this.MarketplaceTab.Controls.Add(this.MarketPlaceReturnBtn);
            this.MarketplaceTab.Controls.Add(this.MarketPlacePanel);
            resources.ApplyResources(this.MarketplaceTab, "MarketplaceTab");
            this.MarketplaceTab.Name = "MarketplaceTab";
            this.MarketplaceTab.UseVisualStyleBackColor = true;
            // 
            // AvatarPanelButton
            // 
            this.AvatarPanelButton.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.AvatarPanelButton, "AvatarPanelButton");
            this.AvatarPanelButton.FlatAppearance.BorderSize = 0;
            this.AvatarPanelButton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.AvatarPanelButton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.AvatarPanelButton.ForeColor = System.Drawing.Color.Gold;
            this.AvatarPanelButton.Name = "AvatarPanelButton";
            this.AvatarPanelButton.UseVisualStyleBackColor = false;
            this.AvatarPanelButton.Click += new System.EventHandler(this.AvatarPanelButton_Click);
            this.AvatarPanelButton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.AvatarPanelButton.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.AvatarPanelButton.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.AvatarPanelButton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MapPanelButton
            // 
            this.MapPanelButton.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.MapPanelButton, "MapPanelButton");
            this.MapPanelButton.FlatAppearance.BorderSize = 0;
            this.MapPanelButton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MapPanelButton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MapPanelButton.ForeColor = System.Drawing.Color.Gold;
            this.MapPanelButton.Name = "MapPanelButton";
            this.MapPanelButton.UseVisualStyleBackColor = false;
            this.MapPanelButton.Click += new System.EventHandler(this.MapPanelButton_Click);
            this.MapPanelButton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MapPanelButton.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MapPanelButton.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MapPanelButton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MarketPlaceMapPanel
            // 
            this.MarketPlaceMapPanel.BackColor = System.Drawing.Color.Black;
            this.MarketPlaceMapPanel.Controls.Add(this.MapErrorLabel);
            this.MarketPlaceMapPanel.Controls.Add(this.MarketPlaceTitle);
            this.MarketPlaceMapPanel.Controls.Add(this.MarketPlaceView);
            this.MarketPlaceMapPanel.Controls.Add(this.MarketPlacePicture);
            this.MarketPlaceMapPanel.Controls.Add(this.BuyMapButton);
            this.MarketPlaceMapPanel.Controls.Add(this.tableLayoutPanel1);
            resources.ApplyResources(this.MarketPlaceMapPanel, "MarketPlaceMapPanel");
            this.MarketPlaceMapPanel.Name = "MarketPlaceMapPanel";
            // 
            // MapErrorLabel
            // 
            resources.ApplyResources(this.MapErrorLabel, "MapErrorLabel");
            this.MapErrorLabel.ForeColor = System.Drawing.Color.Gold;
            this.MapErrorLabel.Name = "MapErrorLabel";
            // 
            // MarketPlaceTitle
            // 
            resources.ApplyResources(this.MarketPlaceTitle, "MarketPlaceTitle");
            this.MarketPlaceTitle.ForeColor = System.Drawing.Color.Gold;
            this.MarketPlaceTitle.Name = "MarketPlaceTitle";
            // 
            // MarketPlaceView
            // 
            this.MarketPlaceView.BackColor = System.Drawing.SystemColors.InfoText;
            this.MarketPlaceView.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.MarketPlaceView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader13,
            this.columnHeader14});
            this.MarketPlaceView.ForeColor = System.Drawing.Color.Red;
            this.MarketPlaceView.FullRowSelect = true;
            this.MarketPlaceView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
            resources.ApplyResources(this.MarketPlaceView, "MarketPlaceView");
            this.MarketPlaceView.MultiSelect = false;
            this.MarketPlaceView.Name = "MarketPlaceView";
            this.MarketPlaceView.UseCompatibleStateImageBehavior = false;
            this.MarketPlaceView.View = System.Windows.Forms.View.Details;
            this.MarketPlaceView.SelectedIndexChanged += new System.EventHandler(this.MarketPlaceView_SelectedIndexChanged);
            // 
            // columnHeader13
            // 
            resources.ApplyResources(this.columnHeader13, "columnHeader13");
            // 
            // columnHeader14
            // 
            resources.ApplyResources(this.columnHeader14, "columnHeader14");
            // 
            // MarketPlacePicture
            // 
            resources.ApplyResources(this.MarketPlacePicture, "MarketPlacePicture");
            this.MarketPlacePicture.Name = "MarketPlacePicture";
            this.MarketPlacePicture.TabStop = false;
            // 
            // BuyMapButton
            // 
            resources.ApplyResources(this.BuyMapButton, "BuyMapButton");
            this.BuyMapButton.BackColor = System.Drawing.Color.Transparent;
            this.BuyMapButton.FlatAppearance.BorderSize = 0;
            this.BuyMapButton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.BuyMapButton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.BuyMapButton.ForeColor = System.Drawing.Color.Gold;
            this.BuyMapButton.Name = "BuyMapButton";
            this.BuyMapButton.UseVisualStyleBackColor = false;
            this.BuyMapButton.Click += new System.EventHandler(this.BuyMapButton_Click);
            this.BuyMapButton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.BuyMapButton.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.BuyMapButton.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.BuyMapButton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // tableLayoutPanel1
            // 
            resources.ApplyResources(this.tableLayoutPanel1, "tableLayoutPanel1");
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            // 
            // MarketPlaceReturnBtn
            // 
            this.MarketPlaceReturnBtn.BackColor = System.Drawing.Color.Transparent;
            resources.ApplyResources(this.MarketPlaceReturnBtn, "MarketPlaceReturnBtn");
            this.MarketPlaceReturnBtn.FlatAppearance.BorderSize = 0;
            this.MarketPlaceReturnBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.MarketPlaceReturnBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.MarketPlaceReturnBtn.ForeColor = System.Drawing.Color.Gold;
            this.MarketPlaceReturnBtn.Name = "MarketPlaceReturnBtn";
            this.MarketPlaceReturnBtn.UseVisualStyleBackColor = false;
            this.MarketPlaceReturnBtn.Click += new System.EventHandler(this.MarketPlaceReturnBtn_Click);
            this.MarketPlaceReturnBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.MarketPlaceReturnBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.MarketPlaceReturnBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.MarketPlaceReturnBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MarketPlacePanel
            // 
            this.MarketPlacePanel.BackColor = System.Drawing.Color.Black;
            this.MarketPlacePanel.Controls.Add(this.BuyAvatarButton);
            this.MarketPlacePanel.Controls.Add(this.MarketPlaceAvatarPriceLabel);
            this.MarketPlacePanel.Controls.Add(this.MarketPlaceAvatarPanel);
            resources.ApplyResources(this.MarketPlacePanel, "MarketPlacePanel");
            this.MarketPlacePanel.Name = "MarketPlacePanel";
            // 
            // BuyAvatarButton
            // 
            resources.ApplyResources(this.BuyAvatarButton, "BuyAvatarButton");
            this.BuyAvatarButton.BackColor = System.Drawing.Color.Transparent;
            this.BuyAvatarButton.FlatAppearance.BorderSize = 0;
            this.BuyAvatarButton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.BuyAvatarButton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.BuyAvatarButton.ForeColor = System.Drawing.Color.Gold;
            this.BuyAvatarButton.Name = "BuyAvatarButton";
            this.BuyAvatarButton.UseVisualStyleBackColor = false;
            this.BuyAvatarButton.Click += new System.EventHandler(this.BuyAvatarButton_Click);
            this.BuyAvatarButton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.BuyAvatarButton.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.BuyAvatarButton.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.BuyAvatarButton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // MarketPlaceAvatarPriceLabel
            // 
            resources.ApplyResources(this.MarketPlaceAvatarPriceLabel, "MarketPlaceAvatarPriceLabel");
            this.MarketPlaceAvatarPriceLabel.ForeColor = System.Drawing.Color.Gold;
            this.MarketPlaceAvatarPriceLabel.Name = "MarketPlaceAvatarPriceLabel";
            // 
            // MarketPlaceAvatarPanel
            // 
            resources.ApplyResources(this.MarketPlaceAvatarPanel, "MarketPlaceAvatarPanel");
            this.MarketPlaceAvatarPanel.Name = "MarketPlaceAvatarPanel";
            // 
            // MenuComplet
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ControlBox = false;
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.KeyPreview = true;
            this.Name = "MenuComplet";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MenuComplet_FormClosing);
            this.VisibleChanged += new System.EventHandler(this.MenuComplet_VisibleChanged);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MenuComplet_KeyDown);
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.MenuComplet_KeyPress);
            this.tabControl1.ResumeLayout(false);
            this.LoginTab.ResumeLayout(false);
            this.ErrorPanel.ResumeLayout(false);
            this.CreateAccountPanel.ResumeLayout(false);
            this.CAInfoPanel.ResumeLayout(false);
            this.CAInfoPanel.PerformLayout();
            this.PseudoPanel.ResumeLayout(false);
            this.PseudoPanel.PerformLayout();
            this.LogInPanel.ResumeLayout(false);
            this.LogInPanel.PerformLayout();
            this.InfoPanel.ResumeLayout(false);
            this.InfoPanel.PerformLayout();
            this.MainTab.ResumeLayout(false);
            this.MainTab.PerformLayout();
            this.DownloadPanel.ResumeLayout(false);
            this.PlayerInfoPanel.ResumeLayout(false);
            this.PlayerInfoPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.AvatarBox)).EndInit();
            this.MultiPlayerPanel.ResumeLayout(false);
            this.SinglePlayerPanel.ResumeLayout(false);
            this.MainPanel.ResumeLayout(false);
            this.CampaignTab.ResumeLayout(false);
            this.CampaignPanel.ResumeLayout(false);
            this.CampaignPanel.PerformLayout();
            this.CampaignPlayerTypePanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.CampaignScreenShotBox)).EndInit();
            this.QuickGameTab.ResumeLayout(false);
            this.QGamePanel.ResumeLayout(false);
            this.QGamePanel.PerformLayout();
            this.PlayerTimePanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.screenShot)).EndInit();
            this.LobbyTab.ResumeLayout(false);
            this.GameTutoPanel.ResumeLayout(false);
            this.MPCreatePanel.ResumeLayout(false);
            this.MPCreatePanel.PerformLayout();
            this.MPInfoPanel.ResumeLayout(false);
            this.MPInfoPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MPScreenShot)).EndInit();
            this.MPGameSelectTab.ResumeLayout(false);
            this.MPJoinGameSelectPanel.ResumeLayout(false);
            this.MPJoinGameSelectPanel.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.MPJoinPanel.ResumeLayout(false);
            this.MPJoinPanel.PerformLayout();
            this.MPJoinInfo.ResumeLayout(false);
            this.MPJoinInfo.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MPJoinScreenShot)).EndInit();
            this.OptionsTab.ResumeLayout(false);
            this.OptionsMainPanel.ResumeLayout(false);
            this.OptionsMainPanel.PerformLayout();
            this.OptionsTitlePanel.ResumeLayout(false);
            this.OptionPanel2.ResumeLayout(false);
            this.NBillesPanel.ResumeLayout(false);
            this.DebufConfigPanel.ResumeLayout(false);
            this.ConfigPanel.ResumeLayout(false);
            this.OptionPanel1.ResumeLayout(false);
            this.MarketplaceTab.ResumeLayout(false);
            this.MarketPlaceMapPanel.ResumeLayout(false);
            this.MarketPlaceMapPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.MarketPlacePicture)).EndInit();
            this.MarketPlacePanel.ResumeLayout(false);
            this.MarketPlacePanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage LoginTab;
        private System.Windows.Forms.TabPage MainTab;
        private System.Windows.Forms.Label UsernameLabelLogin;
        private System.Windows.Forms.TabPage CampaignTab;
        private System.Windows.Forms.TabPage QuickGameTab;
        private System.Windows.Forms.TabPage LobbyTab;
        private System.Windows.Forms.TabPage MPGameSelectTab;
        private System.Windows.Forms.TabPage OptionsTab;
        private System.Windows.Forms.TabPage MarketplaceTab;
        private System.Windows.Forms.Panel LogInPanel;
        private System.Windows.Forms.TextBox UsernameBox;
        private System.Windows.Forms.Label PasswordLabel;
        private System.Windows.Forms.LinkLabel PasswordResetLink;
        private System.Windows.Forms.Button PlayOfflineBtn;
        private System.Windows.Forms.Button LogibBtnLogin;
        private System.Windows.Forms.TextBox PasswordBox;
        private System.Windows.Forms.Panel MainPanel;
        private System.Windows.Forms.Button SoloBtn;
        private System.Windows.Forms.Button MultiPlayerBtn;
        private System.Windows.Forms.Button EditeurBtn;
        private System.Windows.Forms.Button OptionsBtn;
        private System.Windows.Forms.Button MarketplaceBtn;
        private System.Windows.Forms.Button QuitBtn;
        private System.Windows.Forms.Button QGameBtn;
        private System.Windows.Forms.Button CAccountBtn;
        private System.Windows.Forms.Button ConnectBtn;
        private System.Windows.Forms.Panel InfoPanel;
        private System.Windows.Forms.Panel OptionPanel1;
        private System.Windows.Forms.Label label_Rebind;
        private System.Windows.Forms.Button Ressort_bouton;
        private System.Windows.Forms.Button PDJ2_bouton;
        private System.Windows.Forms.Button PGJ2_bouton;
        private System.Windows.Forms.Button PDJ1_bouton;
        private System.Windows.Forms.Button PGJ1_bouton;
        private System.Windows.Forms.Button Default_bouton;
        private System.Windows.Forms.Label label_Ressort;
        private System.Windows.Forms.Label label_PDJ2;
        private System.Windows.Forms.Label label_PGJ2;
        private System.Windows.Forms.Label label_PDJ1;
        private System.Windows.Forms.Label Label_PGJ1;
        private System.Windows.Forms.Panel OptionPanel2;
        private System.Windows.Forms.Panel ConfigPanel;
        private System.Windows.Forms.CheckBox MDBCBox;
        private System.Windows.Forms.Label MDBLabel;
        private System.Windows.Forms.Label FSPLabel;
        private System.Windows.Forms.CheckBox FSPCBox;
        private System.Windows.Forms.Panel DebufConfigPanel;
        private System.Windows.Forms.Label PortailsLabel;
        private System.Windows.Forms.CheckBox PortailsCBox;
        private System.Windows.Forms.CheckBox EclairageCBox;
        private System.Windows.Forms.Label EclairageLabel;
        private System.Windows.Forms.Label VitesseLabel;
        private System.Windows.Forms.CheckBox VitesseCBox;
        private System.Windows.Forms.CheckBox GBilleCBox;
        private System.Windows.Forms.Label GBilleLabel;
        private System.Windows.Forms.CheckBox DebugCBox;
        private System.Windows.Forms.Label DebugEnableLabel;
        private System.Windows.Forms.Panel NBillesPanel;
        private System.Windows.Forms.CheckBox Billes7CBox;
        private System.Windows.Forms.CheckBox Billes5CBox;
        private System.Windows.Forms.CheckBox Billes3CBox;
        private System.Windows.Forms.Label NBillesLabel;
        private System.Windows.Forms.Panel OptionsTitlePanel;
        private System.Windows.Forms.Label OptionsLabel;
        private System.Windows.Forms.Panel OptionsMainPanel;
        private System.Windows.Forms.Button ReturnBtn;
        private System.Windows.Forms.Button AcceptBtn;
        private System.Windows.Forms.Panel CreateAccountPanel;
        private System.Windows.Forms.Button CancelBtn;
        private System.Windows.Forms.Button CreateAccBtn;
        private System.Windows.Forms.Panel CAInfoPanel;
        private System.Windows.Forms.Label CAEmailLabel;
        private System.Windows.Forms.Label CAAgeLabel;
        private System.Windows.Forms.TextBox CAEmailBox;
        private System.Windows.Forms.TextBox CAAgeBox;
        private System.Windows.Forms.Panel PseudoPanel;
        private System.Windows.Forms.Label CAPseudoLabel;
        private System.Windows.Forms.Label CAPasswordLabel;
        private System.Windows.Forms.TextBox CAPseudoBox;
        private System.Windows.Forms.TextBox CAPasswordBox;
        private System.Windows.Forms.Panel ErrorPanel;
        private System.Windows.Forms.Label ErrorLabel;
        private System.Windows.Forms.Button ErrorBtn;
        private System.Windows.Forms.Panel SinglePlayerPanel;
        private System.Windows.Forms.Button CampagneBtn;
        private System.Windows.Forms.Button PRapideBtn;
        private System.Windows.Forms.Button RetourSPBtn;
        private System.Windows.Forms.Panel MultiPlayerPanel;
        private System.Windows.Forms.Button RetourMPBtn;
        private System.Windows.Forms.Button JoinBtn;
        private System.Windows.Forms.Button CreateBtn;
        private System.Windows.Forms.Button MPQuickGameBtn;
        private System.Windows.Forms.Panel QGamePanel;
        private System.Windows.Forms.Button bouton_Cancel;
        private System.Windows.Forms.ListView ZonesDisponibles;
        private System.Windows.Forms.ColumnHeader columnHeader1;
        private System.Windows.Forms.ColumnHeader columnHeader2;
        private System.Windows.Forms.PictureBox screenShot;
        private System.Windows.Forms.Button bouton_OK;
        private System.Windows.Forms.Label label_ZJDisp;
        private System.Windows.Forms.Panel PlayerTimePanel;
        private System.Windows.Forms.CheckBox checkBox2Player;
        private System.Windows.Forms.CheckBox checkBoxSolo;
        private System.Windows.Forms.Label PlayerTypeLabel;
        private System.Windows.Forms.CheckBox checkBoxAI;
        private System.Windows.Forms.TextBox IPAddressBox;
        private System.Windows.Forms.Button ServerConnectBtn;
        private System.Windows.Forms.Button btnFrench;
        private System.Windows.Forms.Button btnEnglish;
        private System.Windows.Forms.Label labelLangage;
        private System.Windows.Forms.Label lblLangue;
        private System.Windows.Forms.Panel PlayerInfoPanel;
        private System.Windows.Forms.Label PlayerNewPasswordLabel;
        private System.Windows.Forms.TextBox PlayerNewPasswordTBox;
        private System.Windows.Forms.Label PlayerOldPasswordLabel;
        private System.Windows.Forms.TextBox PlayerOldPasswordTBox;
        private System.Windows.Forms.Button PlayerEditAnnulerBtn;
        private System.Windows.Forms.Button PlayerEditAcceptBtn;
        private System.Windows.Forms.Button PlayerEditBtn;
        private System.Windows.Forms.Button AchievBtn;
        private System.Windows.Forms.Label PlayerAgeLabel;
        private System.Windows.Forms.TextBox PlayerAgeTBox;
        private System.Windows.Forms.Label PlayerEmailLabel;
        private System.Windows.Forms.TextBox PlayerEmailTBox;
        private System.Windows.Forms.Label PlayerSurnameLabel;
        private System.Windows.Forms.TextBox PlayerSurnameTBox;
        private System.Windows.Forms.Label PlayerNameLabel;
        private System.Windows.Forms.TextBox PlayerNameTBox;
        private System.Windows.Forms.Label APointsLabel;
        private System.Windows.Forms.Label CurrencyLabel;
        private System.Windows.Forms.PictureBox AvatarBox;
        private System.Windows.Forms.Label NomLabel;
        private System.Windows.Forms.Label PlayerCoopVictoriesLabel;
        private System.Windows.Forms.Label PlayerInfoVictoriesLabel;
        private System.Windows.Forms.Label PlayerInfoGamePlayedLabel;
        private System.Windows.Forms.CheckBox PlayerInfoPrivateProfile;
        private System.Windows.Forms.Label PlayerInfoPrivateLabel;
        private System.Windows.Forms.Label PlayerInfoErrorLabel;
        private System.Windows.Forms.Panel CampaignPanel;
        private System.Windows.Forms.Panel CampaignPlayerTypePanel;
        private System.Windows.Forms.CheckBox checkBoxCAI;
        private System.Windows.Forms.CheckBox checkBoxC2;
        private System.Windows.Forms.CheckBox checkBoxCSolo;
        private System.Windows.Forms.Label CampaignPlayerTypeLabel;
        private System.Windows.Forms.Button campaignCancelBtn;
        private System.Windows.Forms.ListView CampaignZonesListView;
        private System.Windows.Forms.ColumnHeader columnHeader3;
        private System.Windows.Forms.ColumnHeader columnHeader4;
        private System.Windows.Forms.PictureBox CampaignScreenShotBox;
        private System.Windows.Forms.Button campaignStartBtn;
        private System.Windows.Forms.Label CampaignZonesLabel;
        private System.Windows.Forms.ListView CampaignSelectedListView;
        private System.Windows.Forms.ColumnHeader columnHeader5;
        private System.Windows.Forms.ColumnHeader columnHeader6;
        private System.Windows.Forms.Label CampaignChoiceLabel;
        private System.Windows.Forms.Button CampaignAddBtn;
        private System.Windows.Forms.Button CampaignEmptyBtn;
        private System.Windows.Forms.Button CampaignRemoveItemBtn;
        private System.Windows.Forms.CheckBox instaDeathCBox;
        private System.Windows.Forms.Label instaDeathLabel;
        private System.Windows.Forms.Label timeAttackLabel;
        private System.Windows.Forms.CheckBox timeAttackCBox;
        private System.Windows.Forms.Label timeLabel;
        private System.Windows.Forms.Button minusBtn;
        private System.Windows.Forms.Button plusBtn;
        private System.Windows.Forms.Label timeLimitLabel;
        private System.Windows.Forms.Label CtimeLimitLabel;
        private System.Windows.Forms.Button CplusBtn;
        private System.Windows.Forms.Button CminusBtn;
        private System.Windows.Forms.Label CtimeLabel;
        private System.Windows.Forms.Label CtimeAttackLabel;
        private System.Windows.Forms.CheckBox CtimeAttackCBox;
        private System.Windows.Forms.Label CinstaDeathLabel;
        private System.Windows.Forms.CheckBox CinstaDeathCBox;
        private System.Windows.Forms.TableLayoutPanel avatarPanel;
        private System.Windows.Forms.Button avatarBtn;
        private System.Windows.Forms.Panel MPCreatePanel;
        private System.Windows.Forms.Label MPTimeLimitLabel;
        private System.Windows.Forms.Button MPCreatePlusBtn;
        private System.Windows.Forms.Button MPCreateMinus;
        private System.Windows.Forms.Label MPtimeLabel;
        private System.Windows.Forms.Label MPTimerLabel;
        private System.Windows.Forms.CheckBox MPCreateCBoxTime;
        private System.Windows.Forms.Label MpInstaDeathLabel;
        private System.Windows.Forms.CheckBox MPCreateCBoxID;
        private System.Windows.Forms.Panel MPInfoPanel;
        private System.Windows.Forms.Button MPCreateCancelBtn;
        private System.Windows.Forms.ListView MPZonesDisponibles;
        private System.Windows.Forms.ColumnHeader columnHeader7;
        private System.Windows.Forms.ColumnHeader columnHeader8;
        private System.Windows.Forms.PictureBox MPScreenShot;
        private System.Windows.Forms.Button MPCreateStartBtn;
        private System.Windows.Forms.Label MPZonesDisponiblesLabel;
        private System.Windows.Forms.ListView joinedPlayerView;
        private System.Windows.Forms.ColumnHeader columnHeader9;
        private System.Windows.Forms.ColumnHeader columnHeader10;
        private System.Windows.Forms.Label MPPasswordLabel;
        private System.Windows.Forms.TextBox MPPasswordTBox;
        private System.Windows.Forms.Button MPCreateRoomBtn;
        private System.Windows.Forms.Panel MPJoinPanel;
        private System.Windows.Forms.ListView MPJoinPlayersView;
        private System.Windows.Forms.ColumnHeader PlayerName;
        private System.Windows.Forms.ColumnHeader PlayerStatus;
        private System.Windows.Forms.Panel MPJoinInfo;
        private System.Windows.Forms.Label MPJoinMapName;
        private System.Windows.Forms.Label MPJoinTimeValue;
        private System.Windows.Forms.Label MPJoinTimeLabel;
        private System.Windows.Forms.Label MPJoinIDLabel;
        private System.Windows.Forms.Button MPJoinBackBtn;
        private System.Windows.Forms.PictureBox MPJoinScreenShot;
        private System.Windows.Forms.Button MPJoinReadyBtn;
        private System.Windows.Forms.Panel MPJoinGameSelectPanel;
        private System.Windows.Forms.ListView MPJoinGameView;
        private System.Windows.Forms.ColumnHeader MapName;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label MPJoinAvailableGamesLabel;
        private System.Windows.Forms.Button MPJoinReturnBtn;
        private System.Windows.Forms.Button MPJoinSelectBtn;
        private System.Windows.Forms.Button RefreshBtn;
        private System.Windows.Forms.TableLayoutPanel AchievementMainPanel;
        private System.Windows.Forms.ColumnHeader HostName;
        private System.Windows.Forms.Label MPJoinPasswordLabel;
        private System.Windows.Forms.TextBox MPJoinPasswordTBox;
        private System.Windows.Forms.Label MPJoinErrorLabel;
        private System.Windows.Forms.CheckBox MPCreateGModeCBox;
        private System.Windows.Forms.Label MPCreateGModeLabel;
        private System.Windows.Forms.ColumnHeader gameType;
        private System.Windows.Forms.Label MPJoinGameTypeLabel;
        private System.Windows.Forms.Panel MarketPlacePanel;
        private System.Windows.Forms.Button MarketPlaceReturnBtn;
        private System.Windows.Forms.TableLayoutPanel MarketPlaceAvatarPanel;
        private System.Windows.Forms.Label MarketPlaceAvatarPriceLabel;
        private System.Windows.Forms.Label AISmartLabel;
        private System.Windows.Forms.CheckBox smartAICBox;
        private System.Windows.Forms.Button TestButton;
        private System.Windows.Forms.Button BuyAvatarButton;
        private System.Windows.Forms.ColumnHeader LobbyOrGame;
        private System.Windows.Forms.ColumnHeader hiddenGames;
        private System.Windows.Forms.Button TutorialBtn;
        private System.Windows.Forms.Panel DownloadPanel;
        private System.Windows.Forms.Label DownloadLabel;
        private System.Windows.Forms.Label ChosenGamesLabel;
        private System.Windows.Forms.ListView MPGameSelected;
        private System.Windows.Forms.ColumnHeader columnHeader11;
        private System.Windows.Forms.ColumnHeader columnHeader12;
        private System.Windows.Forms.Button AddMPGameBtn;
        private System.Windows.Forms.Button EmptyMPGameBtn;
        private System.Windows.Forms.Button RemoveMPGameBtn;
        private System.Windows.Forms.Panel MarketPlaceMapPanel;
        private System.Windows.Forms.Button BuyMapButton;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Button AvatarPanelButton;
        private System.Windows.Forms.Button MapPanelButton;
        private System.Windows.Forms.ListView MarketPlaceView;
        private System.Windows.Forms.ColumnHeader columnHeader13;
        private System.Windows.Forms.ColumnHeader columnHeader14;
        private System.Windows.Forms.PictureBox MarketPlacePicture;
        private System.Windows.Forms.Label MarketPlaceTitle;
        private System.Windows.Forms.Label MapErrorLabel;
        private System.Windows.Forms.Label PlayerTitleLabel;
        private System.Windows.Forms.Label ZoneJoinLabel;
        private System.Windows.Forms.ListView GameListView;
        private System.Windows.Forms.ColumnHeader JoinedGames;
        private System.Windows.Forms.Label JoinPlayerTitleLabel;
        private System.Windows.Forms.Label PlayerCompVictoriesLabel;
        private System.Windows.Forms.Panel GameTutoPanel;
        private System.Windows.Forms.Button GameTutoNext;
        private System.Windows.Forms.Button GameTutoCancel;
        private System.Windows.Forms.Label GameTutoLabel;
    }
}