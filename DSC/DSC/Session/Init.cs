using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DSC
{
    internal static partial class Session
    {
        static Session()
        {
            Directory.CreateDirectory(DefaultProjectPath);
        }
    }    
}
