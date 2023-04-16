namespace JSON_WinForms
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            menuStrip1 = new MenuStrip();
            открытьToolStripMenuItem = new ToolStripMenuItem();
            сохранитьКакToolStripMenuItem = new ToolStripMenuItem();
            treeView1 = new TreeView();
            richTextBox_write = new RichTextBox();
            tableLayoutPanel1 = new TableLayoutPanel();
            richTextBox_write_iterative = new RichTextBox();
            panel1 = new Panel();
            panel2 = new Panel();
            button_json_input = new Button();
            button_input_json = new Button();
            richTextBox1 = new RichTextBox();
            label1 = new Label();
            menuStrip1.SuspendLayout();
            tableLayoutPanel1.SuspendLayout();
            panel1.SuspendLayout();
            panel2.SuspendLayout();
            SuspendLayout();
            // 
            // menuStrip1
            // 
            menuStrip1.ImageScalingSize = new Size(20, 20);
            menuStrip1.Items.AddRange(new ToolStripItem[] { открытьToolStripMenuItem, сохранитьКакToolStripMenuItem });
            menuStrip1.Location = new Point(0, 0);
            menuStrip1.Name = "menuStrip1";
            menuStrip1.Size = new Size(882, 28);
            menuStrip1.TabIndex = 2;
            menuStrip1.Text = "menuStrip1";
            // 
            // открытьToolStripMenuItem
            // 
            открытьToolStripMenuItem.Name = "открытьToolStripMenuItem";
            открытьToolStripMenuItem.Size = new Size(81, 24);
            открытьToolStripMenuItem.Text = "Открыть";
            открытьToolStripMenuItem.Click += открытьToolStripMenuItem_Click;
            // 
            // сохранитьКакToolStripMenuItem
            // 
            сохранитьКакToolStripMenuItem.Enabled = false;
            сохранитьКакToolStripMenuItem.Name = "сохранитьКакToolStripMenuItem";
            сохранитьКакToolStripMenuItem.Size = new Size(132, 24);
            сохранитьКакToolStripMenuItem.Text = "Сохранить как...";
            сохранитьКакToolStripMenuItem.Click += сохранитьКакToolStripMenuItem_Click;
            // 
            // treeView1
            // 
            treeView1.Dock = DockStyle.Fill;
            treeView1.LabelEdit = true;
            treeView1.Location = new Point(0, 0);
            treeView1.Name = "treeView1";
            treeView1.Size = new Size(287, 419);
            treeView1.TabIndex = 3;
            // 
            // richTextBox_write
            // 
            richTextBox_write.BorderStyle = BorderStyle.FixedSingle;
            richTextBox_write.Dock = DockStyle.Fill;
            richTextBox_write.Location = new Point(589, 3);
            richTextBox_write.Name = "richTextBox_write";
            richTextBox_write.ReadOnly = true;
            richTextBox_write.Size = new Size(290, 206);
            richTextBox_write.TabIndex = 4;
            richTextBox_write.Text = "";
            richTextBox_write.WordWrap = false;
            // 
            // tableLayoutPanel1
            // 
            tableLayoutPanel1.ColumnCount = 3;
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 33.3333321F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 33.3333321F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 33.3333321F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 20F));
            tableLayoutPanel1.Controls.Add(richTextBox_write, 2, 0);
            tableLayoutPanel1.Controls.Add(richTextBox_write_iterative, 2, 1);
            tableLayoutPanel1.Controls.Add(panel1, 1, 0);
            tableLayoutPanel1.Controls.Add(panel2, 0, 0);
            tableLayoutPanel1.Dock = DockStyle.Fill;
            tableLayoutPanel1.Location = new Point(0, 28);
            tableLayoutPanel1.Name = "tableLayoutPanel1";
            tableLayoutPanel1.RowCount = 2;
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 20F));
            tableLayoutPanel1.Size = new Size(882, 425);
            tableLayoutPanel1.TabIndex = 5;
            // 
            // richTextBox_write_iterative
            // 
            richTextBox_write_iterative.BorderStyle = BorderStyle.FixedSingle;
            richTextBox_write_iterative.Dock = DockStyle.Fill;
            richTextBox_write_iterative.Location = new Point(589, 215);
            richTextBox_write_iterative.Name = "richTextBox_write_iterative";
            richTextBox_write_iterative.ReadOnly = true;
            richTextBox_write_iterative.Size = new Size(290, 207);
            richTextBox_write_iterative.TabIndex = 5;
            richTextBox_write_iterative.Text = "";
            richTextBox_write_iterative.WordWrap = false;
            // 
            // panel1
            // 
            panel1.Controls.Add(treeView1);
            panel1.Dock = DockStyle.Fill;
            panel1.Location = new Point(296, 3);
            panel1.Name = "panel1";
            tableLayoutPanel1.SetRowSpan(panel1, 2);
            panel1.Size = new Size(287, 419);
            panel1.TabIndex = 6;
            // 
            // panel2
            // 
            panel2.Controls.Add(button_json_input);
            panel2.Controls.Add(button_input_json);
            panel2.Controls.Add(richTextBox1);
            panel2.Controls.Add(label1);
            panel2.Dock = DockStyle.Fill;
            panel2.Location = new Point(3, 3);
            panel2.Name = "panel2";
            tableLayoutPanel1.SetRowSpan(panel2, 2);
            panel2.Size = new Size(287, 419);
            panel2.TabIndex = 7;
            // 
            // button_json_input
            // 
            button_json_input.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            button_json_input.Location = new Point(3, 387);
            button_json_input.Name = "button_json_input";
            button_json_input.Size = new Size(281, 29);
            button_json_input.TabIndex = 3;
            button_json_input.Text = "JSON -> Input";
            button_json_input.UseVisualStyleBackColor = true;
            button_json_input.Click += button_json_input_Click;
            // 
            // button_input_json
            // 
            button_input_json.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            button_input_json.Location = new Point(3, 352);
            button_input_json.Name = "button_input_json";
            button_input_json.Size = new Size(281, 29);
            button_input_json.TabIndex = 2;
            button_input_json.Text = "Input -> JSON";
            button_input_json.UseVisualStyleBackColor = true;
            button_input_json.Click += button_input_json_Click;
            // 
            // richTextBox1
            // 
            richTextBox1.AcceptsTab = true;
            richTextBox1.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            richTextBox1.Location = new Point(3, 25);
            richTextBox1.Name = "richTextBox1";
            richTextBox1.Size = new Size(281, 321);
            richTextBox1.TabIndex = 1;
            richTextBox1.Text = "";
            richTextBox1.WordWrap = false;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(3, 2);
            label1.Name = "label1";
            label1.Size = new Size(46, 20);
            label1.TabIndex = 0;
            label1.Text = "Input:";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(882, 453);
            Controls.Add(tableLayoutPanel1);
            Controls.Add(menuStrip1);
            MainMenuStrip = menuStrip1;
            Name = "Form1";
            Text = "JSON Visual";
            menuStrip1.ResumeLayout(false);
            menuStrip1.PerformLayout();
            tableLayoutPanel1.ResumeLayout(false);
            panel1.ResumeLayout(false);
            panel2.ResumeLayout(false);
            panel2.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private MenuStrip menuStrip1;
        private ToolStripMenuItem открытьToolStripMenuItem;
        private TreeView treeView1;
        private RichTextBox richTextBox_write;
        private TableLayoutPanel tableLayoutPanel1;
        private RichTextBox richTextBox_write_iterative;
        private Panel panel1;
        private ToolStripMenuItem сохранитьКакToolStripMenuItem;
        private Panel panel2;
        private RichTextBox richTextBox1;
        private Label label1;
        private Button button_json_input;
        private Button button_input_json;
    }
}