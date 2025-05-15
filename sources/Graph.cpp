//
// Created by Filip on 5/14/2025.
//
#include <iostream>
#include "../headers/Graph.h"
#include "../headers/parameters.h"
#include <math.h>
using namespace std;

Node::Node(bool t,
           bool e)
{
    end = e;
    type = t;

    nextZero = nullptr;
    nextOne = nullptr;
    nextZeroPheromone = initialConcentration;
    nextOnePheromone = initialConcentration;
}


void Node::setNodes(Node* nZ, Node* nO) {
    nextZero = nZ;
    nextOne = nO;
}


void Node::setPheromones(float nZP, float nOP) {
    nextZeroPheromone = nZP;
    nextOnePheromone = nOP;
}

Node::~Node() {
    if (type == 0) {
        delete nextZero;
        delete nextOne;
    }
}



Graph::Graph() {
    startNode = new Node();
    numberOfLayers = numberOfVariables * pow(2, numberOfVariables);

    Node* newLayerZero = new Node(0);
    Node* newLayerOne = new Node(1);

    startNode->setNodes(newLayerZero, newLayerOne);

    for (int i = 1; i < numberOfLayers; i++) {
        Node* oldLayerZero = newLayerZero;
        Node* oldLayerOne = newLayerOne;

        newLayerZero = new Node(0);
        newLayerOne = new Node(1);

        oldLayerZero->setNodes(newLayerOne, newLayerOne);
        oldLayerOne->setNodes(newLayerZero, newLayerOne);
    }
}



