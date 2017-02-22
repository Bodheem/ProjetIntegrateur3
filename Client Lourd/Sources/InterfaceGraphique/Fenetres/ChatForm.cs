using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Text;
using System.Linq;
using System.Media;
using System.Runtime.InteropServices;
using System.Runtime.Remoting.Channels;
using System.Speech.Synthesis;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using System.Windows.Forms.VisualStyles;
using InterfaceGraphique.Properties;

namespace InterfaceGraphique
{
    public partial class ChatForm : Form
    {
        private List<String> chatRooms;     /// Liste des salles
        private String chatRoomChain;       /// Liste des salles en format d'un seul string
        private int currentChat = 0;        /// L'index du chat courrant
        public System.Timers.Timer threadTimer; /// Timer du message-polling
        public System.Timers.Timer displayTimer;/// Timer du message-polling
        public Stopwatch stopwatch;
        private object _timerLock = new object();   /// Mutex sur le thread
        private object _timerLock2 = new object();
        private bool firstConnect = true;       /// booleen qui verifie si c'est la premiere connexion
        public Thread messageThread = null;            /// Thread qui fait le message-polling
        public Thread displayThread;
        public Thread soundThread;
        private SpeechSynthesizer speaker;
        public bool swapMPRoom;

        public bool connected;
        private bool talkShit = false;
        private static Mutex messageMutex;

        Queue<Tuple<string, string> > sendMessageQueue;
        Queue<string> showMessageQueue;


        System.Media.SoundPlayer player; ///< Sound Player.
        private PrivateFontCollection fonts = new PrivateFontCollection();

