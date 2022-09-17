using DSC.GUI.Controls.Pages;
using DSC.GUI.Controls.Primitives;
using System.Windows.Forms;

namespace DSC.GUI
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
            DisplayPage(new TitlePage());
        }

        void DisplayPage(Page page)
        {
            page.Dock = DockStyle.Fill;
            MainBody.Controls.Clear();
            MainBody.Controls.Add(page);
        }
    }
}
