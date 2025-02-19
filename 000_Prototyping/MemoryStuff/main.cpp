// C++ program to demonstrate working of malloc()
#include <iostream>  
#include <stdlib.h>  
   
#include <iostream>

template<typename T>
struct Random {
    T a;
    T b;
    T c;
    T d[10];
};

int main()  
{  
    // variable declaration
    int var_len = 10;

    char *ptr;

    // allocating memory to the pointer variable using malloc()
    ptr = (char*) malloc(sizeof(char)*var_len);
    memset(ptr, 1, var_len);

    std::cout<<"The address of the heap element is : "<<ptr<<std::endl;
    for(int i = 0; i < var_len; i++){
        std::cout<<"The value of the heap element is : "<<ptr[i]<<std::endl;
    }
    var_len = 20;
    ptr = (char*) realloc(ptr, sizeof(char)*var_len);
    memset(ptr, 20, var_len);

    std::cout<<"The address of the heap element is : "<<ptr<<std::endl;
    for(int i = 0; i < var_len; i++){
        std::cout<<"The value of the heap element is : "<<ptr[i]<<std::endl;
    }
    free(ptr);  

    int* arr = new int[5];
    Random<int> r = {10, 20, 30, 50, 60, 70};
    std::cout<<r.a<<std::endl;
    std::cout<<r.b<<std::endl;
    std::cout<<r.c<<std::endl;
    for(int i=0; i<10; i++){
        std::cout<<r.d[i]<<std::endl;
    }
    return 0;  
}