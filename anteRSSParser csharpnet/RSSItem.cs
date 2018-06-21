using System;
using System.Xml.Linq;

namespace anteRSSParser_csharpnet
{
	public class RSSItem
	{
		private readonly RSSDocumentFormat format;
		private readonly XNode node;

		public RSSItem(RSSDocumentFormat format, XNode node)
		{
			this.format = format;
			this.node = node;
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
