#include "MainWindow.h"

#include <windows.h>

#include <vcclr.h>

using namespace System;
using namespace System::Windows::Forms;

gcroot<anteRSSParserWrapper::RSSManagerWrapper^> manager;

void InitRSSManager();

[STAThread]
#ifdef NDEBUG
int WINAPI CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
#else
int main(array<String^>^args)
#endif
{
	InitRSSManager();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(true);

	anteRSScplusnet::MainWindow mainWindow(manager);

	Application::Run(%mainWindow);

	return 0;
}

void InitRSSManager()
{
	manager = gcnew anteRSSParserWrapper::RSSManagerWrapper("history.db");
	manager->updateFeedListCache();
}