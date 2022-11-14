using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DSC.App.GUI.Controls.Primitives
{ 
    internal class MeasureUpDown : NumericUpDown
    {
        public MeasureUpDown()
        {                        
        }     

        public string MeasureUnit { get; set; } = "";

        /// <summary>
        /// Method called when updating the numeric updown text.
        /// </summary>
        protected override void UpdateEditText()
        {
            Text = Value.ToString() + " " + MeasureUnit;
        }

        /// <summary>
        /// Validate method called before actually updating the text.
        /// This is exactly the same as the base class but it will use the new ParseEditText from this class instead.
        /// </summary>
        protected override void ValidateEditText()
        {
            ParseEditText();
            UpdateEditText();                
        }

        /// <summary>
        /// Converts the text displayed in the up-down control to a numeric value and evaluates it.
        /// </summary>
        protected new void ParseEditText()
        {            
            var txt = Text;            
            if (MeasureUnit != "")
            {
                if (txt.EndsWith(MeasureUnit))
                {
                    txt = txt.Substring(0, txt.Length - MeasureUnit.Length);
                }
            }
            var components = txt.Split(' ').Where(t => t != "").ToArray();

            //MessageBox.Show();

            if (components.Length != 1) return;

            if (int.TryParse(components[0], out int result))
            {
                Value = result;
            }
            UserEdit = false;
        }
    }
}
