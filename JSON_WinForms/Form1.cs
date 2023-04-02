using JSON_Lib_CLR;

namespace JSON_WinForms
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            textBox1.Text = $"{JSON_CLR.test()}";
        }
    }
}
