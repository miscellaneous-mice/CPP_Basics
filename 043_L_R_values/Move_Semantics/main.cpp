#include <iostream>
#include <string>

struct Helper;

class Entity {
private:
    std::string m_Name;
    int m_Age;
    friend struct Helper;
public:
    Entity() : m_Name("Default"), m_Age(0) {};
    Entity(const char* name) : m_Name(name), m_Age(0) {};
    explicit Entity(int age) : m_Name("Default"), m_Age(age) {};
    Entity(const char* name, int age) : m_Name("Default"), m_Age(age) {};
    Entity(const Entity& other) {
        this->m_Name = other.m_Name;
        this->m_Age = other.m_Age;
    }
    Entity(Entity&& other) {
        this->m_Name = other.m_Name;
        this->m_Age = other.m_Age;
        other.m_Name = "";
        other.m_Age = 0;
    }
    void info() const {
        std::cout<<"Name : "<<m_Name<<"\nAge : "<<m_Age<<std::endl<<std::endl;
    }
};

struct Helper {
private:
    Helper() = default;
public:
    static void setname(Entity&& e, const std::string& name) {
        e.m_Name = name;
    }
};

Entity value_Entity() {
    Entity e{};
    return e;
}

Entity& lvalue_Entity() {
    static Entity e{};
    return e;
}

Entity&& rvalue_getEntity() {
    static Entity e{};
    return std::move(e);
}

void Print_val(Entity e) {
    std::cout<<"[lvalue]"<<std::endl;
    e.info();
}

void Print(const Entity& e) {
    std::cout<<"[lvalueref]"<<std::endl;
    e.info();
}

void Print(Entity&& e) {
    std::cout<<"[rvalue]"<<std::endl;
    e.info();
}
    
int main() {
    std::cout<<"\nUsing classes for lvalues and rvalues"<<std::endl;
    std::cout<<"1 ---------- "<<std::endl;
    Entity e1;
    e1.info();

    std::cout<<"2 ---------- "<<std::endl;
    Entity e2{"John"};
    /*
    No move constructor is called because Print() is just binding a reference, not creating a new object.
    Print() accepts an Entity&& parameter, so e2 binds directly to e without requiring a move.
    Inside Print(), e is still e2, so after the function returns, e2 remains unchanged.
    */
    Print(std::move(e2));
    e2.info();


    Print_val((Entity&&)e2);
    e2.info();

    std::cout<<"3 ---------- "<<std::endl;
    Entity e3{Entity(10)};
    Print((Entity&&)e3);
    e3.info();
    Print_val(std::move(e3));
    e3.info();

    std::cout<<"4 ---------- "<<std::endl;
    Entity e4("Catherine", 23);
    Print(e4);
    e4.info();

    std::cout<<"5 ---------- "<<std::endl;
    Entity e5 = std::move(e3);
    // Entity e5 = (Entity&&)e3; // Same as above
    e3.info();
    e5.info();

    std::cout<<"6 ---------- "<<std::endl;
    Entity&& e6 = (Entity&&)e1;
    Entity& e7 = e6;
    // Entity& e7 = std::move(e6); // Not possible as e7 is lvalue and std::move(e6) is rvalue
    e1.info();
    e6.info();
    e7.info();

    std::cout<<"7 ---------- "<<std::endl;
    Print("Bill");
    Print_val(Entity(10));
    Helper::setname((Entity&&)e1, "Jose");
    e1.info();

    std::cout<<"8 ---------- "<<std::endl;
    rvalue_getEntity().info();
    Entity e8 = rvalue_getEntity();
    Print(e8);
    rvalue_getEntity().info();
}