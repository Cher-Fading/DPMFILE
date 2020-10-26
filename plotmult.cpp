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

void plotmult(string filename)
{
  gSystem->AddIncludePath("/afs/rhic/eic/restructured/env/pro/lib/");
  gSystem->Load("/afs/rhic/eic/restructured/env/pro/lib/libeicsmear.so");

  TFile *f = TFile::Open(Form("%s.root", filename.c_str()));
  TTree *EICTree = (TTree *)f->Get("EICTree");
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

   Long64_t nentries = EICTree->GetEntries();
  for (int j = 0; j < nentries; j++){
    EICTree->GetEntry(j);
    cout << sizeof(particles_KS)/sizeof(Int_t) << endl;
    return;
  }
}