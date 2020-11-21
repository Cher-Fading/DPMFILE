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
        //cout << q2_bins[i] << endl;
        initial = initial + incre;
    }
    TH1F *a = new TH1F("test", "test", 30, q2_bins);
    a->SetMarkerStyle(21);
    a->SetMarkerSize(1);
    a->Sumw2();
    TF1 *f1 = new TF1("f1", "log(1000./x)", 1, 1000);

    //f1->SetParameter(0, incre);
    //cout << f1->GetRandom() << endl;
    int ievt = 100000;
    for (int i = 0; i < ievt; i++)
    {
        double r = f1->GetRandom();
        a->Fill(r);
    }

    TCanvas *c0 = new TCanvas("c0", "c0", 500, 500);
    TPad *p0 = (TPad *)c0->cd();
    TH1F *h0 = (TH1F *)p0->DrawFrame(q2_min, 1, q2_max, ievt);
    h0->Draw();
    c0->cd();
    h0->GetXaxis()->SetTitle("x");
    h0->GetYaxis()->SetTitle("y");
    h0->GetXaxis()->SetRangeUser(q2_min, q2_max);
    h0->GetYaxis()->SetRangeUser(1, ievt);
    a->Draw("SAME");
    a->SetMarkerStyle(21);
    a->SetMarkerSize(1);
    TGraphErrors *b = new TGraphErrors();
    for (int i = 1; i < 31; i++)
    {
        b->SetPoint(i, (q2_bins[i] + q2_bins[i - 1]) / 2., a->GetBinContent(i));
        b->SetPointError(i, (q2_bins[i] - q2_bins[i - 1]) / 2., sqrt(a->GetBinContent(i)));
    }

    TFile *f = TFile::Open("test.root", "RECREATE");
    a->Write();
    b->Write("b");
    c0->SetLogx();
    c0->SetLogy();    
    f1->Write();
    c0->SaveAs("test.pdf");
}