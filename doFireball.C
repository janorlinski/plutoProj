R__LOAD_LIBRARY ($PLUTOLIBDIR/libPluto.so)

int doFireball (Int_t numberOfEvents, TString partname, TString filename, Double_t Tbeam, Double_t T1, Double_t T2, Double_t w, Double_t radExp, Double_t a2, Double_t a4, Double_t v1, Double_t v2, Double_t pmin, Double_t pmax, Double_t thetamin, Double_t thetamax, Double_t ycm) { 
  
	// Changing the numerical variables into TString

	TString ycm_s 		= to_string(ycm);
	TString pmin_s 		= to_string(pmin);
	TString pmax_s 		= to_string(pmax);
	TString thetamin_s 	= to_string(thetamin);
	TString thetamax_s 	= to_string(thetamax);


	// Randomization of seed

	PUtils* putils = new PUtils ();
	putils->SetSeed (0);
	gRandom->SetSeed();

	// Main setup

	PFireball* source = new PFireball 
		(partname, Tbeam, T1, T2, w, radExp, a2, a4, v1, v2);
	source ->Print ();
	PParticle* part = new PParticle (partname);
	PParticle* parttable_fireball[] = {source, part};
	PChannel*  channel_fireball   = new PChannel (parttable_fireball, 1, 1);
  	PChannel*  table_of_channels[]   = { channel_fireball };
	PReaction* reaction_thermal = new PReaction 
		(table_of_channels, filename, 1, 1, 0, 0, 0);

	reaction_thermal->Print ();

	// TNtuple as a quick Event Database
	TNtuple *my_ntuple = new TNtuple ("ntu",  "Monitor ntuple", "raplab:pt:theta:mom" );

	gDirectory->pwd();

	reaction_thermal->Do ("rap = [" + partname + "]->Rapidity() - " + ycm_s);
	reaction_thermal->Do ("pt = [" + partname + "]->Pt()");
	reaction_thermal->Do ("theta = [" + partname + "]->Theta()*TMath::RadToDeg()");
	reaction_thermal->Do ("mom = [" + partname + "]->P()");

	// Adding TNtuple to the list of filled objects during loop

	reaction_thermal->Output (my_ntuple); 

	// Additional filtering of the basic TTree

	reaction_thermal->Do ("#thetaAccepted = 1; if (theta < " + thetamin_s + " || theta > " + thetamax_s + ") ; #thetaAccepted  = 0" );
	reaction_thermal->Do ("#momAccepted = 1; if (mom < " + pmin_s + " || mom > " + pmax_s + ") ; #momAccepted  = 0" );

	// Quick histogram - lets do pty

	TH2F *pty = new TH2F ("pty", "pt:y distribution; y_{CM}; p_{t} [GeV]",  80, -4, 4, 200, 0, 2);
	reaction_thermal->Do ( pty, "if #thetaAccepted && #momAccepted; _x = rap ; _y = pt" ); 

	// Loop
	reaction_thermal->Loop (numberOfEvents, 1);

	// Plot or edit your histograms
	gStyle->SetOptStat(0);
	pty->Draw("colz");
	
	return 0;

}

