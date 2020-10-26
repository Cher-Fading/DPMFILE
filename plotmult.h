//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct 26 05:29:56 2020 by ROOT version 6.20/02
// from TTree EICTree/my EIC tree
// found on file: fort91.root
//////////////////////////////////////////////////////////

#ifndef plotmult_h
#define plotmult_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TObject.h"

class plotmult {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxparticles = 774;

   // Declaration of leaf types
 //erhic::EventDpmjet *event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Double32_t      x;
   Double32_t      QSquared;
   Double32_t      y;
   Double32_t      WSquared;
   Double32_t      nu;
   Double32_t      yJB;
   Double32_t      QSquaredJB;
   Double32_t      xJB;
   Double32_t      WSquaredJB;
   Double32_t      yDA;
   Double32_t      QSquaredDA;
   Double32_t      xDA;
   Double32_t      WSquaredDA;
   Int_t           number;
   Int_t           process;
   Int_t           nTracks;
   Double32_t      ELeptonInNucl;
   Double32_t      ELeptonOutNucl;
   Int_t           particles_;
   UInt_t          particles_fUniqueID[kMaxparticles];   //[particles_]
   UInt_t          particles_fBits[kMaxparticles];   //[particles_]
   UShort_t        particles_I[kMaxparticles];   //[particles_]
   Int_t           particles_KS[kMaxparticles];   //[particles_]
   Int_t           particles_id[kMaxparticles];   //[particles_]
   UShort_t        particles_orig[kMaxparticles];   //[particles_]
   UShort_t        particles_orig1[kMaxparticles];   //[particles_]
   UShort_t        particles_daughter[kMaxparticles];   //[particles_]
   UShort_t        particles_ldaughter[kMaxparticles];   //[particles_]
   Double_t        particles_px[kMaxparticles];   //[particles_]
   Double_t        particles_py[kMaxparticles];   //[particles_]
   Double_t        particles_pz[kMaxparticles];   //[particles_]
   Double32_t      particles_E[kMaxparticles];   //[particles_]
   Double32_t      particles_m[kMaxparticles];   //[particles_]
   Double32_t      particles_pt[kMaxparticles];   //[particles_]
   Double_t        particles_xv[kMaxparticles];   //[particles_]
   Double_t        particles_yv[kMaxparticles];   //[particles_]
   Double_t        particles_zv[kMaxparticles];   //[particles_]
   Int_t           particles_parentId[kMaxparticles];   //[particles_]
   Double32_t      particles_p[kMaxparticles];   //[particles_]
   Double32_t      particles_theta[kMaxparticles];   //[particles_]
   Double32_t      particles_phi[kMaxparticles];   //[particles_]
   Double32_t      particles_rapidity[kMaxparticles];   //[particles_]
   Double32_t      particles_eta[kMaxparticles];   //[particles_]
   Double32_t      particles_z[kMaxparticles];   //[particles_]
   Double32_t      particles_xFeynman[kMaxparticles];   //[particles_]
   Double32_t      particles_thetaGamma[kMaxparticles];   //[particles_]
   Double32_t      particles_ptVsGamma[kMaxparticles];   //[particles_]
   Double32_t      particles_phiPrf[kMaxparticles];   //[particles_]
   TRef            particles_event[kMaxparticles];
   Int_t           ievent;
   Int_t           I;
   Int_t           process1;
   Int_t           process2;
   Int_t           IP;
   Int_t           tgtparton;
   Int_t           prjparton;
   Int_t           nucleon;
   Double32_t      xtgtparton;
   Double32_t      xprjparton;
   Double32_t      dtrueW2;
   Double32_t      dtrueNu;
   Double32_t      dtrueQ2;
   Double32_t      dtrueY;
   Double32_t      dtrueX;
   Double32_t      theta_Evt;
   Double32_t      photonFlux;

