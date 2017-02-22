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
        string[] campaignFilePaths; ///< Path des fichiers de zones
        string CampaignFileName;
        List<string> CampaignZonesCampagne; ///< Liste des zones de la campagne.
        StringBuilder CampaignPathMap;

        int Ctime;
        int campaignPlayerType = 1;
        StringBuilder mapList = new StringBuilder("UN ");

        private void SetUpCampaign()
        {
            campaignFilePaths = Directory.GetFiles(Application.StartupPath + @"\zones", "*.xml");
            zonesCampagne = new List<string>();
            CampaignZonesListView.Items.Clear();
            CampaignSelectedListView.Items.Clear();
            CampaignZonesListView.SelectedItems.Clear();
            foreach (string s in campaignFilePaths)
            {
                CampaignPathMap = new StringBuilder(s);
                diff = FonctionsNatives.obtenirDifficulte(CampaignPathMap, CampaignPathMap.Capacity);
                CampaignFileName = Path.GetFileNameWithoutExtension(s);
                var tempItemp = new ListViewItem(new[] { CampaignFileName, diff.ToString() });
                CampaignZonesListView.Items.Add(tempItemp);
            }

            CampaignEmptyBtn.PerformClick();
            string tempConfig = FonctionsNatives.obtenirDerniereCampagne();
            string[] configurations = tempConfig.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

            if (configurations[0] == "UN")
            {
                checkBoxCSolo_Click(checkBoxCSolo,EventArgs.Empty);
            }
            else if (configurations[0] == "DEUX")
            {
                checkBoxCSolo_Click(checkBoxC2, EventArgs.Empty);

            }
            else if (configurations[0] == "AI")
            {
                checkBoxCSolo_Click(checkBoxCAI, EventArgs.Empty);

            }
            for (int i = 1; i < configurations.Length; i++)
            {
                if (File.Exists(Application.StartupPath + @"\zones\" + configurations[i] + ".xml"))
                {
                    CampaignPathMap = new StringBuilder(Application.StartupPath + @"\zones\" + configurations[i] + ".xml");
                    int diff = FonctionsNatives.obtenirDifficulte(CampaignPathMap, CampaignPathMap.Capacity);
                    var item1 = new ListViewItem(new[] { configurations[i], diff.ToString() });
                    CampaignSelectedListView.Items.Add(item1);
                }
                else
                {
                    pathMap = new StringBuilder(Application.StartupPath + @"\zones\default.xml");
                    int diff = FonctionsNatives.obtenirDifficulte(pathMap, pathMap.Capacity);
                    var item1 = new ListViewItem(new[] { "default", diff.ToString() });
                    CampaignSelectedListView.Items.Add(item1);
                }
            }

            // Enables button at start, for lulz
            if (CampaignSelectedListView.Items.Count >= 2)
            {
                campaignStartBtn.Enabled = true;
            }
            CampaignRemoveItemBtn.Enabled = true;


            CampaignPanel.Location = new Point(
                  CampaignPanel.Parent.Width / 2 - CampaignPanel.Size.Width / 2,
              CampaignPanel.Parent.Height / 2 - CampaignPanel.Size.Height / 2);
            CampaignPanel.Anchor = AnchorStyles.None;
        }

        private void CampaignZonesListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (CampaignZonesListView.SelectedIndices.Count <= 0) return;
            int index = CampaignZonesListView.SelectedIndices[0];
            if (index >= 0)
            {
                CampaignFileName = CampaignZonesListView.Items[index].Text;
                CampaignScreenShotBox.SizeMode = PictureBoxSizeMode.StretchImage;
                if (File.Exists(Application.StartupPath + @"\zones\" + CampaignFileName + ".jpg"))
                {
                    CampaignScreenShotBox.Image = Image.FromFile(Application.StartupPath + @"\zones\" + CampaignFileName + ".jpg");
                }
                else
                {
                    CampaignScreenShotBox.Image = Properties.Resources.SaintTrinity;
                }
                campaignStartBtn.Enabled = true;
            }
        }

        private void CampaignSelectedListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (CampaignSelectedListView.SelectedIndices.Count <= 0) return;
            int index = CampaignSelectedListView.SelectedIndices[0];
            if (index >= 0)
            {
                CampaignFileName = CampaignSelectedListView.Items[index].Text;
                CampaignScreenShotBox.SizeMode = PictureBoxSizeMode.StretchImage;
                if (File.Exists(Application.StartupPath + @"\zones\" + CampaignFileName + ".jpg"))
                {
                    CampaignScreenShotBox.Image = Image.FromFile(Application.StartupPath + @"\zones\" + fileNames + ".jpg");
                }
                else
                {
                    CampaignScreenShotBox.Image = Properties.Resources.SaintTrinity;
                }
                campaignStartBtn.Enabled = true;
            }
        }



        private void campaignCancelBtn_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = MainTab;
            MainTab.Focus();
            MainPanel.Visible = false;
            SinglePlayerPanel.Visible = true;
        }

        private void campaignStartBtn_Click(object sender, EventArgs e)
        {
            if (CampaignSelectedListView.Items.Count < 2)
            {
                MessageBox.Show("Vous ne pouvez pas lancer une campagne avec moins de 2 zones!", "ERREUR DE LANCEMENT",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            else
            {
               
                int i = 0;
                foreach (ListViewItem eachItem in CampaignSelectedListView.Items)
                {
                    mapList.Append(eachItem.Text + " ");
                    zonesCampagne.Insert(i, Application.StartupPath + @"\zones\" + eachItem.Text + ".xml");
                    i++;

                }
                mapList.Length--;
                FonctionsNatives.creerFichierCampagne(mapList, mapList.Capacity);

                ZoneInfo zi = new ZoneInfo(CampaignSelectedListView.Items[0].Text, CampaignSelectedListView.Items[0].SubItems[1].Text, false);
                this.Hide();
                zi.ShowDialog();
                if (CtimeAttackCBox.Checked)
                {
                    Ctime = Convert.ToInt32(CtimeLabel.Text);
                }
                LancerModeJeu(zonesCampagne, campaignPlayerType,Ctime,CinstaDeathCBox.Checked);



            }
        }



        private void CampaignRemoveItemBtn_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem eachItem in CampaignSelectedListView.SelectedItems)
            {
                CampaignSelectedListView.Items.Remove(eachItem);
            }
            if (CampaignSelectedListView.Items.Count < 2)
            {
                campaignStartBtn.Enabled = false;
            }
        }

        private void CampaignEmptyBtn_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem eachItem in CampaignSelectedListView.Items)
            {
                CampaignSelectedListView.Items.Remove(eachItem);
            }
            campaignStartBtn.Enabled = false;
            CampaignRemoveItemBtn.Enabled = false;
        }




        private void CampaignAddBtn_Click(object sender, EventArgs e)
        {
            CampaignPathMap = new StringBuilder(Application.StartupPath + @"\zones\" + fileNames + ".xml");
            int diff = FonctionsNatives.obtenirDifficulte(CampaignPathMap, pathMap.Capacity);
            var item1 = new ListViewItem(new[] { CampaignFileName, diff.ToString() });

            CampaignSelectedListView.Items.Add(item1);
            if (CampaignSelectedListView.Items.Count < 2)
            {
                campaignStartBtn.Enabled = false;
            }
            else
            {
                campaignStartBtn.Enabled = true;
            }
            CampaignRemoveItemBtn.Enabled = true;
        }




        private void checkBoxCSolo_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.CheckBox checkedBox = (System.Windows.Forms.CheckBox)sender;

            if (checkedBox.Name == checkBoxCSolo.Name)
            {
                campaignPlayerType = 1;
                mapList = new StringBuilder("UN ");
                checkBoxCSolo.Checked = true;
                checkBoxCSolo.BackgroundImage = Properties.Resources.buttonStock1h;
                checkBoxC2.Checked = false;
                checkBoxC2.BackgroundImage = smallBorder;
                checkBoxCAI.Checked = false;
                checkBoxCAI.BackgroundImage = smallBorder;


            }
            else if (checkedBox.Name == checkBoxC2.Name)
            {
                campaignPlayerType = 2;
                mapList = new StringBuilder("DEUX ");
                checkBoxC2.Checked = true;
                checkBoxC2.BackgroundImage = Properties.Resources.buttonStock1h;
                checkBoxCSolo.Checked = false;
                checkBoxCSolo.BackgroundImage = smallBorder;
                checkBoxCAI.Checked = false;
                checkBoxCAI.BackgroundImage = smallBorder;
            }
            else if (checkedBox.Name == checkBoxCAI.Name)
            {
                campaignPlayerType = 3;
                mapList = new StringBuilder("AI ");
                checkBoxCAI.Checked = true;
                checkBoxCAI.BackgroundImage = Properties.Resources.buttonStock1h;
                checkBoxCSolo.Checked = false;
                checkBoxCSolo.BackgroundImage = smallBorder;
                checkBoxC2.Checked = false;
                checkBoxC2.BackgroundImage = smallBorder;
            }
        }



        #region GameModes

        private void CinstaDeathCBox_CheckedChanged(object sender, EventArgs e)
        {
            if (CinstaDeathCBox.Checked)
            {
                CinstaDeathCBox.BackgroundImage = Properties.Resources.buttonStock1h;
                CinstaDeathCBox.Text = "✓";
            }
            else
            {
                CinstaDeathCBox.Text = "";
                CinstaDeathCBox.BackgroundImage = smallBorder;

            }
        }


        private void CtimeAttackCBox_CheckedChanged(object sender, EventArgs e)
        {
            if (CtimeAttackCBox.Checked)
            {
                CtimeAttackCBox.BackgroundImage = Properties.Resources.buttonStock1h;
                CtimeAttackCBox.Text = "✓";
                CSetUpTimeButtons(true);
            }
            else
            {
                CtimeAttackCBox.Text = "";
                CtimeAttackCBox.BackgroundImage = smallBorder;
                CSetUpTimeButtons(false);
            }
        }


        private void CminusBtn_Click(object sender, EventArgs e)
        {
            Ctime = Convert.ToInt32(CtimeLabel.Text);
            if (Ctime > 1)
            {
                Ctime--;
                if (Ctime == 1)
                {
                    CminusBtn.Enabled = false;
                }
                CplusBtn.Enabled = true;
                CtimeLabel.Text = Ctime.ToString();
            }
        }

        private void CplusBtn_Click(object sender, EventArgs e)
        {
            Ctime = Convert.ToInt32(CtimeLabel.Text);
            if (Ctime < 10)
            {
                Ctime++;
                if (Ctime == 10)
                {
                    CplusBtn.Enabled = false;
                }
                CminusBtn.Enabled = true;
                CtimeLabel.Text = Ctime.ToString();
            }
        }

        private void CSetUpTimeButtons(bool activate)
        {
            CminusBtn.Enabled = activate;
            CplusBtn.Enabled = activate;
            CtimeLabel.Enabled = activate;
            CtimeLimitLabel.Enabled = activate;
        }

        #endregion


    }
}