        Font myFont;



        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ChatForm()
        /// @brief Fonction qui construit la Form. Elle va chercher la liste
        ///        des chambres et la mets a jour.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        public ChatForm()
        {
            InitializeComponent();
            firstConnect = true;
            //byte[] fontData = Properties.Resources.diablo_h;
            //IntPtr fontPtr = System.Runtime.InteropServices.Marshal.AllocCoTaskMem(fontData.Length);
            //System.Runtime.InteropServices.Marshal.Copy(fontData, 0, fontPtr, fontData.Length);
            //uint dummy = 0;
            //fonts.AddMemoryFont(fontPtr, Properties.Resources.diablo_h.Length);
            //FonctionsNatives.AddFontMemResourceEx(fontPtr, (uint)Properties.Resources.diablo_h.Length, IntPtr.Zero, ref dummy);
            //System.Runtime.InteropServices.Marshal.FreeCoTaskMem(fontPtr);

            //myFont = new Font(fonts.Families[0], 10.5F);
            //ChatOutput.Font = myFont;
            //myFont = new Font(fonts.Families[0], 14.0F);
            //ChatInput.Font = myFont;


            speaker = new SpeechSynthesizer();
         

            stopwatch = new Stopwatch();
            connected = true;
            chatRooms = new List<string>();
            sendMessageQueue = new Queue<Tuple<string, string>>();
            showMessageQueue = new Queue<string>();
            messageMutex = new Mutex();
            chatRoomChain = FonctionsNatives.GetLobbies();
            chatRooms = chatRoomChain.Split('\n').ToList();
            chatRooms.RemoveAt(chatRooms.Count - 1);
            Activate();
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ChatForm_Activated(object sender, EventArgs e)
        /// @brief Fonction qui est lance lorsque la form est active.
        ///        Le thread du message-polling est lance avec un timer
        ///        de 250ms qui va lire les messages du serveur
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ChatForm_Activated(object sender, EventArgs e)
        {
            if (messageThread == null)
            {
                messageThread = new Thread(DoWork);
                messageThread.Start();                
            }
           
            chatTimer.Start();


        }

        // Seconday thread operation
        public void DoWork()
        {

            Thread.Sleep(10);
            while (connected)
            {
                Thread.Sleep(10);
                messageMutex.WaitOne();
                if (sendMessageQueue.Count != 0)
                {
                    Tuple<string, string> messageToSend = sendMessageQueue.Dequeue();
                    messageMutex.ReleaseMutex();
                    byte[] sendingMessage = Encoding.UTF8.GetBytes(messageToSend.Item1);
                    byte[] sendingRoom = Encoding.UTF8.GetBytes(messageToSend.Item2);
                  //  Console.WriteLine("MESSAGE BEGIN SEND AT : " + DateTime.Now.ToString("hh.mm.ss.ffffff"));                    
                    FonctionsNatives.SendChatMessage(sendingRoom, sendingMessage);
                 //   Console.WriteLine("MESSAGE END SEND AT : " + DateTime.Now.ToString("hh.mm.ss.ffffff"));
                }
                else
                {
                    messageMutex.ReleaseMutex();
                }
                Thread.Sleep(10);

                //  Console.WriteLine("MESSAGE BEGIN GETHISTORY AT : " + DateTime.Now.ToString("hh.mm.ss.ffffff"));
                if (!FonctionsNatives.GetChatHistoryUpdates())
                {
                    if (Owner != null)
                    {
                        ((MenuComplet)Owner).failCounter++;
                        Console.WriteLine("butt");
                        Invoke(new Action(() =>
                        {
                            if (((MenuComplet) Owner).failCounter > 5)
                            {
                                ((MenuComplet) Owner).totalDisconnect();
                                
                            }
                        }));

                         continue;
                    }
                }
                else
                {
                    if (Owner != null)
                    {
                        ((MenuComplet)Owner).failCounter = 0;
                    }
                }
                //  Console.WriteLine("MESSAGE END GETHISTORY AT : " + DateTime.Now.ToString("hh.mm.ss.ffffff"));

                if (firstConnect)
                {
                    firstConnect = false;
                    StringBuilder currRoom = new StringBuilder(chatRooms[currentChat]);
                    string messages = FonctionsNatives.GetAllMessages(currRoom);
                    byte[] messsageBytes = Encoding.Default.GetBytes(messages);
                    var myReturnedString = Encoding.UTF8.GetString(messsageBytes, 0, messsageBytes.Length);

                    if (!String.IsNullOrWhiteSpace(myReturnedString))
                    {
                        messageMutex.WaitOne();
                        showMessageQueue.Enqueue(myReturnedString);
                        messageMutex.ReleaseMutex();

                    }

                }
                else
                {
                    StringBuilder currRoom = new StringBuilder(chatRooms[currentChat]);

                    string messages = FonctionsNatives.GetMessages(currRoom);

                    byte[] messsageBytes = Encoding.Default.GetBytes(messages);
                    var myReturnedString = Encoding.UTF8.GetString(messsageBytes, 0, messsageBytes.Length);
                    if (!String.IsNullOrWhiteSpace(myReturnedString))
                    {
                        messageMutex.WaitOne();
                        showMessageQueue.Enqueue(myReturnedString);
                       // Console.WriteLine("MESSAGE RECEIVED AT : " + DateTime.Now.ToString("hh.mm.ss.ffffff"));
                        messageMutex.ReleaseMutex();
                    }
                }

               

            }
        }


        public void MultiplayerRoomSelect()
        {
            
                while (!RoomNameLabel.Text.StartsWith("GameRoom"))
                {
                    nextRoomBtn.PerformClick();
                }
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ChatForm_Load(object sender, EventArgs e)
        /// @brief Fonction qui place le chat en bas a gauche lorsque le chat est lancee.
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ChatForm_Load(object sender, EventArgs e)
        {
            // CHAT IS ON THE LEFT
            this.Location = new Point(Screen.PrimaryScreen.WorkingArea.Left, Screen.PrimaryScreen.WorkingArea.Bottom - this.Height + 0);
          

        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ChatInput_KeyPress(object sender, EventArgs e)
        /// @brief Fonction qui permet d'utiliser le bouton ENTER pour
        ///        envoyer un message.
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ChatInput_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 13)
            {
                e.Handled = true;
              SendMsgBtn_Click(sender,e);
        
            }
            ChatForm_KeyPress(sender, e);
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void nextRoomBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet d'aller a la prochaine chambe de conversation.
        ///        Lorsqu'on atteigne la fin de la List, on boucle au debut
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void nextRoomBtn_Click(object sender, EventArgs e)
        {
            chatRoomChain = FonctionsNatives.GetLobbies();
            chatRooms = chatRoomChain.Split('\n').ToList();
            chatRooms.RemoveAt(chatRooms.Count - 1);
            if (chatRooms.Count > 1 || RoomNameLabel.Text != "General")
            {
                
                if (chatRooms.Contains(RoomNameLabel.Text))
                {
                    currentChat++;
                    if (currentChat >= chatRooms.Count)
                    {
                        currentChat = 0;
                    }
                }
                else
                {
                    // Case ou on a delete tous les rooms sauf general
                    currentChat = 0;
                }

                //speaker.Dispose();

                RoomNameLabel.Text = chatRooms[currentChat];
                ChatOutput.Clear();
                firstConnect = true;
            }
           
        }

        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void UnlockBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui permet de LOCK/UNLOCK la Form de chat 
        ///        Lorsque le chat est mobile, le fond d'ecran est noir solide
        ///        Sinon, le chat est transparent.
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void UnlockBtn_Click(object sender, EventArgs e)
        {
            if (FormBorderStyle == FormBorderStyle.None)
            {
                FormBorderStyle = FormBorderStyle.Sizable;
                ChatOutput.BackColor = Color.Black;
                MaximumSize = new Size(0, 0);
                MinimumSize = new Size(431,281);

                ChatInput.MaximumSize = new Size(0,0);
                ChatOutput.MaximumSize = new Size(0,0);
                ChatInput.MinimumSize = new Size(339, 35);
                ChatOutput.MinimumSize = new Size(432, 100);
                ChatPanel.BackColor = Color.Black;
            }
            else
            {
                // Puts it back locked down
                MaximumSize = new Size(431,261);
                MinimumSize = new Size(431, 40);

                ChatInput.MaximumSize = new Size(339, 45);
                ChatOutput.MaximumSize = new Size(432, 175);
                ChatInput.MinimumSize = new Size(339, 0);
                ChatOutput.MinimumSize = new Size(430, 0);

                FormBorderStyle = FormBorderStyle.None;
                Size = MaximumSize;
                this.Location = new Point(Screen.PrimaryScreen.WorkingArea.Left, Screen.PrimaryScreen.WorkingArea.Bottom - this.Height + 0);

            }
        
        }


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void chatTimer_Tick(object sender, EventArgs e)
        /// @brief Fonction qui va etre appelle chaque X ms
        ///        a Chaque appel, C# va poll le C++ pour avoir les nouveaux messages
        ///        et les mets dans le ChatOutput
        /// @param[in] sender : Objet duquel provient un evenement
        /// @param[in] e : evenement qui lance la fonction.
        /// 
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void chatTimer_Tick(object sender, EventArgs e)
        {
            // STOP LE TIMER
            chatTimer.Stop();

            chatTimer.Interval = 100;
            messageMutex.WaitOne();
            if (showMessageQueue.Count != 0)
            {
                string message = showMessageQueue.Dequeue();
                messageMutex.ReleaseMutex();
                if (talkShit)
                {
                   soundThread = null;
                   Task mytask = Task.Run(() =>
                    {
                            soundThread = Thread.CurrentThread;
                            speaker.Rate = 1;
                            speaker.Volume = 100;
                            string user = message.Split(':').First().Split(' ').Last();
                            speaker.SelectVoiceByHints(VoiceGender.Male, VoiceAge.Child);
                            speaker.SpeakAsync(user + " said " + message.Split(':').Last());

                    });
                }

                ChatOutput.AppendText(message);
                player = new System.Media.SoundPlayer(Properties.Resources.messagePop);
                player.Play();
               // Console.WriteLine("MESSAGE PRINTED AT : " + DateTime.Now.ToString("hh.mm.ss.ffffff"));

            }
            else
            {
                messageMutex.ReleaseMutex();
            }
            chatTimer.Start();
        }


      


        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void SendMsgBtn_Click(object sender, EventArgs e)
        /// @brief Fonction qui fait l'envoie des messages du C# vers le C++.
        ///        Tout message vide ou en espaces blancs n'est pas envoye.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void SendMsgBtn_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrWhiteSpace(ChatInput.Text))
            {
            
               string sendingMessage = (ChatInput.Text.TrimStart('\r', '\n').TrimEnd('\r', '\n'));
               string sendingRoom = (chatRooms[currentChat]);
               messageMutex.WaitOne();
               Tuple<string,string> messageToSend = new Tuple<string, string>(sendingMessage,sendingRoom);
               sendMessageQueue.Enqueue(messageToSend);
               messageMutex.ReleaseMutex();
              // Console.WriteLine("MESSAGE ENQUEUED AT : " + DateTime.Now.ToString("hh.mm.ss.ffffff"));

            }
            ChatInput.Text = "";
            ChatInput.Focus();
        }


        #region Boutons
        private void GenericButtonMouseEnter(object sender, EventArgs e)
        {
            Program.ButtonMouseOver((System.Windows.Forms.Button)sender);
        }

        private void GenericButtonMouseLeave(object sender, EventArgs e)
        {
            Program.ButtonMouseLeave((System.Windows.Forms.Button)sender);

        }

        private void GenericButtonMouseDown(object sender, MouseEventArgs e)
        {
            Program.ButtonMouseDown((System.Windows.Forms.Button)sender);

        }

        private void GenericButtonMouseUp(object sender, MouseEventArgs e)
        {
            Program.ButtonMouseUp((System.Windows.Forms.Button)sender);

        }

        #endregion



        ////////////////////////////////////////////////////////////////////////
        ///
        /// @fn private void ChatForm_FormClosing(object sender, EventArgs e)
        /// @brief Fonction qui ferme la forme.
        ///        Le mutex lock et permet de bien fermer la fenetre.
        ///        Le timer est arrete a la fermeture.
        /// @return Aucune.
        ///
        ////////////////////////////////////////////////////////////////////////
        private void ChatForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            connected = false;
            if (speaker != null)
            {
                speaker.Pause();
                speaker.Dispose();
                
            }
            //soundThread.Abort();
       
        }

