#include <iostream>

void foo() { std::cout << "Foo!" << std::endl; }
void bar() { std::cout << "Bar!" << std::endl; }

void foo(int x) {
    std::cout << "foo called with " << x << std::endl;
}

void callFunctionptr(void (*func)()) {
    func();
}

void callFunction(std::string&& name, const std::function<void()>& func) {
    std::cout<<name<<std::endl;
    func();
}

class MyClass {
public:
    void memberFunc() {
            std::cout << "Hello from memberFunc!" << std::endl;
        }
    };
    
    void callMemberFunction(MyClass& obj, void (MyClass::*func)()) {
        (obj.*func)();  // Call member function on object
    }

int main() {
    std::cout<<"Passing function as reference v/s pointer"<<std::endl;
    callFunctionptr(&foo);  // Explicit — using & to pass the function pointer
    callFunctionptr(foo);    // Implicit — works the same, without &


    std::cout<<"\nUsing std::function pointer"<<std::endl;
    void (*func1)() = &foo;  // Store a function pointer
    void (*func2)(int) = &foo;  // Store a function pointer
    std::function<void()> func3 = static_cast<void(*)()>(&foo);  // Store a function pointer
    auto func4 = static_cast<void(*)(int)>(&foo); 
    func1();
    func2(54);
    func3();
    func4(35);

    std::cout<<"\nPassing function pointer as arguments"<<std::endl;
    callFunction("Raw function pointer", func1);
    callFunction("std function pointer", func3);

    std::cout<<"Passing class member functions as parameters"<<std::endl;
    MyClass myObj;
    callMemberFunction(myObj, &MyClass::memberFunc);  // Requires &

    std::cout<<"\nExecuting array for functions"<<std::endl;
    void (*funcArr[])() = { &foo, &bar };  // Array of function pointers
    for (auto func : funcArr) {
        func();
    }

    std::cout<<"\nLambdas"<<std::endl;
    auto lambda = [] () {std::cout << "Hello from lambda!" << std::endl; };
    auto* lambdaPtr = &lambda;  // Take the address of the lambda
    (*lambdaPtr)();  // Call it through the pointer

    auto lambda_fptr = [&func2, &func3] (auto&& x) {
        func2(x);
        func3();
    };
    auto* lambda_ptr = &lambda_fptr;  // Take the address of the lambda
    (*lambda_ptr)(75);  // Call it through the pointer

    std::cout<<"\nExecuting array for function pointers"<<std::endl;
    std::function<void()> funcArrPtr[] = { func1, func3 };  // Array of function pointers
    for (auto func : funcArrPtr) {
        func();
    }

    std::cout<<"\nExecuting array for function pointers with arguments"<<std::endl;
    std::function<void(int)> funcArrPtrArgs[] = {
        [&func2](int element){ func2(element); },
        [&func4](int element){ func4(element); },
    };  // Array of function pointers
    for (auto func : funcArrPtrArgs) {
        func(67);
    }
}