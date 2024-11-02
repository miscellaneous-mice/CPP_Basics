#pragma once
#include <iostream>
#include <typeinfo>

struct Base {
    Base();
    enum Levels{
        NOOB,
        INTERMEDIATE,
        PRO
    };
    std::string utils;
    template <typename T>
    static T* castHandler(void* handler);
    virtual ~Base();
};

class A : virtual public Base {
public:
    A();
    virtual void info();
    ~A();
};

class B : virtual public Base {
public:
    B();
    virtual void info();
    ~B();
};

class Derived : public A, public B {
public:
    Derived();
    void info() override;
    ~Derived();
};

void getInfo(void* entity);
