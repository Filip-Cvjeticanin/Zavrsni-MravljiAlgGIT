//
// Created by Filip on 5/18/2025.
// Streams output to both the console and a log file
//

#ifndef OUTPUTCONTROLL_H
#define OUTPUTCONTROLL_H

#include <fstream>
#include "../headers/parameters.h"

class dualStream {
public:

    std::string name;

    dualStream();

    template<typename T>
    dualStream& operator<<(const T& val) {
        if (printToConsole) *out1 << val;
        *out2 << val;
        return *this;
    }

    dualStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
        // For manipulators like std::endl, std::flush, etc.
        if (printToConsole) *out1 << manip;
        *out2 << manip;
        return *this;
    }

private:
    std::ostream* out1;
    std::ostream* out2;
    std::ofstream fileStream;
};

inline dualStream dout;

#endif //OUTPUTCONTROLL_H
