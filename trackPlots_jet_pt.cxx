#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TLegend.h"

void trackPlots_jet_pt(){
    gStyle->SetOptStat(0); // Disable statistics box
    // Open the root file
    TFile *file = TFile::Open("/Users/delitez/atlas/acts_v2/ci-dependencies/trackToTruth_output/track_to_truth_jets_TEST_10e3_ev.root");
    if (!file || !file->IsOpen()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    // Get the TTree from the file
    TTree *tree = (TTree*)file->Get("events");
    if (!tree) {
        std::cerr << "Error retrieving TTree from file." << std::endl;
        return;
    }

    TH1F *h_jet_pt_isB = new TH1F("h_jet_pt_isB", "Jet pT", 100, 0, 100); // Histogram for jet pT
    TH1F *h_jet_pt_isC = new TH1F("h_jet_pt_isC", "Jet pT", 100, 0, 100); // Histogram for jet pT
    TH1F *h_jet_pt_isLight = new TH1F("h_jet_pt_isLight", "Jet pT", 100, 0, 100); // Histogram for jet pT
    TH1F *h_jet_pt_isOther = new TH1F("h_jet_pt_isOther", "Jet pT", 100, 0, 100); // Histogram for jet pT
    TH1F *h_jet_pt_incl = new TH1F("h_jet_pt_incl", "Jet pT (Inclusive)", 100, 0, 100); // Histogram for inclusive jet pT

    tree->Draw("jet_pt >> h_jet_pt_isB", "jet_label == 5"); // Draw the histogram for jet pT with a condition on jet label
    tree->Draw("jet_pt >> h_jet_pt_isC", "jet_label == 4"); // Draw the histogram for jet pT with a condition on jet label
    tree->Draw("jet_pt >> h_jet_pt_isLight", "jet_label == 0"); // Draw the histogram for jet pT with a condition on jet label
    tree->Draw("jet_pt >> h_jet_pt_incl"); // Draw the histogram for inclusive jet pT
    tree->Draw("jet_pt >> h_jet_pt_isOther", "jet_label != 5 && jet_label != 4 && jet_label != 0"); // Draw the histogram for other jet pT

    TCanvas *c1 = new TCanvas("c1", "Jet pT Distributions", 800, 600);
    c1->SetLogy(); // Set logarithmic scale for y-axis

    h_jet_pt_isLight->Draw(); // Draw the histogram for light jets on the same canvas
    h_jet_pt_isB->Draw("same"); // Draw the histogram
    h_jet_pt_isC->Draw("same"); // Draw the histogram for C jets on the same canvas
    h_jet_pt_isOther->Draw("same"); // Draw the histogram for other jets on the same canvas
    h_jet_pt_incl->Draw("same"); // Draw the histogram for inclusive jets on the same canvas


    h_jet_pt_isB->SetLineColor(kBlue); // Set color for B jets
    h_jet_pt_isC->SetLineColor(kOrange); // Set color for C jets
    h_jet_pt_isLight->SetLineColor(kGreen); // Set color for light jets
    h_jet_pt_isOther->SetLineColor(kRed); // Set color for other jets
    h_jet_pt_incl->SetLineColor(kViolet); // Set color for inclusive jets

    h_jet_pt_isLight->GetXaxis()->SetTitle("Jet pT (GeV)"); // Set x-axis title



    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_jet_pt_isB, "b", "l");
    legend->AddEntry(h_jet_pt_isC, "c", "l");
    legend->AddEntry(h_jet_pt_isLight, "light", "l");
    legend->AddEntry(h_jet_pt_isOther, "other", "l");
    legend->AddEntry(h_jet_pt_incl, "incl", "l");

    legend->Draw("same");

    c1->SaveAs("jet_pt.png"); // Save the canvas as an image file

    
    // number of tracks per jet: jet_ntracks
    // number of constituents per jet: jet_ncomponents



} // void trackPlots
