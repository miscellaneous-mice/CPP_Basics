#include "enums.h"

// Data::EnumType static const type;
int Data::b;

void Data::set_op(EnumType num){
    type = num;
}

void Data::perform_op(int operation, float& num){
    switch(operation) {
        case Add:
            std::cout<<"Performing Addition operation"<<std::endl;
            num += b;
            break;
        case Sub:
            std::cout<<"Performing Subtraction operation"<<std::endl;
            num -= b;
            break;
        case Mul:
            std::cout<<"Performing Multiplication operation"<<std::endl;
            num *= b;
            break;
        case Div:
            std::cout<<"Performing Division operation"<<std::endl;
            if (b == 0)
                std::cout<<"Can't divide by zero"<<std::endl;
            else
                num /= b;
            break;
        default:
            std::cout<<"Not a valid input"<<std::endl;
            break;   
    }
}

void Data::init_op(Data& d){
    int result = 0;
    d.perform_op(d.type, d.a);
}