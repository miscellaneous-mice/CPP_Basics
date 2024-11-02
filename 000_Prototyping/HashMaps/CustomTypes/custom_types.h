#pragma once
#include <iostream>
#include <typeinfo>

struct Base {
    Base();
    std::string virt_type;
    virtual ~Base();
};

class A : virtual public Base {
public:
    A(const std::string& message);
    virtual void info();
    ~A();
};

class B : virtual public Base {
public:
    B(const std::string& message);
    virtual void info();
    ~B();
};

class Derived : public A, public B {
public:
    Derived(const std::string& message);
    void info() override;
    ~Derived();
};