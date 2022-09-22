using DSC.GUI.Controls.Primitives;
using DSC.Properties;
using DSC.Projects;
using DSC.Projects.Components;
using System;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;
using DSC.GUI.Forms;
using DSC.GUI.Controls.Tabs;
using System.CodeDom;

namespace DSC.GUI.Controls.Pages
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
            var tabPage = new TabPage(tab.HeaderName + "      ");
            tab.Dock = DockStyle.Fill;
            tabPage.Controls.Add(tab);
            TabControl.TabPages.Add(tabPage);
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
                        var tab = new AssetTab();
                        tab.Asset = result;
                        Session.Project.Add(result, "Assets");
                        Session.Project.Save();
                        AddTab(tab);                        
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

            switch (item.GetType().Name)            
            {
                case "Asset":
                    {                        
                        var tab = new AssetTab();
                        tab.Asset = item as Asset;                        
                        AddTab(tab);
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
            var tab = new ProjectPropertiesTab();
            tab.HeaderName = "Properties";
            AddTab(tab);
        }
    }
}
