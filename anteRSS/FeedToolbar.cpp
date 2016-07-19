#include "stdafx.h"

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
		toolbarControl = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
			WS_CHILD | TBSTYLE_WRAPABLE, 0, 0, 0, 0,
			parent, NULL, hInst, NULL);

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
