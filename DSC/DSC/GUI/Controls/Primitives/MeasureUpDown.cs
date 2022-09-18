using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.GUI.Controls.Primitives
{ 
    internal class MeasureUpDown : NumericUpDown
    {
        public MeasureUpDown()
        {
            var _event = GetType().GetEvent("TextChanged", BindingFlags.Public);
            var _method = GetType().GetMethod("OnMeasureTextChanged", BindingFlags.NonPublic);
            Delegate handler = Delegate.CreateDelegate(_event.EventHandlerType, this, _method);
            _event.AddEventHandler(this, handler);
        }

        private void OnMeasureTextChanged(object Sender, EventArgs e)
        {
            MessageBox.Show("Here");
        }

        public string MeasureUnit { get; set; } = "";
        protected override void UpdateEditText()
        {
            Text = Value.ToString() + " " + MeasureUnit;
        }

        protected override void ValidateEditText()
        {
            ParseEditText();
            UpdateEditText();                
        }

        protected new void ParseEditText()
        {
            var components = Text.Split(' ').Where(t => t != "").ToArray();
            if(components.Length==1)
            {
                //int.TryParse()
                try
                {

                }
            }
            else if(components.Length==2)
            {

            }
        }
    }
}
