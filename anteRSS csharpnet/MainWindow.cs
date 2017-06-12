using System;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using anteRSSParserWrapper;

namespace anteRSS_csharpnet
{
	public partial class MainWindow : Form
	{
		private const int NUM_META_FEEDS = 2;

		private RSSManagerWrapper manager;

		public MainWindow()
		{
			manager = new RSSManagerWrapper("history.db");
			manager.updateFeedListCache();

			InitializeComponent();

			listFeeds.VirtualListSize = manager.getFeedListCacheLength() + NUM_META_FEEDS;

			browserItemDescription_changeContent("nothing yet");
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
				RSSFeedWrapper current = manager.getFeedListCacheAt(e.ItemIndex - NUM_META_FEEDS);
				e.Item.Text = Encoding.UTF8.GetString(Encoding.Default.GetBytes(current.Name)) + " (" + current.Unread + ")";
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

		private void listFeeds_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (listFeeds.SelectedIndices.Count < 1)
				return; 

			int index = listFeeds.SelectedIndices[0];
			// get feed
			if (index < NUM_META_FEEDS)
			{
				// unread
				if (index == 0) manager.cacheFeedItemsByStatus(0);
				// archived
				else if (index == 1) manager.cacheFeedItemsByStatus(2);
			}
			else
			{
				// the feed in question
				RSSFeedWrapper current = manager.getFeedListCacheAt(index - NUM_META_FEEDS);

				manager.cacheFeedItems(current.FeedId);
			}

			listItems.VirtualListSize = manager.getItemListCacheLength();
			listItems.SelectedIndices.Clear();
			listItems.Invalidate();
		}

		private void listItems_RetrieveVirtualItem(object sender, RetrieveVirtualItemEventArgs e)
		{
			RSSFeedItemWrapper current = manager.getItemListCacheAt(e.ItemIndex);

			e.Item = new ListViewItem("");
			e.Item.SubItems.Add("test");
			e.Item.SubItems.Add(Encoding.UTF8.GetString(Encoding.Default.GetBytes(current.Title)));
		}

		// from https://stackoverflow.com/a/20351048
		private void browserItemDescription_changeContent(string content)
		{
			browserItemDescription.Navigate("about:blank");
			if(browserItemDescription.Document == null)
			{
				browserItemDescription.Document.Write(string.Empty);
			}

			browserItemDescription.DocumentText = content;
		}

		private void listItems_SelectedIndexChanged(object sender, EventArgs e)
		{
			if (listItems.SelectedIndices.Count < 1)
				return;

			int index = listItems.SelectedIndices[0];
			RSSFeedItemWrapper current = manager.getItemListCacheAt(index);

			browserItemDescription_changeContent(Encoding.UTF8.GetString(Encoding.Default.GetBytes(current.Description)));
		}

		private void MainWindow_Load(object sender, EventArgs e)
		{
			// select unread feed
			listFeeds.SelectedIndices.Clear();
			listFeeds.SelectedIndices.Add(0);
			listFeeds.Select();
		}

		private void listItems_ItemActivate(object sender, EventArgs e)
		{
			if (listItems.SelectedIndices.Count < 1)
				return;

			// selected item
			RSSFeedItemWrapper current = manager.getItemListCacheAt(listItems.SelectedIndices[0]);

			MessageBox.Show(this, current.Link, "Link to open", MessageBoxButtons.OK);
		}
	}
}
