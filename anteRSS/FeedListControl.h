#pragma once
#include "anteRSSParser\anteRSSParser.h"
#include <unordered_set>
#include <mutex>

namespace anteRSS
{
	class FeedListControl
	{
		friend class FeedToolbar;
	private:
		// window stuff
		HINSTANCE hInst;
		HWND listControl;

		// rss stuff
		anteRSSParser::RSSManager * manager;
		anteRSSParser::RSSFeedVector feedCache;
		std::wstring editBuffer;
		std::mutex updateMutex;

		// indices
		int imageRSS;
		int imageUpdating;
		int imageError;

		// markers
		std::unordered_set<int> idLoading;

		// functions
		void createImageLists();
		void createColumns();
		int insertRow(int imageIndex, int index, std::wstring text, anteRSSParser::RSSFeed * feed);
		void changeIcon(int index, int imageIndex);
		void updateSingleThread(anteRSSParser::RSSFeed feed, int select);
		void updateAllThread();
	public:
		FeedListControl(HINSTANCE hInst, anteRSSParser::RSSManager * manager);
		void CreateControl(HWND parent);
		void notifyFeedListChanged();
		void notifyResize(RECT rect);
		int notifyNotify(LPARAM lParam);
		anteRSSParser::RSSFeed * getSelectedFeed();
		int getSelectedIndex();
		void setSelected(int index);
		void updateNotify(UINT message, WPARAM wParam, LPARAM lParam);
		void updateSelected();
		void updateAll();
	};
}