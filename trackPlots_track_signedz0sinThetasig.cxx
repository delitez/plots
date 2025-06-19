#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TLegend.h"

void trackPlots_track_signedz0sinThetasig(){
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

    TH1F *h_track_signedz0sinThetasig_isB = new TH1F("h_track_signedz0sinThetasig_isB", "Track signed z0 sinTheta sigma", 100, -5, 5); // Histogram for Track signed z0 sinTheta sigma
    TH1F *h_track_signedz0sinThetasig_isC = new TH1F("h_track_signedz0sinThetasig_isC", "Track signed z0 sinTheta sigma", 100, -5, 5); // Histogram for Track signed z0 sinTheta sigma
    TH1F *h_track_signedz0sinThetasig_isLight = new TH1F("h_track_signedz0sinThetasig_isLight", "Track signed z0 sinTheta sigma", 100, -5, 5); // Histogram for Track signed z0 sinTheta sigma
    TH1F *h_track_signedz0sinThetasig_isOther = new TH1F("h_track_signedz0sinThetasig_isOther", "Track signed z0 sinTheta sigma", 100, -5, 5); // Histogram for Track signed z0 sinTheta sigma
    TH1F *h_track_signedz0sinThetasig_incl = new TH1F("h_track_signedz0sinThetasig_incl", "Track signed z0 sinTheta sigma", 100, -5, 5); // Histogram for inclusive Track signed z0 sinTheta sigma

    tree->Draw("track_signedz0sinThetasig >> h_track_signedz0sinThetasig_isB", "jet_label == 5"); // Draw the histogram for Track signed z0 sinTheta sigma with a condition on Track label
    tree->Draw("track_signedz0sinThetasig >> h_track_signedz0sinThetasig_isC", "jet_label == 4"); // Draw the histogram for Track signed z0 sinTheta sigma with a condition on Track label
    tree->Draw("track_signedz0sinThetasig >> h_track_signedz0sinThetasig_isLight", "jet_label == 0"); // Draw the histogram for Track signed z0 sinTheta sigma with a condition on Track label
    tree->Draw("track_signedz0sinThetasig >> h_track_signedz0sinThetasig_incl"); // Draw the histogram for inclusive Track signed z0 sinTheta sigma
    tree->Draw("track_signedz0sinThetasig >> h_track_signedz0sinThetasig_isOther", "jet_label != 5 && jet_label != 4 && jet_label != 0"); // Draw the histogram for other Track signed z0 sinTheta sigma

    TCanvas *c1 = new TCanvas("c1", "Track signed z0 sinTheta sigma Distributions", 800, 600);
    c1->SetLogy(); // Set logarithmic scale for y-axis

    h_track_signedz0sinThetasig_incl->Draw(); // Draw the histogram for inclusive Tracks on the same canvas
    h_track_signedz0sinThetasig_isLight->Draw("same"); // Draw the histogram for light Tracks on the same canvas
    h_track_signedz0sinThetasig_isB->Draw("same"); // Draw the histogram
    h_track_signedz0sinThetasig_isC->Draw("same"); // Draw the histogram for C Tracks on the same canvas
    h_track_signedz0sinThetasig_isOther->Draw("same"); // Draw the histogram for other Tracks on the same canvas

    h_track_signedz0sinThetasig_isB->SetLineColor(kBlue); // Set color for B Tracks
    h_track_signedz0sinThetasig_isC->SetLineColor(kOrange); // Set color for C Tracks
    h_track_signedz0sinThetasig_isLight->SetLineColor(kGreen); // Set color for light Tracks
    h_track_signedz0sinThetasig_isOther->SetLineColor(kRed); // Set color for other Tracks
    h_track_signedz0sinThetasig_incl->SetLineColor(kViolet); // Set color for inclusive Tracks

    h_track_signedz0sinThetasig_incl->GetXaxis()->SetTitle("Track signed z0 sinTheta sigma"); // Set x-axis title



    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_track_signedz0sinThetasig_isB, "b", "l");
    legend->AddEntry(h_track_signedz0sinThetasig_isC, "c", "l");
    legend->AddEntry(h_track_signedz0sinThetasig_isLight, "light", "l");
    legend->AddEntry(h_track_signedz0sinThetasig_isOther, "other", "l");
    legend->AddEntry(h_track_signedz0sinThetasig_incl, "incl", "l");

    legend->Draw("same");

    c1->SaveAs("track_signedz0sinThetasig.png"); // Save the canvas as an image file

    
    // number of tracks per Track: Track_ntracks
    // number of constituents per Track: Track_ncomponents



} // void trackPlots
