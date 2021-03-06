// read.cxx
//
// Created by TB on 6/13/11.
// Copyright 2011 BNL. All rights reserved.
//
// Example of how to read a file produced by BuildTree for a simple analysis.
// To run, in ROOT do:
// root [0] .L /path/to/read.cxx
// root [1] read("myInputFile.root", 10000 )

#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/EventBase.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/EventPythia.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/Particle.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/ParticleMC.h"
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
const int Q2_max = 1e3;
const float Q2_cut = 5.;

const int listn = 16;
const int partl[listn] = {11, 13, 22, 81, 111,
                          130, 211, 310, 313, 321,
                          323, 411, 421, 431, 2112,
                          2212};
const int charl[listn] = {-1, -1, 0, 0, 0,
                          0, -1, 0, 0, 1,
                          1, 1, 0, 1, 0,
                          1};

void read(TString inFileNames, int nEvents = 0, bool debug = false, bool replot = false)
{

   // If the analysis solely uses TTree::Draw statements,
   // you don't need to load
   // the shared library. You will receive warnings such as
   // Warning in <TClass::TClass>: no dictionary for class Particle
   // is available
   // but these can be ignored. However if you wish to work with the event
   // objects themselves, the shared library must be loaded:
   // Load the shared library, if not done automaticlly:
   //   gSystem->Load("/path/to/libeicsmear.so" );

   // The TTrees are named EICTree.
   // Create a TChain for trees with this name.

   int q2_min = 1;
   Float_t q2_bins[31];
   float initial = log(q2_min);
   float incre = log(Q2_max / q2_min) / 30;

   for (int i = 0; i < 31; i++)
   {
      q2_bins[i] = TMath::Power(TMath::E(), initial);
      if (debug)
         cout << q2_bins[i] << endl;
      initial = initial + incre;
   }

   TChain tree("EICTree");

   // Add the file(s) we want to analyse to the chain.
   // We could add multiple files if we wanted.
   std::string inname = inFileNames.Data();
   std::string outname = inname.substr(inname.find_last_of("/", inname.find("/*.root") - 1) + 1, inname.rfind("/") - inname.find_last_of("/", inname.find("/*.root") - 1) - 1);
   cout << outname << endl;
   TFile *fout;
   TH1F *multP, *Q2P;
   TH2F *Q2E;
   TH1::AddDirectory(kFALSE);
   if (!replot)
   {
      tree.Add(inFileNames); // Wild cards are allowed e.g. tree.Add("*.root" );
                             // tree.Add(/path/to/otherFileNames ); // etc...

      // Create an object to store the current event from the tree.
      // This is how we access the values in the tree.
      // If you want to use generator-specific values, then
      // the event type should match the type in the TTree. Valid types are
      // EventPythia, EventPepsi, EventRapgap, EventDjangoh, EventMilou.
      // If you only need shared quantities like x, Q2 and the particle list
      // you can use EventBase and the macro will be general for any Monte Carlo.
      erhic::EventPythia *event(NULL); // = new EventPythia;
                                       // EventBase* event(NULL);

      // Now associate the contents of the branch with the buffer.
      // The events are stored in a branch named event:
      tree.SetBranchAddress("event", &event); // Note &event, not event.

      // Now we can do some analysis...
      // We record the largest particle pT we find here:
      double highestPt(-1.);

      // Histograms for our analysis.
      /* TH2D Q2VsX("Q2VsX",
              "Q^{2} vs. Bjorken x;log_{10}(x);log_{10}(Q^{2})",
               100, -5., 0., 100, -2., 3. );
   TH1D ptHist("ptHist",
               "pT of charged pions",
               50, 0.0, 2.0 );
   TH1D deltaPhi("deltaPhi",
                 "Delta-phi of hadrons",
                 40, 0.0, 3.1415 );*/
      multP = hotTH1F("Multi", "dN/N vs Track Multiplicity of Final State Particles", 30, 0.5, 30.5, "", "", kRed, 0.3, 21, 1, false);
      //TH1F* multP_2 = hotTH1F("Multi", "dN/N vs Track Multiplicity of Final State Particles", 30,0.5,30.5, "", "", kBlue, 0.3, 21, 1, false);//status = -1 & 1
      Q2P = hotTH1F("Q2", "dN/dQ2 vs Q2", 30, q2_bins, "", "", kRed, 0.3, 21, 1, true);

      Q2E = new TH2F("Q2E", "Heatmap of Electron momentum vs Q2", 30, q2_bins, 30, q2_bins);
      Q2E->GetXaxis()->SetTitle("Q^{2}");
      Q2E->GetYaxis()->SetTitle("-(k-k')^{2}");
      Q2E->GetZaxis()->SetTitle("Normalized (per event) Fraction");

      // Loop over events:
      if (nEvents == 0)
         nEvents = tree.GetEntries();
      cout << "nEvents: " << nEvents << endl;
      if (debug && nEvents > 100)
         nEvents = 1;
      int nev = 0;
      int ievnn = 0;
      for (int i(0); i < nEvents; ++i)
      {

         // Read the next entry from the tree.
         tree.GetEntry(i);
         if (debug)
            cout << "Q2: " << event->GetQ2() << endl
                 << endl;
         int nParticles = event->GetNTracks();
         if (i % 10000 == 0)
            cout << "processing event " << i << " with particles " << nParticles << endl;
         //Q2 cut
         Q2P->Fill(event->GetQ2());
         if ((event->GetQ2()) < Q2_cut || (event->GetQ2() > 1e4))
         {
            ievnn++;
            continue;
         }
         nev++;
         // Fill the Q2 vs. x histogram:

         // The event contains a vector (array) of particles.

         //cout << nParticles << endl;
         // We now know the number of particles in the event, so loop over
         // the particles:
         int counter = 0;
         int electron_c = 0;
         for (int j(0); j < nParticles; ++j)
         {
            //const erhic::ParticleMCeA* particleeA = (erhic::ParticleMCeA*)event->GetTrack(j);
            const Particle *particle = event->GetTrack(j);
            // Let's just select charged pions for this example:

            int pdg = particle->GetPdgCode();
            int ks = particle->GetStatus();
            //pt cut
            double pt = particle->GetPt();
            //eta cut
            double eta = particle->GetEta();
            double px = particle->GetPx();
            double py = particle->GetPy();
            double pz = particle->GetPz();

            //final state particles only
            bool charged = false;
            bool found = false;
            for (int k = 0; k < listn; k++)
            {
               if (partl[k] == abs(pdg))
               {
                  found = true;
                  if (charl[k] != 0)
                     charged = true;
               }
               if (pdg == 80000)
               {
                  charged = true;
                  found = true;
               }
            }
            if (pdg == 11){
               double px = particle->GetPx();
               double py = particle->GetPy();
               double pz = particle->GetPz();
               double E = particle->GetE();
               float newQ2 = 
            }
            if (debug)
               cout << "found? " << found << "; charged? " << charged << endl;
            if (!found)
               cout << "not listed pdg id: " << pdg << endl;
            if (!charged && debug)
               continue;
            //if(abs(pdg) != 211 ) continue;

            //ptHist.Fill(particle->GetPt());
            counter++;
            // Update the highest pT:
            //if(particle->GetPt() > highestPt ) {
            //highestPt = particle->GetPt();
            //} // if
         } // for
         multP->Fill(counter);
      } // for
      fout = TFile::Open(Form("%s_result.root", outname.c_str()), "RECREATE");
      multP->SetMarkerSize(1);
      Q2P->Write();
      multP->Write();
      Q2P->SetMarkerSize(1);
      fout->Close();

      cout << "passed Q2" << nev << endl;
      cout << "not passed Q2 " << ievnn << endl;
   }
   else
      nEvents = 1e7;
   //std::cout << "The highest pT was " << highestPt << " GeV/c" << std::endl;

   TCanvas *c0 = new TCanvas("c0", "c0", 500, 500);
   TPad *thePad = (TPad *)c0->cd();
   TH1F *h1 = thePad->DrawFrame(0, 1e2, 30, nEvents);
   h1->SetXTitle("N_{ch}");
   h1->SetYTitle("dN/dN_{ch}");
   h1->SetTitle("Distribution of Track Multiplicity in Events");
   h1->Draw();
   if (!replot)
      multP->Write();
   //multP_2->Write();
   //multP->Scale(1./multP->GetSumOfWeights());
   //multP_2->Scale(1./multP_2->GetSumOfWeights());
   if (replot)
   {
      fout = TFile::Open(Form("%s_result.root", outname.c_str()), "READ");
      multP = (TH1F *)fout->Get("Multi");

      multP->SetDirectory(0);
      nEvents = 2e7;

      fout->Close();
   }
   multP->SetMarkerSize(1);
   multP->Draw("SAME, HIST P");

   //multP_2->Draw("SAME");
   myMarkerText(0.4, 0.85, kRed, 21, "Particle Status = 1,-1,1001", 1.2, 0.04);
   //myMarkerText( 0.6, 0.8, kBlue, 21, "Particle Abs(status) = 1", 1.2, 0.04);
   myText(0.4, 0.8, kBlack, "#sqrt{s} = 318 GeV", 0.04);
   myText(0.4, 0.75, kBlack, Form("Q^{2} > %.1f GeV", Q2_cut), 0.04);
   myText(0.4, 0.7, kBlack, "0.1 GeV < p_{T}^{trk} < 5 GeV", 0.04);
   myText(0.4, 0.65, kBlack, "-1.5 < #eta < 2.0", 0.04);
   c0->SetLogy();
   c0->SaveAs(Form("%s_mult.pdf", outname.c_str()));

   h1 = thePad->DrawFrame(1, 1e2, Q2_max, nEvents);
   h1->SetXTitle("Q^{2} (GeV^{2})");
   h1->SetYTitle("dN/dQ^{2} (GeV^{2})");
   h1->SetTitle("Distribution of Q^{2} in Events");
   if (!replot)
      Q2P->Draw("SAME Hist p");
   else
   {
      fout = TFile::Open(Form("%s_result.root", outname.c_str()), "READ");
      Q2P = (TH1F *)fout->Get("Q2");
      Q2P->SetDirectory(0);
      fout->Close();
   }
   Q2P->SetMarkerSize(1);
   Q2P->Draw("SAME Hist p");
   //Q2P->Scale(1./Q2P->GetSumOfWeights());

   c0->SetLogx();
   c0->SaveAs(Form("%s_q2.pdf", outname.c_str()));

   //ptHist.Draw();
   //canvas.Print("pt.png" );
}
