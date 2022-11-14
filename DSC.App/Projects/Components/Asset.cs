using System;
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace DSC.App.Projects.Components
{
    [XmlRoot("Asset")]
    public class Asset : ProjectItem
    {
        [XmlIgnore]
        public Bitmap Image { get; set; }

        [XmlElement("TransparentColor")]
        public string _XML_TransparentColor
        {
            get
            {
                return TransparentColor.ToArgb().ToString("X08");
            }
            set
            {
                TransparentColor = Color.FromArgb(
                    int.TryParse(value, NumberStyles.HexNumber, null, out int res) ? res : 0
                );
            }
        }

        [XmlIgnore]
        public Color TransparentColor { get; set; } = Color.Transparent;

        [XmlAttribute("role")]
        public string Role { get; set; } = "Asset";

        public Asset() { }
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
