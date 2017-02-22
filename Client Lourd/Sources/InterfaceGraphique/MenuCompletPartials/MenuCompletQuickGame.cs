using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    partial class MenuComplet
    {
        string[] filePaths; ///< Path des fichiers de zones
        string fileNames;
        public  List<string> zonesCampagne; ///< Liste des zones de la campagne.
        int sortColumn = -1; ///< Pour le tri des colonnes.
        int diff;
        int typeJoueur = 1;
        int time;
        StringBuilder pathMap;

        private void SetUpPartieRapide()
        {

            QGamePanel.Location = new Point(
                  QGamePanel.Parent.Width / 2 - OptionsMainPanel.Size.Width / 2,
              QGamePanel.Parent.Height / 2 - OptionsMainPanel.Size.Height / 2);
            QGamePanel.Anchor = AnchorStyles.None;

            filePaths = Directory.GetFiles(Application.StartupPath + @"\zones", "*.xml");
            zonesCampagne = new List<string>();
            ZonesDisponibles.Items.Clear();
            ZonesDisponibles.SelectedItems.Clear();
            foreach (string s in filePaths)
            {
                pathMap = new StringBuilder(s);
                diff = FonctionsNatives.obtenirDifficulte(pathMap, pathMap.Capacity);
                fileNames = Path.GetFileNameWithoutExtension(s);
                var tempItemp = new ListViewItem(new[] { fileNames, diff.ToString() });
                ZonesDisponibles.Items.Add(tempItemp);
            }
        }

        private void PlayerTimeChanged(object sender, EventArgs e)
        {
            System.Windows.Forms.CheckBox checkedBox = (System.Windows.Forms.CheckBox)sender;

            if (checkedBox.Name == checkBoxSolo.Name)
            {
                typeJoueur = 1;
                checkBoxSolo.Checked = true;
                checkBoxSolo.BackgroundImage = Properties.Resources.buttonStock1h;
                checkBox2Player.Checked = false;
                checkBox2Player.BackgroundImage = smallBorder;
                checkBoxAI.Checked = false;
                checkBoxAI.BackgroundImage = smallBorder;


            }
            else if (checkedBox.Name == checkBox2Player.Name)
            {
                typeJoueur = 2;
                checkBox2Player.Checked = true;
                checkBox2Player.BackgroundImage = Properties.Resources.buttonStock1h;
                checkBoxSolo.Checked = false;
                checkBoxSolo.BackgroundImage = smallBorder;
                checkBoxAI.Checked = false;
                checkBoxAI.BackgroundImage = smallBorder;
            }
            else if (checkedBox.Name == checkBoxAI.Name)
            {
                typeJoueur = 3;
                checkBoxAI.Checked = true;
                checkBoxAI.BackgroundImage = Properties.Resources.buttonStock1h;
                checkBoxSolo.Checked = false;
                checkBoxSolo.BackgroundImage = smallBorder;
                checkBox2Player.Checked = false;
                checkBox2Player.BackgroundImage = smallBorder;
            }

        }


        ////////////////////////////////////////////////////////////////////////
        /// @fn private void ZonesDisponibles_SelectedIndexChanged(object sender, EventArgs e)
        /// @brief Affichage de l'image lorsqu'on clique sur un zone disponible dans la liste.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ////////////////////////////////////////////////////////////////////////
        private void ZonesDisponibles_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (ZonesDisponibles.SelectedIndices.Count <= 0) return;
            int index = ZonesDisponibles.SelectedIndices[0];
            if (index >= 0)
            {
                fileNames = ZonesDisponibles.Items[index].Text;
                screenShot.SizeMode = PictureBoxSizeMode.StretchImage;
                if (File.Exists(Application.StartupPath + @"\zones\" + fileNames + ".jpg"))
                {
                    screenShot.Image = Image.FromFile(Application.StartupPath + @"\zones\" + fileNames + ".jpg");
                }
                else
                {
                    screenShot.Image = Properties.Resources.SaintTrinity;
                }
                bouton_OK.Enabled = true;
            }
        }



        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_OK_Click(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on clique sur le bouton OK.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_OK_Click(object sender, EventArgs e)
        {
            if (ZonesDisponibles.SelectedItems.Count != 0)
            {
                zonesCampagne.Insert(0, Application.StartupPath + @"\zones\" + ZonesDisponibles.SelectedItems[0].Text + ".xml");
                if (timeAttackCBox.Checked)
                {
                    time = Convert.ToInt32(timeLabel.Text);                    
                }

                LancerModeJeu(zonesCampagne, typeJoueur,time,instaDeathCBox.Checked);
            }
            else
            {
                MessageBox.Show("Selectionnez une zone pour commencer la partie", "ERREUR DE LANCEMENT",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void bouton_Cancel_Click(object sender, EventArgs e)
        /// @brief Fonction qui revenir au menu SinglePlayer
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void bouton_Cancel_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = MainTab;
            MainTab.Focus();
            MainPanel.Visible = false;
            SinglePlayerPanel.Visible = true;
        }


     
        
        #region GameModes


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void instaDeathCBox_CheckedChanged(object sender, EventArgs e)
        /// @brief Fonction qui change l'allure du bouton instaDeathCBox
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void instaDeathCBox_CheckedChanged(object sender, EventArgs e)
        {
            if (instaDeathCBox.Checked)
            {
                instaDeathCBox.BackgroundImage = Properties.Resources.buttonStock1h;
                instaDeathCBox.Text = "✓";
            }
            else
            {
                instaDeathCBox.Text = "";
                instaDeathCBox.BackgroundImage = smallBorder;

            }
        }


        private void timeAttackCBox_CheckedChanged(object sender, EventArgs e)
        {
            if (timeAttackCBox.Checked)
            {
                timeAttackCBox.BackgroundImage = Properties.Resources.buttonStock1h;
                timeAttackCBox.Text = "✓";
                SetUpTimeButtons(true);
            }
            else
            {
                timeAttackCBox.Text = "";
                timeAttackCBox.BackgroundImage = smallBorder;
                SetUpTimeButtons(false);
            }
        }


        private void minusBtn_Click(object sender, EventArgs e)
        {
            time = Convert.ToInt32(timeLabel.Text);
            if (time > 1)
            {
                time--;
                if (time == 1)
                {
                    minusBtn.Enabled = false;
                }
                plusBtn.Enabled = true;
                timeLabel.Text = time.ToString();
            }
        }

        private void plusBtn_Click(object sender, EventArgs e)
        {
            time = Convert.ToInt32(timeLabel.Text);
            if (time < 10)
            {
                time++;
                if (time == 10)
                {
                    plusBtn.Enabled = false;
                }
                minusBtn.Enabled = true;
                timeLabel.Text = time.ToString();
            }
        }

        private void SetUpTimeButtons(bool activate)
        {
            minusBtn.Enabled = activate;
            plusBtn.Enabled = activate;
            timeLabel.Enabled = activate;
            timeLimitLabel.Enabled = activate;
        }
     
        #endregion
     
    }
}
