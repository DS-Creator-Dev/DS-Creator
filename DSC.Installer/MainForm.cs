using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.Installer
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        List<InstallationStep> Steps = new List<InstallationStep>()
        {

            new InstallationUnzipper("DSCEngine"),
            new InstallationUnzipper("Tools"),
            new InstallationSetEnvVars()
        };


        private void InstallButton_Click(object sender, EventArgs e)
        {
            InstallationContext context = new InstallationContext(InstallPathSelector.Path);

            Directory.CreateDirectory(context.InstallationPath);

            Task.Run(() =>
            {
                try
                {
                    foreach (var step in Steps)
                    {
                        Print(step.Message);

                        step.Execute(context);
                    }
                    Print("Done.");
                }                
                catch(Exception ex)
                {
                    MessageBox.Show(ex.Message, "Something went wrong");
                }
            });
        }

        private void Print(string message)
        {
            BeginInvoke(new Action(() =>
            {
                ReportBox.Text += message + Environment.NewLine;
            }));
        }
    }
}
