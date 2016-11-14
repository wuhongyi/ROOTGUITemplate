// wuMessage.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 11月 13 13:26:31 2016 (+0800)
// Last-Updated: 一 11月 14 17:55:12 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 72
// URL: http://wuhongyi.cn 

#include "TGFrame.h"

#include <iostream>
#include <unistd.h>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Connect

// TCanvas ProcessedEvent(Int_t,Int_t,Int_t,TObject*)
// TGCheckButton Toggled(Bool_t)
// TGColorSelect ColorSelected(Pixel_t)
// TGComboBox Selected(Int_t)
// TGCompositeFrame ProcessedEvent(Event_t*) ProcessedConfigure(Event_t*)
// TGFrame ProcessedEvent(Event_t*) ProcessedConfigure(Event_t*)
// TGMainFrame CloseWindow()
// TGNumberEntry TextChanged(char*)
// TGPopupMenu Activated(Int_t)
// TGSpeedo OdoClicked() LedClicked()
// TGTextButton Clicked() Pressed() 


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class IDList {

private:
   Int_t nID;   // creates unique widget's IDs

public:
   IDList() : nID(0) {}
   ~IDList() {}
   Int_t GetUnID(void) { return ++nID; }
};

class MainFrame : public TGMainFrame
{
public:
  MainFrame(const TGWindow *p, UInt_t w, UInt_t h);
  virtual ~MainFrame();

  
  virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);//process message queue  一次仅允许一个操作在响应，做个操作将按照先后顺序依次响应

  void ChangeStartLabel();
  void SetGroupEnabled(Bool_t);
  void ChangeUpdate();
  
private:
  TGLabel       *fLbl1, *fLbl2, *fLbl3, *fLbl4;
  
  TGTextButton     *fStart, *fPause, *fExit;
  Bool_t           start, pause;
  
  TGButtonGroup      *fButtonGroup;  // Button group
  TGCheckButton       *fCheckb[4];    // Check buttons
  TGRadioButton       *fRadiob[2];    // Radio buttons

  TGComboBox     *fMonthBox;   // month selector
  TGNumberEntry  *fYearEntry;  // year selector
  TGColorSelect  *fTableColor; // selector of color


  
  IDList           IDs;           // Widget IDs generator
  
  ClassDef(MainFrame, 0)
};

void MainFrame::ChangeStartLabel()
{
  // Slot connected to the Clicked() signal.
  // It will toggle labels "Start" and "Stop".

  fStart->SetState(kButtonDown);
  if (!start) {
     fStart->SetText("&Stop");
     start = kTRUE;
  } else {
     fStart->SetText("&Start");
     start = kFALSE;
  }
  fStart->SetState(kButtonUp);
}

void MainFrame::SetGroupEnabled(Bool_t on)
{
   fButtonGroup->SetState(on);
}

void MainFrame::ChangeUpdate()
{
  Int_t month = fMonthBox->GetSelected();
  Int_t year = atoi(fYearEntry->GetNumberEntry()->GetText());
  Pixel_t pixel = 0;
  pixel = fTableColor->GetColor();

  std::cout<<"Month: "<<month<<"  Year: " <<year<<"  Pixel: "<<pixel<<std::endl;

  // 同个按钮多次按，响应同时单独在运行
  int a = 0;
  while(fCheckb[3]->IsOn())
    {
      for (int i = 0; i < 100; ++i)
	{
	  a+=i;
	}
      gSystem->ProcessEvents();
    }
  
  std::cout<<"@@@ --- @@@"<<std::endl;
}


