#pragma once

namespace anteRSScplusnet {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(anteRSSParserWrapper::RSSManagerWrapper ^ manager)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->manager = manager;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^  listFeedList;
	protected:

	private: System::Windows::Forms::ListView^  listFeedItem;
	protected:

	private: System::Windows::Forms::ToolStrip^  topBar;
	private: System::Windows::Forms::StatusStrip^  statusBar;
	private: System::Windows::Forms::WebBrowser^  browserFeedItemDesc;


	private: System::Windows::Forms::SplitContainer^  splitVertical;
	private: System::Windows::Forms::SplitContainer^  splitHorizontal;


	private: System::Windows::Forms::ToolStripButton^  buttonNewFeed;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripButton^  buttonUpdateSelected;
	private: System::Windows::Forms::ToolStripButton^  buttonUpdateAll;
	private: System::Windows::Forms::ToolStripButton^  buttonRemoveFeed;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripButton^  buttonToggleArchive;
	private: System::Windows::Forms::ToolStripButton^  buttonMarkAllAsRead;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ColumnHeader^  columnFeedList;
	private: System::Windows::Forms::ImageList^  imageListFeeds;
	private: System::Windows::Forms::ColumnHeader^  columnFeedItemSource;
	private: System::Windows::Forms::ColumnHeader^  columnFeedItemTitle;
	private: System::Windows::Forms::ColumnHeader^  columnFeedItemImage;
	private: System::ComponentModel::IContainer^  components;








	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->listFeedList = (gcnew System::Windows::Forms::ListView());
			this->columnFeedList = (gcnew System::Windows::Forms::ColumnHeader());
			this->imageListFeeds = (gcnew System::Windows::Forms::ImageList(this->components));
			this->listFeedItem = (gcnew System::Windows::Forms::ListView());
			this->columnFeedItemImage = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnFeedItemSource = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnFeedItemTitle = (gcnew System::Windows::Forms::ColumnHeader());
			this->topBar = (gcnew System::Windows::Forms::ToolStrip());
			this->buttonNewFeed = (gcnew System::Windows::Forms::ToolStripButton());
			this->buttonRemoveFeed = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->buttonUpdateSelected = (gcnew System::Windows::Forms::ToolStripButton());
			this->buttonUpdateAll = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->buttonToggleArchive = (gcnew System::Windows::Forms::ToolStripButton());
			this->buttonMarkAllAsRead = (gcnew System::Windows::Forms::ToolStripButton());
			this->statusBar = (gcnew System::Windows::Forms::StatusStrip());
			this->browserFeedItemDesc = (gcnew System::Windows::Forms::WebBrowser());
			this->splitVertical = (gcnew System::Windows::Forms::SplitContainer());
			this->splitHorizontal = (gcnew System::Windows::Forms::SplitContainer());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->topBar->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitVertical))->BeginInit();
			this->splitVertical->Panel1->SuspendLayout();
			this->splitVertical->Panel2->SuspendLayout();
			this->splitVertical->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitHorizontal))->BeginInit();
			this->splitHorizontal->Panel1->SuspendLayout();
			this->splitHorizontal->Panel2->SuspendLayout();
			this->splitHorizontal->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// listFeedList
			// 
			this->listFeedList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->listFeedList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->columnFeedList });
			this->listFeedList->FullRowSelect = true;
			this->listFeedList->HideSelection = false;
			this->listFeedList->LabelEdit = true;
			this->listFeedList->Location = System::Drawing::Point(2, 4);
			this->listFeedList->Margin = System::Windows::Forms::Padding(2, 4, 2, 4);
			this->listFeedList->MultiSelect = false;
			this->listFeedList->Name = L"listFeedList";
			this->listFeedList->Size = System::Drawing::Size(189, 473);
			this->listFeedList->SmallImageList = this->imageListFeeds;
			this->listFeedList->TabIndex = 0;
			this->listFeedList->UseCompatibleStateImageBehavior = false;
			this->listFeedList->View = System::Windows::Forms::View::Details;
			this->listFeedList->VirtualMode = true;
			this->listFeedList->ColumnWidthChanging += gcnew System::Windows::Forms::ColumnWidthChangingEventHandler(this, &MainWindow::listFeedList_ColumnWidthChanging);
			this->listFeedList->RetrieveVirtualItem += gcnew System::Windows::Forms::RetrieveVirtualItemEventHandler(this, &MainWindow::listFeedList_RetrieveVirtualItem);
			this->listFeedList->Resize += gcnew System::EventHandler(this, &MainWindow::listFeedList_Resize);
			// 
			// columnFeedList
			// 
			this->columnFeedList->Text = L"Feeds";
			this->columnFeedList->Width = 186;
			// 
			// imageListFeeds
			// 
			this->imageListFeeds->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageListFeeds.ImageStream")));
			this->imageListFeeds->TransparentColor = System::Drawing::Color::Transparent;
			this->imageListFeeds->Images->SetKeyName(0, L"itemunread.ico");
			this->imageListFeeds->Images->SetKeyName(1, L"itemread.ico");
			// 
			// listFeedItem
			// 
			this->listFeedItem->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->listFeedItem->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnFeedItemImage,
					this->columnFeedItemSource, this->columnFeedItemTitle
			});
			this->listFeedItem->FullRowSelect = true;
			this->listFeedItem->GridLines = true;
			this->listFeedItem->HideSelection = false;
			this->listFeedItem->Location = System::Drawing::Point(0, 0);
			this->listFeedItem->Margin = System::Windows::Forms::Padding(2, 4, 2, 4);
			this->listFeedItem->MultiSelect = false;
			this->listFeedItem->Name = L"listFeedItem";
			this->listFeedItem->Size = System::Drawing::Size(582, 233);
			this->listFeedItem->SmallImageList = this->imageListFeeds;
			this->listFeedItem->TabIndex = 1;
			this->listFeedItem->UseCompatibleStateImageBehavior = false;
			this->listFeedItem->View = System::Windows::Forms::View::Details;
			this->listFeedItem->VirtualMode = true;
			this->listFeedItem->ItemActivate += gcnew System::EventHandler(this, &MainWindow::listFeedItem_ItemActivate);
			this->listFeedItem->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &MainWindow::listFeedItem_ItemSelectionChanged);
			this->listFeedItem->RetrieveVirtualItem += gcnew System::Windows::Forms::RetrieveVirtualItemEventHandler(this, &MainWindow::listFeedItem_RetrieveVirtualItem);
			// 
			// columnFeedItemImage
			// 
			this->columnFeedItemImage->Text = L"";
			this->columnFeedItemImage->Width = 24;
			// 
			// columnFeedItemSource
			// 
			this->columnFeedItemSource->Text = L"Source";
			// 
			// columnFeedItemTitle
			// 
			this->columnFeedItemTitle->Text = L"Title";
			// 
			// topBar
			// 
			this->topBar->AutoSize = false;
			this->topBar->BackColor = System::Drawing::SystemColors::Window;
			this->topBar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
				this->buttonNewFeed, this->buttonRemoveFeed,
					this->toolStripSeparator1, this->buttonUpdateSelected, this->buttonUpdateAll, this->toolStripSeparator2, this->buttonToggleArchive,
					this->buttonMarkAllAsRead
			});
			this->topBar->Location = System::Drawing::Point(0, 24);
			this->topBar->Name = L"topBar";
			this->topBar->Padding = System::Windows::Forms::Padding(0, 0, 2, 0);
			this->topBar->Size = System::Drawing::Size(784, 30);
			this->topBar->TabIndex = 2;
			this->topBar->Text = L"toolStrip1";
			// 
			// buttonNewFeed
			// 
			this->buttonNewFeed->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonNewFeed.Image")));
			this->buttonNewFeed->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonNewFeed->Name = L"buttonNewFeed";
			this->buttonNewFeed->Size = System::Drawing::Size(79, 27);
			this->buttonNewFeed->Text = L"New Feed";
			// 
			// buttonRemoveFeed
			// 
			this->buttonRemoveFeed->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonRemoveFeed.Image")));
			this->buttonRemoveFeed->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonRemoveFeed->Name = L"buttonRemoveFeed";
			this->buttonRemoveFeed->Size = System::Drawing::Size(98, 27);
			this->buttonRemoveFeed->Text = L"Remove Feed";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(6, 30);
			// 
			// buttonUpdateSelected
			// 
			this->buttonUpdateSelected->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonUpdateSelected.Image")));
			this->buttonUpdateSelected->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonUpdateSelected->Name = L"buttonUpdateSelected";
			this->buttonUpdateSelected->Size = System::Drawing::Size(112, 27);
			this->buttonUpdateSelected->Text = L"Update Selected";
			// 
			// buttonUpdateAll
			// 
			this->buttonUpdateAll->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonUpdateAll.Image")));
			this->buttonUpdateAll->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonUpdateAll->Name = L"buttonUpdateAll";
			this->buttonUpdateAll->Size = System::Drawing::Size(82, 27);
			this->buttonUpdateAll->Text = L"Update All";
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(6, 30);
			// 
			// buttonToggleArchive
			// 
			this->buttonToggleArchive->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonToggleArchive.Image")));
			this->buttonToggleArchive->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonToggleArchive->Name = L"buttonToggleArchive";
			this->buttonToggleArchive->Size = System::Drawing::Size(113, 27);
			this->buttonToggleArchive->Text = L"Toggle Archived";
			// 
			// buttonMarkAllAsRead
			// 
			this->buttonMarkAllAsRead->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonMarkAllAsRead.Image")));
			this->buttonMarkAllAsRead->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonMarkAllAsRead->Name = L"buttonMarkAllAsRead";
			this->buttonMarkAllAsRead->Size = System::Drawing::Size(116, 27);
			this->buttonMarkAllAsRead->Text = L"Mark All As Read";
			// 
			// statusBar
			// 
			this->statusBar->Location = System::Drawing::Point(0, 539);
			this->statusBar->Name = L"statusBar";
			this->statusBar->Padding = System::Windows::Forms::Padding(2, 0, 16, 0);
			this->statusBar->Size = System::Drawing::Size(784, 22);
			this->statusBar->TabIndex = 3;
			this->statusBar->Text = L"statusStrip1";
			// 
			// browserFeedItemDesc
			// 
			this->browserFeedItemDesc->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->browserFeedItemDesc->Location = System::Drawing::Point(0, 4);
			this->browserFeedItemDesc->Margin = System::Windows::Forms::Padding(2, 4, 2, 4);
			this->browserFeedItemDesc->MinimumSize = System::Drawing::Size(26, 23);
			this->browserFeedItemDesc->Name = L"browserFeedItemDesc";
			this->browserFeedItemDesc->Size = System::Drawing::Size(582, 232);
			this->browserFeedItemDesc->TabIndex = 4;
			// 
			// splitVertical
			// 
			this->splitVertical->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitVertical->Location = System::Drawing::Point(0, 58);
			this->splitVertical->Margin = System::Windows::Forms::Padding(2, 4, 2, 4);
			this->splitVertical->Name = L"splitVertical";
			// 
			// splitVertical.Panel1
			// 
			this->splitVertical->Panel1->Controls->Add(this->listFeedList);
			// 
			// splitVertical.Panel2
			// 
			this->splitVertical->Panel2->Controls->Add(this->splitHorizontal);
			this->splitVertical->Size = System::Drawing::Size(784, 477);
			this->splitVertical->SplitterDistance = 195;
			this->splitVertical->SplitterWidth = 2;
			this->splitVertical->TabIndex = 5;
			// 
			// splitHorizontal
			// 
			this->splitHorizontal->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitHorizontal->Location = System::Drawing::Point(2, 4);
			this->splitHorizontal->Margin = System::Windows::Forms::Padding(2, 4, 2, 4);
			this->splitHorizontal->Name = L"splitHorizontal";
			this->splitHorizontal->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitHorizontal.Panel1
			// 
			this->splitHorizontal->Panel1->Controls->Add(this->listFeedItem);
			// 
			// splitHorizontal.Panel2
			// 
			this->splitHorizontal->Panel2->Controls->Add(this->browserFeedItemDesc);
			this->splitHorizontal->Size = System::Drawing::Size(588, 473);
			this->splitHorizontal->SplitterDistance = 233;
			this->splitHorizontal->TabIndex = 5;
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::Window;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->helpToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(7, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(784, 24);
			this->menuStrip1->TabIndex = 6;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->exitToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"&File";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(92, 22);
			this->exitToolStripMenuItem->Text = L"E&xit";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem });
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"&Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(107, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->splitVertical);
			this->Controls->Add(this->statusBar);
			this->Controls->Add(this->topBar);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(2, 4, 2, 4);
			this->Name = L"MainWindow";
			this->Text = L"anteRSS";
			this->Load += gcnew System::EventHandler(this, &MainWindow::MainWindow_Load);
			this->topBar->ResumeLayout(false);
			this->topBar->PerformLayout();
			this->splitVertical->Panel1->ResumeLayout(false);
			this->splitVertical->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitVertical))->EndInit();
			this->splitVertical->ResumeLayout(false);
			this->splitHorizontal->Panel1->ResumeLayout(false);
			this->splitHorizontal->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitHorizontal))->EndInit();
			this->splitHorizontal->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
