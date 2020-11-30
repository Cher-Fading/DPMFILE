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

void draw(std::string jobname = "ep_HERA4", bool batchmode = true, int batches = 40, std::string evtnb = "1E4", std::string label = "fullcut")
{
    std::string batch = batchmode ? Form("_batch_%d", bacthes) : "";
    TFile *f1 = TFile::Open(Form("%s%s_%s_result%s.root", jobname, batch, evtnb, label), "READ");
    TH1::AddDirectory(kFALSE);
    TH1F *a1 = (TH1F *)f1->Get("Q2");
    TCanvas *c0 = new TCanvas("c0", "c0", 500, 500);
    TPad *p0 = (TPad *)c0->cd();
    TH1F *h0 = (TH1F *)p0->DrawFrame(5, 1, 1000, 2e7);
    h0->Draw();
    c0->cd();
    h0->GetXaxis()->SetTitle("Q^{2}");
    h0->GetYaxis()->SetTitle("Counts");
    h0->GetXaxis()->SetRangeUser(5, 1000);
    h0->GetYaxis()->SetRangeUser(1e2, 2e7);
    c0->SetLogy();
    c0->SetLogx();

    a1->SetMarkerSize(1);
    a1->SetMarkerStyle(21);
    int entries = a1->GetEntries();
    //gStyle->SetErrorX(0);
    a1->Scale(1, "width");
    a1->Draw("SAME HIST P");
    for (int i = 1; i < 31; i++)
    {
        double y1 = a1->GetBinContent(i);
        double x1 = a1->GetXaxis()->GetBinCenter(i);
        TLine *lx1 = new TLine(a1->GetXaxis()->GetBinLowEdge(i), y1, a1->GetXaxis()->GetBinLowEdge(i + 1), y1);
        TLine *ly1 = new TLine(x1, y1 - a1->GetBinErrorLow(i), x1, y1 + a1->GetBinErrorUp(i));
        lx1->SetLineColor(kRed);
        ly1->SetLineColor(kRed);
        if (a1->GetXaxis()->GetBinLowEdge(i) > 5 && a1->GetXaxis()->GetBinLowEdge(i + 1) < 1000 && y1 > 1e2)
            lx1->Draw("SAME");
        if (x1 > 5 && x1 < 1000 && y1 - a1->GetBinErrorLow(i) > 1e2 && y1 + a1->GetBinErrorUp(i) < 1e7)
            ly1->Draw("SAME");
    }
    myMarkerText(0.4, 0.85, kRed, 21, "Q^{2}", 1.2, 0.04);
    myText(0.4, 0.6, kBlack, "#sqrt{s} = 318 GeV", 0.04);
    myText(0.4, 0.75, kBlack, Form("Q^{2} > %.1f GeV", 5.), 0.04);
    myText(0.4, 0.7, kBlack, "0.1 GeV < p_{T}^{trk} < 5 GeV", 0.04);
    myText(0.4, 0.65, kBlack, "-1.5 < #eta < 2.0", 0.04);
    myText(0.4, 0.55, kBlack, "47 GeV < E_{scattered}-p_{z,scattered} < 69 GeV");
    myText(0.4, 0.5, kBlack, Form("Number of Events: %d", entries));

    c0->SaveAs(Form("%s%s_%s_%s_q2.pdf", jobname, batch, evtnb, label));

    a1 = (TH1F *)f1->Get("Multi");
    h0 = (TH1F *)p0->DrawFrame(0, 1, 30, 2e7);
    h0->Draw();
    c0->cd();
    h0->GetXaxis()->SetTitle("Number of Tracks");
    h0->GetYaxis()->SetTitle("Counts");
    h0->GetXaxis()->SetRangeUser(0, 30);
    h0->GetYaxis()->SetRangeUser(1e2, 2e7);
    c0->SetLogy();
    c0->SetLogx(0);

    a1->SetMarkerSize(1);
    a1->SetMarkerStyle(21);
    //gStyle->SetErrorX(0);
    a1->Draw("SAME HIST P");

    myText(0.4, 0.6, kBlack, "#sqrt{s} = 318 GeV", 0.04);
    myText(0.4, 0.75, kBlack, Form("Q^{2} > %.1f GeV", 5.), 0.04);
    myText(0.4, 0.7, kBlack, "0.1 GeV < p_{T}^{trk} < 5 GeV", 0.04);
    myText(0.4, 0.65, kBlack, "-1.5 < #eta < 2.0", 0.04);
    myText(0.4, 0.55, kBlack, "47 GeV < E_{scattered}-p_{z,scattered} < 69 GeV");
    myText(0.4, 0.5, kBlack, Form("Number of Events: %d", entries));

    for (int i = 1; i < 31; i++)
    {
        double y1 = a1->GetBinContent(i);
        double x1 = a1->GetXaxis()->GetBinCenter(i);
        TLine *lx1 = new TLine(a1->GetXaxis()->GetBinLowEdge(i), y1, a1->GetXaxis()->GetBinLowEdge(i + 1), y1);
        TLine *ly1 = new TLine(x1, y1 - a1->GetBinErrorLow(i), x1, y1 + a1->GetBinErrorUp(i));
        lx1->SetLineColor(kRed);
        ly1->SetLineColor(kRed);
        if (a1->GetXaxis()->GetBinLowEdge(i) > 0 && a1->GetXaxis()->GetBinLowEdge(i + 1) < 30 && y1 > 1e2)
            lx1->Draw("SAME");
        if (x1 > 5 && x1 < 30 && y1 - a1->GetBinErrorLow(i) > 1e2 && y1 + a1->GetBinErrorUp(i) < 1e7)
            ly1->Draw("SAME");
    }

    c0->SaveAs(Form("%s%s_%s_%s_mult.pdf", jobname, batch, evtnb, label));
}