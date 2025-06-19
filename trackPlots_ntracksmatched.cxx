#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TLegend.h"

void trackPlots_ntracksmatched(){
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

    TH1F *h_track_matched_jet_idx_isB = new TH1F("h_track_matched_jet_idx_isB", "Tracks IDs matched to jets", 15, 0 , 15); // Histogram for Tracks IDs matched to jets
    TH1F *h_track_matched_jet_idx_isC = new TH1F("h_track_matched_jet_idx_isC", "Tracks IDs matched to jets", 15, 0 , 15); // Histogram for Tracks IDs matched to jets
    TH1F *h_track_matched_jet_idx_isLight = new TH1F("h_track_matched_jet_idx_isLight", "Tracks IDs matched to jets", 15, 0 , 15); // Histogram for Tracks IDs matched to jets
    TH1F *h_track_matched_jet_idx_isOther = new TH1F("h_track_matched_jet_idx_isOther", "Tracks IDs matched to jets", 15, 0 , 15); // Histogram for Tracks IDs matched to jets
    TH1F *h_track_matched_jet_idx_incl = new TH1F("h_track_matched_jet_idx_incl", "Tracks IDs matched to jets", 15, 0 , 15); // Histogram for inclusive Tracks IDs matched to jets

    tree->Draw("track_matched_jet_idx >> h_track_matched_jet_idx_isB", "jet_label == 5"); // Draw the histogram for Tracks IDs matched to jets with a condition on jet label
    tree->Draw("track_matched_jet_idx >> h_track_matched_jet_idx_isC", "jet_label == 4"); // Draw the histogram for Tracks IDs matched to jets with a condition on jet label
    tree->Draw("track_matched_jet_idx >> h_track_matched_jet_idx_isLight", "jet_label == 0"); // Draw the histogram for Tracks IDs matched to jets with a condition on jet label
    tree->Draw("track_matched_jet_idx >> h_track_matched_jet_idx_incl"); // Draw the histogram for inclusive Tracks IDs matched to jets
    tree->Draw("track_matched_jet_idx >> h_track_matched_jet_idx_isOther", "jet_label != 5 && jet_label != 4 && jet_label != 0"); // Draw the histogram for other Tracks IDs matched to jets

    TCanvas *c1 = new TCanvas("c1", "Tracks IDs matched to jets Distributions", 800, 600);

    c1->SetLogy(); // Set logarithmic scale for y-axis
    h_track_matched_jet_idx_incl->Draw(); // Draw the histogram for inclusive jets on the same canvas
    h_track_matched_jet_idx_isLight->Draw("same"); // Draw the histogram for light jets on the same canvas
    h_track_matched_jet_idx_isB->Draw("same"); // Draw the histogram
    h_track_matched_jet_idx_isC->Draw("same"); // Draw the histogram for C jets on the same canvas
    h_track_matched_jet_idx_isOther->Draw("same"); // Draw the histogram for other jets on the same canvas



    h_track_matched_jet_idx_isB->SetLineColor(kBlue); // Set color for B jets
    h_track_matched_jet_idx_isC->SetLineColor(kOrange); // Set color for C jets
    h_track_matched_jet_idx_isLight->SetLineColor(kGreen); // Set color for light jets
    h_track_matched_jet_idx_isOther->SetLineColor(kRed); // Set color for other jets
    h_track_matched_jet_idx_incl->SetLineColor(kViolet); // Set color for inclusive jets

    h_track_matched_jet_idx_incl->GetXaxis()->SetTitle("Track IDs matched to jets"); // Set x-axis title


    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_track_matched_jet_idx_isB, "b", "l");
    legend->AddEntry(h_track_matched_jet_idx_isC, "c", "l");
    legend->AddEntry(h_track_matched_jet_idx_isLight, "light", "l");
    legend->AddEntry(h_track_matched_jet_idx_isOther, "other", "l");
    legend->AddEntry(h_track_matched_jet_idx_incl, "incl", "l");

    legend->Draw("same");

    c1->SaveAs("track_matched_jet_idx.png"); // Save the canvas as an image file

    
    // number of tracks per jet: track_matched_jet_idx
    // number of constituents per jet: track_matched_jet_idx



} // void trackPlots
