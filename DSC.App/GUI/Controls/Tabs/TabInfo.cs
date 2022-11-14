using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.App.GUI.Controls.Tabs
{
    public class TabInfo : UserControl
    {
        public string HeaderName { get; set; }

        private bool _RequiresSave = false;
        public bool RequiresSave
        {
            get => _RequiresSave;
            protected set
            {
                if (_RequiresSave == true && value == false) 
                {                    
                    ChangesSaved?.Invoke(this, new EventArgs());                    
                }
                if (_RequiresSave != value)
                {
                    _RequiresSave = value;
                    SaveRequiredFlagChanged?.Invoke(this, new EventArgs());
                }
            }
        }
        public void MarkSaved() { RequiresSave = true; }

        public virtual bool SaveDataProc() { return true; }

        public void SaveData()         
        {
            if (SaveDataProc())
                RequiresSave = false;
        }

        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // TabInfo
            // 
            this.Name = "TabInfo";
            this.ResumeLayout(false);

        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == (Keys.Control | Keys.S))
            {
                SaveData();
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }

        public delegate void OnChangesSaved(object sender, EventArgs e);
        public event OnChangesSaved ChangesSaved;

        public delegate void OnSaveRequiredFlagChanged(object sender, EventArgs e);
        public event OnSaveRequiredFlagChanged SaveRequiredFlagChanged;
    }
}
