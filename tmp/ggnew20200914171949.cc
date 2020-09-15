// ggnew.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 9月 13 10:21:58 2020 (+0800)
// Last-Updated: 一 9月 14 17:19:49 2020 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 95
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

#define BINNUMBER 4096
#define ENERGYMAX 4096  //keV
#define FILENAME  "co59.m4b"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH2I *h2;
TH1D *h1,*hg,*htmp;
TRootEmbeddedCanvas *cc; 
TCanvas* c1;
TCanvas* c2;
std::set<int> peakbin;
std::set<int> bgbin;
double upx0=-1;
int binx1,binx2;
TBox *b;
double bgscale=1.0;

void tpj();
void gate();
void gate(double,double);
void gshow();
void ggnew()
{
  // gStyle->SetOptStat(0);//不显示统计框

  c1 = new TCanvas("c1","c1");
  c1->ToggleEventStatus();//底端信息栏
  
  h2 = new TH2I("h2","",BINNUMBER,0,ENERGYMAX,BINNUMBER,0,ENERGYMAX);
  
  uint data;

  std::ifstream readdata(FILENAME,std::ios::binary);

  for (int i = 1; i <= BINNUMBER; ++i)
    for (int j = 1; j <= BINNUMBER; ++j)
      {
	readdata.read((char*)&data,sizeof(uint));
	if(data > 0)
	  {
	    h2->SetBinContent(i,j,data);
	  }
      }
  
  readdata.close();

  h1 = h2->ProjectionX();
  tpj();
}


void tpj()
{
  // if(!c1)  c1 = new TCanvas("c1","c1");
  c1->DeleteExec("gateflag");
  c1->DeleteExec("bgflag");
  
  h1->Draw("HIST");

  peakbin.clear();
  bgbin.clear();
}


void gate()
{
  // float uxmin = gPad->GetUxmin();
  // float uxmax = gPad->GetUxmax();

  float uxmin = c1->GetUxmin();
  float uxmax = c1->GetUxmax();
  std::cout<<uxmin<<"  "<<uxmax<<std::endl;
  gate((uxmin+uxmax)/2.,(uxmax-uxmin)/2.);
}

void gate(double gpeak,double wgpeak=50)
{  
  peakbin.clear();
  std::cout<<"Gate: left-click on the left/right bins"<<std::endl;
  if(!c1) c1 = new TCanvas("c1","c1");
  else { std::cout<<"xxxxxxxxxxxxxxxxxxxxxxx"<<std::endl; }

  // c1->SetName("c1");
  
  // c1 = (TCanvas *)gROOT->GetListOfCanvases()->FindObject("c1");
  if (c1) c1->RaiseWindow();
  
  c1->GetListOfPrimitives()->Remove(b);
  
  c1->cd();
  c1->Clear();
  
  h1->GetXaxis()->SetRange(gpeak-wgpeak,gpeak+wgpeak);
  // h1->SetLineColor(gRandom->Uniform(1,9));
  h1->Draw();
  c1->DeleteExec("bgflag");
  c1->AddExec("gateflag","gateflag()");

  c1->ls();
  
  c1->Modified();
  c1->Update();
  c1->Constructor();
}


void bg()
{
  bgbin.clear();
  std::cout<<"Background: left-click bins"<<endl;
  if(!c1)  c1 = new TCanvas("c1","c1");
  c1->Draw();
  c1->DeleteExec("gateflag");
  c1->AddExec("bgflag","bgflag()");
}


