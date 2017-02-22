
using System;
using System.Drawing;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    partial class MenuComplet
    {

        private void SetUpLogIn()
        {
            // Place le paneau de login au centre inferieur de la form
            if (Screen.PrimaryScreen.WorkingArea.Height < 1000)
            {
              //  LoginTab.Height = 768+50;
            }
            LogInPanel.Location = new Point(
                LoginTab.Width / 2 - LogInPanel.Size.Width / 2,
                LoginTab.Height / 1 - LogInPanel.Size.Height / 1);
            LogInPanel.Anchor = AnchorStyles.Bottom;

            ErrorPanel.Location = new Point(
                LoginTab.Width / 2 - ErrorPanel.Width/2,
                LoginTab.Height / 2 - ErrorPanel.Height / 2);
            // Placer le bouton Quitter en bas a droite peu importe la resolution
            QGameBtn.Location = new Point(
                20,
                ClientSize.Height - QGameBtn.Height);
            // Placer le bouton CreerCompte juste en haut du bouton Quitter avec une marge de 5px
            CAccountBtn.Location = new Point(
                20,
                ClientSize.Height - CAccountBtn.Height * 2 - 5
                );
            CreateAccountPanel.Location = LogInPanel.Location;
            if (File.Exists(@"lastuser.yonni"))
            {
                string[] logInfo = System.IO.File.ReadAllText(@"lastuser.yonni").Split(' ');
                UsernameBox.Text = logInfo[0];
                IPAddressBox.Text = logInfo[1];
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void LogibBtnLogin_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet de se connecter a son compte.
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void LogibBtnLogin_Click(object sender, EventArgs e)
        {
          
            if (UsernameBox.Text == "")
            {
                ErrorPanel.Visible = true;
                ErrorLabel.Text = "Impossible de se connecter avec un nom vide!";
                LogInPanel.Visible = false;
            }
            if (PasswordBox.Text == "")
            {
                ErrorPanel.Visible = true;
                ErrorLabel.Text = "Impossible de se connecter avec un mot de passe vide!";
                LogInPanel.Visible = false;
            }
            if (IPAddressBox.Text == "")
            {
                ErrorPanel.Visible = true;
                ErrorLabel.Text = "Impossible de se connecter avec un IP vide!";
                LogInPanel.Visible = false;
            }
            
            else
            {
                StringBuilder username = new StringBuilder(UsernameBox.Text);
                StringBuilder password = new StringBuilder(PasswordBox.Text);
                succesLogIN = FonctionsNatives.LogIn(username, password);
                if (succesLogIN)
                {
                    tabControl1.SelectedTab = MainTab;
                    avatarPanel.Visible = false;
                    if (chat == null)
                    {
                        chat = new ChatForm();
                        chat.Show(this);
                    }

                    Program.playerName = UsernameBox.Text;
                    File.WriteAllText(@"lastuser.yonni", UsernameBox.Text + " " + IPAddressBox.Text);

                    connected = true;
                    NomLabel.Text = Program.playerName;
                    if (Program.playerName == "Charlotte")
                    {
                        AvatarBox.BackgroundImage = Properties.Resources.Avatar;
                    }
                 

                    MainTab.Focus();
                    SetUpPlayerInfo();
                    MultiPlayerBtn.Enabled = true;

                }
                else
                {
                    SetText("Erreur de connexion!.");
                }
            }

        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PlayOfflineBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet de se connecter de facon anonyme
        ///        Le chat n'est pas disponible dans ce mode
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PlayOfflineBtn_Click(object sender, EventArgs e)
        {
            // Créer le compte Offline
            string name = FonctionsNatives.InitializeOffline();
            PlayerInfoPanel.Height = 110;
            ConnectBtn.Location = new Point(ConnectBtn.Location.X, PlayerInfoPanel.Height + 5);
            tabControl1.SelectedTab = MainTab;
            connected = false;
            Program.playerName = name;
            NomLabel.Text = Program.playerName;


            MainTab.Focus();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void CancelBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet de revenir au paneau de connexion
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void CancelBtn_Click(object sender, EventArgs e)
        {
            LogInPanel.Visible = true;

            CreateAccountPanel.Visible = false;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ErroBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet d'enlever le message d'erreur
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ErroBtn_Click(object sender, EventArgs e)
        {
            ErrorPanel.Visible = false;
            if (duplicate)
            {
                CreateAccountPanel.Visible = false;
                LogInPanel.Visible = true;
            }
            CreateAccountPanel.Enabled = true;
            LogInPanel.Visible = true;
           
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void CreateAccBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui de creer un compte. Apres le click,
        ///        le c# envoie l'information vers le C++ qui l'envoie vers le serveur
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void CreateAccBtn_Click(object sender, EventArgs e)
        {
            StringBuilder createAccountInfo = new StringBuilder();
            // Verification des donnes de l'utilisateur
            bool error = false;
           
            if (!Regex.IsMatch(CAPseudoBox.Text,"^[a-zA-Z0-9]*$") || CAPseudoBox.Text == string.Empty)
            {
                ErrorLabel.Text += " Erreur : Le nom d'usager contient des caracteres invalides\n";
                error = true;
            }
            if (CAPasswordBox.Text.Length < 5 || CAPasswordBox.Text.Length > 20)
            {
                ErrorLabel.Text += "Erreur: Le mot de passe doit être entre 5 et 20 caractères\n";
                error = true;
            }

            if (error)
            {
                ErrorPanel.Visible = true;
                ErrorPanel.BringToFront();
                CreateAccountPanel.Enabled = false;
            }
            // Formatage du data :
            else
            {
               
                StringBuilder username = new StringBuilder(CAPseudoBox.Text);
                StringBuilder password = new StringBuilder(CAPasswordBox.Text);
                StringBuilder email = new StringBuilder(CAEmailBox.Text);


                duplicate = FonctionsNatives.CreateAccount(username, password, email);
                Console.WriteLine(duplicate);
                if (!duplicate)
                {
                    SetText("Erreur de creation de compte");
                }
                else
                {
                    SetText("Creation de compte reussie!");
                   
                }
            }
        }
    }
}
