#include "stdafx.h"

#include "anteRSS.h"
#include "ItemListControl.h"
#include "resource.h"

#include <ShlObj.h>

#include <sstream>
#include <algorithm>

using namespace anteRSSParser;

namespace anteRSS
{
	void ItemListControl::createImageLists()
	{
		HICON hiconItem;     // Icon for list-view items.
		HIMAGELIST hLarge;   // Image list for icon view.
		HIMAGELIST hSmall;   // Image list for other views.

							 // Create the full-sized icon image lists. 
		hLarge = ImageList_Create(GetSystemMetrics(SM_CXICON),
			GetSystemMetrics(SM_CYICON),
			ILC_MASK, 1, 1);

		hSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON),
			GetSystemMetrics(SM_CYSMICON),
			ILC_MASK, 1, 1);

		// Add an icon to each image list.  
		hiconItem = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ITEMREAD));

		imageRead = ImageList_AddIcon(hLarge, hiconItem);
		ImageList_AddIcon(hSmall, hiconItem);

		DestroyIcon(hiconItem);

		hiconItem = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ITEMUNREAD));

		imageUnread = ImageList_AddIcon(hLarge, hiconItem);
		ImageList_AddIcon(hSmall, hiconItem);

		DestroyIcon(hiconItem);

		// Assign the image lists to the list-view control. 
		ListView_SetImageList(listControl, hLarge, LVSIL_NORMAL);
		ListView_SetImageList(listControl, hSmall, LVSIL_SMALL);
	}

	void ItemListControl::createColumns()
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

	int ItemListControl::insertRow(int index, RSSFeedItem * item)
	{
		// TODO dynamic allocation
		const size_t length = 256;

		LVITEM lvI;
		wchar_t buf[length];

		// Initialize LVITEM members that are common to all items.
		lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_PARAM;
		lvI.stateMask = 0;
		lvI.iSubItem = 0;
		lvI.state = 0;
		switch (item->status)
		{
		case 0:
			lvI.iImage = imageUnread;
			break;
		case 1:
			lvI.iImage = imageRead;
			break;
		case 2:
			lvI.iImage = imageArchived;
			break;
		default:
			lvI.iImage = imageUnread;
		}
		lvI.iItem = index;
		lvI.lParam = (LPARAM)item;

		StringCchCopy(buf, length, convertToWide(item->title).c_str());
		lvI.pszText = buf;

		int result = ListView_InsertItem(listControl, &lvI);
		ListView_SetColumnWidth(listControl, 0, LVSCW_AUTOSIZE_USEHEADER);
		return result;
	}

	void ItemListControl::changeIcon(int index, int imageIndex)
	{
		LVITEM lvI;
		lvI.mask = LVIF_IMAGE;
		lvI.iImage = imageIndex;
		lvI.iItem = index;

		ListView_SetItem(listControl, &lvI);
	}

	ItemListControl::ItemListControl(HINSTANCE hInst, ItemDescControl * descControl, anteRSSParser::RSSManager * manager)
	{
		this->hInst = hInst;
		this->manager = manager;
		this->descControl = descControl;
	}

	void ItemListControl::CreateControl(HWND parent)
	{
		INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
		icex.dwICC = ICC_LISTVIEW_CLASSES;
		InitCommonControlsEx(&icex);

		RECT rcClient;                       // The parent window's client area.

		GetClientRect(parent, &rcClient);

		// Create the list-view window in report view with label editing enabled.
		listControl = CreateWindowEx(WS_EX_TRANSPARENT,
			WC_LISTVIEW,                // list view class
			L"",                         // no default text
			WS_VISIBLE | WS_CHILD | LVS_REPORT | WS_BORDER | LVS_NOCOLUMNHEADER |
			LVS_SINGLESEL,
			(rcClient.right - rcClient.left) / 5, 0,
			(rcClient.right - rcClient.left) - (rcClient.right - rcClient.left) / 5, (rcClient.bottom - rcClient.top)/2,
			parent,
			(HMENU)IDC_ANTERSS_RSSITEM,
			hInst,
			NULL);

		ListView_SetExtendedListViewStyleEx(listControl, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
		SetWindowTheme(listControl, TEXT("Explorer"), NULL);

		createImageLists();
		createColumns();

		notifyItemListChanged(-1);
	}

	void ItemListControl::notifyItemListChanged(int feedId)
	{
		// means all of it
		if (feedId == 0)
		{
			// TODO do something
		}
		// means all the unread
		else if (feedId == -1)
		{
			itemCache = manager->getItemsOfStatus(0);
		}
		// means all of the archived
		else if (feedId == -2)
		{
			itemCache = manager->getItemsOfStatus(2);
		}
		else
			itemCache = manager->getItemsOfFeed(feedId);

		ListView_DeleteAllItems(listControl);

		int index = 0;
		for (RSSFeedItemVector::iterator it = itemCache.begin(); it != itemCache.end(); ++it, ++index)
		{
			std::stringstream str;
			insertRow(index, &(*it));
		}
	}

	void ItemListControl::notifyResize(RECT rect)
	{
		MoveWindow(listControl, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, true);
		ListView_SetColumnWidth(listControl, 0, LVSCW_AUTOSIZE_USEHEADER);
	}

	void openThread(DownloadManager * dManager, std::string url)
	{
		std::string html = "text/html";

		std::string cType = dManager->getContentType(url);

		// if a webpage
		if (cType.compare(0, html.length(), html) == 0)
		{
			ShellExecute(NULL, L"open", convertToWide(url).c_str(), NULL, NULL, SW_SHOW);
		}
		else
		{
			// get downloads folder
			LPWSTR downloads;
			SHGetKnownFolderPath(FOLDERID_Downloads, 0, NULL, &downloads);

			std::string name = dManager->downloadToFolder(url, convertToUtf8(downloads));

			std::wstringstream location;
			location << downloads << L"\\" << convertToWide(name);
			
			// TODO check if executable
			ShellExecute(NULL, L"open", location.str().c_str(), NULL, NULL, SW_SHOW);
		}

	}

	int ItemListControl::notifyNotify(LPARAM lParam)
	{
		// the nmhdr
		LPNMHDR source = (LPNMHDR)lParam;

		// first, check if it is from this control
		if (source->hwndFrom != listControl)
			return 0;

		switch (source->code)
		{
		// when an item is double clicked
		case NM_DBLCLK:
		{
			LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)lParam;
			if (lpnmitem->iItem >= 0)
			{
				LVITEM item;
				item.iItem = lpnmitem->iItem;
				item.iSubItem = 0;
				item.mask = LVIF_PARAM;

				ListView_GetItem(listControl, &item);

				RSSFeedItem * feedItem = (RSSFeedItem *) item.lParam;

				std::thread thread(openThread, &dManager, feedItem->link);
				thread.detach();
			}

			break;
		}
		// when selection changes
		case LVN_ITEMCHANGED:
		{
			LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;
			if (pnmv->uNewState & LVIS_SELECTED)
			{
				RSSFeedItem * item = (RSSFeedItem *)(pnmv->lParam);

				if (item->status == 0)
				{
					item->status = 1;
					manager->markStatus(item->guid, 1);
					PostMessage(GetParent(listControl), MSG_LIST_NOTIFY, 0, 0);
					changeIcon(pnmv->iItem, imageRead);
				}

				descControl->setText(convertToWide(item->description));
			}
			break;
		}
		// disable editing
		case LVN_BEGINLABELEDIT:
			return 1;
			break;
		default:
			break;
		}

		return 0;
	}

}
