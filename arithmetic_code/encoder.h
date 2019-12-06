#ifndef ARITH_ENCODER_H
#define ARITH_ENCODER_H

#include <string>
#include <fstream>

#include "arith_model.h"

namespace data_compression {

    void encode(std::string filename);
    void output_bit(bool bit);
    void output_bit(bool bit, int &pending);

}

#endif