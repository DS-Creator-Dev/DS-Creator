using DSC.App.Projects.Components;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.App.GUI.Forms
{
    public partial class AssetDialog : Form
    {
        Bitmap Image = null;
        public AssetDialog(Bitmap resource = null)
        {
            InitializeComponent();
            ErrorsLabel.Text = "";
            if (resource != null)
            {
                Image = resource;
                MarkSizesReadOnly();
                Preview.Width = resource.Width;
                Preview.Height = resource.Height;
                Preview.Image = resource;                
            }            
        }

        private Asset _Result;
        public Asset Result { get => _Result; private set => _Result = value; }

        public string AssetName 
        {
            get => NameBox.Text;
            set => NameBox.Text = value;
        }

        private void MarkSizesReadOnly()
        {
            WidthBox.ReadOnly = true;
            HeightBox.ReadOnly = true;
            ColsCountBox.ReadOnly = true;
            RowsCountBox.ReadOnly = true;
            TileSizeBox.Enabled = false;
        }

        private void Width_ValueChanged(object sender, EventArgs e)
        {
            if (preventEvent) return;
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

            ColsCountBox.Value = (int)(WidthBox.Value / TileWidth);
            RowsCountBox.Value = (int)(HeightBox.Value / TileHeight);
            ValidateMeasures();

            preventEvent = false;


        }

        private void WidthBox_ValueChanged(object sender, EventArgs e)
        {
            if (preventEvent) return;

            preventEvent = true;
            ColsCountBox.Value = (int)(WidthBox.Value / TileWidth);
            ValidateMeasures();
            preventEvent = false;
        }

        private void HeightBox_ValueChanged(object sender, EventArgs e)
        {
            if (preventEvent) return;

            preventEvent = true;
            RowsCountBox.Value = (int)(HeightBox.Value / TileHeight);
            ValidateMeasures();
            preventEvent = false;
        }

        private void ColsCountBox_ValueChanged(object sender, EventArgs e)
        {
            if (preventEvent) return;

            preventEvent = true;
            WidthBox.Value = ColsCountBox.Value * TileWidth;
            ValidateMeasures();
            preventEvent = false;

        }

        private void RowsCountBox_ValueChanged(object sender, EventArgs e)
        {
            if (preventEvent) return;

            preventEvent = true;
            HeightBox.Value = RowsCountBox.Value * TileHeight;
            ValidateMeasures();
            preventEvent = false;
        }
        private void ValidateMeasures()
        {
            ErrorsLabel.Text = "";
            if(RowsCountBox.Value * TileHeight != HeightBox.Value)
            {
                ErrorsLabel.Text += "Height pixels and tiles count do not match.\n";
            }

            if (ColsCountBox.Value * TileWidth != WidthBox.Value) 
            {
                ErrorsLabel.Text += "Width pixels and tiles count do not match.\n";
            }
            if (ColsCountBox.Value == 0 || RowsCountBox.Value == 0 ||
                WidthBox.Value == 0 || HeightBox.Value==0)
            {
                ErrorsLabel.Text += "Zero values are not allowed.\n";
            }

            if (ErrorsLabel.Text.Length == 0) 
            {
                Image = new Bitmap((int)WidthBox.Value, (int)HeightBox.Value);
            }
        }

        private void OkButton_Click(object sender, EventArgs e)
        {
            if(ErrorsLabel.Text.Length>0)
            {
                MessageBox.Show("Please solve the errors before continuing");
                return;
            }

            Result = new Asset(NameBox.Text, NameBox.Text + ".png");
            Result.Image = Image;
            DialogResult = DialogResult.OK;
            Close();
        }

        private void NameBox_TextChanged(object sender, EventArgs e)
        {
            var caret = NameBox.SelectionStart;
            NameBox.Text = Regex.Replace(NameBox.Text, @"\s", "_");
            NameBox.SelectionStart = caret;
        }
    }
}
