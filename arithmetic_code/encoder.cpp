#include "encoder.h"

using namespace data_compression;

void encode(std::string filename) {
    std::ifstream target_file(filename);

    unsigned high = 0xFFFFFFFFU;
    unsigned low = 0;

    int pending_bits = 0;
    char c;

    ArithmeticModel* model = new ArithmeticModel();

    while (target_file >> c) {
        unsigned range = high - low + 1;

        ArithmeticModel::ModelProb probability = model->getProbability(c);
        high = low + ((range * probability.getUpper()) / probability.getDenominator());
        low = low + ((range * probability.getLower()) / probability.getDenominator());
    }

    delete model;
}
