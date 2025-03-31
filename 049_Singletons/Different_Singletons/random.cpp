#include "random.h"

namespace Uniform {
    Random::Random() : gen(rd()), dis(-1.0, 1.0) {
        std::cout << "Initialized Uniform randomizer" << std::endl;
    }

    Random& Random::getinstance() {
        static Random* instance = new Random();
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
        static Random* instance = &getinstance();
        if (instance) {
            delete instance;
            instance = nullptr;
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

    void Random::Init() {
        instance = new Random();
    }

    double Random::Generator(long double a, long double b) {
        if (!instance) Init();
        return instance->gen_random(a, b);
    }

    double Random::gen_random(long double a, long double b) noexcept {
        dis.param(std::normal_distribution<double>::param_type(a, b));
        return dis(gen);
    }

    void Random::Shutdown() {
        if (!instance) {
            std::cout << "Normal randomizer instance already deleted" << std::endl;
            return;
        }
        delete instance;
        instance = nullptr;
    }

    Random::~Random() {
        std::cout << "Destroyed Normal randomizer instance" << std::endl;
    }
}

namespace Global {
    static Random* s_Instance = nullptr; 

    Random::Random() : gen(rd()), dis(4) {
        std::cout << "Initialized Normal randomizer" << std::endl;
    }

    void Random::Init() {
        s_Instance = new Random();
    }

    double Random::Generator(long double c) {
        assert(s_Instance);
        return s_Instance->gen_random(c);
    }

    double Random::gen_random(double c) noexcept {
        dis.param(std::poisson_distribution<int>::param_type(c));
        return dis(gen);
    }

    void Random::Shutdown() {
        assert(s_Instance);
        delete s_Instance;
        s_Instance = nullptr;
    }

    Random::~Random() {
        std::cout << "Destroyed Normal randomizer instance" << std::endl;
    }
}
