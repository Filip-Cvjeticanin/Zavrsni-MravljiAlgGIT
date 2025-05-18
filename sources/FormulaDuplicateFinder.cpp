//
// Created by Filip on 5/18/2025.
//

#include <iostream>
#include <vector>
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

int main() {
    string s;
    cout << "Enter formula: ";
    getline(cin, s);
    vector<string> terms;

    // split formula into terms
    split(terms, s);

    // check for each term
    for (int i = 0; i < terms.size(); i++) {

        // check if term was already processed
        bool processed = false;
        for (int j = 0; j < i; j++) {
            if (terms[i] == terms[j]) processed = true;
        }
        if (processed) continue;

        // if term wasn't processed count it how manny times it appears
        int count = 0;
        for (int j = i; j < terms.size(); j++) if (terms[i] == terms[j]) count++;
        cout << terms[i] << " => " << count << endl;
    }
    return 0;
}