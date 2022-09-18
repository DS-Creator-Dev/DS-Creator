using DSC.GUI.Controls.Primitives;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.GUI.Controls.Pages
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
