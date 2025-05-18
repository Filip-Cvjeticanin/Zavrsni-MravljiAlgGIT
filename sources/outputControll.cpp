//
// Created by Filip on 5/18/2025.
//

#include "../headers/outputControll.h"
#include <iostream>
#include <fstream>

dualStream::dualStream(){
    out1 = &std::cout;

    bool valid = true;

    int counter = 1;
    while (valid) {
        std::string filename = "./L-logs/log" + std::to_string(counter) + ".txt";
        std::ifstream infile(filename);
        if (infile.good()) {
            counter++;
        }
        else valid = false;
    }

    name = "log" + std::to_string(counter) + ".txt";
    fileStream.open("./L-logs/" + name);
    out2 = &fileStream;
}
