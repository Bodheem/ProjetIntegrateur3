namespace InterfaceGraphique.Fenetres
{
    partial class AchievementForm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AchievementForm));
            this.AchPanel = new System.Windows.Forms.Panel();
            this.AchTabLPanel = new System.Windows.Forms.TableLayoutPanel();
            this.titleLabel = new System.Windows.Forms.Label();
            this.pointsLabel = new System.Windows.Forms.Label();
            this.AchPB2 = new System.Windows.Forms.PictureBox();
            this.AchPB1 = new System.Windows.Forms.PictureBox();
            this.AchTimer = new System.Windows.Forms.Timer(this.components);
            this.AchPanel.SuspendLayout();
            this.AchTabLPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.AchPB2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AchPB1)).BeginInit();
            this.SuspendLayout();
            // 
            // AchPanel
            // 
            this.AchPanel.Controls.Add(this.AchTabLPanel);
            this.AchPanel.Controls.Add(this.AchPB2);
            this.AchPanel.Controls.Add(this.AchPB1);
            this.AchPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AchPanel.Location = new System.Drawing.Point(0, 0);
            this.AchPanel.Name = "AchPanel";
            this.AchPanel.Size = new System.Drawing.Size(534, 91);
            this.AchPanel.TabIndex = 0;
            // 
            // AchTabLPanel
            // 
            this.AchTabLPanel.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.AchTabLPanel.ColumnCount = 1;
            this.AchTabLPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.AchTabLPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.AchTabLPanel.Controls.Add(this.titleLabel, 0, 0);
            this.AchTabLPanel.Controls.Add(this.pointsLabel, 0, 1);
            this.AchTabLPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AchTabLPanel.Location = new System.Drawing.Point(100, 0);
            this.AchTabLPanel.Name = "AchTabLPanel";
            this.AchTabLPanel.RowCount = 2;
            this.AchTabLPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.AchTabLPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.AchTabLPanel.Size = new System.Drawing.Size(334, 91);
            this.AchTabLPanel.TabIndex = 2;
            // 
            // titleLabel
            // 
            this.titleLabel.AutoSize = true;
            this.titleLabel.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.titleLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.titleLabel.Font = new System.Drawing.Font("Stencil", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.titleLabel.ForeColor = System.Drawing.Color.Gold;
            this.titleLabel.Location = new System.Drawing.Point(3, 0);
            this.titleLabel.Name = "titleLabel";
            this.titleLabel.Size = new System.Drawing.Size(328, 45);
            this.titleLabel.TabIndex = 0;
            this.titleLabel.Text = "ACHIEV";
            this.titleLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pointsLabel
            // 
            this.pointsLabel.AutoSize = true;
            this.pointsLabel.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.pointsLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pointsLabel.Font = new System.Drawing.Font("Old English Text MT", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pointsLabel.ForeColor = System.Drawing.Color.Gold;
            this.pointsLabel.Location = new System.Drawing.Point(3, 45);
            this.pointsLabel.Name = "pointsLabel";
            this.pointsLabel.Size = new System.Drawing.Size(328, 46);
            this.pointsLabel.TabIndex = 1;
            this.pointsLabel.Text = "Points";
            this.pointsLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // AchPB2
            // 
            this.AchPB2.Dock = System.Windows.Forms.DockStyle.Right;
            this.AchPB2.Image = global::InterfaceGraphique.Properties.Resources.Trophy;
            this.AchPB2.Location = new System.Drawing.Point(434, 0);
            this.AchPB2.Name = "AchPB2";
            this.AchPB2.Size = new System.Drawing.Size(100, 91);
            this.AchPB2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.AchPB2.TabIndex = 1;
            this.AchPB2.TabStop = false;
            // 
            // AchPB1
            // 
            this.AchPB1.Dock = System.Windows.Forms.DockStyle.Left;
            this.AchPB1.Image = global::InterfaceGraphique.Properties.Resources.Trophy;
            this.AchPB1.Location = new System.Drawing.Point(0, 0);
            this.AchPB1.Name = "AchPB1";
            this.AchPB1.Size = new System.Drawing.Size(100, 91);
            this.AchPB1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.AchPB1.TabIndex = 0;
            this.AchPB1.TabStop = false;
            // 
            // AchTimer
            // 
            this.AchTimer.Interval = 10;
            this.AchTimer.Tick += new System.EventHandler(this.AchTimer_Tick);
            // 
            // AchievementForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(534, 91);
            this.Controls.Add(this.AchPanel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "AchievementForm";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "AchievementForm";
            this.TopMost = true;
            this.AchPanel.ResumeLayout(false);
            this.AchTabLPanel.ResumeLayout(false);
            this.AchTabLPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.AchPB2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AchPB1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel AchPanel;
        private System.Windows.Forms.PictureBox AchPB1;
        private System.Windows.Forms.PictureBox AchPB2;
        private System.Windows.Forms.Timer AchTimer;
        private System.Windows.Forms.TableLayoutPanel AchTabLPanel;
        private System.Windows.Forms.Label titleLabel;
        private System.Windows.Forms.Label pointsLabel;
    }
}