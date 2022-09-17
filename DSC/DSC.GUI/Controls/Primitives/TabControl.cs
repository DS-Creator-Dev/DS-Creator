using DSC.GUI.Properties;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.GUI.Controls.Primitives
{
    public class TabControl : System.Windows.Forms.TabControl
    {
        public TabControl()
        {
            DrawMode = TabDrawMode.OwnerDrawFixed;
            SizeMode = TabSizeMode.Fixed;            

        }
        protected override void OnDrawItem(DrawItemEventArgs e)
        {            
            base.OnDrawItem(e);            
            try
            {                
                var tabPage = this.TabPages[e.Index];
                var tabRect = this.GetTabRect(e.Index);
                e.Graphics.FillRectangle(
                    SelectedIndex == e.Index ? Brushes.White : Brushes.WhiteSmoke, 
                    tabRect);
                tabRect.Inflate(-2, -2);
                var closeImage = Resources.TabCloseButton;
                e.Graphics.DrawImage(closeImage, (tabRect.Right - closeImage.Width), tabRect.Top + (tabRect.Height - closeImage.Height) / 2);
                TextRenderer.DrawText(e.Graphics, tabPage.Text, tabPage.Font, tabRect, tabPage.ForeColor, TextFormatFlags.Left);
            }
            catch (Exception ex) { throw new Exception(ex.Message); }
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);
            Rectangle r = this.GetTabRect(this.SelectedIndex);
            Rectangle closeButton = new Rectangle(r.Right - 15, r.Top + 4, 9, 7);
            if (closeButton.Contains(e.Location))
            {
                this.TabPages.Remove(this.SelectedTab);
            }
        }
    }
}
