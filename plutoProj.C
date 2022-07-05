R__LOAD_LIBRARY ($PLUTOLIBDIR/libPluto.so)
#include "generateFireball.C"
#include "readFireball.C"

void plutoProj () {

	// This lists all the setup parameters

	Int_t numberOfEvents;
	Double_t Tbeam, T1, T2, w, radExp, a2, a4, v1, v2, pmin, pmax, thetamin, thetamax;
	TString partname, filename;

	// Settings for simulation

	numberOfEvents = 1000000;

	partname = "pi+";
	filename = "thermal_pip_Eb1.23AGeV_T130_90MeV";

	Tbeam = 1.230; // [GeV/A]
	T1 = 0.13; // [GeV]
	T2 = 0.09; // [GeV]
	w = 1.230; // [GeV/A]
	radExp = 0;
	a2 = 0;
	a4 = 0;
	v1 = 0;
	v2 = 0;

	// Settings for analysis

	pmin = 0.005; 		// [GeV]
	pmax = 1.5; 		// [GeV]
	thetamin = 18; 		// deg
	thetamax = 88; 		// deg
	Double_t ycm = 0.74;

	generateFireball (numberOfEvents, partname, filename, 
		Tbeam, T1, T2, w, radExp, a2, a4, v1, v2);

	readFireball(filename, pmin, pmax, thetamin, thetamax, ycm);
}
