using DSC.App.GUI.Controls.Primitives;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.App.GUI.Controls.Tabs
{
    public partial class ProjectPropertiesTab : TabInfo
    {
        public ProjectPropertiesTab()
        {
            InitializeComponent();

            ProjNameBox.Text = Session.Project.Name;

            IsLoaded = true;
        }

        bool IsLoaded = false;

        private void TabControl_DrawItem(object sender, DrawItemEventArgs e)
        {
            var g = e.Graphics;
            var text = this.TabControl.TabPages[e.Index].Text;
            var sizeText = g.MeasureString(text, this.TabControl.Font);

            var x = e.Bounds.Left + 3;
            var y = e.Bounds.Top + (e.Bounds.Height - sizeText.Height) / 2;

            g.DrawString(text, this.TabControl.Font, Brushes.Black, x, y);

        }

        private void ProjNameBox_TextChanged(object sender, EventArgs e)
        {
            if (!IsLoaded)
                return;
            Session.Project.Name = ProjNameBox.Text;
            RequiresSave = true;
        }

        public override bool SaveDataProc()         
        {
            Session.Project.Save();
            return true; 
        }

    }
}
