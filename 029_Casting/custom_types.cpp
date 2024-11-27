#include "custom_types.h"

void Base::info() {
    std::cout<<"Base Class"<<std::endl;
}

void A::info() {
    std::cout<<"A Class"<<std::endl;
}

void B::info() {
    std::cout<<"B Class"<<std::endl;
}


void Derived::info(){
    std::cout<<"Derived Class"<<std::endl;
}
