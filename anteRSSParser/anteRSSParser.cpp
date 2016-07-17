#include "stdafx.h"

#include "anteRSSParser.h"

#include <ctime>
#include <sstream>
#include <iomanip>

namespace anteRSSParser
{
	const RSSItem invalidItem = RSSItem(RSSFormat::INVALID, 0);

	RSSItem::RSSItem(RSSFormat format, tinyxml2::XMLElement * element)
	{
		this->format = format;
		this->asXML = element;
	}

	std::string RSSItem::getTitle()
	{
		if (format == RSSFormat::INVALID)
			return "invalid";

		if (format == RSSFormat::RSS2)
		{
			tinyxml2::XMLElement * title;
			if (title = asXML->FirstChildElement("title"))
				return title->GetText();
			else
				return "no title";
		}

		return std::string();
	}

	std::string RSSItem::getUniqueId()
	{
		if (format == RSSFormat::INVALID)
			return "invalid";

		if (format == RSSFormat::RSS2)
		{
			tinyxml2::XMLElement * guid;
			if (guid = asXML->FirstChildElement("guid"))
				return guid->GetText();
			else
				// TODO generate a deterministic guid
				return "no guid";
		}

		return std::string();
	}

	std::string RSSItem::getDescription()
	{
		if (format == RSSFormat::INVALID)
			return "invalid";

		if (format == RSSFormat::RSS2)
		{
			tinyxml2::XMLElement * desc;
			if (desc = asXML->FirstChildElement("description"))
				return desc->GetText();
			else
				return "no description";
		}

		return std::string();
	}

	std::string RSSItem::getDate()
	{
		if (format == RSSFormat::INVALID)
			return "invalid";

		if (format == RSSFormat::RSS2)
		{
			tinyxml2::XMLElement * desc;
			if (desc = asXML->FirstChildElement("pubDate"))
			{
				char month[4];
				int day;
				int year;
				int hour;
				int minute;
				int second;
				int monthn = 0;

				// I don't care about timezones, since this is only for sorting
				sscanf_s(desc->GetText(), "%*3s, %d %3s %d %d:%d:%d", &day, month, (unsigned)_countof(month), &year, &hour, &minute, &second);
				
				// strange years
				if (year <= 2000)
					return getCurrentTime();

				//Determine month
				const char ref[][4] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
				for (int i = 0; i <= 12; ++i)
				{
					if (!strcmp(month, ref[i]))
					{
						monthn = i;
						break;
					}
				}

				// strftime might have been better
				std::stringstream str;
				str << year << "/"
					<< std::setfill('0') << std::setw(2) << monthn << "/"
					<< std::setfill('0') << std::setw(2) << day << " "
					<< std::setfill('0') << std::setw(2) << hour << ":"
					<< std::setfill('0') << std::setw(2) << minute << ":"
					<< std::setfill('0') << std::setw(2) << second;

				return str.str();
			}
			else
			{
				return getCurrentTime();
			}
		}

		return std::string();
	}

	std::string RSSItem::getActualDate()
	{
		if (format == RSSFormat::INVALID)
			return "invalid";

		if (format == RSSFormat::RSS2)
		{
			tinyxml2::XMLElement * desc;
			if (desc = asXML->FirstChildElement("pubDate"))
				return desc->GetText();
			else
				return "no date";
		}

		return std::string();
	}

	RSSItem RSSItem::getNext()
	{
		if (format == RSSFormat::RSS2)
		{
			tinyxml2::XMLElement * nextItem;
			if (nextItem = asXML->NextSiblingElement("item"))
				return RSSItem(format, nextItem);
			else
				return invalidItem;
		}
		else
			return invalidItem;
	}

	bool RSSItem::isInvalid()
	{
		return (format == RSSFormat::INVALID);
	}

	// resolves the format of the xml document, returns true if it is a workable rss
	bool RSSDocument::determineFormat()
	{
		if (format != RSSFormat::UNKNOWN)
			return (format != RSSFormat::INVALID);

		// TODO populate this

		// RSS format
		tinyxml2::XMLElement * nodeCheck = nullptr;
		if (nodeCheck = FirstChildElement("rss"))
		{
			if (nodeCheck->Attribute("version", "2.0"))
			{
				// TODO more input checks
				format = RSSFormat::RSS2;
			}
			else
			{
				format = RSSFormat::INVALID;
			}
		}
		else
		{
			format = RSSFormat::INVALID;
		}

		return (format != RSSFormat::INVALID);
	}

	RSSDocument::RSSDocument(bool processEntities, tinyxml2::Whitespace ws) : XMLDocument(processEntities, ws)
	{
		format = RSSFormat::UNKNOWN;
	}

	std::string RSSDocument::getTitle()
	{
		if (!determineFormat())
			return "RSS Document invalid or empty.";

		if (format == RSSFormat::RSS2)
		{
			return FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("title")->GetText();
		}
		else
		{
			return "";
		}

		return std::string();
	}

