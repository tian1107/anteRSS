#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	anteRSScplusnet::MainWindow mainWindow;

	Application::Run(%mainWindow);

	return 0;
}