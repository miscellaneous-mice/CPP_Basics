// C++ program to illustrate the use of
// std::forward() function
#include <iostream>
#include <utility>
using namespace std;

// Function that takes lvalue reference
void UtiltyFun(int& i) {
    cout << "Process lvalue: " << i << endl;
}

// Overload of above function but it takes rvalue
void UtiltyFun(int&& i) {
    cout << "Process rvlaue: " << i << endl;
}

// Template function for forwarding arguments
// to utlityFun() 
template <typename T>
void Fun(T&& arg) { // T&& is called as universal reference which means it can hold both type (lvalue and rvalue)
    UtiltyFun(std::forward<T>(arg));
    // UtiltyFun(arg);
}

int main() {
    int x = 10;
  	
  	// Passing lvalue
    Fun(x);
  
  	// Passing rvalue
    Fun(std::move(x)); 
}

/*
Here the function preserves the argument type from a function and then forwards the same argument type as rvalue/lvalue
*/