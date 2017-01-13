#include "stdafx.h"

#include "anteRSS.h"
#include "FeedListControl.h"
#include "resource.h"

#include <sstream>
#include <algorithm>
#include <unordered_set>

using namespace anteRSSParser;

namespace anteRSS
{

	void FeedListControl::createImageLists()
	{
		HICON hiconItem;     // Icon for list-view items.
		HIMAGELIST hLarge;   // Image list for icon view.
		HIMAGELIST hSmall;   // Image list for other views.

							 // Create the full-sized icon image lists. 
		hLarge = ImageList_Create(GetSystemMetrics(SM_CXICON),
			GetSystemMetrics(SM_CYICON),
			ILC_MASK, 3, 1);

		hSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON),
			GetSystemMetrics(SM_CYSMICON),
			ILC_MASK, 1, 1);

		// Add an icon to each image list.  
		hiconItem = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ANTERSS));

		imageRSS = ImageList_AddIcon(hLarge, hiconItem);
		ImageList_AddIcon(hSmall, hiconItem);

		DestroyIcon(hiconItem);

		hiconItem = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ITEMREAD));

		imageError = ImageList_AddIcon(hLarge, hiconItem);
		ImageList_AddIcon(hSmall, hiconItem);

		DestroyIcon(hiconItem);

		hiconItem = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ITEMUNREAD));

		imageUpdating = ImageList_AddIcon(hLarge, hiconItem);
		ImageList_AddIcon(hSmall, hiconItem);

		DestroyIcon(hiconItem);

		// When you are dealing with multiple icons, you can use the previous four lines of 
		// code inside a loop. The following code shows such a loop. The 
		// icons are defined in the application's header file as resources, which 
		// are numbered consecutively starting with IDS_FIRSTICON. The number of 
		// icons is defined in the header file as C_ICONS.
		/*
		for(index = 0; index < C_ICONS; index++)
		{
		hIconItem = LoadIcon (g_hinst, MAKEINTRESOURCE(IDS_FIRSTICON + index));
		ImageList_AddIcon(hSmall, hIconItem);
		ImageList_AddIcon(hLarge, hIconItem);
		Destroy(hIconItem);
		}
		*/

		// Assign the image lists to the list-view control. 
		ListView_SetImageList(listControl, hLarge, LVSIL_NORMAL);
		ListView_SetImageList(listControl, hSmall, LVSIL_SMALL);
	}

	void FeedListControl::createColumns()
	{
		WCHAR szText[256] = L"Feeds";     // Temporary buffer.
		LVCOLUMN lvc;
		int iCol = 0;

		// Initialize the LVCOLUMN structure.
		// The mask specifies that the format, width, text,
		// and subitem members of the structure are valid.
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

		lvc.iSubItem = iCol;
		lvc.pszText = szText;
		lvc.cx = 100;         // Width of column in pixels.

		lvc.fmt = LVCFMT_LEFT;  // Left-aligned column.

		// Insert the columns into the list view.
		ListView_InsertColumn(listControl, iCol, &lvc);
		ListView_SetColumnWidth(listControl, 0, LVSCW_AUTOSIZE_USEHEADER);
	}

	void updateSingleCallback(int feedid, bool success, RSSFeedItemVector newItem, void * data, std::string message)
	{
		void ** buf = (void **)data;

		FeedListControl * control = (FeedListControl *)buf[0];
		int select = *(int *)buf[1];

		if (!success)
		{
			PostMessage(GetParent(control->listControl), MSG_UPD_NOTIFY, feedid, -select);
		}
		else
		{
			PostMessage(GetParent(control->listControl), MSG_UPD_NOTIFY, feedid, select);
		}
	}

	void FeedListControl::updateSingleThread(RSSFeed feed, int select)
	{
		updateMutex.lock();

		void * data[2] = {this, &select};

		// now with callback, designated errors
		manager->updateFeed(feed.id, updateSingleCallback, data);

		updateMutex.unlock();
	}

	void updateAllCallback(int feedid, bool success, RSSFeedItemVector newItem, void * data, std::string message)
	{
		void ** buf = (void **)data;

		FeedListControl * control = (FeedListControl *) buf[0];
		bool notify = *(bool *)buf[1];

		// the last one, always successful
		if (feedid == 0)
		{
			if (notify && !control->newFeeds.empty())
			{
				PostMessage(GetParent(control->listControl), MSG_SHOW_NOTIFY, 0, 0);
			}
			control->feedStatus[0] = FeedStatus::NORMAL;
			control->notifyFeedListChanged();
			PostMessage(GetParent(control->listControl), MSG_ITEM_NOTIFY, 0, -3);
		}
		else
		{
			control->newFeeds.insert(control->newFeeds.end(), newItem.begin(), newItem.end());

			if (success)
			{
				control->feedStatus[feedid] = FeedStatus::NORMAL;
			}
			else
			{
				control->feedStatus[feedid] = FeedStatus::FAILED;
			}

			control->notifyFeedListItemChanged(feedid);
		}
	}

	void FeedListControl::updateAllThread(bool newNotify)
	{
		updateMutex.lock();
		// pointer hacks!
		void * data[2] = { this, &newNotify };
		manager->updateAll(updateAllCallback, data);
		updateMutex.unlock();
	}

	FeedListControl::FeedListControl(HINSTANCE hInst, anteRSSParser::RSSManager * manager)
	{
		this->hInst = hInst;
		this->manager = manager;
		this->prevUnread = false;
	}

	FeedListControl::~FeedListControl()
	{
		// essentially, wait for all threads to end
		updateMutex.lock();
		updateMutex.unlock();
	}

	void FeedListControl::CreateControl(HWND parent)
	{
		INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
		icex.dwICC = ICC_LISTVIEW_CLASSES;
		InitCommonControlsEx(&icex);

		RECT rcClient;                       // The parent window's client area.

		GetClientRect(parent, &rcClient);

		// Create the list-view window in report view with label editing enabled.
		listControl = CreateWindowEx(LVS_EX_DOUBLEBUFFER,
			WC_LISTVIEW,                // list view class
			L"",                         // no default text
			WS_VISIBLE | WS_CHILD | LVS_REPORT | WS_BORDER | LVS_NOCOLUMNHEADER |
			LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_EDITLABELS | LVS_OWNERDATA,
			0, 0,
			(rcClient.right - rcClient.left) / 5, rcClient.bottom - rcClient.top,
			parent,
			(HMENU)IDC_ANTERSS_RSSTREE,
			hInst,
			NULL);

		ListView_SetExtendedListViewStyleEx(listControl, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
		SetWindowTheme(listControl, TEXT("Explorer"), NULL);

		createImageLists();
		createColumns();

		notifyFeedListChanged();
	}

	void FeedListControl::notifyFeedListItemChanged(int feedid)
	{
		unreadPseudoFeed.id = 0;
		unreadPseudoFeed.name = "Unread";

		unreadPseudoFeed.unread = 0;
		int index = 3;
		for (RSSFeedVector::iterator it = feedCache.begin(); it != feedCache.end(); ++it, ++index)
		{
			unreadPseudoFeed.unread += it->unread;
			if (it->id == feedid)
			{
				ListView_Update(listControl, index);
				ListView_RedrawItems(listControl, index, index);
			}
		}

		ListView_Update(listControl, 2);
		ListView_RedrawItems(listControl, 2, 2);
		UpdateWindow(listControl);
	}

	void FeedListControl::notifyFeedListChanged()
	{
		feedCache = manager->getAllFeeds();
		unreadPseudoFeed.id = 0;
		unreadPseudoFeed.name = "Unread";

		unreadPseudoFeed.unread = 0;
		int index = 3;
		for (RSSFeedVector::iterator it = feedCache.begin(); it != feedCache.end(); ++it, ++index)
		{
			unreadPseudoFeed.unread += it->unread;
			ListView_Update(listControl, index);
		}

		// no unread
		if ((unreadPseudoFeed.unread > 0) != prevUnread)
		{
			PostMessage(GetParent(listControl), MSG_UNREAD, 0, unreadPseudoFeed.unread);
			prevUnread = (unreadPseudoFeed.unread > 0);
		}

		// notify change in content?
		ListView_SetItemCountEx(listControl, 3 + feedCache.size(), LVSICF_NOSCROLL);
		InvalidateRect(listControl, NULL, false);
	}

	void FeedListControl::notifyResize(RECT rect)
	{
		MoveWindow(listControl, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, true);
		ListView_SetColumnWidth(listControl, 0, LVSCW_AUTOSIZE_USEHEADER);
	}

	int FeedListControl::notifyNotify(LPARAM lParam)
	{
		// the nmhdr
		LPNMHDR source = (LPNMHDR)lParam;

		// first, check if it is from this control
		if (source->hwndFrom != listControl)
			return 0;

		switch (source->code)
		{
		case NM_CUSTOMDRAW:
		{
			LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW) lParam;
			RSSFeed feed;
			int index;

			switch (lplvcd->nmcd.dwDrawStage)
			{
				case CDDS_PREPAINT:
					return CDRF_NOTIFYITEMDRAW;
				case CDDS_ITEMPREPAINT:
					index = lplvcd->nmcd.dwItemSpec;
					if (index >= 3)
					{
						feed = feedCache.at(index - 3);
						if (feed.unread > 0)
							lplvcd->clrText = RGB(0, 0, 255);
					}
					return CDRF_NEWFONT;
				//There would be some bits here for subitem drawing but they don't seem neccesary as you seem to want a full row color only
				case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
					return CDRF_NEWFONT;
			}

			return TRUE;
		}
		case LVN_GETDISPINFO:
		{
			NMLVDISPINFO* plvdi = (NMLVDISPINFO*) source;
			int index = plvdi->item.iItem;
			RSSFeed feed;

			// an actual feed
			if (index >= 3)
			{
				feed = feedCache.at(index - 3);
			}
			// archived
			else if (index == 2)
			{
				feed.id = 0;
				feed.name = "Archived";
				feed.unread = 0;
			}
			// Unread
			else if (index == 1)
			{
				feed = unreadPseudoFeed;
			}
			// All
			else if (index == 0)
			{
				feed.id = 0;
				feed.name = "All";
				feed.unread = 0;
			}

			if (plvdi->item.mask & LVIF_IMAGE)
			{
				switch (feedStatus[feed.id])
				{
				case NORMAL:
					plvdi->item.iImage = imageRSS;
					break;
				case FAILED:
					plvdi->item.iImage = imageError;
					break;
				case UPDATING:
					plvdi->item.iImage = imageUpdating;
					break;
				default:
					plvdi->item.iImage = imageRSS;
					break;
				}
			}

			if (plvdi->item.mask & LVIF_TEXT)
			{
				std::wstringstream str;
				str << convertToWide(feed.name) << L" (" << feed.unread << L")";
				
				// TODO dynamic allocation
				StringCchCopy(plvdi->item.pszText, 256, str.str().c_str());
			}

			break;
		}
		case LVN_ITEMCHANGED:
		{
			LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;
			if (pnmv->uNewState & LVIS_SELECTED)
			{
				if (pnmv->iItem < 3)
					PostMessage(GetParent(listControl), MSG_ITEM_NOTIFY, 0, -pnmv->iItem);
				else
				{
					int id = feedCache.at(pnmv->iItem - 3).id;
					PostMessage(GetParent(listControl), MSG_ITEM_NOTIFY, 0, id);
				}
			}
			break;
		}
		case NM_CLICK:
		{
			LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)lParam;
			// Only update when it is not handled by LVN_ITEMCHANGED
			if(ListView_GetItemState(listControl, lpnmitem->iItem, LVIS_FOCUSED | LVIS_SELECTED) & (LVIS_FOCUSED | LVIS_SELECTED))
				PostMessage(GetParent(listControl), MSG_ITEM_NOTIFY, 0, -3);

			break;
		}
		case LVN_BEGINLABELEDIT:
		{
			NMLVDISPINFO * pdi = (NMLVDISPINFO *)lParam;
			// all and unread
			if (pdi->item.iItem < 3)
				return 1;
			else
			{
				HWND editControl = ListView_GetEditControl(listControl);
				std::string name = feedCache.at(pdi->item.iItem - 3).name;
				Edit_SetText(editControl, convertToWide(name).c_str());
				return 0;
			}
			break;
		}
		case LVN_ENDLABELEDIT:
		{
			NMLVDISPINFO * pdi = (NMLVDISPINFO *)lParam;
			if (pdi->item.pszText != NULL)
			{
				RSSFeed * feed = &feedCache[pdi->item.iItem - 3];

				manager->renameFeed(feed->id, convertToUtf8(pdi->item.pszText));

				notifyFeedListItemChanged(feed->id);

				// "did not accept" so that it would not overwrite changes by notifyFeedListChanged();
				return 0;
			}
			else
			{
				return 0;
			}
			break;
		}
		default:
			break;
		}

		return 0;
	}

	// Returns the FeedListControl's selected feed if a specific feed, else nullptr
	anteRSSParser::RSSFeed * FeedListControl::getSelectedFeed()
	{
		// Get the first selected item
		int iPos = getSelectedIndex();
		if (iPos > 2) {
			return &(*(feedCache.begin() + (iPos - 3)));
		}

		return nullptr;
	}

	int FeedListControl::getSelectedIndex()
	{
		return ListView_GetNextItem(listControl, -1, LVNI_SELECTED);
	}

	int FeedListControl::getIndexFromId(int id)
	{
		int i = 0;
		for (RSSFeedVector::iterator it = feedCache.begin(); it != feedCache.end(); ++it, ++i)
		{
			if (it->id == id)
				return i + 3;
		}

		return 0;
	}

	void FeedListControl::setSelected(int index)
	{
		ListView_SetItemState(listControl, index, LVIS_FOCUSED | LVIS_SELECTED, 0x000F);                     
	}

	void FeedListControl::updateNotify(UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == MSG_UPD_NOTIFY)
		{
			int listIndex = lParam;
			int feedId = wParam;

			// assuming that the feed list is always sorted
			// this also changes the itemlist, as this sends a change in selection message
			if (listIndex > 0)
			{
				setSelected(listIndex);
				//changeIcon(listIndex, imageRSS);
				//idLoading.erase(feedId);
				feedStatus[feedId] = FeedStatus::NORMAL;
			}
			else
			{
				// TODO this seems to not make the correct image
				setSelected(-listIndex);
				//changeIcon(-listIndex, imageError);
				feedStatus[feedId] = FeedStatus::FAILED;
			}

			notifyFeedListItemChanged(feedId);
		}
	}

	void FeedListControl::updateSelected()
	{
		RSSFeed * feed = getSelectedFeed();
		int select = getSelectedIndex();

		if (feed && feedStatus[feed->id] != FeedStatus::UPDATING && feedStatus[0] != FeedStatus::UPDATING)
		{
			std::wstringstream str;
			str << "To update: " << feed->id << std::endl;
			OutputDebugString(str.str().c_str());

			feedStatus[feed->id] = FeedStatus::UPDATING;
			notifyFeedListItemChanged(feed->id);

			std::thread thread(&FeedListControl::updateSingleThread, this, *feed, select);
			thread.detach();
		}
	}

	void FeedListControl::removeSelected()
	{
		RSSFeed * feed = getSelectedFeed();
		if (feed)
		{
			manager->removeFeed(feed->id);
			notifyFeedListChanged();
		}
	}

	void FeedListControl::updateAll(bool newNotify)
	{
		// it is already happening
		if (feedStatus[0] == FeedStatus::UPDATING)
			return;

		// empty previous newFeeds
		newFeeds.clear();

		feedStatus[0] = FeedStatus::UPDATING;

		RSSFeedVector all = manager->getAllFeeds();
		for (RSSFeedVector::iterator it = all.begin(); it != all.end(); ++it)
		{
			feedStatus[it->id] = FeedStatus::UPDATING;
		}

		notifyFeedListChanged();

		std::thread thread(&FeedListControl::updateAllThread, this, newNotify);
		thread.detach();
	}

	std::wstring FeedListControl::getNotificationTitle()
	{
		return L"anteRSS";
	}

	std::wstring FeedListControl::getNotificationContent()
	{
		std::wstringstream str;

		// completely arbitrary
		if (newFeeds.size() > 3)
		{
			str << newFeeds.size() << " new items received, from ";
			std::unordered_set<int> sources;
			for (RSSFeedItemVector::iterator it = newFeeds.begin(); it != newFeeds.end(); ++it)
			{
				if (sources.find(it->feedid) == sources.end())
				{
					sources.insert(it->feedid);
					RSSFeed feed = manager->getFeed(it->feedid);
					str << convertToWide(feed.name) << "; ";
				}
			}
		}
		else
		{
			str << "New item(s):";
			for (RSSFeedItemVector::iterator it = newFeeds.begin(); it != newFeeds.end(); ++it)
			{
				str << std::endl << convertToWide(it->title);
			}
		}

		return str.str();
	}

}
