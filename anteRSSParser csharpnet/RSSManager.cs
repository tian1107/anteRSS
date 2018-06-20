using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace anteRSSParser_csharpnet
{
	public struct RSSFeed
	{
		public readonly Int32 id;
		public String name;
		public readonly String url;
		public Int32 unread;
	}

	public enum RSSFeedItemStatus:Int32
	{
		unread = 0,
		read = 1,
		archived = 2 
	}

	public struct RSSFeedItem
	{
		public String guid;
		public String title;
		public String description;
		public Int32 feedid;
		public String date;
		public String link;
		public String contentEncoded;
		public RSSFeedItemStatus status;
	};

	public delegate void OnFeedUpdateCallback(Int32 feedId, Boolean success, RSSFeedItem [] newItems);

	public class RSSManager
	{
		public RSSManager(String filename)
		{

		}

		public Int32 AddFeed(String name, String url)
		{
			// Returns the feed id
			return 0;
		}

		public Int32 AddFeed(String url)
		{
			// Returns the feed id
			return 0;
		}

		public void RenameFeed(Int32 feedId, String name)
		{
			
		}

		RSSFeed [] GetAllFeeds()
		{
			return new RSSFeed[0];
		}

		RSSFeed [] GetItemsofFeed(Int32 feedId)
		{
			return new RSSFeed[0];
		}

		RSSFeed [] GetItemsofStatus(RSSFeedItemStatus status)
		{
			return new RSSFeed[0];
		}

		void RemoveFeed(Int32 feedId)
		{

		}

		void UpdateFeed(Int32 feedId, OnFeedUpdateCallback callback)
		{

		}

		void UpdateAllFeeds(OnFeedUpdateCallback callback)
		{

		}

		void ChangeFeedItemStatus(String guid, RSSFeedItemStatus status)
		{

		}

		void MarkAllAsRead(Int32 feedId)
		{
			
		}
	}
}
