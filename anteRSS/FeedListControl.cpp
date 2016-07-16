#include "stdafx.h"

#include "FeedListControl.h"
#include "resource.h"

#include <sstream>

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
			ILC_MASK, 1, 1);

		hSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON),
			GetSystemMetrics(SM_CYSMICON),
			ILC_MASK, 1, 1);

		// Add an icon to each image list.  
		hiconItem = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ANTERSS));

		imageRSS = ImageList_AddIcon(hLarge, hiconItem);
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

	int FeedListControl::insertRow(int imageIndex, int index, std::wstring text)
	{
		// TODO dynamic allocation
		const size_t length = 256;

		LVITEM lvI;
		wchar_t buf[length];

		// Initialize LVITEM members that are common to all items.
		lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
		lvI.stateMask = 0;
		lvI.iSubItem = 0;
		lvI.state = 0;
		lvI.iImage = imageIndex;
		lvI.iItem = index;

		StringCchCopy(buf, length, text.c_str());
		lvI.pszText = buf;

		return ListView_InsertItem(listControl, &lvI);
	}

	FeedListControl::FeedListControl(HINSTANCE hInst, anteRSSParser::RSSManager * manager)
	{
		this->hInst = hInst;
		this->manager = manager;
	}

	void FeedListControl::CreateControl(HWND parent)
	{
		INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
		icex.dwICC = ICC_LISTVIEW_CLASSES;
		InitCommonControlsEx(&icex);

		RECT rcClient;                       // The parent window's client area.

		GetClientRect(parent, &rcClient);

		// Create the list-view window in report view with label editing enabled.
		listControl = CreateWindowEx(0L,
			WC_LISTVIEW,                // list view class
			L"",                         // no default text
			WS_VISIBLE | WS_CHILD | LVS_REPORT | WS_BORDER | LVS_NOCOLUMNHEADER |
			LVS_SINGLESEL | WS_EX_CLIENTEDGE,
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

	void FeedListControl::notifyFeedListChanged()
	{
		insertRow(imageRSS, 0, L"All");
		insertRow(imageRSS, 1, L"Unread");
		insertRow(imageRSS, 2, L"feed1");
	}

	void FeedListControl::notifyResize(LPARAM lParam)
	{
		int width = LOWORD(lParam);
		int height = HIWORD(lParam);

		MoveWindow(listControl, 0, 0, width / 5, height, true);
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
		case LVN_ITEMCHANGED:
		{
			LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;
			if (pnmv->uNewState & LVIS_SELECTED)
			{
				std::wstringstream str;

				str << "new selection! " << pnmv->iItem << std::endl;

				OutputDebugString(str.str().c_str());
			}
			break;
		}
		case LVN_BEGINLABELEDIT:
		{
			NMLVDISPINFO * pdi = (NMLVDISPINFO *)lParam;
			// all and unread
			if (pdi->item.iItem < 2)
				return 1;
			else
				return 0;
			break;
		}
		case LVN_ENDLABELEDIT:
		{
			NMLVDISPINFO * pdi = (NMLVDISPINFO *)lParam;
			if (pdi->item.pszText != NULL)
			{
				// TODO handle renaming

				// you can change the text! (keep the unread count)
				pdi->item.pszText = L"can't edit this!";

				return TRUE;
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

}
