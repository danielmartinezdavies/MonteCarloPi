#ifndef MONTECARLOPI_SOBOLGENERATOR_H
#define MONTECARLOPI_SOBOLGENERATOR_H
#include "RandomNumberGenerator.h"
#include <boost/random/sobol.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/variate_generator.hpp>

class SobolGenerator : public RandomNumberGenerator {
public:
    typedef boost::variate_generator<boost::random::sobol&, boost::uniform_01<float>> quasi_random_gen_t;
    boost::random::sobol engine;
    quasi_random_gen_t gen;
    SobolGenerator(int dimension) : engine(dimension), gen(engine, boost::uniform_01<float>()){}

private:

    float generate_number(){
        return gen.operator()();
    };
};
#endif //MONTECARLOPI_SOBOLGENERATOR_H
