/*
-> .cpp files are just txt files. but compiler interprets this as .cpp files or whatever extension the file has (.c, .h)
-> Every .cpp files give an .obj file after execution of program
-> Files have no meaning to compiler
-> .obj files are translational units given by compiler after compiling an .cpp file
-> If any files are included in Main.cpp file then 2 files will have only one translational unit (.obj file) 
-> Individual files always have their individual translational unit
 */

#include <iostream>
#include <string>
#include <cstring>

void Log(const char* message);

int Multiply(int a, int b);

int main()
{
	int result = Multiply(10, 2);
	std::string s = std::to_string(result); // Takes a single integer variable or other data type and converts into the string (int -> string)
	char const* pchar = s.c_str(); // Converts a given string to an array of characters (string -> char const*)
	Log(pchar);
}
/*
 1) To get the obj file -> C/C++ -> preprocessor -> preprocess to a file -> 'No', Then build the .cpp file and see the .i file

 2) To get the assembly code -> C/C++ -> Output files -> Assembler output -> 'Assembly only-listing', Then build the .cpp file and see the .asm file

 3) To run build the file faster -> C/C++ -> Optimization (under debug configuration) -> Optimization -> 'Maximize speed'
  - But you will get error hence -> C/C++ -> Code generation (under debug configuration) -> Basic runtime checks -> 'default'
*/