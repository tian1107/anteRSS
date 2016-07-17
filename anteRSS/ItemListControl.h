#pragma once
#include "anteRSSParser\anteRSSParser.h"

namespace anteRSS
{
	class ItemListControl
	{
	private:
		// window stuff
		HINSTANCE hInst;
		HWND listControl;

		// rss stuff
		anteRSSParser::RSSManager * manager;
		anteRSSParser::RSSFeedItemVector itemCache;
		std::wstring editBuffer;

		// indices
		int imageRSS;

		// functions
		void createImageLists();
		void createColumns();
		int insertRow(int imageIndex, int index, anteRSSParser::RSSFeedItem * feed);
	public:
		ItemListControl(HINSTANCE hInst, anteRSSParser::RSSManager * manager);
		void CreateControl(HWND parent);
		void notifyItemListChanged(int feedId);
		void notifyResize(LPARAM lParam);
		int notifyNotify(LPARAM lParam);
	};
}