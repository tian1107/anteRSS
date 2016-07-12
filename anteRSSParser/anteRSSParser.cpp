#include "stdafx.h"

#include "anteRSSParser.h"

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
				return "no guid";
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
		addFeedStmt = nullptr;

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
		feedStr = "select id, name, url from FeedInfo;";
		rc = sqlite3_prepare_v2(db, feedStr.c_str(), feedStr.length() + 1, &getAllFeedsStmt, NULL);
	}

	RSSManager::~RSSManager()
	{
		sqlite3_finalize(addFeedStmt);
		sqlite3_finalize(getAllFeedsStmt);
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

}