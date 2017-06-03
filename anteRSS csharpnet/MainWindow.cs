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
		private anteRSSParserWrapper.RSSManagerWrapper manager;
		private ListViewItem tempListFeedItem;

		public MainWindow()
		{
			tempListFeedItem = new ListViewItem("####");

			manager = new anteRSSParserWrapper.RSSManagerWrapper("history.db");
			manager.updateFeedListCache();

			InitializeComponent();
			listFeeds.VirtualListSize = manager.getFeedListCacheLength();
		}

		private void listFeeds_RetrieveVirtualItem(object sender, RetrieveVirtualItemEventArgs e)
		{
			e.Item = tempListFeedItem;
			e.Item.Text = manager.getFeedListCacheAt(e.ItemIndex).Name;
#if DEBUG
			e.Item.ImageIndex = e.ItemIndex & 1;
#else
			e.Item.ImageIndex = 0;
#endif
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
