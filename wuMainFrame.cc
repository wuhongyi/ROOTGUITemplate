// wuMainFrame.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 11月 13 12:58:09 2016 (+0800)
// Last-Updated: 日 11月 13 13:28:09 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 20
// URL: http://wuhongyi.cn 

#include "TGFrame.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class MainFrame : public TGMainFrame
{
public:
  MainFrame(const TGWindow *p, UInt_t w, UInt_t h);
  virtual ~MainFrame();



  

  ClassDef(MainFrame, 0)
};


MainFrame::MainFrame(const TGWindow *p, UInt_t w, UInt_t h)
  : TGMainFrame(p, w, h)// default VerticalFrame
{

  TGHorizontalFrame *fH1 = new TGHorizontalFrame(this, 1, 1, kSunkenFrame);//, kFixedHeight
  this->AddFrame(fH1, new TGLayoutHints(kLHintsTop | kLHintsExpandX));

  TGHorizontalFrame *fH2 = new TGHorizontalFrame(this, 1, 1, kSunkenFrame);
  this->AddFrame(fH2, new TGLayoutHints(kLHintsTop | kLHintsExpandX));

  
  TGLabel *fL1 = new TGLabel(fH1, "FirstLabel");
  fH1->AddFrame(fL1, new TGLayoutHints(kLHintsTop | kLHintsExpandY | kLHintsExpandX, 0, 0, 10, 20));
  TGLabel *fL2 = new TGLabel(fH1, "SecondLabel");
  fH1->AddFrame(fL2, new TGLayoutHints(kLHintsTop | kLHintsExpandY | kLHintsExpandX, 30, 0, 20, 10));


  
  TGVerticalFrame *fV1 = new TGVerticalFrame(fH2, 1, 1, kSunkenFrame);
  fH2->AddFrame(fV1, new TGLayoutHints(kLHintsTop | kLHintsExpandX));

  TGVerticalFrame *fV2 = new TGVerticalFrame(fH2, 1, 1, kSunkenFrame);
  fH2->AddFrame(fV2, new TGLayoutHints(kLHintsTop | kLHintsExpandX));

  TGVerticalFrame *fV3 = new TGVerticalFrame(fH2, 1, 1, kSunkenFrame);
  fH2->AddFrame(fV3, new TGLayoutHints(kLHintsTop | kLHintsExpandX));
  

  TGLabel *fL3 = new TGLabel(fV2, "FirstLabel");
  fV2->AddFrame(fL3, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 10, 0, 0, 5));
  TGLabel *fL4 = new TGLabel(fV2, "SecondLabel");
  fV2->AddFrame(fL4, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 20, 0, 0, 0));
  
  
  // What to clean up in dtor
  SetCleanup(kDeepCleanup);

  // Set a name to the main frame
  SetWindowName("Main Frame");

  MapSubwindows();
  Resize(GetDefaultSize());
  // Resize(800,600);
  MapWindow();
   
}

MainFrame::~MainFrame()
{
  // Clean up all widgets, frames and layouthints that were used
   Cleanup();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void wuMainFrame()
{
  // 
  new MainFrame(gClient->GetRoot(),1,1);
}

// 
// wuMainFrame.cc ends here
