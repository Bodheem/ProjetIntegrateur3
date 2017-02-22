using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InterfaceGraphique
{
    class Outils
    {
        public static Dictionary<string, string> ProprieteStringToDictionnay(string prop)
        {
            Dictionary<string, string> dic = new Dictionary<string, string>();
            string[] words = prop.Split('\n');

            foreach (string line in words)
            {
                string[] details = line.Split(':');
                if (!dic.ContainsKey(details[0]))
                {
                    dic.Add(details[0], details[1]);
                }
            }

            return dic;
        }

        public static string ProprieteDictionnaryToString(Dictionary<string, string> prop)
        {
            StringBuilder sb = new StringBuilder();

            var iter = prop.GetEnumerator();
            iter.MoveNext();
            sb.Append(iter.Current.Key + ":" + iter.Current.Value);

            while (iter.MoveNext())
            {
                sb.AppendLine();
                sb.Append(iter.Current.Key + ":" + iter.Current.Value);
            }

            return sb.ToString();
        }

        public static StringBuilder zoneDefaut = new StringBuilder("zones/default.xml");

        public static StringBuilder zoneTemp = new StringBuilder("zones/zoneTemp.bin");

        public static  Dictionary<string,int> avatarPrices = new Dictionary<string, int>()
        {
            {"AV010",50},
            {"AV011",75},
            {"AV012",15},
            {"AV013",35},
            {"AV014",100},
            {"AV015",200},
            {"AV016",20},
            {"AV017",150},
            {"AV018",69},
            {"AV019",45}
        };

        public static Dictionary<string, int> mapPrices = new Dictionary<string, int>()
        {
            {"M1",500},
            {"M2",750},
            {"M3",150},
            {"M4",350},
            {"M5",100},
            {"M6",200},
            {"M7",200},
            {"M8",150},
            {"M9",690},
            {"M10",450}
        };


        public static Dictionary<string, Achievement> AchievementDictionary = new Dictionary<string, Achievement>();


    }
    
    // BECAUSE IT WAS FUCKING TIME FOR THIS DUMB SHIT
    class Achievement
    {
        public string title;
        public int points;

        public Achievement(string achTitle, int achPoints)
        {
            title = achTitle;
            points = achPoints;
        }
        // EVEN MORE SHIT THAT IM TOO LAZY TO CODE BECAUSE FUCK, WE'LL DO IT LIVE
    }
}
