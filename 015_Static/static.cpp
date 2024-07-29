/*
Case 1) No Error as s_Variable is privately (statically) defined in static.cpp and globally defined in main.cpp
in static.cpp : static int s_Variable = 5
in main.cpp : int s_Variable = 10

Case 2) Error as s_Variable is globally defined in static.cpp and globally defined in main.cpp
in static.cpp : int s_Variable = 5
in main.cpp : int s_Variable = 10

Case 3) No Error as s_Variable is globally defined in static.cpp and defined as externally linked variable in main.cpp
in static.cpp : int s_Variable = 5
in main.cpp : extern int s_Variable

Case 4) Error as s_Variable is privately (statically) and defined as externally linked variable in main.cpp
in static.cpp : static int s_Variable = 5
in main.cpp : extern int s_Variable = 10
*/
#include <iostream>
#include "config.h"

#if use_static
static int s_Variable = 5;
static void Log(const char* message){
    std::cout<<message<<std::endl;
}
#endif

#if !use_static
int s_Variable = 5;
void Log(const char* message){
    std::cout<<message<<std::endl;
}
#endif