MainFrame::MainFrame(const TGWindow *p, UInt_t w, UInt_t h)
  : TGMainFrame(p, w, h)// default VerticalFrame
{
  TGVerticalFrame *fVf = new TGVerticalFrame(this, 10, 10);
  AddFrame(fVf, new TGLayoutHints(kLHintsRight | kLHintsExpandX | kLHintsExpandY));

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  TGHorizontalFrame *fH0 = new TGHorizontalFrame(fVf, 10, 10, kSunkenFrame);
  fVf->AddFrame(fH0, new TGLayoutHints(kLHintsTop | kLHintsExpandX));

  TGGC *fTextGC;
  const TGFont *font = gClient->GetFont("-*-times-bold-r-*-*-18-*-*-*-*-*-*-*");
  if (!font)
    font = gClient->GetResourcePool()->GetDefaultFont();
  FontStruct_t labelfont = font->GetFontStruct();
  GCValues_t   gval;
  gval.fMask = kGCBackground | kGCFont | kGCForeground;
  gval.fFont = font->GetFontHandle();
  gClient->GetColorByName("yellow", gval.fBackground);
  fTextGC = gClient->GetGC(&gval, kTRUE);
  ULong_t bcolor, ycolor;
  gClient->GetColorByName("yellow", ycolor);
  gClient->GetColorByName("blue", bcolor);

  fLbl1 = new TGLabel(fH0, "OwnFont & Bck/ForgrColor", fTextGC->GetGC(),
		      labelfont, kChildFrame, bcolor);
  fH0->AddFrame(fLbl1, new TGLayoutHints(kLHintsNormal, 5, 5, 3, 4));
  fLbl1->SetTextColor(ycolor);

  fLbl2 = new TGLabel(fH0, "Own Font & ForegroundColor", fTextGC->GetGC(),labelfont);
  fH0->AddFrame(fLbl2,  new TGLayoutHints(kLHintsCenterX, 5, 5, 3, 4));
  fLbl2->SetTextColor(ycolor);

  fLbl3 = new TGLabel(fH0, "Normal Label");
  fH0->AddFrame(fLbl3,  new TGLayoutHints(kLHintsCenterX, 5, 5, 3, 4));

  fLbl4 = new TGLabel(fH0, "Multi-line label, resized\nto 300x80 pixels",
		      fTextGC->GetGC(), labelfont, kChildFrame, bcolor);
  fH0->AddFrame(fLbl4, new TGLayoutHints(kLHintsCenterX, 5, 5, 3, 4));
  fLbl4->SetTextColor(ycolor);
  fLbl4->ChangeOptions(fLbl4->GetOptions() | kFixedSize);
  fLbl4->Resize(350, 80);  

  fLbl1->Enable();
  fLbl2->Enable();
  fLbl3->Enable();
  fLbl4->Enable();
  // fLbl1->Disable();
  // fLbl2->Disable();
  // fLbl3->Disable();
  // fLbl4->Disable();

  if (fLbl1->IsDisabled())
    {
      printf("Disabled labels\n");
    }
   
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  TGHorizontalFrame *fH1 = new TGHorizontalFrame(fVf, 10, 10, kSunkenFrame);//, kFixedHeight
  fVf->AddFrame(fH1, new TGLayoutHints(kLHintsTop | kLHintsExpandX));

  fStart = new TGTextButton(fH1, "&Start",1/*button id*/);
  fStart->Associate(this);// 继承 widget 的需要调用该函数才能向主窗口发送 Message
  fH1->AddFrame(fStart, new TGLayoutHints(kLHintsTop | kLHintsExpandX,3, 2, 2, 2));
  fStart->SetToolTipText("Click to toggle the button label (Start/Stop)",400);
  fStart->Connect("Clicked()", "MainFrame", this, "ChangeStartLabel()");// connect signals
  start = kFALSE;
  std::cout<<"start button ID: "<<fStart->WidgetId()<<std::endl;
  
  
  fPause = new TGTextButton(fH1, "&Pause",2/*button id*/);
  fPause->Associate(this);
  fH1->AddFrame(fPause, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 3, 2, 2, 2));
  // fPause->Connect("Clicked()", "MainFrame", this, "ChangePauseLabel()");
  fPause->SetToolTipText("Click to toggle the button label (Pause/Resume)");


  fExit = new TGTextButton(fH1, "&Exit ","gApplication->Terminate(0)");
  fExit->Associate(this);
  fExit->ChangeBackground(0x0000ff);
  // fExit->Resize(300, 20);
  // fExit->ChangeOptions(fExit->GetOptions() | kFixedSize);
  fH1->AddFrame(fExit, new TGLayoutHints(kLHintsTop | kLHintsExpandX,5,5,2,2));
   
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
  TGHorizontalFrame *fH2 = new TGHorizontalFrame(fVf, 10, 10, kSunkenFrame);
  fVf->AddFrame(fH2, new TGLayoutHints(kLHintsTop | kLHintsExpandX));

  fCheckb[3] = new TGCheckButton(fH2, new TGHotString("Enable BG"),IDs.GetUnID());
  fCheckb[3]->SetToolTipText("Enable/Disable the button group");
  fH2->AddFrame(fCheckb[3], new TGLayoutHints(kLHintsCenterX|kLHintsCenterY, 1, 1, 1, 1));
  fCheckb[3]->Connect("Toggled(Bool_t)"/*切换状态*/, "MainFrame", this, "SetGroupEnabled(Bool_t)");// connect signals
  fCheckb[3]->SetOn();
  
  fButtonGroup = new TGButtonGroup(fH2, "Button Group");
  fH2->AddFrame(fButtonGroup, new TGLayoutHints(kLHintsCenterX|kLHintsCenterY, 1, 1, 1, 1));
  fButtonGroup->SetTitlePos(TGGroupFrame::kCenter);
  fButtonGroup->SetButton(kTextCenterX);
  fCheckb[0] = new TGCheckButton(fButtonGroup, new TGHotString("CB 1"),IDs.GetUnID());
  fCheckb[0]->SetToolTipText("Enable/Disable");
  fCheckb[1] = new TGCheckButton(fButtonGroup, new TGHotString("CB 2"),IDs.GetUnID());
  fCheckb[2] = new TGCheckButton(fButtonGroup, new TGHotString("CB 3"),IDs.GetUnID());
  fRadiob[0] = new TGRadioButton(fButtonGroup, new TGHotString("RB 1"),IDs.GetUnID());
  fRadiob[1] = new TGRadioButton(fButtonGroup, new TGHotString("RB 2"),IDs.GetUnID());

  
  fButtonGroup->Show();
  fButtonGroup->SetState(kTRUE);//是否开启，开启才可以选，不开启是灰色的
  fButtonGroup->SetRadioButtonExclusive(kTRUE);

  fCheckb[3]->Associate(this);
  fCheckb[0]->Associate(this);
  fCheckb[1]->Associate(this);
  fCheckb[2]->Associate(this);
  fRadiob[0]->Associate(this);
  fRadiob[1]->Associate(this);

  fCheckb[0]->SetOn();
  fRadiob[1]->SetOn();

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
  TGHorizontalFrame *fH3 = new TGHorizontalFrame(fVf, 10, 10, kSunkenFrame);
  fVf->AddFrame(fH3, new TGLayoutHints(kLHintsTop | kLHintsExpandX));

  TGLabel *dateLabel = new TGLabel(fH3, "Date:");
  fH3->AddFrame(dateLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY,5, 2, 2, 2));
  
  TString monthNames[12] = {"January", "February", "March", "April",
			    "May", "June", "July", "August", "September",
			    "October", "November", "December"};
  TDatime today;
  fMonthBox = new TGComboBox(fH3,-1/*IDs*/);
  fH3->AddFrame(fMonthBox, new TGLayoutHints(kLHintsLeft, 5, 5, 2, 2));
  for (int i = 0; i < 12; i++) {
    fMonthBox->AddEntry(monthNames[i].Data(), i+1);
  }
  fMonthBox->Select(today.GetMonth());
  fMonthBox->Associate(this);
  
  fYearEntry = new TGNumberEntry(fH3, today.GetYear(), 5, -1/*IDs*/,
				 TGNumberFormat::kNESInteger,
				 TGNumberFormat::kNEAPositive,
				 TGNumberFormat::kNELLimitMin, 1995);
  fH3->AddFrame(fYearEntry, new TGLayoutHints(kLHintsLeft, 5, 5, 2, 2));
  fYearEntry->Associate(this);
  fMonthBox->Resize(100, fYearEntry->GetHeight());

  
  TGLabel *tableLabel = new TGLabel(fH3, "Color:");
  fH3->AddFrame(tableLabel, new TGLayoutHints(kLHintsLeft|kLHintsCenterY,5, 2, 2, 2));

  Pixel_t color;
  gClient->GetColorByName("yellow", color);
  fTableColor = new TGColorSelect(fH3, color,-1/*IDs*/);
  fH3->AddFrame(fTableColor, new TGLayoutHints(kLHintsLeft|kLHintsCenterY,5, 2, 2, 2));  
  fTableColor->Associate(this);

  // connect signals
  fMonthBox->Connect("Selected(Int_t)", "MainFrame", this,"ChangeUpdate()");
  fYearEntry->GetNumberEntry()->Connect("TextChanged(char*)", "MainFrame",this, "ChangeUpdate()");
  fTableColor->Connect("ColorSelected(Pixel_t)", "MainFrame", this,"ChangeUpdate()");
  
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
  TGHorizontalFrame *fH4 = new TGHorizontalFrame(fVf, 10, 10, kSunkenFrame);
  fVf->AddFrame(fH4, new TGLayoutHints(kLHintsTop | kLHintsExpandX));






  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
  TGHorizontalFrame *fH5 = new TGHorizontalFrame(fVf, 10, 10, kSunkenFrame);
  fVf->AddFrame(fH5, new TGLayoutHints(kLHintsTop | kLHintsExpandX));






  
  
  
  // What to clean up in dtor
  SetCleanup(kDeepCleanup);

  // Set a name to the main frame
  SetWindowName("Main Frame");

  MapSubwindows();
  // Resize(GetDefaultSize());
  Resize(800,600);
  MapWindow();

  Print();
}

