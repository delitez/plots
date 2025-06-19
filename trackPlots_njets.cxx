#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TLegend.h"

void trackPlots_njets(){
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

    TH1F *h_njets_isB = new TH1F("h_njets_isB", "Number of jets",20, -0.5, 19.5); // Histogram for Number of vertices
    TH1F *h_njets_isC = new TH1F("h_njets_isC", "Number of jets",20, -0.5, 19.5); // Histogram for Number of vertices
    TH1F *h_njets_isLight = new TH1F("h_njets_isLight", "Number of jets",20, -0.5, 19.5); // Histogram for Number of vertices
    TH1F *h_njets_isOther = new TH1F("h_njets_isOther", "Number of jets",20, -0.5, 19.5); // Histogram for Number of vertices
    TH1F *h_njets_incl = new TH1F("h_njets_incl", "Number of jets (Inclusive)", 20, 0, 20); // Histogram for inclusive Number of jets
   

    std::vector<float> *jet_pt = nullptr;
    std::vector<float> *jet_label = nullptr;

    tree->SetBranchAddress("jet_pt", &jet_pt);
    tree->SetBranchAddress("jet_label", &jet_label);

    for(int n=0; n < tree->GetEntries(); n++) {
            tree->GetEntry(n);
            
            int isB = 0;
            int isC = 0;
            int isLight = 0;
            int isOther = 0;
            int incl = 0;
            for (size_t j = 0; j < jet_label->size(); j++) {
                if (jet_label->at(j) == 5) {isB++;}
                else if (jet_label->at(j) == 4) {isC++;}
                else if (jet_label->at(j) == 0) {isLight++;}
                else {isOther++;}
                incl++;
            }
                h_njets_isB->Fill(isB); // Fill the histogram for B jets
                h_njets_isC->Fill(isC); // Fill the histogram for C jets
                h_njets_isLight->Fill(isLight); // Fill the histogram for light jets
                h_njets_isOther->Fill(isOther); // Fill the histogram for other jets
                h_njets_incl->Fill(incl);
        }
        


    TCanvas *c1 = new TCanvas("c1", "Number of jet tracks Distributions", 800, 600);

    h_njets_isOther->Draw(); // Draw the histogram for other jets on the same canvas
    h_njets_isB->Draw("same"); // Draw the histogram

    h_njets_isLight->Draw("same"); // Draw the histogram for light jets on the same canvas
    h_njets_incl->Draw("same"); // Draw the histogram for inclusive jets on the same canvas
    h_njets_isC->Draw("same"); // Draw the histogram for C jets on the same canvas
   

    h_njets_isB->SetLineColor(kBlue); // Set color for B jets
    h_njets_isC->SetLineColor(kOrange); // Set color for C jets
    h_njets_isLight->SetLineColor(kGreen); // Set color for light jets
    h_njets_isOther->SetLineColor(kRed); // Set color for other jets
    h_njets_incl->SetLineColor(kViolet); // Set color for inclusive jets

    h_njets_isLight->GetXaxis()->SetTitle("Number of jets"); // Set x-axis title


    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_njets_isB, "b", "l");
    legend->AddEntry(h_njets_isC, "c", "l");
    legend->AddEntry(h_njets_isLight, "light", "l");
    legend->AddEntry(h_njets_isOther, "other", "l");
    legend->AddEntry(h_njets_incl, "incl", "l");

    legend->Draw("same");

     c1->SaveAs("njets.png"); // Save the canvas as an image file




} // void trackPlots
