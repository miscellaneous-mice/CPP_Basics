#include "custom_types.h"

Base::Base() {
    std::cout<<"Base Constructor"<<std::endl;
}

Base::~Base(){
    std::cout << "Base Destructor"<<std::endl;
}


A::A(const std::string& virt_type){
    this->virt_type = virt_type;
    std::cout<<"A Constructor : "<<this->virt_type<<std::endl;
}
void A::info() {
    std::cout<<"A Class : "<<this->virt_type<<std::endl;
}
A::~A() {
    std::cout << "A Destructor : "<<this->virt_type<<std::endl;;
}

B::B(const std::string& virt_type){
    this->virt_type = virt_type;
    std::cout<<"B Constructor : "<<this->virt_type<<std::endl;
}
void B::info() {
    std::cout<<"B Class : "<<this->virt_type<<std::endl;
}
B::~B() {
    std::cout << "B Destructor : "<<this->virt_type<<std::endl;;
}

Derived::Derived(const std::string& virt_type) : A(virt_type), B(virt_type) {
    this->virt_type = virt_type;
    std::cout<<"Dervied  Constructor : "<<this->virt_type<<std::endl;
}
void Derived::info(){
    std::cout<<"Derived Class : "<<this->virt_type<<std::endl;
}
Derived::~Derived() {
    std::cout << "Derived Destructor : "<<this->virt_type<<std::endl;
}