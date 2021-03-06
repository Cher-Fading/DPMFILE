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
const float Q2_max = 1e3;
//const float Q2_cut = 5.;

const int listn = 36;
const int partl[listn] = {11, 12, 13, 16, 22, 81, 111,
                          130, 211, 310, 313, 321,
                          323, 411, 421, 431, 441,2112,
                          2212, 3122, 3222, 3112, 3212,
                          3322, 3312, 3334, 4112, 4122,
                          4132, 4222, 4232, 4212};
const int charl[listn] = {-1, 0,-1, 0, 0, 0, 0,
                          0, 1, 0, 0, 1,
                          1, 1, 0, 1, 0,0,
                          1, 0, 1, -1, 0,
                          0, -1, -1, 0, 1,
                          0, 2, 1, 1};
//root -q -l 'read.cxx("/sphenix/user/xwang97/DPMJET/ep_HERA2/fort_ep_HERA2_0_1E4.root",5,true,false)' not limiting max passed Q2, debugging, limit max event to 5
//root -q -l 'read.cxx("/sphenix/user/xwang97/DPMJET/ep_HERA2/fort_ep_HERA2_0_1E4.root",0,true,false,5)' limiting max passed Q2 to 5
//root -b -q -l 'read_condor.cxx("'/sphenix/user/xwang97/DPMJET/eAu_EIC_high_1/fort_eAu_EIC_high_1_0_1E4.root'", 0, false, "fullcut", 1., 30.,1000.)'
void read_condorep_EIC(TString filename, int nEvents = 0, bool debug = false, std::string name = "fullcut", float Q2_cut = 5., float come = 27.5, float max_q2 = 10000.)
{

    float q2_min = Q2_cut;
    Float_t mult_bins[31];
    Float_t q2_bins[31];

    float initial = log(q2_min);
    float incre = log(Q2_max / q2_min) / 30.;
    TH1F *q2_ave[30];
    for (int i = 0; i < 31; i++)
    {
        q2_bins[i] = TMath::Power(TMath::E(), initial);
        mult_bins[i] = i + 0.5;
        if (debug)
            cout << q2_bins[i] << "; ";
        initial = initial + incre;
        if (i == 30)
            continue;
        q2_ave[i] = new TH1F(Form("q2_ave_%d", i), "q2_ave", 30, 0.5, 30.5);
    }

    float initialx = log(1e-5);
    float increx = log(1./1e-5)/25.;
    Float_t x_bins[26];
    for (int i = 0;i < 26;i++){
        x_bins[i] = TMath::Power(TMath::E(),initialx);
        initialx=initialx+increx;
        if (debug)
        cout << x_bins[i] << "; ";
    }

    //cout << q2_bins[i];}
    if (debug)
        cout << endl;

    TChain tree("EICTree");

    // Add the file(s) we want to analyse to the chain.
    // We could add multiple files if we wanted.
    std::string inname = filename.Data();
    std::string outname;
    std::string jobname;
    //int condorbatch;
    int jobnum;
    std::string evtnb;
    bool parser = filenameparser(inname, jobnum, evtnb, jobname);
    if (!parser)
    {
        cout << "parsing failed" << endl;
        return;
    }

    TFile *fout;
    TH1F *multP, *Q2P, *multa, *multb, *multc;
TH2F* Q2X;

    TH2F *Q2E;
    THStack *s;
    //TGraphErrors *Q2M_ave;
    TH2F *Q2M, *Q2M_norm, *Q2M_normed;

    tree.Add(filename); // Wild cards are allowed e.g. tree.Add("*.root" );
    // tree.Add(/path/to/otherFileNames ); // etc...
    int nentries = tree.GetEntries();
    outname = "/sphenix/user/xwang97/DPMJET/" + jobname + "/" + jobname + "_" + std::to_string(jobnum) + "_" + std::to_string(nentries) + "_" + evtnb + "_result" + name;
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
Q2X = new TH2F("Q2X","Q2 vs x",25,x_bins,30,q2_bins);
    Q2E = new TH2F("Q2E", "Heatmap of Electron momentum vs Q2", 30, q2_bins, 30, q2_bins);
    /*Q2E->GetXaxis()->SetTitle("Q^{2}");
    Q2E->GetYaxis()->SetTitle("-(k-k')^{2}");
    Q2E->GetZaxis()->SetTitle("Normalized (per event) Fraction");*/
    Q2E->SetMarkerStyle(21);

    Q2M = new TH2F("Q2M", "Heatmap of track multiplicity vs Q2", 30, q2_bins, 30, mult_bins);
    /*Q2M->GetXaxis()->SetTitle("Q^{2}");
    Q2M->GetYaxis()->SetTitle("N_{ch}");
    Q2M->GetZaxis()->SetTitle("Normalized (per Q2 bin) Fraction");*/
    Q2M->SetMarkerStyle(20);
    Q2M_norm = new TH2F("Q2M_norm", "Heatmap of track multiplicity vs Q2", 30, q2_bins, 30, mult_bins);
    //Q2M_ave = hotTGraphErrors("multiplicity averaged vs Q2", "trksvsQ2", kRed, 0.8, 20, 1, 3003, 0.8);

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
        Q2X->Fill(event->GetX(),q2);
        if (debug)
            cout << "Q2: " << q2 << endl;

        if ((event->GetQ2()) < Q2_cut || (event->GetQ2() > max_q2))
        {
            ievnn++;
            //if (debug && passedlim == 0)
            if (debug)
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
            if (pt > 5 || pt < 0.1)
                continue;
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
if (debug)
                cout << "eta: " << eta << endl;
            if (debug)
                cout << "pt " << pt << " GeV" << endl;
            //cout << "particle mass number: " << particleeA->massNum << endl;
            if (debug)
                cout << "ks " << ks << "; pdg " << pdg << endl;
            //final state particles only
            
            
            if (debug)
                cout << "found? " << found << "; charged? " << charged << endl;
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
                if (abs(q2 - q2val) <= 0.5)
                {
                    Q2E->Fill(q2, q2val, 1. / (ein.size() * eout.size()));
                    scattered = true;
                    scattered_ind = l;
		    const Particle *part_sct = event->GetTrack(scattered_ind);
		    if (debug){
		    cout << "scattered: " << i << part_sct->GetE() << endl;
		    cout << "scattered: " << part_sct->GetE() - part_sct->GetPz() << endl;
		    cout << "come: " << come << endl;}
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
        if (part_sc->GetE() < (10. / 27.5 * come))
        {
            ievnn++;
            continue;
        }
        if ((part_sc->GetE() - part_sc->GetPz()) < round((47. / 55.) * (come * 2.)) || (part_sc->GetE() - part_sc->GetPz()) > round((69. / 55.) * (come * 2.)))
        {
            ievnn++;
            continue;
        }
        nev++;
        multP->Fill(counter);
        multa->Fill(countera);
        multb->Fill(counterb);
        multc->Fill(counterc);

        if (q2 <= 1e3)
        {
            Q2P->Fill(q2);
            Q2M->Fill(q2, counter);
            //cout << q2 << " " << (int)(TMath::Log(q2 / q2_min) / incre)<< endl;
            q2_ave[(int)(TMath::Log(q2 / q2_min) / incre)]->Fill(counter);
            for (int i = 1; i < 31; i++)
            {
                Q2M_norm->Fill(q2, i);
            }
        }
        if (debug)
            cout << "Event " << i << " finished processing"
                 << "; This is the " << nev << "-th event passing Q2 processed" << endl
                 << endl;

        //if (passedlim > 0 && nev >= passedlim)
        //    break;
    } // for
    outname = "/sphenix/user/xwang97/DPMJET/" + jobname + "/" + jobname + "_" + std::to_string(jobnum) + "_" + std::to_string(nentries) + "_" + evtnb + "_" + std::to_string(nev) + "_result" + name;
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
    statout << "passed " + name + ": " << nev << endl;
    Q2M_normed=(TH2F*)Q2M->Clone();
    Q2M_normed->Divide(Q2M_norm);
    Q2M->Write();
    Q2X->Write();
    Q2M_norm->Write();
    Q2M_normed->Write();
    for (int i = 0; i < 30; i++)
    {
        q2_ave[i]->Write();
        //Q2M_ave->SetPoint(i + 1, (q2_bins[i] + q2_bins[i + 1]) / 2., q2_ave[i]->GetMean());
        //Q2M_ave->SetPointError(i + 1, (q2_bins[i] - q2_bins[i + 1]) / 2., q2_ave[i]->GetStdDev());
    }
    //Q2M_ave->Write();
    fout->Close();

    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "passed " + name + ": " << nev << endl;
    cout << "not passed " + name + ": " << ievnn << endl;

    cout << "--------------------------------------------------------------------------------------" << endl;
    cout << "not listed pdg: " << endl;
    for (int m = 0; m < notlisted.size(); m++)
    {
        cout << notlisted[m] << endl;
        statout << "not listed pdgid: " << notlisted[m] << endl;
    }
    statout.close();
}
