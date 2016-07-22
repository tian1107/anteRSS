#pragma once
#include "anteRSSParser\anteRSSParser.h"
#include "FeedListControl.h"
#include "ItemListControl.h"

#define BTN_ANTERSS_NEW 0
#define BTN_ANTERSS_UPD 1
#define BTN_ANTERSS_ALL 2
#define BTN_ANTERSS_REM 3
#define BTN_ANTERSS_RDA 4

#define BTN_ANTERSS_LAST 5

namespace anteRSS
{
	class FeedToolbar
	{
	private:
		HINSTANCE hInst;
		HWND toolbarControl;
		HIMAGELIST imageList;

		// indices
		int imageNew;
		int imageUpdate;
		int imageUpdateAll;
		int imageRemove;
		int imageAllRead;

		anteRSSParser::RSSManager * manager;
		FeedListControl * feed;
		ItemListControl * item;
	public:
		FeedToolbar(HINSTANCE hInst, anteRSSParser::RSSManager * manager, FeedListControl * feed, ItemListControl * item);
		void CreateControl(HWND parent);
		void notifyResize();
		int notifyNotify(LPARAM lParam);
		RECT getDimensions();
	};

	// handler for the new feed dialog
	INT_PTR CALLBACK NewFeedDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
}