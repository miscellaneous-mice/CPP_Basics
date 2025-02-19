#pragma once
#include <iostream>
#include <typeinfo>

struct AccessEntity;

struct Base {
private:
    std::string name;
    friend struct AccessEntity;
public:
    Base(std::string name) : name(name) {};
    virtual void info() = 0;
    virtual ~Base() = default;
};

class A : virtual public Base {
protected:
public:
    A(std::string name) : Base(name) {};
    void info() override;
    void funcA();
    ~A() = default;
};

class B : virtual public Base {
public:
    B(std::string name) : Base(name) {};
    void info() override;
    void funcB();
    ~B() = default;
};

class C : public A, public B {
public:
    C(std::string name) : A(name), B(name), Base(name) {};
    void info() override {};
};

struct AccessEntity {
private:
    AccessEntity() = default;
public:
    static std::string getName(std::shared_ptr<Base> entity) {return entity->name;}
};
