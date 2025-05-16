//
// Created by Filip on 5/16/2025.
//

#include <iostream>
#include <cstdio>
#include <cmath>
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

int NOT(int x) {
    if (x==1) return 0 ;
    if (x==0) return 1;
    return x;
}

int findTableIndex(int mask, const int numberRepresentation [], int nVar) {
    int sol = 0;
    int factor = 1;
    for (int i = 0; i < nVar; i++) {
        if (numberRepresentation[i] > -1) {
            sol += numberRepresentation[i] * factor;
        }
        else {
            sol += (mask % 2) * factor;
            mask = mask / 2;
        }
        factor *= 2;
    }
    return sol;
}

void findIndexesToActivate(string member, vector<int> & switchList, int nVar) {

    string uppercase="";
    int numberRepresentation[nVar];

    for (int i = 0; i < nVar; i++) {
        numberRepresentation[i] = -1;
    }

    for (int i = 0; i < member.length(); i++) {
        if (member[i] >= 'a' && member[i] <= 'z') {
            uppercase += member[i] - 32;
        }
        else {
            uppercase += member[i];
        }
    }

    cout << uppercase << endl;
    cout << "==================" << endl;

    int value = 1;
    for (int i = 0; i < member.length(); i++) {
        if (uppercase[i] == '~') value = NOT(value);
        else {
            numberRepresentation[nVar - (member[i] - 'A') - 1] = value;
            value = 1;
        }
    }

    int notSet = 0;
    for (int i = nVar - 1; i >= 0; i--) {
        if (numberRepresentation[i] == -1) notSet++;
        cout << numberRepresentation[i] << " ";
    }
    cout << "\nNot set: " << notSet << endl;


    for (int mask = 0; mask < pow(2, notSet); mask++) {
        cout << "mask: " << mask << " TR: ";
        cout << findTableIndex(mask, numberRepresentation, nVar) << endl;
        switchList.push_back(findTableIndex(mask, numberRepresentation, nVar));
    }


}