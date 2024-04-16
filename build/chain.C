void chain(){

  // TChain *col = new TChain("col");
  // col->Add("AmBe_1e7_posxShift_iso_01.root");  
  // col->Add("AmBe_1e7_posxShift_iso_02.root");  
  // col->Add("AmBe_1e7_posxShift_iso_03.root");  
  // col->Add("AmBe_1e7_posxShift_iso_04.root");  
  // col->Add("AmBe_1e7_posxShift_iso_05.root");  
  // col->Add("AmBe_1e7_posxShift_iso_06.root");  
  // col->Add("AmBe_1e7_posxShift_iso_07.root");  
  // col->Add("AmBe_1e7_posxShift_iso_08.root");  
  // col->Add("AmBe_1e7_posxShift_iso_09.root");  
  // col->Add("AmBe_1e7_posxShift_iso_10.root");

  TChain *det = new TChain("det");
  // det->Add("AmBe_1e7_posxShift_iso_01.root");  
  // det->Add("AmBe_1e7_posxShift_iso_02.root");  
  // det->Add("AmBe_1e7_posxShift_iso_03.root");  
  // det->Add("AmBe_1e7_posxShift_iso_04.root");  
  // det->Add("AmBe_1e7_posxShift_iso_05.root");  
  // det->Add("AmBe_1e7_posxShift_iso_06.root");  
  // det->Add("AmBe_1e7_posxShift_iso_07.root");  
  // det->Add("AmBe_1e7_posxShift_iso_08.root");  
  // det->Add("AmBe_1e7_posxShift_iso_09.root");  
  // det->Add("AmBe_1e7_posxShift_iso_10.root");

  for(int i = 1 ; i < 26 ; i++){
    if (i != 4){
      det->Add(Form("output/cathodeclub_%02d.root", i));
    }
  }
  
  // long nevt_col = col->GetEntries(); //std::cout<<nevt_col<<std::endl;
  // col->SetBranchStatus("*",1);
  long nevt_det = det->GetEntries(); //std::cout<<nevt_det<<std::endl;
  det->SetBranchStatus("*",1);
  // TBranch *kine = col->GetBranch("kine"); col->SetBranchStatus("kine", 1);

  // double kine; col->SetBranchAddress("kine", &kine);
  // double x; col->SetBranchAddress("x", &x);
  // double y; col->SetBranchAddress("y", &y);
  // double z; col->SetBranchAddress("z", &z);
  // double gtime; col->SetBranchAddress("gtime", &gtime);
  
  // double kine; col->SetBranchAddress("kine", &kine);
  // double x; col->SetBranchAddress("x", &x);
  // double y; col->SetBranchAddress("y", &y);
  // double z; col->SetBranchAddress("z", &z);
  // double gtime; col->SetBranchAddress("gtime", &gtime);
  
  // TH1D *h1_kine_ni_tot = new TH1D("h1_kine_ni_tot", "Neutron initiaal kinetic energy entering the colector, all colectors", 1100, 0, 11);

  // for(int i_evt = 0 ; i_evt < nevt_col ; i_evt++){
  //   col->GetEntry(i_evt);
  //   h1_kine_ni_tot->Fill(kine);
  // }

  // h1_kine_ni_tot->Draw();
}
