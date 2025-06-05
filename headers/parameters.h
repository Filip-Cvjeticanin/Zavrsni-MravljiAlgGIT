//
// Created by Filip on 5/14/2025.
//
#ifndef PARAMETERS_H
#define PARAMETERS_H

// Model parameters:
inline int numberOfIterations = 100; //Linear factor
inline int resetAfter = 30;
inline int numberOfVariables = 3; // max 26
inline int numberOfAnts = 50;
inline int numberOfChosenAnts = 2;
inline double initialConcentration = 1.5;
inline double diminishRate = 0.2;
inline std::string truthTable = "11110000"; // Must be 2 ** numberOfVariables
inline bool steadyConvergence = false; // Uses a modification to the initialPheromones to adjust to the
                                                 // number of chosenAnts in an attempt to slow down convergence
                                                 // in wrong directions. Requires an increase in numberOfIterations.
                                                 // EXPERIMENTAL!!!
inline bool limitPheromones = false;
inline double maxPheromones = 20;
inline double excludeProbability = -1;
inline bool printToConsole = false;


// Setup display parameters:
inline bool initialGraphPrint = false;
inline bool excludedGraphPrint = false;

// Ant algorithm display parameters:
inline bool iterationLabel = true;
inline bool displayPopulationAfterWalking = false;
inline bool displayPopulationAfterSorting = false;
inline bool displayBestAnts = true;
inline bool displayBestAntsPath = false;
inline bool displayBestAntsTruthTable = false;
inline bool displayFormulaForEveryAnt = false;
inline bool printGraphAfterIteration = false;
inline bool drawGraphAfterIteration = false;
inline bool displayBestSolution = true;
#endif
