using DSC.App.GUI.Controls.Tabs;
using DSC.App.Properties;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.App.GUI.Controls.Primitives
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

                string title = tabPage.Text;
                var tabinfo = GetTabInfo(tabPage);
                if(tabinfo!=null && tabinfo.RequiresSave)
                {
                    title = "*" + title;
                }
                TextRenderer.DrawText(e.Graphics, title, tabPage.Font, tabRect, tabPage.ForeColor, TextFormatFlags.Left);
            }
            catch (Exception ex) { throw new Exception(ex.Message); }
        }

        private TabInfo GetTabInfo(TabPage tab)
        {
            if(tab.Controls.Count > 0 && (tab.Controls[0] is TabInfo))
            {
                return tab.Controls[0] as TabInfo;
            }
            return null;
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            base.OnMouseDown(e);
            Rectangle r = this.GetTabRect(this.SelectedIndex);
            Rectangle closeButton = new Rectangle(r.Right - 15, r.Top + 4, 9, 7);
            if (closeButton.Contains(e.Location))
            {
                var tabinfo = GetTabInfo(SelectedTab);
                if (tabinfo != null && tabinfo.RequiresSave)
                {
                    var result = MessageBox.Show("There are unsaved changes. Save before closing the tab?",
                        "Save?", MessageBoxButtons.YesNoCancel);
                    if(result==DialogResult.Cancel)
                    {
                        return;
                    }
                    else if(result == DialogResult.Yes)
                    {
                        tabinfo.SaveData();                        
                    }                     
                }
                this.TabPages.Remove(this.SelectedTab);
            }
        }
    }
}
