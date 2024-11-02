#include "utils.h"

Base::Base() {
    std::cout<<"Base Constructor"<<std::endl;
}
template <typename T>
T* Base::castHandler(void* handler){
    return dynamic_cast<T*>(static_cast<Base*>(handler));
}
Base::~Base(){
    std::cout << "Base Destructor"<<std::endl;
}


A::A(){
    std::cout<<"A Constructor"<<std::endl;
}
void A::info() {
    std::cout<<"A Class"<<std::endl;
}
A::~A() {
    std::cout << "A Destructor"<<std::endl;;
}

B::B(){
    std::cout<<"B Constructor"<<std::endl;
}
void B::info() {
    std::cout<<"B Class"<<std::endl;
}
B::~B() {
    std::cout << "B Destructor"<<std::endl;;
}

Derived::Derived() {
    std::cout<<"Dervied  Constructor"<<std::endl;
}
void Derived::info(){
    std::cout<<"Derived Class"<<std::endl;
}
Derived::~Derived() {
    std::cout << "Derived Destructor"<<std::endl;
}

void getInfo(void* entity) {
    if (auto aHandler = Base::castHandler<A>(entity)) {
        aHandler->info();
    } else if (auto bHandler = Base::castHandler<B>(entity)) {
        bHandler->info();
    } else {
        std::cout << "Unknown type" << std::endl;
    }
}