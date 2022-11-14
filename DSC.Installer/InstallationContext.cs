using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DSC.Installer
{
    internal class InstallationContext
    {
        public string InstallationPath { get; }

        public InstallationContext(string installationPath)
        {
            InstallationPath = installationPath;
        }
    }
}
