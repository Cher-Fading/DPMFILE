#define plotmult_cxx
#include "plotmult.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

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

void plotmult::Loop()
{
//   In a ROOT session, you can do:
//      root> .L plotmult.C
//      root> plotmult t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
int q2_min = 1;
int q2_max = 1e3;
   Float_t q2_bins[31];   
  float initial = log(q2_min);
  float incre = log(q2_max/q2_min)/30;
  for (int i = 0; i < 31;i++)  {
      q2_bins[i] = TMath::Power(TMath::E(),initial); 
      initial = initial + incre;
  }

   Long64_t nentries = fChain->GetEntries();
   TH1F* multP = hotTH1F("Multi", "dN/N vs Track Multiplicity of Final State Particles", 30,0.5,30.5, "", "", kRed, 0.3, 21, 1, false);
   TH1F* Q2P = hotTH1F("Q2", "dN/N vs Q2",30,q2_bins, "", "",kRed, 0.3, 21, 1, true);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      cout << (sizeof(particles_KS)/sizeof(Int_t)) << endl;
      return;
   }
}
