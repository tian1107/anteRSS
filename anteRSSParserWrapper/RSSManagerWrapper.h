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

		property System::Int32 FeedId
		{
			System::Int32 get();
		}

		property System::String ^Name
		{
			System::String ^get();
		}

		property System::Int32 Unread
		{
			System::Int32 get();
		}
	};

	public ref class RSSFeedItemWrapper
	{
	private:
		anteRSSParser::RSSFeedItem * content;
	public:
		RSSFeedItemWrapper(anteRSSParser::RSSFeedItem * content);

		property System::String ^Title
		{
			System::String ^get();
		}

		property System::String ^Description
		{
			System::String ^get();
		}

		property System::String ^Link
		{
			System::String ^get();
		}

		property System::Int32 Status
		{
			System::Int32 get();
		}
	};

	delegate System::Void RSSManagerCallbackWrapper(System::Int32 feedid, System::Boolean success, System::String^ errorMessage);

	public ref class RSSManagerWrapper
	{
	private:
		anteRSSParser::RSSManager * manager;
		anteRSSParser::RSSFeedVector * feedCache;
		anteRSSParser::RSSFeedItemVector * itemCache;
		anteRSSParser::RSSFeedItemVector * itemCacheNew;
	public:
		RSSManagerWrapper(System::String^ dbFile);

		System::Void updateFeedListCache();
		RSSFeedWrapper ^ getFeedListCacheAt(System::Int32 index);
		System::Int32 getFeedListCacheLength();

		System::Void cacheFeedItems(System::Int32 feedId);
		System::Void cacheFeedItemsByStatus(System::Int32 status);
		RSSFeedItemWrapper ^ getItemListCacheAt(System::Int32 index);
		System::Int32 getItemListCacheLength();

		//System::Void updateFeed(System::Int32 feedId, RSSManagerCallbackWrapper ^ callback);

		!RSSManagerWrapper();
		~RSSManagerWrapper();
	};

}

