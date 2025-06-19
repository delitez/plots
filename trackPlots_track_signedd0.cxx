#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TLegend.h"

void trackPlots_track_signedd0(){
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

    TH1F *h_track_signedd0_isB = new TH1F("h_track_signedd0_isB", "Track signed d0", 200, -1, 1); // Histogram for Track signed d0
    TH1F *h_track_signedd0_isC = new TH1F("h_track_signedd0_isC", "Track signed d0", 200, -1, 1); // Histogram for Track signed d0
    TH1F *h_track_signedd0_isLight = new TH1F("h_track_signedd0_isLight", "Track signed d0", 200, -1, 1); // Histogram for Track signed d0
    TH1F *h_track_signedd0_isOther = new TH1F("h_track_signedd0_isOther", "Track signed d0", 200, -1, 1); // Histogram for Track signed d0
    TH1F *h_track_signedd0_incl = new TH1F("h_track_signedd0_incl", "Track signed d0", 200, -1, 1); // Histogram for inclusive Track signed d0

    tree->Draw("track_signedd0 >> h_track_signedd0_isB", "jet_label == 5"); // Draw the histogram for Track signed d0 with a condition on Track label
    tree->Draw("track_signedd0 >> h_track_signedd0_isC", "jet_label == 4"); // Draw the histogram for Track signed d0 with a condition on Track label
    tree->Draw("track_signedd0 >> h_track_signedd0_isLight", "jet_label == 0"); // Draw the histogram for Track signed d0 with a condition on Track label
    tree->Draw("track_signedd0 >> h_track_signedd0_incl"); // Draw the histogram for inclusive Track signed d0
    tree->Draw("track_signedd0 >> h_track_signedd0_isOther", "jet_label != 5 && jet_label != 4 && jet_label != 0"); // Draw the histogram for other Track signed d0

    TCanvas *c1 = new TCanvas("c1", "Track signed d0 Distributions", 800, 600);
    c1->SetLogy(); // Set logarithmic scale for y-axis

    h_track_signedd0_incl->Draw(); // Draw the histogram for inclusive Tracks on the same canvas
    h_track_signedd0_isLight->Draw("same"); // Draw the histogram for light Tracks on the same canvas
    h_track_signedd0_isB->Draw("same"); // Draw the histogram
    h_track_signedd0_isC->Draw("same"); // Draw the histogram for C Tracks on the same canvas
    h_track_signedd0_isOther->Draw("same"); // Draw the histogram for other Tracks on the same canvas

    h_track_signedd0_isB->SetLineColor(kBlue); // Set color for B Tracks
    h_track_signedd0_isC->SetLineColor(kOrange); // Set color for C Tracks
    h_track_signedd0_isLight->SetLineColor(kGreen); // Set color for light Tracks
    h_track_signedd0_isOther->SetLineColor(kRed); // Set color for other Tracks
    h_track_signedd0_incl->SetLineColor(kViolet); // Set color for inclusive Tracks

    h_track_signedd0_incl->GetXaxis()->SetTitle("Track signed d0"); // Set x-axis title



    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_track_signedd0_isB, "b", "l");
    legend->AddEntry(h_track_signedd0_isC, "c", "l");
    legend->AddEntry(h_track_signedd0_isLight, "light", "l");
    legend->AddEntry(h_track_signedd0_isOther, "other", "l");
    legend->AddEntry(h_track_signedd0_incl, "incl", "l");

    legend->Draw("same");

    c1->SaveAs("track_signedd0.png"); // Save the canvas as an image file

    
    // number of tracks per Track: Track_ntracks
    // number of constituents per Track: Track_ncomponents



} // void trackPlots
