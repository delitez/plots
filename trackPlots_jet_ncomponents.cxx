#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TLegend.h"

void trackPlots_jet_ncomponents(){
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

    TH1F *h_jet_ncomponents_isB = new TH1F("h_jet_ncomponents_isB", "Number of jet components", 60, 0, 60); // Histogram for Number of jet components
    TH1F *h_jet_ncomponents_isC = new TH1F("h_jet_ncomponents_isC", "Number of jet components", 60, 0, 60); // Histogram for Number of jet components
    TH1F *h_jet_ncomponents_isLight = new TH1F("h_jet_ncomponents_isLight", "Number of jet components", 60, 0, 60); // Histogram for Number of jet components
    TH1F *h_jet_ncomponents_isOther = new TH1F("h_jet_ncomponents_isOther", "Number of jet components", 60, 0, 60); // Histogram for Number of jet components
    TH1F *h_jet_ncomponents_incl = new TH1F("h_jet_ncomponents_incl", "Number of jet components", 60, 0, 60); // Histogram for inclusive Number of jet components

    tree->Draw("jet_ncomponents >> h_jet_ncomponents_isB", "jet_label == 5"); // Draw the histogram for Number of jet components with a condition on jet label
    tree->Draw("jet_ncomponents >> h_jet_ncomponents_isC", "jet_label == 4"); // Draw the histogram for Number of jet components with a condition on jet label
    tree->Draw("jet_ncomponents >> h_jet_ncomponents_isLight", "jet_label == 0"); // Draw the histogram for Number of jet components with a condition on jet label
    tree->Draw("jet_ncomponents >> h_jet_ncomponents_incl"); // Draw the histogram for inclusive Number of jet components
    tree->Draw("jet_ncomponents >> h_jet_ncomponents_isOther", "jet_label != 5 && jet_label != 4 && jet_label != 0"); // Draw the histogram for other Number of jet components

    TCanvas *c1 = new TCanvas("c1", "Number of jet components Distributions", 800, 600);

    h_jet_ncomponents_incl->Draw(); // Draw the histogram for inclusive jets on the same canvas
    h_jet_ncomponents_isLight->Draw("same"); // Draw the histogram for light jets on the same canvas
    h_jet_ncomponents_isB->Draw("same"); // Draw the histogram
    h_jet_ncomponents_isC->Draw("same"); // Draw the histogram for C jets on the same canvas
    h_jet_ncomponents_isOther->Draw("same"); // Draw the histogram for other jets on the same canvas



    h_jet_ncomponents_isB->SetLineColor(kBlue); // Set color for B jets
    h_jet_ncomponents_isC->SetLineColor(kOrange); // Set color for C jets
    h_jet_ncomponents_isLight->SetLineColor(kGreen); // Set color for light jets
    h_jet_ncomponents_isOther->SetLineColor(kRed); // Set color for other jets
    h_jet_ncomponents_incl->SetLineColor(kViolet); // Set color for inclusive jets

    h_jet_ncomponents_incl->GetXaxis()->SetTitle("Number of jet components"); // Set x-axis title


    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_jet_ncomponents_isB, "b", "l");
    legend->AddEntry(h_jet_ncomponents_isC, "c", "l");
    legend->AddEntry(h_jet_ncomponents_isLight, "light", "l");
    legend->AddEntry(h_jet_ncomponents_isOther, "other", "l");
    legend->AddEntry(h_jet_ncomponents_incl, "incl", "l");

    legend->Draw("same");

    c1->SaveAs("jet_ncomponents.png"); // Save the canvas as an image file

    
    // number of tracks per jet: jet_ntracks
    // number of constituents per jet: jet_ncomponents



} // void trackPlots
