#pragma once
#include "anteRSSParser\anteRSSParser.h"
#include "FeedListControl.h"
#include "ItemListControl.h"
#include <mutex>

#define BTN_ANTERSS_NEW 0
#define BTN_ANTERSS_UPD 1
#define BTN_ANTERSS_ALL 2
#define BTN_ANTERSS_REM 3

namespace anteRSS
{
	class FeedToolbar
	{
	private:
		HINSTANCE hInst;
		HWND toolbarControl;
		HIMAGELIST imageList;
		std::mutex updateMutex;

		// indices
		int imageNew;
		int imageUpdate;
		int imageUpdateAll;
		int imageRemove;

		anteRSSParser::RSSManager * manager;
		FeedListControl * feed;
		ItemListControl * item;
		void updateSingleThread();
	public:
		FeedToolbar(HINSTANCE hInst, anteRSSParser::RSSManager * manager, FeedListControl * feed, ItemListControl * item);
		void CreateControl(HWND parent);
		void notifyResize();
		int notifyNotify(LPARAM lParam);
		void updateNotify(UINT message, WPARAM wParam, LPARAM lParam);
		RECT getDimensions();
	};
}