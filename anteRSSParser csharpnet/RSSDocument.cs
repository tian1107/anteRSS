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
			title = "Unknown Title";

			try
			{
				document = XDocument.Parse(content);
			}
			catch (System.Xml.XmlException e)
			{
				format = RSSDocumentFormat.Invalid;
				error = e.Message;
			}

			// Get format and title
			DetermineFormat();
			DetermineTitle();
		}

		public RSSItem [] GetItems()
		{
			IEnumerable<XElement> items;

			if (format == RSSDocumentFormat.RSS2)
			{
				XElement list = document.Element("channel");
				if (list == null)
				{
					items = Enumerable.Empty<XElement>();
				}
				else
				{
					items = list.Elements("item");
				}
			}
			else if (format == RSSDocumentFormat.ATOM1)
			{
				items = document.Elements("entry");
			}
			else
			{
				items = Enumerable.Empty<XElement>();
			}

			// Convert to RSSItem
			RSSItem[] result = new RSSItem[items.Count()];

			for (int i = 0; i < items.Count(); ++i)
			{
				result[i] = new RSSItem(format, items.ElementAt(i));
			}

			return result;
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

		private void DetermineTitle()
		{
			if (format == RSSDocumentFormat.RSS2)
			{
				try
				{
					title = document.Element("channel").Element("title").Value;
				}
				catch (NullReferenceException)
				{
					title = "No title";
				}
			}
			else if (format == RSSDocumentFormat.ATOM1)
			{
				try
				{
					title = document.Element("title").Value;
				}
				catch (NullReferenceException)
				{
					title = "No title";
				}
			}
			else
			{
				title = "Error Title";
			}
		}

		public String GetTitle()
		{
			return title;
		}

		public String GetError()
		{
			return error;
		}
	}
}
