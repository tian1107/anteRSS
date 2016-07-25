#include "stdafx.h"

#include "DownloadManager.h"

#include <sstream>

namespace anteRSSParser
{
	size_t downloadTextFile_cb(void *buffer, size_t size, size_t nmemb, void * data)
	{
		std::stringstream & str = *((std::stringstream *) data);
		char * buf = (char *)buffer;

		str.write(buf, size * nmemb);

		return size * nmemb;
	}

	std::string downloadTextFile(std::string url)
	{
		// the result
		std::stringstream str;

		CURL * curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadTextFile_cb);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);

		// TODO error check!
		curl_easy_perform(curl);

		curl_easy_cleanup(curl);
		return str.str();
	}

	DownloadManager::DownloadManager()
	{
		share = curl_share_init();
		curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_COOKIE);
		curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
		curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_SSL_SESSION);
	}

	DownloadManager::~DownloadManager()
	{
		curl_share_cleanup(share);
	}

	size_t downloadSingle_cb(void *buffer, size_t size, size_t nmemb, void * data)
	{
		std::vector<char> & str = *((std::vector<char> *) data);
		char * buf = (char *)buffer;
		size_t start = str.size();

		// resize
		str.resize(str.size() + size * nmemb);

		// copy
		for (size_t i = start; i < str.size(); ++i)
		{
			str[i] = buf[i - start];
		}

		return size * nmemb;
	}

	// downloads a single file, no null terminator at the end
	std::vector<char> DownloadManager::downloadSingle(std::string url)
	{
		lock.lock();

		// the result
		std::vector<char> str;

		CURL * curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_SHARE, share);

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadSingle_cb);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);

		// TODO error check!
		curl_easy_perform(curl);

		curl_easy_cleanup(curl);

		lock.unlock();

		return str;
	}

	void DownloadManager::downloadMultiple(std::vector<std::string> urls, DownloadManagerCallback callback, void * data)
	{
		lock.lock();
		int repeats = 0;

		CURLM * multi = curl_multi_init();

		std::vector<CURL *> handles;
		std::vector<std::vector<char> *> files;
		for (std::vector<std::string>::iterator it = urls.begin(); it != urls.end(); ++it)
		{
			CURL * curl = curl_easy_init();
			curl_easy_setopt(curl, CURLOPT_SHARE, share);

			curl_easy_setopt(curl, CURLOPT_URL, it->c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadSingle_cb);

			std::vector<char> * file = new std::vector<char>;
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
			files.push_back(file);

			handles.push_back(curl);
			curl_multi_add_handle(multi, curl);
		}

		int filesLeft = 0;
		curl_multi_perform(multi, &filesLeft);
		do
		{
			CURLMcode mc;
			int numfds;
			mc = curl_multi_wait(multi, NULL, 0, 1000, &numfds);

			if (mc != CURLM_OK)
			{
				fprintf(stderr, "curl_multi_wait() failed, code %d.\n", mc);
				break;
			}

			if (!numfds)
			{
				repeats++; /* count number of repeated zero numfds */
				if (repeats > 1)
				{
					Sleep(100); /* sleep 100 milliseconds */
				}
			}
			else
				repeats = 0;

			curl_multi_perform(multi, &filesLeft);
		} while (filesLeft);

		// all files downloaded
		for (int i = 0; i < handles.size(); ++i)
		{
			CURL * curl = handles[i];
			std::vector<char> * file = files[i];

			curl_multi_remove_handle(multi, curl);
			curl_easy_cleanup(curl);

			callback(urls[i], *file, data);

			delete file;
		}

		curl_multi_cleanup(multi);

		lock.unlock();
	}
}