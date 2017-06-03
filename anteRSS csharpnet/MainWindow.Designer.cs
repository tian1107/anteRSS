namespace anteRSS_csharpnet
{
    partial class MainWindow
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
            this.topBar = new System.Windows.Forms.MenuStrip();
            this.buttonBar = new System.Windows.Forms.ToolStrip();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.splitLeftRight = new System.Windows.Forms.SplitContainer();
            this.splitUpDown = new System.Windows.Forms.SplitContainer();
            this.listView1 = new System.Windows.Forms.ListView();
            this.listView2 = new System.Windows.Forms.ListView();
            this.webBrowser1 = new System.Windows.Forms.WebBrowser();
            this.buttonNewFeed = new System.Windows.Forms.ToolStripButton();
            this.buttomRemoveFeed = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.buttonUpdate = new System.Windows.Forms.ToolStripButton();
            this.buttonUpdateAll = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.buttonMarkAllAsRead = new System.Windows.Forms.ToolStripButton();
            this.buttonToggleArchived = new System.Windows.Forms.ToolStripButton();
            this.topBar.SuspendLayout();
            this.buttonBar.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitLeftRight)).BeginInit();
            this.splitLeftRight.Panel1.SuspendLayout();
            this.splitLeftRight.Panel2.SuspendLayout();
            this.splitLeftRight.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitUpDown)).BeginInit();
            this.splitUpDown.Panel1.SuspendLayout();
            this.splitUpDown.Panel2.SuspendLayout();
            this.splitUpDown.SuspendLayout();
            this.SuspendLayout();
            // 
            // topBar
            // 
            this.topBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.topBar.Location = new System.Drawing.Point(0, 0);
            this.topBar.Name = "topBar";
            this.topBar.Size = new System.Drawing.Size(784, 24);
            this.topBar.TabIndex = 0;
            this.topBar.Text = "topBar";
            // 
            // buttonBar
            // 
            this.buttonBar.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.buttonBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.buttonNewFeed,
            this.buttomRemoveFeed,
            this.toolStripSeparator1,
            this.buttonUpdate,
            this.buttonUpdateAll,
            this.toolStripSeparator2,
            this.buttonMarkAllAsRead,
            this.buttonToggleArchived});
            this.buttonBar.Location = new System.Drawing.Point(0, 24);
            this.buttonBar.Name = "buttonBar";
            this.buttonBar.Size = new System.Drawing.Size(784, 25);
            this.buttonBar.TabIndex = 1;
            this.buttonBar.Text = "buttonBar";
            // 
            // statusStrip
            // 
            this.statusStrip.Location = new System.Drawing.Point(0, 539);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(784, 22);
            this.statusStrip.TabIndex = 2;
            this.statusStrip.Text = "statusStrip";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.exitToolStripMenuItem.Text = "E&xit";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "&Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.aboutToolStripMenuItem.Text = "&About";
            // 
            // splitLeftRight
            // 
            this.splitLeftRight.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitLeftRight.Location = new System.Drawing.Point(0, 49);
            this.splitLeftRight.Name = "splitLeftRight";
            // 
            // splitLeftRight.Panel1
            // 
            this.splitLeftRight.Panel1.Controls.Add(this.listView1);
            this.splitLeftRight.Panel1.Padding = new System.Windows.Forms.Padding(3, 0, 0, 0);
            // 
            // splitLeftRight.Panel2
            // 
            this.splitLeftRight.Panel2.Controls.Add(this.splitUpDown);
            this.splitLeftRight.Panel2.Padding = new System.Windows.Forms.Padding(0, 0, 3, 0);
            this.splitLeftRight.Size = new System.Drawing.Size(784, 490);
            this.splitLeftRight.SplitterDistance = 196;
            this.splitLeftRight.TabIndex = 3;
            // 
            // splitUpDown
            // 
            this.splitUpDown.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitUpDown.Location = new System.Drawing.Point(0, 0);
            this.splitUpDown.Name = "splitUpDown";
            this.splitUpDown.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitUpDown.Panel1
            // 
            this.splitUpDown.Panel1.Controls.Add(this.listView2);
            // 
            // splitUpDown.Panel2
            // 
            this.splitUpDown.Panel2.Controls.Add(this.webBrowser1);
            this.splitUpDown.Size = new System.Drawing.Size(581, 490);
            this.splitUpDown.SplitterDistance = 245;
            this.splitUpDown.TabIndex = 0;
            // 
            // listView1
            // 
            this.listView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listView1.Location = new System.Drawing.Point(3, 0);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(193, 490);
            this.listView1.TabIndex = 0;
            this.listView1.UseCompatibleStateImageBehavior = false;
            // 
            // listView2
            // 
            this.listView2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.listView2.Location = new System.Drawing.Point(0, 0);
            this.listView2.Name = "listView2";
            this.listView2.Size = new System.Drawing.Size(581, 245);
            this.listView2.TabIndex = 0;
            this.listView2.UseCompatibleStateImageBehavior = false;
            // 
            // webBrowser1
            // 
            this.webBrowser1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.webBrowser1.Location = new System.Drawing.Point(0, 0);
            this.webBrowser1.MinimumSize = new System.Drawing.Size(20, 20);
            this.webBrowser1.Name = "webBrowser1";
            this.webBrowser1.Size = new System.Drawing.Size(581, 241);
            this.webBrowser1.TabIndex = 0;
            // 
            // buttonNewFeed
            // 
            this.buttonNewFeed.Image = ((System.Drawing.Image)(resources.GetObject("buttonNewFeed.Image")));
            this.buttonNewFeed.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.buttonNewFeed.Name = "buttonNewFeed";
            this.buttonNewFeed.Size = new System.Drawing.Size(79, 22);
            this.buttonNewFeed.Text = "New Feed";
            this.buttonNewFeed.ToolTipText = "Add new feed URL";
            // 
            // buttomRemoveFeed
            // 
            this.buttomRemoveFeed.Image = ((System.Drawing.Image)(resources.GetObject("buttomRemoveFeed.Image")));
            this.buttomRemoveFeed.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.buttomRemoveFeed.Name = "buttomRemoveFeed";
            this.buttomRemoveFeed.Size = new System.Drawing.Size(98, 22);
            this.buttomRemoveFeed.Text = "Remove Feed";
            this.buttomRemoveFeed.ToolTipText = "Remove currently selected feed";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // buttonUpdate
            // 
            this.buttonUpdate.Image = ((System.Drawing.Image)(resources.GetObject("buttonUpdate.Image")));
            this.buttonUpdate.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.buttonUpdate.Name = "buttonUpdate";
            this.buttonUpdate.Size = new System.Drawing.Size(93, 22);
            this.buttonUpdate.Text = "Update Feed";
            this.buttonUpdate.ToolTipText = "Update currently selected feed";
            // 
            // buttonUpdateAll
            // 
            this.buttonUpdateAll.Image = ((System.Drawing.Image)(resources.GetObject("buttonUpdateAll.Image")));
            this.buttonUpdateAll.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.buttonUpdateAll.Name = "buttonUpdateAll";
            this.buttonUpdateAll.Size = new System.Drawing.Size(115, 22);
            this.buttonUpdateAll.Text = "Update All Feeds";
            this.buttonUpdateAll.ToolTipText = "Update all feeds";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // buttonMarkAllAsRead
            // 
            this.buttonMarkAllAsRead.Image = ((System.Drawing.Image)(resources.GetObject("buttonMarkAllAsRead.Image")));
            this.buttonMarkAllAsRead.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.buttonMarkAllAsRead.Name = "buttonMarkAllAsRead";
            this.buttonMarkAllAsRead.Size = new System.Drawing.Size(116, 22);
            this.buttonMarkAllAsRead.Text = "Mark All As Read";
            // 
            // buttonToggleArchived
            // 
            this.buttonToggleArchived.Image = ((System.Drawing.Image)(resources.GetObject("buttonToggleArchived.Image")));
            this.buttonToggleArchived.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.buttonToggleArchived.Name = "buttonToggleArchived";
            this.buttonToggleArchived.Size = new System.Drawing.Size(113, 22);
            this.buttonToggleArchived.Text = "Toggle Archived";
            this.buttonToggleArchived.ToolTipText = "Mark/Unmark item as Archived";
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 561);
            this.Controls.Add(this.splitLeftRight);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.buttonBar);
            this.Controls.Add(this.topBar);
            this.MainMenuStrip = this.topBar;
            this.Name = "MainWindow";
            this.Text = "anteRSS csharpnet";
            this.topBar.ResumeLayout(false);
            this.topBar.PerformLayout();
            this.buttonBar.ResumeLayout(false);
            this.buttonBar.PerformLayout();
            this.splitLeftRight.Panel1.ResumeLayout(false);
            this.splitLeftRight.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitLeftRight)).EndInit();
            this.splitLeftRight.ResumeLayout(false);
            this.splitUpDown.Panel1.ResumeLayout(false);
            this.splitUpDown.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitUpDown)).EndInit();
            this.splitUpDown.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip topBar;
        private System.Windows.Forms.ToolStrip buttonBar;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.SplitContainer splitLeftRight;
        private System.Windows.Forms.SplitContainer splitUpDown;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ListView listView2;
        private System.Windows.Forms.WebBrowser webBrowser1;
        private System.Windows.Forms.ToolStripButton buttonNewFeed;
        private System.Windows.Forms.ToolStripButton buttomRemoveFeed;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton buttonUpdate;
        private System.Windows.Forms.ToolStripButton buttonUpdateAll;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton buttonMarkAllAsRead;
        private System.Windows.Forms.ToolStripButton buttonToggleArchived;
    }
}

