#pragma once
#include <mutex>
#include <vector>
#include <map>
#include <string>
#include <sqlite3.h>

#include "tinyxml2\tinyxml2.h"

#include "RSSDocument.h"
#include "DownloadManager.h"
#include "Util.h"

namespace anteRSSParser
{

	struct RSSFeedItem
	{
		std::string guid;
		std::string title;
		std::string description;
		int feedid;
		std::string date;
		int status;
	};
	typedef std::vector<RSSFeedItem> RSSFeedItemVector;

	struct RSSFeed
	{
		int id;
		std::string name;
		std::string url;
		int unread;
	};
	typedef std::vector<RSSFeed> RSSFeedVector;

	// gets called when a feed is updated, would be in a different thread
	typedef void(*RSSManagerCallback)(int feedid, bool success, RSSFeedItemVector newItem, void * data);

	class RSSManager
	{
		friend void updateAllCallbackSingle(std::string url, std::vector<char> content, void * data);
	private:
		DownloadManager manager;
		sqlite3* db;
		sqlite3_stmt * addFeedStmt;
		sqlite3_stmt * renameFeedStmt;
		sqlite3_stmt * getFeedStmt;
		sqlite3_stmt * getFeedFromUrlStmt;
		sqlite3_stmt * getAllFeedsStmt;
		sqlite3_stmt * getItemsofFeedStmt;
		sqlite3_stmt * getItemsofStatusStmt;
		sqlite3_stmt * removeFeedStmt;
		sqlite3_stmt * removeFeedItemStmt;
		sqlite3_stmt * updateFeedStmt;
		sqlite3_stmt * markItemStmt;
		sqlite3_stmt * markAllReadStmt;

		RSSFeedItemVector updateFeedFromDoc(RSSDocument * doc, int feedId);
	public:
		RSSManager(std::string dbFile);
		~RSSManager();
		void addFeed(RSSFeed feed);
		void addFeed(std::string url);
		void renameFeed(int feedId, std::string name);
		RSSFeed getFeed(int feedId);
		RSSFeed getFeedFromUrl(std::string url);
		RSSFeedVector getAllFeeds();
		RSSFeedItemVector getItemsOfFeed(int feedId);
		RSSFeedItemVector getItemsOfStatus(int status);
		void removeFeed(int feedId);
		void updateFeed(int feedId, RSSManagerCallback callback, void * data);
		void updateAll(RSSManagerCallback callback, void * data);
		void markStatus(std::string guid, int status);
		void markAllAsRead();
		std::string getLastError();
	};
}