//
// Created by Filip on 5/14/2025.
//
#include <iostream>
#include "../headers/Graph.h"
#include "../headers/parameters.h"
#include <cmath>
using namespace std;

Node::Node(bool t,
           bool e)
{
    end = e;
    type = t;
    id = -1;

    sibling = nullptr;
    nextZero = nullptr;
    nextOne = nullptr;
    nextZeroPheromone = initialConcentration;
    nextOnePheromone = initialConcentration;
}


void Node::setNodes(Node* nZ, Node* nO) {
    nextZero = nZ;
    nextOne = nO;
}


void Node::setPheromones(double nZP, double nOP) {
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
    startNode->sibling = startNode;
    startNode->id = 0;
    numberOfLayers = numberOfVariables * pow(2, numberOfVariables);

    Node* newLayerZero = new Node(0);
    Node* newLayerOne = new Node(1);

    newLayerZero->id = 1;
    newLayerOne->id = 1;

    newLayerZero->sibling = newLayerOne;
    newLayerOne->sibling = newLayerZero;

    startNode->setNodes(newLayerZero, newLayerOne);

    for (int i = 1; i < numberOfLayers; i++) {
        Node* oldLayerZero = newLayerZero;
        Node* oldLayerOne = newLayerOne;

        newLayerZero = new Node(0);
        newLayerOne = new Node(1);
        newLayerZero->id = i + 1;
        newLayerOne->id = i + 1;


        newLayerZero->sibling = newLayerOne;
        newLayerOne->sibling = newLayerZero;

        oldLayerZero->setNodes(newLayerZero, newLayerOne);
        oldLayerOne->setNodes(newLayerZero, newLayerOne);


    }

    newLayerZero->end = true;
    newLayerOne->end = true;
}


void Graph::setPheromone(int fromLayer, bool fromType, bool toType, double value) {
    Node* curr = startNode;
    for (int i = 0; i < fromLayer; i++) {
        if (curr == nullptr) {
            cout << "ERROR in setPheromone() ===============================================" << endl;
            return;
        }
        curr = curr->nextZero;
    }

    if (fromType) curr = curr->sibling;
    if (!toType) curr->nextZeroPheromone = value;
    else curr->nextOnePheromone = value;
}

void Graph::printGraph() {
    Node* curr0 = startNode;
    Node* curr1 = startNode;

    cout << "START LAYER:" << endl;
    for (int i = 0; i < numberOfLayers + 1; i++) {
        cout << "Layer " << i  << ": " << endl;
        cout << "   [0-0]:  " << curr0->nextZeroPheromone << ", ";
        cout << "[0-1]:  " << curr0->nextOnePheromone << ", ";
        cout << "[1-0]:  " << curr1->nextZeroPheromone << ", ";
        cout << "[1-1]:  " << curr1->nextOnePheromone << endl;
        curr0 = curr0->nextZero;
        curr1 = curr1->nextOne;
    }
}

void Graph::drawGraph() {
    Node* curr = startNode;
    for (int i = 0; i < numberOfLayers; i++) {
        Node* sib = curr->sibling;
        printf("              +----------+\n");
        printf("              |LAYER%5d|              \n", curr->id);
        printf("              +----------+\n");
        printf("           1                   0       \n");
        printf("          /  \\                / \\      \n");
        printf("         1    0              1   0       \n");
        printf("         |    \\             /    |       \n");
        printf("%10f%10f%10f%10f\n", sib->nextOnePheromone, sib->nextZeroPheromone
            , curr->nextOnePheromone, curr->nextZeroPheromone);
        curr = curr->nextZero;
    }

    printf("              +----------+\n");
    printf("              |LAYER%5d|              \n", curr->id);
    printf("              +----------+\n");
}

void Graph::resetGraph() {
    Node* curr = startNode;
    for (int i = 0; i < numberOfLayers; i++) {
        curr->nextZeroPheromone = initialConcentration;
        curr->nextOnePheromone = initialConcentration;

        curr = curr->sibling;

        curr->nextZeroPheromone = initialConcentration;
        curr->nextOnePheromone = initialConcentration;

        curr = curr->nextZero;
    }
}

void Graph::deactivateUnnecessary(std::vector<bool>& table) {
    // Deaktiviranje nepotrebnih konjunkta =>
    //       - postavljanje feromonskih tragova za uključivanje određenih
    //         elementa na 0
    int counter1 = 0, counter2 = 0;
    for (counter1 = 0; counter1 < pow(2, numberOfVariables); counter1++) {
        for (int i = 0; i < numberOfVariables; i++) {
            if (table[counter1] == 0) {
                setPheromone(counter2, 0, 1, 0);
                setPheromone(counter2, 1, 1, 0);
            }
            counter2++;
        }
    }
}

void Graph::evaporatePheromones() {
    Node* curr = startNode;
    Node* sib;
    curr->nextZeroPheromone = curr->nextZeroPheromone * (1 - diminishRate);
    curr->nextOnePheromone = curr->nextOnePheromone * (1 - diminishRate);
    curr = curr->nextZero;
    for (int i = 1; i < numberOfLayers; i++) {
        sib = curr->sibling;
        curr->nextZeroPheromone = curr->nextZeroPheromone * (1 - diminishRate);
        curr->nextOnePheromone = curr->nextOnePheromone * (1 - diminishRate);
        sib->nextZeroPheromone = sib->nextZeroPheromone * (1 - diminishRate);
        sib->nextOnePheromone = sib->nextOnePheromone * (1 - diminishRate);
        curr = curr->nextZero;
    }
}






