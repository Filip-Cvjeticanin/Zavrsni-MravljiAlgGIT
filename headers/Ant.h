//
// Created by Filip on 5/16/2025.
//

#ifndef ANT_H
#define ANT_H
#include <vector>
#include "./Graph.h"
#include <cmath>
#include "./parameters.h"

void generateMask(int x, std::vector<bool> &mask);

class Ant {
public:
    std::vector <bool> Path;
    std::vector <bool> truthTable;
    double fitness;

    Ant();

    void walk(Graph* g);
    void displayPath();
    double makeTruthTable();


};

#endif //ANT_H
