﻿using System;
using System.CodeDom;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.GUI.Controls.Primitives
{
    public partial class PathSelector : UserControl
    {
        public PathSelector()
        {
            InitializeComponent();
        }

        protected override void SetBoundsCore(
               int x, int y, int width, int height, BoundsSpecified specified)
        {
            // EDIT: ADD AN EXTRA HEIGHT VALIDATION TO AVOID INITIALIZATION PROBLEMS
            // BITWISE 'AND' OPERATION: IF ZERO THEN HEIGHT IS NOT INVOLVED IN THIS OPERATION
            if ((specified & BoundsSpecified.Height) == 0 || height == DisplayBox.Height)
            {
                base.SetBoundsCore(x, y, width, DisplayBox.Height, specified);
                Button.Width = 2*DisplayBox.Height;
            }
            else
            {
                return; // RETURN WITHOUT DOING ANY RESIZING
            }
        }

        public bool SelectsFolder { get; set; } = false;

        public string Path
        {
            get => DisplayBox.Text;
            set
            {
                DisplayBox.Text = value;
                PathChanged?.Invoke(this, new EventArgs());
            }
        }

        public delegate void OnPathChanged(object sender, EventArgs args);
        public event OnPathChanged PathChanged;

        private void Button_Click(object sender, EventArgs e)
        {           
            if(SelectsFolder)
            {
                var dialog = new FolderPicker();
                dialog.InputPath = DisplayBox.Text;
                if(dialog.ShowDialog() == true)
                {
                    Path = dialog.ResultPath;
                }
            }
            else
            {
                throw new NotImplementedException("File selector wip");
            }
        }
    }
}
