#include "stdafx.h"

#include "anteRSSParser.h"

namespace anteRSSParser
{
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