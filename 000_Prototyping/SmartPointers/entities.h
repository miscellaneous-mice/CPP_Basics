#pragma once

#include <iostream>
#include <typeinfo>
#include <map>
#include <any>
#include <string>

#define cls_base "base"
#define cls_a "a"
#define cls_b "b"

class HashMap{
protected:
    HashMap() = default;
    std::map<std::string, std::any> handlers;

    template<typename T>
    bool add_element(const std::string& key, std::shared_ptr<T> value);

    template<typename T>
    std::shared_ptr<T> get_element(const std::string& key);

    bool remove_element(const std::string& key);

    ~HashMap() = default;
};

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
