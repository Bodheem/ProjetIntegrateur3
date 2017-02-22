//////////////////////////////////////////////////////////////////////////////
/// @file Editeur.Designer.cs
/// @author Ballers
/// @date 2015-01-13
/// @version 1.0 
///
/// @ingroup InterfaceGraphique
//////////////////////////////////////////////////////////////////////////////

namespace InterfaceGraphique
{
    partial class Editeur
    {
        /// <summary>
        /// Variable necessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisees.
        /// </summary>
        /// <param name="disposing">true si les ressources managees doivent etre supprimees ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code genere par le Concepteur Windows Form

        /// <summary>
        /// Methode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette methode avec l'editeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Editeur));
            this.EnregistrerS_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel_GL = new System.Windows.Forms.Panel();
            this.panel_Tutorial = new System.Windows.Forms.Panel();
            this.Suivant_tuto_bouton = new System.Windows.Forms.Button();
            this.Annuler_tuto_bouton = new System.Windows.Forms.Button();
            this.enableTutorialCBox = new System.Windows.Forms.CheckBox();
            this.tuto_label = new System.Windows.Forms.Label();
            this.bouton_Creation = new System.Windows.Forms.Button();
            this.Creation_Panel = new System.Windows.Forms.FlowLayoutPanel();
            this.Groupe_Palettes = new System.Windows.Forms.GroupBox();
            this.PDJ2_bouton = new System.Windows.Forms.Button();
            this.PGJ2_bouton = new System.Windows.Forms.Button();
            this.PDJ1_bouton = new System.Windows.Forms.Button();
            this.PGJ1_bouton = new System.Windows.Forms.Button();
            this.Group_Butoir = new System.Windows.Forms.GroupBox();
            this.butoirCirc_bouton = new System.Windows.Forms.Button();
            this.butoirD_bouton = new System.Windows.Forms.Button();
            this.butoirG_bouton = new System.Windows.Forms.Button();
            this.Cible_bouton = new System.Windows.Forms.Button();
            this.Group_Elements = new System.Windows.Forms.GroupBox();
            this.Malus_bouton = new System.Windows.Forms.Button();
            this.Bonus_bouton = new System.Windows.Forms.Button();
            this.Gate = new System.Windows.Forms.Button();
            this.Portails_bouton = new System.Windows.Forms.Button();
            this.Group_Element2 = new System.Windows.Forms.GroupBox();
            this.Trou_bouton = new System.Windows.Forms.Button();
            this.Mur_bouton = new System.Windows.Forms.Button();
            this.Generateur_bouton = new System.Windows.Forms.Button();
            this.Ressort_bouton = new System.Windows.Forms.Button();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.Groupe_Outils = new System.Windows.Forms.GroupBox();
            this.bouton_Suppression = new System.Windows.Forms.Button();
            this.bouton_Selection = new System.Windows.Forms.Button();
            this.bouton_Deplacement = new System.Windows.Forms.Button();
            this.bouton_Duplication = new System.Windows.Forms.Button();
            this.bouton_Rotation = new System.Windows.Forms.Button();
            this.bouton_Scaling = new System.Windows.Forms.Button();
            this.OutilGraphique = new System.Windows.Forms.GroupBox();
            this.labelOCourant = new System.Windows.Forms.Label();
            this.Groupe_Proprietes = new System.Windows.Forms.GroupBox();
            this.Annuler_prop_boutn = new System.Windows.Forms.Button();
            this.OK_prop_bouton = new System.Windows.Forms.Button();
            this.Anglebox = new System.Windows.Forms.TextBox();
            this.Angle_label = new System.Windows.Forms.Label();
            this.FMEbox = new System.Windows.Forms.TextBox();
            this.FME_label = new System.Windows.Forms.Label();
            this.Ybox = new System.Windows.Forms.TextBox();
            this.Y_label = new System.Windows.Forms.Label();
            this.Xbox = new System.Windows.Forms.TextBox();
            this.X_label = new System.Windows.Forms.Label();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.MenuP_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.Nouveau_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.Ouvrir_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.EnregistrerSous_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.Annuler_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.Retablir_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.Proprietes_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.ModeTest_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.ZoomIn_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.ZoomOut_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.ZoomElastique_ToolStrip = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.Tutorial_Toolstrip = new System.Windows.Forms.ToolStripButton();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Nouveau_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Ouvrir_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Enregistrer_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.EnregistrerS_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Proprietes_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ModeTest_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuP_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Edition_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Supprimer_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.SelectAll_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Annuler_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Retablir_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Outils_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Selection_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Deplacement_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Rotation_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MiseE_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Duplication_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Zoom_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Creation_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PG_J1_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PD_J1_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PG_J2_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PD_J2_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.BTG_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.BTD_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.BC_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Cible_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Portails_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Mur_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Ressort_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.GB_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Trou_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.gateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Vues_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Orthographique_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Orbite_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Information_MenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip3 = new System.Windows.Forms.MenuStrip();
            this.fichierToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.testRetourMenuPrincipal = new System.Windows.Forms.ToolStripMenuItem();
            this.testRetourModeEdition = new System.Windows.Forms.ToolStripMenuItem();
            this.caméraToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.orthographiqueToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.orbiteToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.printPreviewDialog1 = new System.Windows.Forms.PrintPreviewDialog();
            this.toolTipPaneauCreation = new System.Windows.Forms.ToolTip(this.components);
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.panel1.SuspendLayout();
            this.panel_GL.SuspendLayout();
            this.panel_Tutorial.SuspendLayout();
            this.Creation_Panel.SuspendLayout();
            this.Groupe_Palettes.SuspendLayout();
            this.Group_Butoir.SuspendLayout();
            this.Group_Elements.SuspendLayout();
            this.Group_Element2.SuspendLayout();
            this.flowLayoutPanel1.SuspendLayout();
            this.Groupe_Outils.SuspendLayout();
            this.OutilGraphique.SuspendLayout();
            this.Groupe_Proprietes.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.menuStrip3.SuspendLayout();
            this.SuspendLayout();
            // 
            // EnregistrerS_ToolStrip
            // 
            resources.ApplyResources(this.EnregistrerS_ToolStrip, "EnregistrerS_ToolStrip");
            this.EnregistrerS_ToolStrip.BackColor = System.Drawing.Color.Transparent;
            this.EnregistrerS_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.EnregistrerS_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.save;
            this.EnregistrerS_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.EnregistrerS_ToolStrip.Name = "EnregistrerS_ToolStrip";
            this.EnregistrerS_ToolStrip.Click += new System.EventHandler(this.Enregistrer_ToolStrip_Click);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.panel_GL);
            this.panel1.Controls.Add(this.Creation_Panel);
            this.panel1.Controls.Add(this.flowLayoutPanel1);
            this.panel1.Controls.Add(this.toolStrip1);
            this.panel1.Controls.Add(this.menuStrip1);
            this.panel1.Controls.Add(this.menuStrip3);
            resources.ApplyResources(this.panel1, "panel1");
            this.panel1.Name = "panel1";
            this.panel1.Click += new System.EventHandler(this.panel1_Click);
            // 
            // panel_GL
            // 
            resources.ApplyResources(this.panel_GL, "panel_GL");
            this.panel_GL.BackColor = System.Drawing.Color.Transparent;
            this.panel_GL.Controls.Add(this.panel_Tutorial);
            this.panel_GL.Controls.Add(this.bouton_Creation);
            this.panel_GL.Name = "panel_GL";
            this.panel_GL.SizeChanged += new System.EventHandler(this.panel_GL_SizeChanged);
            this.panel_GL.MouseClick += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseClick);
            this.panel_GL.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseDown);
            this.panel_GL.MouseLeave += new System.EventHandler(this.panel_GL_MouseLeave);
            this.panel_GL.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseUp);
            this.panel_GL.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.panel_GL_MouseWheel);
            // 
            // panel_Tutorial
            // 
            this.panel_Tutorial.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.panel_Tutorial.Controls.Add(this.Suivant_tuto_bouton);
            this.panel_Tutorial.Controls.Add(this.Annuler_tuto_bouton);
            this.panel_Tutorial.Controls.Add(this.enableTutorialCBox);
            this.panel_Tutorial.Controls.Add(this.tuto_label);
            resources.ApplyResources(this.panel_Tutorial, "panel_Tutorial");
            this.panel_Tutorial.Name = "panel_Tutorial";
            // 
            // Suivant_tuto_bouton
            // 
            resources.ApplyResources(this.Suivant_tuto_bouton, "Suivant_tuto_bouton");
            this.Suivant_tuto_bouton.Name = "Suivant_tuto_bouton";
            this.Suivant_tuto_bouton.UseVisualStyleBackColor = true;
            this.Suivant_tuto_bouton.Click += new System.EventHandler(this.Suivant_tuto_bouton_Click);
            // 
            // Annuler_tuto_bouton
            // 
            resources.ApplyResources(this.Annuler_tuto_bouton, "Annuler_tuto_bouton");
            this.Annuler_tuto_bouton.Name = "Annuler_tuto_bouton";
            this.Annuler_tuto_bouton.UseVisualStyleBackColor = true;
            this.Annuler_tuto_bouton.Click += new System.EventHandler(this.Annuler_tuto_bouton_Click);
            // 
            // enableTutorialCBox
            // 
            resources.ApplyResources(this.enableTutorialCBox, "enableTutorialCBox");
            this.enableTutorialCBox.Name = "enableTutorialCBox";
            this.enableTutorialCBox.UseVisualStyleBackColor = true;
            // 
            // tuto_label
            // 
            resources.ApplyResources(this.tuto_label, "tuto_label");
            this.tuto_label.Name = "tuto_label";
            // 
            // bouton_Creation
            // 
            resources.ApplyResources(this.bouton_Creation, "bouton_Creation");
            this.bouton_Creation.Name = "bouton_Creation";
            this.toolTipPaneauCreation.SetToolTip(this.bouton_Creation, resources.GetString("bouton_Creation.ToolTip"));
            this.bouton_Creation.UseVisualStyleBackColor = true;
            this.bouton_Creation.Click += new System.EventHandler(this.bouton_Creation_Click);
            // 
            // Creation_Panel
            // 
            this.Creation_Panel.BackColor = System.Drawing.SystemColors.InactiveBorder;
            this.Creation_Panel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Creation_Panel.Controls.Add(this.Groupe_Palettes);
            this.Creation_Panel.Controls.Add(this.Group_Butoir);
            this.Creation_Panel.Controls.Add(this.Group_Elements);
            this.Creation_Panel.Controls.Add(this.Group_Element2);
            resources.ApplyResources(this.Creation_Panel, "Creation_Panel");
            this.Creation_Panel.Name = "Creation_Panel";
            this.Creation_Panel.MouseEnter += new System.EventHandler(this.Creation_Panel_MouseEnter);
            // 
            // Groupe_Palettes
            // 
            this.Groupe_Palettes.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.Groupe_Palettes.Controls.Add(this.PDJ2_bouton);
            this.Groupe_Palettes.Controls.Add(this.PGJ2_bouton);
            this.Groupe_Palettes.Controls.Add(this.PDJ1_bouton);
            this.Groupe_Palettes.Controls.Add(this.PGJ1_bouton);
            resources.ApplyResources(this.Groupe_Palettes, "Groupe_Palettes");
            this.Groupe_Palettes.Name = "Groupe_Palettes";
            this.Groupe_Palettes.TabStop = false;
            // 
            // PDJ2_bouton
            // 
            this.PDJ2_bouton.BackColor = System.Drawing.Color.White;
            this.PDJ2_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.PDJ2;
            resources.ApplyResources(this.PDJ2_bouton, "PDJ2_bouton");
            this.PDJ2_bouton.FlatAppearance.BorderSize = 3;
            this.PDJ2_bouton.FlatAppearance.CheckedBackColor = System.Drawing.Color.Red;
            this.PDJ2_bouton.Name = "PDJ2_bouton";
            this.toolTipPaneauCreation.SetToolTip(this.PDJ2_bouton, resources.GetString("PDJ2_bouton.ToolTip"));
            this.toolTip1.SetToolTip(this.PDJ2_bouton, resources.GetString("PDJ2_bouton.ToolTip1"));
            this.PDJ2_bouton.UseVisualStyleBackColor = false;
            this.PDJ2_bouton.Click += new System.EventHandler(this.PDJ2_bouton_Click);
            this.PDJ2_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // PGJ2_bouton
            // 
            this.PGJ2_bouton.BackColor = System.Drawing.Color.White;
            this.PGJ2_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.PGJ2;
            resources.ApplyResources(this.PGJ2_bouton, "PGJ2_bouton");
            this.PGJ2_bouton.FlatAppearance.BorderSize = 3;
            this.PGJ2_bouton.FlatAppearance.CheckedBackColor = System.Drawing.Color.Red;
            this.PGJ2_bouton.Name = "PGJ2_bouton";
            this.toolTipPaneauCreation.SetToolTip(this.PGJ2_bouton, resources.GetString("PGJ2_bouton.ToolTip"));
            this.toolTip1.SetToolTip(this.PGJ2_bouton, resources.GetString("PGJ2_bouton.ToolTip1"));
            this.PGJ2_bouton.UseVisualStyleBackColor = false;
            this.PGJ2_bouton.Click += new System.EventHandler(this.PGJ2_bouton_Click);
            this.PGJ2_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // PDJ1_bouton
            // 
            this.PDJ1_bouton.BackColor = System.Drawing.Color.White;
            this.PDJ1_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.PDJ1;
            resources.ApplyResources(this.PDJ1_bouton, "PDJ1_bouton");
            this.PDJ1_bouton.FlatAppearance.BorderSize = 3;
            this.PDJ1_bouton.FlatAppearance.CheckedBackColor = System.Drawing.Color.Red;
            this.PDJ1_bouton.Name = "PDJ1_bouton";
            this.toolTipPaneauCreation.SetToolTip(this.PDJ1_bouton, resources.GetString("PDJ1_bouton.ToolTip"));
            this.toolTip1.SetToolTip(this.PDJ1_bouton, resources.GetString("PDJ1_bouton.ToolTip1"));
            this.PDJ1_bouton.UseVisualStyleBackColor = false;
            this.PDJ1_bouton.Click += new System.EventHandler(this.PDJ1_bouton_Click);
            this.PDJ1_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // PGJ1_bouton
            // 
            this.PGJ1_bouton.BackColor = System.Drawing.Color.White;
            this.PGJ1_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.PGJ1;
            resources.ApplyResources(this.PGJ1_bouton, "PGJ1_bouton");
            this.PGJ1_bouton.FlatAppearance.BorderColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.PGJ1_bouton.FlatAppearance.BorderSize = 3;
            this.PGJ1_bouton.FlatAppearance.CheckedBackColor = System.Drawing.Color.Red;
            this.PGJ1_bouton.FlatAppearance.MouseDownBackColor = System.Drawing.SystemColors.ActiveBorder;
            this.PGJ1_bouton.Name = "PGJ1_bouton";
            this.toolTipPaneauCreation.SetToolTip(this.PGJ1_bouton, resources.GetString("PGJ1_bouton.ToolTip"));
            this.toolTip1.SetToolTip(this.PGJ1_bouton, resources.GetString("PGJ1_bouton.ToolTip1"));
            this.PGJ1_bouton.UseVisualStyleBackColor = false;
            this.PGJ1_bouton.Click += new System.EventHandler(this.PGJ1_bouton_Click);
            this.PGJ1_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // Group_Butoir
            // 
            this.Group_Butoir.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            resources.ApplyResources(this.Group_Butoir, "Group_Butoir");
            this.Group_Butoir.Controls.Add(this.butoirCirc_bouton);
            this.Group_Butoir.Controls.Add(this.butoirD_bouton);
            this.Group_Butoir.Controls.Add(this.butoirG_bouton);
            this.Group_Butoir.Controls.Add(this.Cible_bouton);
            this.Group_Butoir.Name = "Group_Butoir";
            this.Group_Butoir.TabStop = false;
            // 
            // butoirCirc_bouton
            // 
            this.butoirCirc_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.cible1;
            resources.ApplyResources(this.butoirCirc_bouton, "butoirCirc_bouton");
            this.butoirCirc_bouton.FlatAppearance.BorderSize = 3;
            this.butoirCirc_bouton.Name = "butoirCirc_bouton";
            this.toolTipPaneauCreation.SetToolTip(this.butoirCirc_bouton, resources.GetString("butoirCirc_bouton.ToolTip"));
            this.toolTip1.SetToolTip(this.butoirCirc_bouton, resources.GetString("butoirCirc_bouton.ToolTip1"));
            this.butoirCirc_bouton.UseVisualStyleBackColor = true;
            this.butoirCirc_bouton.Click += new System.EventHandler(this.butourCirc_bouton_Click);
            this.butoirCirc_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // butoirD_bouton
            // 
            this.butoirD_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.ButoirTriangD;
            resources.ApplyResources(this.butoirD_bouton, "butoirD_bouton");
            this.butoirD_bouton.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.butoirD_bouton.FlatAppearance.BorderSize = 3;
            this.butoirD_bouton.Name = "butoirD_bouton";
            this.toolTipPaneauCreation.SetToolTip(this.butoirD_bouton, resources.GetString("butoirD_bouton.ToolTip"));
            this.toolTip1.SetToolTip(this.butoirD_bouton, resources.GetString("butoirD_bouton.ToolTip1"));
            this.butoirD_bouton.UseVisualStyleBackColor = true;
            this.butoirD_bouton.Click += new System.EventHandler(this.butoirD_bouton_Click);
            this.butoirD_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // butoirG_bouton
            // 
            this.butoirG_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.ButoirTriangG;
            resources.ApplyResources(this.butoirG_bouton, "butoirG_bouton");
            this.butoirG_bouton.FlatAppearance.BorderSize = 3;
            this.butoirG_bouton.Name = "butoirG_bouton";
            this.toolTipPaneauCreation.SetToolTip(this.butoirG_bouton, resources.GetString("butoirG_bouton.ToolTip"));
            this.toolTip1.SetToolTip(this.butoirG_bouton, resources.GetString("butoirG_bouton.ToolTip1"));
            this.butoirG_bouton.UseVisualStyleBackColor = true;
            this.butoirG_bouton.Click += new System.EventHandler(this.butoirG_bouton_Click);
            this.butoirG_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // Cible_bouton
            // 
            this.Cible_bouton.BackColor = System.Drawing.Color.White;
            this.Cible_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.cible;
            resources.ApplyResources(this.Cible_bouton, "Cible_bouton");
            this.Cible_bouton.FlatAppearance.BorderSize = 3;
            this.Cible_bouton.Name = "Cible_bouton";
            this.toolTipPaneauCreation.SetToolTip(this.Cible_bouton, resources.GetString("Cible_bouton.ToolTip"));
            this.toolTip1.SetToolTip(this.Cible_bouton, resources.GetString("Cible_bouton.ToolTip1"));
            this.Cible_bouton.UseVisualStyleBackColor = false;
            this.Cible_bouton.Click += new System.EventHandler(this.Cible_bouton_Click);
            this.Cible_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // Group_Elements
            // 
            this.Group_Elements.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.Group_Elements.Controls.Add(this.Malus_bouton);
            this.Group_Elements.Controls.Add(this.Bonus_bouton);
            this.Group_Elements.Controls.Add(this.Gate);
            this.Group_Elements.Controls.Add(this.Portails_bouton);
            resources.ApplyResources(this.Group_Elements, "Group_Elements");
            this.Group_Elements.Name = "Group_Elements";
            this.Group_Elements.TabStop = false;
            // 
            // Malus_bouton
            // 
            this.Malus_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.malus;
            resources.ApplyResources(this.Malus_bouton, "Malus_bouton");
            this.Malus_bouton.FlatAppearance.BorderSize = 3;
            this.Malus_bouton.Name = "Malus_bouton";
            this.toolTip1.SetToolTip(this.Malus_bouton, resources.GetString("Malus_bouton.ToolTip"));
            this.Malus_bouton.UseVisualStyleBackColor = true;
            this.Malus_bouton.Click += new System.EventHandler(this.Malus_Button_Click);
            this.Malus_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // Bonus_bouton
            // 
            this.Bonus_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.bonus;
            resources.ApplyResources(this.Bonus_bouton, "Bonus_bouton");
            this.Bonus_bouton.FlatAppearance.BorderSize = 3;
            this.Bonus_bouton.Name = "Bonus_bouton";
            this.toolTip1.SetToolTip(this.Bonus_bouton, resources.GetString("Bonus_bouton.ToolTip"));
            this.Bonus_bouton.UseVisualStyleBackColor = true;
            this.Bonus_bouton.Click += new System.EventHandler(this.Bonus_Button_Click);
            this.Bonus_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // Gate
            // 
            this.Gate.BackColor = System.Drawing.Color.White;
            this.Gate.BackgroundImage = global::InterfaceGraphique.Properties.Resources.gate;
            resources.ApplyResources(this.Gate, "Gate");
            this.Gate.FlatAppearance.BorderSize = 3;
            this.Gate.Name = "Gate";
            this.Gate.Tag = "Gate";
            this.toolTipPaneauCreation.SetToolTip(this.Gate, resources.GetString("Gate.ToolTip"));
            this.toolTip1.SetToolTip(this.Gate, resources.GetString("Gate.ToolTip1"));
            this.Gate.UseVisualStyleBackColor = false;
            this.Gate.Click += new System.EventHandler(this.Gate_Button_Click);
            this.Gate.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // Portails_bouton
            // 
            this.Portails_bouton.BackColor = System.Drawing.Color.White;
            this.Portails_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.portail;
            resources.ApplyResources(this.Portails_bouton, "Portails_bouton");
            this.Portails_bouton.FlatAppearance.BorderSize = 3;
            this.Portails_bouton.Name = "Portails_bouton";
            this.toolTipPaneauCreation.SetToolTip(this.Portails_bouton, resources.GetString("Portails_bouton.ToolTip"));
            this.toolTip1.SetToolTip(this.Portails_bouton, resources.GetString("Portails_bouton.ToolTip1"));
            this.Portails_bouton.UseVisualStyleBackColor = false;
            this.Portails_bouton.Click += new System.EventHandler(this.Portails_bouton_Click);
            this.Portails_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // Group_Element2
            // 
            resources.ApplyResources(this.Group_Element2, "Group_Element2");
            this.Group_Element2.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.Group_Element2.Controls.Add(this.Trou_bouton);
            this.Group_Element2.Controls.Add(this.Mur_bouton);
            this.Group_Element2.Controls.Add(this.Generateur_bouton);
            this.Group_Element2.Controls.Add(this.Ressort_bouton);
            this.Group_Element2.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Group_Element2.Name = "Group_Element2";
            this.Group_Element2.TabStop = false;
            // 
            // Trou_bouton
            // 
            this.Trou_bouton.BackColor = System.Drawing.Color.White;
            this.Trou_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.Trou;
            resources.ApplyResources(this.Trou_bouton, "Trou_bouton");
            this.Trou_bouton.FlatAppearance.BorderSize = 3;
            this.Trou_bouton.Name = "Trou_bouton";
            this.Trou_bouton.Tag = "Hole";
            this.toolTipPaneauCreation.SetToolTip(this.Trou_bouton, resources.GetString("Trou_bouton.ToolTip"));
            this.toolTip1.SetToolTip(this.Trou_bouton, resources.GetString("Trou_bouton.ToolTip1"));
            this.Trou_bouton.UseVisualStyleBackColor = false;
            this.Trou_bouton.Click += new System.EventHandler(this.Trou_bouton_Click);
            this.Trou_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // Mur_bouton
            // 
            this.Mur_bouton.BackColor = System.Drawing.Color.White;
            this.Mur_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.mur;
            resources.ApplyResources(this.Mur_bouton, "Mur_bouton");
            this.Mur_bouton.FlatAppearance.BorderSize = 3;
            this.Mur_bouton.Name = "Mur_bouton";
            this.toolTipPaneauCreation.SetToolTip(this.Mur_bouton, resources.GetString("Mur_bouton.ToolTip"));
            this.toolTip1.SetToolTip(this.Mur_bouton, resources.GetString("Mur_bouton.ToolTip1"));
            this.Mur_bouton.UseVisualStyleBackColor = false;
            this.Mur_bouton.Click += new System.EventHandler(this.Mur_bouton_Click);
            this.Mur_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // Generateur_bouton
            // 
            this.Generateur_bouton.BackColor = System.Drawing.Color.White;
            this.Generateur_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.Generateur;
            resources.ApplyResources(this.Generateur_bouton, "Generateur_bouton");
            this.Generateur_bouton.FlatAppearance.BorderSize = 3;
            this.Generateur_bouton.Name = "Generateur_bouton";
            this.toolTipPaneauCreation.SetToolTip(this.Generateur_bouton, resources.GetString("Generateur_bouton.ToolTip"));
            this.toolTip1.SetToolTip(this.Generateur_bouton, resources.GetString("Generateur_bouton.ToolTip1"));
            this.Generateur_bouton.UseVisualStyleBackColor = false;
            this.Generateur_bouton.Click += new System.EventHandler(this.Generateur_bouton_Click);
            this.Generateur_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // Ressort_bouton
            // 
            this.Ressort_bouton.BackColor = System.Drawing.Color.White;
            this.Ressort_bouton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.ressort;
            resources.ApplyResources(this.Ressort_bouton, "Ressort_bouton");
            this.Ressort_bouton.FlatAppearance.BorderSize = 3;
            this.Ressort_bouton.Name = "Ressort_bouton";
            this.toolTipPaneauCreation.SetToolTip(this.Ressort_bouton, resources.GetString("Ressort_bouton.ToolTip"));
            this.toolTip1.SetToolTip(this.Ressort_bouton, resources.GetString("Ressort_bouton.ToolTip1"));
            this.Ressort_bouton.UseVisualStyleBackColor = false;
            this.Ressort_bouton.Click += new System.EventHandler(this.Ressort_bouton_Click);
            this.Ressort_bouton.Leave += new System.EventHandler(this.Generic_bouton_Leave);
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.BackColor = System.Drawing.SystemColors.InactiveBorder;
            this.flowLayoutPanel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.flowLayoutPanel1.Controls.Add(this.Groupe_Outils);
            this.flowLayoutPanel1.Controls.Add(this.OutilGraphique);
            this.flowLayoutPanel1.Controls.Add(this.Groupe_Proprietes);
            this.flowLayoutPanel1.Controls.Add(this.richTextBox1);
            resources.ApplyResources(this.flowLayoutPanel1, "flowLayoutPanel1");
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.SizeChanged += new System.EventHandler(this.flowLayoutPanel1_SizeChanged);
            // 
            // Groupe_Outils
            // 
            this.Groupe_Outils.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.Groupe_Outils.Controls.Add(this.bouton_Suppression);
            this.Groupe_Outils.Controls.Add(this.bouton_Selection);
            this.Groupe_Outils.Controls.Add(this.bouton_Deplacement);
            this.Groupe_Outils.Controls.Add(this.bouton_Duplication);
            this.Groupe_Outils.Controls.Add(this.bouton_Rotation);
            this.Groupe_Outils.Controls.Add(this.bouton_Scaling);
            resources.ApplyResources(this.Groupe_Outils, "Groupe_Outils");
            this.Groupe_Outils.Name = "Groupe_Outils";
            this.Groupe_Outils.TabStop = false;
            // 
            // bouton_Suppression
            // 
            resources.ApplyResources(this.bouton_Suppression, "bouton_Suppression");
            this.bouton_Suppression.Image = global::InterfaceGraphique.Properties.Resources.delete;
            this.bouton_Suppression.Name = "bouton_Suppression";
            this.toolTipPaneauCreation.SetToolTip(this.bouton_Suppression, resources.GetString("bouton_Suppression.ToolTip"));
            this.toolTip1.SetToolTip(this.bouton_Suppression, resources.GetString("bouton_Suppression.ToolTip1"));
            this.bouton_Suppression.UseVisualStyleBackColor = true;
            this.bouton_Suppression.Click += new System.EventHandler(this.bouton_Suppression_Click);
            // 
            // bouton_Selection
            // 
            resources.ApplyResources(this.bouton_Selection, "bouton_Selection");
            this.bouton_Selection.Image = global::InterfaceGraphique.Properties.Resources.Selection;
            this.bouton_Selection.Name = "bouton_Selection";
            this.toolTipPaneauCreation.SetToolTip(this.bouton_Selection, resources.GetString("bouton_Selection.ToolTip"));
            this.toolTip1.SetToolTip(this.bouton_Selection, resources.GetString("bouton_Selection.ToolTip1"));
            this.bouton_Selection.UseVisualStyleBackColor = true;
            this.bouton_Selection.Click += new System.EventHandler(this.bouton_Selection_Click);
            // 
            // bouton_Deplacement
            // 
            resources.ApplyResources(this.bouton_Deplacement, "bouton_Deplacement");
            this.bouton_Deplacement.Image = global::InterfaceGraphique.Properties.Resources.move;
            this.bouton_Deplacement.Name = "bouton_Deplacement";
            this.toolTipPaneauCreation.SetToolTip(this.bouton_Deplacement, resources.GetString("bouton_Deplacement.ToolTip"));
            this.toolTip1.SetToolTip(this.bouton_Deplacement, resources.GetString("bouton_Deplacement.ToolTip1"));
            this.bouton_Deplacement.UseVisualStyleBackColor = true;
            this.bouton_Deplacement.Click += new System.EventHandler(this.bouton_Deplacement_Click);
            // 
            // bouton_Duplication
            // 
            resources.ApplyResources(this.bouton_Duplication, "bouton_Duplication");
            this.bouton_Duplication.Image = global::InterfaceGraphique.Properties.Resources.duplicate;
            this.bouton_Duplication.Name = "bouton_Duplication";
            this.toolTipPaneauCreation.SetToolTip(this.bouton_Duplication, resources.GetString("bouton_Duplication.ToolTip"));
            this.toolTip1.SetToolTip(this.bouton_Duplication, resources.GetString("bouton_Duplication.ToolTip1"));
            this.bouton_Duplication.UseVisualStyleBackColor = true;
            this.bouton_Duplication.Click += new System.EventHandler(this.bouton_Duplication_Click);
            // 
            // bouton_Rotation
            // 
            resources.ApplyResources(this.bouton_Rotation, "bouton_Rotation");
            this.bouton_Rotation.Image = global::InterfaceGraphique.Properties.Resources.rotation;
            this.bouton_Rotation.Name = "bouton_Rotation";
            this.toolTipPaneauCreation.SetToolTip(this.bouton_Rotation, resources.GetString("bouton_Rotation.ToolTip"));
            this.toolTip1.SetToolTip(this.bouton_Rotation, resources.GetString("bouton_Rotation.ToolTip1"));
            this.bouton_Rotation.UseVisualStyleBackColor = true;
            this.bouton_Rotation.Click += new System.EventHandler(this.bouton_Rotation_Click);
            // 
            // bouton_Scaling
            // 
            resources.ApplyResources(this.bouton_Scaling, "bouton_Scaling");
            this.bouton_Scaling.Image = global::InterfaceGraphique.Properties.Resources.scale1;
            this.bouton_Scaling.Name = "bouton_Scaling";
            this.toolTipPaneauCreation.SetToolTip(this.bouton_Scaling, resources.GetString("bouton_Scaling.ToolTip"));
            this.toolTip1.SetToolTip(this.bouton_Scaling, resources.GetString("bouton_Scaling.ToolTip1"));
            this.bouton_Scaling.UseVisualStyleBackColor = true;
            this.bouton_Scaling.Click += new System.EventHandler(this.bouton_Scaling_Click);
            // 
            // OutilGraphique
            // 
            this.OutilGraphique.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.OutilGraphique.Controls.Add(this.labelOCourant);
            resources.ApplyResources(this.OutilGraphique, "OutilGraphique");
            this.OutilGraphique.Name = "OutilGraphique";
            this.OutilGraphique.TabStop = false;
            // 
            // labelOCourant
            // 
            this.labelOCourant.ForeColor = System.Drawing.SystemColors.InfoText;
            resources.ApplyResources(this.labelOCourant, "labelOCourant");
            this.labelOCourant.Name = "labelOCourant";
            // 
            // Groupe_Proprietes
            // 
            resources.ApplyResources(this.Groupe_Proprietes, "Groupe_Proprietes");
            this.Groupe_Proprietes.BackColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.Groupe_Proprietes.Controls.Add(this.Annuler_prop_boutn);
            this.Groupe_Proprietes.Controls.Add(this.OK_prop_bouton);
            this.Groupe_Proprietes.Controls.Add(this.Anglebox);
            this.Groupe_Proprietes.Controls.Add(this.Angle_label);
            this.Groupe_Proprietes.Controls.Add(this.FMEbox);
            this.Groupe_Proprietes.Controls.Add(this.FME_label);
            this.Groupe_Proprietes.Controls.Add(this.Ybox);
            this.Groupe_Proprietes.Controls.Add(this.Y_label);
            this.Groupe_Proprietes.Controls.Add(this.Xbox);
            this.Groupe_Proprietes.Controls.Add(this.X_label);
            this.Groupe_Proprietes.Name = "Groupe_Proprietes";
            this.Groupe_Proprietes.TabStop = false;
            // 
            // Annuler_prop_boutn
            // 
            resources.ApplyResources(this.Annuler_prop_boutn, "Annuler_prop_boutn");
            this.Annuler_prop_boutn.Name = "Annuler_prop_boutn";
            this.Annuler_prop_boutn.TabStop = false;
            this.Annuler_prop_boutn.UseVisualStyleBackColor = true;
            this.Annuler_prop_boutn.Click += new System.EventHandler(this.Annuler_prop_boutn_Click);
            // 
            // OK_prop_bouton
            // 
            resources.ApplyResources(this.OK_prop_bouton, "OK_prop_bouton");
            this.OK_prop_bouton.Name = "OK_prop_bouton";
            this.OK_prop_bouton.TabStop = false;
            this.OK_prop_bouton.UseVisualStyleBackColor = true;
            this.OK_prop_bouton.Click += new System.EventHandler(this.OK_prop_bouton_Click);
            // 
            // Anglebox
            // 
            resources.ApplyResources(this.Anglebox, "Anglebox");
            this.Anglebox.Name = "Anglebox";
            this.Anglebox.TabStop = false;
            // 
            // Angle_label
            // 
            resources.ApplyResources(this.Angle_label, "Angle_label");
            this.Angle_label.Name = "Angle_label";
            // 
            // FMEbox
            // 
            resources.ApplyResources(this.FMEbox, "FMEbox");
            this.FMEbox.Name = "FMEbox";
            this.FMEbox.TabStop = false;
            // 
            // FME_label
            // 
            resources.ApplyResources(this.FME_label, "FME_label");
            this.FME_label.Name = "FME_label";
            // 
            // Ybox
            // 
            resources.ApplyResources(this.Ybox, "Ybox");
            this.Ybox.Name = "Ybox";
            this.Ybox.TabStop = false;
            // 
            // Y_label
            // 
            resources.ApplyResources(this.Y_label, "Y_label");
            this.Y_label.Name = "Y_label";
            // 
            // Xbox
            // 
            resources.ApplyResources(this.Xbox, "Xbox");
            this.Xbox.Name = "Xbox";
            this.Xbox.TabStop = false;
            // 
            // X_label
            // 
            resources.ApplyResources(this.X_label, "X_label");
            this.X_label.Name = "X_label";
            // 
            // richTextBox1
            // 
            resources.ApplyResources(this.richTextBox1, "richTextBox1");
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.TabStop = false;
            // 
            // toolStrip1
            // 
            resources.ApplyResources(this.toolStrip1, "toolStrip1");
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(40, 40);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuP_ToolStrip,
            this.toolStripSeparator2,
            this.Nouveau_ToolStrip,
            this.Ouvrir_ToolStrip,
            this.EnregistrerS_ToolStrip,
            this.EnregistrerSous_ToolStrip,
            this.toolStripSeparator1,
            this.Annuler_ToolStrip,
            this.Retablir_ToolStrip,
            this.toolStripSeparator3,
            this.Proprietes_ToolStrip,
            this.ModeTest_ToolStrip,
            this.toolStripSeparator4,
            this.ZoomIn_ToolStrip,
            this.ZoomOut_ToolStrip,
            this.ZoomElastique_ToolStrip,
            this.toolStripSeparator5,
            this.toolStripButton1,
            this.toolStripButton2,
            this.toolStripSeparator6,
            this.Tutorial_Toolstrip});
            this.toolStrip1.Name = "toolStrip1";
            // 
            // MenuP_ToolStrip
            // 
            resources.ApplyResources(this.MenuP_ToolStrip, "MenuP_ToolStrip");
            this.MenuP_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.MenuP_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.Return_home;
            this.MenuP_ToolStrip.Name = "MenuP_ToolStrip";
            this.MenuP_ToolStrip.Click += new System.EventHandler(this.MenuP_ToolStrip_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Margin = new System.Windows.Forms.Padding(10, 0, 10, 0);
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            resources.ApplyResources(this.toolStripSeparator2, "toolStripSeparator2");
            // 
            // Nouveau_ToolStrip
            // 
            resources.ApplyResources(this.Nouveau_ToolStrip, "Nouveau_ToolStrip");
            this.Nouveau_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Nouveau_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.NouveauFichier;
            this.Nouveau_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Nouveau_ToolStrip.Name = "Nouveau_ToolStrip";
            this.Nouveau_ToolStrip.Click += new System.EventHandler(this.Nouveau_Click);
            // 
            // Ouvrir_ToolStrip
            // 
            resources.ApplyResources(this.Ouvrir_ToolStrip, "Ouvrir_ToolStrip");
            this.Ouvrir_ToolStrip.BackColor = System.Drawing.Color.Transparent;
            this.Ouvrir_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Ouvrir_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.open1;
            this.Ouvrir_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Ouvrir_ToolStrip.Name = "Ouvrir_ToolStrip";
            this.Ouvrir_ToolStrip.Click += new System.EventHandler(this.Ouvrir_Click);
            // 
            // EnregistrerSous_ToolStrip
            // 
            resources.ApplyResources(this.EnregistrerSous_ToolStrip, "EnregistrerSous_ToolStrip");
            this.EnregistrerSous_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.EnregistrerSous_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.enregistrersous;
            this.EnregistrerSous_ToolStrip.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.EnregistrerSous_ToolStrip.Name = "EnregistrerSous_ToolStrip";
            this.EnregistrerSous_ToolStrip.Click += new System.EventHandler(this.EnregistrerSous_ToolStrip_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Margin = new System.Windows.Forms.Padding(10, 0, 10, 0);
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            resources.ApplyResources(this.toolStripSeparator1, "toolStripSeparator1");
            // 
            // Annuler_ToolStrip
            // 
            resources.ApplyResources(this.Annuler_ToolStrip, "Annuler_ToolStrip");
            this.Annuler_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Annuler_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.undo;
            this.Annuler_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Annuler_ToolStrip.Name = "Annuler_ToolStrip";
            this.Annuler_ToolStrip.Click += new System.EventHandler(this.Annuler_ToolStrip_Click);
            // 
            // Retablir_ToolStrip
            // 
            resources.ApplyResources(this.Retablir_ToolStrip, "Retablir_ToolStrip");
            this.Retablir_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Retablir_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.redo;
            this.Retablir_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Retablir_ToolStrip.Name = "Retablir_ToolStrip";
            this.Retablir_ToolStrip.Click += new System.EventHandler(this.Retablir_ToolStrip_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Margin = new System.Windows.Forms.Padding(10, 0, 10, 0);
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            resources.ApplyResources(this.toolStripSeparator3, "toolStripSeparator3");
            // 
            // Proprietes_ToolStrip
            // 
            resources.ApplyResources(this.Proprietes_ToolStrip, "Proprietes_ToolStrip");
            this.Proprietes_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Proprietes_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.settings;
            this.Proprietes_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.Proprietes_ToolStrip.Name = "Proprietes_ToolStrip";
            this.Proprietes_ToolStrip.Click += new System.EventHandler(this.Proprietes_ToolStrip_Click);
            // 
            // ModeTest_ToolStrip
            // 
            resources.ApplyResources(this.ModeTest_ToolStrip, "ModeTest_ToolStrip");
            this.ModeTest_ToolStrip.Name = "ModeTest_ToolStrip";
            this.ModeTest_ToolStrip.Click += new System.EventHandler(this.ModeTest_ToolStrip_Click);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            resources.ApplyResources(this.toolStripSeparator4, "toolStripSeparator4");
            // 
            // ZoomIn_ToolStrip
            // 
            resources.ApplyResources(this.ZoomIn_ToolStrip, "ZoomIn_ToolStrip");
            this.ZoomIn_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.ZoomIn_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.zoomIN;
            this.ZoomIn_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.ZoomIn_ToolStrip.Name = "ZoomIn_ToolStrip";
            this.ZoomIn_ToolStrip.Click += new System.EventHandler(this.ZoomIn_ToolStrip_Click);
            // 
            // ZoomOut_ToolStrip
            // 
            resources.ApplyResources(this.ZoomOut_ToolStrip, "ZoomOut_ToolStrip");
            this.ZoomOut_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.ZoomOut_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.ZoomOut;
            this.ZoomOut_ToolStrip.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.ZoomOut_ToolStrip.Name = "ZoomOut_ToolStrip";
            this.ZoomOut_ToolStrip.Click += new System.EventHandler(this.ZoomOut_ToolStrip_Click);
            // 
            // ZoomElastique_ToolStrip
            // 
            resources.ApplyResources(this.ZoomElastique_ToolStrip, "ZoomElastique_ToolStrip");
            this.ZoomElastique_ToolStrip.BackColor = System.Drawing.Color.Transparent;
            this.ZoomElastique_ToolStrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.ZoomElastique_ToolStrip.Image = global::InterfaceGraphique.Properties.Resources.zoomElastique2;
            this.ZoomElastique_ToolStrip.Margin = new System.Windows.Forms.Padding(0, 4, 0, 4);
            this.ZoomElastique_ToolStrip.Name = "ZoomElastique_ToolStrip";
            this.ZoomElastique_ToolStrip.Click += new System.EventHandler(this.ZoomElastique_ToolStrip_Click);
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Margin = new System.Windows.Forms.Padding(10, 0, 10, 0);
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            resources.ApplyResources(this.toolStripSeparator5, "toolStripSeparator5");
            // 
            // toolStripButton1
            // 
            resources.ApplyResources(this.toolStripButton1, "toolStripButton1");
            this.toolStripButton1.AutoToolTip = false;
            this.toolStripButton1.Image = global::InterfaceGraphique.Properties.Resources.camera;
            this.toolStripButton1.Margin = new System.Windows.Forms.Padding(4, 0, 8, 0);
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Click += new System.EventHandler(this.toolStripButton1_Click);
            // 
            // toolStripButton2
            // 
            resources.ApplyResources(this.toolStripButton2, "toolStripButton2");
            this.toolStripButton2.AutoToolTip = false;
            this.toolStripButton2.Image = global::InterfaceGraphique.Properties.Resources.camera;
            this.toolStripButton2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.toolStripButton2.Name = "toolStripButton2";
            this.toolStripButton2.Click += new System.EventHandler(this.toolStripButton2_Click);
            // 
            // toolStripSeparator6
            // 
            this.toolStripSeparator6.Name = "toolStripSeparator6";
            resources.ApplyResources(this.toolStripSeparator6, "toolStripSeparator6");
            // 
            // Tutorial_Toolstrip
            // 
            resources.ApplyResources(this.Tutorial_Toolstrip, "Tutorial_Toolstrip");
            this.Tutorial_Toolstrip.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Tutorial_Toolstrip.Image = global::InterfaceGraphique.Properties.Resources.Help_btn1;
            this.Tutorial_Toolstrip.Name = "Tutorial_Toolstrip";
            this.Tutorial_Toolstrip.Click += new System.EventHandler(this.Tutorial_Toolstrip_Click);
            // 
            // menuStrip1
            // 
            resources.ApplyResources(this.menuStrip1, "menuStrip1");
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem,
            this.Edition_MenuItem,
            this.Outils_MenuItem,
            this.Vues_MenuItem,
            this.Information_MenuItem});
            this.menuStrip1.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.menuStrip1.Name = "menuStrip1";
            // 
            // fichierToolStripMenuItem
            // 
            this.fichierToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Nouveau_MenuItem,
            this.Ouvrir_MenuItem,
            this.Enregistrer_MenuItem,
            this.EnregistrerS_MenuItem,
            this.Proprietes_MenuItem,
            this.ModeTest_MenuItem,
            this.MenuP_MenuItem});
            this.fichierToolStripMenuItem.Name = "fichierToolStripMenuItem";
            resources.ApplyResources(this.fichierToolStripMenuItem, "fichierToolStripMenuItem");
            // 
            // Nouveau_MenuItem
            // 
            this.Nouveau_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.NouveauFichier;
            this.Nouveau_MenuItem.Name = "Nouveau_MenuItem";
            resources.ApplyResources(this.Nouveau_MenuItem, "Nouveau_MenuItem");
            this.Nouveau_MenuItem.Click += new System.EventHandler(this.Nouveau_MenuItem_Click);
            // 
            // Ouvrir_MenuItem
            // 
            this.Ouvrir_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.open;
            this.Ouvrir_MenuItem.Name = "Ouvrir_MenuItem";
            resources.ApplyResources(this.Ouvrir_MenuItem, "Ouvrir_MenuItem");
            this.Ouvrir_MenuItem.Click += new System.EventHandler(this.Ouvrir_MenuItem_Click);
            // 
            // Enregistrer_MenuItem
            // 
            this.Enregistrer_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.save;
            this.Enregistrer_MenuItem.Name = "Enregistrer_MenuItem";
            resources.ApplyResources(this.Enregistrer_MenuItem, "Enregistrer_MenuItem");
            this.Enregistrer_MenuItem.Click += new System.EventHandler(this.Enregistrer_MenuItem_Click);
            // 
            // EnregistrerS_MenuItem
            // 
            this.EnregistrerS_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.enregistrersous;
            this.EnregistrerS_MenuItem.Name = "EnregistrerS_MenuItem";
            resources.ApplyResources(this.EnregistrerS_MenuItem, "EnregistrerS_MenuItem");
            this.EnregistrerS_MenuItem.Click += new System.EventHandler(this.EnregistrerS_MenuItem_Click);
            // 
            // Proprietes_MenuItem
            // 
            this.Proprietes_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.settings;
            this.Proprietes_MenuItem.Name = "Proprietes_MenuItem";
            resources.ApplyResources(this.Proprietes_MenuItem, "Proprietes_MenuItem");
            this.Proprietes_MenuItem.Click += new System.EventHandler(this.Proprietes_MenuItem_Click);
            // 
            // ModeTest_MenuItem
            // 
            this.ModeTest_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.Tester;
            this.ModeTest_MenuItem.Name = "ModeTest_MenuItem";
            resources.ApplyResources(this.ModeTest_MenuItem, "ModeTest_MenuItem");
            this.ModeTest_MenuItem.Click += new System.EventHandler(this.ModeTest_MenuItem_Click);
            // 
            // MenuP_MenuItem
            // 
            this.MenuP_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.Return_home;
            this.MenuP_MenuItem.Name = "MenuP_MenuItem";
            resources.ApplyResources(this.MenuP_MenuItem, "MenuP_MenuItem");
            this.MenuP_MenuItem.Click += new System.EventHandler(this.MenuP_MenuItem_Click);
            // 
            // Edition_MenuItem
            // 
            this.Edition_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Supprimer_MenuItem,
            this.SelectAll_MenuItem,
            this.Annuler_MenuItem,
            this.Retablir_MenuItem});
            this.Edition_MenuItem.Name = "Edition_MenuItem";
            resources.ApplyResources(this.Edition_MenuItem, "Edition_MenuItem");
            // 
            // Supprimer_MenuItem
            // 
            this.Supprimer_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.delete;
            this.Supprimer_MenuItem.Name = "Supprimer_MenuItem";
            resources.ApplyResources(this.Supprimer_MenuItem, "Supprimer_MenuItem");
            this.Supprimer_MenuItem.Click += new System.EventHandler(this.Supprimer_MenuItem_Click_1);
            // 
            // SelectAll_MenuItem
            // 
            this.SelectAll_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.Selection;
            this.SelectAll_MenuItem.Name = "SelectAll_MenuItem";
            resources.ApplyResources(this.SelectAll_MenuItem, "SelectAll_MenuItem");
            this.SelectAll_MenuItem.Click += new System.EventHandler(this.SelectAll_MenuItem_Click);
            // 
            // Annuler_MenuItem
            // 
            this.Annuler_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.undo;
            this.Annuler_MenuItem.Name = "Annuler_MenuItem";
            resources.ApplyResources(this.Annuler_MenuItem, "Annuler_MenuItem");
            this.Annuler_MenuItem.Click += new System.EventHandler(this.Annuler_MenuItem_Click);
            // 
            // Retablir_MenuItem
            // 
            this.Retablir_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.redo;
            this.Retablir_MenuItem.Name = "Retablir_MenuItem";
            resources.ApplyResources(this.Retablir_MenuItem, "Retablir_MenuItem");
            this.Retablir_MenuItem.Click += new System.EventHandler(this.Retablir_MenuItem_Click);
            // 
            // Outils_MenuItem
            // 
            this.Outils_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Selection_MenuItem,
            this.Deplacement_MenuItem,
            this.Rotation_MenuItem,
            this.MiseE_MenuItem,
            this.Duplication_MenuItem,
            this.Zoom_MenuItem,
            this.Creation_MenuItem});
            this.Outils_MenuItem.Name = "Outils_MenuItem";
            resources.ApplyResources(this.Outils_MenuItem, "Outils_MenuItem");
            // 
            // Selection_MenuItem
            // 
            this.Selection_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.Selection;
            this.Selection_MenuItem.Name = "Selection_MenuItem";
            resources.ApplyResources(this.Selection_MenuItem, "Selection_MenuItem");
            this.Selection_MenuItem.Click += new System.EventHandler(this.Selection_MenuItem_Click);
            // 
            // Deplacement_MenuItem
            // 
            resources.ApplyResources(this.Deplacement_MenuItem, "Deplacement_MenuItem");
            this.Deplacement_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.move;
            this.Deplacement_MenuItem.Name = "Deplacement_MenuItem";
            this.Deplacement_MenuItem.Click += new System.EventHandler(this.Deplacement_MenuItem_Click);
            // 
            // Rotation_MenuItem
            // 
            resources.ApplyResources(this.Rotation_MenuItem, "Rotation_MenuItem");
            this.Rotation_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.rotation;
            this.Rotation_MenuItem.Name = "Rotation_MenuItem";
            this.Rotation_MenuItem.Click += new System.EventHandler(this.Rotation_MenuItem_Click);
            // 
            // MiseE_MenuItem
            // 
            resources.ApplyResources(this.MiseE_MenuItem, "MiseE_MenuItem");
            this.MiseE_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.scale1;
            this.MiseE_MenuItem.Name = "MiseE_MenuItem";
            this.MiseE_MenuItem.Click += new System.EventHandler(this.MiseE_MenuItem_Click);
            // 
            // Duplication_MenuItem
            // 
            resources.ApplyResources(this.Duplication_MenuItem, "Duplication_MenuItem");
            this.Duplication_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.duplicate;
            this.Duplication_MenuItem.Name = "Duplication_MenuItem";
            this.Duplication_MenuItem.Click += new System.EventHandler(this.Duplication_MenuItem_Click);
            // 
            // Zoom_MenuItem
            // 
            this.Zoom_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.zoomElastique2;
            this.Zoom_MenuItem.Name = "Zoom_MenuItem";
            resources.ApplyResources(this.Zoom_MenuItem, "Zoom_MenuItem");
            this.Zoom_MenuItem.Click += new System.EventHandler(this.Zoom_MenuItem_Click);
            // 
            // Creation_MenuItem
            // 
            this.Creation_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.PG_J1_MenuItem,
            this.PD_J1_MenuItem,
            this.PG_J2_MenuItem,
            this.PD_J2_MenuItem,
            this.BTG_MenuItem,
            this.BTD_MenuItem,
            this.BC_MenuItem,
            this.Cible_MenuItem,
            this.Portails_MenuItem,
            this.Mur_MenuItem,
            this.Ressort_MenuItem,
            this.GB_MenuItem,
            this.Trou_MenuItem,
            this.gateToolStripMenuItem});
            this.Creation_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.add;
            this.Creation_MenuItem.Name = "Creation_MenuItem";
            resources.ApplyResources(this.Creation_MenuItem, "Creation_MenuItem");
            this.Creation_MenuItem.Click += new System.EventHandler(this.Creation_MenuItem_Click);
            // 
            // PG_J1_MenuItem
            // 
            this.PG_J1_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.PGJ1;
            this.PG_J1_MenuItem.Name = "PG_J1_MenuItem";
            resources.ApplyResources(this.PG_J1_MenuItem, "PG_J1_MenuItem");
            this.PG_J1_MenuItem.Click += new System.EventHandler(this.PG_J1_MenuItem_Click);
            // 
            // PD_J1_MenuItem
            // 
            this.PD_J1_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.PDJ1;
            this.PD_J1_MenuItem.Name = "PD_J1_MenuItem";
            resources.ApplyResources(this.PD_J1_MenuItem, "PD_J1_MenuItem");
            this.PD_J1_MenuItem.Click += new System.EventHandler(this.PD_J1_MenuItem_Click);
            // 
            // PG_J2_MenuItem
            // 
            this.PG_J2_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.PGJ2;
            this.PG_J2_MenuItem.Name = "PG_J2_MenuItem";
            resources.ApplyResources(this.PG_J2_MenuItem, "PG_J2_MenuItem");
            this.PG_J2_MenuItem.Click += new System.EventHandler(this.PG_J2_MenuItem_Click);
            // 
            // PD_J2_MenuItem
            // 
            this.PD_J2_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.PDJ2;
            this.PD_J2_MenuItem.Name = "PD_J2_MenuItem";
            resources.ApplyResources(this.PD_J2_MenuItem, "PD_J2_MenuItem");
            this.PD_J2_MenuItem.Click += new System.EventHandler(this.PD_J2_MenuItem_Click);
            // 
            // BTG_MenuItem
            // 
            this.BTG_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.ButoirTriangG;
            this.BTG_MenuItem.Name = "BTG_MenuItem";
            resources.ApplyResources(this.BTG_MenuItem, "BTG_MenuItem");
            this.BTG_MenuItem.Click += new System.EventHandler(this.BTG_MenuItem_Click);
            // 
            // BTD_MenuItem
            // 
            this.BTD_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.ButoirTriangD;
            this.BTD_MenuItem.Name = "BTD_MenuItem";
            resources.ApplyResources(this.BTD_MenuItem, "BTD_MenuItem");
            this.BTD_MenuItem.Click += new System.EventHandler(this.BTD_MenuItem_Click);
            // 
            // BC_MenuItem
            // 
            this.BC_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.cible1;
            this.BC_MenuItem.Name = "BC_MenuItem";
            resources.ApplyResources(this.BC_MenuItem, "BC_MenuItem");
            this.BC_MenuItem.Click += new System.EventHandler(this.BC_MenuItem_Click);
            // 
            // Cible_MenuItem
            // 
            this.Cible_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.cible;
            this.Cible_MenuItem.Name = "Cible_MenuItem";
            resources.ApplyResources(this.Cible_MenuItem, "Cible_MenuItem");
            this.Cible_MenuItem.Click += new System.EventHandler(this.Cible_MenuItem_Click);
            // 
            // Portails_MenuItem
            // 
            this.Portails_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.portail;
            this.Portails_MenuItem.Name = "Portails_MenuItem";
            resources.ApplyResources(this.Portails_MenuItem, "Portails_MenuItem");
            this.Portails_MenuItem.Click += new System.EventHandler(this.Portails_MenuItem_Click);
            // 
            // Mur_MenuItem
            // 
            this.Mur_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.mur;
            this.Mur_MenuItem.Name = "Mur_MenuItem";
            resources.ApplyResources(this.Mur_MenuItem, "Mur_MenuItem");
            this.Mur_MenuItem.Click += new System.EventHandler(this.Mur_MenuItem_Click);
            // 
            // Ressort_MenuItem
            // 
            this.Ressort_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.ressort;
            this.Ressort_MenuItem.Name = "Ressort_MenuItem";
            resources.ApplyResources(this.Ressort_MenuItem, "Ressort_MenuItem");
            this.Ressort_MenuItem.Click += new System.EventHandler(this.Ressort_MenuItem_Click);
            // 
            // GB_MenuItem
            // 
            this.GB_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.Generateur;
            this.GB_MenuItem.Name = "GB_MenuItem";
            resources.ApplyResources(this.GB_MenuItem, "GB_MenuItem");
            this.GB_MenuItem.Click += new System.EventHandler(this.GB_MenuItem_Click);
            // 
            // Trou_MenuItem
            // 
            this.Trou_MenuItem.Image = global::InterfaceGraphique.Properties.Resources.Trou;
            this.Trou_MenuItem.Name = "Trou_MenuItem";
            resources.ApplyResources(this.Trou_MenuItem, "Trou_MenuItem");
            this.Trou_MenuItem.Click += new System.EventHandler(this.Trou_MenuItem_Click);
            // 
            // gateToolStripMenuItem
            // 
            this.gateToolStripMenuItem.Image = global::InterfaceGraphique.Properties.Resources.gate;
            this.gateToolStripMenuItem.Name = "gateToolStripMenuItem";
            resources.ApplyResources(this.gateToolStripMenuItem, "gateToolStripMenuItem");
            this.gateToolStripMenuItem.Click += new System.EventHandler(this.Gate_Button_Click);
            // 
            // Vues_MenuItem
            // 
            this.Vues_MenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Orthographique_MenuItem,
            this.Orbite_MenuItem});
            this.Vues_MenuItem.Name = "Vues_MenuItem";
            resources.ApplyResources(this.Vues_MenuItem, "Vues_MenuItem");
            // 
            // Orthographique_MenuItem
            // 
            this.Orthographique_MenuItem.Name = "Orthographique_MenuItem";
            resources.ApplyResources(this.Orthographique_MenuItem, "Orthographique_MenuItem");
            this.Orthographique_MenuItem.Click += new System.EventHandler(this.Orthographique_MenuItem_Click);
            // 
            // Orbite_MenuItem
            // 
            this.Orbite_MenuItem.Name = "Orbite_MenuItem";
            resources.ApplyResources(this.Orbite_MenuItem, "Orbite_MenuItem");
            this.Orbite_MenuItem.Click += new System.EventHandler(this.Orbite_MenuItem_Click);
            // 
            // Information_MenuItem
            // 
            this.Information_MenuItem.CheckOnClick = true;
            this.Information_MenuItem.Name = "Information_MenuItem";
            resources.ApplyResources(this.Information_MenuItem, "Information_MenuItem");
            this.Information_MenuItem.Click += new System.EventHandler(this.Information_MenuItem_Click);
            // 
            // menuStrip3
            // 
            this.menuStrip3.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fichierToolStripMenuItem1,
            this.caméraToolStripMenuItem1});
            resources.ApplyResources(this.menuStrip3, "menuStrip3");
            this.menuStrip3.Name = "menuStrip3";
            // 
            // fichierToolStripMenuItem1
            // 
            this.fichierToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.testRetourMenuPrincipal,
            this.testRetourModeEdition});
            this.fichierToolStripMenuItem1.Name = "fichierToolStripMenuItem1";
            resources.ApplyResources(this.fichierToolStripMenuItem1, "fichierToolStripMenuItem1");
            // 
            // testRetourMenuPrincipal
            // 
            this.testRetourMenuPrincipal.Name = "testRetourMenuPrincipal";
            resources.ApplyResources(this.testRetourMenuPrincipal, "testRetourMenuPrincipal");
            this.testRetourMenuPrincipal.Click += new System.EventHandler(this.testRetourMenuPrincipal_Click);
            // 
            // testRetourModeEdition
            // 
            this.testRetourModeEdition.Name = "testRetourModeEdition";
            resources.ApplyResources(this.testRetourModeEdition, "testRetourModeEdition");
            this.testRetourModeEdition.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
            // 
            // caméraToolStripMenuItem1
            // 
            this.caméraToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.orthographiqueToolStripMenuItem,
            this.orbiteToolStripMenuItem1});
            this.caméraToolStripMenuItem1.Name = "caméraToolStripMenuItem1";
            resources.ApplyResources(this.caméraToolStripMenuItem1, "caméraToolStripMenuItem1");
            // 
            // orthographiqueToolStripMenuItem
            // 
            this.orthographiqueToolStripMenuItem.Name = "orthographiqueToolStripMenuItem";
            resources.ApplyResources(this.orthographiqueToolStripMenuItem, "orthographiqueToolStripMenuItem");
            // 
            // orbiteToolStripMenuItem1
            // 
            this.orbiteToolStripMenuItem1.Name = "orbiteToolStripMenuItem1";
            resources.ApplyResources(this.orbiteToolStripMenuItem1, "orbiteToolStripMenuItem1");
            // 
            // printPreviewDialog1
            // 
            resources.ApplyResources(this.printPreviewDialog1, "printPreviewDialog1");
            this.printPreviewDialog1.Name = "printPreviewDialog1";
            // 
            // toolTip1
            // 
            this.toolTip1.AutomaticDelay = 0;
            this.toolTip1.AutoPopDelay = 5500;
            this.toolTip1.InitialDelay = 20;
            this.toolTip1.ReshowDelay = 110;
            // 
            // Editeur
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panel1);
            this.KeyPreview = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Editeur";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Editeur_FormClosing);
            this.Shown += new System.EventHandler(this.Editeur_Shown);
            this.SizeChanged += new System.EventHandler(this.Fenetre_Redimension);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel_GL.ResumeLayout(false);
            this.panel_Tutorial.ResumeLayout(false);
            this.panel_Tutorial.PerformLayout();
            this.Creation_Panel.ResumeLayout(false);
            this.Groupe_Palettes.ResumeLayout(false);
            this.Group_Butoir.ResumeLayout(false);
            this.Group_Elements.ResumeLayout(false);
            this.Group_Element2.ResumeLayout(false);
            this.flowLayoutPanel1.ResumeLayout(false);
            this.Groupe_Outils.ResumeLayout(false);
            this.OutilGraphique.ResumeLayout(false);
            this.Groupe_Proprietes.ResumeLayout(false);
            this.Groupe_Proprietes.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.menuStrip3.ResumeLayout(false);
            this.menuStrip3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Nouveau_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem MenuP_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Outils_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Enregistrer_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem EnregistrerS_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Vues_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Ouvrir_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Proprietes_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem ModeTest_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Information_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Orthographique_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Orbite_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Selection_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Deplacement_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Rotation_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem MiseE_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Duplication_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Creation_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Zoom_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem PG_J1_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem PD_J1_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem PG_J2_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem PD_J2_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem BTG_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem BTD_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem BC_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Cible_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Portails_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Mur_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Ressort_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem GB_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Trou_MenuItem;
        private System.Windows.Forms.FlowLayoutPanel Creation_Panel;
        private System.Windows.Forms.GroupBox Groupe_Palettes;
        private System.Windows.Forms.PrintPreviewDialog printPreviewDialog1;
        private System.Windows.Forms.Button PDJ1_bouton;
        private System.Windows.Forms.Button PGJ1_bouton;
        private System.Windows.Forms.Button PDJ2_bouton;
        private System.Windows.Forms.Button PGJ2_bouton;
        private System.Windows.Forms.GroupBox Group_Butoir;
        private System.Windows.Forms.Button butoirD_bouton;
        private System.Windows.Forms.Button butoirG_bouton;
        private System.Windows.Forms.Button butoirCirc_bouton;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.Panel panel_GL;
        private System.Windows.Forms.GroupBox Groupe_Outils;
        private System.Windows.Forms.GroupBox Groupe_Proprietes;
        private System.Windows.Forms.Button bouton_Selection;
        private System.Windows.Forms.Button bouton_Creation;
        private System.Windows.Forms.Button bouton_Duplication;
        private System.Windows.Forms.Button bouton_Scaling;
        private System.Windows.Forms.Button bouton_Rotation;
        private System.Windows.Forms.Button bouton_Deplacement;
        private System.Windows.Forms.TextBox Anglebox;
        private System.Windows.Forms.Label Angle_label;
        private System.Windows.Forms.TextBox FMEbox;
        private System.Windows.Forms.Label FME_label;
        private System.Windows.Forms.TextBox Ybox;
        private System.Windows.Forms.Label Y_label;
        private System.Windows.Forms.TextBox Xbox;
        private System.Windows.Forms.Label X_label;
        private System.Windows.Forms.Button Annuler_prop_boutn;
        private System.Windows.Forms.Button OK_prop_bouton;
        private System.Windows.Forms.GroupBox Group_Elements;
        private System.Windows.Forms.GroupBox Group_Element2;
        private System.Windows.Forms.Button Cible_bouton;
        private System.Windows.Forms.Button Mur_bouton;
        private System.Windows.Forms.Button Portails_bouton;
        private System.Windows.Forms.Button Trou_bouton;
        private System.Windows.Forms.Button Generateur_bouton;
        private System.Windows.Forms.Button Ressort_bouton;
        private System.Windows.Forms.GroupBox OutilGraphique;
        private System.Windows.Forms.Label labelOCourant;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.MenuStrip menuStrip3;
        private System.Windows.Forms.ToolStripMenuItem fichierToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem testRetourMenuPrincipal;
        private System.Windows.Forms.ToolStripMenuItem testRetourModeEdition;
        private System.Windows.Forms.ToolStripMenuItem caméraToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem orthographiqueToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem orbiteToolStripMenuItem1;
        private System.Windows.Forms.Button Gate;
        private System.Windows.Forms.ToolStripMenuItem gateToolStripMenuItem;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton Ouvrir_ToolStrip;
        private System.Windows.Forms.ToolStripButton Nouveau_ToolStrip;
        private System.Windows.Forms.ToolStripButton ModeTest_ToolStrip;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton MenuP_ToolStrip;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton Proprietes_ToolStrip;
        private System.Windows.Forms.ToolStripButton EnregistrerSous_ToolStrip;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripButton ZoomIn_ToolStrip;
        private System.Windows.Forms.ToolStripButton ZoomOut_ToolStrip;
        private System.Windows.Forms.ToolTip toolTipPaneauCreation;
        private System.Windows.Forms.Button bouton_Suppression;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.ToolStripButton ZoomElastique_ToolStrip;
        private System.Windows.Forms.ToolStripButton Annuler_ToolStrip;
        private System.Windows.Forms.ToolStripButton Retablir_ToolStrip;
        private System.Windows.Forms.ToolStripMenuItem Edition_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Supprimer_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Annuler_MenuItem;
        private System.Windows.Forms.ToolStripMenuItem Retablir_MenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripMenuItem SelectAll_MenuItem;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
        private System.Windows.Forms.ToolStripButton toolStripButton2;
        private System.Windows.Forms.Button Malus_bouton;
        private System.Windows.Forms.Button Bonus_bouton;
        private System.Windows.Forms.Panel panel_Tutorial;
        private System.Windows.Forms.Label tuto_label;
        private System.Windows.Forms.ToolStripButton EnregistrerS_ToolStrip;
        private System.Windows.Forms.CheckBox enableTutorialCBox;
        private System.Windows.Forms.Button Annuler_tuto_bouton;
        private System.Windows.Forms.Button Suivant_tuto_bouton;
        private System.Windows.Forms.ToolStripButton Tutorial_Toolstrip;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator6;
    }
}

