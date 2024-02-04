#include <iostream>

void increment(int value){
	value++;
}

void increment_ptr(int* value) {
	// We first dereference the value (*value) then increment (++) the value after dereferencing.
	(*value)++;	// *value++ increments the memory address of value which is address of a.
}

void increment_ref(int& value) {
	value++;
}

int main() {
	// Intro----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	int a;

	// & is acutally part of the type, not a reference, not address of another variable, it's just part of type.
	int& ref = a; // Here only variable is just a, there are no 2 variables (a, ref) created here. We've just created an alias for a.

	ref = 5; // Assiging a = 2

	std::cout << a << std::endl;
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Advantage------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Pass by value
	increment(a);
	std::cout << a << std::endl; // a isn't affected by the function

	// Using pointer to pass the argument
	increment_ptr(&a);
	std::cout << a << std::endl; // a is affected, as we are changing the contents of memory address of a, by passing address of 'a' through a pointer just like (int* value = &a)

	// Using reference to pass the arguments
	increment_ref(a);
	std::cout << a << std::endl; // a is affected, as we are changing the contents of memory address of a, by passing 'a' through a reference just like (int& value = a)
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// DisAdvantage---------------------------------------------------------------------------------------------------------------------------------------------------------------------
	int b = 2;
	int c = 3;
	
	//int& ref_d;  We can't do this because it's just a reference to a variable, it's not an actaul variable. Hence when reference is create it should be immediately assign to something.
	int& ref_d = a;
	ref_d = b; // Throws an error as it can be used to reference only one variable. A reference, can't act as alias for a as well as b. Alias is just an assumed variable.
	std::cout << a << std::endl; // We just endup with assigning value of b to a. Hence a is 2

	// Instead of using references we can use pointer's change what memory address pointer is pointing to.
	int* ptr = &a;
	*ptr = 8;
	ptr = &b;
	*ptr = 7;
	std::cout << a <<" " << b << std::endl;


}	
/*
-> References are pointers in disguise. Just that they are syntactically different

-> References by themselves aren't new variable, hence don't occupy any memory. They are just reference to a variable

-> Two types of passing a variable through a function
	-> Pass the address of variable through a pointer. The Below code is same as int* value = &a;

		increment_ptr(&a);

		void increment_ptr(int* value) {
			(*value)++;
		}
		
	-> Pass the variable through a reference. The Below code is same as int& value = a;

		increment_ref(a);

		void increment_ref(int& value) {
			value++;
		}
		


*/
