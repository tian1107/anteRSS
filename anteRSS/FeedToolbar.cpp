#include "stdafx.h"
#include "resource.h"

#include "FeedToolbar.h"

namespace anteRSS
{

	FeedToolbar::FeedToolbar(HINSTANCE hInst, anteRSSParser::RSSManager * manager)
	{
		this->hInst = hInst;
		this->manager = manager;
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
			{ MAKELONG(imageNew,  ImageListID),      0, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, (INT_PTR)L"New" },
			{ MAKELONG(imageUpdate, ImageListID),    1, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, (INT_PTR)L"Update" },
			{ MAKELONG(imageUpdateAll, ImageListID), 2, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, (INT_PTR)L"Update All" },
			{ MAKELONG(imageRemove, ImageListID),    3, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, (INT_PTR)L"Remove" }
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

	RECT FeedToolbar::getDimensions()
	{
		RECT result;
		GetWindowRect(toolbarControl, &result);
		return result;
	}

}
