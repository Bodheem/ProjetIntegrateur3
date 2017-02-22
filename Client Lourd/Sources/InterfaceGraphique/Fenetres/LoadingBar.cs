using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Fenetres
{
    public partial class LoadingBar : Form
    {
        /* For the Children
        
        [DllImport("Gdi32.dll", EntryPoint = "CreateRoundRectRgn")]
        private static extern IntPtr CreateRoundRectRgn
        (
            int nLeftRect, // x-coordinate of upper-left corner
            int nTopRect, // y-coordinate of upper-left corner
            int nRightRect, // x-coordinate of lower-right corner
            int nBottomRect, // y-coordinate of lower-right corner
            int nWidthEllipse, // height of ellipse
            int nHeightEllipse // width of ellipse
         );
        */

        string[] usine;
        int percentage;
        int image;
        Bitmap myImage;
        public LoadingBar()
        {
            InitializeComponent();

            this.ClientSize = Screen.PrimaryScreen.Bounds.Size;
            // Background sauve en memoire
            Bitmap myImage = new Bitmap(Properties.Resources.GenericBackground);
            BackgroundImage = myImage;
            BackgroundImageLayout = ImageLayout.Stretch;
            WindowState = FormWindowState.Maximized;
            AllowTransparency = true;
            StartPosition = FormStartPosition.CenterScreen;
            LoadingPanel.Width = (int)((double)Screen.PrimaryScreen.WorkingArea.Width*0.8);
            LoadingPanel.Location = new Point(
                Width/2 - LoadingPanel.Width/2,
                Height - LoadingPanel.Height - 20);
            //Region = System.Drawing.Region.FromHrgn(CreateRoundRectRgn(0, 0, Width, Height, 20, 20));

            usine = System.IO.File.ReadAllLines(Application.StartupPath + @"\media\objets\liste.txt");
            percentage = 0;

        }

        public void populateLoadingBar()
        {
            for (int i = 0; i < usine.Length; i++)
            {
                StringBuilder monUsine = new StringBuilder(usine[i]);
                percentage = Convert.ToInt32(i*100.0/usine.Length);
                //Console.WriteLine(percentage);
                LoadingLabel.Text = percentage.ToString() + "%";
                System.Windows.Forms.PictureBox pb = new PictureBox();
                pb.BorderStyle = BorderStyle.None;
                myImage = new Bitmap(Properties.Resources.Trophy);
                pb.BackgroundImage = myImage;
                pb.BackgroundImageLayout = ImageLayout.Stretch;
                pb.Visible = true;
                pb.Size = new Size(LoadingPanel.Width / (usine.Length + 1 ), LoadingPanel.Height);
                pb.Dock = DockStyle.Left;
                LoadingPanel.Controls.Add(pb);
                Refresh();
                //Console.WriteLine(" ajout de l'usine " + usine[i].ToString());
                FonctionsNatives.preparerUsineArbre(monUsine, monUsine.Capacity);

            }

            // Charger la zone de jeu par défaut
            FonctionsNatives.chargerZone(Outils.zoneDefaut, Outils.zoneDefaut.Length);
            //Close();

        }

        public void startSound()
        {
            FonctionsNatives.initialiserSon();
            Close();
        }
        private void LoadingBar_Shown(object sender, EventArgs e)
        {
      
        }


    }
}
