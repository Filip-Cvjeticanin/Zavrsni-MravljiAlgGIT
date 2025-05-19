//
// Created by Filip on 5/14/2025.
//
#ifndef PARAMETERS_H
#define PARAMETERS_H

// Model parameters:
inline int numberOfIterations = 5000; //Linear factor
inline int resetAfter = 30;
inline int numberOfVariables = 6; // max 26
inline int numberOfAnts = 1500;
inline int numberOfChosenAnts = 2;
inline double initialConcentration = 2.5;
inline double diminishRate = 0.2;
inline std::string truthTable = "1000000100101110100110011000111010101010010101001100100011111111"; // Must be 2 ** numberOfVariables
inline constexpr bool steadyConvergence = false; // Uses a modification to the initialPheromones to adjust to the
                                                 // number of chosenAnts in an attempt to slow down convergence
                                                 // in wrong directions. Requires an increase in numberOfIterations.
                                                 // EXPERIMENTAL!!!
inline constexpr bool limitPheromones = false;
inline double maxPheromones = 20;
inline double excludeProbability = -1;


// Setup display parameters:
inline constexpr bool initialGraphPrint = false;
inline constexpr bool excludedGraphPrint = false;

// Ant algorithm display parameters:
inline constexpr bool iterationLabel = true;
inline constexpr bool displayPopulationAfterWalking = false;
inline constexpr bool displayPopulationAfterSorting = false;
inline constexpr bool displayBestAnts = true;
inline constexpr bool displayBestAntsPath = false;
inline constexpr bool displayBestAntsTruthTable = false;
inline constexpr bool displayFormulaForEveryAnt = false;
inline constexpr bool printGraphAfterIteration = false;
inline constexpr bool drawGraphAfterIteration = false;
inline constexpr bool displayBestSolution = true;
#endif
