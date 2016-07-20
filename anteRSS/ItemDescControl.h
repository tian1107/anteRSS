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
		void notifyResize(RECT rect);
		void setText(std::wstring text);
	};
}