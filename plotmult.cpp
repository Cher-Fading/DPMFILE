#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/EventBase.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/EventPythia.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/Particle.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/EventDpmjet.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/Forester.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/ForesterStatus.h.betterbutdifferent"

#include "../atlasstyle-00-04-02/AtlasUtils.h"
#include "../atlasstyle-00-04-02/AtlasStyle.h"
#include "../atlasstyle-00-04-02/AtlasLabels.h"
#include "../atlasstyle-00-04-02/AtlasStyle.C"

#ifdef __CLING__
// these are not headers - do not treat them as such - needed for ROOT6
#include "../atlasstyle-00-04-02/AtlasLabels.C"
#include "../atlasstyle-00-04-02/AtlasUtils.C"
#endif

#ifdef __CINT__
gROOT->LoadMacro("../atlasstyle-00-04-02/AtlasLabels.C");
gROOT->LoadMacro("../atlasstyle-00-04-02/AtlasUtils.C");
#endif

const int listn = 13;
const int partl[listn] = {11,13,22,81,130,211,310,321,411,421,431,2112,2212};
const int charl[listn] = {-1,-1,0,0,0,-1,0,1,1,0,1,0,1};

void plotmult(string filename)
{
  gSystem->AddIncludePath("/afs/rhic/eic/restructured/env/pro/lib/");
  gSystem->Load("/afs/rhic/eic/restructured/env/pro/lib/libeicsmear.so");

  TFile *f = TFile::Open(Form("%s.root", filename.c_str()),"READ");
  TTree *EICTree = (TTree *)f->Get("EICTree");
  //cout << "here" << endl;
  int kMaxparticles = 1000;
  Int_t particles_KS[kMaxparticles];
  Int_t particles_id[kMaxparticles];
  Double32_t particles_pt[kMaxparticles];
  Double32_t      QSquared;
  EICTree->SetBranchAddress("QSquared", &QSquared);
  EICTree->SetBranchAddress("particles.KS", particles_KS);
  EICTree->SetBranchAddress("particles.id", particles_id);
  EICTree->SetBranchAddress("particles.pt", particles_pt);
  if (EICTree == 0) return;
int q2_min = 1;
int q2_max = 1e3;
   Float_t q2_bins[31];   
  float initial = log(q2_min);
  float incre = log(q2_max/q2_min)/30;
  for (int i = 0; i < 31;i++)  {
      q2_bins[i] = TMath::Power(TMath::E(),initial); 
      initial = initial + incre;
  }
    TFile* fout = TFile::Open(Form("%s_result.root",filename.c_str()),"RECREATE");
  TH1F* multP = hotTH1F("Multi", "dN/N vs Track Multiplicity of Final State Particles", 30,0.5,30.5, "", "", kRed, 0.3, 21, 1, false);
  //TH1F* multP_2 = hotTH1F("Multi", "dN/N vs Track Multiplicity of Final State Particles", 30,0.5,30.5, "", "", kBlue, 0.3, 21, 1, false);//status = -1 & 1
   TH1F* Q2P = hotTH1F("Q2", "dN/N vs Q2",30,q2_bins, "", "",kRed, 0.3, 21, 1, true);
   //TH1F* Q2P_2 = hotTH1F("Q2", "dN/N vs Q2",30,q2_bins, "", "",kBlue, 0.3, 21, 1, true);

   Long64_t nentries = EICTree->GetEntries();
  for (int j = 0; j < nentries; j++){
    if (j%1000==0) cout << "At event " << j << endl;
    EICTree->GetEntry(j);
    //if (QSquared < 5) continue;
cout << QSquared << endl;
return;
    Q2P->Fill(QSquared);
    //cout << sizeof(particles_id)/sizeof(Int_t) << endl;
    int counter1 = 0;
    //int counter2 = 0;
    for (int i = 0; i < kMaxparticles; i++){
      //cout << particles_pt[i] << endl;
      //cout << particles_id[i] << endl;
      //cout << particles_KS[i] << endl;
      if (particles_pt[i] == 0) break;
      if (particles_pt[i] < 0.1 || particles_pt[i] > 5) continue;
      if (abs(particles_KS[i]) !=1 && particles_KS[i]!=1001) continue;
      bool charged = false;
      for (int k = 0; k < listn; k++){
	if (partl[k]==particles_id[i] && charl[k]!=0) charged = true;}
	if (!charged) continue;
      counter1++;
      //if (particles_KS[i]==1){
	//counter1++;
      //}
    }
  multP->Fill(counter1);
  //multP_2->Fill(counter2);
  }
  f ->Close();
  
     TCanvas* c0 = new TCanvas("c0","c0",500,500);

   TPad* thePad = (TPad*)c0->cd();
   TH1F *h1 = thePad->DrawFrame(0,1e-3,30,1);
   h1->SetXTitle("N_{ch}");
   h1->SetYTitle("dN/dN_{ch}");
   h1->SetTitle("Distribution of Track Multiplicity in Events");
   h1->Draw();
    multP->Write();
   //multP_2->Write();
   multP->Scale(1./multP->GetSumOfWeights());
   //multP_2->Scale(1./multP_2->GetSumOfWeights());
   multP->Draw("SAME");
   //multP_2->Draw("SAME");
   myMarkerText( 0.6, 0.85, kRed, 21, "Particle Status = 1", 1.2, 0.04);
   //myMarkerText( 0.6, 0.8, kBlue, 21, "Particle Abs(status) = 1", 1.2, 0.04);
   myText(0.6,0.75,kBlack,"Q^{2} > 1 GeV",0.04);
   myText(0.6,0.7,kBlack,"0.1 GeV < p_{T}^{trk} < 5 GeV",0.04);
   c0->SaveAs(Form("%s_mult.pdf",filename.c_str()));

   
   h1 = thePad->DrawFrame(1,1e-3,1e3,1);
   h1->SetXTitle("Q^{2} (GeV^{2})");
   h1->SetYTitle("dN/dQ^{2} (GeV^{2})");
   h1->SetTitle("Distribution of Q^{2} in Events");
   Q2P->Write();
   Q2P->Scale(1./Q2P->GetSumOfWeights());
   Q2P->Draw("SAME");
   c0->SaveAs(Form("%s_q2.pdf",filename.c_str()));
   
   fout->Close();
   
   
}
