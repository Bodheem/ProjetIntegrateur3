using System;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.Runtime.InteropServices;
using System.Threading;
using InterfaceGraphique.Langages;

using System.Windows.Forms;

namespace InterfaceGraphique
{
    partial class MenuComplet
    {
        int[] defaultValues = { 65, 83, 52, 53 };
        int[] currentValues = { 65, 83, 52, 53, 32, 49, 50, 74, 75, 76, 66, 84 };
        int[] valuesXML = new int[14];
        int nbBilles = 3;
        string maTouche;

        private void SetUpOptionsMenu()
        {
            OptionsMainPanel.Location = new Point(
                   OptionsMainPanel.Parent.Width / 2 - OptionsMainPanel.Size.Width / 2,
               OptionsMainPanel.Parent.Height / 2 - OptionsMainPanel.Size.Height / 2);
            OptionsMainPanel.Anchor = AnchorStyles.None;

           // InitialiserTouches();
           InitialiserAvecBinaire();
        }

        private void CheckBox_CheckChanged(object sender, EventArgs e)
        {
            System.Windows.Forms.CheckBox checkedBox = (System.Windows.Forms.CheckBox)sender;

           
            Program.CheckBoxChecked((System.Windows.Forms.CheckBox)sender, smallBorder);
            if (checkedBox == DebugCBox)
            {
                if (!DebugCBox.Checked)
                {
                    checkBoxEnable(false);
                }
                else
                {
                    checkBoxEnable(true);
                }
            }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void radioButtonEnable(bool active)
        /// @brief Active ou desactive les Radio Buttons.
        /// @param[in] active : Numero de config a obtenir.
        /// @return Vrai si le controle est effectue.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void checkBoxEnable(bool active)
        {
            //MDBCBox.Enabled = active;
            //FSPCBox.Enabled = active;
            GBilleCBox.Enabled = active;
            VitesseCBox.Enabled = active;
            EclairageCBox.Enabled = active;
            PortailsCBox.Enabled = active;

            if (!active)
            {
              
                GBilleLabel.ForeColor = Color.Gray;
                VitesseLabel.ForeColor = Color.Gray;
                EclairageLabel.ForeColor = Color.Gray;
                PortailsLabel.ForeColor = Color.Gray;

            }
            else
            {
               
                GBilleLabel.ForeColor = Color.Gold;
                VitesseLabel.ForeColor = Color.Gold;
                EclairageLabel.ForeColor = Color.Gold;
                PortailsLabel.ForeColor = Color.Gold;
            }
        }

        private void NBillesCBoxChanged(object sender, EventArgs e)
        {
            System.Windows.Forms.CheckBox checkedBox = (System.Windows.Forms.CheckBox)sender;

            if (checkedBox.Name == Billes3CBox.Name)
            {
                nbBilles = 3;
                Billes3CBox.Checked = true;
                Billes3CBox.BackgroundImage = Properties.Resources.buttonStock1h;
                Billes5CBox.Checked = false;
                Billes5CBox.BackgroundImage = smallBorder;
                Billes7CBox.Checked = false;
                Billes7CBox.BackgroundImage = smallBorder;


            }
            else if (checkedBox.Name == Billes5CBox.Name)
            {
                nbBilles = 5;
                Billes5CBox.Checked = true;
                Billes5CBox.BackgroundImage = Properties.Resources.buttonStock1h;
                Billes3CBox.Checked = false;
                Billes3CBox.BackgroundImage = smallBorder;
                Billes7CBox.Checked = false;
                Billes7CBox.BackgroundImage = smallBorder;
            }
            else if (checkedBox.Name == Billes7CBox.Name)
            {
                nbBilles = 7;
                Billes7CBox.Checked = true;
                Billes7CBox.BackgroundImage = Properties.Resources.buttonStock1h;
                Billes5CBox.Checked = false;
                Billes5CBox.BackgroundImage = smallBorder;
                Billes3CBox.Checked = false;
                Billes3CBox.BackgroundImage = smallBorder;
            }

        }

        private void ReturnBtn_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = MainTab;
            MainTab.Focus();
        }

