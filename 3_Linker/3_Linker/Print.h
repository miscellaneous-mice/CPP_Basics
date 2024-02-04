#pragma once

#define Using_Header true // Delete #include "Print.h" in print.cpp and Arthematic.cpp for other examples
#define best_method !Using_Header

#if !best_method
static void Print(const char* message) // If you add static then when you include "Print.h" in Print.cpp and Arthematic.cpp then there are 2 different versions of this function in both files.
//void Print(const char* message) // Linker error
{
	std::cout << message << std::endl;
}
#endif

#if best_method
void Print(const char* message);  //Fucntion declaration
#endif
/*

If you put 
void Print(const char* message)

Instead of 
static void Print(const char* message)

Then when you call #include "Print.h" in Print.cpp and Arthematic.cpp
void Print(const char* message) // If you do
{
	std::cout << message << std::endl;
}
will be pasted in both Print.cpp and Arthematic.cpp hence linker error, as linker doesn't know which void Print to be used in Print("Multiply")

But if you add static then when you include "Print.h" in Print.cpp and Arthematic.cpp then there are 2 different versions of this functioon in both files.
Hence no error when calling Print("Multiply") as it knows only one version of void Print i.e. it's own version of #include "Print.h"
*/
