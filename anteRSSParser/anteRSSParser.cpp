#include "stdafx.h"

#include "anteRSSParser.h"

#include <ctime>
#include <sstream>
#include <iomanip>

namespace anteRSSParser
{

	RSSFeedItemVector RSSManager::updateFeedFromDoc(RSSDocument * doc, int feedId)
	{
		RSSFeedItemVector result;

		simpleSQL(db, "begin transaction;");

		RSSItem item = doc->getFirstItem();
		while (!item.isInvalid())
		{
			sqlite3_clear_bindings(updateFeedStmt);
			sqlite3_bind_text(updateFeedStmt, 1, item.getUniqueId().c_str(), -1, SQLITE_TRANSIENT);
			sqlite3_bind_text(updateFeedStmt, 2, item.getTitle().c_str(), -1, SQLITE_TRANSIENT);
			sqlite3_bind_text(updateFeedStmt, 3, item.getDescription().c_str(), -1, SQLITE_TRANSIENT);
			sqlite3_bind_int(updateFeedStmt, 4, feedId);
			sqlite3_bind_text(updateFeedStmt, 5, item.getDate().c_str(), -1, SQLITE_TRANSIENT);
			sqlite3_bind_text(updateFeedStmt, 6, item.getActualDate().c_str(), -1, SQLITE_TRANSIENT);
			int rc = sqlite3_step(updateFeedStmt);

			// new thing!
			if (rc == SQLITE_DONE)
			{
				RSSFeedItem feedItem;
				feedItem.date = item.getDate();
				feedItem.description = item.getDescription();
				feedItem.feedid = feedId;
				feedItem.guid = item.getUniqueId();
				feedItem.status = 0;
				feedItem.title = item.getTitle();
				result.push_back(feedItem);
			}

			sqlite3_reset(updateFeedStmt);

			item = item.getNext();
		}

		simpleSQL(db, "commit;");

		return result;
	}

