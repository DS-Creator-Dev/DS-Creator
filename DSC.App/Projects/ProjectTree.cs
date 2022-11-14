using DSC.App.Projects.Components;
using System;
using System.CodeDom;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace DSC.App.Projects
{
    [XmlRoot("Tree")]
    public class ProjectTree
    {
        /// <summary>
        /// Project Tree Root
        /// </summary>                
        public ProjectTreeNode Root { get; set; } = new ProjectTreeNode("Root", ProjectTreeNodeType.Folder);

        /// <summary>
        /// Creates folder at path
        /// </summary>
        /// <param name="path">Relative path to project (e.g. "assets/characters")</param>
        /// <returns>Node instance of the last dir in path</returns>
        public ProjectTreeNode Add(string path)
        {
            var dirs = path.Split('/').Where(item => item != "");
            var node = Root;
            foreach(var dir in dirs)
            {
                var target = node.Children.Find(n => n.Name == dir);
                if(target==null)
                {
                    target = new ProjectTreeNode(dir, ProjectTreeNodeType.Folder);
                    node.Add(target);
                }
                node = target;
            }
            return node;
        }

        public void PopulateTreeView(TreeView treeView, ProjectTreeViewDisplayOption option)
        {
            treeView.Nodes.Clear();
            var treeRoot = new TreeNode(Root.Name);
            treeRoot.Tag = Root;
            treeRoot.ContextMenuStrip = RootContextMenu;

            if (option == ProjectTreeViewDisplayOption.FolderHierarchy)
            {
                Root.PopulateTreeNode(treeRoot, delegate (ProjectTreeNode n, TreeNode t)
                {
                    if (n.NodeType == ProjectTreeNodeType.Folder)
                    {
                        t.ContextMenuStrip = FolderContextMenu;
                    }
                });
            }
            else if (option == ProjectTreeViewDisplayOption.Categorized)
            {
                throw new NotImplementedException();
            }
            treeView.Nodes.Add(treeRoot);
        }

        [XmlIgnore]
        public ContextMenuStrip FolderContextMenu { get; set; } = null;

        [XmlIgnore]
        public ContextMenuStrip RootContextMenu { get; set; } = null;
    }

    public enum ProjectTreeNodeType
    {
        Folder, File
    } 

    public enum ProjectTreeViewDisplayOption
    {
        FolderHierarchy,
        Categorized
    }

    [XmlRoot("Node")]
    public class ProjectTreeNode
    {
        public ProjectTreeNode() { }
        public ProjectTreeNode(string name, ProjectTreeNodeType nodeType)
        {
            Name = name;
            NodeType = nodeType;                             
        }

        [XmlIgnore]
        public ProjectTreeNode Parent { get; private set; } = null;

        public string Name { get; set; } = "";

        [XmlAttribute("type")]
        public ProjectTreeNodeType NodeType { get; set; }

        [XmlArray("Children"), XmlArrayItem("Node")]
        public List<ProjectTreeNode> Children { get; set; } = new List<ProjectTreeNode>();

        [XmlElement("Item")]
        public ProjectItem Item { get; set; } = null;

        public ProjectTreeNode Add(ProjectTreeNode node)
        {
            if (NodeType == ProjectTreeNodeType.File) 
                throw new ProjectTreeAddToLeafException();
            Children.Add(node);
            node.Parent = this;
            return node;
        }

        public ProjectTreeNode Add(ProjectItem item)
        {
            if (NodeType == ProjectTreeNodeType.File)
                throw new ProjectTreeAddToLeafException();
            var node = new ProjectTreeNode(item.Name, ProjectTreeNodeType.File);            
            node.Item = item;
            return Add(node);
        }

        public IEnumerable<ProjectItem> GetItems(Func<ProjectItem, bool> pred)
        {
            foreach(ProjectTreeNode child in Children)
            {
                if (child.Item != null && pred(child.Item)) 
                {
                    yield return child.Item;
                }
                foreach (var item in child.GetItems(pred)) 
                {
                    yield return item;
                }
            }
            yield break;
        }

        public IEnumerable<ProjectTreeNode> GetLeaves()
        {
            foreach (ProjectTreeNode child in Children)
            {
                if (child.Item != null)
                {
                    yield return child;
                }
                foreach (var item in child.GetLeaves())
                {
                    yield return item;
                }
            }
            yield break;
        }

        public string RelativePath
        {
            get
            {
                string result = "";
                var node = this;
                if(node.Item!=null)
                {
                    result = node.Item.BaseFileName;
                    node = node.Parent;
                }
                while (node.Parent != null) 
                {
                    if (result == "")
                        result = node.Name;
                    else
                        result = node.Name + "/" + result;
                    node = node.Parent;
                }                
                return result;
            }
        }

        internal void PopulateTreeNode(TreeNode treeNode, Action<ProjectTreeNode, TreeNode> NodeCreatedCallback = null)
        {
            if (NodeType == ProjectTreeNodeType.Folder) 
            {                
                treeNode.ImageIndex = 1;
                treeNode.SelectedImageIndex = 1;
                foreach (var node in Children)
                {
                    var tNode = new TreeNode(node.Name);
                    tNode.Tag = node;
                                        

                    NodeCreatedCallback?.Invoke(node, tNode);
                    node.PopulateTreeNode(tNode, NodeCreatedCallback);
                    treeNode.Nodes.Add(tNode);
                }
            }
        }

        private void SanityCheck()
        {
            if (Children.Count > 0 && NodeType != ProjectTreeNodeType.Folder) 
            {
                throw new Exception("Non-folder item has children");
            }
        }

        internal void DeserializeCheck()
        {
            SanityCheck();            
            // infere data that was lost during serialization
            if (NodeType == ProjectTreeNodeType.Folder)
            {
                foreach (var child in Children)
                {
                    child.Parent = this;
                    child.DeserializeCheck();
                }
            }
        }

    }

    class ProjectTreeAddToLeafException : Exception { }
}
