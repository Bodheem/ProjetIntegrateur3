using System;

namespace InterfaceGraphique
{
    /// <summary>
    /// Objet contenant les messages du tutoriel et les méthodes de mise à jour
    /// </summary>
    class Tutoriel
    {

        #region messages
        #region Messages Editeur
        private string f1 = "Bienvenue dans le tutoriel de Painball! Vous pouvez interrompre ce turoriel à n'importe quel moment en appuyant sur le bouton 'Annuler'.\n\n Pour continuer, appuyez sur le bouton 'Suivant'.";
      //  private string f2 = "Commençons par quelque-chose de simple. Pour placer un butoir circulaire, cliquez sur l'icône du coeur dans le menu à droite, puis placez le à l'endroit désiré sur la table.\n\nPlacez un butoir maintenant!";
        private string f2 = "Pour placer un butoir circulaire, cliquez sur l'icône du coeur dans le menu à droite, puis placez le à l'endroit désiré sur la table.\n\nPlacez un butoir maintenant!";        
        private string f3 = "Sélectionnez le coeur, puis utilisez le panneau d'outils à gauche pour effectuer des transformations.\n\n Tentez de déplacer le coeur!";
        private string f4 = "Pour créer des portails, placez d'abord le premier, puis cliquez dans un autre endroit pour placer le deuxième.\n\n Placez un portail maintenant!";
        private string f5 = "Le murs s'étirent jusqu'à l'endroit de votre deuxième clic.\n\n Ajoutez un mur à la table!";
        private string f6 = "Assurez-vous de placer un générateur, un ressort et un trou pour que la zone soit jouable.\n\n Appuyez sur 'Suivant' lorsque vous avez terminé."; 
        private string f7 = "Testez votre zone à l'aide du bouton 'Tester' dans la barre d'outils.\n\n Appuyez sur 'Suivant' lorsque vous avez terminé.";
        private string f8 = "Si vous voulez, sauvegardez la zone dans le menu 'fichier'.\n\n Appuyez sur 'Suivant' lorsque vous avez terminé.";
        private string f9 = "Félicitations! Vous avez terminé le tutoriel de l'éditeur. Cliquez sur 'suivant' pour quitter.";

        private string a1 = "Welcome to the Painball tutorial! You can interrupt this tutorial at any time by pressing the 'Cancel' button.\n\n To continue, click 'Next'.";
        private string a2 = "To place a circular bumper, click on the heart icon in the right-side menu and place it at the desired location on the table.\n\n Place a bumper now!";
        private string a3 = "Select the bumper by clicking on it and then use the left 'tools' panel to transform the object.\n\n Try moving the heart now!";
        private string a4 = "To create portals, start by placing the first portal, thne click on another location to place the linked portal.\n\n Create a portal now!";
        private string a5 = "The walls are stretched to the location of your second click.\n\n Add a wall to the table now!";
        private string a6 = "Make sure to place a generator, a spring and a hole to make the zone playable.\n\n Press 'Next' when you're done.";
        private string a7 = "Test your zone with the 'test' button in the tool strip.\n\n Press 'Next' when you're done.";
        private string a8 = "If you wish, save the zone in the 'File' menu.\n\n Press 'Next' when you're done.";
        private string a9 = "Congratulations! You've completed the editor Tutorial! Press 'Next' to quit.";
        #endregion

        #region Messages Mode Jeu
        private string m1 = "Bienvenue dans le tutoriel des modes de jeu de Painball! Vous pouvez quitter ce tutoriel à tout momment en appuyant sur le bouton 'Annuler'.\n\nAppuyez sur 'Suivant' pour continuer";
        private string m2 = "Voici l'interface de création de partie multijoueur. Nous utiliserons cette interface pour la démonstration. L'interface solo est semblable, mais plus simple et comporte les mêmes modes de jeu montrés ici.";
        private string m3 = "Commençons par choisir une zone! Sélectionnez-là dans la liste de gauche et appuyez sur 'Ajouter' lorsque votre choix est fait.";
        private string m4 = "Bon choix! Vous pouvez remarquer que la partie est par défaut en mode 'coopératif' Ce mode permet au joueurs de contrôler chacun un ensemble de palettes et de travailler ensemble pour amasser un maximum de points!\n\nCliquez sur le carré à côté de 'coopératif' pour basculer en mode 'Competitif'.";
        private string m5 = "La partie est maintenant en mode 'Compétitif'. Dans ce mode, les joueurs contrôlent une instance de palettes et tentent de marquer plus de points que leurs adversaires.\n\n Mettez maintenant la partie en mode 'Mort Instantanée'.";
        private string m6 = "En mode 'Mort subite', les joueurs n'ont qu'une seule bille et ne peuvent pas en gagner d'autres.\n\nPassez maintenant en mode 'Temps Limité'.";
        private string m7 = "En mode 'Temps Limité', les joueurs disposent d'un temps limité pour gagner.\n\n Finalisez vos paramètres de partie et cliquez sur 'Suivant'.";
        private string m8 = "Félicitations! Cela conclut le tutoriel sur les modes de jeu. Vous savez maintenant comment créer une partie et le fonctionnement des modes de jeu de PainBall.\n\n Ciquez sur 'Suivant' pour retourner au menu principal.";

