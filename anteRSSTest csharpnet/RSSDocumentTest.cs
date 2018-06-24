using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using anteRSSParser_csharpnet;

namespace anteRSSTest_csharpnet
{
	[TestClass]
	public class RSSDocumentTest
	{
		[TestMethod]
		public void RSS2Test()
		{
			string contents = System.IO.File.ReadAllText("RSSDocument Test Inputs/RSS2Test.xml");

			RSSDocument document = new RSSDocument(contents);

			Assert.AreEqual("Ajax and XUL", document.GetTitle());
			Assert.AreEqual(2, document.GetItems().Length);
		}
	}
}
