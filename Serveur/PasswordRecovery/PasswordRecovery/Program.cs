using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Mail;
using System.Text;
using System.Threading.Tasks;

namespace PasswordRecovery
{
    class Program
    {
        static void Main(string[] args)
        {
            SmtpClient SmtpServer = new SmtpClient("smtp.gmail.com");
            var mail = new MailMessage();
            string password = args[0];
            string destinationEmail = args[1];
            mail.From = new MailAddress("ballersdevteam@hotmail.com");
            mail.To.Add(destinationEmail);
            mail.Subject = "Password recovery PAINBALL";
            mail.IsBodyHtml = true;
            string htmlBody;
            htmlBody = "Voici votre mot de passe : " + password + "\n Vous pouvez le changer dans le jeu!\n";
            mail.Body = htmlBody;
            SmtpServer.Port = 587;
            SmtpServer.UseDefaultCredentials = false;
            SmtpServer.Credentials = new System.Net.NetworkCredential("ballersdevteam@gmail.com", "dankmemes69");
            SmtpServer.EnableSsl = true;
            try
            {
                SmtpServer.Send(mail);
            }
            catch (Exception e)
            {
                Console.WriteLine("ERROR : " + e.StackTrace);
            }
        }
    }
}
