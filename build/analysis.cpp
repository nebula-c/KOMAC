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
    TH1D *h1 = new TH1D("h1", "particles", 1000, 0, 3000);
    TCanvas *c1 = new TCanvas("c1");

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
    

    Long64_t nentries = tree_step->GetEntries();
    int i;
    cout << "nentries : " << nentries << endl;
    for(i=0;i<=nentries;i++)
    {
        tree_step->GetEntry(i);
        tree_event->GetEntry(i);
        if(volumeID == 9)// && amIdetected == false)   //if it's a first detect in a step
        {   
            
            if(particleID!=2212 && particleID != 11)
            {
                // cout << "event ID : " << eventID << endl;
                // cout << "particle ID : " << particleID << endl;
            }
            h1->Fill(particleID);
            count++;            
            //amIdetected = true;    
        }   
        if(nowEventID!=eventID)
        {   
            //amIdetected = false;
            nowEventID = eventID;
        }   
        
        
        // if(nowEventID!=eventID2)s
        // {                  
        //     std::cout<< "eventid is " << eventID2 << ", edep is " << edep << std::endl;
        //     amIdetected = false;
        //     nowEventID = eventID2;
        // }   

    }
    
    // i++;
    // tree_event->GetEntry(i);
    // h3->Fill(edep);
    c1->SetLogy();
    h1->Draw();
}