#pragma once
#include "anteRSSParser\anteRSSParser.h"
#include <unordered_map>
#include <mutex>

namespace anteRSS
{
	enum FeedStatus
	{
		NORMAL,
		UPDATING,
		FAILED
	};

	class FeedListControl
	{
		friend void updateAllCallback(int feedid, bool success, anteRSSParser::RSSFeedItemVector newItem, void * data, std::string message);
		friend void updateSingleCallback(int feedid, bool success, anteRSSParser::RSSFeedItemVector newItem, void * data, std::string message);
	private:
		// window stuff
		HINSTANCE hInst;
		HWND listControl;

		// rss stuff
		anteRSSParser::RSSManager * manager;
		anteRSSParser::RSSFeedVector feedCache;
		anteRSSParser::RSSFeed unreadPseudoFeed;
		anteRSSParser::RSSFeedItemVector newFeeds;
		std::wstring editBuffer;
		std::mutex updateMutex;

		// indices
		int imageRSS;
		int imageUpdating;
		int imageError;

		// markers
		std::unordered_map<int, FeedStatus> feedStatus;	// 0 ok 1 updating 2 error
		bool prevUnread;

		// functions
		void createImageLists();
		void createColumns();
		void updateSingleThread(anteRSSParser::RSSFeed feed, int select);
		void updateAllThread(bool newNotify);
	public:
		FeedListControl(HINSTANCE hInst, anteRSSParser::RSSManager * manager);
		~FeedListControl();
		void CreateControl(HWND parent);
		void notifyFeedListChanged();
		void notifyResize(RECT rect);
		int notifyNotify(LPARAM lParam);
		anteRSSParser::RSSFeed * getSelectedFeed();
		int getSelectedIndex();
		int getIndexFromId(int id);
		void setSelected(int index);
		void updateNotify(UINT message, WPARAM wParam, LPARAM lParam);
		void updateSelected();
		void removeSelected();
		void updateAll(bool newNotify);
		std::wstring getNotificationTitle();
		std::wstring getNotificationContent();
	};
}