R__LOAD_LIBRARY ($PLUTOLIBDIR/libPluto.so)

int generateFireball (Int_t numberOfEvents, TString partname, TString filename, Double_t Tbeam, Double_t T1, Double_t T2, Double_t w, Double_t radExp, Double_t a2, Double_t a4, Double_t v1, Double_t v2) {
	
	//Int_t numberOfEvents;
	//Double_t Tbeam, T1, T2, w, radExp, a2, a4, v1, v2, pmin, pmax, thetamin, thetamax;
	//TString partname, filename;

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

	// Reacting

	reaction_thermal->Print ();
	reaction_thermal->loop (numberOfEvents, 1);

	return 0;
}
