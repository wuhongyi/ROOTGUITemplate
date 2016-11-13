// wuMessage.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 11月 13 13:26:31 2016 (+0800)
// Last-Updated: 日 11月 13 20:57:26 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 29
// URL: http://wuhongyi.cn 

#include "TGFrame.h"

#include <iostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MainFrame : public TGMainFrame
{
public:
  MainFrame(const TGWindow *p, UInt_t w, UInt_t h);
  virtual ~MainFrame();

  
  virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);//process message queue

  void ChangeStartLabel();

  
private:
  TGTextButton     *fStart, *fPause, *fExit;
  Bool_t            start, pause;
  
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

MainFrame::MainFrame(const TGWindow *p, UInt_t w, UInt_t h)
  : TGMainFrame(p, w, h)// default VerticalFrame
{
  TGVerticalFrame *fVf = new TGVerticalFrame(this, 10, 10);
  AddFrame(fVf, new TGLayoutHints(kLHintsRight | kLHintsExpandX | kLHintsExpandY));

  
  TGHorizontalFrame *fH1 = new TGHorizontalFrame(fVf, 10, 10, kSunkenFrame);//, kFixedHeight
  fVf->AddFrame(fH1, new TGLayoutHints(kLHintsTop | kLHintsExpandX));

  fStart = new TGTextButton(fH1, "&Start",1/*button id*/);
  fStart->Associate(this);// 继承 widget 的需要调用该函数才能向主窗口发送 Message
  fH1->AddFrame(fStart, new TGLayoutHints(kLHintsTop | kLHintsExpandX,3, 2, 2, 2));
  fStart->SetToolTipText("Click to toggle the button label (Start/Stop)");
  fStart->Connect("Clicked()", "MainFrame", this, "ChangeStartLabel()");
  start = kFALSE;
  std::cout<<"start button ID: "<<fStart->WidgetId()<<std::endl;
  
  
  fPause = new TGTextButton(fH1, "&Pause",2/*button id*/);
  fPause->Associate(this);
  fH1->AddFrame(fPause, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 3, 2, 2, 2));
  // fPause->Connect("Clicked()", "MainFrame", this, "ChangePauseLabel()");
  fPause->SetToolTipText("Click to toggle the button label (Pause/Resume)");


  fExit = new TGTextButton(fH1, "&Exit ","gApplication->Terminate(0)");
  fExit->Associate(this);
  fH1->AddFrame(fExit, new TGLayoutHints(kLHintsTop | kLHintsExpandX,5,5,2,2));
   

  
  TGHorizontalFrame *fH2 = new TGHorizontalFrame(fVf, 10, 10, kSunkenFrame);
  fVf->AddFrame(fH2, new TGLayoutHints(kLHintsTop | kLHintsExpandX));



  TGHorizontalFrame *fH3 = new TGHorizontalFrame(fVf, 10, 10, kSunkenFrame);
  fVf->AddFrame(fH3, new TGLayoutHints(kLHintsTop | kLHintsExpandX));

  
  
  
  // What to clean up in dtor
  SetCleanup(kDeepCleanup);

  // Set a name to the main frame
  SetWindowName("Main Frame");

  MapSubwindows();
  // Resize(GetDefaultSize());
  Resize(800,600);
  MapWindow();
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
