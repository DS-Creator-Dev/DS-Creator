namespace DSC.App.GUI.Controls.Tabs
{
    partial class AssetTab
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
            this.ImageContainer = new System.Windows.Forms.Panel();
            this.ImagePanel = new System.Windows.Forms.Panel();
            this.GridPanel = new DSC.App.GUI.Controls.Primitives.TransparentPanel();
            this.ZoomInBtn = new System.Windows.Forms.Button();
            this.ZoomOutBtn = new System.Windows.Forms.Button();
            this.ColorPicker = new System.Windows.Forms.ColorDialog();
            this.label1 = new System.Windows.Forms.Label();
            this.TransparentColorButton = new System.Windows.Forms.Button();
            this.PropertiesPanel = new System.Windows.Forms.Panel();
            this.label2 = new System.Windows.Forms.Label();
            this.ImageContainer.SuspendLayout();
            this.ImagePanel.SuspendLayout();
            this.PropertiesPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // ImageContainer
            // 
            this.ImageContainer.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ImageContainer.AutoScroll = true;
            this.ImageContainer.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.ImageContainer.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ImageContainer.Controls.Add(this.ImagePanel);
            this.ImageContainer.Location = new System.Drawing.Point(3, 3);
            this.ImageContainer.Name = "ImageContainer";
            this.ImageContainer.Size = new System.Drawing.Size(463, 365);
            this.ImageContainer.TabIndex = 0;
            // 
            // ImagePanel
            // 
            this.ImagePanel.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.ImagePanel.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.ImagePanel.Controls.Add(this.GridPanel);
            this.ImagePanel.Location = new System.Drawing.Point(0, 0);
            this.ImagePanel.Name = "ImagePanel";
            this.ImagePanel.Size = new System.Drawing.Size(128, 128);
            this.ImagePanel.TabIndex = 0;
            this.ImagePanel.Paint += new System.Windows.Forms.PaintEventHandler(this.ImagePanel_Paint);
            // 
            // GridPanel
            // 
            this.GridPanel.BackColor = System.Drawing.Color.Transparent;
            this.GridPanel.Location = new System.Drawing.Point(0, 0);
            this.GridPanel.Name = "GridPanel";
            this.GridPanel.Size = new System.Drawing.Size(128, 128);
            this.GridPanel.TabIndex = 1;
            this.GridPanel.Paint += new System.Windows.Forms.PaintEventHandler(this.GridPanel_Paint);
            // 
            // ZoomInBtn
            // 
            this.ZoomInBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.ZoomInBtn.Location = new System.Drawing.Point(472, 316);
            this.ZoomInBtn.Name = "ZoomInBtn";
            this.ZoomInBtn.Size = new System.Drawing.Size(75, 23);
            this.ZoomInBtn.TabIndex = 1;
            this.ZoomInBtn.Text = "Zoom In";
            this.ZoomInBtn.UseVisualStyleBackColor = true;
            this.ZoomInBtn.Click += new System.EventHandler(this.ZoomInBtn_Click);
            // 
            // ZoomOutBtn
            // 
            this.ZoomOutBtn.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.ZoomOutBtn.Location = new System.Drawing.Point(472, 345);
            this.ZoomOutBtn.Name = "ZoomOutBtn";
            this.ZoomOutBtn.Size = new System.Drawing.Size(75, 23);
            this.ZoomOutBtn.TabIndex = 2;
            this.ZoomOutBtn.Text = "Zoom Out";
            this.ZoomOutBtn.UseVisualStyleBackColor = true;
            this.ZoomOutBtn.Click += new System.EventHandler(this.ZoomOutBtn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(94, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Transparent Color:";
            // 
            // TransparentColorButton
            // 
            this.TransparentColorButton.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.TransparentColorButton.FlatAppearance.BorderSize = 0;
            this.TransparentColorButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.TransparentColorButton.Location = new System.Drawing.Point(112, 8);
            this.TransparentColorButton.Name = "TransparentColorButton";
            this.TransparentColorButton.Size = new System.Drawing.Size(49, 23);
            this.TransparentColorButton.TabIndex = 4;
            this.TransparentColorButton.UseVisualStyleBackColor = false;
            this.TransparentColorButton.Click += new System.EventHandler(this.TransparentColorButton_Click);
            // 
            // PropertiesPanel
            // 
            this.PropertiesPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.PropertiesPanel.Controls.Add(this.label2);
            this.PropertiesPanel.Controls.Add(this.label1);
            this.PropertiesPanel.Controls.Add(this.TransparentColorButton);
            this.PropertiesPanel.Location = new System.Drawing.Point(472, 33);
            this.PropertiesPanel.Name = "PropertiesPanel";
            this.PropertiesPanel.Size = new System.Drawing.Size(192, 136);
            this.PropertiesPanel.TabIndex = 5;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(17, 34);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(144, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "[To add custom color picker ^]";
            // 
            // AssetTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.PropertiesPanel);
            this.Controls.Add(this.ZoomOutBtn);
            this.Controls.Add(this.ZoomInBtn);
            this.Controls.Add(this.ImageContainer);
            this.Name = "AssetTab";
            this.Size = new System.Drawing.Size(667, 371);
            this.ImageContainer.ResumeLayout(false);
            this.ImagePanel.ResumeLayout(false);
            this.PropertiesPanel.ResumeLayout(false);
            this.PropertiesPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel ImageContainer;
        private System.Windows.Forms.Panel ImagePanel;
        private Primitives.TransparentPanel GridPanel;
        private System.Windows.Forms.Button ZoomInBtn;
        private System.Windows.Forms.Button ZoomOutBtn;
        private System.Windows.Forms.ColorDialog ColorPicker;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button TransparentColorButton;
        private System.Windows.Forms.Panel PropertiesPanel;
        private System.Windows.Forms.Label label2;
    }
}
