using DSC.App.GUI.Controls.Pages;
using DSC.App.GUI.Controls.Primitives;
using DSC.App.Projects;
using System.Windows.Forms;

namespace DSC.App.GUI
{
    public partial class MainForm : Form, PageHost
    {        
        public MainForm(string proj_path = null)
        {
            // set proj_path to open directly into WorkspacePage
            InitializeComponent();
            if (proj_path != null) 
            {
                Session.Project = Project.Load(proj_path);
            }
            if (Session.Project == null)
            {
                DisplayPage(new TitlePage());
            }
            else
            {
                DisplayPage(new WorkspacePage());
            }
        }

        public void DisplayPage(Page page)
        {
            page.Dock = DockStyle.Fill;
            MainBody.Controls.Clear();
            MainBody.Controls.Add(page);            
        }

        private void exitToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            Close();
        }

        private void closeProjectToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            DisplayPage(new TitlePage());
        }

        private void propertiesToolStripMenuItem_Click(object sender, System.EventArgs e)
        {
            if(MainBody.Controls.Count>0)
            {
                var page = MainBody.Controls[0];
                if(page.GetType()==typeof(WorkspacePage))
                {
                    (page as WorkspacePage).OpenProjectPropertiesTab();
                }
            }

        }
    }
}
