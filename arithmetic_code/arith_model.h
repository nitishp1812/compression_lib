#ifndef ARITH_MODEL_H
#define ARITH_MODEL_H

#include <string>
#include <utility>
#include <fstream>
#include <iostream>

namespace data_compression {
    std::pair<double, double> getProbability(char c);
    void arithmetic_encode(std::string in_filename, std::string out_filename);
    void arithmetic_decode(std::string in_filename, std::string out_filename);
    char getSymbol(double val);
}

#endif