# About plutoProj
Generating pi mesons from a fireball using the PLUTO code. Developed for Computer Tools for Nuclear Physics @ FUW in 2022. 

# How to use me?

The user must first assure the correct inclusion of PLUTO libraries. Then it is enough to invoke plutoProj(), for example using 'root -l plutoProj.C'.

All important settings regarding the simulation and data analysis can be easily accessed and modified in the plutoProj.C macro. It includes the number of events to be generated, type of particle, fireball parameters and acceptance cuts for the analysis. The rapidity of center of mass for a system needs to be calculated individually and treated as a setting parameter.

# Structure of the program

'plutoProj.C' is the main macro, which contains all necessary settings and coordinates the program. It includes two dependent macros: 'generateFireball.C' and 'readFireball.C'.

'generateFireball.C' generates the fireball and saves it to .root file. 'readFireball.C' then loads this .root file and performs data analysis using TClonesArray. The goal of the data analysis is to present a pt:y distribution of generated particles.

# Task list

#### Done 

 - first steps in PLUTO - generating Fireball pi+ @ 1.23A GeV
 - allowing for customisation of the fireball
 - data analysis -> pt:y plot using TClonesArray and cuts in the particles loop
 - main macro which coordinates the program in a clean and user-friendly way

#### In progress

 - use the different methods for data analysis and data cuts

#### To do

 - when generating pi mesons include also their production from delta resonanses
 - test the program thoroughly
 - integrate the program with histogui to allow for GUI based (a) setting of the fireball and (b) visualising the distributions
