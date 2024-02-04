#include <iostream>
#include "Execution.h"

#if types
int main()
{
	// Void pointer
	int var = 8; // This variable has a memory address which has data 8 stored in it.
	void* ptr = nullptr; // Has the memory address of 0 assigned to the ptr	
	ptr = &var; // We got the memory address of the var variable and store memory address in ptr.
	
	// Int pointer
	int* ptr2 = &var; // Has same value at the int pointer as it has in the void pointer
	*ptr2 = 2;

	// Double pointer
	double* ptr3 = (double*)&var; // Cast the memory address to a double. Has the same data as the in the address as void pointer
	*ptr3 = 3;

	char var_size = 1;
	// Number of Bytes written to the address location
	char* ptr4 = (char*)&var_size; // Has same value at the int pointer as it has in the void pointer
	*ptr4 = 1;  // Here 1 byte is written into address location &var

	long int* ptr5 = (long int*)&var_size; // Has same value at the int pointer as it has in the void pointer
	*ptr5 = 2; // Here 4 byte value is written into address location &var

	long long int* ptr6 = (long long int*)&var_size; // Has same value at the int pointer as it has in the void pointer
	*ptr6 = 3; // Here 8 byte value is written into address location &var

	Log("Hello");

}
#endif
/*
Pointer is an integer that stores memory address which is 1 byte of data (8-bit). It can also be 16-bit interger, 32-bit interger, 64-bit interger. (Interger is address)

If we assign a type to a pointer it is just saying what type of data is in that pointer's memory address
	-> void* ptr -> We do not care what type of data is stored in the ptr address. We just need ptr to hold an address
				 -> Hence void* ptr = address; is used to just store the address into the pointer ptr

To See the memory address in Visual studio
	-> Hover over the pointer ptr in Debug mode
	-> Copy the address
	-> TM -> Debug -> Windows -> Memory -> Paste the address in Address: Tab

*/