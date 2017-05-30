#include "MainWindow.h"

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
}

System::Void anteRSScplusnet::MainWindow::listFeedList_UpdateList()
{
	listFeedList->VirtualListSize = manager->getFeedListCacheLength();
	return System::Void();
}

inline System::Void anteRSScplusnet::MainWindow::MainWindow_Load(System::Object ^ sender, System::EventArgs ^ e) {
	listFeedList_UpdateList();
	columnFeedList->Width = listFeedList->ClientSize.Width - 1;
}
