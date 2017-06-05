#include "stdafx.h"

#include "DownloadManager.h"

namespace anteRSSParser
{
	DownloadManager::DownloadManager()
	{
		downloadManager = new DownloadManagerUnthreaded();
	}

	DownloadManager::~DownloadManager()
	{
		delete downloadManager;
	}

	std::string DownloadManager::getContentType(std::string url)
	{
		lock.lock();

		std::string result = downloadManager->getContentType(url);

		lock.unlock();

		return result;
	}

	// downloads a single file, no null terminator at the end
	std::vector<char> DownloadManager::downloadSingle(std::string url, bool &success)
	{
		lock.lock();

		std::vector<char> str = downloadManager->downloadSingle(url, success);

		lock.unlock();

		return str;
	}

	std::string DownloadManager::downloadToFolder(std::string url, std::string path)
	{
		lock.lock();

		std::string name = downloadManager->downloadToFolder(url, path);

		lock.unlock();

		return name;
	}

	void DownloadManager::downloadMultiple(std::vector<std::string> urls, DownloadManagerCallback callback, void * data)
	{
		lock.lock();
		
		downloadManager->downloadMultiple(urls, callback, data);

		lock.unlock();
	}

	std::string DownloadManager::getLastError()
	{
		return downloadManager->getLastError();
	}

}