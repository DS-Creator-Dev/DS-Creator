using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.GUI.Controls.Tabs
{
    public partial class AssetTab : UserControl
    {
        public AssetTab()
        {
            InitializeComponent();            
        }

        int AssetWidth = 128;
        int AssetHeight = 128;

        private int _Zoom = 1;
        private int Zoom
        {
            get => _Zoom;
            set
            {
                _Zoom = value;
                GridPanel.SetBounds(0, 0, AssetWidth * _Zoom, AssetHeight * _Zoom);                
                ImagePanel.SetBounds(0, 0, AssetWidth * _Zoom, AssetHeight * _Zoom);                
            }
        }

        private void GridPanel_Paint(object sender, PaintEventArgs e)
        {            
            for(int y=0;y< GridPanel.Height;y+=8*Zoom)
            {
                e.Graphics.DrawLine(Pens.LightGray, 0, y, GridPanel.Width, y);
            }

            for (int x = 0; x < GridPanel.Width; x += 8 * Zoom)
            {
                e.Graphics.DrawLine(Pens.LightGray, x, 0, x, GridPanel.Height);
            }
        }        

        private void ZoomInBtn_Click(object sender, EventArgs e)
        {
            if(Zoom<8)
                Zoom++;
        }

        private void ZoomOutBtn_Click(object sender, EventArgs e)
        {
            if (Zoom > 1)
                Zoom--;
        }

        private void ImagePanel_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawLine(Pens.Red, 0, 0, ImagePanel.Width, ImagePanel.Height);
            e.Graphics.DrawLine(Pens.Red, 0, ImagePanel.Height, ImagePanel.Width, 0);
        }
    }
}
