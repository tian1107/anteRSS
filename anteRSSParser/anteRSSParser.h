#pragma once
#include <mutex>
#include <vector>
#include <map>
#include <string>
#include <sqlite3.h>

#include "tinyxml2\tinyxml2.h"

namespace anteRSSParser
{

	enum RSSFormat
	{
		INVALID	= -1,
		UNKNOWN	= 0,
		RSS2	= 1,
		ATOM1	= 2,
	};

	class RSSItem
	{
	private:
		RSSFormat format;
		tinyxml2::XMLElement * asXML;
	public:
		RSSItem(RSSFormat format, tinyxml2::XMLElement * element);
		std::string getTitle();
		std::string getUniqueId();
		std::string getDescription();
		std::string getDate();
		std::string getActualDate();
		RSSItem getNext();
		bool isInvalid();
	};

	class RSSDocument : public tinyxml2::XMLDocument 
	{
		friend class RSSManager;
	private:
		RSSFormat format;
		bool cached;
		std::map<std::string, RSSItem> itemCache;
		bool determineFormat();
	public:
		RSSDocument(bool processEntities = true, tinyxml2::Whitespace ws = tinyxml2::PRESERVE_WHITESPACE);
		std::string getTitle();
		RSSItem getFirstItem();
		void reset(bool makeEmpty);
	};

	struct RSSFeedItem
	{
		std::string guid;
		std::string title;
		std::string description;
		std::string feedid;
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

	typedef void(*DownloadManagerCallback)(std::string url, std::vector<char> content, void * data);

	class DownloadManager
	{
	private:
		CURLSH * share;
		std::mutex lock;
	public:
		DownloadManager();
		~DownloadManager();
		std::vector<char> downloadSingle(std::string url);
		void downloadMultiple(std::vector<std::string> urls, DownloadManagerCallback callback, void * data);
	};

	class RSSManager
	{
	private:
		DownloadManager manager;
		sqlite3* db;
		sqlite3_stmt * addFeedStmt;
		sqlite3_stmt * renameFeedStmt;
		sqlite3_stmt * getFeedStmt;
		sqlite3_stmt * getFeedFromUrlStmt;
		sqlite3_stmt * getAllFeedsStmt;
		sqlite3_stmt * removeFeedStmt;
		sqlite3_stmt * updateFeedStmt;
	public:
		RSSManager(std::string dbFile);
		~RSSManager();
		void addFeed(RSSFeed feed);
		void renameFeed(int feedId, std::string name);
		RSSFeed getFeed(int feedId);
		RSSFeed getFeedFromUrl(std::string url);
		RSSFeedVector getAllFeeds();
		void removeFeed(int feedId);
		void updateFeed(int feedId, RSSManagerCallback callback, void * data);
		void updateAll(RSSManagerCallback callback, void * data);
		void markAsRead(std::string guid, bool read);
		void markAsArchive(std::string guid, bool archive);
		std::string getLastError();
	};

	// Converts utf8 strings to wstring
	std::wstring convertToWide(const std::string& str);
	std::string convertToUtf8(const std::wstring& wstr);

	// formatted current time
	std::string getCurrentTime();

	// a query where nothing is returned, and nothing is inputted
	void simpleSQL(sqlite3 * db, std::string query);

	// just download a thing
	std::string downloadTextFile(std::string url);
}