MainFrame::~MainFrame()
{
  // Clean up all widgets, frames and layouthints that were used
   Cleanup();
}

Bool_t MainFrame::ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)
{
  // WidgetMessageTypes.h

  // System predefined widget message types. Message types are constants  
  // that indicate which widget sent the message and by which widget      
  // function (sub-message). Make sure your own message types don't clash  
  // whith the ones defined in this file. ROOT reserves all message ids   
  // between 0 - 1000. User defined messages should be in the range       
  // 1001 - 10000. Sub-messages must always be in the range 1-255.        
  // To use MK_MSG() just cast your message id's to an EWidgetMessageType.

  
  int test1 = 0, test2 = 0;

  test1 = GET_MSG(msg);
  test2 = GET_SUBMSG(msg);
  
  std::cout<<msg <<"  "<< parm1<<"  "<<parm2<<std::endl;
  std::cout<<test1<<"  "<<test2<<std::endl;

  switch(test1)
    {
    case kC_COMMAND:
      switch (test2)
	{
	case kCM_MENU://TGMenuBar TGPopupMenu
	  // menu id,user data
	  // Selecting a menu item will generate the event
	  
	  break;

	  //================================================

	case kCM_MENUSELECT:
	  
	  break;

	  //================================================

	case kCM_BUTTON://TGTextButton TGPictureButton
	  // button id,user data
	  // Selecting a text or picture button will generate the event
	  
	  break;

	  //================================================

	case kCM_CHECKBUTTON://TGCheckButton
	  // button id,user data
	  // Selecting a check button will generate the event
	  
	  break;

	  //================================================

	case kCM_RADIOBUTTON://TGRadioButton
	  // button id,user data
	  // Selecting a radio button will generate the event
	  
	  break;

	  //================================================

	case kCM_LISTBOX://TGListBox
	  // listbox id,item id
	  // Selecting an item in the listbox will generate the event
	  
	  break;

	  //================================================

	case kCM_COMBOBOX://TGComboBox
	  // combobox id,item id
	  // Selecting an item in the combobox will generate the event

	  
	  break;

	  //================================================

	case kCM_TAB://TGTab
	  // tab id,0
	  // Clicking on a tab will bring the associated composite frame to the   
	  // front and generate the event
	  
	  break;

	  //================================================
   
	default:
	  break;
	}

      break;
      
      //------------------------------------------------------------------------
      
    case kC_HSCROLL:
      switch (test2)
	{
	case kSB_LINEUP:
	  	  
	  break;

	  //================================================

	case kSB_LINEDOWN:
	  	  
	  break;

	  //================================================

	case kSB_PAGEUP:
	  	  
	  break;

	  //================================================

	case kSB_PAGEDOWN:
	  	  
	  break;

	  //================================================

	case kSB_SLIDERTRACK://TGHScrollBar
	  // position,0
	  // The TGHScrollBar will generate the event messages
	  
	  break;

	  //================================================

	case kSB_SLIDERPOS://TGHScrollBar
	  // position,0
	  // The TGHScrollBar will generate the event messages
	  
	  break;
	  
	  //================================================
   
	default:
	  break;  
	}
      
      break;

      //------------------------------------------------------------------------
      
    case kC_VSCROLL:
      switch (test2)
	{
	case kSB_LINEUP:
	  	  
	  break;

	  //================================================

	case kSB_LINEDOWN:
	  	  
	  break;

	  //================================================

	case kSB_PAGEUP:
	  	  
	  break;

	  //================================================

	case kSB_PAGEDOWN:
	  	  
	  break;

	  //================================================

	case kSB_SLIDERTRACK://TGVScrollBar
	  // position,0
	  // The TGVScrollBar will generate the event messages
	  
	  break;

	  //================================================

	case kSB_SLIDERPOS://TGVScrollBar
	  // position,0
	  // The TGVScrollBar will generate the event messages
	  
	  break;
	  
	  //================================================
   
	default:
	  break;  
	}
      
      break;

      //------------------------------------------------------------------------
      
    case kC_TEXTENTRY:
      switch (test2)
	{
	case kTE_TEXTCHANGED://TGTextEntry
	  // widget id,0
	  // Changing text in the text entry widget will generate the event
	  
	  break;
	  
	  //================================================
   
	case kTE_ENTER://TGTextEntry
	  // widget id,0
	  // Hitting the enter key will generate
	  
	  break;
	  
	  //================================================
   
	case kTE_TAB://TGTextEntry
	  // widget id,0
	  // Hitting the tab key will generate
	  
	  break;
	  
	  //================================================
   
	case kTE_KEY:
	  
	  break;

	  //================================================
   
	default:
	  break;  
	}
      
      break;

      //------------------------------------------------------------------------

    case kC_CONTAINER:
      switch (test2)
	{
	case kCT_ITEMCLICK://TGListView
	  // which button, location(y<<16|x)
	  // A list view can generate the events
	  
	  break;

	  //================================================
   
	case kCT_ITEMDBLCLICK://TGListView
	  // which button, location(y<<16|x)
	  // A list view can generate the events
	  
	  break;

	  //================================================
   
	case kCT_SELCHANGED://TGListView
	  // total items,selected items
	  // A list view can generate the events
	  
	  break;

	  //================================================
   
	case kCT_KEY:
	  
	  break;
	  
	  //================================================
   
	default:
	  break;  
	}
	  
      break;

      //------------------------------------------------------------------------

    case kC_HSLIDER:
      switch (test2)
	{
	  // Use the functions GetMinPosition(), GetMaxPosition() and             
	  // GetPosition() to retrieve the position of the slider.

	  // Use the function GetPointerPosition() to retrieve the position of    
	  // the pointer
	  
	case kSL_POS://TGDoubleHSlider TGTripleHSlider
	  // slider id,0
	  // Dragging the slider will generate the event
	  
	  break;

	  //================================================
   
	case kSL_TRACK:
	  	  
	  break;

	  //================================================
   
	case kSL_PRESS://TGDoubleHSlider TGTripleHSlider
	  // slider id,0
	  // Pressing the mouse will generate the event
	  
	  break;

	  //================================================
   
	case kSL_RELEASE://TGDoubleHSlider TGTripleHSlider
	  // slider id,0
	  // Releasing the mouse will generate the event
	  
	  break;

	  //================================================
   
	case kSL_POINTER://TGTripleHSlider
	  // slider id,0
	  // Moving the pointer will generate the event
	  
	  break;

	  //================================================
   
	default:
	  break;  
	}
	    
      break;

      //------------------------------------------------------------------------
      
    case kC_VSLIDER:
      switch (test2)
	{
	  // Use the functions GetMinPosition(), GetMaxPosition() and             
	  // GetPosition() to retrieve the position of the slider.

	  // Use the function GetPointerPosition() to retrieve the position of    
	  // the pointer
	  
	case kSL_POS://TGDoubleVSlider TGTripleHSlider
	  // slider id,0
	  // Dragging the slider will generate the event
	  
	  break;

	  //================================================
   
	case kSL_TRACK:
	  	  
	  break;

	  //================================================
   
	case kSL_PRESS://TGDoubleVSlider TGTripleHSlider
	  // slider id,0
	  // Pressing the mouse will generate the event
	  
	  break;

	  //================================================
   
	case kSL_RELEASE://TGDoubleVSlider TGTripleHSlider
	  // slider id,0
	  // Releasing the mouse will generate the event
	  
	  break;

	  //================================================
   
	case kSL_POINTER://TGTripleHSlider
	  // slider id,0
	  // Moving the pointer will generate the event
	  
	  break;

	  //================================================
   
	default:
	  break;  
	}

      break;

      //------------------------------------------------------------------------
      
    case kC_LISTTREE://
      switch (test2)
	{
	case kCT_ITEMCLICK://TGListTree
	  // which button, location(y<<16|x)
	  // A list tree can generate the events
	  
	  break;

	  //================================================
   
	case kCT_ITEMDBLCLICK://TGListTree
	  // which button, location(y<<16|x)
	  // A list tree can generate the events
	  
	  break;

	  //================================================
   
	case kCT_SELCHANGED:
	  
	  break;

	  //================================================
   
	case kCT_KEY:
	  
	  break;
	  
	  //================================================
   
	default:
	  break;  
	}            

      break;

      //------------------------------------------------------------------------
      
    case kC_TEXTVIEW:
      switch (test2)
	{
	case kTXT_ISMARKED:// TGView
	  // widget id, [true|false]  	  
	  break;

	  //================================================
   
	case kTXT_DATACHANGE:// TGView
	  // widget id, 0
	  
	  break;

	  //================================================
   
	case kTXT_CLICK2:// TGView
	  // widget id, position (y << 16) | x)
	  
	  break;

	  //================================================
   
	case kTXT_CLICK3:// TGView
	  // widget id, position (y << 16) | x)
	  
	  break;

	  //================================================
   
	case kTXT_F3:// TGView
	  // widget id, true
	  
	  break;

	  //================================================
   
	case kTXT_OPEN:
	  	  	  
	  break;

	  //================================================
   
	case kTXT_CLOSE:
	  	  	  
	  break;

	  //================================================
   
	case kTXT_SAVE:
   	  	  
	  break;

	  //================================================
   
	default:
	  break;  
	}
      
      break;

      //------------------------------------------------------------------------
      
    case kC_COLORSEL:
      switch (test2)
	{ 
	case kCOL_CLICK:// TGColorPalette TGColorPick
	  // widget id,0
	  // and the signal:  ColorSelected(Pixel_t color) 

	  
	  break;

	  //================================================
   
	case kCOL_SELCHANGED:// TGColorSelect
	  // widget id,pixel
	  // and the signal: ColorSelected(Pixel_t pixel)
	  
	  // The TGColorSelect widget is like a checkbutton but instead of the    
	  // check mark there is color area with a little down arrow. When        
	  // clicked on the arrow the TGColorPopup pops up. 

	  
	  break;

	  //================================================
   
	default:
	  break;  
	}
      
      break;

      //------------------------------------------------------------------------
      
    case kC_PATTERNSEL:
      switch (test2)
	{             
	case kPAT_CLICK:
	  	  
	  break;

	  //================================================
   
	case kPAT_SELCHANGED:
	  	  
	  break;

	  //================================================
   
	default:
	  break;  
	}
      
      break;

      //------------------------------------------------------------------------
      
    case kC_MARKERSEL:
      switch (test2)
	{             
	case kMAR_CLICK:
	  	  	  
	  break;

	  //================================================
   
	case kMAR_SELCHANGED:
	  	  	  
	  break;

	  //================================================
   
	default:
	  break;  
	}            

      break;

      //------------------------------------------------------------------------
      
    case kC_POPUP:
      switch (test2)
	{             
	case kPOP_HIDE:
	  	  	  	  
	  break;

	  //================================================
   
	default:
	  break;  
	}            

      break;

      //------------------------------------------------------------------------
      
    case kC_DOCK:
      switch (test2)
	{             
	case kDOCK_DOCK:
	  	  	  	  	  
	  break;

	  //================================================
   
	case kDOCK_UNDOCK:
	  	  	  	  	  
	  break;

	  //================================================
   
	case kDOCK_SHOW:
	  	  	  	  	  
	  break;

	  //================================================
   
	case kDOCK_HIDE:
	  	  	  	  	  
	  break;

	  //================================================
   
	default:
	  break;  
	}      

      break;

      //------------------------------------------------------------------------
      
    case kC_MDI:
      switch (test2)
	{             
	case kMDI_CURRENT:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_CREATE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_CLOSE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_RESTORE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_MOVE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_SIZE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_MINIMIZE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_MAXIMIZE:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_HELP:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	case kMDI_MENU:
	  	  	  	  	  	  
	  break;

	  //================================================
   
	default:
	  break;  
	}

      break;

      //------------------------------------------------------------------------

    default:
      break;
    }
  
  return kTRUE;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void wuMessage()
{

  new MainFrame(gClient->GetRoot(),1,1);
  
}

// 
// wuMessage.cc ends here
