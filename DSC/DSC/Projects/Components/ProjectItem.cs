using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace DSC.Projects.Components
{    
    public abstract class ProjectItem
    {
        [XmlIgnore]
        public ProjectTreeNode ParentNode { get; set; } = null;
        public string Name { get; set; } = "";

        public string BaseFileName { get; set; } = "";

        public ProjectItem() { }
        public ProjectItem(string name, string baseFileName)
        {
            Name = name;
            BaseFileName = baseFileName;
        }

        public abstract void Save(string file);
        public abstract void Load(string file);


    }
}
