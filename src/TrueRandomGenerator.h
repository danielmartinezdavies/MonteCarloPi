#ifndef MONTECARLOPI_TRUERANDOMGENERATOR_H
#define MONTECARLOPI_TRUERANDOMGENERATOR_H
#include "RandomNumberGenerator.h"
#include <random>
class TrueRandomGenerator : public RandomNumberGenerator {
public:
    std::random_device non_det;
    std::uniform_real_distribution<float> dis;
    TrueRandomGenerator() : dis(0.0, 1.0){}

private:

    float generate_number(){
        return dis(non_det);
    };
};
#endif //MONTECARLOPI_TRUERANDOMGENERATOR_H
