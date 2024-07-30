#include "enums.h"

int main(){
    Data L;
    L.a = 5;
    Data::b = 2;
    L.set_op(Data::Div);
    Data::init_op(L);
    std::cout<<L.a<<std::endl;
    L.set_op(Data::Add);
    Data::init_op(L);
    std::cout<<L.a<<std::endl;
    return 0;
}