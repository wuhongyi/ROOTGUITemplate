
// Event
   // kNoEvent       =  0,
   // kButton1Down   =  1, kButton2Down   =  2, kButton3Down   =  3, kKeyDown  =  4,
   // kWheelUp       =  5, kWheelDown     =  6, kButton1Shift  =  7, kButton1ShiftMotion  =  8,
   // kButton1Up     = 11, kButton2Up     = 12, kButton3Up     = 13, kKeyUp    = 14,
   // kButton1Motion = 21, kButton2Motion = 22, kButton3Motion = 23, kKeyPress = 24,
   // kArrowKeyPress = 25, kArrowKeyRelease = 26,
   // kButton1Locate = 41, kButton2Locate = 42, kButton3Locate = 43, kESC      = 27,
   // kMouseMotion   = 51, kMouseEnter    = 52, kMouseLeave    = 53,
   // kButton1Double = 61, kButton2Double = 62, kButton3Double = 63

#include "TObject.h"
#include "TH1.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TRandom.h"
#include <iostream>
using namespace std;

void DynamicExec()
{
  // int pe = gPad->GetEvent();



  TObject *select = gPad->GetSelected();
  if(!select) return;

  // 拿到鼠标放置位置的TH1
  if (!select->InheritsFrom(TH1::Class())) {gPad->SetUniqueID(0); return;}
  TH1 *h = (TH1*)select;
  gPad->GetCanvas()->FeedbackMode(kTRUE);


  //erase old position and draw a line at current position
  int pold = gPad->GetUniqueID();
  int px = gPad->GetEventX();
  int py = gPad->GetEventY();
  float uxmin = gPad->GetUxmin();
  float uxmax = gPad->GetUxmax();
  float uymin = gPad->GetUymin();
  float uymax = gPad->GetUymax();
  int pxmin = gPad->XtoAbsPixel(uxmin);
  int pxmax = gPad->XtoAbsPixel(uxmax);
  int pymin = gPad->YtoAbsPixel(uymin);
  int pymax = gPad->YtoAbsPixel(uymax);


  // 画出本画板的线
  if(pold) gVirtualX->DrawLine(pold,pymin,pold,pymax);
  gVirtualX->DrawLine(px,pymin,px,pymax);
  gPad->SetUniqueID(px);
  Float_t upx = gPad->AbsPixeltoX(px);
  Float_t x = gPad->PadtoX(upx);

  // 当前TH1 x位置坐标
  cout<<px<<endl;

  // 当前指向的子画板
  // cout<<gPad->GetName()<<endl;

  // 取得最外面的画板 c1
  // cout<<gPad->GetMother()<<endl;

  // gPad->GetMother()->cd(1)->GetListOfPrimitives()->Last()->Print();


  // 画出第一个画板的线
  gPad->GetMother()->cd(1);
  TLine *ll;
  if(gPad->GetMother()->cd(1)->GetListOfPrimitives()->FindObject("TLine"))
    {
      TLine *lll =(TLine*)gPad->GetMother()->cd(1)->GetListOfPrimitives()->FindObject("TLine");
      lll->PaintLine(x,gPad->GetMother()->cd(1)->GetUymin(),x,gPad->GetMother()->cd(1)->GetUymax());      
    }
  else
    {
      ll = new TLine;
      ll->PaintLine(x,gPad->GetMother()->cd(1)->GetUymin(),x,gPad->GetMother()->cd(1)->GetUymax());
    }



  gPad->GetMother()->Update();

}

void dynamic()
{
  TCanvas* c1 = new TCanvas("c1","c1");
  TH1D *h1 = new TH1D("h1","",4096,0,2048);
  TH1D *h2 = new TH1D("h2","",4096,0,2048);

  Double_t px,py;
  for (Int_t i = 0; i < 50000; i++)
    {
      gRandom->Rannor(px,py);

      h1->Fill(px*100+1024);
      h2->Fill(py*200+1024);
    }


  c1->Divide(1,2);

  c1->cd(1);
  h1->Draw();
  c1->cd(2);
  h2->Draw();


  // 开启画板响应
  c1->cd(2)->AddExec("asasdsfdgdggd","DynamicExec()");
  // 关闭画板响应
  // c1->cd(2)->DeleteExec("asasdsfdgdggd");
}
