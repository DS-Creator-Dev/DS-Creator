using DSC.GUI.Controls.Primitives;
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

namespace DSC.GUI.Controls.Pages
{
    public partial class NewProjectPage : Page
    {
        public NewProjectPage()
        {
            InitializeComponent();
        }

        private void ProjectPathSeletor_PathChanged(object sender, EventArgs args)
        {
            MessageBox.Show(ProjectPathSeletor.Path);
        }

        private void BackButton_Click(object sender, EventArgs e)
        {
            NavigateTo(new TitlePage());
        }

        bool disableTextChanged = false;
        private void ProjectNameBox_TextChanged(object sender, EventArgs e)
        {
            if (disableTextChanged)
                return;
            disableTextChanged = true;
            var caret = ProjectNameBox.SelectionStart;
            ProjectNameBox.Text = Regex.Replace(ProjectNameBox.Text, @"\s", "_");
            ProjectNameBox.SelectionStart = caret;
            disableTextChanged = false;
        }

        private void OkButton_Click(object sender, EventArgs e)
        {
            NavigateTo(new WorkspacePage());
        }
    }
}
