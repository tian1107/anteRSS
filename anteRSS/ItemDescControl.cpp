#include "stdafx.h"

#include "ItemDescControl.h"

namespace anteRSS
{

	ItemDescControl::ItemDescControl(HINSTANCE hInst)
	{
		this->hInst = hInst;
	}

	void ItemDescControl::CreateControl(HWND parent)
	{
		syslink = CreateWindowEx(WS_EX_TRANSPARENT, WC_LINK,
			L"For more information, <A HREF=\"http://www.microsoft.com\">click here</A> " \
			L"or <A ID=\"idInfo\">here</A>.",
			WS_VISIBLE | WS_CHILD | WS_TABSTOP,
			0, 0, 0, 0,
			parent, NULL, hInst, NULL);
	}

	int ItemDescControl::notifyNotify(LPARAM lParam)
	{
		// the nmhdr
		LPNMHDR source = (LPNMHDR)lParam;

		// first, check if it is from this control
		if (source->hwndFrom != syslink)
			return 0;

		switch (source->code)
		{
		case NM_CLICK:
		case NM_RETURN:
		{
			PNMLINK pNMLink = (PNMLINK)lParam;
			LITEM   item = pNMLink->item;

			ShellExecute(NULL, L"open", item.szUrl, NULL, NULL, SW_SHOW);

			break;
		}
		default:
			break;
		}

		return 0;
	}

	void ItemDescControl::notifyResize(RECT rect)
	{
		MoveWindow(syslink, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, true);
	}

	void ItemDescControl::setText(std::wstring text)
	{
		SetWindowText(syslink, text.c_str());
	}

}
