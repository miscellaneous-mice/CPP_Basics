#pragma once
#include "Another_Way.h"

#if Unsual
//#include<iostream>

void Log(const char* message);
#endif

#if Standard
#include<iostream>

void Log(const char* message);
#endif