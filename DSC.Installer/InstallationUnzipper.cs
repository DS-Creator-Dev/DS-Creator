using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace DSC.Installer
{
    internal class InstallationUnzipper : InstallationStep
    {
        private string ResourceName;
        private byte[] Archive;
        public InstallationUnzipper(string res_name)
        {
            ResourceName = res_name;            
            Archive = typeof(Properties.Resources)
                .GetProperty(res_name + "Zip", BindingFlags.NonPublic | BindingFlags.Static)
                .GetValue(null) as byte[];
        }

        public override string Message { get => $"Installing {ResourceName}"; }

        public override void Execute(InstallationContext context)
        {            
            using (ZipArchive archive = new ZipArchive(new MemoryStream(Archive))) 
            {
                foreach (ZipArchiveEntry entry in archive.Entries)
                {
                    if(!entry.FullName.EndsWith("/")) // is file
                    {
                        var path = Path.Combine(context.InstallationPath, entry.FullName);
                        Directory.CreateDirectory(Path.GetDirectoryName(path));
                        entry.ExtractToFile(path);
                    }                    
                }
            }
        }
    }
}
