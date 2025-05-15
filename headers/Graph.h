//
// Created by Filip on 5/14/2025.
//

#ifndef GRAPH_H
#define GRAPH_H

class Node {
public:
    explicit Node(bool t = NULL,
                  bool e = false);

    void setNodes(Node* nZ, Node* nO);
    void setPheromones(float nZP, float nOP);


    Node* nextZero;
    Node* nextOne;

    float nextZeroPheromone;
    float nextOnePheromone;

    bool end;
    bool type;

    ~Node();
};


class Graph {
public:
    Node* startNode;

    int numberOfLayers;

    Graph();
};
#endif //GRAPH_H
