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
		protected RSSDocumentFormat format;
		protected String error;
		protected String title;

		public RSSDocument(String content)
		{
			format = RSSDocumentFormat.Unknown;
			error = "No Error";
			title = "Untitled";

			try
			{
				document = XDocument.Parse(content);
			}
			catch (System.Xml.XmlException e)
			{
				format = RSSDocumentFormat.Invalid;
				error = e.Message;
			}

			// TODO get title, format
			DetermineFormat();
			throw new NotImplementedException();
		}

		public RSSItem [] getItems()
		{
			throw new NotImplementedException();
		}

		private void DetermineFormat()
		{
			// Check first if document is valid xml
			if (format != RSSDocumentFormat.Unknown)
				return;

			// Check if RSS 2.0
			if(document.Root.Name.LocalName.Equals("rss"))
			{
				if (document.Root.Attribute("version").Value.Equals("2.0"))
				{
					format = RSSDocumentFormat.RSS2;
				}
				else
				{
					format = RSSDocumentFormat.Invalid;
					error = "Only RSS 2.0 is accepted.";
				}
			}
			// Check if ATOM 1
			else if (document.Root.Name.LocalName.Equals("feed"))
			{
				format = RSSDocumentFormat.ATOM1;
			}
			// Other formats
			else
			{
				format = RSSDocumentFormat.Invalid;
				error = "This XML Document could not be used.";
			}
		}

		public String getTitle()
		{
			return title;
		}

		public String getError()
		{
			return error;
		}
	}
}
