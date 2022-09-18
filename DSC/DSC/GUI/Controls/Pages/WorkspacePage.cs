using DSC.GUI.Controls.Primitives;
using DSC.Properties;
using DSC.Projects;
using DSC.Projects.Components;
using System;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;

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
            Process.Start(System.IO.Path.Combine(Session.Project.ProjectPath, node.RelativePath));                        
        }       

        private void newActorToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            var menu = GetMenu(sender);
            var tree = menu.SourceControl as TreeView;
            var node = tree.SelectedNode.Tag as ProjectTreeNode;

        }
    }
}
