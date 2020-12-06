// read.cxx
//
// Created by TB on 6/13/11.
// Copyright 2011 BNL. All rights reserved.
//
// Example of how to read a file produced by BuildTree for a simple analysis.
// To run, in ROOT do:
// root [0] .L /path/to/read.cxx
// root [1] read("myInputFile.root", 10000 )
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/EventBase.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/EventPythia.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/Particle.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/ParticleMC.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/EventDpmjet.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/Forester.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/ForesterStatus.h.betterbutdifferent"

#ifdef __CLING__
// these are not headers - do not treat them as such - needed for ROOT6
#include "../atlasstyle-00-04-02/AtlasLabels.C"
#include "../atlasstyle-00-04-02/AtlasUtils.C"
#include "filenameparser.cpp"
#endif

#ifdef __CINT__
gROOT->LoadMacro("filenameparser.cpp");
gROOT->LoadMacro("../atlasstyle-00-04-02/AtlasLabels.C");
gROOT->LoadMacro("../atlasstyle-00-04-02/AtlasUtils.C");
#endif
const int Q2_max = 1e3;
const float Q2_cut = 5.;

const int listn = 26;
const int partl[listn] = {11, 13, 22, 81, 111,
                          130, 211, 310, 313, 321,
                          323, 411, 421, 431, 2112,
                          2212, 3122, 3222, 3112, 3212,
                          3322, 3312, 4122, 4132, 4232,
                          4212};
const int charl[listn] = {-1, -1, 0, 0, 0,
                          0, -1, 0, 0, 1,
                          1, 1, 0, 1, 0,
                          1, 0, 1, -1, 0,
                          0, -1, 1, 0, 1,
                          1};
