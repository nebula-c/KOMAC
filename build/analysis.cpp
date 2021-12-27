#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TF1.h"

#include "iostream"

void analysis()
{
    TFile *file = new TFile("myrun.root", "read");
    TTree *tree_step = (TTree*) file -> Get("step");
    TTree *tree_event = (TTree*) file -> Get("event");
    TGraph *g1 = new TGraph();
    TH1D *h1 = new TH1D("h1", "Silicon hitmap_x", 1024, -15, 15);
    TH1D *h2 = new TH1D("h2", "Silicon hitmap_y", 512, -7.5, 7.5);
    TH1D *h3 = new TH1D("h3", "Energy Loss", 1000, 0, 1);

    Int_t eventID, volumeID, particleID, eventID2;
    double_t rx,ry,rz;
    Char_t particleName;
    int count=1, nowEventID=0;
    bool amIdetected = false;
    double_t edep;

    tree_step->SetBranchAddress("eventID",&eventID);
    tree_step->SetBranchAddress("volumeID",&volumeID);
    tree_step->SetBranchAddress("particleID",&particleID);
    tree_step->SetBranchAddress("particleName",&particleName);
    tree_step->SetBranchAddress("prePosition.x",&rx);
    tree_step->SetBranchAddress("prePosition.y",&ry);
    tree_step->SetBranchAddress("prePosition.z",&rz);
    
    tree_event->SetBranchAddress("edep1",&edep);
    tree_event->SetBranchAddress("eventID", &eventID2);
    

    Long64_t nentries = tree_event->GetEntries();
    int i;
    for(i=0;i<nentries;i++)
    {
        tree_step->GetEntry(i);
        tree_event->GetEntry(i);
        if(volumeID==1)
        {
            if(volumeID == 1 && amIdetected == false)   //if it's a first detect in a step
            {   
                g1->SetPoint(g1->GetN(),rx,ry);
                h1->Fill(rx);
                h2->Fill(ry);
                
                count++;            
                amIdetected = true;    
            }   
            if(nowEventID!=eventID)
            {   
                amIdetected = false;
                nowEventID = eventID;
            }   
        }
        
        if(nowEventID!=eventID2)
        {                  
            std::cout<< "eventid is " << eventID2 << std::endl;
            h2->Fill(eventID2);
            h3->Fill(edep);
            amIdetected = false;
            nowEventID = eventID2;
        }   
        
    }
    
    h3->SetXTitle("MeV");
    h3->Draw();
    h2->Draw();
    // TCanvas *c1 = new TCanvas("c1");
    // TCanvas *c2 = new TCanvas("c2");
    // TCanvas *c3 = new TCanvas("c3");

    // c1->SetLogy();
    // c1->SetLogx();
    // h1->GetXaxis()->SetLimits(0,1000);

    // c1->cd();
    // g1->SetMarkerStyle(20);
    // g1->SetMarkerSize(0.5);
    // g1->GetHistogram()->SetTitle("Hitmap at Silicon");
    
    // g1->Draw("ap");
    // c2->cd();
    // h1->Draw();
    // c3->cd();
    // h2->Draw();
}