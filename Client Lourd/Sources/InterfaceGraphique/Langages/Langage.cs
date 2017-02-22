using System;
using System.Globalization;


namespace InterfaceGraphique.Langages
{
    class Langage
    {
        private static CultureInfo ci;

        public static void LoadLangagePreference()
        {
            try
            {
                string text = System.IO.File.ReadAllText("lang.txt");
                string[] words = text.Split(':');
                string lang = words[1];

                setLangage(lang);
            }
            catch (Exception)
            {
                setLangage("fr");
            }
        }

        public static void SaveLangagePreference()
        {
            string text = "Langage:" + ci.Name;
            System.IO.File.WriteAllText("lang.txt", text);
        }

        public static void setLangage(string lang)
        {
            if (lang == "fr" || lang == "en")
            {
                ci = new CultureInfo(lang);
            }
        }

        public static string getCurrentLangage()
        {
            return ci.Name;
        }

        public static CultureInfo getCultureInfo()
        {
            return ci;
        }
    }
}
