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

anteRSSParserWrapper::RSSManagerWrapper::!RSSManagerWrapper()
{
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

System::String ^ anteRSSParserWrapper::RSSFeedWrapper::Name::get()
{
	return marshal_as<System::String ^>(content->name);
}

System::Int32 anteRSSParserWrapper::RSSFeedWrapper::Unread::get()
{
	return content->unread;
}
