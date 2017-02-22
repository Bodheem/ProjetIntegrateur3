namespace InterfaceGraphique
{
    partial class PartieTerminee
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PartieTerminee));
            this.boutonRecommencer = new System.Windows.Forms.Button();
            this.boutonMenuP = new System.Windows.Forms.Button();
            this.EndLabel = new System.Windows.Forms.Label();
            this.partieTerminePanel = new System.Windows.Forms.Panel();
            this.victoryImage = new System.Windows.Forms.PictureBox();
            this.partieTerminePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.victoryImage)).BeginInit();
            this.SuspendLayout();
            // 
            // boutonRecommencer
            // 
            this.boutonRecommencer.BackColor = System.Drawing.Color.Transparent;
            this.boutonRecommencer.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("boutonRecommencer.BackgroundImage")));
            this.boutonRecommencer.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.boutonRecommencer.FlatAppearance.BorderSize = 0;
            this.boutonRecommencer.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.boutonRecommencer.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.boutonRecommencer.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.boutonRecommencer.ForeColor = System.Drawing.Color.Gold;
            this.boutonRecommencer.Location = new System.Drawing.Point(12, 314);
            this.boutonRecommencer.Name = "boutonRecommencer";
            this.boutonRecommencer.Size = new System.Drawing.Size(300, 100);
            this.boutonRecommencer.TabIndex = 0;
            this.boutonRecommencer.Text = "Recommencer";
            this.boutonRecommencer.UseVisualStyleBackColor = false;
            this.boutonRecommencer.Click += new System.EventHandler(this.boutonRecommencer_Click);
            this.boutonRecommencer.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.boutonRecommencer.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.boutonRecommencer.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.boutonRecommencer.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // boutonMenuP
            // 
            this.boutonMenuP.BackColor = System.Drawing.Color.Transparent;
            this.boutonMenuP.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("boutonMenuP.BackgroundImage")));
            this.boutonMenuP.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.boutonMenuP.FlatAppearance.BorderSize = 0;
            this.boutonMenuP.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.boutonMenuP.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.boutonMenuP.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.boutonMenuP.ForeColor = System.Drawing.Color.Gold;
            this.boutonMenuP.Location = new System.Drawing.Point(12, 208);
            this.boutonMenuP.Name = "boutonMenuP";
            this.boutonMenuP.Size = new System.Drawing.Size(300, 100);
            this.boutonMenuP.TabIndex = 1;
            this.boutonMenuP.Text = "Retourner au menu principal";
            this.boutonMenuP.UseVisualStyleBackColor = false;
            this.boutonMenuP.Click += new System.EventHandler(this.boutonMenuP_Click);
            this.boutonMenuP.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.boutonMenuP.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.boutonMenuP.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.boutonMenuP.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // EndLabel
            // 
            this.EndLabel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.EndLabel.AutoSize = true;
            this.EndLabel.BackColor = System.Drawing.Color.Transparent;
            this.EndLabel.ForeColor = System.Drawing.Color.Gold;
            this.EndLabel.Location = new System.Drawing.Point(280, 151);
            this.EndLabel.Name = "EndLabel";
            this.EndLabel.Size = new System.Drawing.Size(61, 13);
            this.EndLabel.TabIndex = 4;
            this.EndLabel.Text = "YOU LOST";
            this.EndLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // partieTerminePanel
            // 
            this.partieTerminePanel.BackColor = System.Drawing.Color.Black;
            this.partieTerminePanel.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.partieTerminePanel.Controls.Add(this.victoryImage);
            this.partieTerminePanel.Controls.Add(this.EndLabel);
            this.partieTerminePanel.Controls.Add(this.boutonMenuP);
            this.partieTerminePanel.Controls.Add(this.boutonRecommencer);
            this.partieTerminePanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.partieTerminePanel.Location = new System.Drawing.Point(0, 0);
            this.partieTerminePanel.Name = "partieTerminePanel";
            this.partieTerminePanel.Size = new System.Drawing.Size(970, 681);
            this.partieTerminePanel.TabIndex = 5;
            // 
            // victoryImage
            // 
            this.victoryImage.Image = global::InterfaceGraphique.Properties.Resources.spookyGif;
            this.victoryImage.Location = new System.Drawing.Point(530, 257);
            this.victoryImage.Name = "victoryImage";
            this.victoryImage.Size = new System.Drawing.Size(300, 330);
            this.victoryImage.TabIndex = 5;
            this.victoryImage.TabStop = false;
            // 
            // PartieTerminee
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(970, 681);
            this.Controls.Add(this.partieTerminePanel);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = global::InterfaceGraphique.Properties.Resources.Pinball;
            this.MaximizeBox = false;
            this.Name = "PartieTerminee";
            this.Text = "Fin de Partie";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.PartieTerminee_FormClosing);
            this.Shown += new System.EventHandler(this.PartieTerminee_Shown);
            this.partieTerminePanel.ResumeLayout(false);
            this.partieTerminePanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.victoryImage)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button boutonRecommencer;
        private System.Windows.Forms.Button boutonMenuP;
        private System.Windows.Forms.Label EndLabel;
        private System.Windows.Forms.Panel partieTerminePanel;
        private System.Windows.Forms.PictureBox victoryImage;
    }
}