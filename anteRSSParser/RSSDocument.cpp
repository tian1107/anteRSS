#include "stdafx.h"

#include "RSSDocument.h"
#include "Util.h"

#include <iomanip>
#include <sstream>

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

	std::string RSSItem::getLink()
	{
		if (format == RSSFormat::INVALID)
			return "invalid";

		if (format == RSSFormat::RSS2)
		{
			tinyxml2::XMLElement * desc;
			if (desc = asXML->FirstChildElement("link"))
				return desc->GetText();
			else
				return "no link";
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
				const char ref[][4] = { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
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
			tinyxml2::XMLElement * rss = FirstChildElement("rss");
			tinyxml2::XMLElement * channel = rss->FirstChildElement("channel");
			if (channel)
			{
				tinyxml2::XMLElement * title = rss->FirstChildElement("title");
				if (title && title->GetText())
				{
					return title->GetText();
				}
				else
				{
					return "Untitled";
				}
			}
			else
			{
				return "Unchanneled";
			}
			
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
}