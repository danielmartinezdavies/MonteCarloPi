#ifndef MONTECARLOPI_PARAMETERS_H
#define MONTECARLOPI_PARAMETERS_H
#include <vector>
#include <string>
#include <iostream>
#include "RandomNumberGenerator.h"
#include "SobolGenerator.h"

class Parameters {
public:
    std::unique_ptr<RandomNumberGenerator> rng;
    Parameters() {
        rng = std::make_unique<SobolGenerator>(2);
    }
};
Parameters parseInputParameters(const std::vector<std::string> &parameters){
    Parameters p;
    for(int i = 0; i < parameters.size();i++) {
        if (parameters[i] == "--help") {
            std::cout << "Possible Parameters:\n"
                         "--sobol\n"
                         "--random\n"
                         "--pseudo\n"
                      << std::endl;
            exit(0);

        }
        else if (parameters[i] == "--sobol") {
            p.rng = std::make_unique<SobolGenerator>(2);
        }

    }

    return p;
}
#endif //MONTECARLOPI_PARAMETERS_H
