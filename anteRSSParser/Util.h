#pragma once

namespace anteRSSParser
{
	// Converts utf8 strings to wstring
	std::wstring convertToWide(const std::string& str);
	std::string convertToUtf8(const std::wstring& wstr);

	// formatted current time
	std::string getCurrentTime();

	// a query where nothing is returned, and nothing is inputted
	void simpleSQL(sqlite3 * db, std::string query);
}