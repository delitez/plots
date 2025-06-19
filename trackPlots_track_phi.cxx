#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TLegend.h"

void trackPlots_track_phi(){
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

    TH1F *h_track_phi_isB = new TH1F("h_track_phi_isB", "Track phi", 100, -5, 5); // Histogram for Track phi
    TH1F *h_track_phi_isC = new TH1F("h_track_phi_isC", "Track phi", 100, -5, 5); // Histogram for Track phi
    TH1F *h_track_phi_isLight = new TH1F("h_track_phi_isLight", "Track phi", 100, -5, 5); // Histogram for Track phi
    TH1F *h_track_phi_isOther = new TH1F("h_track_phi_isOther", "Track phi", 100, -5, 5); // Histogram for Track phi
    TH1F *h_track_phi_incl = new TH1F("h_track_phi_incl", "Track phi", 100, -5, 5); // Histogram for inclusive Track phi

    tree->Draw("track_phi >> h_track_phi_isB", "jet_label == 5"); // Draw the histogram for Track phi with a condition on Track label
    tree->Draw("track_phi >> h_track_phi_isC", "jet_label == 4"); // Draw the histogram for Track phi with a condition on Track label
    tree->Draw("track_phi >> h_track_phi_isLight", "jet_label == 0"); // Draw the histogram for Track phi with a condition on Track label
    tree->Draw("track_phi >> h_track_phi_incl"); // Draw the histogram for inclusive Track phi
    tree->Draw("track_phi >> h_track_phi_isOther", "jet_label != 5 && jet_label != 4 && jet_label != 0"); // Draw the histogram for other Track phi

    TCanvas *c1 = new TCanvas("c1", "Track phi Distributions", 800, 600);
    c1->SetLogy(); // Set logarithmic scale for y-axis

   // h_track_phi_incl->Draw(); // Draw the histogram for inclusive Tracks on the same canvas
    h_track_phi_isLight->Draw(); // Draw the histogram for light Tracks on the same canvas
    h_track_phi_isB->Draw("same"); // Draw the histogram
    h_track_phi_isC->Draw("same"); // Draw the histogram for C Tracks on the same canvas
    h_track_phi_isOther->Draw("same"); // Draw the histogram for other Tracks on the same canvas

    h_track_phi_isB->SetLineColor(kBlue); // Set color for B Tracks
    h_track_phi_isC->SetLineColor(kOrange); // Set color for C Tracks
    h_track_phi_isLight->SetLineColor(kGreen); // Set color for light Tracks
    h_track_phi_isOther->SetLineColor(kRed); // Set color for other Tracks
    h_track_phi_incl->SetLineColor(kViolet); // Set color for inclusive Tracks

    h_track_phi_isLight->GetXaxis()->SetTitle("Track phi"); // Set x-axis title



    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_track_phi_isB, "b", "l");
    legend->AddEntry(h_track_phi_isC, "c", "l");
    legend->AddEntry(h_track_phi_isLight, "light", "l");
    legend->AddEntry(h_track_phi_isOther, "other", "l");
    //legend->AddEntry(h_track_phi_incl, "incl", "l");

    legend->Draw("same");

    c1->SaveAs("track_phi.png"); // Save the canvas as an image file

    
    // number of tracks per Track: Track_ntracks
    // number of constituents per Track: Track_ncomponents



} // void trackPlots