void gateflag()
{
  int pe = gPad->GetEvent();
  if(pe != 11) return;
  gPad->GetCanvas()->FeedbackMode(kTRUE);
  // if(gPad->GetUniqueID() == 0)
  if(upx0 <0)
    {
      gPad->SetUniqueID(gPad->GetEventX());
      upx0 = -1;
      //点击第一下
      TObject *select = gPad->GetSelected();
      if(!select) {return;}
      if (!select->InheritsFrom(TH1::Class())) {return;}
      int px = gPad->GetEventX();
      TH1 *h = (TH1*)select;
      h->Draw();
      upx0 = gPad->AbsPixeltoX(px);
      double x0 = gPad->PadtoX(upx0);
      double binx0 = h->FindBin(x0);
      
      b = new TBox(h->GetBinLowEdge(binx0),
			 gPad->GetUymin(),
			 h->GetBinWidth(binx0)+h->GetBinLowEdge(binx0),
			 h->GetBinContent(binx0));
      b->SetFillColorAlpha(kBlue,0.35);
      b->Draw();

      
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

      TH1 *h = (TH1*)select;

      double x1 = gPad->PadtoX(upx0);
      binx1 = h->FindBin(x1);
      x1=h->GetBinCenter(binx1);
      Float_t upx2 = gPad->AbsPixeltoX(px);
      double x2 = gPad->PadtoX(upx2);
      binx2 = h->FindBin(x2);
      x2=h->GetBinCenter(binx2);
      if(binx1 == binx2) return;
      
      if( binx1 > binx2)
	{
	  Float_t temp;
	  temp = binx1;
	  binx1 = binx2;
	  binx2 = temp;
	}
      for (int i = binx1; i <= binx2; ++i)
	{
	  peakbin.insert(i);
	  if(i == binx1) continue;
	  b = new TBox(h->GetBinLowEdge(i),
			     gPad->GetUymin(),
			     h->GetBinWidth(i)+h->GetBinLowEdge(i),
			     h->GetBinContent(i));
	  b->SetFillColorAlpha(kBlue,0.35);
	  b->Draw();

	}
      
      std::cout<<x1<<" - "<<x2<<std::endl;
      gPad->Update();
      upx0 = -1;
      bg();

    }
}

void bgflag()
{
  int pe = gPad->GetEvent();
  if(pe != 11) return;
  gPad->GetCanvas()->FeedbackMode(kTRUE);    
  gPad->SetUniqueID(gPad->GetEventX());
  //点击第一下
  TObject *select = gPad->GetSelected();
  if(!select) {return;}
  if (!select->InheritsFrom(TH1::Class())) {return;}
  int px = gPad->GetEventX();
  TH1 *h = (TH1*)select;
  double upxb = gPad->AbsPixeltoX(px);
  double x0 = gPad->PadtoX(upxb);
  double binx0 = h->FindBin(x0);
  x0=h->GetBinCenter(binx0);
  bgbin.insert(binx0);
  cout<<x0<<endl;
  b = new TBox(h->GetBinLowEdge(binx0),
		     gPad->GetUymin(),
		     h->GetBinWidth(binx0)+h->GetBinLowEdge(binx0),
		     h->GetBinContent(binx0));
  b->SetFillColorAlpha(kGreen,0.35);
  b->Draw();
  gPad->Update();
}



void show()
{
  std::cout<<"peakbin.size="<<peakbin.size()<<" : ";
  for(auto is=peakbin.begin();is!=peakbin.end();is++)
    std::cout<< *is<<" ";
  std::cout<<std::endl;
  
  std::cout<<"bgbin.size="<<bgbin.size()<<" : ";
  for(auto is=bgbin.begin();is!=bgbin.end();is++)
    std::cout<< *is<<" ";
  std::cout<<std::endl;
}

void gshow()
{
  if(!c2)
    {
      c2 = new TCanvas("c2","c2");
      c2->ToggleEventStatus();//底端信息栏
    }
  c2->cd();
  
  if(!hg) hg = new TH1D("hg","",BINNUMBER,0,ENERGYMAX);
  hg->Reset();
  if(!htmp) htmp = new TH1D("hgtmp","",BINNUMBER,0,ENERGYMAX);
  double weight = double(peakbin.size())/bgbin.size();
  
  for(auto is=peakbin.begin();is!=peakbin.end();is++) {
    htmp->Reset();//这里用reset来清除，虽然有没有清除对projecttion的结果没影响
    htmp = h2->ProjectionX("",int(*is),int(*is));
    hg->Add(hg,htmp,1,1);
  }
  for(auto is=bgbin.begin();is!=bgbin.end();is++) {
    htmp->Reset();
    htmp = h2->ProjectionX("",int(*is),int(*is));
    hg->Add(hg,htmp,1,-weight*bgscale);//在选择的峰右侧，由于高能效率等因素，只按照bin数来进行归一化可能存在本底扣除不充分的问题（右侧选择区域的本底计数通常低于峰位置的本底计数）  
  }
  hg->Draw("HIST");
}

void bgs(double scale)
{
  bgscale = scale;
}

// 
// ggnew.cc ends here
