using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace anteRSS_csharpnet
{
	public partial class MainWindow : Form
	{
		private const int NUM_META_FEEDS = 2;

		private anteRSSParserWrapper.RSSManagerWrapper manager;

		public MainWindow()
		{
			manager = new anteRSSParserWrapper.RSSManagerWrapper("history.db");
			manager.updateFeedListCache();

			InitializeComponent();
			listFeeds.VirtualListSize = manager.getFeedListCacheLength();
		}

		private void listFeeds_RetrieveVirtualItem(object sender, RetrieveVirtualItemEventArgs e)
		{
			e.Item = new ListViewItem();
			// Unread
			if (e.ItemIndex == 0)
			{
				e.Item.Text = "Unread (0)";
			}
			// Archived
			else if (e.ItemIndex == 1)
			{
				e.Item.Text = "Archived (0)";
			}
			else
			{
				anteRSSParserWrapper.RSSFeedWrapper current = manager.getFeedListCacheAt(e.ItemIndex - NUM_META_FEEDS);
				e.Item.Text = current.Name + " (" + current.Unread + ")";
				if (current.Unread > 0)
				{
					e.Item.ForeColor = Color.Blue;
				}
				else
				{
					e.Item.ForeColor = SystemColors.WindowText;
				}

#if DEBUG
				e.Item.ImageIndex = e.ItemIndex & 1;
#else
				e.Item.ImageIndex = 0;
#endif
			}
		}

		private void splitLeftRight_SplitterMoved(object sender, SplitterEventArgs e)
		{
			Properties.Settings.Default.formLeftRightSplitter = splitLeftRight.SplitterDistance;
		}

		private void splitUpDown_SplitterMoved(object sender, SplitterEventArgs e)
		{
			Properties.Settings.Default.formUpDownSplitter = splitUpDown.SplitterDistance;
		}
	}
}
