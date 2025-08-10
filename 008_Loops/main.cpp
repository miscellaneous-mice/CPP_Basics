#include "Log.h"

int main()
{
#if standard
	for (float i = 0; i < 0.5; i = i + 0.1) {
		Log("hello world");
	}

	Log("================================================");

	float i = 0;
	while (i < 0.5) {
		Log("Hello World");
		i += 0.1;
	}

	Log("================================================");

	i = 0;
	do {
		Log("Hello world");
		i += 0.1;
	} while (i < 0.5);
#endif

#if !standard
	float i = 0;
	bool condition = true;
	for ( ; condition ; ) {
		Log("hello world");
		i = i + 0.1;
		condition = (i < 0.5);
	}

	while (condition) {
		Log("Hello World");
		i += 0.1;
	}

	Log("================================================");

	i = 0;
	do {
		Log("Hello world");
		i += 0.1;
	} while (condition);
#endif
}
/*
While loop -> Loops based on the variable state (True or False) in the program.

For loop -> Loop used to search through an array in the program.

Do while loop -> Runs atleast one time as it checks the condition after the code execution in the loop.
*/