#include <iostream>

#include <iostream>

class Base {
public:
    Base() = default;
    virtual void info() {
        std::cout<<"Base class"<<std::endl;
    }
};

class A : virtual public Base {
public:
    A() = default;
    void info() override {
        std::cout<<"A class"<<std::endl;
    }
};


class B : virtual public Base {
public:
    B() = default;
    void info() override {
        std::cout<<"B class"<<std::endl;
    }
};

class Example {
public:
    Example() { std::cout<<"Created Example"<<std::endl; }
    Example(int num) {std::cout<<"Created Example with "<<num<<std::endl; }
    ~Example() { std::cout<<"Destroyed Example"<<std::endl; }
};

class Entity {
private:
    const char* m_Name = "Tommy";
    Example ex; // initial initialization
public:
    mutable int m_Debugcnt = 0; // This is made mutable so that this variable can be modified inside a const method
    Entity () {
        ex = Example(8); // Created a duplicate of Example class and discards the initial initialization.
    }
    Entity (int num) : ex(Example(num)) {}; // Creates only one instance of Example with constructor instead of created a duplicate.
    void getName() const {
        std::cout<<m_Name<<std::endl;
        m_Debugcnt++;
    }
};

class ScopedPtr {
private:
    Entity* e;
public:
    ScopedPtr(Entity* entity) : e(entity) {};
    ~ScopedPtr() { delete e; }
    Entity* operator->(){
        return e;
    }
};

int main() {
    std::cout<<"Member initializer lists"<<std::endl;
    const Entity e1;
    {
        Entity e2(4);
    }

    std::cout<<"\nMutable keyword"<<std::endl;
    e1.getName(); // Here as e is a const Entity, hence the method also should be defined a const

    int x = 0;
    auto f1 = [=]() {
        e1.m_Debugcnt++;
        std::cout<<e1.m_Debugcnt<<std::endl;
    };
    f1();
    std::cout<<e1.m_Debugcnt<<std::endl;

    auto f2 = [&]() {
        e1.m_Debugcnt++;
        std::cout<<e1.m_Debugcnt<<std::endl;
    };
    f2();
    std::cout<<e1.m_Debugcnt<<std::endl;

    auto f3 = [=]() mutable {
        x++; // To Increment x you have to use mutable lambdas when passing by value [=]
        std::cout<<x<<std::endl;
    };
    f3();
    std::cout<<x<<std::endl;

    auto f4 = [&]() mutable {
        x++; // To Increment x you have to use mutable lambdas when passing by value [=]
        std::cout<<x<<std::endl;
    };
    f4();
    std::cout<<x<<std::endl;

    std::cout<<"\nArrow operator"<<std::endl;
    Entity* e3 = new Entity();
    ScopedPtr s(e3);
    s->getName();

    std::cout<<"\nGetting common types"<<std::endl;
    A a;
    a.info();
    B b;
    b.info();
    using cls = typename std::common_type<A, Base>::type; // Same as using cls = typename std::common_type<B, Base>::type;
    cls C;
    C.info();
}