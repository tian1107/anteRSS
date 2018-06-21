using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace anteRSSParser_csharpnet
{
	public enum RSSDocumentFormat
	{
		Invalid = -1,
		Unknown = 0,
		RSS2 = 1,
		ATOM1 = 2
	}

	public class RSSDocument
	{
		protected XDocument document;

		public String Title { get; }

		public RSSDocument(String content)
		{
			document = XDocument.Parse(content);

			// TODO get title, format
			throw new NotImplementedException();
		}

		public RSSItem [] getItems()
		{
			throw new NotImplementedException();
		}
	}
}
