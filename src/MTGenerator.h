#ifndef MONTECARLOPI_MTGENERATOR_H
#define MONTECARLOPI_MTGENERATOR_H
#include "RandomNumberGenerator.h"
#include <random>
class MTGenerator : public RandomNumberGenerator {
public:
    std::mt19937 generator;
    std::uniform_real_distribution<float> dis;
    MTGenerator() : generator(123), dis(0.0, 1.0){}
    MTGenerator(int seed) : generator(seed), dis(0.0, 1.0){}

private:

    float generate_number(){
        return dis(generator);
    };
};
#endif //MONTECARLOPI_MTGENERATOR_H