private: anteRSSParserWrapper::RSSManagerWrapper^ manager;

private: System::Void listFeedList_Resize(System::Object^  sender, System::EventArgs^  e);
private: System::Void listFeedList_ColumnWidthChanging(System::Object^  sender, System::Windows::Forms::ColumnWidthChangingEventArgs^  e);
private: System::Void listFeedList_RetrieveVirtualItem(System::Object^  sender, System::Windows::Forms::RetrieveVirtualItemEventArgs^  e);

public: System::Void listFeedList_UpdateList();
private: System::Void browserFeedItemDesc_changeDescription(System::Int32 selectedIndex);
private: System::Void MainWindow_Load(System::Object^  sender, System::EventArgs^  e);
#ifndef NDEBUG
private: System::Void buttonDebug_Click(System::Object^  sender, System::EventArgs^  e);
#endif
private: System::Void listFeedItem_RetrieveVirtualItem(System::Object^  sender, System::Windows::Forms::RetrieveVirtualItemEventArgs^  e);
private: System::Void listFeedItem_ItemActivate(System::Object^  sender, System::EventArgs^  e);
private: System::Void listFeedItem_ItemSelectionChanged(System::Object^  sender, System::Windows::Forms::ListViewItemSelectionChangedEventArgs^  e);
};
}
