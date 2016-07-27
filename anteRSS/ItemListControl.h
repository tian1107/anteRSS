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
		anteRSSParser::RSSFeedItemVector itemCache;
		std::wstring editBuffer;
		anteRSSParser::DownloadManager dManager;

		// indices
		int imageRead;
		int imageUnread;
		int imageArchived;

		// functions
		void createImageLists();
		void createColumns();
		int insertRow(int index, anteRSSParser::RSSFeedItem * feed);
		void changeIcon(int index, int imageIndex);
	public:
		ItemListControl(HINSTANCE hInst, ItemDescControl * descControl, anteRSSParser::RSSManager * manager);
		void CreateControl(HWND parent);
		void notifyItemListChanged(int feedId);
		void notifyResize(RECT rect);
		int notifyNotify(LPARAM lParam);
	};
}