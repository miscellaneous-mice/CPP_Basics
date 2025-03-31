#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
 
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
 
    // If an event occurs 4 times a minute on average, how
    // often is it that it occurs n times in one minute?
    std::poisson_distribution<> d(4);
 
    std::map<int, int> hist;
    for (int n = 0; n != 10000; ++n)
        ++hist[d(gen)];
 
    for (auto [x, y] : hist)
        std::cout << x << " " << std::string(y / 100, '*') << '\n';
}
