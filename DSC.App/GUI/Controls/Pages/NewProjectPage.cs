using DSC.App.GUI.Controls.Primitives;
using DSC.App.Projects;
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

namespace DSC.App.GUI.Controls.Pages
{
    public partial class NewProjectPage : Page
    {
        public NewProjectPage()
        {
            InitializeComponent();
            ProjectPathSeletor.Path = Session.DefaultProjectPath;
        }

        private void ProjectPathSeletor_PathChanged(object sender, EventArgs args)
        {
            
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
            var name = ProjectNameBox.Text;
            var path = ProjectPathSeletor.Path;

            // TO DO: Validate name & path...

            try
            {
                Session.Project = new Project(name, path);
                Session.Project.Save();
                NavigateTo(new WorkspacePage());
            }
            catch(Exception ex)
            {
                throw ex; // Debug
                MessageBox.Show(ex.Message);
            }            
        }
    }
}
