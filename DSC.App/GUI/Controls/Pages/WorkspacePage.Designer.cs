namespace DSC.App.GUI.Controls.Pages
{
    partial class WorkspacePage
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.Container = new System.Windows.Forms.SplitContainer();
            this.ProjectTreeView = new System.Windows.Forms.TreeView();
            this.InnerContainer = new System.Windows.Forms.SplitContainer();
            this.TabControl = new DSC.App.GUI.Controls.Primitives.TabControl();
            this.ToolbarsPanel = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.showInExplorerToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newActorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newAssetToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newSceneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ProjectTreeViewFolderContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.showInExplorerToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.ProjectTreeViewRootContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripMenuItem();
            this.assetToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.fromFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.showInExplorerToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.Container)).BeginInit();
            this.Container.Panel1.SuspendLayout();
            this.Container.Panel2.SuspendLayout();
            this.Container.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.InnerContainer)).BeginInit();
            this.InnerContainer.Panel1.SuspendLayout();
            this.InnerContainer.SuspendLayout();
            this.ToolbarsPanel.SuspendLayout();
            this.ProjectTreeViewFolderContextMenu.SuspendLayout();
            this.ProjectTreeViewRootContextMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // Container
            // 
            this.Container.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Container.Location = new System.Drawing.Point(0, 34);
            this.Container.Name = "Container";
            // 
            // Container.Panel1
            // 
            this.Container.Panel1.BackColor = System.Drawing.Color.WhiteSmoke;
            this.Container.Panel1.Controls.Add(this.ProjectTreeView);
            // 
            // Container.Panel2
            // 
            this.Container.Panel2.Controls.Add(this.InnerContainer);
            this.Container.Size = new System.Drawing.Size(808, 306);
            this.Container.SplitterDistance = 181;
            this.Container.TabIndex = 0;
            // 
            // ProjectTreeView
            // 
            this.ProjectTreeView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ProjectTreeView.Location = new System.Drawing.Point(3, 3);
            this.ProjectTreeView.Name = "ProjectTreeView";
            this.ProjectTreeView.Size = new System.Drawing.Size(175, 206);
            this.ProjectTreeView.TabIndex = 0;
            this.ProjectTreeView.NodeMouseDoubleClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.ProjectTreeView_NodeMouseDoubleClick);
            // 
            // InnerContainer
            // 
            this.InnerContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.InnerContainer.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.InnerContainer.Location = new System.Drawing.Point(0, 0);
            this.InnerContainer.Name = "InnerContainer";
            // 
            // InnerContainer.Panel1
            // 
            this.InnerContainer.Panel1.BackColor = System.Drawing.Color.WhiteSmoke;
            this.InnerContainer.Panel1.Controls.Add(this.TabControl);
            // 
            // InnerContainer.Panel2
            // 
            this.InnerContainer.Panel2.BackColor = System.Drawing.Color.WhiteSmoke;
            this.InnerContainer.Size = new System.Drawing.Size(623, 306);
            this.InnerContainer.SplitterDistance = 496;
            this.InnerContainer.TabIndex = 0;
            // 
            // TabControl
            // 
            this.TabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TabControl.DrawMode = System.Windows.Forms.TabDrawMode.OwnerDrawFixed;
            this.TabControl.Location = new System.Drawing.Point(0, 0);
            this.TabControl.Name = "TabControl";
            this.TabControl.Padding = new System.Drawing.Point(15, 3);
            this.TabControl.SelectedIndex = 0;
            this.TabControl.Size = new System.Drawing.Size(496, 306);
            this.TabControl.SizeMode = System.Windows.Forms.TabSizeMode.FillToRight;
            this.TabControl.TabIndex = 0;
            // 
            // ToolbarsPanel
            // 
            this.ToolbarsPanel.Controls.Add(this.label1);
            this.ToolbarsPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.ToolbarsPanel.Location = new System.Drawing.Point(0, 0);
            this.ToolbarsPanel.Name = "ToolbarsPanel";
            this.ToolbarsPanel.Size = new System.Drawing.Size(808, 34);
            this.ToolbarsPanel.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(4, 6);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(110, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "[Toolbar icons here...]";
            // 
            // showInExplorerToolStripMenuItem
            // 
            this.showInExplorerToolStripMenuItem.Name = "showInExplorerToolStripMenuItem";
            this.showInExplorerToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // newActorToolStripMenuItem
            // 
            this.newActorToolStripMenuItem.Name = "newActorToolStripMenuItem";
            this.newActorToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // newAssetToolStripMenuItem
            // 
            this.newAssetToolStripMenuItem.Name = "newAssetToolStripMenuItem";
            this.newAssetToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // newSceneToolStripMenuItem
            // 
            this.newSceneToolStripMenuItem.Name = "newSceneToolStripMenuItem";
            this.newSceneToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // ProjectTreeViewFolderContextMenu
            // 
            this.ProjectTreeViewFolderContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.showInExplorerToolStripMenuItem1});
            this.ProjectTreeViewFolderContextMenu.Name = "ProjectTreeViewFolderContextMenu";
            this.ProjectTreeViewFolderContextMenu.Size = new System.Drawing.Size(163, 26);
            // 
            // showInExplorerToolStripMenuItem1
            // 
            this.showInExplorerToolStripMenuItem1.Name = "showInExplorerToolStripMenuItem1";
            this.showInExplorerToolStripMenuItem1.Size = new System.Drawing.Size(162, 22);
            this.showInExplorerToolStripMenuItem1.Text = "Show In Explorer";
            this.showInExplorerToolStripMenuItem1.Click += new System.EventHandler(this.showInExplorerToolStripMenuItem1_Click);
            // 
            // ProjectTreeViewRootContextMenu
            // 
            this.ProjectTreeViewRootContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem3,
            this.showInExplorerToolStripMenuItem2});
            this.ProjectTreeViewRootContextMenu.Name = "ProjectTreeViewRootContextMenu";
            this.ProjectTreeViewRootContextMenu.Size = new System.Drawing.Size(157, 48);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.assetToolStripMenuItem});
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(156, 22);
            this.toolStripMenuItem3.Text = "Add";
            // 
            // assetToolStripMenuItem
            // 
            this.assetToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem1,
            this.fromFileToolStripMenuItem});
            this.assetToolStripMenuItem.Name = "assetToolStripMenuItem";
            this.assetToolStripMenuItem.Size = new System.Drawing.Size(102, 22);
            this.assetToolStripMenuItem.Text = "Asset";
            // 
            // newToolStripMenuItem1
            // 
            this.newToolStripMenuItem1.Name = "newToolStripMenuItem1";
            this.newToolStripMenuItem1.Size = new System.Drawing.Size(132, 22);
            this.newToolStripMenuItem1.Text = "New...";
            this.newToolStripMenuItem1.Click += new System.EventHandler(this.newToolStripMenuItem1_Click);
            // 
            // fromFileToolStripMenuItem
            // 
            this.fromFileToolStripMenuItem.Name = "fromFileToolStripMenuItem";
            this.fromFileToolStripMenuItem.Size = new System.Drawing.Size(132, 22);
            this.fromFileToolStripMenuItem.Text = "From File...";
            this.fromFileToolStripMenuItem.Click += new System.EventHandler(this.newAssetFromFileToolStripMenuItem_Click);
            // 
            // showInExplorerToolStripMenuItem2
            // 
            this.showInExplorerToolStripMenuItem2.Name = "showInExplorerToolStripMenuItem2";
            this.showInExplorerToolStripMenuItem2.Size = new System.Drawing.Size(156, 22);
            this.showInExplorerToolStripMenuItem2.Text = "ShowInExplorer";
            this.showInExplorerToolStripMenuItem2.Click += new System.EventHandler(this.showInExplorerToolStripMenuItem1_Click);
            // 
            // WorkspacePage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.Container);
            this.Controls.Add(this.ToolbarsPanel);
            this.Name = "WorkspacePage";
            this.Size = new System.Drawing.Size(808, 340);
            this.Container.Panel1.ResumeLayout(false);
            this.Container.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.Container)).EndInit();
            this.Container.ResumeLayout(false);
            this.InnerContainer.Panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.InnerContainer)).EndInit();
            this.InnerContainer.ResumeLayout(false);
            this.ToolbarsPanel.ResumeLayout(false);
            this.ToolbarsPanel.PerformLayout();
            this.ProjectTreeViewFolderContextMenu.ResumeLayout(false);
            this.ProjectTreeViewRootContextMenu.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer Container;
        private System.Windows.Forms.SplitContainer InnerContainer;
        private System.Windows.Forms.Panel ToolbarsPanel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TreeView ProjectTreeView;
        private Primitives.TabControl TabControl;
        private System.Windows.Forms.ToolStripMenuItem addToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem showInExplorerToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newActorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newAssetToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newSceneToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip ProjectTreeViewFolderContextMenu;
        private System.Windows.Forms.ToolStripMenuItem showInExplorerToolStripMenuItem1;
        private System.Windows.Forms.ContextMenuStrip ProjectTreeViewRootContextMenu;
        private System.Windows.Forms.ToolStripMenuItem showInExplorerToolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem assetToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem fromFileToolStripMenuItem;
    }
}
