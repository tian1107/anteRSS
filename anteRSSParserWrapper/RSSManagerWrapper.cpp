#include "Stdafx.h"

#include "RSSManagerWrapper.h"

#include <msclr\marshal_cppstd.h>
#include "anteRSSParser\RSSManager.h"

using namespace anteRSSParserWrapper;
using namespace msclr::interop;

// Local function for converting std::string to String^
System::String ^ stdStringtoCSString(std::string in)
{
	cli::array<System::Byte>^ a = gcnew cli::array<System::Byte>(in.length());
	int i = in.length();
	while (i-- > 0)
		a[i] = in[i];

	return System::Text::Encoding::UTF8->GetString(a);
}

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

System::Void anteRSSParserWrapper::RSSManagerWrapper::cacheFeedItemsByStatus(System::Int32 status)
{
	itemCache->swap(manager->getItemsOfStatus(status));
	return System::Void();
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
	return stdStringtoCSString(content->name);
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
	return stdStringtoCSString(content->title);
}

System::String ^ anteRSSParserWrapper::RSSFeedItemWrapper::Description::get()
{
	if(content->contentEncoded.empty())
		return stdStringtoCSString(content->description);
	else
		return stdStringtoCSString(content->contentEncoded);
}

System::String ^ anteRSSParserWrapper::RSSFeedItemWrapper::Link::get()
{
	return stdStringtoCSString(content->link);
}

System::Int32 anteRSSParserWrapper::RSSFeedItemWrapper::Status::get()
{
	return content->status;
}