	RSSItem RSSDocument::getFirstItem()
	{
		if (!determineFormat())
			return invalidItem;

		if (format == RSSFormat::RSS2)
		{
			tinyxml2::XMLElement * firstItem;
			if (firstItem = FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item"))
				return RSSItem(format, firstItem);
			else
				return invalidItem;
		}
		else
		{
			return invalidItem;
		}

		return invalidItem;
	}

	void RSSDocument::reset(bool makeEmpty)
	{
		if (makeEmpty)
			Clear();

		format = RSSFormat::UNKNOWN;
	}

	std::wstring convertToWide(const std::string& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.from_bytes(str);
	}

	std::string convertToUtf8(const std::wstring & wstr)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(wstr);
	}

	std::string getCurrentTime()
	{
		std::time_t tt = std::time(NULL);
		std::tm time;
		_gmtime64_s(&time, &tt);

		// strftime might have been better
		std::stringstream str;
		str << (time.tm_year + 1900) << "/"
			<< std::setfill('0') << std::setw(2) << (time.tm_mon + 1) << "/"
			<< std::setfill('0') << std::setw(2) << time.tm_mday << " "
			<< std::setfill('0') << std::setw(2) << time.tm_hour << ":"
			<< std::setfill('0') << std::setw(2) << time.tm_min << ":"
			<< std::setfill('0') << std::setw(2) << time.tm_sec;

		return str.str();
	}

	void simpleSQL(sqlite3 * db, std::string query)
	{
		sqlite3_stmt * statement;
		sqlite3_prepare_v2(db, query.c_str(), query.length() + 1, &statement, NULL);
		sqlite3_step(statement);
		sqlite3_finalize(statement);
	}

	size_t downloadTextFile_cb(void *buffer, size_t size, size_t nmemb, void * data)
	{
		std::stringstream & str = *((std::stringstream *) data);
		char * buf = (char *)buffer;

		str.write(buf, size * nmemb);

		return size * nmemb;
	}

	std::string downloadTextFile(std::string url)
	{
		// the result
		std::stringstream str;

		// TODO shared curl stuff
		CURL * curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadTextFile_cb);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);

		// TODO error check!
		curl_easy_perform(curl);

		curl_easy_cleanup(curl);
		return str.str();
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
		feedStr = "update FeedInfo set name=?1 where id=?2";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &renameFeedStmt, NULL);
		feedStr = "select id, name, url from FeedInfo where id=?1;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &getFeedStmt, NULL);
		feedStr = "select id, name, url from FeedInfo where url=?1;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &getFeedFromUrlStmt, NULL);
		feedStr = "select id, name, url from FeedInfo order by name collate nocase;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &getAllFeedsStmt, NULL);
		feedStr = "delete from FeedInfo where id=?1;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &removeFeedStmt, NULL);
		feedStr = "insert into FeedItems (guid, title, description, feedid, date, actualdate) values (?1, ?2, ?3, ?4, ?5, ?6);";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &updateFeedStmt, NULL);
	}

	RSSManager::~RSSManager()
	{
		sqlite3_finalize(addFeedStmt);
		sqlite3_finalize(renameFeedStmt);
		sqlite3_finalize(getFeedStmt);
		sqlite3_finalize(getFeedFromUrlStmt);
		sqlite3_finalize(getAllFeedsStmt);
		sqlite3_finalize(removeFeedStmt);
		sqlite3_finalize(updateFeedStmt);
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
			result.push_back(feed);
			rc = sqlite3_step(getAllFeedsStmt);
		}

		sqlite3_reset(getAllFeedsStmt);

		return result;
	}

	void RSSManager::removeFeed(int feedId)
	{
		sqlite3_clear_bindings(removeFeedStmt);
		sqlite3_bind_int(removeFeedStmt, 1, feedId);
		int rc = sqlite3_step(removeFeedStmt);
		sqlite3_reset(removeFeedStmt);
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
		

		RSSItem item = doc.getFirstItem();
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

		if (callback)
		{
			callback(feedId, true, result, data);
		}
	}

	DownloadManager::DownloadManager()
	{
		share = curl_share_init();
		curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);
		curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
		curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_SSL_SESSION);
	}

	DownloadManager::~DownloadManager()
	{
		curl_share_cleanup(share);
	}

	size_t downloadSingle_cb(void *buffer, size_t size, size_t nmemb, void * data)
	{
		std::vector<char> & str = *((std::vector<char> *) data);
		char * buf = (char *)buffer;
		size_t start = str.size();

		// resize
		str.resize(str.size() + size * nmemb);

		// copy
		for (size_t i = start; i < str.size(); ++i)
		{
			str[i] = buf[i - start];
		}

		return size * nmemb;
	}

	// downloads a single file, no null terminator at the end
	std::vector<char> DownloadManager::downloadSingle(std::string url)
	{
		lock.lock();

		// the result
		std::vector<char> str;

		// TODO shared curl stuff
		CURL * curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_SHARE, share);

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadSingle_cb);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);

		// TODO error check!
		curl_easy_perform(curl);

		curl_easy_cleanup(curl);

		lock.unlock();

		return str;
	}
}