#pragma once
#include <iostream>
#include <typeinfo>

struct Base {
    Base() = default;
    virtual void info();
    virtual ~Base() = default;
};

class A : virtual public Base {
public:
    A() = default;
    void info() override;
    ~A() = default;
};

class B : virtual public Base {
public:
    B() = default;
    void info() override;
    ~B() = default;
};
