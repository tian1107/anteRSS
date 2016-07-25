#include "stdafx.h"

#include "Util.h"

#include <sstream>
#include <iomanip>

namespace anteRSSParser
{

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

}