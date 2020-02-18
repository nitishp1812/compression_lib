#ifndef ARITH_MODEL_H
#define ARITH_MODEL_H

#include <string>
#include <utility>
#include <fstream>
#include <iostream>

namespace data_compression {
    std::pair<double, double> getProbability(char c);
    double encode(std::string filename);
    std::string decode(double encoded);
    char getSymbol(double val);
}

#endif