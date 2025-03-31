#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
 
int main()
{
    std::random_device rd{};
    std::mt19937 gen{rd()};
 
    // Values near the mean are the most likely. Standard deviation
    // affects the dispersion of generated values from the mean.
    std::uniform_real_distribution d{2.0, 10.0};
 
    // Draw a sample from the normal distribution and round it to an integer.
    auto random_int = [&d, &gen]{ return std::lround(d(gen)); };
 
    std::map<long, unsigned> histogram{};
    for (auto n{10000}; n; --n)
        ++histogram[random_int()];
 
    for (const auto [k, v] : histogram)
        std::cout << std::setw(2) << k << ' ' << std::string(v / 200, '*') << '\n';
}