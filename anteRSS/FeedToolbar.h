#pragma once
#include "anteRSSParser\anteRSSParser.h"

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

		// indices
		int imageNew;
		int imageUpdate;
		int imageUpdateAll;
		int imageRemove;

		anteRSSParser::RSSManager * manager;
	public:
		FeedToolbar(HINSTANCE hInst, anteRSSParser::RSSManager * manager);
		void CreateControl(HWND parent);
		void notifyResize();
		int notifyNotify(LPARAM lParam);
		RECT getDimensions();
	};
}