	RSSManager::RSSManager(std::string dbFile)
	{
		int rc = sqlite3_open(dbFile.c_str(), &db);

		// TODO error checking here
		if (rc) {
			//OutputDebugString((std::wstring(L"Can't open database") + anteRSSParser::convertToWide(sqlite3_errmsg(db)) + L"\n").c_str());
			return;
		}
		else {
			//OutputDebugString(L"Opened it success!\n");
		}

		// create tables if not already there
		simpleSQL(db, 
			"CREATE TABLE IF NOT EXISTS \"FeedItems\" (\n\t`guid`\tTEXT NOT NULL UNIQUE,\n\t`title`\tTEXT NOT NULL,\n\t`description`\tTEXT NOT NULL,\n\t`feedid`\tINTEGER NOT NULL,\n\t`date`\tTEXT NOT NULL,\n\t`actualdate`\tTEXT,\n\t`status`\tINTEGER NOT NULL DEFAULT 0,\n\tPRIMARY KEY(guid)\n);");

		simpleSQL(db, 
			"CREATE TABLE IF NOT EXISTS \"FeedInfo\" (\n\t`id`\tINTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\n\t`name`\tTEXT NOT NULL,\n\t`url`\tTEXT NOT NULL UNIQUE\n)");

		std::string feedStr = "insert into FeedInfo (name, url) values (?1, ?2);";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &addFeedStmt, NULL);
		feedStr = "update FeedInfo set name=?1 where id=?2;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &renameFeedStmt, NULL);
		feedStr = "select feed.id, feed.name, feed.url, count(case when item.status = 0 then 1 else null end) as \"unread\" from FeedInfo feed left join FeedItems item on feed.id = item.feedid where feed.id = ?1;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &getFeedStmt, NULL);
		feedStr = "select feed.id, feed.name, feed.url, count(case when item.status = 0 then 1 else null end) as \"unread\" from FeedInfo feed left join FeedItems item on feed.id = item.feedid where url=?1;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &getFeedFromUrlStmt, NULL);
		feedStr = "select feed.id, feed.name, feed.url, count(case when item.status = 0 then 1 else null end) as \"unread\" from FeedInfo feed left join FeedItems item on feed.id = item.feedid group by feed.id order by name collate nocase;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &getAllFeedsStmt, NULL);
		feedStr = "select guid, title, description, feedid, status, date from FeedItems where feedid=?1 order by date desc;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &getItemsofFeedStmt, NULL);
		feedStr = "select guid, title, description, feedid, status, date from FeedItems where status=?1 order by date desc;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &getItemsofStatusStmt, NULL);
		feedStr = "delete from FeedInfo where id=?1;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &removeFeedStmt, NULL);
		feedStr = "delete from FeedItems where feedid=?1;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &removeFeedItemStmt, NULL);
		feedStr = "insert into FeedItems (guid, title, description, feedid, date, actualdate) values (?1, ?2, ?3, ?4, ?5, ?6);";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &updateFeedStmt, NULL);
		feedStr = "update FeedItems set status=?1 where guid=?2;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &markItemStmt, NULL);
		feedStr = "update FeedItems set status=1 where status=0;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &markAllReadStmt, NULL);
	}

	RSSManager::~RSSManager()
	{
		sqlite3_finalize(addFeedStmt);
		sqlite3_finalize(renameFeedStmt);
		sqlite3_finalize(getFeedStmt);
		sqlite3_finalize(getFeedFromUrlStmt);
		sqlite3_finalize(getAllFeedsStmt);
		sqlite3_finalize(getItemsofFeedStmt);
		sqlite3_finalize(getItemsofStatusStmt);
		sqlite3_finalize(removeFeedStmt);
		sqlite3_finalize(removeFeedItemStmt);
		sqlite3_finalize(updateFeedStmt);
		sqlite3_finalize(markItemStmt);
		sqlite3_close(db);
	}

	void RSSManager::addFeed(RSSFeed feed)
	{
		sqlite3_clear_bindings(addFeedStmt);
		sqlite3_bind_text(addFeedStmt, 1, feed.name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(addFeedStmt, 2, feed.url.c_str(), -1, SQLITE_STATIC);
		int rc = sqlite3_step(addFeedStmt);
		sqlite3_reset(addFeedStmt);
	}

	void RSSManager::addFeed(std::string url)
	{
		// TODO error check

		RSSFeed feed;
		feed.url = url;
		
		RSSDocument doc;
		std::vector<char> & file = manager.downloadSingle(feed.url);
		doc.Parse(file.data(), file.size());

		feed.name = doc.getTitle();

		addFeed(feed);

		// might as well update the thing

		// get new id
		feed = getFeedFromUrl(feed.url);

		updateFeedFromDoc(&doc, feed.id);
	}

	void RSSManager::renameFeed(int feedId, std::string name)
	{
		sqlite3_clear_bindings(renameFeedStmt);
		sqlite3_bind_text(renameFeedStmt, 1, name.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(renameFeedStmt, 2, feedId);
		int rc = sqlite3_step(renameFeedStmt);
		sqlite3_reset(renameFeedStmt);
	}

	RSSFeed RSSManager::getFeed(int feedId)
	{
		RSSFeed result = RSSFeed();
		sqlite3_clear_bindings(getFeedStmt);
		sqlite3_bind_int(getFeedStmt, 1, feedId);
		int rc = sqlite3_step(getFeedStmt);

		if (rc == SQLITE_ROW)
		{
			result.id = sqlite3_column_int(getFeedStmt, 0);
			result.name = (const char *)sqlite3_column_text(getFeedStmt, 1);
			result.url = (const char *)sqlite3_column_text(getFeedStmt, 2);
			result.unread = sqlite3_column_int(getFeedStmt, 3);
		}

		sqlite3_reset(getFeedStmt);

		return result;
	}

	RSSFeed RSSManager::getFeedFromUrl(std::string url)
	{
		RSSFeed result = RSSFeed();
		sqlite3_clear_bindings(getFeedFromUrlStmt);
		sqlite3_bind_text(getFeedFromUrlStmt, 1, url.c_str(), -1, SQLITE_STATIC);
		int rc = sqlite3_step(getFeedFromUrlStmt);

		if (rc == SQLITE_ROW)
		{
			result.id = sqlite3_column_int(getFeedFromUrlStmt, 0);
			result.name = (const char *)sqlite3_column_text(getFeedFromUrlStmt, 1);
			result.url = (const char *)sqlite3_column_text(getFeedFromUrlStmt, 2);
			result.unread = sqlite3_column_int(getFeedFromUrlStmt, 3);
		}

		sqlite3_reset(getFeedFromUrlStmt);

		return result;
	}

	RSSFeedVector RSSManager::getAllFeeds()
	{
		std::vector<RSSFeed> result;

		int rc = sqlite3_step(getAllFeedsStmt);
		while (rc == SQLITE_ROW)
		{
			RSSFeed feed;
			feed.id = sqlite3_column_int(getAllFeedsStmt, 0);
			feed.name = (const char *) sqlite3_column_text(getAllFeedsStmt, 1);
			feed.url = (const char *) sqlite3_column_text(getAllFeedsStmt, 2);
			feed.unread = sqlite3_column_int(getAllFeedsStmt, 3);
			result.push_back(feed);
			rc = sqlite3_step(getAllFeedsStmt);
		}

		sqlite3_reset(getAllFeedsStmt);

		return result;
	}

	RSSFeedItemVector RSSManager::getItemsOfFeed(int feedId)
	{
		RSSFeedItemVector result;

		sqlite3_clear_bindings(getItemsofFeedStmt);
		sqlite3_bind_int(getItemsofFeedStmt, 1, feedId);
		int rc = sqlite3_step(getItemsofFeedStmt);

		while (rc == SQLITE_ROW)
		{
			RSSFeedItem item;

			// guid, title, description, feedid, status, date

			item.guid = (const char *)sqlite3_column_text(getItemsofFeedStmt, 0);
			item.title = (const char *)sqlite3_column_text(getItemsofFeedStmt, 1);
			item.description = (const char *)sqlite3_column_text(getItemsofFeedStmt, 2);
			item.feedid = sqlite3_column_int(getItemsofFeedStmt, 3);
			item.status = sqlite3_column_int(getItemsofFeedStmt, 4);
			item.date = (const char *)sqlite3_column_text(getItemsofFeedStmt, 5);
			
			result.push_back(item);
			rc = sqlite3_step(getItemsofFeedStmt);
		}

		sqlite3_reset(getItemsofFeedStmt);

		return result;
	}

	RSSFeedItemVector RSSManager::getItemsOfStatus(int status)
	{
		RSSFeedItemVector result;

		sqlite3_clear_bindings(getItemsofStatusStmt);
		sqlite3_bind_int(getItemsofStatusStmt, 1, status);
		int rc = sqlite3_step(getItemsofStatusStmt);

		while (rc == SQLITE_ROW)
		{
			RSSFeedItem item;

			// guid, title, description, feedid, status, date

			item.guid = (const char *)sqlite3_column_text(getItemsofStatusStmt, 0);
			item.title = (const char *)sqlite3_column_text(getItemsofStatusStmt, 1);
			item.description = (const char *)sqlite3_column_text(getItemsofStatusStmt, 2);
			item.feedid = sqlite3_column_int(getItemsofStatusStmt, 3);
			item.status = sqlite3_column_int(getItemsofStatusStmt, 4);
			item.date = (const char *)sqlite3_column_text(getItemsofStatusStmt, 5);

			result.push_back(item);
			rc = sqlite3_step(getItemsofStatusStmt);
		}

		sqlite3_reset(getItemsofStatusStmt);

		return result;
	}

	void RSSManager::removeFeed(int feedId)
	{
		sqlite3_clear_bindings(removeFeedStmt);
		sqlite3_bind_int(removeFeedStmt, 1, feedId);
		int rc = sqlite3_step(removeFeedStmt);
		sqlite3_reset(removeFeedStmt);

		sqlite3_clear_bindings(removeFeedItemStmt);
		sqlite3_bind_int(removeFeedItemStmt, 1, feedId);
		rc = sqlite3_step(removeFeedItemStmt);
		sqlite3_reset(removeFeedItemStmt);
	}

	void RSSManager::updateFeed(int feedId, RSSManagerCallback callback, void * data)
	{
		RSSFeedItemVector result;

		RSSDocument doc;

		RSSFeed & feed = getFeed(feedId);
		if (feed.url.empty())
		{
			if (callback)
				callback(feedId, false, result, data);
			return;
		}

		// for debugging things
#ifdef _DEBUG
		//
		if (feed.url.at(0) == 0x7f)
		{
			doc.LoadFile(feed.url.substr(1, std::string::npos).c_str());
		}
		else
#endif
		{
			std::vector<char> & file = manager.downloadSingle(feed.url);
			doc.Parse(file.data(), file.size());
		}
		
		result = updateFeedFromDoc(&doc, feedId);

		if (callback)
		{
			callback(feedId, true, result, data);
		}
	}

	void updateAllCallbackSingle(std::string url, std::vector<char> content, void * data)
	{
		void ** buf = (void **) data;
		RSSManager * control = (RSSManager *) buf[0];
		RSSManagerCallback callback = (RSSManagerCallback) buf[1];
		void * cData = buf[2];

		RSSFeed feed = control->getFeedFromUrl(url);
		RSSDocument doc;
		doc.Parse(content.data(), content.size());

		RSSFeedItemVector result = control->updateFeedFromDoc(&doc, feed.id);
		if (callback)
			callback(feed.id, true, result, cData);

	}

	void RSSManager::updateAll(RSSManagerCallback callback, void * data)
	{
		RSSFeedVector feeds = getAllFeeds();

		std::vector<std::string> urls;
		for (RSSFeedVector::iterator it = feeds.begin(); it != feeds.end(); ++it)
		{
			// take note that there will be no debug stuff
			urls.push_back(it->url);
		}

		void * buf[3] = { this, callback, data };

		manager.downloadMultiple(urls, updateAllCallbackSingle, buf);

		// mark the end
		if (callback)
		{
			callback(0, true, RSSFeedItemVector(), data);
		}
	}

	void RSSManager::markStatus(std::string guid, int status)
	{
		sqlite3_clear_bindings(markItemStmt);
		sqlite3_bind_int(markItemStmt, 1, status);
		sqlite3_bind_text(markItemStmt, 2, guid.c_str(), -1, SQLITE_STATIC);
		int rc = sqlite3_step(markItemStmt);
		sqlite3_reset(markItemStmt);
	}

	void RSSManager::markAllAsRead()
	{
		sqlite3_step(markAllReadStmt);
		sqlite3_reset(markAllReadStmt);
	}

}