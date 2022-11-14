namespace DSC.App.GUI.Controls.Pages
{
    partial class TitlePage
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
            this.LogoContainer = new System.Windows.Forms.Panel();
            this.Logo = new System.Windows.Forms.PictureBox();
            this.NewProjButton = new System.Windows.Forms.Button();
            this.LoadProjButton = new System.Windows.Forms.Button();
            this.DocsButton = new System.Windows.Forms.Button();
            this.ButtonsPanel = new System.Windows.Forms.Panel();
            this.DiscordButton = new System.Windows.Forms.Button();
            this.LogoContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Logo)).BeginInit();
            this.ButtonsPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // LogoContainer
            // 
            this.LogoContainer.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.LogoContainer.Controls.Add(this.Logo);
            this.LogoContainer.Location = new System.Drawing.Point(0, 39);
            this.LogoContainer.Name = "LogoContainer";
            this.LogoContainer.Size = new System.Drawing.Size(589, 185);
            this.LogoContainer.TabIndex = 0;
            // 
            // Logo
            // 
            this.Logo.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Logo.Image = global::DSC.App.Properties.Resources.DSC_Logo;
            this.Logo.Location = new System.Drawing.Point(0, 0);
            this.Logo.Name = "Logo";
            this.Logo.Size = new System.Drawing.Size(589, 185);
            this.Logo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.Logo.TabIndex = 0;
            this.Logo.TabStop = false;
            // 
            // NewProjButton
            // 
            this.NewProjButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.NewProjButton.Location = new System.Drawing.Point(4, 3);
            this.NewProjButton.Name = "NewProjButton";
            this.NewProjButton.Size = new System.Drawing.Size(136, 23);
            this.NewProjButton.TabIndex = 1;
            this.NewProjButton.Text = "New Project";
            this.NewProjButton.UseVisualStyleBackColor = true;
            this.NewProjButton.Click += new System.EventHandler(this.NewProjButton_Click);
            // 
            // LoadProjButton
            // 
            this.LoadProjButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.LoadProjButton.Location = new System.Drawing.Point(4, 32);
            this.LoadProjButton.Name = "LoadProjButton";
            this.LoadProjButton.Size = new System.Drawing.Size(136, 23);
            this.LoadProjButton.TabIndex = 2;
            this.LoadProjButton.Text = "Load Project";
            this.LoadProjButton.UseVisualStyleBackColor = true;
            this.LoadProjButton.Click += new System.EventHandler(this.LoadProjButton_Click);
            // 
            // DocsButton
            // 
            this.DocsButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.DocsButton.Location = new System.Drawing.Point(4, 61);
            this.DocsButton.Name = "DocsButton";
            this.DocsButton.Size = new System.Drawing.Size(136, 23);
            this.DocsButton.TabIndex = 3;
            this.DocsButton.Text = "Documentation";
            this.DocsButton.UseVisualStyleBackColor = true;
            this.DocsButton.Click += new System.EventHandler(this.DocsButton_Click);
            // 
            // ButtonsPanel
            // 
            this.ButtonsPanel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.ButtonsPanel.Controls.Add(this.DiscordButton);
            this.ButtonsPanel.Controls.Add(this.NewProjButton);
            this.ButtonsPanel.Controls.Add(this.DocsButton);
            this.ButtonsPanel.Controls.Add(this.LoadProjButton);
            this.ButtonsPanel.Location = new System.Drawing.Point(220, 230);
            this.ButtonsPanel.Name = "ButtonsPanel";
            this.ButtonsPanel.Size = new System.Drawing.Size(143, 118);
            this.ButtonsPanel.TabIndex = 4;
            // 
            // DiscordButton
            // 
            this.DiscordButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.DiscordButton.Location = new System.Drawing.Point(4, 90);
            this.DiscordButton.Name = "DiscordButton";
            this.DiscordButton.Size = new System.Drawing.Size(136, 23);
            this.DiscordButton.TabIndex = 4;
            this.DiscordButton.Text = "Discord";
            this.DiscordButton.UseVisualStyleBackColor = true;
            this.DiscordButton.Click += new System.EventHandler(this.DiscordButton_Click);
            // 
            // TitlePage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.ButtonsPanel);
            this.Controls.Add(this.LogoContainer);
            this.Name = "TitlePage";
            this.Size = new System.Drawing.Size(589, 364);
            this.LogoContainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.Logo)).EndInit();
            this.ButtonsPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel LogoContainer;
        private System.Windows.Forms.PictureBox Logo;
        private System.Windows.Forms.Button NewProjButton;
        private System.Windows.Forms.Button LoadProjButton;
        private System.Windows.Forms.Button DocsButton;
        private System.Windows.Forms.Panel ButtonsPanel;
        private System.Windows.Forms.Button DiscordButton;
    }
}