//root -q -l 'read.cxx("/sphenix/user/xwang97/DPMJET/ep_HERA2/fort_ep_HERA2_0_1E4.root",5,true,false)' not limiting max passed Q2, debugging, limit max event to 5
//root -q -l 'read.cxx("/sphenix/user/xwang97/DPMJET/ep_HERA2/fort_ep_HERA2_0_1E4.root",0,true,false,5)' limiting max passed Q2 to 5
void read_condor(TString filename, int nEvents = 0, bool debug = false, int passedlim = 0, std::string name = "fullcut")
{

    int q2_min = 1;
    Float_t q2_bins[31];
    float initial = log(q2_min);
    float incre = log(Q2_max / q2_min) / 30.;

    for (int i = 0; i < 31; i++)
    {
        q2_bins[i] = TMath::Power(TMath::E(), initial);
        if (debug)
            cout << q2_bins[i] << "; ";
        initial = initial + incre;
    }
    if (debug)
        cout << endl;

    TChain tree("EICTree");

    // Add the file(s) we want to analyse to the chain.
    // We could add multiple files if we wanted.
    std::string inname = filename.Data();
    std::string outname;
    std::string jobname;
    int condorbatch;
    int jobnum;
    int evtnb;
    bool parser = filenameparser(inname, condorbatch, jobnum, evtnb, jobname);
    if (!parser)
    {
        cout << "parising failed" << endl;
        return;
    }

    TFile *fout;
    TH1F *multP, *Q2P, *multa, *multb, *multc;
    TH2F *Q2E;
    THStack *s;

    tree.Add(filename); // Wild cards are allowed e.g. tree.Add("*.root" );
    // tree.Add(/path/to/otherFileNames ); // etc...
    int nentries = tree.GetEntries();
    outname = "/sphenix/user/xwang97/DPMJET/" + jobname + "/" + jobname + "_"+ std::to_string(jobnum) + "_" + std::to_string(nentries) + "_result" + name;
    //TH1::AddDirectory(kFALSE);
std::ofstream statout(Form("%s_result.txt", outname.c_str()));
    if (nentries == 0)
    {
        statout << "tot: " << 0 << endl;
        statout.close();
        return;
    }
    // Create an object to store the current event from the tree.
    // This is how we access the values in the tree.
    // If you want to use generator-specific values, then
    // the event type should match the type in the TTree. Valid types are
    // EventPythia, EventPepsi, EventRapgap, EventDjangoh, EventMilou.
    // If you only need shared quantities like x, Q2 and the particle list
    // you can use EventBase and the macro will be general for any Monte Carlo.
    erhic::EventDpmjet *event(NULL);        // = new EventPythia;
                                            // EventBase* event(NULL)
    tree.SetBranchAddress("event", &event); // Note &event, not event.
    multP = hotTH1F("Multi", "dN/N vs Track Multiplicity of Final State Particles", 30, 0.5, 30.5, "", "", kRed, 0.3, 21, 1, false);
    //TH1F* multP_2 = hotTH1F("Multi", "dN/N vs Track Multiplicity of Final State Particles", 30,0.5,30.5, "", "", kBlue, 0.3, 21, 1, false);//status = -1 & 1
    Q2P = hotTH1F("Q2", "dN/dQ2 vs Q2", 30, q2_bins, "", "", kRed, 0.3, 21, 1, true);
    multa = hotTH1F("Q2_1", "dN/dQ2 vs Q2", 30, 0.5, 30.5, "", "", kBlack, 0.3, 21, 1, true);
    multb = hotTH1F("Q2_1_neg", "dN/dQ2 vs Q2", 30, 0.5, 30.5, "", "", kBlue, 0.3, 21, 1, true);
    multc = hotTH1F("Q2_1001", "dN/dQ2 vs Q2", 30, 0.5, 30.5, "", "", kMagenta, 0.3, 21, 1, true);

    Q2E = new TH2F("Q2E", "Heatmap of Electron momentum vs Q2", 30, q2_bins, 30, q2_bins);
    Q2E->GetXaxis()->SetTitle("Q^{2}");
    Q2E->GetYaxis()->SetTitle("-(k-k')^{2}");
    Q2E->GetZaxis()->SetTitle("Normalized (per event) Fraction");
    Q2E->SetMarkerStyle(21);

    // Loop over events:
    if (nEvents == 0)
    {
        nEvents = nentries;
        statout << "tot: " << nentries << endl;
    }
    std::vector<int> notlisted;
    cout << "nEvents: " << nEvents << endl;
    int nev = 0;
    int ievnn = 0;
    cout << "Start event looping......" << endl;
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    for (int i(0); i < nEvents; ++i)
    {
        int counter = 0;
        int countera = 0;
        int counterb = 0;
        int counterc = 0;
        std::vector<TLorentzVector> ein;
        std::vector<TLorentzVector> eout;
        std::vector<int> ein_ind;
        std::vector<int> eout_ind;
        // Read the next entry from the tree.
        tree.GetEntry(i);
        int nParticles = event->GetNTracks();
        if (i % 10000 == 0)
            cout << "processing event " << i << " with particles " << nParticles << endl;
        //Q2 cut

        double q2 = event->GetQ2();
        if (debug)
            cout << "Q2: " << q2 << endl;

        if ((event->GetQ2()) < Q2_cut || (event->GetQ2() > 1e4))
        {
            ievnn++;
            if (debug && passedlim == 0)
                cout << "Event " << i << " finished processing. " << endl
                     << endl;
            continue;
        }
        // Fill the Q2 vs. x histogram:

        // The event contains a vector (array) of particles.

        //cout << nParticles << endl;
        // We now know the number of particles in the event, so loop over
        // the particles:

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
            double e = particle->GetE();
            //determine incoming electron's 4-momentum
            if (pdg == 11 && ks == 21 && px == 0 && py == 0 && abs(pz) > 0)
            {
                TLorentzVector a(px, py, pz, e);
                ein_ind.push_back(j);
                ein.push_back(a);
            }
            if (pdg == 11 && ks == 1)
            {
                TLorentzVector b(px, py, pz, e);
                eout_ind.push_back(j);
                eout.push_back(b);
            }
            if (eta < -1.5 || eta > 2.0)
                continue;
            if (debug)
                cout << "eta: " << eta << endl;
            if (debug)
                cout << "pt " << pt << " GeV" << endl;
            if (pt > 5 || pt < 0.1)
                continue;
            //cout << "particle mass number: " << particleeA->massNum << endl;
            if (debug)
                cout << "ks " << ks << "; pdg " << pdg << endl;
            //final state particles only
            if (ks != 1 && ks != -1 && ks != 1001)
                continue;
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
            if (debug)
                cout << "found? " << found << "; charged? " << charged << endl;
            if (!found)
            {
                //cout << "not listed pdg id: " << pdg << endl;
                bool listed = false;
                for (int m = 0; m < notlisted.size(); m++)
                {
                    if (notlisted[m] == pdg)
                        listed = true;
                }
                if (!listed)
                    notlisted.push_back(pdg);
                continue;
            }
            if (!charged)
                continue;
            //if(abs(pdg) != 211 ) continue;

            //ptHist.Fill(particle->GetPt());
            counter++;
            if (ks == 1)
                countera++;
            if (ks == -1)
                counterb++;
            if (ks == 1001)
                counterc++;
            // Update the highest pT:
            //if(particle->GetPt() > highestPt ) {
            //highestPt = particle->GetPt();
            //} // if
        } // for
        bool scattered = false;
        int scattered_ind = -1;
        std::vector<int> wrong;
        std::vector<double> wrongval;
        for (int k = 0; k < ein.size(); k++)
        {
            for (int l = 0; l < eout.size(); l++)
            {
                double q2val = -(ein[k] - eout[l]) * (ein[k] - eout[l]);

                if (debug)
                {
                    cout << "event: " << i << "; in: " << k << "; out:" << l << endl;
                    cout << "Q2: " << q2 << "; q2 eval: " << q2val << endl;
                }
                if (round(q2) == round(q2val))
                {
                    Q2E->Fill(q2, q2val, 1. / (ein.size() * eout.size()));
                    scattered = true;
                    scattered_ind = l;
                }
                else
                {
                    wrong.push_back(k);
                    wrong.push_back(l);
                    wrongval.push_back(q2val);
                }
            }
        }
        if (!scattered)
        {
            cout << "in size: " << ein.size() << "; out size: " << eout.size() << endl;
            for (int nn = 0; nn < wrongval.size(); nn++)
            {
                const Particle *par1 = event->GetTrack(ein_ind[wrong[2 * nn]]);
                const Particle *par2 = event->GetTrack(eout_ind[wrong[2 * nn + 1]]);
                cout << "part 1: pdgid: " << par1->GetPdgCode() << "; Status: " << par1->GetStatus() << "; momentum: (" << par1->GetE() << "," << par1->GetPx() << "," << par1->GetPy() << "," << par1->GetPz() << ")" << endl;
                cout << "part 2: pdgid: " << par2->GetPdgCode() << "; Status: " << par2->GetStatus() << "; momentum: (" << par2->GetE() << "," << par2->GetPx() << "," << par2->GetPy() << "," << par2->GetPz() << ")" << endl;
                cout << "Q2: " << q2 << "; q2 eval: " << wrongval[nn] << endl;

                return;
            }
        }
        const Particle *part_sc = event->GetTrack(scattered_ind);
        if (part_sc->GetE() < 10)
            continue;
        if ((part_sc->GetE() - part_sc->GetPz()) < 47 || (part_sc->GetE() - part_sc->GetPz()) > 69)
            continue;
        nev++;
        multP->Fill(counter);
        multa->Fill(countera);
        multb->Fill(counterb);
        multc->Fill(counterc);
        Q2P->Fill(q2);
        if (debug)
            cout << "Event " << i << " finished processing"
                 << "; This is the " << nev << "-th event passing Q2 processed" << endl
                 << endl;

        if (passedlim > 0 && nev >= passedlim)
            break;
    } // for
    outname = "/sphenix/user/xwang97/DPMJET/" + jobname + "_" + std::to_string(condorbatch) + "/" + jobname + "_" + std::to_string(condorbatch) +"_"+ std::to_string(jobnum) + "_" + std::to_string(nentries) + "_"+std::to_string(nev)+ "_result" + name;
    //cout << outname << endl;
    //return;
    if (debug)
        outname += "_debug";
    cout << "Name: " << outname << endl;
    fout = TFile::Open(Form("%s.root", outname.c_str()), "RECREATE");
    multP->SetMarkerSize(1);
    Q2P->Write();
    multP->Write();
    Q2P->SetMarkerSize(1);
    Q2E->SetMarkerSize(1);
    Q2E->Write();
    s = new THStack("s", "");
    multa->SetFillColor(kBlack);
    multb->SetFillColor(kBlue);
    multc->SetFillColor(kMagenta);
    s->Add(multa);
    s->Add(multb);
    s->Add(multc);

    s->Write();
    statout << "passed Q2>5: " << nev << endl;

    fout->Close();

    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "passed Q2: " << nev << endl;
    cout << "not passed Q2 " << ievnn << endl;

    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "not listed pdg: " << endl;
    for (int m = 0; m < notlisted.size(); m++)
    {
        cout << notlisted[m] << endl;
        statout << "not listed pdgid: " << notlisted[m] << endl;
    }
    statout.close();
}
