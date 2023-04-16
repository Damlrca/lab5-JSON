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
            treeView1 = new TreeView();
            richTextBox_write = new RichTextBox();
            tableLayoutPanel1 = new TableLayoutPanel();
            richTextBox_write_iterative = new RichTextBox();
            menuStrip1.SuspendLayout();
            tableLayoutPanel1.SuspendLayout();
            SuspendLayout();
            // 
            // menuStrip1
            // 
            menuStrip1.ImageScalingSize = new Size(20, 20);
            menuStrip1.Items.AddRange(new ToolStripItem[] { открытьToolStripMenuItem });
            menuStrip1.Location = new Point(0, 0);
            menuStrip1.Name = "menuStrip1";
            menuStrip1.Size = new Size(482, 28);
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
            // treeView1
            // 
            treeView1.Dock = DockStyle.Fill;
            treeView1.Location = new Point(3, 3);
            treeView1.Name = "treeView1";
            treeView1.Size = new Size(154, 324);
            treeView1.TabIndex = 3;
            // 
            // richTextBox_write
            // 
            richTextBox_write.BorderStyle = BorderStyle.FixedSingle;
            richTextBox_write.Dock = DockStyle.Fill;
            richTextBox_write.Location = new Point(163, 3);
            richTextBox_write.Name = "richTextBox_write";
            richTextBox_write.ReadOnly = true;
            richTextBox_write.Size = new Size(154, 324);
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
            tableLayoutPanel1.Controls.Add(richTextBox_write, 1, 0);
            tableLayoutPanel1.Controls.Add(treeView1, 0, 0);
            tableLayoutPanel1.Controls.Add(richTextBox_write_iterative, 2, 0);
            tableLayoutPanel1.Dock = DockStyle.Fill;
            tableLayoutPanel1.Location = new Point(0, 28);
            tableLayoutPanel1.Name = "tableLayoutPanel1";
            tableLayoutPanel1.RowCount = 1;
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
            tableLayoutPanel1.Size = new Size(482, 330);
            tableLayoutPanel1.TabIndex = 5;
            // 
            // richTextBox_write_iterative
            // 
            richTextBox_write_iterative.BorderStyle = BorderStyle.FixedSingle;
            richTextBox_write_iterative.Dock = DockStyle.Fill;
            richTextBox_write_iterative.Location = new Point(323, 3);
            richTextBox_write_iterative.Name = "richTextBox_write_iterative";
            richTextBox_write_iterative.ReadOnly = true;
            richTextBox_write_iterative.Size = new Size(156, 324);
            richTextBox_write_iterative.TabIndex = 5;
            richTextBox_write_iterative.Text = "";
            richTextBox_write_iterative.WordWrap = false;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(482, 358);
            Controls.Add(tableLayoutPanel1);
            Controls.Add(menuStrip1);
            MainMenuStrip = menuStrip1;
            Name = "Form1";
            Text = "JSON Visual";
            menuStrip1.ResumeLayout(false);
            menuStrip1.PerformLayout();
            tableLayoutPanel1.ResumeLayout(false);
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
    }
}