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

void draw(std::string jobname = "ep_HERA4", bool batchmode = true, int batches = 40, std::string evtnb = "1E4", std::string label = "fullcut", float come = 27.5, float s = 100., float q2_min = 5., float q2_max = 10000., float q2_max_edge = 1000.)
{
    std::string batch = batchmode ? Form("_batch_%d", batches) : "";
    TFile *f1 = TFile::Open(Form("/sphenix/user/xwang97/DPMJET/%s_%s%s_result%s.root", jobname.c_str(), evtnb.c_str(), batch.c_str(), label.c_str()), "READ");
    TH1::AddDirectory(kFALSE);
    TH1F *a1 = (TH1F *)f1->Get("Q2");
    TCanvas *c0 = new TCanvas("c0", "c0", 500, 500);
gStyle->SetOptStat(0);
    TPad *p0 = (TPad *)c0->cd();
    TH1F *h0 = (TH1F *)p0->DrawFrame(q2_min, 1, q2_max_edge, 2e7);
    h0->Draw();
    c0->cd();
    h0->GetXaxis()->SetTitle("Q^{2}");
    h0->GetYaxis()->SetTitle("Counts");
    h0->GetXaxis()->SetRangeUser(q2_min, q2_max_edge);
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
        if (a1->GetXaxis()->GetBinLowEdge(i) > q2_min && a1->GetXaxis()->GetBinLowEdge(i + 1) < q2_max_edge && y1 > 1e2)
            lx1->Draw("SAME");
        if (x1 > q2_min && x1 < q2_max_edge && y1 - a1->GetBinErrorLow(i) > 1e2 && y1 + a1->GetBinErrorUp(i) < 1e7)
            ly1->Draw("SAME");
    }
    myMarkerText(0.5, 0.85, kRed, 21, "Q^{2}", 1.2, 0.04);
    myText(0.5, 0.6, kBlack, Form("#sqrt{s} = %d GeV", (int)round(s)), 0.04);
    myText(0.5, 0.75, kBlack, Form("%.1f GeV < Q^{2} < %.1f GeV", q2_min, q2_max), 0.04);
    myText(0.5, 0.7, kBlack, "0.1 GeV < p_{T}^{trk} < 5 GeV", 0.04);
    myText(0.5, 0.65, kBlack, "-1.5 < #eta < 2.0", 0.04);
    myText(0.5, 0.55, kBlack, Form("%d GeV < E_{scattered}-p_{z,scattered} < %d GeV", (int)round(47. / 55. * 2. * come), (int)round(69. / 55. * 2. * come)));
    myText(0.5, 0.5, kBlack, Form("Number of Events: %d", entries));

    c0->SaveAs(Form("%s%s_%s_q2%s.png", jobname.c_str(), batch.c_str(), evtnb.c_str(), label.c_str()));

    TH1F *a3[30];
    TGraphErrors *a3_ave = hotTGraphErrors("multiplicity averaged vs Q2", "trksvsQ2", kRed, 0.8, 20, 1, 3003, 0.8);
    for (int i = 0; i < 30; i++)
    {
        a3[i] = (TH1F *)(f1->Get(Form("q2_ave_%d", i))->Clone());
        float lowedge = a1->GetXaxis()->GetBinLowEdge(i + 1);
        float highedge = a1->GetXaxis()->GetBinLowEdge(i + 2);
        a3_ave->SetPoint(i + 1, (lowedge + highedge) / 2., a3[i]->GetMean());
        a3_ave->SetPointError(i + 1, (highedge - lowedge) / 2., a3[i]->GetStdDev());
    }

    c0->cd();
    a3_ave->GetXaxis()->SetTitle("Q^{2}");
    a3_ave->GetYaxis()->SetTitle("<Number of Tracks>");
    a3_ave->GetXaxis()->SetRangeUser(a3_ave->GetXaxis()->GetBinLowEdge(1), a3_ave->GetXaxis()->GetBinLowEdge(31));
    //a3_ave->GetYaxis()->SetRangeUser(1e2, 2e7);
    c0->SetLogy(0);
    c0->SetLogx(1);

    a3_ave->SetMarkerSize(1);
    a3_ave->SetMarkerStyle(21);
    //gStyle->SetErrorX(0);
    a3_ave->Draw("APE");

    myText(0.5, 0.6, kBlack, Form("#sqrt{s} = %d GeV", (int)round(s)), 0.04);
    myText(0.5, 0.75, kBlack, "0.03 < y < 0.95", 0.04);
    myText(0.5, 0.7, kBlack, "0.1 GeV < p_{T}^{trk} < 5 GeV", 0.04);
    myText(0.5, 0.65, kBlack, "-1.5 < #eta_{trk} < 2.0", 0.04);
    myText(0.5, 0.55, kBlack, Form("%d GeV < E_{scattered}-p_{z,scattered} < %d GeV", (int)round(47. / 55. * 2. * come), (int)round(69. / 55. * 2. * come)));
    myText(0.5, 0.5, kBlack, Form("Number of Events: %d", entries));

    c0->SaveAs(Form("%s%s_%s_q2m_ave%s.png", jobname.c_str(), batch.c_str(), evtnb.c_str(), label.c_str()));
    cout << "low edge: " << a1->GetXaxis()->GetBinLowEdge(1) << "; " << q2_min << endl;
    cout << "high edge: " << a1->GetXaxis()->GetBinLowEdge(31) << "; " << q2_max << endl;

    c0->cd();
    TH2F *q2m = (TH2F *)f1->Get("Q2M");
    q2m->Draw("colz");
    q2m->GetXaxis()->SetTitle("Q^{2}");
    q2m->GetYaxis()->SetTitle("Track Multiplicity");
    q2m->GetZaxis()->SetTitle("Number of Events");
    q2m->GetXaxis()->SetRangeUser(q2_min, q2_max_edge);
    c0->SetLogx(1);
    c0->SetLogy(0);
