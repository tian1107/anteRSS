#pragma once
#include "anteRSSParser\anteRSSParser.h"

namespace anteRSS
{
	class FeedListControl
	{
	private:
		// window stuff
		HINSTANCE hInst;
		HWND listControl;

		// rss stuff
		anteRSSParser::RSSManager * manager;
		anteRSSParser::RSSFeedVector feedCache;
		std::wstring editBuffer;

		// indices
		int imageRSS;

		// functions
		void createImageLists();
		void createColumns();
		int insertRow(int imageIndex, int index, std::wstring text, anteRSSParser::RSSFeed * feed);
	public:
		FeedListControl(HINSTANCE hInst, anteRSSParser::RSSManager * manager);
		void CreateControl(HWND parent);
		void notifyFeedListChanged();
		void notifyResize(RECT rect);
		int notifyNotify(LPARAM lParam);
		anteRSSParser::RSSFeed * getSelectedFeed();
	};
}