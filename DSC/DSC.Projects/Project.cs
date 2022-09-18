using DSC.Projects.Components;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DSC.Projects
{
    public class Project
    {
        public string Name { get; set; }

        public String Path { get; set; }

        ProjectTree Tree { get; } = new ProjectTree();        

        void Add(Asset asset, string path)
        {            

        }
    }
}
