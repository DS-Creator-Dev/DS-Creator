using DSC.App.GUI.Controls.Primitives;
using DSC.App.Properties;
using DSC.App.Projects;
using DSC.App.Projects.Components;
using System;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;
using DSC.App.GUI.Forms;
using DSC.App.GUI.Controls.Tabs;
using System.CodeDom;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace DSC.App.GUI.Controls.Pages
{
    public partial class WorkspacePage : Page
    {
        public WorkspacePage()
        {
            InitializeComponent();

            var ProjectsTreeViewImageList = new ImageList();
            ProjectsTreeViewImageList.Images.Add(new Bitmap(32, 32));
            ProjectsTreeViewImageList.Images.Add(Resources.FolderIcon);
            ProjectTreeView.ImageList = ProjectsTreeViewImageList;

            Project project = Session.Project;            

            project.Tree.FolderContextMenu = ProjectTreeViewFolderContextMenu;
            project.Tree.RootContextMenu = ProjectTreeViewRootContextMenu;
            project.Tree.PopulateTreeView(ProjectTreeView, ProjectTreeViewDisplayOption.FolderHierarchy);                     
        }

        public Panel LeftPanel { get => Container.Panel1; }
        public Panel CenterPanel { get => InnerContainer.Panel1; }
        public Panel RightPanel { get => InnerContainer.Panel2; }        

        private bool IsSameOrSubclass(Type potentialDescendant, Type potentialBase)
        {
            return potentialDescendant.IsSubclassOf(potentialBase)
                   || potentialDescendant == potentialBase;
        }

        private ContextMenuStrip GetMenu(object menuItem)
        {
            object target = menuItem;

            // Trace back the context menu item to find its parent menu
            while (target!=null && target.GetType() != typeof(ContextMenuStrip))
            {                
                if(IsSameOrSubclass(target.GetType(), typeof(ToolStripDropDownMenu)))
                {                    
                    target = (target as ToolStripDropDownMenu).OwnerItem;
                }                
                else if(IsSameOrSubclass(target.GetType(), typeof(ToolStripItem)))
                {                    
                    target = (target as ToolStripItem).Owner;
                }
            }            
            return target as ContextMenuStrip;
        }

        private void showInExplorerToolStripMenuItem1_Click(object sender, EventArgs e)
        {                        
            var menu = GetMenu(sender);
            var tree = menu.SourceControl as TreeView;
            var node = tree.SelectedNode.Tag as ProjectTreeNode;
            try
            {
                Process.Start(System.IO.Path.Combine(Session.Project.ProjectPath, node.RelativePath));
            }
            catch { }
        }              

        private void AddTab(TabInfo tab)
        {
            tab.SaveRequiredFlagChanged += TabInfo_SaveRequiredFlagChanged;
            var tabPage = new TabPage(tab.HeaderName + "      ");
            tabPage.Tag = tab.Tag;            
            tab.Dock = DockStyle.Fill;
            tabPage.Controls.Add(tab);
            TabControl.TabPages.Add(tabPage);
            TabControl.SelectedTab = tabPage;
        }

        private bool IsTabOpen(Func<object, bool> pred, out TabPage tab)
        {
            foreach (TabPage ctab in TabControl.Controls)
            {
                if(pred(ctab.Tag))
                {
                    tab = ctab;
                    return true;
                }
            }
            tab = null;
            return false;
        }

        private bool IsTabOpen(ProjectItem item, out TabPage tab)
        {
            return IsTabOpen((object o) =>
            {
                if (o == null || !(o is ProjectItem))
                    return false;
                MessageBox.Show((o as ProjectItem).WorkPath+"\n"+ item.WorkPath);
                return (o as ProjectItem).WorkPath == item.WorkPath;
            }, out tab);
        }

        private bool IsTabOpen(string name, out TabPage tab)
        {
            return IsTabOpen((object o) =>
            {
                if (o == null || !(o is string))
                    return false;
                return (o as string) == name;
            }, out tab);
        }

        private void AddTab(ProjectItem item)
        {      
            if(IsTabOpen(item, out TabPage ctab))
            {
                MessageBox.Show("Tab already open");
                TabControl.SelectedTab = ctab;
                return;
            }           
            TabInfo tab = null;
            if (item is Asset)
            {
                var asset = item as Asset;
                tab = new AssetTab();
                (tab as AssetTab).Asset = asset;
                MessageBox.Show("Tab created");
            }
            if (tab != null)
            {
                tab.Tag = item;                
                AddTab(tab);
            }
            else MessageBox.Show("Error - added tab is null.");
        }

        private void newAssetFromFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var ofd = new OpenFileDialog();
            ofd.Filter = "PNG Files (*.png)|*.png";
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                var filename = ofd.FileName;
                //try
                {
                    var bmp = new Bitmap(filename);
                    var dialog = new AssetDialog(bmp);
                    dialog.AssetName = System.IO.Path.GetFileNameWithoutExtension(filename);
                    if(dialog.ShowDialog() == DialogResult.OK)
                    {
                        Asset result = dialog.Result;
                        Session.Project.Add(result, "Assets");
                        Session.Project.Save();
                        AddTab(result);
                        Session.Project.Tree.PopulateTreeView(ProjectTreeView, ProjectTreeViewDisplayOption.FolderHierarchy);
                    }
                }
                /*catch(Exception ex)
                {
                    throw ex;
                    MessageBox.Show(ex.Message);
                }*/
            }
        }

        private void newToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            var dialog = new AssetDialog();

            dialog.ShowDialog();
        }

        private void ProjectTreeView_NodeMouseDoubleClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            var visual_node = e.Node;
            ProjectTreeNode node = visual_node.Tag as ProjectTreeNode;

            if (node.NodeType == ProjectTreeNodeType.Folder)
                return;

            ProjectItem item = node.Item;

            item.Load(System.IO.Path.Combine(Session.Project.ProjectPath, node.RelativePath));
            MessageBox.Show(item.GetType().Name);

            switch (item.GetType().Name)            
            {
                case "Asset":
                    {                                                
                        AddTab(item);
                        break;
                    }
                default:
                    {
                        break;
                    }
            }

        }

        public void OpenProjectPropertiesTab()
        {            
            if(IsTabOpen("Properties", out TabPage ctab))
            {
                TabControl.SelectedTab = ctab;
                return;
            }
            var tab = new ProjectPropertiesTab();
            tab.HeaderName = "Properties";
            tab.Tag = "Properties";
            tab.ChangesSaved += PropertiesTab_ChangesSave;            
            AddTab(tab);            
        }        

        private void PropertiesTab_ChangesSave(object sender, EventArgs e)
        {            
            Session.Project.Tree.PopulateTreeView(ProjectTreeView, ProjectTreeViewDisplayOption.FolderHierarchy);            
        }

       private void TabInfo_SaveRequiredFlagChanged(object sender, EventArgs e)
       {
            TabControl.Invalidate();
       }
    }
}
