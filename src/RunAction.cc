//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
// #include "Run.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4AnalysisManager.hh" 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
{


  // // set printing event number per each event
  // G4RunManager::GetRunManager()->SetPrintProgress(1);

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in Analysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  // Declaring the analysisManager in RunAction ensures multi-threading

  // Create directories
  // analysisManager->SetHistoDirectoryName("histograms");
  // analysisManager->SetNtupleDirectoryName("ntuple");
  // analysisManager->SetVerboseLevel(1);
  analysisManager->SetVerboseLevel(0);
  analysisManager->SetNtupleMerging(true);
  //   // Note: merging ntuples is available only with Root output

  // Book histograms, ntuple
  //

  // Creating histograms
  // analysisManager->CreateH1("col" ,"Edep in collimator", 100, 0., 15*keV);
  // analysisManager->CreateH1("det1" ,"Edep in detector 1", 100, 0., 15*keV);
  // analysisManager->CreateH1("det2" ,"Edep in detector 2", 100, 0., 15*keV);
  // analysisManager->CreateH1("det3" ,"Edep in detector 3", 100, 0., 15*keV);
  // analysisManager->CreateH1("det4" ,"Edep in detector 4", 100, 0., 15*keV);
  // analysisManager->CreateH1("det5" ,"Edep in detector 5", 100, 0., 15*keV);
  // analysisManager->CreateH1("det6" ,"Edep in detector 6", 100, 0., 15*keV);
  // analysisManager->CreateH1("det7" ,"Edep in detector 7", 100, 0., 15*keV);
  // analysisManager->CreateH1("det8" ,"Edep in detector 8", 100, 0., 15*keV);
  // analysisManager->CreateH1("det9" ,"Edep in detector 9", 100, 0., 15*keV);

  analysisManager->CreateH1("l1b1" ,"Detector L1B1, efficiency: 100%", 100, 0., 15);//in KeV unit (see SensitiveDetector.cc /CLHEP::keV
  analysisManager->CreateH1("l1b2" ,"Detector L1B2, efficiency: 100%", 100, 0., 15);//1
  analysisManager->CreateH1("l1b3" ,"Detector L1B3, efficiency: 100%", 100, 0., 15);//2
  analysisManager->CreateH1("l1b4" ,"Detector L1B4, efficiency: 100%", 100, 0., 15);//3
  analysisManager->CreateH1("l1b5" ,"Detector L1B5, efficiency: 100%", 100, 0., 15);//4

  analysisManager->CreateH1("l2b1" ,"Detector L2B1, efficiency: 100%", 100, 0., 15);//5
  analysisManager->CreateH1("l2b2" ,"Detector L2B2, efficiency: 100%", 100, 0., 15);//6
  analysisManager->CreateH1("l2b3" ,"Detector L2B3, efficiency: 100%", 100, 0., 15);//7
  analysisManager->CreateH1("l2b4" ,"Detector L2B4, efficiency: 100%", 100, 0., 15);//8
  analysisManager->CreateH1("l2b5" ,"Detector L2B5, efficiency: 100%", 100, 0., 15);//10

  analysisManager->CreateH1("l3b1" ,"Detector L3B1, efficiency: 100%", 100, 0., 15);//11
  analysisManager->CreateH1("l3b2" ,"Detector L3B2, efficiency: 100%", 100, 0., 15);//12
  analysisManager->CreateH1("l3b3" ,"Detector L3B3, efficiency: 100%", 100, 0., 15);//13
  analysisManager->CreateH1("l3b4" ,"Detector L3B4, efficiency: 100%", 100, 0., 15);//14
  analysisManager->CreateH1("l3b5" ,"Detector L3B5, efficiency: 100%", 100, 0., 15);//15


  analysisManager->CreateH1("l1b1_p" ,"Detector L1B1, efficiency: 100%. Proton only", 100, 0., 15);//in KeV unit (see SensitiveDetector.cc /CLHEP::keV
  analysisManager->CreateH1("l1b2_p" ,"Detector L1B2, efficiency: 100%. Proton only", 100, 0., 15);//1 + 16
  analysisManager->CreateH1("l1b3_p" ,"Detector L1B3, efficiency: 100%. Proton only", 100, 0., 15);//2 + 16
  analysisManager->CreateH1("l1b4_p" ,"Detector L1B4, efficiency: 100%. Proton only", 100, 0., 15);//3 + 16
  analysisManager->CreateH1("l1b5_p" ,"Detector L1B5, efficiency: 100%. Proton only", 100, 0., 15);//4 + 16

  analysisManager->CreateH1("l2b1_p" ,"Detector L2B1, efficiency: 100%. Proton only", 100, 0., 15);//5 + 16
  analysisManager->CreateH1("l2b2_p" ,"Detector L2B2, efficiency: 100%. Proton only", 100, 0., 15);//6 + 16
  analysisManager->CreateH1("l2b3_p" ,"Detector L2B3, efficiency: 100%. Proton only", 100, 0., 15);//7 + 16
  analysisManager->CreateH1("l2b4_p" ,"Detector L2B4, efficiency: 100%. Proton only", 100, 0., 15);//8 + 16
  analysisManager->CreateH1("l2b5_p" ,"Detector L2B5, efficiency: 100%. Proton only", 100, 0., 15);//10 + 16

  analysisManager->CreateH1("l3b1_p" ,"Detector L3B1, efficiency: 100%. Proton only", 100, 0., 15);//11 + 16
  analysisManager->CreateH1("l3b2_p" ,"Detector L3B2, efficiency: 100%. Proton only", 100, 0., 15);//12 + 16
  analysisManager->CreateH1("l3b3_p" ,"Detector L3B3, efficiency: 100%. Proton only", 100, 0., 15);//13 + 16
  analysisManager->CreateH1("l3b4_p" ,"Detector L3B4, efficiency: 100%. Proton only", 100, 0., 15);//14 + 16
  analysisManager->CreateH1("l3b5_p" ,"Detector L3B5, efficiency: 100%. Proton only", 100, 0., 15);//15 + 16


  analysisManager->CreateH1("l1b1_r" ,"Detector L1B1, efficiency: 100%. Gamma only", 100, 0., 15);//in KeV unit (see SensitiveDetector.cc /CLHEP::keV
  analysisManager->CreateH1("l1b2_r" ,"Detector L1B2, efficiency: 100%. Gamma only", 100, 0., 15);//1 + 32
  analysisManager->CreateH1("l1b3_r" ,"Detector L1B3, efficiency: 100%. Gamma only", 100, 0., 15);//2 + 32
  analysisManager->CreateH1("l1b4_r" ,"Detector L1B4, efficiency: 100%. Gamma only", 100, 0., 15);//3 + 32
  analysisManager->CreateH1("l1b5_r" ,"Detector L1B5, efficiency: 100%. Gamma only", 100, 0., 15);//4 + 32

  analysisManager->CreateH1("l2b1_r" ,"Detector L2B1, efficiency: 100%. Gamma only", 100, 0., 15);//5 + 32
  analysisManager->CreateH1("l2b2_r" ,"Detector L2B2, efficiency: 100%. Gamma only", 100, 0., 15);//6 + 32
  analysisManager->CreateH1("l2b3_r" ,"Detector L2B3, efficiency: 100%. Gamma only", 100, 0., 15);//7 + 32
  analysisManager->CreateH1("l2b4_r" ,"Detector L2B4, efficiency: 100%. Gamma only", 100, 0., 15);//8 + 32
  analysisManager->CreateH1("l2b5_r" ,"Detector L2B5, efficiency: 100%. Gamma only", 100, 0., 15);//10 + 32

  analysisManager->CreateH1("l3b1_r" ,"Detector L3B1, efficiency: 100%. Gamma only", 100, 0., 15);//11 + 32
  analysisManager->CreateH1("l3b2_r" ,"Detector L3B2, efficiency: 100%. Gamma only", 100, 0., 15);//12 + 32
  analysisManager->CreateH1("l3b3_r" ,"Detector L3B3, efficiency: 100%. Gamma only", 100, 0., 15);//13 + 32
  analysisManager->CreateH1("l3b4_r" ,"Detector L3B4, efficiency: 100%. Gamma only", 100, 0., 15);//14 + 32
  analysisManager->CreateH1("l3b5_r" ,"Detector L3B5, efficiency: 100%. Gamma only", 100, 0., 15);//15 + 32


  analysisManager->CreateH1("l1b1_o" ,"Detector L1B1, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//in KeV unit (see SensitiveDetector.cc /CLHEP::keV
  analysisManager->CreateH1("l1b2_o" ,"Detector L1B2, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//1 + 48
  analysisManager->CreateH1("l1b3_o" ,"Detector L1B3, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//2 + 48
  analysisManager->CreateH1("l1b4_o" ,"Detector L1B4, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//3 + 48
  analysisManager->CreateH1("l1b5_o" ,"Detector L1B5, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//4 + 48

  analysisManager->CreateH1("l2b1_o" ,"Detector L2B1, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//5 + 48
  analysisManager->CreateH1("l2b2_o" ,"Detector L2B2, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//6 + 48
  analysisManager->CreateH1("l2b3_o" ,"Detector L2B3, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//7 + 48
  analysisManager->CreateH1("l2b4_o" ,"Detector L2B4, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//8 + 48
  analysisManager->CreateH1("l2b5_o" ,"Detector L2B5, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//10 + 48

  analysisManager->CreateH1("l3b1_o" ,"Detector L3B1, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//11 + 48
  analysisManager->CreateH1("l3b2_o" ,"Detector L3B2, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//12 + 48
  analysisManager->CreateH1("l3b3_o" ,"Detector L3B3, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//13 + 48
  analysisManager->CreateH1("l3b4_o" ,"Detector L3B4, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//14 + 48
  analysisManager->CreateH1("l3b5_o" ,"Detector L3B5, efficiency: 100%. No neutron, proton, nor gamma", 100, 0., 15);//15 + 48

  // analysisManager->CreateH1("det1" ,"proton in collimator 1", 100, 0., 15);
  // analysisManager->CreateH1("det2" ,"gamma in collimator 2", 100, 0., 15);
  // analysisManager->CreateH1("det3" ,"e- in collimator 3", 1000, 0., 5500);
  // analysisManager->CreateH1("det4" ,"e+ in collimator 4", 1000, 0., 1500);
  // analysisManager->CreateH1("det5" ,"deuteron in collimator 5", 100, 0., 15);
  // analysisManager->CreateH1("det6" ,"C12 in collimator 6", 100, 0., 15);
  // analysisManager->CreateH1("det7" ,"C13 in collimator 7", 100, 0., 15);
  // analysisManager->CreateH1("det8" ,"C14 in collimator 8", 100, 0., 15);
  // analysisManager->CreateH1("det9" ,"others in collimator 9", 100, 0., 15);
  // analysisManager->CreateH1("det10" ,"all edep", 1000, 0., 5500);

  // Creating ntuple
  analysisManager->CreateNtuple("det", "Detector particle bank");
  analysisManager->CreateNtupleSColumn("pid_str"); //0
  analysisManager->CreateNtupleIColumn("pid");//1
  analysisManager->CreateNtupleDColumn("kine");//2
  analysisManager->CreateNtupleDColumn("edep");//3
  analysisManager->CreateNtupleDColumn("x");//4
  analysisManager->CreateNtupleDColumn("y");//5
  analysisManager->CreateNtupleDColumn("z");//6

  analysisManager->CreateNtuple("col", "Collimator particle bank");
  analysisManager->CreateNtupleSColumn("pid_str"); //0+7
  analysisManager->CreateNtupleIColumn("pid");//1+7
  analysisManager->CreateNtupleDColumn("kine");//2+7
  analysisManager->CreateNtupleDColumn("edep");//3+7
  analysisManager->CreateNtupleDColumn("x");//4+7
  analysisManager->CreateNtupleDColumn("y");//5+7
  analysisManager->CreateNtupleDColumn("z");//6+7

  // analysisManager->CreateNtupleDColumn("kine_e");//4. temporary for electron
  // analysisManager->CreateNtupleIColumn("evtid");//5. temporary
  // analysisManager->CreateNtupleIColumn("trid");//6. temporary
  // analysisManager->CreateNtupleIColumn("paid");//7. temporary
  // analysisManager->CreateNtupleDColumn("kine_r");//8. temporary

  analysisManager->FinishNtuple();
  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{

  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "col_det.csv";
  // Other supported output types:
  G4String fileName2 = "col_det.root";
  // G4String fileName = "col_det.hdf5";
  // G4String fileName = "col_det.xml";
  // analysisManager->OpenFile(fileName);
  analysisManager->OpenFile(fileName2);
  G4cout << "Using " << analysisManager->GetType() << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
  // print histogram statistics
  //
  auto analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->GetH1(1) ) {
    G4cout << G4endl << " ----> print histograms statistic ";
    if(isMaster) {
      G4cout << "for the entire run " << G4endl << G4endl;
    }
    else {
      G4cout << "for the local thread " << G4endl << G4endl;
    }

    // G4cout << " Coll Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(0)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(0)->rms(),  "keV") << G4endl;

    // G4cout << " Detector1 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(1)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(1)->rms(),  "keV") << G4endl;

    // G4cout << " Detector2 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(2)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(2)->rms(),  "keV") << G4endl;

    // G4cout << " Detector3 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(3)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(3)->rms(),  "keV") << G4endl;

    // G4cout << " Detector4 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(4)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(4)->rms(),  "keV") << G4endl;

    // G4cout << " Detector5 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(5)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(5)->rms(),  "keV") << G4endl;

    // G4cout << " Detector6 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(6)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(6)->rms(),  "keV") << G4endl;

    // G4cout << " Detector7 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(7)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(7)->rms(),  "keV") << G4endl;

    // G4cout << " Detector8 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(8)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(8)->rms(),  "keV") << G4endl;

    // G4cout << " Detector9 Edep : mean = "
    //    << G4BestUnit(analysisManager->GetH1(9)->mean(), "keV")
    //    << " rms = "
    //    << G4BestUnit(analysisManager->GetH1(9)->rms(),  "keV") << G4endl;

    // save histograms & ntuple
    //
    analysisManager->Write();
    analysisManager->CloseFile();
    
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void RunAction::AddEdep(G4double edep)
// {
//   fEdep  += edep;
//   fEdep2 += edep*edep;
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

