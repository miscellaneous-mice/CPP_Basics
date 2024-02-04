#include <iostream>

// A normal function of void return type
// No input paramterets
void Func1(void) {
	std::cout<<"Hello, this is Func1!\n"<<std::endl;
}

// A normal function with an int parameter 
// and void return type 
void Func2(int a)
{
	std::cout << "Hello, this is Func2!, Value of A is: " << a << std::endl;
}

// A normal function of int return type
// has 3 int input parameters
int Func3(int a, int b, int c)
{
	return a + b + c;
}

int main() {
	// Declare a function pointer
	void (*fun_ptr_1)(void);

	// Assign the address of myFunction to the pointer
	fun_ptr_1 = &Func1;

	// Call the function through the pointer
	fun_ptr_1();


	// Declare a function pointer
	void (*fun_ptr_2)(int);
	
	// Assign the address of myFunction to the pointer
	fun_ptr_2 = Func2;  // & removed 

	// Call the function through the pointer
	fun_ptr_2(10);  // * removed 


	// Declare a function pointer
	int (*fun_ptr_3)(int, int, int);

	// Assign the address of myFunction to the pointer
	fun_ptr_3 = Func3;

	std::cout << "Hello, this is Func3!, Sum is: " << fun_ptr_3(10, 20, 30) << std::endl;

	return 0;
}