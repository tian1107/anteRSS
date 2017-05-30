#include "MainWindow.h"

inline System::Void anteRSScplusnet::MainWindow::listFeedList_Resize(System::Object ^ sender, System::EventArgs ^ e) {
	columnFeedList->Width = -2;	// fill
}

inline System::Void anteRSScplusnet::MainWindow::listFeedList_ColumnWidthChanging(System::Object ^ sender, System::Windows::Forms::ColumnWidthChangingEventArgs ^ e) {
	e->Cancel = true;
	e->NewWidth = -2;
}
