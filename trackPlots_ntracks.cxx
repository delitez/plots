#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TLegend.h"

void trackPlots_ntracks(){
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

    std::vector<float> *track_pt = nullptr;
    std::vector<float> *jet_label = nullptr;

    tree->SetBranchAddress("track_pt", &track_pt);
    tree->SetBranchAddress("jet_label", &jet_label);

    TH1F *h_ntracks_isB = new TH1F("h_ntracks_isB", "Number of tracks",100, 0, 5000); // Histogram for Number of tracks
    TH1F *h_ntracks_isC = new TH1F("h_ntracks_isC", "Number of tracks",100, 0, 5000); // Histogram for Number of tracks
    TH1F *h_ntracks_isLight = new TH1F("h_ntracks_isLight", "Number of tracks",100, 0, 5000); // Histogram for Number of tracks
    TH1F *h_ntracks_isOther = new TH1F("h_ntracks_isOther", "Number of tracks",100, 0, 5000); // Histogram for Number of tracks
    TH1F *h_ntracks_incl = new TH1F("h_ntracks_incl", "Number of tracks",100, 0, 5000); // Histogram for inclusive Number of tracks
    
    TH1F *h_ntracks_isB_perEvent = new TH1F("h_ntracks_isB_perEvent", "Number of tracks",100, 0, 500); // Histogram for Number of tracks
    TH1F *h_ntracks_isC_perEvent = new TH1F("h_ntracks_isC_perEvent", "Number of tracks",100, 0, 500); // Histogram for Number of tracks
    TH1F *h_ntracks_isLight_perEvent = new TH1F("h_ntracks_isLight_perEvent", "Number of tracks",100, 0, 500); // Histogram for Number of tracks
    TH1F *h_ntracks_isOther_perEvent = new TH1F("h_ntracks_isOther_perEvent", "Number of tracks",100, 0, 500); // Histogram for Number of tracks
    TH1F *h_ntracks_incl_perEvent = new TH1F("h_ntracks_incl_perEvent", "Number of tracks",100, 0, 500); // Histogram for inclusive Number of tracks

     for(int n=0; n < tree->GetEntries(); n++) {
            tree->GetEntry(n);
            
            int ntracks_isB = 0;
            int ntracks_isC = 0;
            int ntracks_isLight = 0;
            int ntracks_isOther = 0;
            int ntracks_incl = 0;

            // Count the number of tracks for each jet label
            for (size_t j = 0; j < jet_label->size(); j++) {
                if (jet_label->at(j) == 5) { // B jets
                    ntracks_isB += track_pt->size(); // Count the number of tracks for B jets
                    // Fill for an example event
                    h_ntracks_isB_perEvent->Fill(track_pt->size());
                } else if (jet_label->at(j) == 4) { // C jets
                    ntracks_isC += track_pt->size(); // Count the number of tracks for C jets
                    h_ntracks_isC_perEvent->Fill(track_pt->size());
                } else if (jet_label->at(j) == 0) { // Light jets
                    ntracks_isLight += track_pt->size(); // Count the number of tracks for light jets
                    h_ntracks_isLight_perEvent->Fill(track_pt->size());
                } else { // Other jets
                    ntracks_isOther += track_pt->size(); // Count the number of tracks for other
                    h_ntracks_isOther_perEvent->Fill(track_pt->size());
                }
                ntracks_incl += track_pt->size(); // Count the number of tracks for inclusive jets
                h_ntracks_incl_perEvent->Fill(track_pt->size());
            }
            // Fill the histograms based on the jet labels
            h_ntracks_isB->Fill(ntracks_isB); // Fill the histogram for B jets
            h_ntracks_isC->Fill(ntracks_isC); // Fill the histogram for C
            h_ntracks_isLight->Fill(ntracks_isLight); // Fill the histogram for light jets
            h_ntracks_isOther->Fill(ntracks_isOther); // Fill the histogram for other
            h_ntracks_incl->Fill(ntracks_incl); // Fill the histogram for inclusive jets
        }


    TCanvas *c1 = new TCanvas("c1", "Number of jet tracks Distributions", 800, 600);

   // h_ntracks_isOther->Draw(); // Draw the histogram for light jets on the same canvas
    h_ntracks_isC->Draw(); // Draw the histogram for C jets on the same canvas
    h_ntracks_incl->Draw("same"); // Draw the histogram for inclusive jets on the same canvas
    h_ntracks_isB->Draw("same"); // Draw the histogram
    h_ntracks_isLight->Draw("same"); // Draw the histogram for other jets on the same canvas

    h_ntracks_isB->SetLineColor(kBlue); // Set color for B jets
    h_ntracks_isC->SetLineColor(kOrange); // Set color for C jets
    h_ntracks_isLight->SetLineColor(kGreen); // Set color for light jets
    h_ntracks_isOther->SetLineColor(kRed); // Set color for other jets
    h_ntracks_incl->SetLineColor(kViolet); // Set color for inclusive jets

    h_ntracks_isC->GetXaxis()->SetTitle("Total number of tracks"); // Set x-axis title


    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(h_ntracks_isB, "b", "l");
    legend->AddEntry(h_ntracks_isC, "c", "l");
    legend->AddEntry(h_ntracks_isLight, "light", "l");
    legend->AddEntry(h_ntracks_isOther, "other", "l");
    legend->AddEntry(h_ntracks_incl, "incl", "l");

    legend->Draw("same");
    c1->SetLogy(); // Set logarithmic scale for y-axis

    c1->SaveAs("ntracks.png"); // Save the canvas as an image file

    TCanvas *c2 = new TCanvas("c2", "Number of jet tracks Distributions", 800, 600);

   // h_ntracks_isOther->Draw(); // Draw the histogram for light jets on the same canvas
    h_ntracks_incl_perEvent->Draw(); // Draw the histogram for C jets on the same canvas
    h_ntracks_isC_perEvent->Draw("same"); // Draw the histogram for inclusive jets on the same canvas
    h_ntracks_isB_perEvent->Draw("same"); // Draw the histogram
    h_ntracks_isLight_perEvent->Draw("same"); // Draw the histogram for other jets on the same canvas

    h_ntracks_isB_perEvent->SetLineColor(kBlue); // Set color for B jets
    h_ntracks_isC_perEvent->SetLineColor(kOrange); // Set color for C jets
    h_ntracks_isLight_perEvent->SetLineColor(kGreen); // Set color for light jets
    h_ntracks_isOther_perEvent->SetLineColor(kRed); // Set color for other jets
    h_ntracks_incl_perEvent->SetLineColor(kViolet); // Set color for inclusive jets

    h_ntracks_incl_perEvent->GetXaxis()->SetTitle("Number of tracks per (last) event"); // Set x-axis title


    TLegend *legend_perEvent = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend_perEvent->AddEntry(h_ntracks_isB_perEvent, "b", "l");
    legend_perEvent->AddEntry(h_ntracks_isC_perEvent, "c", "l");
    legend_perEvent->AddEntry(h_ntracks_isLight_perEvent, "light", "l");
    legend_perEvent->AddEntry(h_ntracks_isOther_perEvent, "other", "l");
    legend_perEvent->AddEntry(h_ntracks_incl_perEvent, "incl", "l");

    legend_perEvent->Draw("same");


    c2->SaveAs("ntracks_perEvent.png"); // Save the canvas as an image file




} // void trackPlots
