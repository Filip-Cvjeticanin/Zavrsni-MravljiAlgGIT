//
// Created by Filip on 5/14/2025.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>


class Node {
public:
    Node* nextZero;
    Node* nextOne;
    Node* sibling;
    double nextZeroPheromone;
    double nextOnePheromone;
    bool end;
    bool type;
    int id;
    explicit Node(bool t = NULL, bool e = false);
    void setNodes(Node* nZ, Node* nO);
    void setPheromones(double nZP, double nOP);

    ~Node();
};


class Graph {
public:
    Node* startNode;

    int numberOfLayers;
    void setPheromone(int fromLayer, bool fromType, bool toType, double value);

    void printGraph();
    void drawGraph();

    void resetGraph();
    void deactivateUnnecessary(std::vector<bool> &table);

    void evaporatePheromones();
    Graph();
};
#endif //GRAPH_H
