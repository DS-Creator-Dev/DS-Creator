using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DSC.Installer
{
    internal abstract class InstallationStep
    {
        public abstract string Message { get; }
        public abstract void Execute(InstallationContext context);
    }
}
