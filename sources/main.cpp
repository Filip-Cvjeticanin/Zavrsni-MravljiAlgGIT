//
// Created by Filip on 5/14/2025.
//
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

#include "../headers/parameters.h"
#include "../headers/Graph.h"
#include "../headers/FormulaParsing.h"
#include "../headers/Ant.h"

using namespace std;

void displayAnt(int i, Ant* antPopulation []) {
    cout << "i:" << i << "    " << "id: " << antPopulation[i]->id << "    " << "fitness: " << antPopulation[i]->fitness;
    if (displayFormulaForEveryAnt) cout << "        " << antPopulation[i]->getFormula();
    cout << endl;
}

int main() {
    cout << "MravljiAlgoritam" << endl;
    if (steadyConvergence) initialConcentration = numberOfChosenAnts * 2;
    numberOfChosenAnts = min(numberOfChosenAnts, numberOfAnts);
    Graph g = Graph();
    cout << g.numberOfLayers << endl;

    if (initialGraphPrint) g.printGraph();

    string inlineTruthTable;
    // Unos tablice istinitosti i spremanje u memoriju.
    vector<bool> TABLE;
    for (int i = 0; i < pow(2, numberOfVariables); i++) {
        TABLE.push_back(0);
    }
    bool choice;
    cout << "\n\nUpisi 0 za koristenje tablice istinitosti, 1 za unos formule:\n";
    cout << "> ";
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
                cout << switchList[j] << " ";
                TABLE[switchList[j]] = 1;
            }
            cout << endl;
        }

        inlineTruthTable = "";
        cout << "TRUTH TABLE:\n";
        for (int i = 0; i < TABLE.size(); i++) {
            cout << i << ": "<< TABLE[i] << endl;
            inlineTruthTable += TABLE[i] + 48;
        }
        cout << "inlineTruthTable: " << inlineTruthTable << endl;
    }

    for (int i = 0; i < TABLE.size(); i++) {
        inlineTruthTable += TABLE[i] + 48;
    }

    // Deaktiviranje nepotrebnih konjunkta =>
    g.deactivateUnnecessary(TABLE);

    if (excludedGraphPrint) {
        cout << "\n\nGraf nakon iskljucivanja nepotrebnih konjunkata\n";
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
            cout << "\n\n\n            =====================================================================================\n";
            printf("            |                          ITERATION NUMBER: %4d                                   |\n", iter);
            cout << "            =====================================================================================\n";
        }

        if (displayPopulationAfterWalking) cout << "\nPopulation after walking:\n";
        for (int i = 0; i < numberOfAnts; i++) {
            if (i>numberOfChosenAnts - 1) antPopulation[i]->walk(&g);
            antPopulation[i]->evalFitness(TABLE);
            if (displayPopulationAfterWalking) displayAnt(i, antPopulation);
        }

        sort(antPopulation, antPopulation + numberOfAnts, compareAntsByFitness);

        if (displayPopulationAfterSorting) cout << "\nPopulation after sorting:\n";
        for (int i = 0; i < numberOfAnts; i++) {
            if (displayPopulationAfterSorting) displayAnt(i, antPopulation);
        }

        if (displayBestAnts) cout << "\nBest from population:\n";
        for (int i = 0;i < numberOfChosenAnts; i++) {
            if (displayBestAnts) {
                cout << "\nid: " << antPopulation[i]->id << "    " << "fitness: " << antPopulation[i]->fitness << endl;
                if (displayBestAntsPath) antPopulation[i]->displayPath();
                if (displayBestAntsTruthTable) antPopulation[i]->displayTruthTable();
                cout << "   Ant's formula: " << antPopulation[i]->getFormula() << endl;
                //cout << "Inline path:" << antPopulation[0]->inlinePath() << endl;
            }


            antPopulation[i]->leavePheromones(&g);
        }

        g.evaporatePheromones();

        if (printGraphAfterIteration) g.printGraph();
        if (drawGraphAfterIteration) g.drawGraph();

        // Reset graph after <resetAfter> itterations.
        if (iter % resetAfter == 0) {
            bestPath = antPopulation[0]->inlinePath();
            g.resetGraph();
            g.deactivateUnnecessary(TABLE);
            cout << "\n\n              *************** RESET ***************\n\n";

            for (int i = 0; i < numberOfChosenAnts; i++) {
                antPopulation[i]->loadPath(bestPath);
            }
        }

    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "\n\nSimulation time: " << elapsed.count() << " ms\n";

    if (displayBestSolution) {
        cout << "\nBest fitness: " << antPopulation[0]->fitness << endl;
        cout << "\nBest solution: " << antPopulation[0]->getFormula() << endl;
        cout << "Inline table:" << inlineTruthTable << endl;
        cout << "Inline path:" << antPopulation[0]->inlinePath() << endl;
    }

    // Log solution to file
    string filenameTemplate = "../solutionLogs/";
    filenameTemplate += "N" + to_string(numberOfVariables) + "M" + to_string(numberOfAnts) + "I" +
                              to_string(numberOfIterations);
    int counter = 1;
    while (true) {
        string filename = filenameTemplate + "-" + to_string(counter) + ".txt";
        counter++;
        ifstream infile(filename);
        if (infile.good()) continue;

        ofstream outfile(filename);
        outfile << "Simulation time: " << elapsed.count() << " ms\n";
        outfile << "\nBest fitness: " << antPopulation[0]->fitness << endl;
        outfile << "\nBest solution: " << antPopulation[0]->getFormula() << endl;
        outfile << "Inline table:" << inlineTruthTable << endl;
        outfile << "Inline path:" << antPopulation[0]->inlinePath() << endl;
        break;

    }

    return 0;
}
