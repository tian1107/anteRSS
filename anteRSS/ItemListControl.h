#pragma once
#include "anteRSSParser\anteRSSParser.h"
#include "ItemDescControl.h"

namespace anteRSS
{
	class ItemListControl
	{
	private:
		// window stuff
		HINSTANCE hInst;
		HWND listControl;
		ItemDescControl * descControl;

		// rss stuff
		anteRSSParser::RSSManager * manager;
		int itemCacheIndexStart;
		int itemCacheIndexEnd;
		anteRSSParser::RSSFeedItemVector itemCache;
		anteRSSParser::DownloadManager dManager;

		// indices
		int imageRead;
		int imageUnread;
		int imageArchived;

		// functions
		void createImageLists();
		void createColumns();
		anteRSSParser::RSSFeedItem & getFeedItem(int listIndex);
		void selectItem(int iItem);
	public:
		ItemListControl(HINSTANCE hInst, ItemDescControl * descControl, anteRSSParser::RSSManager * manager);
		void CreateControl(HWND parent);
		void notifyItemListChanged(int feedId);
		void notifyResize(RECT rect);
		int notifyNotify(LPARAM lParam);
		void archiveSelected();
	};
}