   // List of branches
   TBranch        *b_event_fUniqueID;   //!
   TBranch        *b_event_fBits;   //!
   TBranch        *b_event_x;   //!
   TBranch        *b_event_QSquared;   //!
   TBranch        *b_event_y;   //!
   TBranch        *b_event_WSquared;   //!
   TBranch        *b_event_nu;   //!
   TBranch        *b_event_yJB;   //!
   TBranch        *b_event_QSquaredJB;   //!
   TBranch        *b_event_xJB;   //!
   TBranch        *b_event_WSquaredJB;   //!
   TBranch        *b_event_yDA;   //!
   TBranch        *b_event_QSquaredDA;   //!
   TBranch        *b_event_xDA;   //!
   TBranch        *b_event_WSquaredDA;   //!
   TBranch        *b_event_number;   //!
   TBranch        *b_event_process;   //!
   TBranch        *b_event_nTracks;   //!
   TBranch        *b_event_ELeptonInNucl;   //!
   TBranch        *b_event_ELeptonOutNucl;   //!
   TBranch        *b_event_particles_;   //!
   TBranch        *b_particles_fUniqueID;   //!
   TBranch        *b_particles_fBits;   //!
   TBranch        *b_particles_I;   //!
   TBranch        *b_particles_KS;   //!
   TBranch        *b_particles_id;   //!
   TBranch        *b_particles_orig;   //!
   TBranch        *b_particles_orig1;   //!
   TBranch        *b_particles_daughter;   //!
   TBranch        *b_particles_ldaughter;   //!
   TBranch        *b_particles_px;   //!
   TBranch        *b_particles_py;   //!
   TBranch        *b_particles_pz;   //!
   TBranch        *b_particles_E;   //!
   TBranch        *b_particles_m;   //!
   TBranch        *b_particles_pt;   //!
   TBranch        *b_particles_xv;   //!
   TBranch        *b_particles_yv;   //!
   TBranch        *b_particles_zv;   //!
   TBranch        *b_particles_parentId;   //!
   TBranch        *b_particles_p;   //!
   TBranch        *b_particles_theta;   //!
   TBranch        *b_particles_phi;   //!
   TBranch        *b_particles_rapidity;   //!
   TBranch        *b_particles_eta;   //!
   TBranch        *b_particles_z;   //!
   TBranch        *b_particles_xFeynman;   //!
   TBranch        *b_particles_thetaGamma;   //!
   TBranch        *b_particles_ptVsGamma;   //!
   TBranch        *b_particles_phiPrf;   //!
   TBranch        *b_particles_event;   //!
   TBranch        *b_event_ievent;   //!
   TBranch        *b_event_I;   //!
   TBranch        *b_event_process1;   //!
   TBranch        *b_event_process2;   //!
   TBranch        *b_event_IP;   //!
   TBranch        *b_event_tgtparton;   //!
   TBranch        *b_event_prjparton;   //!
   TBranch        *b_event_nucleon;   //!
   TBranch        *b_event_xtgtparton;   //!
   TBranch        *b_event_xprjparton;   //!
   TBranch        *b_event_dtrueW2;   //!
   TBranch        *b_event_dtrueNu;   //!
   TBranch        *b_event_dtrueQ2;   //!
   TBranch        *b_event_dtrueY;   //!
   TBranch        *b_event_dtrueX;   //!
   TBranch        *b_event_theta_Evt;   //!
   TBranch        *b_event_photonFlux;   //!

   plotmult(TTree *tree=0);
   virtual ~plotmult();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef plotmult_cxx
plotmult::plotmult(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("~/dpmjet3-32BIT/fort91.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("~/dpmjet3-32BIT/fort91.root");
      }
      f->GetObject("EICTree",tree);

   }
   Init(tree);
}

