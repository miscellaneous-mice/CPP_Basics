#include <iostream>
#include <string>
#include <cassert>

// rvalue function
int Get_lvalue() {
    return 10;
}

// lvalue reference function
int& Get_rvalue() {
    static int val = 10;
    return val;
}

// lvalue function
void SetValue(int value) {
    std::cout<<"Set value to : "<<value<<std::endl;
}

// lvalue reference function
void Set_lvalue(int& value) {
    std::cout<<"Set lvalue to : "<<value<<std::endl;
}

// rvalue reference function
void Set_rvalue(int&& value) {
    std::cout<<"Set rvalue to : "<<value<<std::endl;
}

// lvalue/rvalue reference function
void SetValueRef(const int& value) {
    std::cout<<"Set value to : "<<value<<std::endl;
}

void Print(const std::string& value) {
    std::cout<<"[lvalue]"<<value<<std::endl;
}

void Print(std::string&& value) {
    std::cout<<"[rvalue]"<<value<<std::endl;
}

int main() {
    int a = 5; // Here we are assigning a lvalue (a) with rvalue (5)
    a = Get_lvalue(); // Here we assign a lvalue (a) with a function with returns rvalue (Get_lvalue() -> 5)
    // Get_lvalue() = a; // This is an issue as we are trying to assign a rvalue (Get_lvalue() -> 10) with lvalue (a)
    std::cout<<a<<std::endl;

    int temp = a; // This is a lvalue (a) set to an lvalue (temp)
    int& b = a; // This is a lvalue (a) to an lvalue reference (b)
    std::cout<<temp<<", "<<b<<std::endl;

    int value = Get_rvalue();  // Here we are assigning a lvalue (value) with rvalue (Get_rvalue() -> 10)
    Get_rvalue() = 15; // We are assigning a lvalue reference (Get_rvalue() -> val) with an rvalue (15)
    std::cout<<Get_rvalue()<<", "<<value<<std::endl;

    int& value_ref = Get_rvalue(); // Here we are assigning a lvalue reference (value_ref) with lvalue reference (Get_rvalue() -> val)
    Get_rvalue() = 20; // We are assigning a lvalue reference (Get_rvalue() -> val) with an rvalue (15). This will also affect all the lvalue references point (value) to this lvalue reference (Get_rvalue() -> val)
    std::cout<<Get_rvalue()<<", "<<value<<std::endl;

    "Hola mucho gusto"; // We can't leave rvalues in on itself, as there is no memory assigned to this variable
    void("Hola mucho gusto"); // Hence we can tell the compiler to discard the rvalue after this line execution as it's temporary
    assert((void("Not equal"), Get_rvalue() == value_ref)); // To evaluate 2 rvalues we use the comma operator inside the parenthesis to give the right element as result

    SetValue(10); // This is just assigning a rvalue (10) to an lvalue (value)
    SetValue(value); // This is just assigning a lvalue (value) to an lvalue (value)

    int& c = temp;
    // int& c = 10; // We can only take a lvalue reference of an lvalue
    Set_lvalue(value); // We can only take a lvalue reference of an lvalue
    // Set_lvalue(10); // We cannot take a lvalue reference of an rvalue as rvalues are temporary data

    int&& d = 10; // We can only take a rvalue reference of an rvalue
    // int&& d = value; // We cannot take a rvalue reference of an lvalue
    Set_rvalue(10); // We can only take a rvalue reference of an rvalue
    // Set_rvalue(value);  // We cannot take a rvalue reference of an lvalue

    const int& ref1 = 10; // This is basically just int temp = 10; const int& ref1 = temp;
    const int& ref2 = value; // This is just taking lvalue reference of an lvalue
    SetValueRef(value); // We can assign lvalue reference to an lvalue
    SetValueRef(10); // We can assign lvalue reference to an rvalue for const type&

    std::string str1 = "Howa"; // lvalue -> str1, rvalue -> "Howa"
    std::string str2 = "Overlay"; // lvalue -> str2, rvalue -> "Overlay"
    std::string result = str1 + str2; // lvalue -> result, rvalue -> str1 + str2

    Print(str1);
    Print(result);
    Print(str1 + str2);
}

/*
lvalues : These are actual variables with allocated memory
    - int a -> lvalue
    - int& b = a -> lvalue reference
rvalues : These are temporary variables without allocated memory (constants)
    - void("This is an rvalue string") -> rvalue
    - int&& b = 10; -> rvalue reference
Support for both lvalue and rvalue : These variables support both lvalue and rvalue assignment
    - const int& c
*/