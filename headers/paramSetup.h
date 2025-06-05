//
// Created by Filip on 6/4/2025.
//

#ifndef PARAMSETUP_H
#define PARAMSETUP_H
#include <string>

#endif //PARAMSETUP_H

// Functions for setting model paramaters.
void model_setup(const std::string& path);
std::string parse_model_line(std::string line);
bool str_to_bool(const std::string& str);
void print_params();

