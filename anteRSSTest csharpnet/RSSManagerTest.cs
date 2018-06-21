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

			// should work
			Assert.AreEqual(1, manager.AddFeed("test", "a"));
			Assert.AreEqual(2, manager.AddFeed("test1", "b"));
			Assert.AreEqual(3, manager.AddFeed("test2", "c"));
			Assert.AreEqual(4, manager.AddFeed("あいうえお", "d"));

			// shouldn't work
			Assert.AreEqual(-1, manager.AddFeed("test3", "b"));

			// TODO check file contents
		}
	}
}
