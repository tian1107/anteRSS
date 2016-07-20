#include "stdafx.h"
#include "resource.h"
#include <sstream>

#include "anteRSS.h"
#include "FeedToolbar.h"

using namespace anteRSSParser;

namespace anteRSS
{

	FeedToolbar::FeedToolbar(HINSTANCE hInst, anteRSSParser::RSSManager * manager, FeedListControl * feed, ItemListControl * item)
	{
		this->hInst = hInst;
		this->manager = manager;
		this->feed = feed;
		this->item = item;
	}

	void FeedToolbar::CreateControl(HWND parent)
	{
		// Declare and initialize local constants.
		const int ImageListID = 0;
		const int numButtons = 4;
		const int bitmapSize = 16;
		HICON hiconItem;

		const DWORD buttonStyles = BTNS_AUTOSIZE;

		toolbarControl = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
			WS_CHILD | TBSTYLE_WRAPABLE | TBSTYLE_LIST, 0, 0, 0, 0,
			parent, NULL, hInst, NULL);

		// Create the image list.
		imageList = ImageList_Create(bitmapSize, bitmapSize,   // Dimensions of individual bitmaps.
			ILC_COLOR16 | ILC_MASK,   // Ensures transparent background.
			numButtons, 0);

		// Set the image list.
		SendMessage(toolbarControl, TB_SETIMAGELIST,
			(WPARAM)ImageListID,
			(LPARAM)imageList);

		// Load the button images.
		hiconItem = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ITEMREAD));
		imageNew = ImageList_AddIcon(imageList, hiconItem);
		DestroyIcon(hiconItem);

		hiconItem = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ITEMUNREAD));
		imageUpdate = ImageList_AddIcon(imageList, hiconItem);
		DestroyIcon(hiconItem);

		// Initialize button info.
		// IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.

		TBBUTTON tbButtons[numButtons] =
		{
			{ MAKELONG(imageNew,  ImageListID),      BTN_ANTERSS_NEW, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, (INT_PTR)L"New" },
			{ MAKELONG(imageUpdate, ImageListID),    BTN_ANTERSS_UPD, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, (INT_PTR)L"Update" },
			{ MAKELONG(imageUpdateAll, ImageListID), BTN_ANTERSS_ALL, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, (INT_PTR)L"Update All" },
			{ MAKELONG(imageRemove, ImageListID),    BTN_ANTERSS_REM, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, (INT_PTR)L"Remove" }
		};

		// Add buttons.
		SendMessage(toolbarControl, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
		SendMessage(toolbarControl, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)&tbButtons);

		SendMessage(toolbarControl, TB_AUTOSIZE, 0, 0);
		ShowWindow(toolbarControl, TRUE);
	}

	void FeedToolbar::notifyResize()
	{
		SendMessage(toolbarControl, TB_AUTOSIZE, 0, 0);
	}

	int FeedToolbar::notifyNotify(LPARAM lParam)
	{
		// the nmhdr
		LPNMHDR source = (LPNMHDR)lParam;

		// first, check if it is from this control
		if (source->hwndFrom != toolbarControl)
			return 0;

		switch (source->code)
		{
		case NM_CLICK:
		{
			LPNMMOUSE lpnm = (LPNMMOUSE)lParam;

			switch (lpnm->dwItemSpec)
			{
			case BTN_ANTERSS_UPD:
			{
				feed->updateSelected();
				break;
			}
			default:
				break;
			}
			break;
		}
		default:
			break;
		}

		return 0;
	}

	RECT FeedToolbar::getDimensions()
	{
		RECT result;
		GetWindowRect(toolbarControl, &result);
		return result;
	}

}
