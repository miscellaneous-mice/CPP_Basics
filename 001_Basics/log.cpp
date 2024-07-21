// Preprocessor basically compiles the code before execution of main function
#include <iostream>

void Log(const char* message) // Function definition
//void Logr(const char* message) // Linker error
{
	// Below statement is same as std::cout.print(message).print("\n")
	std::cout << message << std::endl; // As we know operators such as "<<" is also a function and "Hello world" is the parameter
	// Hence "<<" pushes the string to the cout, hence prints to console
}

// Linker actually finds this right function to be included in Main.cpp
// Linker error : Means linker couldn't find this function anywhere to be included in Main.cpp. Comment Log and uncomment Logr.
// Without function definition in Log.cpp, there in linker error in Main.cpp due to incorrect function declaration.