        private string j1 = "Welcome to the Painball game modes tutorial! You can interrupt this tutorial at any time by pressing the 'Cancel' button.\n\n To continue, click 'Next'.";
        private string j2 = "This is the multiplayer 'Create game' interface. We'll use this interface for the demonstration. The Solo interface is similar, although simpler and has the same game modes shown here.";
        private string j3 = "Let's start by selecting a zone! Select it from the left list and click 'Add' when your choice is made.";
        private string j4 = "Good choice! Notice that the game is is 'Coop' mode. In this mode, players control their own flipper set and work together to make a maximum of points! \n\nClick on the button left of 'Coop' to switch to 'Versus' mode.";
        private string j5 = "The game is now in 'Versus' mode. in this mode, players control a flipper instance and try to score the most points.\n\nNow, activate 'Sudden Death' mode.";
        private string j6 = "In 'Sudden Death' mode, players have only one ball and can't win more. Now activate 'Time Attack' mode.";
        private string j7 = "In 'Time Attack' mode, players have a limited time to win.\n\n Finalize your game settings and click on 'Next'.";
        private string j8 = "Congratulations! This concludes the game modes tutorial. You now know how to create a game and how the game modes work in PainBall.\n\n Click 'Next' to go back to the main menu.";

        #endregion
        #endregion


        public int CurrentMessage;
        public int CurrentMessageGame;

        /// <summary>
        /// constructeur par défaut
        /// </summary>
        public Tutoriel()
        {
            CurrentMessage = 1;
        }

        //**** MÉTHODES ****

        /// <summary>
        /// charge le premier message du tutoriel selon la langue
        /// </summary>
        /// <returns>le premier message</returns>
        public string initTutorial()
        {
            string lang = Langages.Langage.getCurrentLangage();
            CurrentMessage = 1;
            if (lang == "fr")
                return f1;
            else return a1;
        }

        public string initTutorialGame()
        {
            string lang = Langages.Langage.getCurrentLangage();
            CurrentMessageGame = 1;
            if (lang == "fr")
                return m1;
            else return j1;
        }

        /// <summary>
        /// Retourne Le string suivant de index pour le panel du tutoriel.
        /// </summary>
        /// <returns>message mis à jour</returns>
        public string manualUpdateMessage(int index)
        {
            string next = "";
            string lang = Langages.Langage.getCurrentLangage();

            if (lang == "fr")
            {
                switch (index)
                {
                    case 1:
                        next = f2;
                        CurrentMessage = 2;
                        break;
                    case 2:
                        next = f3;
                        CurrentMessage = 3;
                        break;
                    case 3:
                        next = f4;
                        CurrentMessage = 4;
                        break;
                    case 4:
                        next = f5;
                        CurrentMessage = 5;
                        break;
                    case 5:
                        next = f6;
                        CurrentMessage = 6;
                        break;
                    case 6:
                        next = f7;
                        CurrentMessage = 7;
                        break;
                    case 7:
                        next = f8;
                        CurrentMessage = 8;
                        break;
                    case 8:
                        next = f9;
                        CurrentMessage = 9;
                        break;
                    case 9:
                        next = "END";
                        break;
                }
            }
            else if (lang == "en")
            {
                switch (index)
                {
                    case 1:
                        next = a2;
                        CurrentMessage = 2;
                        break;
                    case 2:
                        next = a3;
                        CurrentMessage = 3;
                        break;
                    case 3:
                        next = a4;
                        CurrentMessage = 4;
                        break;
                    case 4:
                        next = a5;
                        CurrentMessage = 5;
                        break;
                    case 5:
                        next = a6;
                        CurrentMessage = 6;
                        break;
                    case 6:
                        next = a7;
                        CurrentMessage = 7;
                        break;
                    case 7:
                        next = a8;
                        CurrentMessage = 8;
                        break;
                    case 8:
                        next = a9;
                        CurrentMessage = 9;
                        break;
                    case 9:
                        next = "END";
                        break;
                }
            }
            else
            {
                Exception unknownLanguageException = new Exception();
                throw unknownLanguageException;
            }
            return next;
        }


        public string manualUpdateMessageGame(int index)
        {
            string next = "";
            string lang = Langages.Langage.getCurrentLangage();

            if (lang == "fr")
            {
                switch (index)
                {
                    case 1:
                        next = m2;
                        CurrentMessageGame = 2;
                        break;
                    case 2:
                        next = m3;
                        CurrentMessageGame = 3;
                        break;
                    case 3:
                        next = m4;
                        CurrentMessageGame = 4;
                        break;
                    case 4:
                        next = m5;
                        CurrentMessageGame = 5;
                        break;
                    case 5:
                        next = m6;
                        CurrentMessageGame = 6;
                        break;
                    case 6:
                        next = m7;
                        CurrentMessageGame = 7;
                        break;
                    case 7:
                        next = m8;
                        CurrentMessageGame = 8;
                        break;
                    case 8:
                        next = "END";
                        break;
                }
            }
            else if (lang == "en")
            {
                switch (index)
                {
                    case 1:
                        next = j2;
                        CurrentMessageGame = 2;
                        break;
                    case 2:
                        next = j3;
                        CurrentMessageGame = 3;
                        break;
                    case 3:
                        next = j4;
                        CurrentMessageGame = 4;
                        break;
                    case 4:
                        next = j5;
                        CurrentMessageGame = 5;
                        break;
                    case 5:
                        next = j6;
                        CurrentMessageGame = 6;
                        break;
                    case 6:
                        next = j7;
                        CurrentMessageGame = 7;
                        break;
                    case 7:
                        next = j8;
                        CurrentMessageGame = 8;
                        break;
                    case 8:
                        next = "END";
                        break;
                }
            }
            else
            {
                Exception unknownLanguageException = new Exception();
                throw unknownLanguageException;
            }
            return next;
        }
        /// <summary>
        /// fonction de mise à jour automatique du tutoriel
        /// </summary>
        /// <returns> message mis à jour</returns>
        public string updateMessage()
        {
            return manualUpdateMessage(CurrentMessage);
        }
        public string updateMessageGame()
        {
            return manualUpdateMessageGame(CurrentMessageGame);
        }
    }
}
