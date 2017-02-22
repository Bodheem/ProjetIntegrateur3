namespace InterfaceGraphique
{
    partial class ModeJeu
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ModeJeu));
            this.panel_GL = new System.Windows.Forms.Panel();
            this.InfoPanel = new System.Windows.Forms.FlowLayoutPanel();
            this.label_Titre = new System.Windows.Forms.Label();
            this.label_Nom = new System.Windows.Forms.Label();
            this.Player1 = new System.Windows.Forms.Label();
            this.points1 = new System.Windows.Forms.Label();
            this.Player2 = new System.Windows.Forms.Label();
            this.points2 = new System.Windows.Forms.Label();
            this.Player3 = new System.Windows.Forms.Label();
            this.points3 = new System.Windows.Forms.Label();
            this.Player4 = new System.Windows.Forms.Label();
            this.points4 = new System.Windows.Forms.Label();
            this.MultiPlayerLabel = new System.Windows.Forms.Label();
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.fichier_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mPrincipal_menu = new System.Windows.Forms.ToolStripMenuItem();
            this.Camera_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Ortho_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Orbitale_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.QuitMPGameBtn = new System.Windows.Forms.Button();
            this.panel_GL.SuspendLayout();
            this.InfoPanel.SuspendLayout();
            this.menuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel_GL
            // 
            this.panel_GL.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.panel_GL.BackColor = System.Drawing.Color.Transparent;
            this.panel_GL.Controls.Add(this.InfoPanel);
            this.panel_GL.Controls.Add(this.MultiPlayerLabel);
            this.panel_GL.Controls.Add(this.menuStrip);
            this.panel_GL.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel_GL.Location = new System.Drawing.Point(0, 0);
            this.panel_GL.Name = "panel_GL";
            this.panel_GL.Size = new System.Drawing.Size(784, 733);
            this.panel_GL.TabIndex = 4;
            this.panel_GL.SizeChanged += new System.EventHandler(this.panel_GL_SizeChanged);
            this.panel_GL.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseDown);
            this.panel_GL.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseMove);
            this.panel_GL.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseUp);
            // 
            // InfoPanel
            // 
            this.InfoPanel.BackColor = System.Drawing.Color.Transparent;
            this.InfoPanel.BackgroundImage = global::InterfaceGraphique.Properties.Resources.testBlack;
            this.InfoPanel.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.InfoPanel.Controls.Add(this.label_Titre);
            this.InfoPanel.Controls.Add(this.label_Nom);
            this.InfoPanel.Controls.Add(this.Player1);
            this.InfoPanel.Controls.Add(this.points1);
            this.InfoPanel.Controls.Add(this.Player2);
            this.InfoPanel.Controls.Add(this.points2);
            this.InfoPanel.Controls.Add(this.Player3);
            this.InfoPanel.Controls.Add(this.points3);
            this.InfoPanel.Controls.Add(this.Player4);
            this.InfoPanel.Controls.Add(this.points4);
            this.InfoPanel.Controls.Add(this.QuitMPGameBtn);
            this.InfoPanel.ForeColor = System.Drawing.Color.Gold;
            this.InfoPanel.Location = new System.Drawing.Point(182, 145);
            this.InfoPanel.Name = "InfoPanel";
            this.InfoPanel.Size = new System.Drawing.Size(389, 163);
            this.InfoPanel.TabIndex = 5;
            this.InfoPanel.Visible = false;
            // 
            // label_Titre
            // 
            this.label_Titre.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label_Titre.Location = new System.Drawing.Point(3, 0);
            this.label_Titre.Name = "label_Titre";
            this.label_Titre.Size = new System.Drawing.Size(187, 23);
            this.label_Titre.TabIndex = 0;
            this.label_Titre.Text = "SCORES";
            this.label_Titre.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label_Nom
            // 
            this.label_Nom.ForeColor = System.Drawing.Color.Gold;
            this.label_Nom.Location = new System.Drawing.Point(196, 0);
            this.label_Nom.Name = "label_Nom";
            this.label_Nom.Size = new System.Drawing.Size(187, 23);
            this.label_Nom.TabIndex = 18;
            this.label_Nom.Text = "Nom de la zone:";
            this.label_Nom.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Player1
            // 
            this.Player1.ForeColor = System.Drawing.Color.Gold;
            this.Player1.Location = new System.Drawing.Point(3, 23);
            this.Player1.Name = "Player1";
            this.Player1.Size = new System.Drawing.Size(82, 42);
            this.Player1.TabIndex = 1;
            this.Player1.Text = "Points:";
            this.Player1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // points1
            // 
            this.points1.ForeColor = System.Drawing.Color.Gold;
            this.points1.Location = new System.Drawing.Point(91, 23);
            this.points1.Name = "points1";
            this.points1.Size = new System.Drawing.Size(82, 42);
            this.points1.TabIndex = 2;
            this.points1.Text = "0";
            this.points1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Player2
            // 
            this.Player2.ForeColor = System.Drawing.Color.Gold;
            this.Player2.Location = new System.Drawing.Point(179, 23);
            this.Player2.Name = "Player2";
            this.Player2.Size = new System.Drawing.Size(82, 42);
            this.Player2.TabIndex = 19;
            this.Player2.Text = "Points:";
            this.Player2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // points2
            // 
            this.points2.ForeColor = System.Drawing.Color.Gold;
            this.points2.Location = new System.Drawing.Point(267, 23);
            this.points2.Name = "points2";
            this.points2.Size = new System.Drawing.Size(82, 42);
            this.points2.TabIndex = 20;
            this.points2.Text = "0";
            this.points2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Player3
            // 
            this.Player3.ForeColor = System.Drawing.Color.Gold;
            this.Player3.Location = new System.Drawing.Point(3, 65);
            this.Player3.Name = "Player3";
            this.Player3.Size = new System.Drawing.Size(82, 42);
            this.Player3.TabIndex = 21;
            this.Player3.Text = "Points:";
            this.Player3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // points3
            // 
            this.points3.ForeColor = System.Drawing.Color.Gold;
            this.points3.Location = new System.Drawing.Point(91, 65);
            this.points3.Name = "points3";
            this.points3.Size = new System.Drawing.Size(82, 42);
            this.points3.TabIndex = 22;
            this.points3.Text = "0";
            this.points3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Player4
            // 
            this.Player4.ForeColor = System.Drawing.Color.Gold;
            this.Player4.Location = new System.Drawing.Point(179, 65);
            this.Player4.Name = "Player4";
            this.Player4.Size = new System.Drawing.Size(82, 42);
            this.Player4.TabIndex = 23;
            this.Player4.Text = "Points:";
            this.Player4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // points4
            // 
            this.points4.ForeColor = System.Drawing.Color.Gold;
            this.points4.Location = new System.Drawing.Point(267, 65);
            this.points4.Name = "points4";
            this.points4.Size = new System.Drawing.Size(82, 42);
            this.points4.TabIndex = 24;
            this.points4.Text = "0";
            this.points4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // MultiPlayerLabel
            // 
            this.MultiPlayerLabel.AutoSize = true;
            this.MultiPlayerLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MultiPlayerLabel.Location = new System.Drawing.Point(285, 223);
            this.MultiPlayerLabel.Name = "MultiPlayerLabel";
            this.MultiPlayerLabel.Size = new System.Drawing.Size(0, 39);
            this.MultiPlayerLabel.TabIndex = 1;
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichier_MenuItem,
            this.Camera_MenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(784, 24);
            this.menuStrip.TabIndex = 0;
            this.menuStrip.Text = "menuStrip1";
            this.menuStrip.Visible = false;
            // 
            // fichier_MenuItem
            // 
            this.fichier_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mPrincipal_menu});
            this.fichier_MenuItem.Name = "fichier_MenuItem";
            this.fichier_MenuItem.Size = new System.Drawing.Size(54, 20);
            this.fichier_MenuItem.Text = "Fichier";
            // 
            // mPrincipal_menu
            // 
            this.mPrincipal_menu.Name = "mPrincipal_menu";
            this.mPrincipal_menu.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Q)));
            this.mPrincipal_menu.Size = new System.Drawing.Size(197, 22);
            this.mPrincipal_menu.Text = "Menu Principal";
            this.mPrincipal_menu.Click += new System.EventHandler(this.mPrincipal_menu_Click);
            // 
            // Camera_MenuItem
            // 
            this.Camera_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Ortho_MenuItem,
            this.Orbitale_MenuItem});
            this.Camera_MenuItem.Name = "Camera_MenuItem";
            this.Camera_MenuItem.Size = new System.Drawing.Size(39, 20);
            this.Camera_MenuItem.Text = "Vue";
            // 
            // Ortho_MenuItem
            // 
            this.Ortho_MenuItem.Name = "Ortho_MenuItem";
            this.Ortho_MenuItem.ShortcutKeyDisplayString = "1";
            this.Ortho_MenuItem.Size = new System.Drawing.Size(172, 22);
            this.Ortho_MenuItem.Text = "Orthographique";
            this.Ortho_MenuItem.Click += new System.EventHandler(this.Ortho_MenuItem_Click);
            // 
            // Orbitale_MenuItem
            // 
            this.Orbitale_MenuItem.Name = "Orbitale_MenuItem";
            this.Orbitale_MenuItem.ShortcutKeyDisplayString = "2";
            this.Orbitale_MenuItem.Size = new System.Drawing.Size(172, 22);
            this.Orbitale_MenuItem.Text = "Orbitale";
            this.Orbitale_MenuItem.Click += new System.EventHandler(this.Orbitale_MenuItem_Click);
            // 
            // QuitMPGameBtn
            // 
            this.QuitMPGameBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.QuitMPGameBtn.BackColor = System.Drawing.Color.Transparent;
            this.QuitMPGameBtn.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("QuitMPGameBtn.BackgroundImage")));
            this.QuitMPGameBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.QuitMPGameBtn.FlatAppearance.BorderSize = 0;
            this.QuitMPGameBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.QuitMPGameBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.QuitMPGameBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.QuitMPGameBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
            this.QuitMPGameBtn.ForeColor = System.Drawing.Color.Gold;
            this.QuitMPGameBtn.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.QuitMPGameBtn.Location = new System.Drawing.Point(3, 110);
            this.QuitMPGameBtn.Name = "QuitMPGameBtn";
            this.QuitMPGameBtn.Size = new System.Drawing.Size(120, 35);
            this.QuitMPGameBtn.TabIndex = 25;
            this.QuitMPGameBtn.TabStop = false;
            this.QuitMPGameBtn.Text = "Quitter";
            this.QuitMPGameBtn.UseVisualStyleBackColor = false;
            this.QuitMPGameBtn.Visible = false;
            this.QuitMPGameBtn.Click += new System.EventHandler(this.QuitMPGameBtn_Click);
            this.QuitMPGameBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.QuitMPGameBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.QuitMPGameBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.QuitMPGameBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // ModeJeu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 733);
            this.Controls.Add(this.panel_GL);
            this.Icon = global::InterfaceGraphique.Properties.Resources.Pinball;
            this.MainMenuStrip = this.menuStrip;
            this.MinimumSize = new System.Drawing.Size(800, 600);
            this.Name = "ModeJeu";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ModeJeu";
            this.Deactivate += new System.EventHandler(this.ModeJeu_Deactivate);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.PartieRapide_FormClosing);
            this.Load += new System.EventHandler(this.PartieRapide_Load);
            this.Shown += new System.EventHandler(this.ModeJeu_Shown);
            this.SizeChanged += new System.EventHandler(this.PartieRapide_redimensionner);
            this.VisibleChanged += new System.EventHandler(this.ModeJeu_VisibleChanged);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.PartieRapide_KeyDown);
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.PartieRapide_KeyPress);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.PartieRapide_KeyUp);
            this.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseWheel);
            this.panel_GL.ResumeLayout(false);
            this.panel_GL.PerformLayout();
            this.InfoPanel.ResumeLayout(false);
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel_GL;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem fichier_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Camera_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Ortho_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Orbitale_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem mPrincipal_menu;
        private System.Windows.Forms.FlowLayoutPanel InfoPanel;
        private System.Windows.Forms.Label label_Titre;
        private System.Windows.Forms.Label Player1;
        private System.Windows.Forms.Label points1;
        private System.Windows.Forms.Label label_Nom;
        private System.Windows.Forms.Label MultiPlayerLabel;
        private System.Windows.Forms.Label Player2;
        private System.Windows.Forms.Label points2;
        private System.Windows.Forms.Label Player3;
        private System.Windows.Forms.Label points3;
        private System.Windows.Forms.Label Player4;
        private System.Windows.Forms.Label points4;
        private System.Windows.Forms.Button QuitMPGameBtn;
    }
}