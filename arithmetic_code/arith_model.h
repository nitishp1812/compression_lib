#ifndef ARITH_MODEL_H
#define ARITH_MODEL_H

#include <vector>

namespace data_compression {
    class ArithmeticModel {
        public:
        struct ModelProb {
            private:
            int upper_, lower_, denominator_;

            public:
            int getUpper();
            int getLower();
            int getDenominator();
        };
        
        ~ArithmeticModel();
        ModelProb getProbability(char c);
    };
}

#endif