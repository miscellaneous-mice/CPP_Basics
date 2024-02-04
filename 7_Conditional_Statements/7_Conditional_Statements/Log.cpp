#include "Another_Way.h"

#if Unsual
#include<iostream>
#endif

#if Standard
#include "Log.h"
#endif

void Log(const char* message) {
	std::cout << message << std::endl;
}
/*
You necessarily don't need to #include "Log.h". But it's more convinient to store all the standard libraries (like iostream) used by Log.cpp inside Log.h

Another Way to write header files is include all the standard libraries in "Log.cpp" used by the function definition and just have function declaration in "Log.h" which isn't standard
way of writing code.
*/