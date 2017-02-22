using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Media;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InterfaceGraphique.Fenetres
{
    public partial class AchievementForm : Form
    {
        bool starting;
        int i = 0;
        public AchievementForm(string achName, int achPoints,int counter = 1)
        {
            InitializeComponent();
            this.Location = new Point(Screen.PrimaryScreen.WorkingArea.Width/2 -Width/2, Screen.PrimaryScreen.WorkingArea.Bottom - this.Height*counter);
            starting = true;
            pointsLabel.Text = achPoints.ToString();
            titleLabel.Text = achName;
            Opacity = 0.0;
            Program.player = new SoundPlayer(Properties.Resources.AIRPORN);
            Program.player.Play();
            AchTimer.Start();
        }

        private void AchTimer_Tick(object sender, EventArgs e)
        {
            if (starting)
            {
                Opacity += 0.015;
                if (Opacity >= 1)
                {
                    starting = false;
                }
            }
            else if (Opacity >= 1)
            {
                i++;
                if (i == 100)
                {
                    i = 0;
                    Opacity =0.99;
                }
            }
            else
            {
                Opacity -= 0.01;
                if (Opacity == 0)
                {
                    ((MenuComplet)Owner).achievementCounter--;
                    if (((MenuComplet) Owner).achievementCounter < 0)
                    {
                        ((MenuComplet) Owner).achievementCounter = 0;
                    }
                    Close();

                }
            }
        }
    }
}
