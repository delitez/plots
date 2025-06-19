#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TLegend.h"

void trackPlots_track_eta(){
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

    TH1F *h_track_eta_isB = new TH1F("h_track_eta_isB", "Track eta", 100, -5, 5); // Histogram for Track eta
    TH1F *h_track_eta_isC = new TH1F("h_track_eta_isC", "Track eta", 100, -5, 5); // Histogram for Track eta
    TH1F *h_track_eta_isLight = new TH1F("h_track_eta_isLight", "Track eta", 100, -5, 5); // Histogram for Track eta
    TH1F *h_track_eta_isOther = new TH1F("h_track_eta_isOther", "Track eta", 100, -5, 5); // Histogram for Track eta
    TH1F *h_track_eta_incl = new TH1F("h_track_eta_incl", "Track eta", 100, -5, 5); // Histogram for inclusive Track eta

    tree->Draw("track_eta >> h_track_eta_isB", "jet_label == 5"); // Draw the histogram for Track eta with a condition on Track label
    tree->Draw("track_eta >> h_track_eta_isC", "jet_label == 4"); // Draw the histogram for Track eta with a condition on Track label
    tree->Draw("track_eta >> h_track_eta_isLight", "jet_label == 0"); // Draw the histogram for Track eta with a condition on Track label
    tree->Draw("track_eta >> h_track_eta_incl"); // Draw the histogram for inclusive Track eta
    tree->Draw("track_eta >> h_track_eta_isOther", "jet_label != 5 && jet_label != 4 && jet_label != 0"); // Draw the histogram for other Track eta

    TCanvas *c1 = new TCanvas("c1", "Track eta Distributions", 800, 600);
    c1->SetLogy(); // Set logarithmic scale for y-axis

    h_track_eta_incl->Draw(); // Draw the histogram for inclusive Tracks on the same canvas
    h_track_eta_isLight->Draw("same"); // Draw the histogram for light Tracks on the same canvas
    h_track_eta_isB->Draw("same"); // Draw the histogram
    h_track_eta_isC->Draw("same"); // Draw the histogram for C Tracks on the same canvas
    h_track_eta_isOther->Draw("same"); // Draw the histogram for other Tracks on the same canvas

    h_track_eta_isB->SetLineColor(kBlue); // Set color for B Tracks
    h_track_eta_isC->SetLineColor(kOrange); // Set color for C Tracks
    h_track_eta_isLight->SetLineColor(kGreen); // Set color for light Tracks
    h_track_eta_isOther->SetLineColor(kRed); // Set color for other Tracks
    h_track_eta_incl->SetLineColor(kViolet); // Set color for inclusive Tracks

    h_track_eta_incl->GetXaxis()->SetTitle("Track eta"); // Set x-axis title



    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_track_eta_isB, "b", "l");
    legend->AddEntry(h_track_eta_isC, "c", "l");
    legend->AddEntry(h_track_eta_isLight, "light", "l");
    legend->AddEntry(h_track_eta_isOther, "other", "l");
    legend->AddEntry(h_track_eta_incl, "incl", "l");

    legend->Draw("same");

    c1->SaveAs("track_eta.png"); // Save the canvas as an image file

    
    // number of tracks per Track: Track_ntracks
    // number of constituents per Track: Track_ncomponents



} // void trackPlots
