/*
-   Static outside a class means that the Static function/variable is only going to be visible to that translation unit while compiling,
    i.e. only to that code and is only defined internally for that code. This ensures that static function declaration in a script does 
    not impact the function declaration in other script (Prevent duplication of function declaration in a translation unit)

-   Static method/variable in class means that there is going to be only one instance of a static function/variable across 
    all the instances of that class

-   It's good practice to use static if a variable is declared in global scope for a translational unit
*/

#include <iostream>
#include "config.h"

#if use_static
int s_Variable = 10;
void Log(const char* message){
    std::cout<<message<<std::endl;
}
#endif

#if !use_static
extern int s_Variable; 
extern void Log(const char* message);
#endif

int& Get_static() {
    /* static value are declared on the seperate part of the memory,
    hence these don't get destroyed after the function ends, i.e. returns the reference to this variable */
    static int val = 20;
    return val;
}

int& Get_value() {
    /* Non static values are not defined on the stack,
    hence when function execution ends, the val variable scope lifetime ends, i.e. returns the destroyed reference to this variable */
    int val = 20;
    return val;
}


int main(){
    std::string s = std::to_string(s_Variable);
    Log(s.c_str());

    Get_value() = 10;
    std::cout<<Get_value()<<std::endl;

    Get_static() = 30;
    std::cout<<Get_static()<<std::endl;

    int& ref = Get_static();
    ref = 40;
    std::cout<<Get_static()<<std::endl;
    return 0;
}