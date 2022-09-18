using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace DSC.Projects.Components
{
    [XmlRoot("Asset")]
    public class Asset : ProjectItem
    {
        [XmlIgnore]
        public Bitmap Image { get; set; }

        public Asset(string name, string baseFileName) : base(name, baseFileName)
        { }

        public Asset(string name, string baseFileName, int width, int height)
            : this(name, baseFileName)
        {
            Image = new Bitmap(width, height);
        }

        public override void Save(string file)
        {
            Image.Save(file);
        }
        public override void Load(string file)
        {
            Image = new Bitmap(file);
        }        
    }
}
