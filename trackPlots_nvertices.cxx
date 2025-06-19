#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TLegend.h"

void trackPlots_nvertices(){
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

    std::vector<float> *recovertex_x = nullptr;
    std::vector<float> *jet_label = nullptr;

    tree->SetBranchAddress("recovertex_x", &recovertex_x);
    tree->SetBranchAddress("jet_label", &jet_label);

    TH1F *h_nvertices_isB = new TH1F("h_nvertices_isB", "Number of vertices",50, 0, 500); // Histogram for Number of vertices
    TH1F *h_nvertices_isC = new TH1F("h_nvertices_isC", "Number of vertices",50, 0, 500); // Histogram for Number of vertices
    TH1F *h_nvertices_isLight = new TH1F("h_nvertices_isLight", "Number of vertices",50, 0, 500); // Histogram for Number of vertices
    TH1F *h_nvertices_isOther = new TH1F("h_nvertices_isOther", "Number of vertices",50, 0, 500); // Histogram for Number of vertices
    TH1F *h_nvertices_incl = new TH1F("h_nvertices_incl", "Number of vertices",50, 0, 500); // Histogram for inclusive Number of vertices
    
    TH1F *h_nvertices_isB_perEvent = new TH1F("h_nvertices_isB_perEvent", "Number of vertices",50, 0, 50); // Histogram for Number of vertices
    TH1F *h_nvertices_isC_perEvent = new TH1F("h_nvertices_isC_perEvent", "Number of vertices",50, 0, 50); // Histogram for Number of vertices
    TH1F *h_nvertices_isLight_perEvent = new TH1F("h_nvertices_isLight_perEvent", "Number of vertices",50, 0, 50); // Histogram for Number of vertices
    TH1F *h_nvertices_isOther_perEvent = new TH1F("h_nvertices_isOther_perEvent", "Number of vertices",50, 0, 50); // Histogram for Number of vertices
    TH1F *h_nvertices_incl_perEvent = new TH1F("h_nvertices_incl_perEvent", "Number of vertices",50, 0, 50); // Histogram for inclusive Number of vertices

     for(int n=0; n < tree->GetEntries(); n++) {
            tree->GetEntry(n);
            
            int nvertices_isB = 0;
            int nvertices_isC = 0;
            int nvertices_isLight = 0;
            int nvertices_isOther = 0;
            int nvertices_incl = 0;

            // Count the Number of vertices for each jet label
            for (size_t j = 0; j < jet_label->size(); j++) {
                if (jet_label->at(j) == 5) { // B jets
                    nvertices_isB += recovertex_x->size(); // Count the Number of vertices for B jets
                    // Fill for an example event
                    h_nvertices_isB_perEvent->Fill(recovertex_x->size());
                } else if (jet_label->at(j) == 4) { // C jets
                    nvertices_isC += recovertex_x->size(); // Count the Number of vertices for C jets
                    h_nvertices_isC_perEvent->Fill(recovertex_x->size());
                } else if (jet_label->at(j) == 0) { // Light jets
                    nvertices_isLight += recovertex_x->size(); // Count the Number of vertices for light jets
                    h_nvertices_isLight_perEvent->Fill(recovertex_x->size());
                } else { // Other jets
                    nvertices_isOther += recovertex_x->size(); // Count the Number of vertices for other
                    h_nvertices_isOther_perEvent->Fill(recovertex_x->size());
                }
                nvertices_incl += recovertex_x->size(); // Count the Number of vertices for inclusive jets
                h_nvertices_incl_perEvent->Fill(recovertex_x->size());
            }
            // Fill the histograms based on the jet labels
            h_nvertices_isB->Fill(nvertices_isB); // Fill the histogram for B jets
            h_nvertices_isC->Fill(nvertices_isC); // Fill the histogram for C
            h_nvertices_isLight->Fill(nvertices_isLight); // Fill the histogram for light jets
            h_nvertices_isOther->Fill(nvertices_isOther); // Fill the histogram for other
            h_nvertices_incl->Fill(nvertices_incl); // Fill the histogram for inclusive jets
        }


    TCanvas *c1 = new TCanvas("c1", "Number of jet tracks Distributions", 800, 600);

   // h_nvertices_isOther->Draw(); // Draw the histogram for light jets on the same canvas
    h_nvertices_isC->Draw(); // Draw the histogram for C jets on the same canvas
    h_nvertices_incl->Draw("same"); // Draw the histogram for inclusive jets on the same canvas
    h_nvertices_isB->Draw("same"); // Draw the histogram
    h_nvertices_isLight->Draw("same"); // Draw the histogram for other jets on the same canvas

    h_nvertices_isB->SetLineColor(kBlue); // Set color for B jets
    h_nvertices_isC->SetLineColor(kOrange); // Set color for C jets
    h_nvertices_isLight->SetLineColor(kGreen); // Set color for light jets
    h_nvertices_isOther->SetLineColor(kRed); // Set color for other jets
    h_nvertices_incl->SetLineColor(kViolet); // Set color for inclusive jets

    h_nvertices_isC->GetXaxis()->SetTitle("Total number of vertices"); // Set x-axis title


    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_nvertices_isB, "b", "l");
    legend->AddEntry(h_nvertices_isC, "c", "l");
    legend->AddEntry(h_nvertices_isLight, "light", "l");
    legend->AddEntry(h_nvertices_isOther, "other", "l");
    legend->AddEntry(h_nvertices_incl, "incl", "l");

    legend->Draw("same");
    c1->SetLogy(); // Set logarithmic scale for y-axis

    c1->SaveAs("nvertices.png"); // Save the canvas as an image file

    TCanvas *c2 = new TCanvas("c2", "Number of jet tracks Distributions", 800, 600);

   // h_nvertices_isOther->Draw(); // Draw the histogram for light jets on the same canvas
    h_nvertices_incl_perEvent->Draw(); // Draw the histogram for C jets on the same canvas
    h_nvertices_isC_perEvent->Draw("same"); // Draw the histogram for inclusive jets on the same canvas
    h_nvertices_isB_perEvent->Draw("same"); // Draw the histogram
    h_nvertices_isLight_perEvent->Draw("same"); // Draw the histogram for other jets on the same canvas

    h_nvertices_isB_perEvent->SetLineColor(kBlue); // Set color for B jets
    h_nvertices_isC_perEvent->SetLineColor(kOrange); // Set color for C jets
    h_nvertices_isLight_perEvent->SetLineColor(kGreen); // Set color for light jets
    h_nvertices_isOther_perEvent->SetLineColor(kRed); // Set color for other jets
    h_nvertices_incl_perEvent->SetLineColor(kViolet); // Set color for inclusive jets

    h_nvertices_incl_perEvent->GetXaxis()->SetTitle("Number of vertices per (last) event"); // Set x-axis title


    TLegend *legend_perEvent = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend_perEvent->AddEntry(h_nvertices_isB_perEvent, "b", "l");
    legend_perEvent->AddEntry(h_nvertices_isC_perEvent, "c", "l");
    legend_perEvent->AddEntry(h_nvertices_isLight_perEvent, "light", "l");
    legend_perEvent->AddEntry(h_nvertices_isOther_perEvent, "other", "l");
    legend_perEvent->AddEntry(h_nvertices_incl_perEvent, "incl", "l");

    legend_perEvent->Draw("same");


    c2->SaveAs("nvertices_perEvent.png"); // Save the canvas as an image file



} // void trackPlots
