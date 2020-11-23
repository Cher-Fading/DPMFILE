void draaawww()
{
    int q2_min = 1;
    int q2_max = 1000;
    Float_t q2_bins[31];
    float initial = log(q2_min);
    float incre = log(q2_max / q2_min) / 30;
    //cout << incre << endl;

    for (int i = 0; i < 31; i++)
    {
        q2_bins[i] = TMath::Power(TMath::E(), initial);
        cout << q2_bins[i] << endl;
        initial = initial + incre;
    }
    TFile* f = TFile::Open("ep_HERA2_result.root","REAd");
    TH1F *a = (TH1F*)f->Get("Q2");

    TCanvas *c0 = new TCanvas("c0", "c0", 500, 500);
    TPad *p0 = (TPad *)c0->cd();
    TH1F *h0 = (TH1F *)p0->DrawFrame(q2_min, 1, q2_max, 2e7);
    h0->Draw();
    c0->cd();
    h0->GetXaxis()->SetTitle("x");
    h0->GetYaxis()->SetTitle("y");
    h0->GetXaxis()->SetRangeUser(q2_min, q2_max);
    h0->GetYaxis()->SetRangeUser(1, 2e7);
    c0->SetLogy();
    c0->SetLogx();
    a->Draw("SAME");
    TLine* la = new TLine(794.328,1e3,999.999,1e3);
    la->Draw("SAME");

    c0->SaveAs("test.pdf");
}