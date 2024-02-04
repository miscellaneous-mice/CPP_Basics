#include "Log.h"
#include <iostream>

int main() {
	for (int i = 0; i < 5; i++) {
		if (i % 2 != 0)
			continue;
		Log("Hello world");
		std::cout << i << std::endl;
	}
	
	Log("==================================");

	for (int i = 0; i < 5; i++) {
		if (i % 2 != 0)
			break;
		Log("Hello world");
		std::cout << i << std::endl;
	}

	Log("==================================");

	for (int i = 0; i < 5; i++) {
		if (i % 2 != 0)
			return 0;
		Log("Hello world");
		std::cout << i << std::endl;
	}
}

/*
See Debug
Continue :
	This is used to continue/jump to the next iteration of forloop without executing any code below inside the forloop

Break : 
	This is used to come out of a forloop

Return :
	When we return a value in the function, then the function execution is over. In our case if we return 0 -> Comes out of the main function.

*/