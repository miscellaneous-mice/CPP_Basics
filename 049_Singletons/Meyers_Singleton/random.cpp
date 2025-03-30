#include "random.h"

namespace Uniform {
    Random::Random(long double a, long double b) : gen(rd()), dis(a, b) {
        std::cout<<"Initialized Uniform randomizer"<<std::endl;
    }
    Random& Random::getinstance(long double a, long double b) {
        static Random instance(a, b);
        return instance;
    }
    double Random::Generator(long double a, long double b) {
        return getinstance(a, b).gen_random();
    }

    double Random::gen_random() noexcept {
        return dis(gen);
    }
    Random::~Random() {
        std::cout<<"Destriod Uniform randomizer instance"<<std::endl;
    }
}

namespace Normal {
    Random::Random(long double a, long double b) : gen(rd()), dis(a, b) {
        std::cout<<"Initialized Normal randomizer"<<std::endl;
    }
    Random& Random::getinstance(long double a, long double b) {
        static Random instance(a, b);
        return instance;
    }
    double Random::Generator(long double a, long double b) {
        return getinstance(a, b).gen_random();
    }

    double Random::gen_random() noexcept {
        return dis(gen);
    }
    Random::~Random() {
        std::cout<<"Destriod Normal randomizer instance"<<std::endl;
    }
}