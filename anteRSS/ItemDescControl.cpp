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
		default:
			break;
		}

		return 0;
	}

	void ItemDescControl::notifyResize(RECT rect)
	{
		MoveWindow(syslink, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, true);
	}

	void ItemDescControl::notifyCommand(WPARAM wParam, LPARAM lParam)
	{
		int wmId = LOWORD(wParam);
		int code = HIWORD(wParam);

		if (wmId != IDC_ANTERSS_RSSDESC)
			return;

		switch (code)
		{
		case WEBFN_CLICKED:
		{
			const wchar_t * url = WebformLastClick(syslink);
			ShellExecute(NULL, L"open", url, NULL, NULL, SW_SHOW);
			break;
		}
		default:

			break;
		}
	}

	void ItemDescControl::setText(std::wstring text)
	{
		WebformReady(syslink);
		WebformSet(syslink, text.c_str());
		WebformGo(syslink, 0);
	}

}
