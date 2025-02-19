#include <iostream>
#include <functional>
#include <map>

enum class operations {
    ADD, SUBTRACT, MULTIPLY, DIVIDE
};

static std::map<operations, float (*)(int a, int b)> calc = {
    {operations::ADD, [](int a, int b) -> float { return a + b ; }},
    {operations::SUBTRACT, [](int a, int b) -> float { return a - b ; }},
    {operations::MULTIPLY, [](int a, int b) -> float { return a * b ; }},
    {operations::DIVIDE, [](int a, int b) -> float { return a / b ; }},
};

void print(int a, int b, const std::function<float(int, int)>& funcptr) {
	std::cout << "The result is : " << funcptr(a, b) << std::endl;
}

// Driver Function
int main() {
    const int x = 15;
    const int y = 2;
    const unsigned char offset = 2;

    std::function<float(int, int)> add = [offset](int a, int b) -> float { return calc[operations::ADD](a, b) + offset; };
    std::function<float(int, int)> subtract = [offset](int a, int b) -> float { return calc[operations::SUBTRACT](a, b) + offset; };
    std::function<float(int, int)> multiply = [offset](int a, int b) -> float { return calc[operations::MULTIPLY](a, b) + offset; };
    std::function<float(int, int)> divide = [offset](int a, int b) -> float { return calc[operations::DIVIDE](a, b) + offset; };
    print(x, y, add);
    print(x, y, subtract);
    print(x, y, multiply);
    print(x, y, divide);
    return 0;
}
