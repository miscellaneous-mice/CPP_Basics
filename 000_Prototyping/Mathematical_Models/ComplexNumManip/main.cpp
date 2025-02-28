#include <iostream>
#include <complex>
#include <cmath>
#include <iomanip>
#include <tuple>
#include <ranges>

class Distance {
public:
    constexpr Distance(double&& value) : value(value) {}
    double getValue() const { return value; }

private:
    double value;
};

constexpr Distance operator"" s(long double seconds) {
    return Distance(seconds);
}

constexpr Distance operator"" m(long double meters) {
    return Distance(meters);
}

int main() {
    constexpr Distance d = 5.0s;  // implicit conversion from double to Distance
    std::cout<<d.getValue()<<std::endl;

    return 0;
}
