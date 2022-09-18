using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.GUI.Forms
{
    public partial class AssetDialog : Form
    {
        public AssetDialog()
        {
            InitializeComponent();
        }

        private void Width_ValueChanged(object sender, EventArgs e)
        {
            if (preventEvent) return;
        }

        private void measureUpDown1_ValueChanged(object sender, EventArgs e)
        {

        }

        int TileWidth = 8;
        int TileHeight = 8;

        bool preventEvent = false;

        private void TileSizeBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            var sel = TileSizeBox.SelectedItem as string;            
            var size = sel.Split('x').Select(a => int.Parse(a)).ToArray();
            var width = size[0];
            var height = size[1];
            TileWidth = width;
            TileHeight = height;

            preventEvent = true;

            ColsCountBox.Value = WidthBox.Value / TileWidth;
            RowsCountBox.Value = HeightBox.Value / TileHeight;

            preventEvent = false;


        }

        private void WidthBox_ValueChanged(object sender, EventArgs e)
        {
            if (preventEvent) return;

            preventEvent = true;
            ColsCountBox.Value = WidthBox.Value / TileWidth;
            preventEvent = false;
        }

        private void HeightBox_ValueChanged(object sender, EventArgs e)
        {
            if (preventEvent) return;

            preventEvent = true;
            RowsCountBox.Value = HeightBox.Value / TileHeight;
            preventEvent = false;
        }

        private void ColsCountBox_ValueChanged(object sender, EventArgs e)
        {
            if (preventEvent) return;

            preventEvent = true;
            WidthBox.Value = ColsCountBox.Value * TileWidth;            
            preventEvent = false;

        }

        private void RowsCountBox_ValueChanged(object sender, EventArgs e)
        {
            if (preventEvent) return;

            preventEvent = true;
            HeightBox.Value = RowsCountBox.Value * TileHeight;
            preventEvent = false;
        }
    }
}
