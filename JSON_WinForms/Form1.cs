using JSON_Lib_CLR;

namespace JSON_WinForms
{
    public partial class Form1 : Form
    {
        private JSON js = new JSON();

        public Form1()
        {
            InitializeComponent();
        }

        private void îòêðûòüToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                js.read_file(ofd.FileName);
                richTextBox1.Text = js.write_to_string();
                treeView1.Nodes.Clear();
                treeView1.Nodes.Add(js.GenerateTreeNode());
            }
        }
    }
}
