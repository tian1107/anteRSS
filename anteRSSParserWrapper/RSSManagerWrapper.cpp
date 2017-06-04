#include "Stdafx.h"

#include "RSSManagerWrapper.h"

#include <msclr\marshal_cppstd.h>
#include "anteRSSParser\RSSManager.h"

using namespace anteRSSParserWrapper;
using namespace msclr::interop;

anteRSSParserWrapper::RSSManagerWrapper::RSSManagerWrapper(System::String^ dbFile)
{
	manager = new anteRSSParser::RSSManager(marshal_as<std::string>(dbFile));
	feedCache = new anteRSSParser::RSSFeedVector();
	itemCache = new anteRSSParser::RSSFeedItemVector();
}

void anteRSSParserWrapper::RSSManagerWrapper::updateFeedListCache()
{
	feedCache->swap(manager->getAllFeeds());
}

RSSFeedWrapper ^ anteRSSParserWrapper::RSSManagerWrapper::getFeedListCacheAt(System::Int32 index)
{
	return gcnew RSSFeedWrapper(&(feedCache->at(index)));
}

System::Int32 anteRSSParserWrapper::RSSManagerWrapper::getFeedListCacheLength()
{
	return feedCache->size();
}

System::Void anteRSSParserWrapper::RSSManagerWrapper::cacheFeedItems(System::Int32 feedId)
{
	itemCache->swap(manager->getItemsOfFeed(feedId));
}

RSSFeedItemWrapper ^ anteRSSParserWrapper::RSSManagerWrapper::getItemListCacheAt(System::Int32 index)
{
	return gcnew RSSFeedItemWrapper(&(itemCache->at(index)));
}

System::Int32 anteRSSParserWrapper::RSSManagerWrapper::getItemListCacheLength()
{
	return itemCache->size();
}

anteRSSParserWrapper::RSSManagerWrapper::!RSSManagerWrapper()
{
	delete itemCache;
	delete feedCache;
	delete manager;
}

anteRSSParserWrapper::RSSManagerWrapper::~RSSManagerWrapper()
{
	this->~RSSManagerWrapper();
}

anteRSSParserWrapper::RSSFeedWrapper::RSSFeedWrapper(anteRSSParser::RSSFeed * content)
{
	this->content = content;
}

System::Int32 anteRSSParserWrapper::RSSFeedWrapper::FeedId::get()
{
	return content->id;
}

System::String ^ anteRSSParserWrapper::RSSFeedWrapper::Name::get()
{
	return marshal_as<System::String ^>(content->name);
}

System::Int32 anteRSSParserWrapper::RSSFeedWrapper::Unread::get()
{
	return content->unread;
}

anteRSSParserWrapper::RSSFeedItemWrapper::RSSFeedItemWrapper(anteRSSParser::RSSFeedItem * content)
{
	this->content = content;
}

System::String ^ anteRSSParserWrapper::RSSFeedItemWrapper::Title::get()
{
	return marshal_as<System::String ^>(content->title);
}

System::String ^ anteRSSParserWrapper::RSSFeedItemWrapper::Description::get()
{
	return marshal_as<System::String ^>(content->description);
}
