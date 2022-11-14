using DSC.App.Projects.Components;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.App.GUI.Controls.Tabs
{
    public partial class AssetTab : TabInfo
    {
        public AssetTab()
        {
            InitializeComponent();            

            typeof(Panel).InvokeMember("DoubleBuffered", BindingFlags.SetProperty
            | BindingFlags.Instance | BindingFlags.NonPublic, null,
            ImagePanel, new object[] { true });

            /*GridPanel.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            GridPanel.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            UpdateStyles();*/
        }

        public int AssetWidth { get; set; } = 128;
        public int AssetHeight { get; set; } = 128;

        private Asset _Asset;
        public Asset Asset
        {
            get => _Asset;
            set
            {
                _Asset = value;
                if (Asset != null)
                {
                    HeaderName = Asset.BaseFileName;

                    TransparentColorButton.BackColor = ColorPicker.Color = Asset.TransparentColor;

                    SetImage(Asset.Image);
                    Zoom = Zoom; // force redraw
                }
            }
        }

        public void SetImage(Bitmap bmp)
        {
            AssetWidth = bmp.Width;
            AssetHeight = bmp.Height;
            ImagePanel.BackgroundImage = bmp;
        }

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
            // prevent anti alias while zooming in
            e.Graphics.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
            e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighSpeed;
            e.Graphics.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.HighSpeed;

            // to be changed (aesthetically)

            var pen = new Pen(new SolidBrush(Color.FromArgb(128, Color.LightGray)));

            for(int y=0;y< GridPanel.Height;y+=8*Zoom)
            {
                e.Graphics.DrawLine(pen, 0, y, GridPanel.Width, y);
            }

            for (int x = 0; x < GridPanel.Width; x += 8 * Zoom)
            {
                e.Graphics.DrawLine(pen, x, 0, x, GridPanel.Height);
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
        }

        private void TransparentColorButton_Click(object sender, EventArgs e)
        {
            if (ColorPicker.ShowDialog() == DialogResult.OK)
            {
                TransparentColorButton.BackColor = ColorPicker.Color;
                Asset.TransparentColor = ColorPicker.Color;
                Session.Project.Save(); // TO OPTIMIZE
            }
        }
    }
}
