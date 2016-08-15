#pragma once


namespace anteRSS
{
	class ItemDescControl
	{
	private:
		HINSTANCE hInst;
		HWND syslink;
	public:
		ItemDescControl(HINSTANCE hInst);
		void CreateControl(HWND parent);
		int notifyNotify(LPARAM lParam);
		void notifyResize(RECT rect);
		void notifyCommand(WPARAM wParam, LPARAM lParam);
		void setText(std::wstring text);
	};
}