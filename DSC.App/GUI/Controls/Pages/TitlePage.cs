using DSC.App.GUI.Controls.Primitives;
using DSC.App.Projects;
using DSC.Commons.GUI.Controls;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.App.GUI.Controls.Pages
{
    public partial class TitlePage : Page
    {
        public TitlePage()
        {
            InitializeComponent();            
        }

        private void NewProjButton_Click(object sender, EventArgs e)
        {
            NavigateTo(new NewProjectPage());            
        }

        private void LoadProjButton_Click(object sender, EventArgs e)
        {                        
            var dialog = new FolderPicker();
            dialog.InputPath = Session.DefaultProjectPath;
            if(dialog.ShowDialog()==true)
            {               
                var path = dialog.ResultPath;
                
                try
                {
                    Session.Project = Project.Load(path);
                    NavigateTo(new WorkspacePage());
                }
                catch(ProjectFileNotFoundException)
                {
                    MessageBox.Show("The chosen path is not a DSC project directory.");
                }
                catch (Exception ex)
                {
                    throw ex; // Debug
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void DocsButton_Click(object sender, EventArgs e)
        {
            // Open in browser:
            Process.Start("explorer", "https://bowersindustry.github.io/ds-creator-docs/");
        }

        private void DiscordButton_Click(object sender, EventArgs e)
        {
            // Open in browser:
            Process.Start("explorer", "https://discord.com/invite/CqrXmqxAf8");            
        }
    }
}
