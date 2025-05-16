//
// Created by Filip on 5/16/2025.
//

#ifndef ANT_H
#define ANT_H
#include <vector>
#include "./Graph.h"
#include <cmath>
#include "./parameters.h"

class Ant {
public:
    std::vector <bool> Path;
    std::vector <bool> truthTable;
    double fitness;

    Ant();

    void walk(Graph* g);
    void displayPath();


};

#endif //ANT_H
