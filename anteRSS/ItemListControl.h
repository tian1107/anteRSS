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
		int imageRead;
		int imageUnread;
		int imageArchived;

		// functions
		void createImageLists();
		void createColumns();
		int insertRow(int index, anteRSSParser::RSSFeedItem * feed);
		void changeIcon(int index, int imageIndex);
	public:
		ItemListControl(HINSTANCE hInst, anteRSSParser::RSSManager * manager);
		void CreateControl(HWND parent);
		void notifyItemListChanged(int feedId);
		void notifyResize(LPARAM lParam);
		int notifyNotify(LPARAM lParam);
	};
}