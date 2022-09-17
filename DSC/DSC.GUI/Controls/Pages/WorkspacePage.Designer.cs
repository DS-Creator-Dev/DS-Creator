namespace DSC.GUI.Controls.Pages
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
            this.Container = new System.Windows.Forms.SplitContainer();
            this.InnerContainer = new System.Windows.Forms.SplitContainer();
            this.TabControl = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.ToolbarsPanel = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.ProjectTreeView = new System.Windows.Forms.TreeView();
            ((System.ComponentModel.ISupportInitialize)(this.Container)).BeginInit();
            this.Container.Panel1.SuspendLayout();
            this.Container.Panel2.SuspendLayout();
            this.Container.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.InnerContainer)).BeginInit();
            this.InnerContainer.Panel1.SuspendLayout();
            this.InnerContainer.SuspendLayout();
            this.TabControl.SuspendLayout();
            this.ToolbarsPanel.SuspendLayout();
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
            this.Container.Size = new System.Drawing.Size(609, 306);
            this.Container.SplitterDistance = 137;
            this.Container.TabIndex = 0;
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
            this.InnerContainer.Size = new System.Drawing.Size(468, 306);
            this.InnerContainer.SplitterDistance = 341;
            this.InnerContainer.TabIndex = 0;
            // 
            // TabControl
            // 
            this.TabControl.Controls.Add(this.tabPage1);
            this.TabControl.Controls.Add(this.tabPage2);
            this.TabControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TabControl.Location = new System.Drawing.Point(0, 0);
            this.TabControl.Name = "TabControl";
            this.TabControl.SelectedIndex = 0;
            this.TabControl.Size = new System.Drawing.Size(341, 306);
            this.TabControl.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(333, 280);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "tabPage1";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(192, 74);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // ToolbarsPanel
            // 
            this.ToolbarsPanel.Controls.Add(this.label1);
            this.ToolbarsPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.ToolbarsPanel.Location = new System.Drawing.Point(0, 0);
            this.ToolbarsPanel.Name = "ToolbarsPanel";
            this.ToolbarsPanel.Size = new System.Drawing.Size(609, 34);
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
            // ProjectTreeView
            // 
            this.ProjectTreeView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ProjectTreeView.Location = new System.Drawing.Point(3, 3);
            this.ProjectTreeView.Name = "ProjectTreeView";
            this.ProjectTreeView.Size = new System.Drawing.Size(131, 206);
            this.ProjectTreeView.TabIndex = 0;
            // 
            // WorkspacePage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.Container);
            this.Controls.Add(this.ToolbarsPanel);
            this.Name = "WorkspacePage";
            this.Size = new System.Drawing.Size(609, 340);
            this.Container.Panel1.ResumeLayout(false);
            this.Container.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.Container)).EndInit();
            this.Container.ResumeLayout(false);
            this.InnerContainer.Panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.InnerContainer)).EndInit();
            this.InnerContainer.ResumeLayout(false);
            this.TabControl.ResumeLayout(false);
            this.ToolbarsPanel.ResumeLayout(false);
            this.ToolbarsPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer Container;
        private System.Windows.Forms.SplitContainer InnerContainer;
        private System.Windows.Forms.TabControl TabControl;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Panel ToolbarsPanel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TreeView ProjectTreeView;
    }
}
