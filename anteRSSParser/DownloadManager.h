#pragma once

#include <curl\curl.h>
#include <string>
#include <vector>
#include <mutex>

namespace anteRSSParser
{
	typedef void(*DownloadManagerCallback)(std::string url, std::vector<char> content, void * data);

	class DownloadManager
	{
	private:
		CURLSH * share;
		std::mutex lock;
	public:
		DownloadManager();
		~DownloadManager();
		std::string getContentType(std::string url);
		std::vector<char> downloadSingle(std::string url);
		std::string downloadToFolder(std::string url, std::string path);
		void downloadMultiple(std::vector<std::string> urls, DownloadManagerCallback callback, void * data);
	};

	// just download a thing
	std::string downloadTextFile(std::string url);
}