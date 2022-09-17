using DSC.GUI.Controls.Primitives;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.GUI.Controls.Pages
{
    public partial class WorkspacePage : Page
    {
        public WorkspacePage()
        {
            InitializeComponent();            
        }

        public Panel LeftPanel { get => Container.Panel1; }
        public Panel CenterPanel { get => InnerContainer.Panel1; }
        public Panel RightPanel { get => InnerContainer.Panel2; }
    }
}
