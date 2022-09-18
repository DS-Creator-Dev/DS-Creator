﻿using DSC.Projects.Components;
using System;
using System.CodeDom;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.Projects
{
    public class ProjectTree
    {
        /// <summary>
        /// Project Tree Root
        /// </summary>
        public ProjectTreeNode Root { get; } = new ProjectTreeNode("Root", ProjectTreeNodeType.Folder);

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
            treeRoot.ContextMenuStrip = FolderContextMenu;

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

        public ContextMenuStrip FolderContextMenu { get; set; } = null;
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

    public class ProjectTreeNode
    {
        public ProjectTreeNode(string name, ProjectTreeNodeType nodeType)
        {
            Name = name;
            NodeType = nodeType;            
            if (nodeType == ProjectTreeNodeType.Folder)
            {
                Children = new List<ProjectTreeNode>();
            }            
        }

        public ProjectTreeNode Parent { get; private set; } = null;
        public string Name { get; set; }
        public ProjectTreeNodeType NodeType { get; }
        public List<ProjectTreeNode> Children { get; } = null;

        ProjectItem Item { get; set; } = null;

        public void Add(ProjectTreeNode node)
        {
            if (Children == null)
                throw new ProjectTreeAddToLeafException();
            Children.Add(node);
            node.Parent = this;
        }

        public void Add(ProjectItem item)
        {
            if (Children == null)
                throw new ProjectTreeAddToLeafException();
            var node = new ProjectTreeNode(item.Name, ProjectTreeNodeType.File);            
            Add(node);
        }

        public string RelativePath
        {
            get
            {
                string result = "";
                var node = this;
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
            if (Children != null)
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

    }

    class ProjectTreeAddToLeafException : Exception { }
}
