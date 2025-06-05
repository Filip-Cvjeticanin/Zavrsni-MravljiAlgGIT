//
// Created by Filip on 6/4/2025.
//

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

#include "../headers/paramSetup.h"
#include "../headers/outputControll.h"
#include "../headers/parameters.h"

using namespace std;

void model_setup(const string& path) {

    ifstream file(path); // Open the file
    string line;

    if (file.is_open()) {
        string result;
        try {
            // numberOfIterations
            getline(file, line);
            result = parse_model_line(line);
            numberOfIterations = stoi(result);

            // resetAfter
            getline(file, line);
            result = parse_model_line(line);
            resetAfter = stoi(result);

            // numberOfVariables
            getline(file, line);
            result = parse_model_line(line);
            numberOfVariables = stoi(result);

            // numberOfAnts
            getline(file, line);
            result = parse_model_line(line);
            numberOfAnts = stoi(result);

            // numberOfChosenAnts
            getline(file, line);
            result = parse_model_line(line);
            numberOfChosenAnts = stoi(result);

            // initialConcentration
            getline(file, line);
            result = parse_model_line(line);
            initialConcentration = stod(result);

            // diminishRate
            getline(file, line);
            result = parse_model_line(line);
            diminishRate = stod(result);

            // truthTable
            getline(file, line);
            result = parse_model_line(line);
            truthTable = result;

            // steadyConvergence
            getline(file, line);
            result = parse_model_line(line);
            steadyConvergence = str_to_bool(result);

            // limitPheromones
            getline(file, line);
            result = parse_model_line(line);
            limitPheromones = str_to_bool(result);

            // maxPheromones
            getline(file, line);
            result = parse_model_line(line);
            maxPheromones = stod(result);

            // excludeProbability
            getline(file, line);
            result = parse_model_line(line);
            excludeProbability = stod(result);

            // printToConsole
            getline(file, line);
            result = parse_model_line(line);
            printToConsole = str_to_bool(result);

            file.close();

        } catch (const exception& e) {
            dout << "CONFIG ERROR: Wrong file content!!!" << endl;
        }
        file.close(); // Close the file
    } else {
        dout << "CONFIG ERROR: File not found!!!" << endl;
    }
}

string parse_model_line(string line) {
    string sol = "";
    bool copy = false;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '#') break;
        if (!copy) {
            if (line[i] == '=') copy = true;
        }
        else sol = sol + line[i];
    }
    return sol;
}

bool str_to_bool(const string& str) {
    if (str.substr(0,4) == "true") return true;
    return false;
}

void print_params() {
    dout << "number of iterations: " << numberOfIterations << endl;
    dout << "reset after: " << resetAfter << endl;
    dout << "number of variables: " << numberOfVariables << endl;
    dout << "number of antennas: " << numberOfAnts << endl;
    dout << "number of chosen antennas: " << numberOfChosenAnts << endl;
    dout << "initial concentration: " << initialConcentration << endl;
    dout << "diminish rate: " << diminishRate << endl;
    dout << "truth table: ";
    for (int i = 0; i < pow(2,numberOfVariables); i++) {
        dout << truthTable[i];
    }
    dout << endl;
    dout << "steadyConvergence: " << steadyConvergence << endl;
    dout << "limit pheromones: " << limitPheromones << endl;
    dout << "max pheromones: " << maxPheromones << endl;
    dout << "exclude probability: " << excludeProbability << endl;
    dout << "printToConsole: " << printToConsole << endl;
}
