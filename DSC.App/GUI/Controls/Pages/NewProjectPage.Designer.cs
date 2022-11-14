using DSC.Commons.GUI.Controls;

namespace DSC.App.GUI.Controls.Pages
{
    partial class NewProjectPage
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
            this.ContentPanel = new System.Windows.Forms.Panel();
            this.ProjectNameBox = new System.Windows.Forms.TextBox();
            this.ProjectPathSeletor = new PathSelector();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.OkButton = new System.Windows.Forms.Button();
            this.BackButton = new System.Windows.Forms.Button();
            this.ContentPanel.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // ContentPanel
            // 
            this.ContentPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ContentPanel.Controls.Add(this.panel1);
            this.ContentPanel.Controls.Add(this.ProjectNameBox);
            this.ContentPanel.Controls.Add(this.ProjectPathSeletor);
            this.ContentPanel.Controls.Add(this.label2);
            this.ContentPanel.Controls.Add(this.label1);
            this.ContentPanel.Location = new System.Drawing.Point(85, 52);
            this.ContentPanel.Name = "ContentPanel";
            this.ContentPanel.Size = new System.Drawing.Size(340, 175);
            this.ContentPanel.TabIndex = 0;
            // 
            // ProjectNameBox
            // 
            this.ProjectNameBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.ProjectNameBox.Location = new System.Drawing.Point(97, 50);
            this.ProjectNameBox.Name = "ProjectNameBox";
            this.ProjectNameBox.Size = new System.Drawing.Size(239, 20);
            this.ProjectNameBox.TabIndex = 3;
            this.ProjectNameBox.TextChanged += new System.EventHandler(this.ProjectNameBox_TextChanged);
            // 
            // ProjectPathSeletor
            // 
            this.ProjectPathSeletor.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.ProjectPathSeletor.Location = new System.Drawing.Point(97, 78);
            this.ProjectPathSeletor.Name = "ProjectPathSeletor";
            this.ProjectPathSeletor.Path = "";
            this.ProjectPathSeletor.SelectsFolder = true;
            this.ProjectPathSeletor.Size = new System.Drawing.Size(240, 20);
            this.ProjectPathSeletor.TabIndex = 2;
            this.ProjectPathSeletor.PathChanged += new PathSelector.OnPathChanged(this.ProjectPathSeletor_PathChanged);
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 82);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "ProjectPath";
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 53);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Project Name";
            // 
            // panel1
            // 
            this.panel1.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.panel1.Controls.Add(this.BackButton);
            this.panel1.Controls.Add(this.OkButton);
            this.panel1.Location = new System.Drawing.Point(173, 104);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(163, 31);
            this.panel1.TabIndex = 4;
            // 
            // OkButton
            // 
            this.OkButton.Location = new System.Drawing.Point(84, 4);
            this.OkButton.Name = "OkButton";
            this.OkButton.Size = new System.Drawing.Size(75, 23);
            this.OkButton.TabIndex = 0;
            this.OkButton.Text = "Ok";
            this.OkButton.UseVisualStyleBackColor = true;
            this.OkButton.Click += new System.EventHandler(this.OkButton_Click);
            // 
            // BackButton
            // 
            this.BackButton.Location = new System.Drawing.Point(3, 4);
            this.BackButton.Name = "BackButton";
            this.BackButton.Size = new System.Drawing.Size(75, 23);
            this.BackButton.TabIndex = 1;
            this.BackButton.Text = "Back";
            this.BackButton.UseVisualStyleBackColor = true;
            this.BackButton.Click += new System.EventHandler(this.BackButton_Click);
            // 
            // NewProjectPage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ContentPanel);
            this.Name = "NewProjectPage";
            this.Size = new System.Drawing.Size(508, 287);
            this.ContentPanel.ResumeLayout(false);
            this.ContentPanel.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel ContentPanel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private PathSelector ProjectPathSeletor;
        private System.Windows.Forms.TextBox ProjectNameBox;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button BackButton;
        private System.Windows.Forms.Button OkButton;
    }
}
