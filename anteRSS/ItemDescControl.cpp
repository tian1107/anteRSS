#include "stdafx.h"

#include "resource.h"
#include "ItemDescControl.h"
#include "webform.h"

namespace anteRSS
{

	ItemDescControl::ItemDescControl(HINSTANCE hInst)
	{
		this->hInst = hInst;
	}

	void ItemDescControl::CreateControl(HWND parent)
	{
		syslink = CreateWindowEx(0, WEBFORM_CLASS, _T(""),
			WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | WS_VSCROLL | WS_BORDER,
			0, 0, 100, 100, parent, (HMENU)IDC_ANTERSS_RSSDESC, hInst, 0);
		WebformReady(syslink);
		WebformSet(syslink, L"nothing yet");
		WebformGo(syslink, 0);
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
		WebformReady(syslink);
		WebformSet(syslink, text.c_str());
		WebformGo(syslink, 0);
	}

}
