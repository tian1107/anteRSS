#include "stdafx.h"
#include "CppUnitTest.h"

#include <windows.h>
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
			manager = new RSSManager(":memory:");
		}

		~RSSManagerTest()
		{
			delete manager;
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
			Assert::AreEqual(1, feedid, L"update callback incorrect feed", LINE_INFO());
			Assert::IsTrue(success, L"unsuccessful update", LINE_INFO());

			if ((int) data == 0)
			{
				Assert::AreEqual(3, (int) newItem.size(), L"wrong number of new items", LINE_INFO());
			}
			else if ((int) data == 1)
			{
				Assert::AreEqual(1, (int)newItem.size(), L"wrong number of new items", LINE_INFO());
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

	};
}