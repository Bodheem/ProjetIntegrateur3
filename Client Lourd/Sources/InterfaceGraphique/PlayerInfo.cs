using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms.VisualStyles;

namespace InterfaceGraphique
{
    public class PlayerInfo
    {
        public string userName { get; set; }
        public string playerName { get; set; }
        public string playerSurname { get; set; }
        public string playerPassword { get; set; }
        public string playerEmail { get; set; }
        public int playerAge { get; set; }
        public bool playerPublicProfile { get; set; }
        public int playerAchievementPoints { get; set; }
        public int playerCurrency { get; set; }
        public int playerPlayedGames { get; set; }
        public int playerVictories { get; set; }
        public int playerCoopVictories { get; set; }
        public int playerCompVictories { get; set; }
        public string playerAvatar { get; set; }
        public string[] unlockedAvatars = new string[] {};
        public string[] unlockedMaps = new string[] {};
        public string[] unlockedAchievements = new string[] {};
        public string unSplitAvatars = "";
        public string unSplitAchievements = "";
        public string unSplitMaps = "";


        public void UpdatePlayerInfo(Dictionary<string, string> playerInformation)
        {
            Array.Clear(unlockedAvatars, 0, unlockedAvatars.Length);
            Array.Clear(unlockedAchievements, 0, unlockedAchievements.Length);
            Array.Clear(unlockedMaps, 0, unlockedMaps.Length);


            if (playerInformation.ContainsKey("USERNAME"))
                userName = playerInformation["USERNAME"];

            if (playerInformation.ContainsKey("NAME"))
                playerName = playerInformation["NAME"];

            if (playerInformation.ContainsKey("PASSWORD"))
                playerPassword = playerInformation["PASSWORD"];


            if (playerInformation.ContainsKey("SURNAME"))
                playerSurname = playerInformation["SURNAME"];

            if (playerInformation.ContainsKey("COURRIEL"))
                playerEmail = playerInformation["COURRIEL"];

            if (playerInformation.ContainsKey("SHEKELS"))
                playerCurrency = Convert.ToInt32(playerInformation["SHEKELS"]);

            if (playerInformation.ContainsKey("AGE"))
                playerAge = Convert.ToInt32(playerInformation["AGE"]);

            if (playerInformation.ContainsKey("ACHIEVEMENT_POINT"))
                playerAchievementPoints = Convert.ToInt32(playerInformation["ACHIEVEMENT_POINT"]);

            if (playerInformation.ContainsKey("IS_PUBLIC"))
                playerPublicProfile = playerInformation["IS_PUBLIC"] == "1" ? true : false;

            if (playerInformation.ContainsKey("AVATAR"))
            {
                playerAvatar = playerInformation["AVATAR"];
                
            }

            if (playerInformation.ContainsKey("GAMES_PLAYED"))
            {
                playerPlayedGames = Convert.ToInt32(playerInformation["GAMES_PLAYED"]);

            }

            if (playerInformation.ContainsKey("GAMES_WON"))
            {
                playerVictories = Convert.ToInt32(playerInformation["GAMES_WON"]);

            }

            if (playerInformation.ContainsKey("GAMES_COMP_WON"))
            {
                playerCompVictories = Convert.ToInt32(playerInformation["GAMES_COMP_WON"]);

            }
            if (playerInformation.ContainsKey("GAMES_COOP_WON"))
            {
                playerCoopVictories = Convert.ToInt32(playerInformation["GAMES_COOP_WON"]);

            }


            if (playerInformation.ContainsKey("AVATAR_UNLOCKED"))
            {
                unSplitAvatars = playerInformation["AVATAR_UNLOCKED"];
                unlockedAvatars = unSplitAvatars.Split(',');
               
              
            }

            if (playerInformation.ContainsKey("ACHIEVEMENT_UNLOCKED"))
            {
                unSplitAchievements = playerInformation["ACHIEVEMENT_UNLOCKED"];
                unlockedAchievements = unSplitAchievements.Split(',');
                //foreach (var a in unlockedAchievements)
                //{
                //    Console.WriteLine(a);
                //}
            }

            if (playerInformation.ContainsKey("MAP_UNLOCKED"))
            {
                unSplitMaps = playerInformation["MAP_UNLOCKED"];
                unlockedMaps = unSplitMaps.Split(',');
                //foreach (var a in unlockedAchievements)
                //{
                //    Console.WriteLine(a);
                //}
            }
            
        }
    }
}
