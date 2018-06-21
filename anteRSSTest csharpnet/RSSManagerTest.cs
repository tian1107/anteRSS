using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using anteRSSParser_csharpnet;

namespace anteRSSTest_csharpnet
{
	[TestClass]
	public class RSSManagerTest
	{
		[TestMethod]
		public void ConstructorTest()
		{
			// The test file
			String testFile = "test0.db";

			// Delete the file
			System.IO.File.Delete(testFile);

			// Create new file
			RSSManager manager = new RSSManager(testFile);

			Assert.IsTrue(System.IO.File.Exists(testFile));

			// Reopen it
			RSSManager manager2 = new RSSManager(testFile);

			// TODO check file contents
		}

		[TestMethod]
		public void AddFeedTest()
		{
			// The test file
			String testFile = "test1.db";

			// Delete the file
			System.IO.File.Delete(testFile);

			// Create a new one
			RSSManager manager = new RSSManager(testFile);

			// Variables for test
			String[] names = { "test1", "test2", "試し", "こうなる", "test1", "➝", "🆗" };
			String[] urls = { "a", "b", "c", "d", "e", "http://a/", "test.xml" };

			for (int i = 0; i < names.Length; ++i)
			{
				Assert.AreEqual(i + 1, manager.AddFeed(names[i], urls[i]));
			}

			// shouldn't work, same url
			Assert.AreEqual(-1, manager.AddFeed("test3", "b"));

			// Check contents
			for (int i = 0; i < names.Length; ++i)
			{
				RSSFeed result = manager.GetFeed(i + 1);
				Assert.AreEqual(i + 1, result.id);
				Assert.AreEqual(names[i], result.name);
				Assert.AreEqual(urls[i], result.url);
				Assert.AreEqual(0, result.unread);
			}
		}
	}
}
