void draaawww()
{
    TFile *f1 = TFile::Open("ep_HERA2_nocut_result.root", "REAd");
    TFile *f2 = TFile::Open("ep_HERA2_cut_result.root", "REAd");
    TH1F *a1 = (TH1F *)f1->Get("Q2");
    TH1F *a2 = (TH1F *)f2->Get("Q2");
    TCanvas *c0 = new TCanvas("c0", "c0", 500, 500);
    TPad *p0 = (TPad *)c0->cd();
    TH1F *h0 = (TH1F *)p0->DrawFrame(1, 1, 1000, 2e7);
    h0->Draw();
    c0->cd();
    h0->GetXaxis()->SetTitle("x");
    h0->GetYaxis()->SetTitle("y");
    h0->GetXaxis()->SetRangeUser(1, 1000);
    h0->GetYaxis()->SetRangeUser(1e2, 2e7);
    c0->SetLogy();
    c0->SetLogx();

    a1->SetMarkerSize(1);
    a1->SetMarkerStyle(21);
    //gStyle->SetErrorX(0);
    a1->Draw("SAME HIST P");
    a2->SetMarkerSize(0.8);
    a2->SetMarkerStyle(20);
    a2->SetLineColor(kBlue);
    a2->SetMarkerColor(kBlue);
    a2->SetLineStyle(2);
    a2->Draw("SAME HIST P");
    for (int i = 1; i < 31; i++)
    {
        double y1 = a1->GetBinContent(i);
        double x1 = a1->GetXaxis()->GetBinCenter(i);
        TLine *lx1 = new TLine(a1->GetXaxis()->GetBinLowerEdge(i), y1, a1->GetXaxis()->GetBinLowerEdge(i + 1), y1);
        TLine *ly1 = new TLine(x1, y1 - a1->GetBinErrorLow(i), x1, y1 + a1->GetBinErrorUp(i));
        lx1->SetLineColor(kRed);
        ly1->SetLineColor(kRed);
        lx1->Draw("SAME");
        ly1->Draw("SAME");
        double y2 = a2->GetBinContent(i);
        double x2 = a2->GetXaxis()->GetBinCenter(i);
        TLine *lx2 = new TLine(a2->GetXaxis()->GetBinLowerEdge(i), y2, a2->GetXaxis()->GetBinLowerEdge(i + 1), y2);
        TLine *ly2 = new TLine(x2, y2 - a1->GetBinErrorLow(i), x2, y2 + a1->GetBinErrorUp(i));
        lx2->SetLineColor(kRed);
        ly2->SetLineColor(kRed);
        lx2->Draw("SAME");
        ly2->Draw("SAME");
    }

    c0->SaveAs("test.pdf");
}