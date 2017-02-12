#pragma once

#include <tinyxml2\tinyxml2.h>

namespace anteRSSParser
{
	// Converts utf8 strings to wstring
	std::wstring convertToWide(const std::string& str);
	std::string convertToUtf8(const std::wstring& wstr);

	// formatted current time
	std::string getCurrentTime();

	// a query where nothing is returned, and nothing is inputted
	int simpleSQL(sqlite3 * db, std::string query);

	// prints contents of a node as a string
	std::string getSubText(tinyxml2::XMLElement * element);
}