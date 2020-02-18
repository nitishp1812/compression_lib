#include "arith_model.h"

double data_compression::encode(std::string filename) {
    std::ifstream in_file(filename);

    double high = 1.0;
    double low = 0.0;
    char c;

    while ( in_file >> c ) {
        std::pair<double, double> prob = getProbability(c);
        double range = high - low;

        low = low + (range * prob.first);
        high = low + (range * prob.second); 
    }
    
    double compressed = low + ((high - low) / 2);
    return compressed;
}

std::string data_compression::decode(double encoded) {
    double high = 1.0;
    double low = 0.0;

    std::string out = "";

    for (;;) {
        double range = high - low;
        encoded = (encoded - low) / range;
        
        char c = getSymbol(encoded);
        out += c;
        
        double next = (encoded * 100) - static_cast<int>(encoded * 100);
        if (next <= 0.0 || next > 0.26) // end of double encoded string
            return;
        
        std::pair<double,double> prob = getProbability(c);
        low = low + (range * prob.first);
        high = low + (range * prob.second); 
    }

    return out;
}

std::pair<double, double> data_compression::getProbability(char c) {
    return {(c - 'A') * 0.01, ((c - 'A') * 0.01) + 0.01};
}

char data_compression::getSymbol(double val) {
    return 'A' + static_cast<int>(val * 100); // get the first 2 decimal digits
}
