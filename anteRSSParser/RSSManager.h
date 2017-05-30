#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>

#include "RSSDocument.h"

namespace anteRSSParser
{
	class DownloadManager;

	struct RSSFeedItem
	{
		std::string guid;
		std::string title;
		std::string description;
		int feedid;
		std::string date;
		int status;
		std::string link;
		std::string contentEncoded;
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
	typedef void(*RSSManagerCallback)(int feedid, bool success, RSSFeedItemVector newItem, void * data, std::string errorMessage);

	class RSSManager
	{
		friend void updateAllCallbackSingle(std::string url, std::vector<char> content, void * data, bool success);
	private:
		DownloadManager * manager;
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
		sqlite3_stmt * markAllFeedReadStmt;
		sqlite3_stmt * getProgramInfoStmt;
		sqlite3_stmt * setProgramInfoStmt;

		RSSFeedItemVector updateFeedFromDoc(RSSDocument * doc, int feedId);
		RSSFeedItem getFeedItemFromStatement(sqlite3_stmt * stmt);
		void updateDatabaseFormat();
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
		void markAllAsRead(int feedid);
		std::string getProgramInfo(std::string infoname, std::string defaultValue);
		void setProgramInfo(std::string infoname, std::string value);
		std::string getLastError();
	};
}