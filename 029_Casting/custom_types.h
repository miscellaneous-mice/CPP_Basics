#pragma once
#include <iostream>

class Base {
public:
    virtual void info();
};

class A : virtual public Base {
public:
    void info() override;
};

class B : virtual public Base {
public:
    void info() override;
};

class Derived : public A, public B {
public:
    void info() override;
};