        private void AcceptBtn_Click(object sender, EventArgs e)
        {
            tabControl1.SelectedTab = MainTab;
            MainTab.Focus();
            //TODO: code pour set les proprietes

            for (int i = 0; i < 5; i++)
                valuesXML[i] = currentValues[i];

            valuesXML[5] = nbBilles;
            valuesXML[6] = Convert.ToInt32(MDBCBox.Checked);
            valuesXML[7] = Convert.ToInt32(FSPCBox.Checked);
            valuesXML[8] = Convert.ToInt32(GBilleCBox.Checked);
            valuesXML[9] = Convert.ToInt32(VitesseCBox.Checked);
            valuesXML[10] = Convert.ToInt32(EclairageCBox.Checked);
            valuesXML[11] = Convert.ToInt32(PortailsCBox.Checked);
            valuesXML[12] = Convert.ToInt32(DebugCBox.Checked);
            valuesXML[13] = Convert.ToInt32(smartAICBox.Checked);
            foreach (var configs in valuesXML)
            {
                Console.WriteLine(configs);   
            }
            FonctionsNatives.creerFichierConfig(valuesXML);
            Langage.SaveLangagePreference();


            Thread.CurrentThread.CurrentCulture = Langage.getCultureInfo();
            Thread.CurrentThread.CurrentUICulture = Langage.getCultureInfo();
            ChangeLanguage(Langage.getCultureInfo());
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private bool isValid(int touche)
        /// @brief Verifie si la touche choisie est valide.
        /// @param[in] touche : Touche appuyee.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private bool isValid(int touche)
        {
            if (touche >= 96 && touche <= 105)
                return true;
            if ((touche >= 65 && touche <= 90) || (touche >= 48 && touche <= 57) || (touche == 32))
            {
                foreach (int x in currentValues)
                {
                    if (x.Equals(touche))
                    {
                        label_Rebind.Text = "Touche deja utilisée";
                        //Console.WriteLine("Touche deja utilise");
                        return false;
                    }
                }
                return true;
            }
            else
            {
                label_Rebind.Text = "Touche invalide";
                return false;
            }

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void InitialiserAvecBinaire()
        /// @brief Initialisation des touches.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void InitialiserTouches()
        {
            maTouche = char.ConvertFromUtf32(currentValues[0]);
            if (currentValues[0] >= 96 && currentValues[0] <= 105)
                maTouche = "NumPad" + char.ConvertFromUtf32(currentValues[0] - 48);
            if (maTouche == " ")
                maTouche = "Espace";

            PGJ1_bouton.Text = maTouche;

            maTouche = char.ConvertFromUtf32(currentValues[1]);
            if (currentValues[1] >= 96 && currentValues[1] <= 105)
                maTouche = "NumPad" + char.ConvertFromUtf32(currentValues[1] - 48);
            if (maTouche == " ")
                maTouche = "Espace";
            PDJ1_bouton.Text = maTouche;

            maTouche = char.ConvertFromUtf32(currentValues[2]);
            if (currentValues[2] >= 96 && currentValues[2] <= 105)
                maTouche = "NumPad" + char.ConvertFromUtf32(currentValues[2] - 48);
            if (maTouche == " ")
                maTouche = "Espace";
            PGJ2_bouton.Text = maTouche;

            maTouche = char.ConvertFromUtf32(currentValues[3]);
            if (currentValues[3] >= 96 && currentValues[3] <= 105)
                maTouche = "NumPad" + char.ConvertFromUtf32(currentValues[3] - 48);
            if (maTouche == " ")
                maTouche = "Espace";
            PDJ2_bouton.Text = maTouche;

            maTouche = char.ConvertFromUtf32(currentValues[4]);
            if (currentValues[4] >= 96 && currentValues[4] <= 105)
                maTouche = "NumPad" + char.ConvertFromUtf32(currentValues[4] - 48);
            if (maTouche == " ")
                maTouche = "Espace";
            Ressort_bouton.Text = maTouche;
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void InitialiserAvecBinaire()
        /// @brief Initialisation des configurations par defaut a l'aide d'un fichier binaire.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void InitialiserAvecBinaire()
        {
            EventArgs e;
            IntPtr config = FonctionsNatives.chargerFichierConfiguration();
            int[] result = new int[14];
            Marshal.Copy(config, valuesXML, 0, 14);

            for (int i = 0; i < 5; i++)
            {
                currentValues[i] = valuesXML[i];

            }
            InitialiserTouches();

            switch (valuesXML[5])
            {
                case 3:
                   Billes3CBox.Checked = true;
                    Billes3CBox.BackgroundImage = Properties.Resources.buttonStock1h;
                    Billes5CBox.Checked = false;
                    Billes5CBox.BackgroundImage = smallBorder;
                    Billes7CBox.Checked = false;
                    Billes7CBox.BackgroundImage = smallBorder;
                    break;
                case 5:
                    Billes5CBox.Checked = true;
                    Billes5CBox.BackgroundImage = Properties.Resources.buttonStock1h;
                    Billes3CBox.Checked = false;
                    Billes3CBox.BackgroundImage = smallBorder;
                    Billes7CBox.Checked = false;
                    Billes7CBox.BackgroundImage = smallBorder;
                    break;
                case 7:
                    Billes7CBox.Checked = true;
                    Billes7CBox.BackgroundImage = Properties.Resources.buttonStock1h;
                    Billes5CBox.Checked = false;
                    Billes5CBox.BackgroundImage = smallBorder;
                    Billes3CBox.Checked = false;
                    Billes3CBox.BackgroundImage = smallBorder;
                    break;
            }
           
            //valuesXML[6] = Convert.ToInt32(MDB_OK.Checked);
            if (valuesXML[6] != 0)
                MDBCBox.Checked = true;
           

            //valuesXML[7] = Convert.ToInt32(FRS_OK.Checked);
            if (valuesXML[7] != 0)
                FSPCBox.Checked = true;
           
            //valuesXML[8] = Convert.ToInt32(GB_OK.Checked);
            if (valuesXML[8] != 0)
                GBilleCBox.Checked = true;
          

            //valuesXML[9] = Convert.ToInt32(VAC_OK.Checked);
            if (valuesXML[9] != 0)
                VitesseCBox.Checked = true;
         

            //valuesXML[10] = Convert.ToInt32(AE_OK.Checked);
            if (valuesXML[10] != 0)
                EclairageCBox.Checked = true;
         

            //valuesXML[11] = Convert.ToInt32(PORTAL_OK.Checked);    
            if (valuesXML[11] != 0)
                PortailsCBox.Checked = true;
           

            if (valuesXML[12] != 0)
            {
                DebugCBox.Checked = true;

            }

            if (valuesXML[13] != 0)
            {
                smartAICBox.Checked = true;
            }
           
            /*
            */
        }
        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PGJ1_bouton_KeyDown(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on entre une touche au clavier sur
        ///        un bouton de palette.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PGJ1_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            int touche = e.KeyValue;
            if (this.isValid(touche) == true)
            {
                currentValues[0] = touche;
                maTouche = char.ConvertFromUtf32(touche);
                if (maTouche == " ")
                    maTouche = "Espace";
                if (touche >= 96 && touche <= 105)
                    PGJ1_bouton.Text = "NumPad" + char.ConvertFromUtf32(touche - '0');
                else
                    PGJ1_bouton.Text = maTouche;
            }


        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PDJ1_bouton_KeyDown(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on entre une touche au clavier sur
        ///        un bouton de palette.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PDJ1_bouton_KeyDown(object sender, KeyEventArgs e)
        {

            int touche = e.KeyValue;
            // Console.WriteLine(e.KeyData.ToString());
            // Console.WriteLine(touche);
            if (this.isValid(touche) == true)
            {
                currentValues[1] = touche;
                maTouche = char.ConvertFromUtf32(touche);
                if (maTouche == " ")
                    maTouche = "Espace";
                if (touche >= 96 && touche <= 105)
                    PDJ1_bouton.Text = "NumPad" + char.ConvertFromUtf32(touche - '0');
                else
                    PDJ1_bouton.Text = maTouche;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PGJ2_bouton_KeyDown(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on entre une touche au clavier sur
        ///        un bouton de palette.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PGJ2_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            int touche = e.KeyValue;
            if (this.isValid(touche) == true)
            {
                maTouche = char.ConvertFromUtf32(touche);
                currentValues[2] = touche;
                if (maTouche == " ")
                    maTouche = "Espace";
                if (touche >= 96 && touche <= 105)
                    PGJ2_bouton.Text = "NumPad" + char.ConvertFromUtf32(touche - '0');
                else
                    PGJ2_bouton.Text = maTouche;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void PDJ2_bouton_KeyDown(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on entre une touche au clavier sur
        ///        un bouton de palette.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void PDJ2_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            int touche = e.KeyValue;
            if (this.isValid(touche) == true)
            {
                currentValues[3] = touche;
                maTouche = char.ConvertFromUtf32(touche);
                if (maTouche == " ")
                    maTouche = "Espace";
                if (touche >= 96 && touche <= 105)
                    PDJ2_bouton.Text = "NumPad" + char.ConvertFromUtf32(touche - '0');
                else
                    PDJ2_bouton.Text = maTouche;
            }
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void Ressort_bouton_KeyDown(object sender, EventArgs e)
        /// @brief Gestion d'evenement lorsqu'on entre une touche au clavier sur
        ///        le bouton de ressort.
        /// @param[in] sender : Objet duquel provient un evenement.
        /// @param[in] e : evenement qui lance la fonction.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void Ressort_bouton_KeyDown(object sender, KeyEventArgs e)
        {
            int touche = e.KeyValue;

            if (this.isValid(touche) == true)
            {
                currentValues[4] = touche;
                maTouche = char.ConvertFromUtf32(touche);
                if (maTouche == " ")
                    maTouche = "Espace";
                if (touche >= 96 && touche <= 105)
                    Ressort_bouton.Text = "NumPad" + char.ConvertFromUtf32(touche - '0');
                else
                    Ressort_bouton.Text = maTouche;
                
            }
        }

        private void Default_bouton_Click(object sender, EventArgs e)
        {
            PGJ1_bouton.Text = char.ConvertFromUtf32(defaultValues[0]);
            PDJ1_bouton.Text = char.ConvertFromUtf32(defaultValues[1]);
            PGJ2_bouton.Text = char.ConvertFromUtf32(defaultValues[2]);
            PDJ2_bouton.Text = char.ConvertFromUtf32(defaultValues[3]);
            Ressort_bouton.Text = "Espace";
            currentValues[0] = 65;
            currentValues[1] = 83;
            currentValues[2] = 52;
            currentValues[3] = 53;
            currentValues[4] = 32;
        }


        private void btnFrench_Click(object sender, EventArgs e)
        {
            btnFrench.FlatAppearance.BorderColor = Color.Gold;
            btnFrench.FlatAppearance.BorderSize = 2;
            btnEnglish.FlatAppearance.BorderSize = 0;

            Langage.setLangage("fr");
        }

        private void btnEnglish_Click(object sender, EventArgs e)
        {
            btnEnglish.FlatAppearance.BorderColor = Color.Gold;
            btnEnglish.FlatAppearance.BorderSize = 2;
            btnFrench.FlatAppearance.BorderSize = 0;

            Langage.setLangage("en");
        }

        private void ChangeLanguage(CultureInfo lang)
        {
            ComponentResourceManager resources = new ComponentResourceManager(typeof(MenuComplet));

            ApplyResourceToControl(resources, tabControl1, lang);
            resources.ApplyResources(this, "$this", lang);
        }

        private static void ApplyResourceToControl(ComponentResourceManager resources, Control control, CultureInfo lang)
        {
            foreach (Control c in control.Controls)
            {
                ApplyResourceToControl(resources, c, lang);
                
                string text = resources.GetString(c.Name + ".Text", lang);
                if (text != null)
                    c.Text = text;
            }
        }
    }
}
