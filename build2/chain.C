void chain(){

  TChain *det = new TChain("det");
  det->Add("AmBe_1e7_negxShift_iso_01.root");  
  det->Add("AmBe_1e7_negxShift_iso_02.root");  
  det->Add("AmBe_1e7_negxShift_iso_03.root");  
  det->Add("AmBe_1e7_negxShift_iso_04.root");  
  det->Add("AmBe_1e7_negxShift_iso_05.root");  
  det->Add("AmBe_1e7_negxShift_iso_06.root");  
  det->Add("AmBe_1e7_negxShift_iso_07.root");  
  det->Add("AmBe_1e7_negxShift_iso_08.root");  
  det->Add("AmBe_1e7_negxShift_iso_09.root");  
  det->Add("AmBe_1e7_negxShift_iso_10.root");

  long nevt = det->GetEntries(); //std::cout<<nevt<<std::endl;
  det->SetBranchStatus("*",0);
  // TBranch *kine = det->GetBranch("kine"); det->SetBranchStatus("kine", 1);

  double kine; det->SetBranchAddress("kine", &kine);
  
  TH1D *h1_kine_ni_tot = new TH1D("h1_kine_ni_tot", "Neutron initiaal kinetic energy entering the detector, all detectors", 1100, 0, 11);

  for(int i_evt = 0 ; i_evt < nevt ; i_evt++){
    det->GetEntry(i_evt);
    h1_kine_ni_tot->Fill(kine);
  }

  h1_kine_ni_tot->Draw();
}
