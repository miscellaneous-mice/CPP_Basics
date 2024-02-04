
#include "Log.h"
#include <iostream>

#ifndef _LOG_H //We can see that none of the below function is working as it's already defined in Log.h
#define _LOG_H
// Resolves error of including Log.h multiple times in a single .cpp file
#define header true

void Log(const char* message);
void InitLog();

#endif

#if !header
void Log(const char* message); // Program tell compiler that Log functions exists somewhere
#endif

#if header
void Log(const char* message) {
	std::cout << message << std::endl;
}
#endif

void InitLog() {
	Log("Hi from Log.cpp");
}

