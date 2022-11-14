using DSC.App.Utils;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DSC.App
{
    internal class ConfigFile
    {
        private ConfigFile() { }
        private static ConfigFile _ConfigFile = new ConfigFile();
        public static ConfigFile Instance { get => _ConfigFile; }

        /// <summary>
        /// config.ini file containing user data (devkitARM paths etc)
        /// This member is initialized in Session.init() uing reflection.
        /// </summary>
        private IniFile IniFile;
        
        /// <summary>
        /// Index access wrapper around the IniFile.
        /// </summary>
        /// <param name="key">property name</param>
        /// <returns>property value</returns>
        public string this[string key]
        {
            get => IniFile.Read(key);
            set => IniFile.Write(key, value);
        }
    }

    internal static partial class Session
    {
        /// <summary>
        /// User configuration file
        /// </summary>
        public static ConfigFile Config = ConfigFile.Instance;
    }
}
