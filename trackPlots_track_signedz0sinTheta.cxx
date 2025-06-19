#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TLegend.h"

void trackPlots_track_signedz0sinTheta(){
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

    TH1F *h_track_signedz0sinTheta_isB = new TH1F("h_track_signedz0sinTheta_isB", "Track signed z0 sinTheta", 200, -1, 1); // Histogram for Track signed z0 sinTheta
    TH1F *h_track_signedz0sinTheta_isC = new TH1F("h_track_signedz0sinTheta_isC", "Track signed z0 sinTheta", 200, -1, 1); // Histogram for Track signed z0 sinTheta
    TH1F *h_track_signedz0sinTheta_isLight = new TH1F("h_track_signedz0sinTheta_isLight", "Track signed z0 sinTheta", 200, -1, 1); // Histogram for Track signed z0 sinTheta
    TH1F *h_track_signedz0sinTheta_isOther = new TH1F("h_track_signedz0sinTheta_isOther", "Track signed z0 sinTheta", 200, -1, 1); // Histogram for Track signed z0 sinTheta
    TH1F *h_track_signedz0sinTheta_incl = new TH1F("h_track_signedz0sinTheta_incl", "Track signed z0 sinTheta", 200, -1, 1); // Histogram for inclusive Track signed z0 sinTheta

    tree->Draw("track_signedz0sinTheta >> h_track_signedz0sinTheta_isB", "jet_label == 5"); // Draw the histogram for Track signed z0 sinTheta with a condition on Track label
    tree->Draw("track_signedz0sinTheta >> h_track_signedz0sinTheta_isC", "jet_label == 4"); // Draw the histogram for Track signed z0 sinTheta with a condition on Track label
    tree->Draw("track_signedz0sinTheta >> h_track_signedz0sinTheta_isLight", "jet_label == 0"); // Draw the histogram for Track signed z0 sinTheta with a condition on Track label
    tree->Draw("track_signedz0sinTheta >> h_track_signedz0sinTheta_incl"); // Draw the histogram for inclusive Track signed z0 sinTheta
    tree->Draw("track_signedz0sinTheta >> h_track_signedz0sinTheta_isOther", "jet_label != 5 && jet_label != 4 && jet_label != 0"); // Draw the histogram for other Track signed z0 sinTheta

    TCanvas *c1 = new TCanvas("c1", "Track signed z0 sinTheta Distributions", 800, 600);
    c1->SetLogy(); // Set logarithmic scale for y-axis

    h_track_signedz0sinTheta_incl->Draw(); // Draw the histogram for inclusive Tracks on the same canvas
    h_track_signedz0sinTheta_isLight->Draw("same"); // Draw the histogram for light Tracks on the same canvas
    h_track_signedz0sinTheta_isB->Draw("same"); // Draw the histogram
    h_track_signedz0sinTheta_isC->Draw("same"); // Draw the histogram for C Tracks on the same canvas
    h_track_signedz0sinTheta_isOther->Draw("same"); // Draw the histogram for other Tracks on the same canvas

    h_track_signedz0sinTheta_isB->SetLineColor(kBlue); // Set color for B Tracks
    h_track_signedz0sinTheta_isC->SetLineColor(kOrange); // Set color for C Tracks
    h_track_signedz0sinTheta_isLight->SetLineColor(kGreen); // Set color for light Tracks
    h_track_signedz0sinTheta_isOther->SetLineColor(kRed); // Set color for other Tracks
    h_track_signedz0sinTheta_incl->SetLineColor(kViolet); // Set color for inclusive Tracks

    h_track_signedz0sinTheta_incl->GetXaxis()->SetTitle("Track signed z0 sinTheta"); // Set x-axis title



    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_track_signedz0sinTheta_isB, "b", "l");
    legend->AddEntry(h_track_signedz0sinTheta_isC, "c", "l");
    legend->AddEntry(h_track_signedz0sinTheta_isLight, "light", "l");
    legend->AddEntry(h_track_signedz0sinTheta_isOther, "other", "l");
    legend->AddEntry(h_track_signedz0sinTheta_incl, "incl", "l");

    legend->Draw("same");

    c1->SaveAs("track_signedz0sinTheta.png"); // Save the canvas as an image file

    
    // number of tracks per Track: Track_ntracks
    // number of constituents per Track: Track_ncomponents



} // void trackPlots
