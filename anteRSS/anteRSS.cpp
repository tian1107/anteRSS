// anteRSS.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "anteRSS.h"
#include "anteRSSParser\anteRSSParser.h"
#include "FeedListControl.h"
#include "ItemListControl.h"
#include "FeedToolbar.h"

using namespace anteRSSParser;
using namespace anteRSS;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
NOTIFYICONDATA niData = { 0 };					// the tray icon data

// rss stuff
RSSManager * manager = nullptr;

// window stuff
HWND hWndMain;
FeedListControl * rssTree;
ItemListControl * rssItem;
FeedToolbar * toolbar;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// memory leak check
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// initialize curl
	curl_global_init(CURL_GLOBAL_ALL);

	// initialize rss
	manager = new RSSManager("history.db");

	// initialize controls
	rssTree = new FeedListControl(hInstance, manager);
	rssItem = new ItemListControl(hInstance, manager);
	toolbar = new FeedToolbar(hInstance, manager, rssTree, rssItem);

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_ANTERSS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ANTERSS));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	delete manager;
	delete toolbar;
	delete rssItem;
	delete rssTree;

	// destroy curl
	curl_global_cleanup();

	return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ANTERSS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ANTERSS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	hWndMain = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, HWND_MESSAGE, nullptr, hInstance, nullptr);

	if (!hWndMain)
	{
		return FALSE;
	}

	// create shell icon
	niData.cbSize = sizeof(niData);
	niData.hWnd = hWndMain;
	niData.uFlags = NIF_ICON | NIF_TIP | NIF_GUID | NIF_MESSAGE | NIF_SHOWTIP;

#ifdef _DEBUG
	// {ECD20B38-A984-47EB-8F48-54517C7ABCEB}
	static const GUID iconGuid =
	{ 0xecd20b38, 0xa984, 0x47eb,{ 0x8f, 0x48, 0x54, 0x51, 0x7c, 0x7a, 0xbc, 0xeb } };
#else
	// {2A6D05DC-0E5D-4FC6-AA5C-9C0B583F0CBF}
	static const GUID iconGuid =
	{ 0x2a6d05dc, 0xe5d, 0x4fc6,{ 0xaa, 0x5c, 0x9c, 0xb, 0x58, 0x3f, 0xc, 0xbf } };
#endif

	niData.guidItem = iconGuid;
	niData.uCallbackMessage = MSG_TRAY_ICON;
	niData.uVersion = NOTIFYICON_VERSION_4;

	StringCchCopy(niData.szTip, ARRAYSIZE(niData.szTip), TEXT("anteRSS"));

	LoadIconMetric(hInst, MAKEINTRESOURCE(IDI_SMALL), LIM_SMALL, &(niData.hIcon));

	Shell_NotifyIcon(NIM_ADD, &niData) ? S_OK : E_FAIL;
	Shell_NotifyIcon(NIM_SETVERSION, &niData);

	//ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWndMain);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case MSG_UPD_NOTIFY:
		toolbar->updateNotify(message, wParam, lParam);
		break;
	case MSG_ITEM_NOTIFY:
		rssItem->notifyItemListChanged((int) lParam);
		break;
	case MSG_LIST_NOTIFY:
		rssTree->notifyFeedListChanged(true);
		break;
	case WM_SIZE:
		toolbar->notifyResize();

		RECT windowRect, toolbarRect;
		GetClientRect(hWndMain, &windowRect);
		toolbarRect = toolbar->getDimensions();

		RECT treeRect;
		treeRect.top = windowRect.top + toolbarRect.bottom - toolbarRect.top;
		treeRect.bottom = windowRect.bottom;
		treeRect.left = windowRect.left;
		treeRect.right = (windowRect.right - windowRect.left) / 5;

		RECT itemRect;
		itemRect.top = windowRect.top + toolbarRect.bottom - toolbarRect.top;
		itemRect.bottom = (itemRect.top + windowRect.bottom) / 2;	// what?! average?
		itemRect.left = (windowRect.right - windowRect.left) / 5;
		itemRect.right = windowRect.right;

		rssTree->notifyResize(treeRect);
		rssItem->notifyResize(itemRect);
		break;
	case WM_NOTIFY:
	{
		return rssTree->notifyNotify(lParam) + rssItem->notifyNotify(lParam) + toolbar->notifyNotify(lParam);
		break;
	}
	case WM_CREATE:
	{
		toolbar->CreateControl(hWnd);
		rssTree->CreateControl(hWnd);
		rssItem->CreateControl(hWnd);
		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
		{
			niData.uFlags |= NIF_INFO;
			niData.dwInfoFlags = NIIF_INFO;

			HRESULT hr = StringCchCopy(niData.szInfo,
				ARRAYSIZE(niData.szInfo),
				TEXT("Your message text goes here."));

			if (FAILED(hr))
			{
				// TODO: Write an error handler in case the call to StringCchCopy fails.
			}

			HRESULT hr2 = StringCchCopy(niData.szInfoTitle,
				ARRAYSIZE(niData.szInfoTitle),
				TEXT("anteRSS"));

			if (FAILED(hr2))
			{
				// TODO: Write an error handler in case the call to StringCchCopy fails.
			}

			Shell_NotifyIcon(NIM_MODIFY, &niData);

			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		}
		case ID_ANTERSS_TRAYEXIT:
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_ANTERSS_TRAYOPEN:
			if (IsWindowVisible(hWnd))
			{

			}
			else
			{
				SetParent(hWnd, nullptr);
				ShowWindow(hWnd, SW_SHOW);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_SYSCOMMAND:
		switch (wParam)
		{
		case SC_MINIMIZE:
			SetParent(hWnd, HWND_MESSAGE);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case MSG_TRAY_ICON:
		switch (LOWORD(lParam))
		{
		case WM_CONTEXTMENU:
		{
			int x = GET_X_LPARAM(wParam);
			int y = GET_Y_LPARAM(wParam);

			HMENU trayMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_TRAYMENU));
			trayMenu = GetSubMenu(trayMenu, 0);

			if (GetForegroundWindow() != hWnd)
				SetForegroundWindow(hWnd);
			TrackPopupMenu(trayMenu, TPM_LEFTBUTTON | TPM_NONOTIFY, x, y, 0, hWnd, NULL);
			PostMessage(hWnd, WM_NULL, 0, 0);
			break;
		}
		case NIN_POPUPOPEN:
			OutputDebugStringW(L"open event!\n");
			break;
		case NIN_SELECT:
			if (IsWindowVisible(hWnd))
			{

			}
			else
			{
				SetParent(hWnd, nullptr);
				ShowWindow(hWnd, SW_SHOW);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		DestroyIcon(niData.hIcon);
		Shell_NotifyIcon(NIM_DELETE, &niData);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}