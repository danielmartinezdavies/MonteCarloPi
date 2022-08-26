#ifndef MONTECARLOPI_PARAMETERS_H
#define MONTECARLOPI_PARAMETERS_H
#include <vector>
#include <string>
#include <iostream>
#include "RandomNumberGenerator.h"
#include "SobolGenerator.h"
#include "TrueRandomGenerator.h"
#include "MTGenerator.h"

class Parameters {
public:
    std::unique_ptr<RandomNumberGenerator> rng;
    Parameters() {
        rng = std::make_unique<SobolGenerator>(2);
    }
};
Parameters parseInputParameters(const std::vector<std::string> &parameters){
    Parameters p;
    int seed = 123;
    auto isSmaller = [&](int i) {return i < parameters.size()-1;};
    for(int i = 0; i < parameters.size();i++) {
        if (parameters[i] == "--help") {
            std::cout << "Possible Parameters:\n"
                         "--sobol\n"
                         "--random\n"
                         "--mersenne_twister\n"
                         "--seed  - specify seed for pseudo random number generators\n"
                      << std::endl;
            exit(0);

        }
        else if (parameters[i] == "--sobol") {
            p.rng = std::make_unique<SobolGenerator>(2);
        }
        else if (parameters[i] == "--random") {
            p.rng = std::make_unique<TrueRandomGenerator>();
        }
        else if (isSmaller(i) && parameters[i] == "--seed") {
            seed = (std::stoi(parameters[i+1]));
        }
        else if (parameters[i] == "--mersenne_twister") {
            p.rng = std::make_unique<MTGenerator>(seed);
        }


    }

    return p;
}
#endif //MONTECARLOPI_PARAMETERS_H
