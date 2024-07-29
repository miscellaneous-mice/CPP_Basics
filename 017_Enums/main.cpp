#include "enums.h"

int main(){
    Data L;
    L.a = 1;
    Data::b = 5;
    L.set_op(Data::Div);
    Data::init_op(L);
    std::cout<<L.a<<std::endl;
    return 0;
}