gPad->SetRightMargin(0.2);
q2m->GetZaxis()->SetTitleOffset(2);
    c0->SaveAs(Form("%s%s_%s_q2m%s.png", jobname.c_str(), batch.c_str(), evtnb.c_str(), label.c_str()));
    TH2F *q2m_norm = (TH2F *)q2m->Clone();
    for (int i = 0; i < 30; i++)
    { //each q2 bin
        float norm = 0;
        for (int j = 0; j < 30; j++)
        { //each mult bin
            norm = norm + q2m->GetBinContent(i + 1, j + 1);
        }
        for (int k = 0; k < 30; k++)
        {
            q2m_norm->SetBinContent(i + 1, k + 1, norm);
        }
    }
    TH2F *q2m_normed = (TH2F *)q2m->Clone();
    q2m_normed->Divide(q2m_norm);
    c0->cd();
    q2m_normed->Draw("colz");
    q2m_normed->GetXaxis()->SetTitle("Q^{2}");
    q2m_normed->GetYaxis()->SetTitle("Track Multiplicity");
    q2m_normed->GetZaxis()->SetTitle("Fraction of Events (normalized per q2 bin)");
    q2m_normed->GetXaxis()->SetRangeUser(q2_min, q2_max_edge);
    c0->SetLogx(1);
    c0->SetLogy(0);
q2m_normed->GetZaxis()->SetTitleOffset(2);
    c0->SaveAs(Form("%s%s_%s_q2m_normed_%s.png", jobname.c_str(), batch.c_str(), evtnb.c_str(), label.c_str()));


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
gPad->SetRightMargin(0.1);
    a1->SetMarkerSize(1);
    a1->SetMarkerStyle(21);
    //gStyle->SetErrorX(0);
    a1->Draw("SAME HIST P");

    myText(0.5, 0.6, kBlack, Form("#sqrt{s} = %d GeV", (int)round(s)), 0.04);
    myText(0.5, 0.75, kBlack, Form("%.1f GeV < Q^{2} < %.1f GeV", q2_min, q2_max), 0.04);
    myText(0.5, 0.7, kBlack, "0.1 GeV < p_{T}^{trk} < 5 GeV", 0.04);
    myText(0.5, 0.65, kBlack, "-1.5 < #eta < 2.0", 0.04);
    myText(0.5, 0.55, kBlack, Form("%d GeV < E_{scattered}-p_{z,scattered} < %d GeV", (int)round(47. / 55. * 2. * come), (int)round(69. / 55. * 2. * come)));
    myText(0.5, 0.5, kBlack, Form("Number of Events: %d", entries));

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

    c0->SaveAs(Form("%s%s_%s_multi%s.png", jobname.c_str(), batch.c_str(), evtnb.c_str(), label.c_str()));

}
