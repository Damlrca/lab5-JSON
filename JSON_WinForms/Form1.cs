using JSON_Lib_CLR;

namespace JSON_WinForms
{
    public partial class Form1 : Form
    {
        private readonly JSON js;

        public Form1()
        {
            InitializeComponent();
            js = new JSON();
            Update_richTextBox_write();
            Update_richTextBox_write_iterative();
            Update_treeView();
            richTextBox1.SelectionStart = 0;
            ActiveControl = richTextBox1;
        }

        private void Update_treeView()
        {
            treeView1.Nodes.Clear();
            TreeNode treeNode = js.GenerateTreeNode();
            if (treeNode != null)
                treeView1.Nodes.Add(treeNode);
        }

        private void Update_richTextBox_write()
        {
            richTextBox_write.Text = "JSON::write_to_string:\n" + js.write_to_string();
        }

        private void Update_richTextBox_write_iterative()
        {
            richTextBox_write_iterative.Text = "JSON::write_to_string_iterarive:\n" + js.write_to_string_iterative();
        }

        private void JSON_to_Input()
        {
            richTextBox1.Text = js.write_to_string();
        }

        private void Input_to_JSON()
        {
            js.read_from_string(richTextBox1.Text);
        }

        private void îòêðûòüToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                js.read_file(ofd.FileName);
                Update_richTextBox_write();
                Update_richTextBox_write_iterative();
                Update_treeView();
                JSON_to_Input();
            }
        }

        private void ñîõðàíèòüÊàêToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void button_input_json_Click(object sender, EventArgs e)
        {
            Input_to_JSON();
            Update_richTextBox_write();
            Update_richTextBox_write_iterative();
            Update_treeView();
        }

        private void button_json_input_Click(object sender, EventArgs e)
        {
            JSON_to_Input();
        }
    }
}
