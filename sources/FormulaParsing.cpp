//
// Created by Filip on 5/16/2025.
//

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "../headers/FormulaParsing.h"

using namespace std;

void split(vector<string> & vekt, string formula) {
    formula += "+";
    cout << formula << endl;
    int i = 0;
    string tmp = "";
    while (i < formula.length()) {
        if (formula[i] == ' ') {
            i++;
            continue;
        }
        if (formula[i] == '+') {
            vekt.push_back(tmp);
            tmp = "";
        }
        else tmp += formula[i];
        i++;
    }
}