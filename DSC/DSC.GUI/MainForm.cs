using DSC.GUI.Controls.Pages;
using DSC.GUI.Controls.Primitives;
using System.Windows.Forms;

namespace DSC.GUI
{
    public partial class MainForm : Form, PageHost
    {
        public MainForm()
        {
            InitializeComponent();
            DisplayPage(new TitlePage());
        }

        public void DisplayPage(Page page)
        {
            page.Dock = DockStyle.Fill;
            MainBody.Controls.Clear();
            MainBody.Controls.Add(page);            
        }
    }
}
