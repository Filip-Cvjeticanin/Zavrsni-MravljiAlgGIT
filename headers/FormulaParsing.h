//
// Created by Filip on 5/16/2025.
//

#ifndef FORMULAPARSING_H
#define FORMULAPARSING_H

#include <vector>

void split(std::vector<std::string> & vekt, std::string formula);
int NOT(int x);
int findTableIndex(int mask, const int numberRepresentation [], int nVar);
void findIndexesToActivate(std::string member, std::vector<int> & switchList, int nVar);
#endif //FORMULAPARSING_H
