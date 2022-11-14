using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DSC.Installer
{
    internal class InstallationSetEnvVars : InstallationStep
    {
        public override string Message => "Setting environment variables...";

        public override void Execute(InstallationContext context)
        {
            Environment.SetEnvironmentVariable("DSC", 
                context.InstallationPath, 
                EnvironmentVariableTarget.User);
            Environment.SetEnvironmentVariable("DSCENGINE",
                Path.Combine(context.InstallationPath, "DSCEngine"),
                EnvironmentVariableTarget.User);
            Environment.SetEnvironmentVariable("DSCTOOLS",
                Path.Combine(context.InstallationPath, "tools"),
                EnvironmentVariableTarget.User);
        }
    }
}
