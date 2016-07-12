#include "stdafx.h"

#include "anteRSSParser.h"

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
			return asXML->FirstChildElement("title")->GetText();
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
				return desc->GetText();
			else
			{
				// give current time instead
				std::time_t tt = std::time(NULL);
				std::tm time;
				_gmtime64_s(&time, &tt);

				std::stringstream str;
				str << (time.tm_year + 1900) << "/" 
					<< std::setfill('0') << std::setw(2) << (time.tm_mon + 1) << "/" 
					<< std::setfill('0') << std::setw(2) << time.tm_mday << " " 
					<< std::setfill('0') << std::setw(2) << time.tm_hour << ":" 
					<< std::setfill('0') << std::setw(2) << time.tm_min << ":" 
					<< std::setfill('0') << std::setw(2) << time.tm_sec;

				return str.str();
			}
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

		std::string feedStr = "insert into FeedInfo (name, url) values (?1, ?2);";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &addFeedStmt, NULL);
		feedStr = "select id, name, url from FeedInfo where id=?1;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &getFeedStmt, NULL);
		feedStr = "select id, name, url from FeedInfo;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &getAllFeedsStmt, NULL);
		feedStr = "delete from FeedInfo where id=?1;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &removeFeedStmt, NULL);
		feedStr = "insert into FeedItems (guid, title, description, feedid, date) values (?1, ?2, ?3, ?4, ?5);";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &updateFeedStmt, NULL);
	}

	RSSManager::~RSSManager()
	{
		sqlite3_finalize(addFeedStmt);
		sqlite3_finalize(getFeedStmt);
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

	void RSSManager::updateFeed(int feedId, RSSManagerCallback callback)
	{
		RSSDocument doc;

		RSSFeed & feed = getFeed(feedId);
		// TODO replace with curl
		doc.LoadFile(feed.url.c_str());

		RSSItem item = doc.getFirstItem();
		while (!item.isInvalid())
		{
			sqlite3_clear_bindings(updateFeedStmt);
			sqlite3_bind_text(updateFeedStmt, 1, item.getUniqueId().c_str(), -1, SQLITE_TRANSIENT);
			sqlite3_bind_text(updateFeedStmt, 2, item.getTitle().c_str(), -1, SQLITE_TRANSIENT);
			sqlite3_bind_text(updateFeedStmt, 3, item.getDescription().c_str(), -1, SQLITE_TRANSIENT);
			sqlite3_bind_int(updateFeedStmt, 4, feedId);
			sqlite3_bind_text(updateFeedStmt, 5, item.getDate().c_str(), -1, SQLITE_TRANSIENT);
			int rc = sqlite3_step(updateFeedStmt);
			sqlite3_reset(updateFeedStmt);

			item = item.getNext();
		}

		if (callback)
		{
			callback(feedId, true);
		}
	}

}