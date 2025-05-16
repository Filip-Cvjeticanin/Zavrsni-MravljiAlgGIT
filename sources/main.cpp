//
// Created by Filip on 5/14/2025.
//
#include <iostream>
#include <math.h>
#include <vector>
#include "../headers/parameters.h"
#include "../headers/Graph.h"

using namespace std;

int main() {
    cout << "MravljiAlgoritam" << endl;
    Graph g = Graph();
    cout << g.numberOfLayers << endl;

    g.printGraph();



    // Unos tablice istinitosti i spremanje u memoriju.
    vector<bool> TABLE;
    //cin >> truthTable; OVDJE SE MOŽE OMOGUĆITI UNOS TABLICE ISTINITOSTI
    //                    inače se koristi default postavljen u parameters.h
    for (int i = 0; i < pow(2, numberOfVariables); i++) {
        if (truthTable[i] == '0') TABLE.push_back(0);
        else TABLE.push_back(1);
    }

    // Izrada tablice istinitosti iz formule i spremanje u memoriju.
    //    ...
    //    ...

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
    return 0;
}
