#pragma once

#include "anteRSSParser\RSSManager.h"

namespace anteRSSParserWrapper
{
	public ref class RSSFeedWrapper
	{
	private:
		anteRSSParser::RSSFeed * content;
	public:
		RSSFeedWrapper(anteRSSParser::RSSFeed * content);

		property System::String ^Name
		{
			System::String ^get();
		}

		property System::Int32 ^Unread
		{
			System::Int32 ^get();
		}
	};

	public ref class RSSManagerWrapper
	{
	private:
		anteRSSParser::RSSManager * manager;
		anteRSSParser::RSSFeedVector * feedCache;
	public:
		RSSManagerWrapper(System::String^ dbFile);

		System::Void updateFeedListCache();
		RSSFeedWrapper ^ getFeedListCacheAt(System::Int32 index);
		System::Int32 getFeedListCacheLength();

		!RSSManagerWrapper();
		~RSSManagerWrapper();
	};

}

