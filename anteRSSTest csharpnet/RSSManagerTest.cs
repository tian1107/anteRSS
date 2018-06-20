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
			using (RSSManager manager = new RSSManager(testFile))
			{

			}

			Assert.IsTrue(System.IO.File.Exists(testFile));

			// Reopen it
			using (RSSManager manager = new RSSManager(testFile))
			{

			}

			// TODO check file contents
		}
	}
}
