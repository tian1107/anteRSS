#pragma once
#include "anteRSSParser\anteRSSParser.h"

namespace anteRSS
{
	class FeedListControl
	{
	private:
		HINSTANCE hInst;
		HWND listControl;
		anteRSSParser::RSSManager * manager;

		// indices
		int imageRSS;

		void createImageLists();
		void createColumns();
		int insertRow(int imageIndex, int index, std::wstring text);
	public:
		FeedListControl(HINSTANCE hInst, anteRSSParser::RSSManager * manager);
		void CreateControl(HWND parent);
		void notifyFeedListChanged();
		void notifyResize(LPARAM lParam);
		int notifyNotify(LPARAM lParam);
	};
}