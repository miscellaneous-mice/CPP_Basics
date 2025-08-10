#include <iostream>

#define getoffset(s, a) ((size_t)&(((s*)0)->a))
#define getvalue(ptr, st, val) (*(decltype(st::val)*)((uint8_t*)ptr + getoffset(st, val)))

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

int main() {
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

    std::cout<<"\nType Punning"<<std::endl;
    int a = 10; // 0a 00 00 00 -> 4 bytes
    double b = a; // 00 00 00 00 00 00 24 40 -> 8 bytes // Implicit conversion happens automatically : double b = (double)a
    std::cout<<"int : "<<a<<", double : "<<b<<std::endl;

	double c = *(double*)&a; // 0a 00 00 00 00 00 00 00 -> 8 bytes, copied the 4 bytes of the a and allocated to c which is 8 bytes
	std::cout<<"int : "<<a<<", double : "<<c<<std::endl;

	GameState gamestate = GameState(84, 54.7, 10L, false);
	void* ptr = (void*)&gamestate;
	std::cout<< "Level : " << *(int*)((char*)ptr + getoffset(GameState, level)) <<std::endl;
	std::cout<< "Health : " << *(double*)((char*)ptr + getoffset(GameState, health)) <<std::endl;
	std::cout<< "Score : " << *(long*)((char*)ptr + getoffset(GameState, score)) <<std::endl;
	std::cout<< "Is game Finished : " << *(bool*)((char*)ptr + getoffset(GameState, game_completed)) <<std::endl;

	std::cout<<"\nType punning using macros"<<std::endl;
	std::cout<<getvalue(ptr, GameState, level)<<std::endl;
	std::cout<<getvalue(ptr, GameState, health)<<std::endl;
	std::cout<<getvalue(ptr, GameState, score)<<std::endl;
	std::cout<<getvalue(ptr, GameState, game_completed)<<std::endl;
}

/*

Converting Hex to decimal using IEEE754 : 
-----------------------------------------------------------------
-----------------------------------------------------------------
Hexadecimal : 00 00 00 00 00 00 24 40 (little endian)

Convert to big endian Standard format : 40 24 00 00 00 00 00 00

Convert this Hexadecimal to binary format : 
40 = 01000000  
24 = 00100100  
00 = 00000000  
00 = 00000000  
00 = 00000000  
00 = 00000000  
00 = 00000000  
00 = 00000000  
Final Binary : 01000000 00100100 00000000 00000000 00000000 00000000 00000000 00000000
--------------------
Expression : 
For 64 bit value (8 bytes) : 
---------------------------------------------------------------------------------
| S | Exponent (11 bits) | Mantissa (52 bits)								    |
---------------------------------------------------------------------------------
| 0 | 10000000010 	     | 0100000000000000000000000000000000000000000000000000 |
---------------------------------------------------------------------------------
Sign Bit -> 0
--------------------
Exponent : 
10000000010
E = 1 × 2¹⁰ + 0 × 2⁹ + 0 × 2⁸ + 0 × 2⁷ + 0 × 2⁶ + 0 × 2⁵ + 0 × 2⁴ + 0 × 2³ + 0 × 2² + 1 × 2¹ + 0 × 2⁰  
E = 1024 + 2  
E = 1026

Bias : 1023 (Max value of Exponent : 2047 (2^11 - 1) -> -1023 to 1024)
--------------------
Mantissa : 
0100000000000000000000000000000000000000000000000000 -> mantissa bits
1.0100000000000000000000000000000000000000000000000000 -> In Binary

M = 1 + (0 * 1/2) + (1 * 1/4) + (0 * 1/8) + (0 * 1/16) + (0 * 1/32) .....) => 1.25
--------------------
Result : 
Value = (-1 ^ S) * M * (2 ^ (E - Bias))
Value = (-1 ^ 0) * 1.25 * (2 ^ (1026 - 1023))
Value = 1 * 1.25 * (2 ^ 3)
Value = 1.25 * 8 = 10

-----------------------------------------------------------------
-----------------------------------------------------------------
Hexadecimal : 01 00 24 0a (little endian)

Convert to big endian Standard format : 0a 24 00 01

Convert this Hexadecimal to binary format : 
0a = 00001010
24 = 00100100 
00 = 00000000  
01 = 00000001
Final Binary : 00001010 00100100 00000000 00000001
--------------------
Expression : 
For 32 bit value (8 bytes) : 
---------------------------------------------------------------------------------
| S | Exponent (8 bits)  | Mantissa (23 bits)								    |
---------------------------------------------------------------------------------
| 0 | 00010100 	         | 01001000000000000000001							    |
---------------------------------------------------------------------------------
Sign Bit -> 0
--------------------
Exponent : 
00010100
E = 0 × 2⁷ + 0 × 2⁶ + 0 × 2⁵ + 1 × 2⁴ + 0 × 2³ + 1 × 2² + 0 × 2¹ + 0 × 2⁰  
E = 16 + 4 = 20

Bias : 127 (Max value of Exponent : 255 (2^8 - 1) -> -127 to 128)
--------------------
Mantissa : 
01001000000000000000001 -> mantissa bits
1.01001000000000000000001 -> In Binary

M = 1 + (0 * 1/2) + (1 * 1/4) + (0 * 1/8) + (0 * 1/16) + (1 * 1/32) ..... + (1 * 1/(2^23))
M = 1 + 0.25 + 0.03125 + 0.00000012
M = 1.28125012
--------------------
Result : 
Value = (-1 ^ S) * M * (2 ^ (E - Bias))
Value = (-1 ^ 0) * 1.28125012 * (2 ^ (20 - 127))
Value = 1.28125012 * 6.16297582e-33
Value = 7.89631351e-33

-----------------------------------------------------------------
-----------------------------------------------------------------
*/