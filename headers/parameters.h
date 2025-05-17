//
// Created by Filip on 5/14/2025.
//
#ifndef PARAMETERS_H
#define PARAMETERS_H

// Model parameters:
inline int numberOfIterations = 10;
inline int numberOfVariables = 3; // max 26
inline int numberOfAnts = 50;
inline int numberOfChosenAnts = 5;
inline double initialConcentration = 1;
inline double diminishRate = 0.2;
inline std::string truthTable = "10001011"; // mora biti dužine 2 ** numberOfVariables

// Ant algorithm display parameters:
inline constexpr bool displayPopulationAfterWalking = false;
inline constexpr bool displayPopulationAfterSorting = false;
inline constexpr bool displayBestAnts = false;
inline constexpr bool displayFormulaForEveryAnt = false;
inline constexpr bool printGraphAfterIteration = false;
inline constexpr bool drawGraphAfterIteration = false;
inline constexpr bool displayBestSolution = true;
#endif
