using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace DSC.App.Projects.Components
{    
    [XmlRoot("Item")]
    [XmlInclude(typeof(Asset))]
    public abstract class ProjectItem
    {
        [XmlIgnore]
        public ProjectTreeNode ParentNode { get; set; } = null;

        [XmlAttribute("name")]
        public string Name { get; set; } = "";

        [XmlAttribute("basefilename")]
        public string BaseFileName { get; set; } = "";

        [XmlIgnore]
        public string WorkPath { get; set; } = "";

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
