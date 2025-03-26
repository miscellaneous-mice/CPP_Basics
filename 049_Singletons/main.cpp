#include <random>
#include <iostream>
#include <vector>

class Random {
public:
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    static Random& Get() {
        static Random instance;
        return instance;
    }

    static double RandomNumber() {
        return Get().gen_random();
    }

    static std::vector<double> GenRandElements(size_t n) {
        std::vector<double> result;
        result.reserve(n);
        for (size_t i = 0; i < n; ++i) {
            result.push_back(RandomNumber());
        }
        return result;
    }

private:
    Random() : gen(rd()), dis(-1.0, 1.0) {}

    double gen_random() noexcept {
        return dis(gen);
    }

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<double> dis;
};

int main() {
    std::cout << Random::RandomNumber() << std::endl;
    std::cout << Random::RandomNumber() << std::endl;

    for (auto& rand_elem : Random::GenRandElements(5))
        std::cout << rand_elem << ", ";
    std::cout << std::endl;

    return 0;
}
