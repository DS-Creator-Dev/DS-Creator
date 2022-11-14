namespace DSC.Installer
{
    partial class MainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.InstallPathSelector = new DSC.Commons.GUI.Controls.PathSelector();
            this.label1 = new System.Windows.Forms.Label();
            this.InstallButton = new System.Windows.Forms.Button();
            this.ReportBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // InstallPathSelector
            // 
            this.InstallPathSelector.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.InstallPathSelector.Location = new System.Drawing.Point(12, 46);
            this.InstallPathSelector.Name = "InstallPathSelector";
            this.InstallPathSelector.Path = "C:\\DS-Creator";
            this.InstallPathSelector.SelectsFolder = false;
            this.InstallPathSelector.Size = new System.Drawing.Size(732, 20);
            this.InstallPathSelector.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(102, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "DSC Installer";
            // 
            // InstallButton
            // 
            this.InstallButton.Location = new System.Drawing.Point(15, 72);
            this.InstallButton.Name = "InstallButton";
            this.InstallButton.Size = new System.Drawing.Size(75, 23);
            this.InstallButton.TabIndex = 2;
            this.InstallButton.Text = "Install";
            this.InstallButton.UseVisualStyleBackColor = true;
            this.InstallButton.Click += new System.EventHandler(this.InstallButton_Click);
            // 
            // ReportBox
            // 
            this.ReportBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ReportBox.Location = new System.Drawing.Point(15, 101);
            this.ReportBox.Multiline = true;
            this.ReportBox.Name = "ReportBox";
            this.ReportBox.Size = new System.Drawing.Size(729, 157);
            this.ReportBox.TabIndex = 3;
            // 
            // MainForm
            // 
            this.AcceptButton = this.InstallButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(756, 270);
            this.Controls.Add(this.ReportBox);
            this.Controls.Add(this.InstallButton);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.InstallPathSelector);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainForm";
            this.Text = "DSC Installer";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Commons.GUI.Controls.PathSelector InstallPathSelector;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button InstallButton;
        private System.Windows.Forms.TextBox ReportBox;
    }
}

