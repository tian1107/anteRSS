using System;
using System.Xml.Linq;

namespace anteRSSParser_csharpnet
{
	public class RSSItem
	{
		private readonly RSSDocumentFormat format;
		private readonly XElement element;

		public RSSItem(RSSDocumentFormat format, XElement element)
		{
			this.format = format;
			this.element = element;
		}

		public String Title
		{
			get
			{
				throw new NotImplementedException();
			}
		}

		public String GUID
		{
			get
			{
				throw new NotImplementedException();
			}
		}

		public String Description
		{
			get
			{
				throw new NotImplementedException();
			}
		}

		public String Link
		{
			get
			{
				throw new NotImplementedException();
			}
		}

		public String ContentEncoded
		{
			get
			{
				throw new NotImplementedException();
			}
		}

		public String DateFormatted
		{
			get
			{
				throw new NotImplementedException();
			}
		}

		public String DateActual
		{
			get
			{
				throw new NotImplementedException();
			}
		}

		public RSSFeedItem ConvertToRSSFeedItem()
		{
			throw new NotImplementedException();
		}
	}
}
