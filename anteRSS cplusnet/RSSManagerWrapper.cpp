#include "RSSManagerWrapper.h"

#include <msclr\marshal_cppstd.h>
#include "anteRSSParser\RSSManager.h"

using namespace anteRSScplusnet;
using namespace msclr::interop;

anteRSScplusnet::RSSManagerWrapper::RSSManagerWrapper(System::String^ dbFile)
{
	manager = new anteRSSParser::RSSManager(marshal_as<std::string>(dbFile));
	feedCache = new anteRSSParser::RSSFeedVector();
}

void anteRSScplusnet::RSSManagerWrapper::updateFeedListCache()
{
	feedCache->swap(manager->getAllFeeds());
}

RSSFeedWrapper ^ anteRSScplusnet::RSSManagerWrapper::getFeedListCacheAt(System::Int32 index)
{
	return gcnew RSSFeedWrapper(&(feedCache->at(index)));
}

System::Int32 anteRSScplusnet::RSSManagerWrapper::getFeedListCacheLength()
{
	return feedCache->size();
}

anteRSScplusnet::RSSManagerWrapper::!RSSManagerWrapper()
{
	delete feedCache;
	delete manager;
}

anteRSScplusnet::RSSManagerWrapper::~RSSManagerWrapper()
{
	this->~RSSManagerWrapper();
}

anteRSScplusnet::RSSFeedWrapper::RSSFeedWrapper(anteRSSParser::RSSFeed * content)
{
	this->content = content;
}

System::String ^ anteRSScplusnet::RSSFeedWrapper::Name::get()
{
	return marshal_as<System::String ^>(content->name);
}
