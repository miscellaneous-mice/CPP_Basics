#include "log.cpp"

void Log(const char* message); // Function Declaration

int main() // This is where C++ excecution starts
{
	Log("Hello world"); // Compiler just trusts us there is Log function.
}


/*
============================================================================
Important notes of C++ code

1) Only cpp files(.cpp) get compiled. Not header files(.h). Header files get compiled after including on a cpp file

2) When compiling each cpp file an .obj file is produced. So linker stitches all the .obj files together into a
   single .exe file

3) Main function is a special case of a int function where you don't have to return a value. Cause it assumes you are default returning 0

============================================================================
*/