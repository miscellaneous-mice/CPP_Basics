#include <iostream>
#include "Execution.h"

#if operations
int main()
{
	Log("Dereferecing and writing data to the pointer address");
	int var = 8;
	// void* ptr = &var; // Gives error when writing int data to the void pointer
	int* ptr = &var;

	// Dereferencing and read the value from the memory address of the ptr
	Log(*ptr);

	// Dereferencing and writing the value to the memory address of the ptr
	*ptr = 6;
	Log(var); // We've changed our var from 8 to 10



	Log("\nAllocating memory on the heap");
	// Allocating 8 bytes of memory in the heap, and returning address of beginning of block of memory.
	char* buffer = new char[8]; // new char[8] allocates 8 bytes of data in the heap. The starting address of this data is stored in char* buffer.

	// Takes in the address of beginning of the block of memory (buffer), takes in the value to be filled (1), how many bytes of memory should be filled from first memory block (8 bytes)
	memset(buffer, 1, 8);



	Log("\nDouble pointers");
	// d_ptr stores the memory address of the pointer buffer. We know d_ptr is 4 bytes as this is a 32-bit application. Also due to endianess of our machine, address is stored in reverse order
	char** d_ptr = &buffer;

	// As we allocated memory in the heap memory using the [] operation, we should also delete the data after we've done with it using [] operator
	delete[] buffer;
}
#endif

/*
Dereferencing
	-> You can read the data from the memory address std::cout<<*ptr<<std::endl;

	-> You can also write data to the memory address *ptr = data. 
		-> If it's a void pointer data cannot be written to the ptr address as computer doesn't know what type of data or how many bytes it should write to the memory.

		-> Hence to write data to pointer, we need to specify the type of pointer to be the type of data in that address int *ptr = value. Now compiler knows data in address is an
		   integer, hence it should write 4 bytes of data into the memory.
		   ------------------------------------------------------------------------------------------------------------------------------------------------------------------
		   int dummy; // We initialize this variable just to get the memory address
		   int* ptr = &dummy;  // We assign an address to the int type pointer

		   *ptr = 8; // 8 is an integer. Hence as we initialized ptr as int, compiler knows it should assign 4 bytes of data to write 8 which is int into the ptr address.
		   ------------------------------------------------------------------------------------------------------------------------------------------------------------------

Allocation of memory in the heap
	-> char* buffer = new char[8] -> Allocates the memory on the heap using the [] operator. All the code above allocates memory in the stack.

Double pointers
	-> As pointers themselves are variables, hence there the address stored for every pointer. Hence we can use another pointer to point to our pointer.
	-> The double pointers address size is equal to n-bit application of our PC. If we are running a 32-bit application then our address size is 4 bytes.
	-> Due to our endianess of the machine, the order in which a sequence of bytes is stored in computer memory is in reverse order (little endian -> LSB first)
	
*/