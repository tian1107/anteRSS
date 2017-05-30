#include "MainWindow.h"

#include "RSSManagerWrapper.h"

#include <vcclr.h>

using namespace System;
using namespace System::Windows::Forms;

gcroot<anteRSScplusnet::RSSManagerWrapper^> manager;

void InitRSSManager();

[STAThread]
int main(array<String^>^args)
{
	InitRSSManager();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	anteRSScplusnet::MainWindow mainWindow(manager);

	Application::Run(%mainWindow);

	return 0;
}

void InitRSSManager()
{
	manager = gcnew anteRSScplusnet::RSSManagerWrapper("history.db");
	manager->updateFeedListCache();
}