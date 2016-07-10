#pragma once
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
		bool hasNext();
		RSSItem getNext();
		bool isInvalid();
	};

	extern const RSSItem invalidItem;

	class RSSDocument : public tinyxml2::XMLDocument 
	{
	private:
		RSSFormat format;
		bool determineFormat();
	public:
		RSSDocument(bool processEntities = true, tinyxml2::Whitespace ws = tinyxml2::PRESERVE_WHITESPACE);
		std::string getTitle();
		RSSItem getFirstItem();
		void reset(bool makeEmpty);
	};

	// Converts utf8 strings to wstring
	std::wstring convertToWide(const std::string& str);
}