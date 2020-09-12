
#include <TH1.h>
#include <TCanvas.h>
#include <TQObject.h>
#include "TROOT.h"

void exec3()
{
   // Temporary work around the lack of automatic refresh of the list
   // when a script is reloaded.
   gROOT->GetListOfGlobalFunctions()->Delete();

   TH1F *h = new TH1F("h","h",100,-3,3);
   h->FillRandom("gaus",1000);
   TCanvas *c1=new TCanvas("c1");
   h->Draw();
   c1->Update();
   // c1->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0, 0, "exec3event(Int_t,Int_t,Int_t,TObject*)");

   c1->AddExec("xxxxname","PanelGausFit()");
   // c1->DeleteExec("xxxxname");
}

void exec3event(Int_t event, Int_t x, Int_t y, TObject *selected)
{
   TCanvas *c = (TCanvas *) gTQSender;
   printf("Canvas %s: event=%d, x=%d, y=%d, selected=%s\n", c->GetName(),
          event, x, y, selected->IsA()->GetName());
  
}



void PanelGausFit()
{
  int pe = gPad->GetEvent();
  if(pe != 11) return;
  // gPad->GetCanvas()->FeedbackMode(kTRUE);

  if(gPad->GetUniqueID() == 0)
    {
      gPad->SetUniqueID(gPad->GetEventX());
    }
  else
    {
      int pxold = gPad->GetUniqueID();
      Float_t upxold = gPad->AbsPixeltoX(pxold);
      int px = gPad->GetEventX();
      Float_t upx = gPad->AbsPixeltoX(px);

      TObject *select = gPad->GetSelected();
      if(!select) {gPad->SetUniqueID(0); return;}
      if (!select->InheritsFrom(TH1::Class())) {gPad->SetUniqueID(0); return;}
      TH1 *h = (TH1*)select;					      
      if(upxold > upx)
	{
	  Float_t temp;
	  temp = upxold;
	  upxold = upx;
	  upx = temp;
	}
      if(h->Fit("gaus","QL","",upxold,upx) == 0)
	{
	  double posl = h->GetFunction("gaus")->GetParameter(1)-3*h->GetFunction("gaus")->GetParameter(2);
	  double posr = h->GetFunction("gaus")->GetParameter(1)+3*h->GetFunction("gaus")->GetParameter(2);	  
	    
	  h->SetTitle(TString::Format("Peak: %0.2f  P/T: %0.2f%%  #DeltaE/E: %0.2f%%",h->GetFunction("gaus")->GetParameter(1),h->Integral(h->FindBin(posl),h->FindBin(posr))/h->GetEntries()*100,h->GetFunction("gaus")->GetParameter(2)*2.355/h->GetFunction("gaus")->GetParameter(1)*100.0).Data());
	}
      else
	{
	  h->SetTitle("Please choose Fit range again.");
	}
      gPad->SetUniqueID(0);
    }
}
