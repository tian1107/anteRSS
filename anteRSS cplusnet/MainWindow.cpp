#include "MainWindow.h"

#include <Windows.h>
#include <Uxtheme.h>

inline System::Void anteRSScplusnet::MainWindow::listFeedList_Resize(System::Object ^ sender, System::EventArgs ^ e) {
	Control^ control = dynamic_cast<Control^>(sender);
	columnFeedList->Width = control->ClientSize.Width - 1;
}

inline System::Void anteRSScplusnet::MainWindow::listFeedList_ColumnWidthChanging(System::Object ^ sender, System::Windows::Forms::ColumnWidthChangingEventArgs ^ e) {
	e->Cancel = true;
	e->NewWidth = listFeedList->ClientSize.Width - 1;
}

inline System::Void anteRSScplusnet::MainWindow::listFeedList_RetrieveVirtualItem(System::Object ^ sender, System::Windows::Forms::RetrieveVirtualItemEventArgs ^ e) {
	e->Item = gcnew ListViewItem(manager->getFeedListCacheAt(e->ItemIndex)->Name);
	e->Item->ImageIndex = e->ItemIndex & 0x1;
}

System::Void anteRSScplusnet::MainWindow::listFeedList_UpdateList()
{
	listFeedList->VirtualListSize = manager->getFeedListCacheLength();
	return System::Void();
}

inline System::Void anteRSScplusnet::MainWindow::MainWindow_Load(System::Object ^ sender, System::EventArgs ^ e) {
	// make lists better
	// though still requires winapi
	SetWindowTheme(static_cast<HWND>(listFeedList->Handle.ToPointer()), TEXT("Explorer"), NULL);
	
	listFeedList_UpdateList();
}
