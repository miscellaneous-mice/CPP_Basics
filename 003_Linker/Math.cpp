#include "Header.h"
#if Math_Log
#include <iostream>

void Log(const char* message);

static int Multiply(int a, int b) // Hence we specify static because it specifies we are just gonna use this function only for this file.
//int Multiply(int a, int b) // Even if we never call this function. Program does linking of this function as it could be used in another file.
{
	// Comment this Log("Multiply") hence when we build project we never called Log function hence no linking error. (Even when Logr is specified in Log.cpp)
	Log("Mutiply"); // Program trusts us that there is Log function somewhere (compiling stage) until we build project and Linker tries to find the specified function.
	return a * b;  // Remove ';' -> error C2143 : syntax error : missing ';' before '}' -> Happens during compiling stage
}

#if 1 // Here 0 -> fatal error LNK1120: 1 unresolved externals -> Happens during linking stage 
int main()
{
	int result = 0;
	// result = Multiply(5, 8); // if you comment this then Multiply is never called (Hence Log is never called) hence no error as this function is static
	std::cout << result << std::endl; 
	return 0;
}
#endif

#endif
/*
- There are 2 stages of execution of code 
   1) Compiling -> compile (ctrl+F7) : Here only compiling happens
   2) Linking -> Build project(F5) : Here only compiling and linking happens

- Now without main function (Entry point) you can compile not build (build -> Error, compile -> No error)
  Note : Entry point necessarily need not be a main function. It can be any function, but by default it is main function.

- You can specify if you need to define entry point in the program to execute.
  properties -> Linker -> Advanced -> Entry point

*/

/* 
How linker works:

1) In compiling stage program trusts us that a function exists in some file. (Function may or may not exist in another file) Eg: see Logr in Log.cpp

2) In linking stage Only when a function is called then linker does the linking. eg: see Log("Multiply")

3) But also, in linking stage the linker actually links the multiply function (Even if it is never called), because it may be used in another file (Mutliply 
   function), Hence when this happens when multiply function is linked all the elements inside the function is also in linking stage, hence when Log function 
   in Multiply function isn't specified anywhere. Throws a linking error. (Eg: see result = Multiply(5,8))

4) Hence, we use static because linker understands that this function is only gonna be used for this file. Hence when the function isn't called then there
   is no linking of that function, hence contents inside that function doesn't matter. But when function is called -> Throws linking error

*/