#pragma once

#include <string>
#include <vector>
#include <mutex>

#include "DownloadManagerUnthreaded.h"

namespace anteRSSParser
{
	class DownloadManager
	{
	private:
		DownloadManagerUnthreaded * downloadManager;
		std::mutex lock;
	public:
		DownloadManager();
		~DownloadManager();
		std::string getContentType(std::string url);
		std::vector<char> downloadSingle(std::string url, bool &isSuccess);
		std::string downloadToFolder(std::string url, std::string path);
		void downloadMultiple(std::vector<std::string> urls, DownloadManagerCallback callback, void * data);
		std::string getLastError();
	};
}