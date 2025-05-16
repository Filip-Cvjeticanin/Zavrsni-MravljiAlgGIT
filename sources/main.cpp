//
// Created by Filip on 5/14/2025.
//
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#include "../headers/parameters.h"
#include "../headers/Graph.h"
#include "../headers/FormulaParsing.h"
#include "../headers/Ant.h"

using namespace std;

int main() {
    cout << "MravljiAlgoritam" << endl;
    Graph g = Graph();
    cout << g.numberOfLayers << endl;

    g.printGraph();

    // Unos tablice istinitosti i spremanje u memoriju.
    vector<bool> TABLE;
    for (int i = 0; i < pow(2, numberOfVariables); i++) {
        TABLE.push_back(0);
    }
    bool choice;
    cout << "\n\nUpisi 0 za koristenje tablice istinitosti, 1 za unos formule: ";
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

        string inlineTruthTable = "";
        cout << "TRUTH TABLE:\n";
        for (int i = 0; i < TABLE.size(); i++) {
            cout << i << ": "<< TABLE[i] << endl;
            inlineTruthTable += TABLE[i] + 48;
        }
        cout << "inlineTruthTable: " << inlineTruthTable << endl;
    }

    // Deaktiviranje nepotrebnih konjunkta =>
    //       - postavljanje feromonskih tragova za uključivanje određenih
    //         elementa na 0
    int counter1 = 0, counter2 = 0;
    for (counter1 = 0; counter1 < pow(2, numberOfVariables); counter1++) {
        for (int i = 0; i < numberOfVariables; i++) {
            if (TABLE[counter1] == 0) {
                g.setPheromone(counter2, 0, 1, 0);
                g.setPheromone(counter2, 1, 1, 0);
            }
            counter2++;
        }
    }

    cout << "\n\nGraf nakon isključivanja nepotrebnih konjunkata\n";
    g.printGraph();
    g.drawGraph();


    // OVDJE POCINJEMO SA SIMULACIJOM MRAVA
    // ...
    // ...
    // ...

    /*cout << "\n\nTestiranje klase mrava:\n";
    Ant *a2 = new Ant();
    char c = 'n';
    while (c == 'n') {
        cout << "Mrav 2: " << endl;
        a2->walk(&g);
        a2->displayPath();
        a2->makeTruthTable();
        a2->displayTruthTable();
        cout << a2->evalFitness(TABLE);
        cin >> c;
    }*/

    Ant* antPopulation[numberOfAnts];
    for (int i = 0; i < numberOfAnts; i++) {
        antPopulation[i] = new Ant(i);
        antPopulation[i]->walk(&g);
        antPopulation[i]->evalFitness(TABLE);
        cout << "i:" << i << "    " << "fitness: " << antPopulation[i]->fitness << endl;
    }
    sort(antPopulation, antPopulation + numberOfAnts, compareAntsByFitness);
    for (int i = 0; i < numberOfAnts; i++) {
        cout << "i:" << i << "    " << "id: " << antPopulation[i]->id << "    " << "fitness: " << antPopulation[i]->fitness << endl;
    }
    for (int i = 0;i < numberOfChosenAnts; i++) {
        cout << "\nid: " << antPopulation[i]->id << "    " << "fitness: " << antPopulation[i]->fitness << endl;
        antPopulation[i]->displayPath();
        antPopulation[i]->displayTruthTable();
    }
    return 0;
}
