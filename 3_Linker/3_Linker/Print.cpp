#include "Header.h"
#if Arthematic_Print
#include <iostream>
#include "Print.h"

void InitPrint()
{
	Print("Initialized Print");
}


#if best_method
void Print(const char* message) // Fucntion definition
{
	std::cout << message << std::endl;
}
#endif

#if 0 // If you set this to 1 -> compiler error is thrown. (During compiling stage)
void Print(const char* message)  
{
	std::cout << message << std::endl;
}
#endif

#endif