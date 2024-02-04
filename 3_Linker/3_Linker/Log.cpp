#include "Header.h"
#if Math_Log
#include <iostream>

void Logr(const char* message)  // Uncomment this compile Math.cpp (it works), try to build the entire project (Linking error)
//void Log(const char* message)   // Linker expects to find this function as its specified as such in Math.cpp
{
	std::cout << message << std::endl;
}

#endif

/*

Linker mainly finds 2 things for identifying this function when used in another file
1) Type of function (int, void, etc..)
2) Name of the function (Log, Logr)
3) Number of parameters, type of parameters specified

Hence when any of this doesn't match when using this function in another file, throws a linking error.
Eg:

In Log.cpp a function is specified as :
void Log(const char* message)

In Math.cpp if this Log function is specified in any of the following format. Throws a linking error:
int Log(const char* message)
void Log(int a, int b)
void Logr(const char * message)

*/
