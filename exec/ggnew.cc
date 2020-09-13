// ggnew.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 9月 13 10:21:58 2020 (+0800)
// Last-Updated: 日 9月 13 19:19:52 2020 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 44
// URL: http://wuhongyi.cn 


// 实现思路
// gate() 选择开窗时候，在直方图上点击两下。则两个点击的区间即为门区间。改区间存到全局变量
// bg()   选择本底，点击一下画一个bin。数据也存在全局变量
// show() 根据全局变量的信息，进行开窗运算
// 需要添加图像清除等。把错误的选择能够清除，或者在次点击可以清除bg选择等。


#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include "TRandom.h"
#include "TBenchmark.h"
#include "TString.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TSystem.h"

#include <fstream>
#include <iostream>
#include <set>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH2I *h2;
TH1D *h1;
TCanvas* c1;
std::set<int> peakbin;
std::set<int> bgbin;

void ggnew()
{
  c1 = new TCanvas("c1","c1");
  
  h2 = new TH2I("h2","",4096,0,4096,4096,0,4096);
  
  uint data;

  std::ifstream readdata("co59.m4b",std::ios::binary);

  for (int i = 1; i <= 4096; ++i)
    for (int j = 1; j <= 4096; ++j)
      {
	readdata.read((char*)&data,sizeof(uint));
	if(data > 0)
	  {
	    h2->SetBinContent(i,j,data);
	  }
      }
  
  readdata.close();

  h1 = h2->ProjectionX();

}


void tpj()
{
  c1->DeleteExec("gateflag");
  c1->DeleteExec("bgflag");
  
  h1->Draw("HIST");

  peakbin.clear();
  bgbin.clear();
}


void gate()
{
  c1->DeleteExec("bgflag");
  c1->AddExec("gateflag","gateflag()");
}


void bg()
{
  c1->DeleteExec("gateflag");
  c1->AddExec("bgflag","bgflag()");
}


void gateflag()
{
  int pe = gPad->GetEvent();
  if(pe != 11) return;
  gPad->GetCanvas()->FeedbackMode(kTRUE);

  if(gPad->GetUniqueID() == 0)
    {
      gPad->SetUniqueID(gPad->GetEventX());
      std::cout<<"xxx"<<std::endl;

      //点击第一下
      TObject *select = gPad->GetSelected();
      if(!select) {return;}
      if (!select->InheritsFrom(TH1::Class())) {return;}
      int px = gPad->GetEventX();

      TH1 *h = (TH1*)select;
      Float_t upx0 = gPad->AbsPixeltoX(px);
      double x0 = gPad->PadtoX(upx0);
      int binx0 = h->FindBin(x0);
      TLine *ll = new TLine();
      // ll->SetLineColor(2);
      ll->DrawLine(h->GetBinCenter(binx0),0,h->GetBinCenter(binx0),h->GetBinContent(binx0));
      ll->Draw();
	  
      gPad->Update();
    }
  else
    {
      int pxold = gPad->GetUniqueID();
      Float_t upxold = gPad->AbsPixeltoX(pxold);
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
      
      Float_t upx = gPad->AbsPixeltoX(px);
      Float_t upy = gPad->AbsPixeltoY(py);
      
      TObject *select = gPad->GetSelected();
      if(!select) {gPad->SetUniqueID(0); return;}
      if (!select->InheritsFrom(TH1::Class())) {gPad->SetUniqueID(0); return;}

      if(upxold == upx) return;

      TH1 *h = (TH1*)select;
					      
      if(upxold > upx)
	{
	  Float_t temp;
	  temp = upxold;
	  upxold = upx;
	  upx = temp;
	}

      // if(pxold) gVirtualX->DrawLine(pxold,pymin,pxold,pymax);
      // gVirtualX->DrawLine(px,pymin,px,pymax);

      Float_t upx1 = gPad->AbsPixeltoX(pxold);
      double x1 = gPad->PadtoX(upx1);
      int binx1 = h->FindBin(x1);
      Float_t upx2 = gPad->AbsPixeltoX(px);
      double x2 = gPad->PadtoX(upx2);
      int binx2 = h->FindBin(x2);
      
      for (int i = binx1; i <= binx2; ++i)
	{
	  peakbin.insert(i);
	  
	  TLine *ll = new TLine();
	  ll->SetLineColor(2);
	  ll->DrawLine(h->GetBinCenter(i),0,h->GetBinCenter(i),h->GetBinContent(i));
	  
	  std::cout<<"ref: "<<i<<"  "<<h->GetBinContent(i)<<std::endl;
	  ll->Draw();
	}
      
      // TLine *ll1;
      // TLine *ll2;
      // ll1 = new TLine;
      // ll1->DrawLine(x1,uymin,x1,uymax);
      // ll1->Draw();
      // ll2 = new TLine;
      // ll2->DrawLine(x2,uymin,x2,uymax);
      // ll2->Draw();
      // gVirtualX->DrawLine(upxold,py,upx,py);

      std::cout<<x1<<"  "<<x2<<std::endl;
      std::cout<<uymin<<"  "<<uymax<<std::endl;
      gPad->Update();
      gPad->SetUniqueID(0);
    }
}

void bgflag()
{
  int pe = gPad->GetEvent();
  if(pe != 11) return;
  gPad->GetCanvas()->FeedbackMode(kTRUE);

  TObject *select = gPad->GetSelected();
  if(!select) {gPad->SetUniqueID(0); return;}
  if (!select->InheritsFrom(TH1::Class())) {gPad->SetUniqueID(0); return;}

  TH1 *h = (TH1*)select;	

  int px = gPad->GetEventX();
  Float_t upx = gPad->AbsPixeltoX(px);
  double x = gPad->PadtoX(upx);
  int binx = h->FindBin(x);

  bgbin.insert(binx);
  
  TLine *ll = new TLine();
  ll->SetLineColor(3);
  ll->DrawLine(h->GetBinCenter(binx),0,h->GetBinCenter(binx),h->GetBinContent(binx));
  ll->Draw();
  gPad->Update();
  gPad->SetUniqueID(0);

  
}

void show()
{

  std::cout<<"peakbin: "<<peakbin.size()<<"  bgbin: "<<bgbin.size()<<std::endl;
  
}


// 
// ggnew.cc ends here
