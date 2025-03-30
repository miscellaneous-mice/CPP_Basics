#include "random.h"

namespace Uniform {
    Random::Random() : gen(rd()), dis(-1.0, 1.0) {
        std::cout << "Initialized Uniform randomizer" << std::endl;
    }

    Random& Random::getinstance() {
        static Random* instance = new Random();
        if (instance == nullptr) {
            throw std::runtime_error("Uniform Random instance has been deleted!");
        }
        return *instance;
    }

    double Random::Generator(long double a, long double b) {
        return getinstance().gen_random(a, b);
    }

    double Random::gen_random(long double a, long double b) noexcept {
        dis.param(std::uniform_real_distribution<double>::param_type(a, b));
        return dis(gen);
    }

    void Random::Shutdown() {
        static Random*& instance = *reinterpret_cast<Random**>(&getinstance());
        if (instance) {
            delete instance;
            instance = nullptr;
            std::cout << "Uniform randomizer instance deleted" << std::endl;
        } else {
            std::cout << "Uniform randomizer instance already deleted" << std::endl;
        }
    }

    Random::~Random() {
        std::cout << "Destroyed Uniform randomizer instance" << std::endl;
    }
}

namespace Normal {
    Random::Random() : gen(rd()), dis(-1.0, 1.0) {
        std::cout << "Initialized Normal randomizer" << std::endl;
    }

    Random& Random::getinstance() {
        static Random* instance = new Random();
        if (instance == nullptr) {
            throw std::runtime_error("Normal Random instance has been deleted!");
        }
        return *instance;
    }

    double Random::Generator(long double a, long double b) {
        return getinstance().gen_random(a, b);
    }

    double Random::gen_random(long double a, long double b) noexcept {
        dis.param(std::normal_distribution<double>::param_type(a, b));
        return dis(gen);
    }

    void Random::Shutdown() {
        static Random*& instance = *reinterpret_cast<Random**>(&getinstance());
        if (instance) {
            delete instance;
            instance = nullptr;
            std::cout << "Normal randomizer instance deleted" << std::endl;
        } else {
            std::cout << "Normal randomizer instance already deleted" << std::endl;
        }
    }

    Random::~Random() {
        std::cout << "Destroyed Normal randomizer instance" << std::endl;
    }
}
