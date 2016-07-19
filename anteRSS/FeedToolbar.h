#pragma once
#include "anteRSSParser\anteRSSParser.h"

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
		RECT getDimensions();
	};
}