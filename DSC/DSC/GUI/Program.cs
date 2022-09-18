using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.GUI
{
    internal static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To see the Console logs, Set Project->Properties->Output type to
            // Console Application.
            Console.WriteLine(Session.ExecutablePath);
            Console.WriteLine(Session.AppDataPath);
            Console.WriteLine(Session.DefaultProjectPath);

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }
}
