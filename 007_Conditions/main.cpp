// 7_Conditional_Statements.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Log.h"

int main()
{
    int x = 5;
    bool ComparisonResult = (x == 6); // false
    if (ComparisonResult) [[likely]] // Checking if comparison Result is anything but zero. If it is then the branch inside the if statement is executed
    {
        Log("x is 5");
    }
    std::cout << "Hello world" << std::endl;

    //Checking for null_pointer
    const char* ptr = nullptr;
    // const char* ptr = "Hello";
    if (ptr)
        Log("Pointer isn't null");
    else if (ptr == "Hello") // Only going to check this condition if the above statement fails
        Log("Pointer is Hello");
    else
        Log("Pointer is null");
}
/*
- The "==" is a function that compares values of the memory locations of the given integers. Then returns a bool value i.e. true or false.
- For example (5 == 6)
    - First we get the memory of the 2 integers (i.e. memory of integer 5 and 6)
    - Hence we compare each integer (5 and 6) bit by bit with the other integer. If they are equal we return true.
- The if statement syntax is 
    if (bool value){
        branch;        -> This line is only ever executed if the statement in "if condition" is true
    }

- If the compiler optimizes this code we know that x and 6 are constants, hence the if statement can be executed in compile time. Hence the code would look something like this after 
  optimization (for if statement is false)
  Unoptimized Code :
    int main()
    {
    int x = 5;
    bool ComparisonResult = x == 6;
    if (ComparisonResult) // Checking if comparison Result is anything but zero. If it is then the branch inside the if statement is executed
    {
        Log("x is 5");
    }
    std::cout << "Hello world" << std::endl;
    }

  Optimized Code:
    int main()
    {
    std::cout << "Hello world" << std::endl;
    }

- Else if statement actual syntax
    Our syntax:
        else if (ptr == "Hello") // Only going to check this condition if the above statement fails
            Log("Pointer is Hello");
    
    Another syntax:
        else
        {
            if (ptr == "Hello")
                Log("Pointer is Hello");
        }

- In assembly 

    int x = 5;
00007FF70EA71D6B  mov         dword ptr [x],5                   -> Moves 5 into a register
    bool ComparisonResult = x == 5;
00007FF70EA71D72  cmp         dword ptr [x],5                   -> Compares the register bit by bit with another value
00007FF70EA71D76  jne         main+34h (07FF70EA71D84h)         -> jne -> jump not equal -> jump to 07FF70EA71D84 if not equal i.e. if comparison fails (above line)
00007FF70EA71D78  mov         dword ptr [rbp+0F4h],1            -> Gives the register value as 1 -> True
00007FF70EA71D82  jmp         main+3Eh (07FF70EA71D8Eh)         -> jmp -> jump to 07FF70EA71D8E
00007FF70EA71D84  mov         dword ptr [rbp+0F4h],0            -> Gives the register value as 0 -> False
00007FF70EA71D8E  movzx       eax,byte ptr [rbp+0F4h]
00007FF70EA71D95  mov         byte ptr [ComparisonResult],al
    if (ComparisonResult)
00007FF70EA71D98  movzx       eax,byte ptr [ComparisonResult]   -> Loading some values into the eax register
00007FF70EA71D9C  test        eax,eax                           -> Testing if eax passes our conditions. Hence if comparisonResult is false then this test is going to suceed.
00007FF70EA71D9E  je          main+5Ch (07FF70EA71DACh)         -> je -> jump equal -> jumps to 07FF70EA71DAC if the above conditions is satisfied i.e. if test suceeds
    {
        Log("x is 5");                                          -> if je fails -> We just move into the if statement branch and execute the function i.e. if condition is true
00007FF70EA71DA0  lea         rcx,[string "x is 5" (07FF70EA7ABB0h)]
00007FF70EA71DA7  call        Log (07FF70EA71357h)              -> Calls out function
    }
}
00007FF7F0C71DAC  xor         eax,eax
00007FF7F0C71DAE  lea         rsp,[rbp+108h]
00007FF7F0C71DB5  pop         rdi
00007FF7F0C71DB6  pop         rbp
00007FF7F0C71DB7  ret

*/