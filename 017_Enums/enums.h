#pragma once

#include <iostream>

struct Data{
public:
    enum EnumType
    {
        Add=1, Sub, Mul, Div
    };
private:
    EnumType type;
    void perform_op(int operation, float& num);
public:
    float a;
    static int b;
    Data() : type(Add) {}
    void set_op(EnumType num);
    static void init_op(Data& d);
};