        private void ChatForm_Shown(object sender, EventArgs e)
        {
            // Put focus automatically
           // ChatInput.Focus();
        }

        private void TextToSpeechButton_Click(object sender, EventArgs e)
        {
            if (talkShit)
            {
                talkShit = false;
                TextToSpeechButton.Text = "Ø";
            }
            else
            {
                talkShit = true;
                TextToSpeechButton.Text = "O";
            }
        }

        private void ChatForm_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == (char) 27)
            {
                if (Program.testMenu.modeJeuMain != null)
                {
                    Program.testMenu.modeJeuMain.Focus();

                }
            }

        }

        private void minimizeButton_Click(object sender, EventArgs e)
        {
            if (FormBorderStyle == FormBorderStyle.Sizable)
            {
                UnlockBtn.PerformClick();
            }
            if (ChatOutput.Size == ChatOutput.MinimumSize)
            {
                Size = MaximumSize;
                ChatPanel.Size = ChatPanel.MaximumSize;
                ChatOutput.Size = ChatOutput.MaximumSize;
                ChatInput.Size = ChatInput.MaximumSize;
                SendMsgBtn.Size = SendMsgBtn.MaximumSize;

            }
            else
            {
                Size = MinimumSize;
                ChatPanel.Size = ChatPanel.MinimumSize;
                ChatOutput.Size = ChatOutput.MinimumSize;
                ChatInput.Size = ChatInput.MinimumSize;
                SendMsgBtn.Size = SendMsgBtn.MinimumSize;


            }
            this.Location = new Point(Screen.PrimaryScreen.WorkingArea.Left, Screen.PrimaryScreen.WorkingArea.Bottom - this.Height + 0);

        }
       

       
    }
}

