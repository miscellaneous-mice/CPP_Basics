#include <iostream>
#include <string>
#include <map>
#include <typeinfo>

struct Config {
    enum Level {
        noob = 1, intermediate, pro
    };
    int x;
    int y;
    Config() : x(0), y(0) {};
};

class A : virtual public Config {
private:
    Config::Level level;
    std::string name;  // Make name non-static
public:
    A(const std::string& name) : name(name), level(Config::noob) {};
    std::string getName() const { return name; }
    void setLevel(Config::Level lvl) { level = lvl; }
    virtual void Info();
};

class B : virtual public Config {
private:
    Config::Level level;
    std::string name;  // Make name non-static
public:
    B(const std::string& name) : name(name), level(Config::pro) {};
    std::string getName() const { return name; }
    void setLevel(Config::Level lvl) { level = lvl; }
    virtual void Info();
};

class Access : public A, public B {
private:
    std::string name;
    static std::map<std::string, void*> Entities;
public:
    Access(const std::string& name) : name(name), A(name), B(name) {}
    void Info() override;
    static void* AddEntity(void* entity, const std::type_info& type, Config::Level lvl, int x, int y);
    void Elements();
};

std::map<std::string, void*> Access::Entities;

void A::Info() {
    std::cout << "Entity A: " << name << " : Level " << level << std::endl;
}

void B::Info() {
    std::cout << "Entity B: " << name << " : Level " << level << std::endl;
}

void Access::Info() {
    std::cout << "Accessor: " << name << std::endl;
}

void* Access::AddEntity(void* entity, const std::type_info& type, Config::Level lvl, int val1, int val2) {
    if (type == typeid(A)) {
        A* aEntity = static_cast<A*>(entity);
        aEntity->x = val1;
        aEntity->y = val2;
        aEntity->setLevel(lvl);
        Entities[aEntity->getName()] = aEntity;
        return aEntity;
    } else if (type == typeid(B)) {
        B* bEntity = static_cast<B*>(entity);
        bEntity->x = val1;
        bEntity->y = val2;
        bEntity->setLevel(lvl);
        Entities[bEntity->getName()] = bEntity;
        return bEntity;
    }
    return nullptr;
}

void Access::Elements() {
    for (const auto& pair : Entities) {
        // if (typeid(*static_cast<A*>(pair.second)) == typeid(A)) {
        //     static_cast<A*>(pair.second)->Info();
        // } else if (typeid(*static_cast<B*>(pair.second)) == typeid(B)) {
        //     static_cast<B*>(pair.second)->Info();
        // }
        if (auto value = static_cast<A*>(pair.second)) {
            value->Info();
        } else if (auto value = static_cast<B*>(pair.second)) {
            value->Info();
        }
    }
}

int main() {
    Access* acc = new Access("Jose");
    A* a = new A("Polard");
    B* b = new B("Gale");

    A* aEntity = static_cast<A*>(acc->AddEntity(a, typeid(A), Config::noob, 5, 2));
    B* bEntity = static_cast<B*>(acc->AddEntity(b, typeid(B), Config::pro, 6, 1));

    acc->Elements();

    std::cout << "a->x: " << aEntity->x << ", a->y: " << aEntity->y << std::endl;
    std::cout << "b->x: " << bEntity->x << ", b->y: " << bEntity->y << std::endl;

    delete acc;
    delete a;
    delete b;

    return 0;
}
