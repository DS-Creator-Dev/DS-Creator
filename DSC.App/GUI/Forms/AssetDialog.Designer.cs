namespace DSC.App.GUI.Forms
{
    partial class AssetDialog
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.NameBox = new System.Windows.Forms.TextBox();
            this.PreviewPanel = new System.Windows.Forms.Panel();
            this.OkButton = new System.Windows.Forms.Button();
            this.SizePanelContainer = new System.Windows.Forms.Panel();
            this.SizePanel = new System.Windows.Forms.Panel();
            this.TileSizeBox = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.VerticalSep = new System.Windows.Forms.Panel();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.ErrorsLabel = new System.Windows.Forms.Label();
            this.Preview = new System.Windows.Forms.PictureBox();
            this.RowsCountBox = new DSC.App.GUI.Controls.Primitives.MeasureUpDown();
            this.ColsCountBox = new DSC.App.GUI.Controls.Primitives.MeasureUpDown();
            this.HeightBox = new DSC.App.GUI.Controls.Primitives.MeasureUpDown();
            this.WidthBox = new DSC.App.GUI.Controls.Primitives.MeasureUpDown();
            this.PreviewPanel.SuspendLayout();
            this.SizePanelContainer.SuspendLayout();
            this.SizePanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Preview)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RowsCountBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ColsCountBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.HeightBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.WidthBox)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(64, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Asset Name";
            // 
            // NameBox
            // 
            this.NameBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.NameBox.Location = new System.Drawing.Point(82, 6);
            this.NameBox.Name = "NameBox";
            this.NameBox.Size = new System.Drawing.Size(742, 20);
            this.NameBox.TabIndex = 1;
            this.NameBox.TextChanged += new System.EventHandler(this.NameBox_TextChanged);
            // 
            // PreviewPanel
            // 
            this.PreviewPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this.PreviewPanel.AutoScroll = true;
            this.PreviewPanel.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.PreviewPanel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.PreviewPanel.Controls.Add(this.Preview);
            this.PreviewPanel.Location = new System.Drawing.Point(388, 32);
            this.PreviewPanel.Name = "PreviewPanel";
            this.PreviewPanel.Size = new System.Drawing.Size(436, 377);
            this.PreviewPanel.TabIndex = 2;
            // 
            // OkButton
            // 
            this.OkButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.OkButton.Location = new System.Drawing.Point(749, 415);
            this.OkButton.Name = "OkButton";
            this.OkButton.Size = new System.Drawing.Size(75, 23);
            this.OkButton.TabIndex = 3;
            this.OkButton.Text = "Ok";
            this.OkButton.UseVisualStyleBackColor = true;
            this.OkButton.Click += new System.EventHandler(this.OkButton_Click);
            // 
            // SizePanelContainer
            // 
            this.SizePanelContainer.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.SizePanelContainer.Controls.Add(this.SizePanel);
            this.SizePanelContainer.Location = new System.Drawing.Point(12, 134);
            this.SizePanelContainer.Name = "SizePanelContainer";
            this.SizePanelContainer.Size = new System.Drawing.Size(369, 208);
            this.SizePanelContainer.TabIndex = 4;
            // 
            // SizePanel
            // 
            this.SizePanel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.SizePanel.Controls.Add(this.ErrorsLabel);
            this.SizePanel.Controls.Add(this.TileSizeBox);
            this.SizePanel.Controls.Add(this.label5);
            this.SizePanel.Controls.Add(this.RowsCountBox);
            this.SizePanel.Controls.Add(this.ColsCountBox);
            this.SizePanel.Controls.Add(this.label6);
            this.SizePanel.Controls.Add(this.label4);
            this.SizePanel.Controls.Add(this.VerticalSep);
            this.SizePanel.Controls.Add(this.label2);
            this.SizePanel.Controls.Add(this.HeightBox);
            this.SizePanel.Controls.Add(this.WidthBox);
            this.SizePanel.Controls.Add(this.label3);
            this.SizePanel.Location = new System.Drawing.Point(3, 45);
            this.SizePanel.Name = "SizePanel";
            this.SizePanel.Size = new System.Drawing.Size(366, 144);
            this.SizePanel.TabIndex = 4;
            // 
            // TileSizeBox
            // 
            this.TileSizeBox.FormattingEnabled = true;
            this.TileSizeBox.Items.AddRange(new object[] {
            "8x8",
            "8x16",
            "8x32",
            "16x8",
            "16x16",
            "16x32",
            "32x8",
            "32x16",
            "32x32",
            "32x64",
            "64x32",
            "64x64"});
            this.TileSizeBox.Location = new System.Drawing.Point(271, 9);
            this.TileSizeBox.Name = "TileSizeBox";
            this.TileSizeBox.Size = new System.Drawing.Size(92, 21);
            this.TileSizeBox.TabIndex = 11;
            this.TileSizeBox.Text = "8x8";
            this.TileSizeBox.SelectedIndexChanged += new System.EventHandler(this.TileSizeBox_SelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(170, 37);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(78, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Columns Count";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(170, 63);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 13);
            this.label6.TabIndex = 9;
            this.label6.Text = "Rows Count";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(170, 12);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Tile Size";
            // 
            // VerticalSep
            // 
            this.VerticalSep.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.VerticalSep.Location = new System.Drawing.Point(162, 10);
            this.VerticalSep.Name = "VerticalSep";
            this.VerticalSep.Size = new System.Drawing.Size(2, 80);
            this.VerticalSep.TabIndex = 4;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(64, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Asset Width";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 58);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(67, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Asset Height";
            // 
            // ErrorsLabel
            // 
            this.ErrorsLabel.AutoSize = true;
            this.ErrorsLabel.ForeColor = System.Drawing.Color.Red;
            this.ErrorsLabel.Location = new System.Drawing.Point(6, 96);
            this.ErrorsLabel.Name = "ErrorsLabel";
            this.ErrorsLabel.Size = new System.Drawing.Size(60, 13);
            this.ErrorsLabel.TabIndex = 12;
            this.ErrorsLabel.Text = "Errors Here";
            // 
            // Preview
            // 
            this.Preview.BackColor = System.Drawing.Color.White;
            this.Preview.Location = new System.Drawing.Point(0, 0);
            this.Preview.Name = "Preview";
            this.Preview.Size = new System.Drawing.Size(32, 32);
            this.Preview.TabIndex = 0;
            this.Preview.TabStop = false;
            // 
            // RowsCountBox
            // 
            this.RowsCountBox.Location = new System.Drawing.Point(271, 61);
            this.RowsCountBox.Maximum = new decimal(new int[] {
            65536,
            0,
            0,
            0});
            this.RowsCountBox.MeasureUnit = "tiles";
            this.RowsCountBox.Name = "RowsCountBox";
            this.RowsCountBox.Size = new System.Drawing.Size(92, 20);
            this.RowsCountBox.TabIndex = 10;
            this.RowsCountBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.RowsCountBox.ValueChanged += new System.EventHandler(this.RowsCountBox_ValueChanged);
            // 
            // ColsCountBox
            // 
            this.ColsCountBox.Location = new System.Drawing.Point(271, 35);
            this.ColsCountBox.Maximum = new decimal(new int[] {
            65536,
            0,
            0,
            0});
            this.ColsCountBox.MeasureUnit = "tiles";
            this.ColsCountBox.Name = "ColsCountBox";
            this.ColsCountBox.Size = new System.Drawing.Size(92, 20);
            this.ColsCountBox.TabIndex = 7;
            this.ColsCountBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.ColsCountBox.ValueChanged += new System.EventHandler(this.ColsCountBox_ValueChanged);
            // 
            // HeightBox
            // 
            this.HeightBox.Location = new System.Drawing.Point(83, 56);
            this.HeightBox.Maximum = new decimal(new int[] {
            65536,
            0,
            0,
            0});
            this.HeightBox.MeasureUnit = "px";
            this.HeightBox.Name = "HeightBox";
            this.HeightBox.Size = new System.Drawing.Size(73, 20);
            this.HeightBox.TabIndex = 3;
            this.HeightBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.HeightBox.ValueChanged += new System.EventHandler(this.HeightBox_ValueChanged);
            // 
            // WidthBox
            // 
            this.WidthBox.Location = new System.Drawing.Point(83, 30);
            this.WidthBox.Maximum = new decimal(new int[] {
            65536,
            0,
            0,
            0});
            this.WidthBox.MeasureUnit = "px";
            this.WidthBox.Name = "WidthBox";
            this.WidthBox.Size = new System.Drawing.Size(73, 20);
            this.WidthBox.TabIndex = 0;
            this.WidthBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.WidthBox.ValueChanged += new System.EventHandler(this.WidthBox_ValueChanged);
            // 
            // AssetDialog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(836, 450);
            this.Controls.Add(this.SizePanelContainer);
            this.Controls.Add(this.OkButton);
            this.Controls.Add(this.PreviewPanel);
            this.Controls.Add(this.NameBox);
            this.Controls.Add(this.label1);
            this.Name = "AssetDialog";
            this.Text = "AssetDialog";
            this.PreviewPanel.ResumeLayout(false);
            this.SizePanelContainer.ResumeLayout(false);
            this.SizePanel.ResumeLayout(false);
            this.SizePanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Preview)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RowsCountBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ColsCountBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.HeightBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.WidthBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox NameBox;
        private System.Windows.Forms.Panel PreviewPanel;
        private System.Windows.Forms.Button OkButton;
        private System.Windows.Forms.Panel SizePanelContainer;
        private Controls.Primitives.MeasureUpDown WidthBox;
        private Controls.Primitives.MeasureUpDown HeightBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Panel SizePanel;
        private System.Windows.Forms.Panel VerticalSep;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private Controls.Primitives.MeasureUpDown RowsCountBox;
        private Controls.Primitives.MeasureUpDown ColsCountBox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox TileSizeBox;
        private System.Windows.Forms.Label ErrorsLabel;
        private System.Windows.Forms.PictureBox Preview;
    }
}