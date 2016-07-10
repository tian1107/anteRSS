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
}