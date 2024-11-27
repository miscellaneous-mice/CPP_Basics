#include <iostream>
#include <functional>

// Function containing function pointer
// as parameter

enum class operations {
    ADD, SUBTRACT, MULTIPLY, DIVIDE
};

float calc(operations op, int a, int b) {
    switch(op){
        case operations::ADD:
            return a + b;
        case operations::SUBTRACT:
            return a - b;
        case operations::MULTIPLY:
            return a * b;
        case operations::DIVIDE:
            return a / b;
        default:
            return 0.0;
    }
}

void print(int a, int b, const std::function<float(int, int)>& funcptr) {
	std::cout << "The result is : " << funcptr(a, b) << std::endl;
}

// Driver Function
int main() {
    const int x = 15;
    const int y = 2;
    const unsigned char offset = 2;

    float (*perform_op)(operations, int, int) = &calc;

    std::function<float(int, int)> add = [offset, perform_op](int a, int b) -> float { return perform_op(operations::ADD, a, b) + offset; };
    std::function<float(int, int)> subtract = [offset, perform_op](int a, int b) -> float { return perform_op(operations::SUBTRACT, a, b) + offset; };
    std::function<float(int, int)> multiply = [offset, perform_op](int a, int b) -> float { return perform_op(operations::MULTIPLY, a, b) + offset; };
    std::function<float(int, int)> divide = [offset, perform_op](int a, int b) -> float { return perform_op(operations::DIVIDE, a, b) + offset; };
    print(x, y, add);
    print(x, y, subtract);
    print(x, y, multiply);
    print(x, y, divide);
    return 0;
}
