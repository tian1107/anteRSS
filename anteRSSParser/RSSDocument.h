#pragma once

#include "tinyxml2\tinyxml2.h"
#include <string>

namespace anteRSSParser
{
	enum RSSFormat
	{
		INVALID = -1,
		UNKNOWN = 0,
		RSS2 = 1,
		ATOM1 = 2,
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
		std::string getLink();
		std::string getContentEncoded();
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
		bool determineFormat();
	public:
		RSSDocument(bool processEntities = true, tinyxml2::Whitespace ws = tinyxml2::PRESERVE_WHITESPACE);
		std::string getTitle();
		RSSItem getFirstItem();
		void reset(bool makeEmpty);
	};
}