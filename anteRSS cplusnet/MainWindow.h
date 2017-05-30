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
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
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
	private: System::Windows::Forms::WebBrowser^  feedFeedItemDesc;
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








	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->listFeedList = (gcnew System::Windows::Forms::ListView());
			this->columnFeedList = (gcnew System::Windows::Forms::ColumnHeader());
			this->listFeedItem = (gcnew System::Windows::Forms::ListView());
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
			this->feedFeedItemDesc = (gcnew System::Windows::Forms::WebBrowser());
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
			this->listFeedList->Location = System::Drawing::Point(3, 3);
			this->listFeedList->Name = L"listFeedList";
			this->listFeedList->Size = System::Drawing::Size(190, 478);
			this->listFeedList->TabIndex = 0;
			this->listFeedList->UseCompatibleStateImageBehavior = false;
			this->listFeedList->View = System::Windows::Forms::View::Details;
			this->listFeedList->ColumnWidthChanging += gcnew System::Windows::Forms::ColumnWidthChangingEventHandler(this, &MainWindow::listFeedList_ColumnWidthChanging);
			this->listFeedList->Resize += gcnew System::EventHandler(this, &MainWindow::listFeedList_Resize);
			// 
			// columnFeedList
			// 
			this->columnFeedList->Text = L"Feeds";
			this->columnFeedList->Width = 186;
			// 
			// listFeedItem
			// 
			this->listFeedItem->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->listFeedItem->Location = System::Drawing::Point(0, 0);
			this->listFeedItem->Name = L"listFeedItem";
			this->listFeedItem->Size = System::Drawing::Size(575, 236);
			this->listFeedItem->TabIndex = 1;
			this->listFeedItem->UseCompatibleStateImageBehavior = false;
			// 
			// topBar
			// 
			this->topBar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
				this->buttonNewFeed, this->buttonRemoveFeed,
					this->toolStripSeparator1, this->buttonUpdateSelected, this->buttonUpdateAll, this->toolStripSeparator2, this->buttonToggleArchive,
					this->buttonMarkAllAsRead
			});
			this->topBar->Location = System::Drawing::Point(0, 24);
			this->topBar->Name = L"topBar";
			this->topBar->Size = System::Drawing::Size(784, 25);
			this->topBar->TabIndex = 2;
			this->topBar->Text = L"toolStrip1";
			// 
			// buttonNewFeed
			// 
			this->buttonNewFeed->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonNewFeed.Image")));
			this->buttonNewFeed->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonNewFeed->Name = L"buttonNewFeed";
			this->buttonNewFeed->Size = System::Drawing::Size(79, 22);
			this->buttonNewFeed->Text = L"New Feed";
			// 
			// buttonRemoveFeed
			// 
			this->buttonRemoveFeed->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonRemoveFeed.Image")));
			this->buttonRemoveFeed->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonRemoveFeed->Name = L"buttonRemoveFeed";
			this->buttonRemoveFeed->Size = System::Drawing::Size(98, 22);
			this->buttonRemoveFeed->Text = L"Remove Feed";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(6, 25);
			// 
			// buttonUpdateSelected
			// 
			this->buttonUpdateSelected->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonUpdateSelected.Image")));
			this->buttonUpdateSelected->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonUpdateSelected->Name = L"buttonUpdateSelected";
			this->buttonUpdateSelected->Size = System::Drawing::Size(112, 22);
			this->buttonUpdateSelected->Text = L"Update Selected";
			// 
			// buttonUpdateAll
			// 
			this->buttonUpdateAll->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonUpdateAll.Image")));
			this->buttonUpdateAll->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonUpdateAll->Name = L"buttonUpdateAll";
			this->buttonUpdateAll->Size = System::Drawing::Size(82, 22);
			this->buttonUpdateAll->Text = L"Update All";
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(6, 25);
			// 
			// buttonToggleArchive
			// 
			this->buttonToggleArchive->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonToggleArchive.Image")));
			this->buttonToggleArchive->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonToggleArchive->Name = L"buttonToggleArchive";
			this->buttonToggleArchive->Size = System::Drawing::Size(113, 22);
			this->buttonToggleArchive->Text = L"Toggle Archived";
			// 
			// buttonMarkAllAsRead
			// 
			this->buttonMarkAllAsRead->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonMarkAllAsRead.Image")));
			this->buttonMarkAllAsRead->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->buttonMarkAllAsRead->Name = L"buttonMarkAllAsRead";
			this->buttonMarkAllAsRead->Size = System::Drawing::Size(116, 22);
			this->buttonMarkAllAsRead->Text = L"Mark All As Read";
			// 
			// statusBar
			// 
			this->statusBar->Location = System::Drawing::Point(0, 539);
			this->statusBar->Name = L"statusBar";
			this->statusBar->Size = System::Drawing::Size(784, 22);
			this->statusBar->TabIndex = 3;
			this->statusBar->Text = L"statusStrip1";
			// 
			// feedFeedItemDesc
			// 
			this->feedFeedItemDesc->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->feedFeedItemDesc->Location = System::Drawing::Point(0, 3);
			this->feedFeedItemDesc->MinimumSize = System::Drawing::Size(20, 20);
			this->feedFeedItemDesc->Name = L"feedFeedItemDesc";
			this->feedFeedItemDesc->Size = System::Drawing::Size(575, 229);
			this->feedFeedItemDesc->TabIndex = 4;
			// 
			// splitVertical
			// 
			this->splitVertical->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitVertical->Location = System::Drawing::Point(0, 52);
			this->splitVertical->Name = L"splitVertical";
			// 
			// splitVertical.Panel1
			// 
			this->splitVertical->Panel1->Controls->Add(this->listFeedList);
			// 
			// splitVertical.Panel2
			// 
			this->splitVertical->Panel2->Controls->Add(this->splitHorizontal);
			this->splitVertical->Size = System::Drawing::Size(784, 484);
			this->splitVertical->SplitterDistance = 196;
			this->splitVertical->TabIndex = 5;
			// 
			// splitHorizontal
			// 
			this->splitHorizontal->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->splitHorizontal->Location = System::Drawing::Point(3, 3);
			this->splitHorizontal->Name = L"splitHorizontal";
			this->splitHorizontal->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitHorizontal.Panel1
			// 
			this->splitHorizontal->Panel1->Controls->Add(this->listFeedItem);
			// 
			// splitHorizontal.Panel2
			// 
			this->splitHorizontal->Panel2->Controls->Add(this->feedFeedItemDesc);
			this->splitHorizontal->Size = System::Drawing::Size(578, 478);
			this->splitHorizontal->SplitterDistance = 239;
			this->splitHorizontal->TabIndex = 5;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->helpToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
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
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->splitVertical);
			this->Controls->Add(this->statusBar);
			this->Controls->Add(this->topBar);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainWindow";
			this->Text = L"anteRSS";
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
	

private: System::Void listFeedList_Resize(System::Object^  sender, System::EventArgs^  e);
private: System::Void listFeedList_ColumnWidthChanging(System::Object^  sender, System::Windows::Forms::ColumnWidthChangingEventArgs^  e);
};
}
