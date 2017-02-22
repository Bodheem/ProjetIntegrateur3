using System.Drawing;

namespace InterfaceGraphique
{
    partial class ChatForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ChatForm));
            this.ChatOutput = new System.Windows.Forms.RichTextBox();
            this.ChatInput = new System.Windows.Forms.RichTextBox();
            this.ChatPanel = new System.Windows.Forms.Panel();
            this.minimizeButton = new System.Windows.Forms.Button();
            this.TextToSpeechButton = new System.Windows.Forms.Button();
            this.SendMsgBtn = new System.Windows.Forms.Button();
            this.UnlockBtn = new System.Windows.Forms.Button();
            this.nextRoomBtn = new System.Windows.Forms.Button();
            this.RoomNameLabel = new System.Windows.Forms.Label();
            this.chatTimer = new System.Windows.Forms.Timer(this.components);
            this.ChatPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // ChatOutput
            // 
            this.ChatOutput.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ChatOutput.BackColor = System.Drawing.Color.Black;
            this.ChatOutput.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.ChatOutput.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.ChatOutput.Font = new System.Drawing.Font("Times New Roman", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ChatOutput.ForeColor = System.Drawing.Color.White;
            this.ChatOutput.HideSelection = false;
            this.ChatOutput.Location = new System.Drawing.Point(0, 41);
            this.ChatOutput.MaximumSize = new System.Drawing.Size(432, 175);
            this.ChatOutput.MinimumSize = new System.Drawing.Size(430, 0);
            this.ChatOutput.Name = "ChatOutput";
            this.ChatOutput.ReadOnly = true;
            this.ChatOutput.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical;
            this.ChatOutput.Size = new System.Drawing.Size(432, 175);
            this.ChatOutput.TabIndex = 2;
            this.ChatOutput.Text = "";
            // 
            // ChatInput
            // 
            this.ChatInput.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ChatInput.BackColor = System.Drawing.SystemColors.InfoText;
            this.ChatInput.Font = new System.Drawing.Font("Times New Roman", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ChatInput.ForeColor = System.Drawing.Color.White;
            this.ChatInput.Location = new System.Drawing.Point(0, 214);
            this.ChatInput.MaximumSize = new System.Drawing.Size(339, 45);
            this.ChatInput.MinimumSize = new System.Drawing.Size(339, 4);
            this.ChatInput.Name = "ChatInput";
            this.ChatInput.Size = new System.Drawing.Size(339, 45);
            this.ChatInput.TabIndex = 2;
            this.ChatInput.Text = "";
            this.ChatInput.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.ChatInput_KeyPress);
            // 
            // ChatPanel
            // 
            this.ChatPanel.BackColor = System.Drawing.Color.Black;
            this.ChatPanel.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.ChatPanel.Controls.Add(this.minimizeButton);
            this.ChatPanel.Controls.Add(this.TextToSpeechButton);
            this.ChatPanel.Controls.Add(this.SendMsgBtn);
            this.ChatPanel.Controls.Add(this.UnlockBtn);
            this.ChatPanel.Controls.Add(this.nextRoomBtn);
            this.ChatPanel.Controls.Add(this.RoomNameLabel);
            this.ChatPanel.Controls.Add(this.ChatOutput);
            this.ChatPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ChatPanel.Location = new System.Drawing.Point(0, 0);
            this.ChatPanel.MinimumSize = new System.Drawing.Size(431, 40);
            this.ChatPanel.Name = "ChatPanel";
            this.ChatPanel.Size = new System.Drawing.Size(431, 261);
            this.ChatPanel.TabIndex = 1;
            // 
            // minimizeButton
            // 
            this.minimizeButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.minimizeButton.BackColor = System.Drawing.Color.Transparent;
            this.minimizeButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.buttonStock1;
            this.minimizeButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.minimizeButton.FlatAppearance.BorderSize = 0;
            this.minimizeButton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.minimizeButton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.minimizeButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.minimizeButton.Font = new System.Drawing.Font("Moire ExtraBold", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.minimizeButton.ForeColor = System.Drawing.Color.Gold;
            this.minimizeButton.Location = new System.Drawing.Point(394, 3);
            this.minimizeButton.Name = "minimizeButton";
            this.minimizeButton.Size = new System.Drawing.Size(25, 25);
            this.minimizeButton.TabIndex = 8;
            this.minimizeButton.Text = "_";
            this.minimizeButton.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.minimizeButton.UseVisualStyleBackColor = false;
            this.minimizeButton.Click += new System.EventHandler(this.minimizeButton_Click);
            this.minimizeButton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.minimizeButton.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.minimizeButton.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.minimizeButton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // TextToSpeechButton
            // 
            this.TextToSpeechButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.TextToSpeechButton.BackColor = System.Drawing.Color.Transparent;
            this.TextToSpeechButton.BackgroundImage = global::InterfaceGraphique.Properties.Resources.buttonStock1;
            this.TextToSpeechButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.TextToSpeechButton.FlatAppearance.BorderSize = 0;
            this.TextToSpeechButton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.TextToSpeechButton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.TextToSpeechButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.TextToSpeechButton.Font = new System.Drawing.Font("Moire ExtraBold", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextToSpeechButton.ForeColor = System.Drawing.Color.Gold;
            this.TextToSpeechButton.Location = new System.Drawing.Point(332, 3);
            this.TextToSpeechButton.Name = "TextToSpeechButton";
            this.TextToSpeechButton.Size = new System.Drawing.Size(25, 25);
            this.TextToSpeechButton.TabIndex = 7;
            this.TextToSpeechButton.Text = "Ø";
            this.TextToSpeechButton.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.TextToSpeechButton.UseVisualStyleBackColor = false;
            this.TextToSpeechButton.Click += new System.EventHandler(this.TextToSpeechButton_Click);
            // 
            // SendMsgBtn
            // 
            this.SendMsgBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.SendMsgBtn.BackColor = System.Drawing.Color.Transparent;
            this.SendMsgBtn.BackgroundImage = global::InterfaceGraphique.Properties.Resources.buttonStock1;
            this.SendMsgBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.SendMsgBtn.FlatAppearance.BorderSize = 0;
            this.SendMsgBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.SendMsgBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.SendMsgBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.SendMsgBtn.ForeColor = System.Drawing.Color.Gold;
            this.SendMsgBtn.Location = new System.Drawing.Point(342, 214);
            this.SendMsgBtn.MaximumSize = new System.Drawing.Size(86, 45);
            this.SendMsgBtn.MinimumSize = new System.Drawing.Size(86, 0);
            this.SendMsgBtn.Name = "SendMsgBtn";
            this.SendMsgBtn.Size = new System.Drawing.Size(86, 45);
            this.SendMsgBtn.TabIndex = 6;
            this.SendMsgBtn.Text = "Send";
            this.SendMsgBtn.UseVisualStyleBackColor = false;
            this.SendMsgBtn.Click += new System.EventHandler(this.SendMsgBtn_Click);
            this.SendMsgBtn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseDown);
            this.SendMsgBtn.MouseEnter += new System.EventHandler(this.GenericButtonMouseEnter);
            this.SendMsgBtn.MouseLeave += new System.EventHandler(this.GenericButtonMouseLeave);
            this.SendMsgBtn.MouseUp += new System.Windows.Forms.MouseEventHandler(this.GenericButtonMouseUp);
            // 
            // UnlockBtn
            // 
            this.UnlockBtn.BackColor = System.Drawing.Color.White;
            this.UnlockBtn.BackgroundImage = global::InterfaceGraphique.Properties.Resources.scale1;
            this.UnlockBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.UnlockBtn.FlatAppearance.BorderSize = 0;
            this.UnlockBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.DimGray;
            this.UnlockBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.DimGray;
            this.UnlockBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.UnlockBtn.Location = new System.Drawing.Point(12, 3);
            this.UnlockBtn.Name = "UnlockBtn";
            this.UnlockBtn.Size = new System.Drawing.Size(25, 25);
            this.UnlockBtn.TabIndex = 5;
            this.UnlockBtn.UseVisualStyleBackColor = false;
            this.UnlockBtn.Click += new System.EventHandler(this.UnlockBtn_Click);
            // 
            // nextRoomBtn
            // 
            this.nextRoomBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.nextRoomBtn.BackColor = System.Drawing.Color.Transparent;
            this.nextRoomBtn.BackgroundImage = global::InterfaceGraphique.Properties.Resources.buttonStock1;
            this.nextRoomBtn.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.nextRoomBtn.FlatAppearance.BorderSize = 0;
            this.nextRoomBtn.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.nextRoomBtn.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.nextRoomBtn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.nextRoomBtn.Font = new System.Drawing.Font("Moire ExtraBold", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nextRoomBtn.ForeColor = System.Drawing.Color.Gold;
            this.nextRoomBtn.Location = new System.Drawing.Point(363, 3);
            this.nextRoomBtn.Name = "nextRoomBtn";
            this.nextRoomBtn.Size = new System.Drawing.Size(25, 25);
            this.nextRoomBtn.TabIndex = 4;
            this.nextRoomBtn.Text = ">";
            this.nextRoomBtn.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            this.nextRoomBtn.UseVisualStyleBackColor = false;
            this.nextRoomBtn.Click += new System.EventHandler(this.nextRoomBtn_Click);
            // 
            // RoomNameLabel
            // 
            this.RoomNameLabel.BackColor = System.Drawing.SystemColors.ControlText;
            this.RoomNameLabel.Dock = System.Windows.Forms.DockStyle.Top;
            this.RoomNameLabel.Font = new System.Drawing.Font("Times New Roman", 26.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RoomNameLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(64)))), ((int)(((byte)(0)))));
            this.RoomNameLabel.Location = new System.Drawing.Point(0, 0);
            this.RoomNameLabel.Name = "RoomNameLabel";
            this.RoomNameLabel.Size = new System.Drawing.Size(431, 40);
            this.RoomNameLabel.TabIndex = 3;
            this.RoomNameLabel.Text = "General";
            this.RoomNameLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // chatTimer
            // 
            this.chatTimer.Interval = 1000;
            this.chatTimer.Tick += new System.EventHandler(this.chatTimer_Tick);
            // 
            // ChatForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(431, 261);
            this.ControlBox = false;
            this.Controls.Add(this.ChatInput);
            this.Controls.Add(this.ChatPanel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(431, 261);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(431, 40);
            this.Name = "ChatForm";
            this.Text = "ChatForm";
            this.TopMost = true;
            this.TransparencyKey = System.Drawing.SystemColors.InactiveBorder;
            this.Activated += new System.EventHandler(this.ChatForm_Activated);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ChatForm_FormClosing);
            this.Load += new System.EventHandler(this.ChatForm_Load);
            this.Shown += new System.EventHandler(this.ChatForm_Shown);
            this.Enter += new System.EventHandler(this.ChatForm_Load);
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.ChatForm_KeyPress);
            this.ChatPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox ChatOutput;
        private System.Windows.Forms.RichTextBox ChatInput;
        private System.Windows.Forms.Panel ChatPanel;
        private System.Windows.Forms.Label RoomNameLabel;
        private System.Windows.Forms.Button nextRoomBtn;
        private System.Windows.Forms.Button UnlockBtn;
        private System.Windows.Forms.Button SendMsgBtn;
        private System.Windows.Forms.Timer chatTimer;
        private System.Windows.Forms.Button TextToSpeechButton;
        private System.Windows.Forms.Button minimizeButton;



    }
}