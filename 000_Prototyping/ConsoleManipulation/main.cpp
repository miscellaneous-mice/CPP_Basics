#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
#include <cmath>

int main () {
    long double PI = M_PI;
    std::cout << std::setprecision(5) << PI << '\n';
    std::cout << std::setprecision(9) << PI << '\n';
    std::cout << std::fixed;
    std::cout << std::setprecision(5) << PI << '\n';
    std::cout << std::setprecision(9) << PI << '\n';

    std::cout << std::setbase(16);
    std::cout << 110 << std::endl;

    // std::cout<<"\x1b[2J"; // Clear output screen

    std::cout << std::hex;
    std::cout << std::setiosflags (std::ios::showbase | std::ios::uppercase);
    std::cout << 100 << std::endl;

    // using fmtflags as class member constants:
    std::cout.setf (std::ios_base::hex , std::ios_base::basefield);
    std::cout.setf (std::ios_base::showbase);
    std::cout << 100 << '\n';
}
