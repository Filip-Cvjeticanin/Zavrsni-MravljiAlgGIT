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
#include "../headers/outputControll.h"
#include <filesystem>

#include "../headers/Graph.h"

using namespace std;

// Generira masku takvu da je na nultoj poziciji u vektoru vrijednost najznačajnije varijable
// Npr:   A   B   C                     0   1   2
//        0   0   1       =>    mask = [0,  0,  1]

void generateMask(int x, std::vector<bool> &mask) {
    mask.clear();
    for (int j = 0; j < numberOfVariables; j++) {
        mask.insert(mask.begin(), x % 2);
        x = x / 2;
    }
}

bool compareAntsByFitness(Ant* a, Ant* b) {
    return a->fitness > b->fitness;
}

Ant::Ant(int id) {
    this->id = id;
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

    bool skipGroup = false;

    for (int i = 0; i < g->numberOfLayers; i++) {
        double probabilityZero = curr->nextZeroPheromone / (curr->nextZeroPheromone + curr->nextOnePheromone);
        double randomNumber = dist(gen);

        // On start of decide if it's going to be excluded with probabilit p;
        if (i % numberOfVariables == 0) {
            skipGroup = false;
            double probability = -1;
            if (fitness >= 1) probability = excludeProbability;
            double randomNumber2 = dist(gen);
            if (randomNumber2 < probability) skipGroup = true;
        }

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
    dout << "   Ant's path: " << endl;
    for (int i = 0; i < pow(2,numberOfVariables); i++) {
        printf("    %4d: ", i);
        for (int j = 0; j < numberOfVariables; j++) {
            dout << Path[j + numberOfVariables * i] << " -> ";
        }
        dout << endl;
    }
}

void Ant::makeTruthTable() {

    for (int i = 0; i < pow(2,numberOfVariables); i++) {

        truthTable[i] = 0;

        vector<bool> values;
        generateMask(i, values);

        int pathCounter = 0;
        for (int j = 0; j < pow(2,numberOfVariables); j++) {

            vector<bool> notTemp;
            generateMask(j, notTemp);

            bool result;
            bool checked = false;
            bool allGood = true;
            //dout << " i j " << i << " " << j << "==============" <<endl;
            for (int k = 0; k < numberOfVariables; k++) {
                //dout << pathCounter<< ": "<< Path[pathCounter] << endl;
                if (Path[pathCounter] && values[k] == notTemp[k]) {
                    checked = true;
                }
                else if (Path[pathCounter] && values[k] != notTemp[k]) {
                    allGood = false;
                }
                pathCounter++;

            }
            result = checked && allGood;
            //dout << "checked " << checked << endl;
            //dout << "allGood " << allGood << endl;
            //dout << "result " << result << endl;

            truthTable[i] = truthTable[i] || result;
        }
    }
}

void Ant::displayTruthTable() {
    dout << "   Ant's truth table:" << endl;
    for (int i = 0; i < truthTable.size(); i++) {
        dout << "       " << i << ": " << truthTable[i] << endl;
    }
}

string Ant::getFormula() {
    string formula = "";
    bool newContent = false;
    int pathCounter = 0;

    for (int i = 0; i < pow(2,numberOfVariables); i++) {
        vector<bool> mask;
        generateMask(i, mask);

        if (newContent) formula += " + ";
        newContent = false;

        for (int j = 0; j < numberOfVariables; j++) {
            if (Path[pathCounter]) {
                newContent = true;
                if (!mask[j]) formula += "~";
                formula += (j + 65);
            }
            pathCounter++;
        }
    }

    // Makni " + " s kraja ako postoji.
    if (formula.size() >= 3 && formula.substr(formula.size() - 3) == " + ") {
        formula.erase(formula.size() - 3);
    }

    return formula;
}

string Ant::inlinePath() {
    string sol;
    for (int i = 0; i < numberOfVariables * pow(2, numberOfVariables); i++) {
        if (Path[i]) sol += '1';
        else sol += '0';
    }
    return sol;
}

void Ant::loadPathFromTable(std::vector<bool> &table) {
    int pathCounter = 0;
    for (int i = 0; i < pow(2,numberOfVariables); i++) {
        if (table[i] == 0) {
            pathCounter += numberOfVariables;
            continue;
        }
        vector<bool> mask;
        generateMask(i, mask);
        for (int j = 0; j < numberOfVariables; j++) {
            Path[pathCounter] = 1;
            pathCounter++;
        }
    }
    makeTruthTable();
}

void Ant::loadPath(std::string inlinePath) {
    for (int i = 0; i < inlinePath.length(); i++) {
        if (inlinePath[i] == '1') Path[i] = 1;
        else Path[i] = 0;
    }
    makeTruthTable();
}


double Ant::evalFitness(const std::vector <bool> &TABLE) {
    this->makeTruthTable();

    int pathSum = pow(2,numberOfVariables);
    int tableMatch = 0;

    for (int i = 0; i < numberOfVariables*pow(2,numberOfVariables); i++) {
        pathSum += Path[i];
    }

    for (int i = 0; i < pow(2,numberOfVariables); i++) {
        if (TABLE[i] == truthTable[i]) tableMatch++;
    }

    double sol;
    if (tableMatch == pow(2,numberOfVariables)) sol = (double) tableMatch / pathSum + 1;
    else sol = tableMatch / pow(2,numberOfVariables);
    fitness = sol;
    return sol;
}

void Ant::leavePheromones(Graph *g) {
    Node* curr = g->startNode;
    double leaveAmount = 0.1;
    if (fitness >= 1) leaveAmount = fitness;
    for (int i = 0; i < g->numberOfLayers; i++) {
        if (Path[i] == 0) {
            curr->nextZeroPheromone += leaveAmount;
            if (limitPheromones) curr->nextZeroPheromone = min(curr->nextZeroPheromone + leaveAmount, maxPheromones);
            curr = curr->nextZero;
        }
        else if(Path[i] == 1){
            curr->nextOnePheromone += leaveAmount;
            if (limitPheromones) curr->nextOnePheromone = min(curr->nextOnePheromone + leaveAmount, maxPheromones);
            curr = curr->nextOne;
        }
    }
}
