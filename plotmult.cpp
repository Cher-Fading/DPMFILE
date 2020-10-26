void plotmult(string filename){
    gSystem->AddIncludePath("/afs/rhic/eic/restructured/env/pro/lib/");
  gSystem->Load("/afs/rhic/eic/restructured/env/pro/lib/libeicsmear.so");
  gInterpreter->AddIncludePath("/afs/rhic/eic/restructured/env/pro/lib/");
  gInterpreter->Load("/afs/rhic/eic/restructured/env/pro/lib/libeicsmear.so");
    TFile* f = TFile::Open(Form("%s.root",filename.c_str()));
    TTree* EICTree = (TTree*)f->Get("EICTree");
    

}