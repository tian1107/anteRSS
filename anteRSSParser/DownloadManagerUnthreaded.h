#pragma once

#include <curl\curl.h>
#include <string>
#include <vector>

namespace anteRSSParser
{
	typedef void(*DownloadManagerCallback)(std::string url, std::vector<char> content, void * data, bool success);

	class DownloadManagerUnthreaded
	{
	private:
		CURLSH * share;
		CURL * getEasyHandle(std::string url);
		char errbuf[CURL_ERROR_SIZE];
	public:
		DownloadManagerUnthreaded();

		std::string getContentType(std::string url);
		std::vector<char> downloadSingle(std::string url, bool &isSuccess);
		std::string downloadToFolder(std::string url, std::string path);
		void downloadMultiple(std::vector<std::string> urls, DownloadManagerCallback callback, void * data);
		std::string getLastError();

		~DownloadManagerUnthreaded();
	};
}