plotmult::~plotmult()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t plotmult::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t plotmult::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void plotmult::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_event_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_event_fBits);
   fChain->SetBranchAddress("x", &x, &b_event_x);
   fChain->SetBranchAddress("QSquared", &QSquared, &b_event_QSquared);
   fChain->SetBranchAddress("y", &y, &b_event_y);
   fChain->SetBranchAddress("WSquared", &WSquared, &b_event_WSquared);
   fChain->SetBranchAddress("nu", &nu, &b_event_nu);
   fChain->SetBranchAddress("yJB", &yJB, &b_event_yJB);
   fChain->SetBranchAddress("QSquaredJB", &QSquaredJB, &b_event_QSquaredJB);
   fChain->SetBranchAddress("xJB", &xJB, &b_event_xJB);
   fChain->SetBranchAddress("WSquaredJB", &WSquaredJB, &b_event_WSquaredJB);
   fChain->SetBranchAddress("yDA", &yDA, &b_event_yDA);
   fChain->SetBranchAddress("QSquaredDA", &QSquaredDA, &b_event_QSquaredDA);
   fChain->SetBranchAddress("xDA", &xDA, &b_event_xDA);
   fChain->SetBranchAddress("WSquaredDA", &WSquaredDA, &b_event_WSquaredDA);
   fChain->SetBranchAddress("number", &number, &b_event_number);
   fChain->SetBranchAddress("process", &process, &b_event_process);
   fChain->SetBranchAddress("nTracks", &nTracks, &b_event_nTracks);
   fChain->SetBranchAddress("ELeptonInNucl", &ELeptonInNucl, &b_event_ELeptonInNucl);
   fChain->SetBranchAddress("ELeptonOutNucl", &ELeptonOutNucl, &b_event_ELeptonOutNucl);
   fChain->SetBranchAddress("particles", &particles_, &b_event_particles_);
   fChain->SetBranchAddress("particles.fUniqueID", particles_fUniqueID, &b_particles_fUniqueID);
   fChain->SetBranchAddress("particles.fBits", particles_fBits, &b_particles_fBits);
   fChain->SetBranchAddress("particles.I", particles_I, &b_particles_I);
   fChain->SetBranchAddress("particles.KS", particles_KS, &b_particles_KS);
   fChain->SetBranchAddress("particles.id", particles_id, &b_particles_id);
   fChain->SetBranchAddress("particles.orig", particles_orig, &b_particles_orig);
   fChain->SetBranchAddress("particles.orig1", particles_orig1, &b_particles_orig1);
   fChain->SetBranchAddress("particles.daughter", particles_daughter, &b_particles_daughter);
   fChain->SetBranchAddress("particles.ldaughter", particles_ldaughter, &b_particles_ldaughter);
   fChain->SetBranchAddress("particles.px", particles_px, &b_particles_px);
   fChain->SetBranchAddress("particles.py", particles_py, &b_particles_py);
   fChain->SetBranchAddress("particles.pz", particles_pz, &b_particles_pz);
   fChain->SetBranchAddress("particles.E", particles_E, &b_particles_E);
   fChain->SetBranchAddress("particles.m", particles_m, &b_particles_m);
   fChain->SetBranchAddress("particles.pt", particles_pt, &b_particles_pt);
   fChain->SetBranchAddress("particles.xv", particles_xv, &b_particles_xv);
   fChain->SetBranchAddress("particles.yv", particles_yv, &b_particles_yv);
   fChain->SetBranchAddress("particles.zv", particles_zv, &b_particles_zv);
   fChain->SetBranchAddress("particles.parentId", particles_parentId, &b_particles_parentId);
   fChain->SetBranchAddress("particles.p", particles_p, &b_particles_p);
   fChain->SetBranchAddress("particles.theta", particles_theta, &b_particles_theta);
   fChain->SetBranchAddress("particles.phi", particles_phi, &b_particles_phi);
   fChain->SetBranchAddress("particles.rapidity", particles_rapidity, &b_particles_rapidity);
   fChain->SetBranchAddress("particles.eta", particles_eta, &b_particles_eta);
   fChain->SetBranchAddress("particles.z", particles_z, &b_particles_z);
   fChain->SetBranchAddress("particles.xFeynman", particles_xFeynman, &b_particles_xFeynman);
   fChain->SetBranchAddress("particles.thetaGamma", particles_thetaGamma, &b_particles_thetaGamma);
   fChain->SetBranchAddress("particles.ptVsGamma", particles_ptVsGamma, &b_particles_ptVsGamma);
   fChain->SetBranchAddress("particles.phiPrf", particles_phiPrf, &b_particles_phiPrf);
   fChain->SetBranchAddress("particles.event", particles_event, &b_particles_event);
   fChain->SetBranchAddress("ievent", &ievent, &b_event_ievent);
   fChain->SetBranchAddress("I", &I, &b_event_I);
   fChain->SetBranchAddress("process1", &process1, &b_event_process1);
   fChain->SetBranchAddress("process2", &process2, &b_event_process2);
   fChain->SetBranchAddress("IP", &IP, &b_event_IP);
   fChain->SetBranchAddress("tgtparton", &tgtparton, &b_event_tgtparton);
   fChain->SetBranchAddress("prjparton", &prjparton, &b_event_prjparton);
   fChain->SetBranchAddress("nucleon", &nucleon, &b_event_nucleon);
   fChain->SetBranchAddress("xtgtparton", &xtgtparton, &b_event_xtgtparton);
   fChain->SetBranchAddress("xprjparton", &xprjparton, &b_event_xprjparton);
   fChain->SetBranchAddress("dtrueW2", &dtrueW2, &b_event_dtrueW2);
   fChain->SetBranchAddress("dtrueNu", &dtrueNu, &b_event_dtrueNu);
   fChain->SetBranchAddress("dtrueQ2", &dtrueQ2, &b_event_dtrueQ2);
   fChain->SetBranchAddress("dtrueY", &dtrueY, &b_event_dtrueY);
   fChain->SetBranchAddress("dtrueX", &dtrueX, &b_event_dtrueX);
   fChain->SetBranchAddress("theta_Evt", &theta_Evt, &b_event_theta_Evt);
   fChain->SetBranchAddress("photonFlux", &photonFlux, &b_event_photonFlux);
   Notify();
}

Bool_t plotmult::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void plotmult::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t plotmult::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef plotmult_cxx
