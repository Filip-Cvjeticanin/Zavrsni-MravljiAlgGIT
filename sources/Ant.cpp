//
// Created by Filip on 5/16/2025.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include <limits>

#include "../headers/parameters.h"
#include "../headers/Ant.h"
#include "../headers/Graph.h"

using namespace std;

Ant::Ant() {
    fitness = 0;
    for (int i = 0; i < pow(2, numberOfVariables); i++) {
        truthTable.push_back(0);
    }
    for (int i = 0; i < pow(2, numberOfVariables) * numberOfVariables; i++) {
        Path.push_back(0);
    }
}

void Ant::walk(Graph* g) {
    std::random_device rd;  // Random seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<> dist(0.0, std::nextafter(1.0, 2.0)); // [0.0, 1.0]

    Node* curr = g->startNode;

    for (int i = 0; i < g->numberOfLayers; i++) {
        double probabilityZero = curr->nextZeroPheromone / (curr->nextZeroPheromone + curr->nextOnePheromone);
        double randomNumber = dist(gen);
        if (randomNumber < probabilityZero) {
            Path[i] = 0;
            curr = curr->nextZero;
        }
        else {
            Path[i] = 1;
            curr = curr->nextOne;
        }
    }
}

void Ant::displayPath() {
    for (int i = 0; i < pow(2,numberOfVariables); i++) {
        printf("%4d: ", i);
        for (int j = 0; j < numberOfVariables; j++) {
            cout << Path[j + numberOfVariables * i] << " -> ";
        }
        cout << endl;
    }
}

