#include <iostream>
// #define NDEBUG
#include <cassert>
#include <complex>
#include <iomanip>
 
// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert((void(msg), exp))
 
int main()
{
    void("void helps to avoid 'unused value' warning"); // This is just used to initialize a void without any assignement
    bool val = (void("void helps to avoid 'unused value' warning"), 2 + 2 == 4);
    std::cout<<val<<std::endl;


    assert(2 + 2 == 4);
    std::cout << "Checkpoint #1\n";
 
    assert((void("void helps to avoid 'unused value' warning"), 2 * 2 == 4));
    std::cout << "Checkpoint #2\n";
 
    assert((010 + 010 == 16) && "Yet another way to add an assert message");
    std::cout << "Checkpoint #3\n";
 
    assertm((2 + 2) % 3 == 1, "Success");
    std::cout << "Checkpoint #4\n";
 
    // assertm(2 + 2 == 5, "Failed"); // assertion fails
    // std::cout << "Checkpoint #5\n";

    using namespace std::complex_literals;

    std::complex<double> c = 1.0 + 2i;
    assert((void("Comparing complex types"), c == std::complex<double>{1, 2})); 
    std::cout << "Execution continues past the last assert\n"; // No output
}

/*
    - void("void helps to avoid 'unused value' warning"); is just used to act as an message in the assert statement
    - It is declared as void(...) as any value inside void will get destroyed after the execution of the line
    - h = (a, b) will return the expression result of b.
*/