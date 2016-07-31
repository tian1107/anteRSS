#include "stdafx.h"

#include "DownloadManager.h"
#include "Util.h"

#include <sstream>
#include <fstream>
#include <algorithm>

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
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 240);	// 240 seconds before timeout

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

	std::string DownloadManager::getContentType(std::string url)
	{
		lock.lock();

		CURL * curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_SHARE, share);
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 240);	// 240 seconds before timeout

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// TODO error check!
		curl_easy_perform(curl);

		char * str;
		curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &str);

		std::string result(str);

		curl_easy_cleanup(curl);

		lock.unlock();

		return result;
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
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 240);	// 240 seconds before timeout

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadSingle_cb);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);

		// TODO error check!
		curl_easy_perform(curl);

		curl_easy_cleanup(curl);

		lock.unlock();

		return str;
	}

	size_t downloadFileHeader_cb(void *buffer, size_t size, size_t nmemb, void * data)
	{
		char * buf = (char *)buffer;
		std::string line(buf, size * nmemb);
		std::string line2(buf, size * nmemb);
		std::string & name = *(std::string *) data;

		//convert to lowercase
		std::transform(line2.begin(), line2.end(), line2.begin(), ::tolower);

		std::string tag = "content-disposition:";
		std::string subTag = "filename=";

		// when line starts with tag
		if (line2.compare(0, tag.length(), tag) == 0)
		{
			size_t pos = line.find(subTag, tag.length());
			if (pos != line.npos)
			{
				size_t start = -1;
				size_t end = -1;
				for (size_t i = pos; i < line.length(); ++i)
				{
					char c = line[i];
					if (c == '\"')
					{
						// starting
						if (start == -1)
						{
							start = i + 1;
						}
						// ending
						else
						{
							end = i;
							break;
						}
					}
				}

				name = line.substr(start, end - start);
			}
		}

		return size * nmemb;
	}

	std::string DownloadManager::downloadToFolder(std::string url, std::string path)
	{
		lock.lock();

		// the result
		std::vector<char> str;
		std::string name = "";

		CURL * curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_SHARE, share);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 240);	// 240 seconds before timeout

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadSingle_cb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);

		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, downloadFileHeader_cb);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &name);

		// TODO error check!
		curl_easy_perform(curl);

		// TODO unit test

		// save to file
		// get name if not exists
		if (name.length() < 1)
		{
			size_t start = url.find_last_of("/\\") + 1;
			if (start != url.npos)
			{
				name = url.substr(start);
			}
			else
			{
				name = "temp.txt";
			}
		}

		std::ofstream out(path + "/" + name, std::ios::out | std::ios::binary);
		std::copy(str.begin(), str.end(), std::ostreambuf_iterator<char>(out));
		out.close();

		curl_easy_cleanup(curl);

		lock.unlock();

		return name;
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
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 240);	// 240 seconds before timeout

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