void plotmult(string filename){
    gSystem->AddIncludePath("/afs/rhic/eic/restructured/env/pro/lib/");
  gSystem->Load("/afs/rhic/eic/restructured/env/pro/lib/libeicsmear.so");
 #include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/EventBase.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/EventPythia.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/Particle.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/EventDpmjet.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/Forester.h"
#include "/afs/rhic/eic/restructured/env/pro/PACKAGES/eic-smear/include/eicsmear/erhic/ForesterStatus.h.betterbutdifferent"
    TFile* f = TFile::Open(Form("%s.root",filename.c_str()));
    TTree* EICTree = (TTree*)f->Get("EICTree");
    

}