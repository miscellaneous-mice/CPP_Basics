#include <math.h>
#include <iostream>
#include <iomanip>
#include <variant>


void Print(const std::variant<long, double, float, int>& value) {
    std::visit([&](auto&& v) {
        std::cout << std::setprecision(14) << v <<std::endl;
    }, value);
}

int main() {
    float PI = 3.14159265358979323846f;
    
    Print(static_cast<int>(PI));
    Print(*reinterpret_cast<int*>(&PI));
    Print(*reinterpret_cast<float*>(&PI));

    
    // Print(reinterpret_cast<int*>(&PI));
    // Print(reinterpret_cast<float*>(&PI));
    
    return 0;
}