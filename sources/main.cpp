//
// Created by Filip on 5/14/2025.
//
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <filesystem>

#include "../headers/parameters.h"
#include "../headers/Graph.h"
#include "../headers/FormulaParsing.h"
#include "../headers/Ant.h"
#include "../headers/outputControll.h"
#include "../headers/paramSetup.h"

using namespace std;

void displayAnt(int i, Ant* antPopulation []) {
    dout << "i:" << i << "    " << "id: " << antPopulation[i]->id << "    " << "fitness: " << antPopulation[i]->fitness;
    if (displayFormulaForEveryAnt) dout << "        " << antPopulation[i]->getFormula();
    dout << endl;
}

int main() {
    model_setup("./modelParameters.conf");
    print_params();

    dout << "\nMravljiAlgoritam" << endl;
    if (steadyConvergence) initialConcentration = numberOfChosenAnts * 2;
    numberOfChosenAnts = min(numberOfChosenAnts, numberOfAnts);
    Graph g = Graph();

    if (initialGraphPrint) g.printGraph();

    string inlineTruthTable;
    // Unos tablice istinitosti i spremanje u memoriju.
    vector<bool> TABLE;
    for (int i = 0; i < pow(2, numberOfVariables); i++) {
        TABLE.push_back(0);
    }
    bool choice;
    dout << "\n\nUpisi 0 za koristenje tablice istinitosti, 1 za unos formule:\n";
    dout << "> ";
    cin >> choice;
    if (choice == 0) {
        //cin >> truthTable; OVDJE SE MOŽE OMOGUĆITI UNOS TABLICE ISTINITOSTI
        //                    inače se koristi default postavljen u parameters.h
        for (int i = 0; i < pow(2, numberOfVariables); i++) {
            if (truthTable[i] == '0') TABLE[i] = 0;
            else TABLE[i] = 1;
        }
    }
    else if (choice == 1){
        // Izrada tablice istinitosti iz formule i spremanje u memoriju.
        string formula;
        getline(cin, formula);
        getline(cin, formula);
        vector<string> konjunkti;
        split(konjunkti, formula);

        // POZIV NOVE FUNKCIJE
        for (int i = 0; i < konjunkti.size(); i++) {
            vector<int> switchList;
            findIndexesToActivate(konjunkti[i], switchList, numberOfVariables);

            for (int j = 0; j < switchList.size(); j++) {
                dout << switchList[j] << " ";
                TABLE[switchList[j]] = 1;
            }
            dout << endl;
        }

        inlineTruthTable = "";
        dout << "TRUTH TABLE:\n";
        for (int i = 0; i < TABLE.size(); i++) {
            dout << i << ": "<< TABLE[i] << endl;
            inlineTruthTable += TABLE[i] + 48;
        }
        dout << "inlineTruthTable: " << inlineTruthTable << endl;
    }

    for (int i = 0; i < TABLE.size(); i++) {
        inlineTruthTable += TABLE[i] + 48;
    }

    // Deaktiviranje nepotrebnih konjunkta =>
    g.deactivateUnnecessary(TABLE);

    if (excludedGraphPrint) {
        dout << "\n\nGraf nakon iskljucivanja nepotrebnih konjunkata\n";
        g.printGraph();
        g.drawGraph();
    }

    //                                  SIMULATION START
    //                                  SIMULATION START
    //                                  SIMULATION START

    auto start = std::chrono::high_resolution_clock::now();

    Ant* antPopulation[numberOfAnts];
    for (int i = 0; i < numberOfAnts; i++) {
        antPopulation[i] = new Ant(i);
    }

    string bestPath;
    for (int i = 0; i < numberOfChosenAnts; i++) {
        antPopulation[i]->loadPathFromTable(TABLE);
    }

    // Iterate.
    for (int iter = 1; iter <= numberOfIterations; iter++) {

        if (iterationLabel) {
            dout << "\n\n\n            =====================================================================================\n";
            dout << "            |                          ITERATION NUMBER:  " << std::setw(4) << iter << "                                   |" << std::endl;
            dout << "            =====================================================================================\n";
        }

        if (displayPopulationAfterWalking) dout << "\nPopulation after walking:\n";
        for (int i = 0; i < numberOfAnts; i++) {
            if (i>numberOfChosenAnts - 1) antPopulation[i]->walk(&g);
            antPopulation[i]->evalFitness(TABLE);
            if (displayPopulationAfterWalking) displayAnt(i, antPopulation);
        }

        sort(antPopulation, antPopulation + numberOfAnts, compareAntsByFitness);

        if (displayPopulationAfterSorting) dout << "\nPopulation after sorting:\n";
        for (int i = 0; i < numberOfAnts; i++) {
            if (displayPopulationAfterSorting) displayAnt(i, antPopulation);
        }

        g.evaporatePheromones();

        if (displayBestAnts) dout << "\nBest from population:\n";
        for (int i = 0;i < numberOfChosenAnts; i++) {
            if (displayBestAnts) {
                dout << "\nid: " << antPopulation[i]->id << "    " << "fitness: " << antPopulation[i]->fitness << endl;
                if (displayBestAntsPath) antPopulation[i]->displayPath();
                if (displayBestAntsTruthTable) antPopulation[i]->displayTruthTable();
                dout << "   Ant's formula: " << antPopulation[i]->getFormula() << endl;
                //dout << "Inline path:" << antPopulation[0]->inlinePath() << endl;
            }


            antPopulation[i]->leavePheromones(&g);
        }



        if (printGraphAfterIteration) g.printGraph();
        if (drawGraphAfterIteration) g.drawGraph();

        // Reset graph after <resetAfter> itterations.
        if (iter % resetAfter == 0) {
            bestPath = antPopulation[0]->inlinePath();
            g.resetGraph();
            g.deactivateUnnecessary(TABLE);
            dout << "\n\n              *************** RESET ***************\n\n";

            for (int i = 0; i < numberOfChosenAnts; i++) {
                antPopulation[i]->loadPath(bestPath);
            }
        }

    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    dout << "\n\nSimulation time: " << elapsed.count() << " ms\n";

    if (displayBestSolution) {
        dout << "\nBest fitness: " << antPopulation[0]->fitness << endl;
        dout << "\nBest solution: " << antPopulation[0]->getFormula() << endl;
        dout << "Inline table:" << inlineTruthTable << endl;
        dout << "Inline path:" << antPopulation[0]->inlinePath() << endl;
    }

    ofstream outFile;
    string resultingPath = "./L-solutionLogs/";
    resultingPath += "solution-";
    resultingPath += dout.name;
    outFile.open(resultingPath);

    outFile << "number of iterations: " << numberOfIterations << endl;
    outFile << "reset after: " << resetAfter << endl;
    outFile << "number of variables: " << numberOfVariables << endl;
    outFile << "number of antennas: " << numberOfAnts << endl;
    outFile << "number of chosen antennas: " << numberOfChosenAnts << endl;
    outFile << "initial concentration: " << initialConcentration << endl;
    outFile << "diminish rate: " << diminishRate << endl;
    outFile << "truth table: ";
    for (int i = 0; i < pow(2,numberOfVariables); i++) {
        outFile << truthTable[i];
    }
    outFile << endl;
    outFile << "steadyConvergence: " << steadyConvergence << endl;
    outFile << "limit pheromones: " << limitPheromones << endl;
    outFile << "max pheromones: " << maxPheromones << endl;
    outFile << "exclude probability: " << excludeProbability << endl;
    outFile << "printToConsole: " << printToConsole << endl;

    outFile << "\n\nSimulation time: " << elapsed.count() << " ms\n";
    outFile << "\nBest fitness: " << antPopulation[0]->fitness << endl;
    outFile << "\nBest solution: " << antPopulation[0]->getFormula() << endl;
    outFile << "Inline table:" << inlineTruthTable << endl;
    outFile << "Inline path:" << antPopulation[0]->inlinePath() << endl;
    return 0;
}
