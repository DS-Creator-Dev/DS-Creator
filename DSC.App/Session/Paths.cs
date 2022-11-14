using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DSC.App
{
    internal static partial class Session
    {
        /// <summary>
        /// The path containing the running DSC.exe file
        /// </summary>
        public static readonly string ExecutablePath = AppDomain.CurrentDomain.BaseDirectory;

        /// <summary>
        /// Path to store user preferences
        /// </summary>
        public static readonly string AppDataPath =
            Path.Combine(
                Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
                "DSC"
                );

        /// <summary>
        /// The default path to store projects
        /// </summary>
        public static string DefaultProjectPath = Path.Combine(AppDataPath, "Projects");
    }
}
