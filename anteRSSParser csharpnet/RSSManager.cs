using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using System.Data.SQLite;

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
		private readonly String readOnlyConnection;
		private readonly String writeConnection;

		public RSSManager(String filename)
		{
			// Generate connection strings
			writeConnection = "Data Source=\"" + filename + "\";Version=3;UTF8Encoding=True;";
			readOnlyConnection = writeConnection + "Read Only=True;";

			UpdateDatabaseFormat();
		}

		protected String GetConnectionString(Boolean readOnly = true)
		{
			if (readOnly)
			{
				return readOnlyConnection;
			}
			else
			{
				return writeConnection;
			}
		}

		protected void UpdateDatabaseFormat()
		{
			using (SQLiteConnection conn = new SQLiteConnection(GetConnectionString(false)))
			{
				conn.Open();

				// create tables if not already there
				SQLiteCommand createFeedInfo = new SQLiteCommand(
					"CREATE TABLE IF NOT EXISTS \"FeedInfo\" (\n\t`id`\tINTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\n\t`name`\tTEXT NOT NULL,\n\t`url`\tTEXT NOT NULL UNIQUE\n)",
					conn);
				createFeedInfo.ExecuteNonQuery();

				SQLiteCommand createProgramInfo = new SQLiteCommand(
					"CREATE TABLE IF NOT EXISTS `ProgramInfo` (\n\t`infoname`\tTEXT NOT NULL UNIQUE,\n\t`value`\tTEXT,\n\tPRIMARY KEY(infoname)\n);",
					conn);
				createProgramInfo.ExecuteNonQuery();

				try
				{
					SQLiteCommand createFeedItems = new SQLiteCommand(
						"CREATE TABLE \"FeedItems\" (\n\t`guid`\tTEXT NOT NULL UNIQUE,\n\t`title`\tTEXT NOT NULL,\n\t`description`\tTEXT NOT NULL,\n\t`feedid`\tINTEGER NOT NULL,\n\t`date`\tTEXT NOT NULL,\n\t`actualdate`\tTEXT,\n\t`status`\tINTEGER NOT NULL DEFAULT 0,\n\t`link`\tTEXT,\n\t`contentencoded`\tTEXT,\n\tPRIMARY KEY(guid)\n);",
						conn);
					createFeedItems.ExecuteNonQuery();
				}
				catch (SQLiteException ex)
				{
					// FeedItems table already exists
					if (ex.ResultCode == SQLiteErrorCode.Error)
					{
						// Get program info statement
						SQLiteCommand getVersion = new SQLiteCommand(
							"select value from ProgramInfo where infoname=@name;", conn);

						// Get version
						getVersion.Parameters.AddWithValue("@name", "version");
						String version = (String)getVersion.ExecuteScalar();

						if (version == null)    // version 0, before content encoded and ProgramInfo
						{
							new SQLiteCommand(
								"alter table FeedItems add column `contentencoded` TEXT; ", conn)
								.ExecuteNonQuery();
						}
					}
				}

				// Set to the current version
				SQLiteCommand updateInfo = new SQLiteCommand(
					"insert or replace into ProgramInfo (infoname, value) values (@name, @value);", conn);

				updateInfo.Parameters.AddWithValue("@name", "version");
				updateInfo.Parameters.AddWithValue("@value", "0.1");

				updateInfo.ExecuteNonQuery();

				conn.Close();
			}
		}

		public Int32 AddFeed(String name, String url)
		{
			Int32 id = -1;

			using (SQLiteConnection conn = new SQLiteConnection(GetConnectionString(false))) 
			{
				conn.Open();

				SQLiteCommand command = new SQLiteCommand("insert into FeedInfo (name, url) values (@name, @url); select last_insert_rowid();", 
					conn);
				command.Parameters.AddWithValue("@name", name);
				command.Parameters.AddWithValue("@url", url);

				try
				{
					object temp = command.ExecuteScalar();
					if (temp != null)
						id = Convert.ToInt32(temp);
				}
				catch (SQLiteException ex)
				{
					// If something happens
					if (ex.ResultCode != SQLiteErrorCode.Done)
					{
						id = -1;
					}
				}
				finally
				{
					command.Dispose();
				}

				conn.Close();
			}

			// Returns the feed id
			return id;
		}

		public Int32 AddFeed(String url)
		{
			// Returns the feed id
			throw new NotImplementedException();
		}

		public RSSFeed GetFeed(Int32 id)
		{
			/*SQLiteCommand getFeed = new SQLiteCommand(
				"select feed.id, feed.name, feed.url, count(case when item.status = 0 then 1 else null end) as \"unread\" from FeedInfo feed left join FeedItems item on feed.id = item.feedid where feed.id = @id;",
				readDb);*/
			throw new NotImplementedException();
		}

		public void RenameFeed(Int32 feedId, String name)
		{
			throw new NotImplementedException();

		}

		RSSFeed [] GetAllFeeds()
		{
			throw new NotImplementedException();

		}

		RSSFeed [] GetItemsofFeed(Int32 feedId)
		{
			throw new NotImplementedException();

		}

		RSSFeed [] GetItemsofStatus(RSSFeedItemStatus status)
		{
			throw new NotImplementedException();

		}

		void RemoveFeed(Int32 feedId)
		{
			throw new NotImplementedException();

		}

		void UpdateFeed(Int32 feedId, OnFeedUpdateCallback callback)
		{
			throw new NotImplementedException();

		}

		void UpdateAllFeeds(OnFeedUpdateCallback callback)
		{
			throw new NotImplementedException();

		}

		void ChangeFeedItemStatus(String guid, RSSFeedItemStatus status)
		{
			throw new NotImplementedException();

		}

		void MarkAllAsRead(Int32 feedId)
		{
			throw new NotImplementedException();

		}
	}
}
