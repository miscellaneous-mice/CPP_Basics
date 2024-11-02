#include <iostream>
#include <map>
#include <string>
#include <any>

#define cls_base "base"
#define cls_a "a"
#define cls_b "b"

class Base {
public:
    Base() {
        std::cout << "Created Base" << std::endl;
    }
    virtual void getInfo() {
        std::cout << "Base" << std::endl;
    }
    virtual ~Base() {
        std::cout << "Deleted Base" << std::endl;
    }
};

class A : public Base {
public:
    A() {
        std::cout << "Created A" << std::endl;
    }
    void getInfo() override {
        std::cout << "A" << std::endl;
    }
    ~A() {
        std::cout << "Deleted A" << std::endl;
    }
};

class B : public Base {
public:
    B() {
        std::cout << "Created B" << std::endl;
    }
    void getInfo() override {
        std::cout << "B" << std::endl;
    }
    ~B() {
        std::cout << "Deleted B" << std::endl;
    }
};

class Map {
public:
    std::map<std::string, std::any> hashmap;
    
    template <typename T>
    void add_element(const std::string& key, T* value) {
        this->hashmap[key] = value;
    }
    
    template <typename T>
    T* get_element(const std::string& key) {
        try {
            return dynamic_cast<T*>(std::any_cast<Base*>(this->hashmap[key]));
        } catch (const std::bad_any_cast& e) {
            std::cerr << "Bad cast: " << e.what() << std::endl;
            return nullptr;
        } catch (const std::out_of_range& e) {
            std::cerr << "Key not found: " << e.what() << std::endl;
            return nullptr;
        }
    }
};

template <typename T>
T* castEntity(void* entity){
    return dynamic_cast<T*>(static_cast<Base*>(entity));
}

void entityInfo(void* entity) {
    if(auto a = castEntity<A>(entity)){
        a->getInfo();
    }
    else if(auto b = castEntity<B>(entity)){
        b->getInfo();
    }
}

int main() {
    Base* a = new A();
    Base* b = new B();
    Map* mp = new Map();
    
    mp->add_element(cls_a, a);
    mp->add_element(cls_b, b);
    mp->get_element<A>(cls_a)->getInfo();
    mp->get_element<B>(cls_b)->getInfo();
    
    // for (const auto& pair: mp->hashmap){
    //     entityInfo(pair.second);
    // }
    
    for (const auto& pair: mp->hashmap){
        if(const auto& a = mp->get_element<A>(pair.first)){
            // a->getInfo();
            entityInfo(a);
        }
        else if(const auto& b = mp->get_element<B>(pair.first)){
            // b->getInfo();
            entityInfo(b);
        }
    }

    delete a;
    delete b;
    delete mp;
    
    return 0;
}
