//////////////////////////////////////////////////////////////////////////////
/// @file Proprietes.cs
/// @author Ballers
/// @date 2015-01-27
/// @version 1.0 
/// @ingroup Fenetres
//////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace InterfaceGraphique
{
    ///////////////////////////////////////////////////////////////////////////
    /// @class Proprietes
    /// @brief Fenetre des proprietes de la partie.
    ///
    /// @author The Ballers
    /// @date 2015-01-27
    /// 
    /// @ingroup Fenetres
    ///////////////////////////////////////////////////////////////////////////
    public partial class Proprietes : Form
    {
        string errorMessage = "";
        public Dictionary<string, string> Propriete;

        public static string mapId = "ID";
        public static string autheur = "Author";
        public static string lastModificationBy = "LastModificationBy";
        public static string version = "Version";
        public static string cost = "Cout";
        public static string pointButoir = "PointsButoir";
        public static string pointTriangulaire = "PointsTriangulaire";
        public static string pointCible = "PointsCible";
        public static string pointVictoire = "PointsVictoire";
        public static string pointBilleGratuite = "PointsBilleGratuite";
        public static string difficulte = "Difficulte";
        
        ////////////////////////////////////////////////////////////////////////
        /// @fn public Proprietes()
        /// @brief Constructeur par parameetre de la fenetre.
        /// param[in] a : Liste des proprietes a instancier.
        /// @return Aucune (constructeur).
        ////////////////////////////////////////////////////////////////////////
        public Proprietes(Dictionary<string, string> list)
        {
            InitializeComponent();
          
            Propriete = list;
            copyRightCBox.Visible = FonctionsNatives.isOnlineAccount();
            if (Propriete[autheur] == FonctionsNatives.getUserName() || Propriete[autheur] == "HORS-LIGNE" || Propriete[autheur] == "TEST")
            {
                copyRightCBox.Enabled = true;
            }
            else
            {
                copyRightCBox.Enabled = false;

            }
            ptsButCirc_Box.Text = Propriete[pointButoir];
            ptsButTri_Box.Text = Propriete[pointTriangulaire];
            ptsCible_Box.Text = Propriete[pointCible];
            ptsVictoire_Box.Text = Propriete[pointVictoire];
            ptsFreeBall_Box.Text = Propriete[pointBilleGratuite];
            difficulte_ComboBox.Text = Propriete[difficulte];
        }


        ////////////////////////////////////////////////////////////////////////
        /// @fn private bool checkValue()
        /// @brief Verifie que les valeurs entrees par l'utilisateur sont valides.
        /// @return True si les valeurs entrees sont valides, false sinon.
        ////////////////////////////////////////////////////////////////////////
        private bool checkValue()
        {
            int n;
            bool isValid = true;
          
            if( !(int.TryParse(ptsButCirc_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\nLa valeur des points pour un butoir circulaire est invalide";
            }
            else
            {
                if( (n <= 0) || (n > 10000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur des points pour un butoir circulaire est hors de la limite( 0 a 10000) ";
                }
                    
            }
            if (!(int.TryParse(ptsButTri_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\nLa valeur des points pour un butoir triangulaire est invalide";
            }
            else
            {
                if ((n <= 0) || (n > 10000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur des points pour un butoir triangulaire est hors la limite( 0 a 10000) ";
                }

            }
            if (!(int.TryParse(ptsCible_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\nLa valeur des points pour une cible est invalide";
            }
            else
            {
                if ((n <= 0) || (n > 10000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur des points pour une cible est hors la limite( 0 a 10000) ";
                }

            }
            if (!(int.TryParse(ptsVictoire_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\nLa valeur des points pour une victoire est invalide";
            }
            else
            {
                if ((n <= 0) || (n > 10000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur des points pour une victoire est hors la limite( 0 a 10000) ";
                }

            }
            if (!(int.TryParse(ptsFreeBall_Box.Text, out n)))
            {
                isValid = false;
                errorMessage += "\nLa valeur des points pour une balle gratuite est invalide";
            }
            else
            {
                if ((n <= 0) || (n > 10000))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur des points pour une balle gratuite est hors la limite( 0 a 10000) ";
                }

            }
            if (!(int.TryParse(difficulte_ComboBox.Text, out n)))
            {
                isValid = false;
                errorMessage += "\nLa valeur de la difficulte est invalide";
            }
            else
            {
                if ((n < 1) || (n > 10))
                {
                    isValid = false;
                    errorMessage += "\nLa valeur de difficulte est hors la limite(1 a 10) ";
                }
            }
            return isValid;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void propAnnuler_Bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Annuler.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void propAnnuler_Bouton_Click(object sender, EventArgs e)
        {
            this.Close();        
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn public List<int> getProps()
        /// @brief Accesseur de l'attribut des proprietes.
        /// 
        /// @return La liste des proprietes de jeu.
        ///
        ////////////////////////////////////////////////////////////////////////
        public Dictionary<string, string> getPropriete()
        {
            return Propriete;
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void propConfirm_Bouton_Click(object sender, EventArgs e)
        /// @brief Gestion des evenements lorsque l'utilisateur clique sur 
        ///        le bouton Confirmer.
        /// 
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void propConfirm_Bouton_Click(object sender, EventArgs e)
        {
            if (checkValue())
            {
                Propriete[pointButoir] = ptsButCirc_Box.Text;
                Propriete[pointTriangulaire] = ptsButTri_Box.Text;
                Propriete[pointCible] = ptsCible_Box.Text;
                Propriete[pointVictoire] = ptsVictoire_Box.Text;
                Propriete[pointBilleGratuite] = ptsFreeBall_Box.Text;
                Propriete[difficulte] = difficulte_ComboBox.Text;
                if (copyRightCBox.Checked)
                {
                    Propriete[autheur] = FonctionsNatives.getUserName();
                }
                else
                {
                    Propriete[autheur] = "HORS-LIGNE";
                    // fucking yonni
                }
                this.Hide();
            }
            else
            {
                MessageBox.Show(errorMessage, "Valeurs incorrectes",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
                errorMessage = "";
            }
        }        
    }
}
