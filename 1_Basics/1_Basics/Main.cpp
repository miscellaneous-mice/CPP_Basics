
void Log(const char* message); // Function Declaration

int main() // This is where C++ excecution starts
{
	Log("Hello world"); // Compiler just trusts us there is Log function.
}

/*
============================================================================
Configuration of settings in visual studio

1) Top Left of "Local windows Debugger" there is drop down menu for choosing the platform you are building
   application for.

2) Left to this platform choosing drop down menu there is mode we wanna run the program. Default set to 'Debug'.

3) Right click on the project (Inside solution explorer) click on settings to give instructions of how the
   application is to be executed.

============================================================================
*/

/*
============================================================================
Important notes of C++ code

1) Only cpp files(.cpp) get compiled. Not header files(.h). Header files get compiled after including on a cpp file

2) When compiling each cpp file an .obj file is produced. So linker stitches all the .obj files together into a
   single .exe file

3) Main function is a special case of a int function where you don't have to return a value. Cause it assumes you are default returning 0

============================================================================
*/