#include "stdafx.h"
#include "CppUnitTest.h"

#include <fstream>
#include <windows.h>
#include <curl/curl.h>
#include "anteRSSParser\anteRSSParser.h"

using namespace anteRSSParser;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace anteRSSTest
{		
	TEST_CLASS(RSSManagerTest)
	{
	public:
		RSSManager * manager;
		RSSManagerTest()
		{
			curl_global_init(CURL_GLOBAL_ALL);
			manager = new RSSManager(":memory:");
		}

		~RSSManagerTest()
		{
			delete manager;
			curl_global_cleanup();
		}

		TEST_METHOD(addFeedTest)
		{
			RSSFeed feed;
			feed.id = 0;
			feed.name = "testtitle 日本語できるかな？　";
			feed.url = "testurl";

			manager->addFeed(feed);
			manager->addFeed(feed);

			RSSFeedVector result = manager->getAllFeeds();

			Assert::AreEqual(1, (int) result.size(), L"feeds added amount mismatch", LINE_INFO());

			RSSFeed resultFeed = result.at(0);

			Assert::AreEqual(feed.name, resultFeed.name, L"name not preserved", LINE_INFO());
			Assert::AreEqual(feed.url, resultFeed.url, L"url not preserved", LINE_INFO());
			Assert::AreNotEqual(feed.id, resultFeed.id, L"no new id", LINE_INFO());

			RSSFeed feed2;
			feed2.id = 0;
			feed2.name = "あたらしい！";
			feed2.url = "testurl2";

			manager->addFeed(feed2);

			result = manager->getAllFeeds();

			Assert::AreEqual(2, (int)result.size(), L"feeds added amount mismatch", LINE_INFO());

			RSSFeed resultFeed2 = result.at(1);

			Assert::AreEqual(feed2.name, resultFeed2.name, L"name not preserved", LINE_INFO());
			Assert::AreEqual(feed2.url, resultFeed2.url, L"url not preserved", LINE_INFO());
			Assert::AreNotEqual(feed2.id, resultFeed2.id, L"no new id", LINE_INFO());
			Assert::AreNotEqual(resultFeed.id, resultFeed2.id, L"no new id", LINE_INFO());
		}

		TEST_METHOD(removeFeedTest)
		{
			RSSFeed feed;
			feed.id = 0;
			feed.name = "testtitle 日本語できるかな？　";
			feed.url = "testurl";

			manager->addFeed(feed);

			RSSFeed feed2;
			feed2.id = 0;
			feed2.name = "あたらしい！";
			feed2.url = "testurl2";

			manager->addFeed(feed2);

			RSSFeedVector result = manager->getAllFeeds();

			Assert::AreEqual(2, (int)result.size(), L"feeds added amount mismatch", LINE_INFO());

			manager->removeFeed(result.at(0).id);
			manager->removeFeed(11);

			RSSFeedVector result2 = manager->getAllFeeds();

			Assert::AreEqual(1, (int)result2.size(), L"feeds removed amount mismatch", LINE_INFO());

			RSSFeed resultFeed2 = result2.at(0);

			Assert::AreEqual(feed2.name, resultFeed2.name, L"name not preserved", LINE_INFO());
			Assert::AreEqual(feed2.url, resultFeed2.url, L"url not preserved", LINE_INFO());
		}

		TEST_METHOD(getFeedTest)
		{
			RSSFeed feed;
			feed.id = 0;
			feed.name = "testtitle 日本語できるかな？　";
			feed.url = "testurl";

			manager->addFeed(feed);

			RSSFeed resultFeed = manager->getFeed(1);

			Assert::AreEqual(feed.name, resultFeed.name, L"name not preserved", LINE_INFO());
			Assert::AreEqual(feed.url, resultFeed.url, L"url not preserved", LINE_INFO());
			Assert::AreNotEqual(feed.id, resultFeed.id, L"no new id", LINE_INFO());
		}

		TEST_METHOD(getFeedFromUrlTest)
		{
			RSSFeed feed;
			feed.id = 0;
			feed.name = "testtitle 日本語できるかな？　";
			feed.url = "testurl";

			manager->addFeed(feed);

			RSSFeedVector result = manager->getAllFeeds();
			Assert::AreEqual(1, (int)result.size(), L"feed not added", LINE_INFO());

			RSSFeed resultFeed = manager->getFeedFromUrl(feed.url);

			Assert::AreEqual(feed.name, resultFeed.name, L"name not preserved", LINE_INFO());
			Assert::AreEqual(feed.url, resultFeed.url, L"url not preserved", LINE_INFO());
			Assert::AreNotEqual(feed.id, resultFeed.id, L"no new id", LINE_INFO());
		}

		static void updateFeedTestCallback(int feedid, bool success, RSSFeedItemVector newItem, void * data)
		{

			if ((int) data == 0)
			{
				Assert::AreEqual(1, feedid, L"update callback incorrect feed", LINE_INFO());
				Assert::IsTrue(success, L"unsuccessful update", LINE_INFO());
				Assert::AreEqual(3, (int) newItem.size(), L"wrong number of new items", LINE_INFO());
			}
			else if ((int) data == 1)
			{
				Assert::AreEqual(1, feedid, L"update callback incorrect feed", LINE_INFO());
				Assert::IsTrue(success, L"unsuccessful update", LINE_INFO());
				Assert::AreEqual(1, (int)newItem.size(), L"wrong number of new items", LINE_INFO());
			}
			else if ((int)data == 2)
			{
				Assert::AreEqual(1, feedid, L"update callback incorrect feed", LINE_INFO());
				Assert::IsTrue(success, L"unsuccessful update", LINE_INFO());
				Assert::AreEqual(4, (int)newItem.size(), L"wrong number of new items", LINE_INFO());
			}
			
		}

		TEST_METHOD(updateFeedTest)
		{
			RSSFeed feed;
			feed.id = 0;
			feed.name = "testtitle 日本語できるかな？　";
			feed.url = "\x7ftest/test.xml";

			manager->addFeed(feed);

			CopyFile(L"test/rss-2.0-sample-old.xml", L"test/test.xml", false);

			manager->updateFeed(1, updateFeedTestCallback, 0);

			CopyFile(L"test/rss-2.0-sample.xml", L"test/test.xml", false);

			manager->updateFeed(1, updateFeedTestCallback, (void *) 1);
		}

		TEST_METHOD(updateFeedTest2)
		{
			RSSFeed feed;
			feed.id = 0;
			feed.name = "あたらしい！";
			feed.url = "http://www.rssboard.org/files/rss-2.0-namespace.xml";

			manager->addFeed(feed);

			manager->updateFeed(1, updateFeedTestCallback, (void *) 2);
		}

		TEST_METHOD(downloadTest)
		{
			std::string result = downloadTextFile("https://urlecho.appspot.com/echo?status=200&Content-Type=text%2Fplain&body=testing");
			Assert::AreEqual("testing", result.c_str(), L"download failed", LINE_INFO());
		}

		TEST_METHOD(downloadManagerTest)
		{
			DownloadManager dManager;
			std::vector<char> & result = dManager.downloadSingle("https://urlecho.appspot.com/echo?status=200&Content-Type=text%2Fplain&body=testing");
			Assert::IsTrue(result.size() > 0, L"download empty", LINE_INFO());
			Assert::AreEqual(0, strncmp("testing", result.data(), result.size()), L"download failed", LINE_INFO());

			std::vector<char> result2 = dManager.downloadSingle("https://www.google.com.ph/images/branding/googlelogo/2x/googlelogo_color_272x92dp.png");

			// png check, not conclusive
			char header[] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };
			char trailer[] = { 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82 };

			for (size_t i = 0; i < ARRAYSIZE(header); ++i)
			{
				Assert::AreEqual(header[i], result2[i], L"file corrupted", LINE_INFO());
			}

			for (size_t i = 0; i < ARRAYSIZE(trailer); ++i)
			{
				Assert::AreEqual(trailer[i], result2[i + result2.size() - ARRAYSIZE(trailer)], L"file corrupted", LINE_INFO());
			}

		}

	};
}