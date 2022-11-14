using DSC.App.Utils;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.App
{
    internal static partial class Session
    {
        static Session()
        {
            Directory.CreateDirectory(DefaultProjectPath);
            
            // init Config
            Config.GetType().GetField("IniFile", BindingFlags.NonPublic | BindingFlags.Instance)
                .SetValue(Config, new IniFile(Path.Combine(Session.AppDataPath, "config.ini")));

            StartupChecks();
        }

        public static  void StartupChecks()
        {            
        }
    }    
}
