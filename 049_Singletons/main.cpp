#include <random>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

class Random {
public:
    Random(const Random& other) = delete;
    static Random& Get() {
        static Random instance;
        return instance;
    }

    static double RandomNumber() {
        return Get().gen_random();
    }

    static std::vector<double> GenRandElements(size_t&& n) {
        return std::vector<double>(n, RandomNumber());
    } 
private:
    Random() = default;
    double gen_random() noexcept
    {
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<double> dis(-1.0, 1.0);
        return dis(gen);
    }
    std::random_device rd;
};

int main() {
    std::cout<<Random::RandomNumber()<<std::endl;
    std::cout<<Random::RandomNumber()<<std::endl;
    std::cout<<Random::RandomNumber()<<std::endl;
    std::cout<<Random::RandomNumber()<<std::endl;
    std::cout<<Random::RandomNumber()<<std::endl;

    for(auto& rand_elem : Random::GenRandElements(5))
        std::cout<<rand_elem<<", ";
    std::cout<<std::endl;
    return 0;
}