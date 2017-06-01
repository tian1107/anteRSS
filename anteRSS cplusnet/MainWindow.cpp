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

System::Void anteRSScplusnet::MainWindow::browserFeedItemDesc_changeDescription(System::Int32 selectedIndex)
{
	browserFeedItemDesc->Navigate("about:blank");
	if (browserFeedItemDesc->Document != nullptr)
	{
		browserFeedItemDesc->Document->Write("");
	}

	browserFeedItemDesc->DocumentText = "" + selectedIndex;
}

inline System::Void anteRSScplusnet::MainWindow::MainWindow_Load(System::Object ^ sender, System::EventArgs ^ e) {
	// make lists better
	// though still requires winapi
	SetWindowTheme(static_cast<HWND>(listFeedList->Handle.ToPointer()), TEXT("Explorer"), NULL);
	SetWindowTheme(static_cast<HWND>(listFeedItem->Handle.ToPointer()), TEXT("Explorer"), NULL);
	
	// fill up feed list
	listFeedList_UpdateList();

#ifndef NDEBUG
	// debug button thing
	ToolStripButton ^ buttonDebug = gcnew ToolStripButton("debug button");
	buttonDebug->Click += gcnew System::EventHandler(this, &MainWindow::buttonDebug_Click);
	topBar->Items->Add(buttonDebug);
#endif
}

#ifndef NDEBUG
System::Void anteRSScplusnet::MainWindow::buttonDebug_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	listFeedItem->VirtualListSize++;
	return System::Void();
}
#endif

inline System::Void anteRSScplusnet::MainWindow::listFeedItem_RetrieveVirtualItem(System::Object ^ sender, System::Windows::Forms::RetrieveVirtualItemEventArgs ^ e) {
	array<System::String ^>^ row = gcnew array<System::String ^>(listFeedItem->Columns->Count);

	row[0] = "";
	row[1] = "test1";
	row[2] = "test2" + e->ItemIndex;

	e->Item = gcnew ListViewItem(row, 0);
}



inline System::Void anteRSScplusnet::MainWindow::listFeedItem_ItemActivate(System::Object ^ sender, System::EventArgs ^ e) {
	browserFeedItemDesc_changeDescription(listFeedItem->SelectedIndices[0]);
}

inline System::Void anteRSScplusnet::MainWindow::listFeedItem_ItemSelectionChanged(System::Object ^ sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs ^ e) {
	if (e->IsSelected)
	{
		browserFeedItemDesc_changeDescription(e->ItemIndex);
	}
}
