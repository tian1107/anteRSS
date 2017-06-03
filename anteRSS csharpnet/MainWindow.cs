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

		public MainWindow()
		{
			manager = new anteRSSParserWrapper.RSSManagerWrapper("history.db");
			manager.updateFeedListCache();

			InitializeComponent();
			listFeeds.VirtualListSize = manager.getFeedListCacheLength();
		}

		private void listFeeds_RetrieveVirtualItem(object sender, RetrieveVirtualItemEventArgs e)
		{
			e.Item = new ListViewItem(manager.getFeedListCacheAt(e.ItemIndex).Name);
		}
	}
}
