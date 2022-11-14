using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.App.GUI.Controls.Primitives
{
    public partial class Page : UserControl
    {         
        public Page()
        {
            InitializeComponent();            
        }        

        public void NavigateTo(Page otherPage)
        {
            (ParentForm as PageHost).DisplayPage(otherPage);
        }
    }   
}
