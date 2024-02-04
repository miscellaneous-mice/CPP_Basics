#include "Header.h"
#if Arthematic_Print
#include <iostream>
#include "Print.h"

//void Print(const char* message);

#if 0  // Here linking error is thrown, not Compiling error unlike in Print.cpp.
void Print(const char* message)
{
	std::cout << message << std::endl;
}
#endif

static int Product(int a, int b)
//int Product(int a, int b) 
{
	Print("Mutiply");
	return a * b; 
}

int main()
{
	int result = 0;
	result = Product(5, 8); 
	std::cout << result << std::endl;
	return 0;
}
#endif
