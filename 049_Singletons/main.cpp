#include <random>
#include <iostream>
#include <cmath>
#include <iomanip>

class Random {
public:
    Random(const Random& other) = delete;
    static Random& Get() {
        static Random instance;
        return instance;
    }

    static double randnum() {
        return Get().gen_random();
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
    std::cout<<Random::randnum()<<std::endl;
    std::cout<<Random::randnum()<<std::endl;
    std::cout<<Random::randnum()<<std::endl;
    std::cout<<Random::randnum()<<std::endl;
    std::cout<<Random::randnum()<<std::endl;
    return 0;
}