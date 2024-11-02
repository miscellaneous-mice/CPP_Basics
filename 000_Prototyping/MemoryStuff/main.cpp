// C++ program to demonstrate working of malloc()
#include <iostream>  
#include <stdlib.h>  
   
int main()  
{  
    // variable declaration
    int var_len = 10;

    char *ptr;

    // allocating memory to the pointer variable using malloc()
    ptr = (char*) malloc(sizeof(int)*var_len);
    memset(ptr, 1, var_len);
    
    std::cout<<"The address of the heap element is : "<<ptr<<std::endl;
    std::cout<<"The value of the heap element is : "<<*ptr<<std::endl;
    free(ptr);  
    return 0;  
}