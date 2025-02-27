#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <ranges>

int main()
{
    using namespace std::complex_literals;
    std::cout << std::fixed << std::setprecision(2); // Sets the decimal precision for console output
 
    std::complex<int> z1 = 1i * 1i; // imaginary unit squared
    std::cout << "i * i = " << z1 << '\n';
 
    std::complex<long long> z2 = std::pow(1i, 2); // imaginary unit squared
    std::cout << "pow(i, 2) = " << z2 << '\n';
 
    const double PI = std::acos(-1); // or std::numbers::pi in C++20
    std::complex<double> z3 = std::exp(1i * PI); // Euler's formula
    std::cout << "exp(i * pi) = " << z3 << '\n';
 
    std::complex<double> z4 = 1.0 + 2i, z5 = 1.0 - 2i; // conjugates
    std::cout << "(1 + 2i) * (1 - 2i) = " << z4 * z5 << '\n';
 
    const auto zz = {0.0 + 1i, 2.0 + 3i, 4.0 + 5i};

    for (double re : zz | std::views::transform([](auto z){ return z.real(); }))
        std::cout << re << ' ';
    std::cout << '\n';
    for (double im : zz | std::views::transform([](auto z){ return z.imag(); }))
        std::cout << im << ' ';
    std::cout << '\n';
}

/*
To denote 1.0 + 2i
- Include the namespace std::complex_literals to use scientific notations like 2i, -4i, etc.
- Using #include<iomanip> to denot the complex number as sum of 1.0 + 2i.
*/
