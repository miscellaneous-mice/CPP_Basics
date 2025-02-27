#include <iostream>
#include <cstring>
int main()
{
   int var;
   int var1;

   int* ptr = &var;
   int* ptr1;

   int* heap = new int(5);

   memset(ptr, 0x01, 8);
   memset(heap, 0x01, 8);

   asm ("mov %0, %1;" : "=r" ( ptr1 ): "r" ( ptr ));

   asm ("mov %0, %1;" : "=r" ( var1 ): "r" ( *ptr1 ));

   std::cout<<"\n"<<ptr1<<std::endl;
   std::cout<<"\n"<<var<<std::endl;
   std::cout<<"\n"<<var1<<std::endl;
   //std::cout<<"\n"<<*ptr<<std::endl;
   std::cout<<"\n"<<heap<<std::endl;
   return 0;
}