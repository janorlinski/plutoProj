R__LOAD_LIBRARY ($PLUTOLIBDIR/libPluto.so)

int readFireball (TString filename, Double_t pmin, Double_t pmax, Double_t thetamin, Double_t thetamax, Double_t ycm) {

	//Int_t numberOfEvents;
	//Double_t Tbeam, T1, T2, w, radExp, a2, a4, v1, v2, pmin, pmax, thetamin, thetamax;
	//TString partname, filename;

	// This macro is supposed to read data from the PLUTO file

	// Definition of a TH2D for the pt:y distribution

	TH2F *pty = new TH2F ("pty", "pt:y distribution; y_{CM}; p_{t} [GeV]",  80, -4, 4, 200, 0, 2);

	// First let's define the TClonesArray necessary for extraction of 
	// particles from events.

	TClonesArray* partArray = new TClonesArray ("PParticle", 10);
	PParticle* Part[10];

	// Then, load the TTree

	TFile f (filename + ".root");
	TTree *t = (TTree*) f.Get ("data");
	t->SetBranchAddress ("Particles" , &partArray );

	// Loop over events

	Int_t nR = t->GetEntries() ;
	cout << "\n * Analysing " << nR << " reactions.\n\n";

	for (int iR=0; iR<nR; iR++) {
		t->GetEntry (iR);
		if (iR%1000==0) cout << "processing event no " << iR << " with " << partArray->GetEntries() << " particles \n";

	// And over particles

		for (Int_t iP = 0; iP < partArray->GetEntries() ; iP++ ) {
      			Part[iP] = (PParticle*) partArray->At (iP);

	// All operations on individual particles can be done here

			Double_t rap = Part[iP]->Rapidity(); 	// rapidity in LAB
			Double_t pt = Part[iP]->Pt();		// pt in LAB, GeV

	// Applying LAB cuts

			if (Part[iP]->P() < pmin || Part[iP]->P() > pmax) 
				continue;
			if (Part[iP]->Theta()*TMath::RadToDeg() < thetamin 
			|| Part[iP]->Theta()*TMath::RadToDeg() > thetamax) 					continue;

	// Filling histos

			pty->Fill(rap - ycm, Part[iP]->Pt());

		}
	}

	// Plot or edit your histograms
	gStyle->SetOptStat(0);
	pty->Draw("colz");
	
return 0;

}
