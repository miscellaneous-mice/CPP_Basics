#include <iostream>
#include "Execution.h"

struct GameState {
    int level;
    double health;
    long score;
    bool game_completed;
	GameState(int level, double health, long score, bool game_completed) : level(level), health(health), score(score), game_completed(game_completed) {
		std::cout<<"Initialized Game Instance"<<std::endl;
	};
	~GameState() {
		std::cout<<"Deleted Game Instance"<<std::endl;
	}
};

void Print(GameState* gs) {
	if (!gs) {
		std::cout<<"gs pointer is nullified"<<std::endl;
		return;
	}
    std::cout<<"Current state of game is : " 
    << "Current level : " << gs->level 
    << ", Current health : " << gs->health
    << ", Current score : " << gs->score
    << ", Is game completed : " << gs->game_completed
    << std::endl;
}

void Delete(GameState* gs) {
	/*
	Issue in the function:
	- gs is passed by value, meaning a copy of the pointer is created.
	- delete gs; frees the memory, making the original pointer in main() a dangling pointer.
	- gs = nullptr; only updates the local copy inside Delete(), but does not affect the original pointer in main().

	Potential issues on multiple calls:
	- When Delete(gs); is called again, gs in main() is still pointing to the freed memory (dangling pointer)
	- So a double delete occurs, leading to a crash.
	*/
    if (gs != nullptr) {
        delete gs; // frees the memory in all the pointer instances, and  "zeroes out" values.
        gs = nullptr; // only affects the local copy of the pointer.
    } else {
        std::cout<<"Instance already deleted"<<std::endl;
    }
}

void DeleteInstance(GameState* gs) {
	/*
	Issue in the function:
	- `gs` is passed by value, meaning it is a local copy and does not affect the original pointer outside the function.
	- `GameState**)gs` attempts to cast `gs` (which is `GameState*`) into `GameState**`, which is incorrect and leads to undefined behavior.
	- `instance = *((GameState**)gs);`
	  - This dereferences a pointer that was never meant to be a `GameState**`, leading to an invalid memory access.
	  - If this does not crash immediately, `instance` holds a garbage pointer.
	- `delete gs;` incorrectly deletes `gs`, which was already misused in the cast, further causing potential corruption.
	- Setting `gs = nullptr;` only affects the local copy of `gs`, not the original pointer outside the function.

	Potential issues on multiple calls:
	- On the first call, the program might crash due to the invalid cast.
	- If it does not crash, `gs` is deleted incorrectly.
	- On the second call:
	  - If `gs` was set to `nullptr` externally, the function works correctly.
	  - If not, the function accesses a dangling pointer, leading to undefined behavior.
	*/
    GameState* instance = *((GameState**)gs);
    if (instance != nullptr) {
        delete gs;
        gs = nullptr;
    } else {
        std::cout<<"Instance already deleted"<<std::endl;
    }
}

void DeleteRef(GameState*& gs) {
	/*
	First Call :
	- gs is passed by reference, meaning a doesnt not create copy of the pointer.
	- delete gs; frees the memory, making the original pointer in main() a dangling pointer.
	- gs = nullptr; only updates the original pointer in main().

	Second Call
	- When Delete(gs); is called again, gs in main() is still pointing to the nullptr
	- Hence as the function handles the nullptr check, therefore no crash occurs
	*/
    if (gs != nullptr) {
        delete gs; // frees the memory in all the pointer instances, and  "zeroes out" values.
        gs = nullptr; // only affects the global instance of the pointer.
    } else {
        std::cout<<"Instance already deleted"<<std::endl;
    }
}

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

	Log("\nPointers are just ints");
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr); // Same as (uint64_t)ptr
    std::cout << "Pointer Address (stored in uintptr_t): " << addr << std::endl;
    std::cout << "Pointer Address (directly from pointer): " << ptr << std::endl;

	std::cout<<"\nPointer references"<<std::endl;
	std::cout<<"------------------------------"<<std::endl;
	GameState* gs = new GameState(66, 95.7, 900L, false);
    Print(gs);

	std::cout<<"Delete by passing pointer as value"<<std::endl;
    Delete(gs); // Frees the memory of gs, but gs is not set to nullptr
    Print(gs);
	// Delete(gs); // Will throw error as gs is already delete but not set to nullptr

	std::cout<<"------------------------------"<<std::endl;
	gs = new GameState(54, 75.7, 4000L, false);
	Print(gs);
	std::cout<<"Delete by passing pointer as reference"<<std::endl;
    DeleteRef(gs);  // Frees the memory of gs, but gs is set to nullptr
	Print(gs);
	DeleteRef(gs); // As gs is set to nullptr. Hence, does not throw and error.

	std::cout<<"------------------------------"<<std::endl;
	gs = new GameState(84, 54.7, 10L, false);
	Print(gs);
	std::cout<<"Delete by casting via passing pointer as value"<<std::endl;
    DeleteInstance(gs); 
	Print(gs);
	DeleteInstance(gs);
	Print(gs);
	std::cout<<"------------------------------"<<std::endl;
}

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

Unlike uint64_t, which is always 64-bit, uintptr_t adapts to the architecture (e.g., 32-bit or 64-bit), i.e.
for 32 bit architecture -> uint32_t addr = (uint32_t)ptr
for 64 bit architecture -> uint64_t addr = (uint64_t)ptr
*/