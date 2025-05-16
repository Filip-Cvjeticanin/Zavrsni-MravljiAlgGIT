//
// Created by Filip on 5/14/2025.
//

#ifndef GRAPH_H
#define GRAPH_H


class Node {
public:
    Node* nextZero;
    Node* nextOne;
    Node* sibling;
    float nextZeroPheromone;
    float nextOnePheromone;
    bool end;
    bool type;
    int id;
    explicit Node(bool t = NULL, bool e = false);
    void setNodes(Node* nZ, Node* nO);
    void setPheromones(float nZP, float nOP);

    ~Node();
};


class Graph {
public:
    Node* startNode;

    int numberOfLayers;
    void setPheromone(int fromLayer, bool fromType, bool toType, float value);
    void printGraph();
    void drawGraph();
    Graph();
};
#endif //GRAPH_H
