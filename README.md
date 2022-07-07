# About plutoProj
Generating pi mesons from a fireball using the PLUTO code. Developed for Computer Tools for Nuclear Physics @ FUW in 2022. 

# How to use me?

First download and unpack this repository. 

Assure the correct inclusion of PLUTO and ROOT libraries. Then it is enough to invoke plutoProj.C, for example using `root -l plutoProj.C`. Please do not try to compile the macro and use the intepreted mode of ROOT instead.

All important settings regarding the simulation and data analysis can be easily accessed and modified in the plutoProj.C macro. It includes the number of events to be generated, type of particle, fireball parameters and acceptance cuts for the analysis. The plutoProj.C macro also allows the selection of working mode: via `TNTuple` or via `TClonesArray` using the logical conditions in lines 41 and 47. The rapidity of center of mass for a system needs to be calculated individually and treated as a setting parameter.

# Structure of the program

`plutoProj.C` is the main macro, which contains all necessary settings and coordinates the program. It includes three sub-macros: `generateFireball()`, `doFireball()` and `readFireball()`.

`generateFireball()` generates the fireball and saves it to a .root file. `readFireball()` then loads this file and performs data analysis using the TClonesArray class. The goal of the data analysis is to present a pt:y distribution of generated particles. `doFireball()` performs both these tasks in one function using the TNTuple class. However, bear in mind that the first method appears to be quicker. 
