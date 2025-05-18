//
// Created by Filip on 5/16/2025.
//

#ifndef ANT_H
#define ANT_H
#include <vector>
#include "./Graph.h"
#include <cmath>
#include "./parameters.h"

class Ant;

void generateMask(int x, std::vector<bool> &mask);
bool compareAntsByFitness(Ant* a, Ant* b);

class Ant {
public:
    std::vector <bool> Path;
    std::vector <bool> truthTable;
    double fitness;
    int id;

    Ant(int id = -1);

    void walk(Graph* g);
    void displayPath();
    void makeTruthTable();
    void displayTruthTable();
    std::string getFormula();
    std::string inlinePath();

    void loadPathFromTable(std::vector<bool> &table);
    void loadPath(std::string inlinePath);

    double evalFitness(const std::vector <bool> &TABLE);
    void leavePheromones(Graph* g);
};

#endif //ANT_H
