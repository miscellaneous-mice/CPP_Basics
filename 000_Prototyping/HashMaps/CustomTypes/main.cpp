#include <any>
#include <map>
#include <string>
#include <iostream>
#include "custom_types.h"
#include <csignal>

void signalHandler(int signal) {
    if (signal == SIGSEGV) {
        std::cerr << "Caught SIGSEGV: Invalid memory access (segmentation fault)" << std::endl;
    } else if (signal == SIGBUS) {
        std::cerr << "Caught SIGBUS: Bus error (invalid address alignment)" << std::endl;
    }
    // Exit the program or perform cleanup
    exit(signal);
}

class HashMap {
public:
    HashMap(){
        std::signal(SIGSEGV, signalHandler);
        std::signal(SIGBUS, signalHandler);
    }
    std::map<std::string, std::any> Map;

    template<typename T>
    void add_element(const std::string& key, T value) {
        this->Map[key] = value;  // Store value as std::any
    }

    template<typename T>
    T* get_element(const std::string& key) {
        try {
            return std::any_cast<T*>(this->Map[key]);  // Retrieve the value and cast it
        } catch (const std::bad_any_cast& e) {
            std::cerr << "Bad cast: " << e.what() << std::endl;
            return nullptr;
        }
    }
    
    void print_info() {
        for (const auto& pair : this->Map) {
            const std::type_info& type = pair.second.type();
            if (type == typeid(A*)){
                this->get_element<A>(pair.first)->info();
            }
            else if (type == typeid(B*)){
                this->get_element<B>(pair.first)->info();
            }
            else if (type == typeid(Derived*)){
                this->get_element<Derived>(pair.first)->info();
            }
            else {
                std::cout << "Unknown type" << std::endl;
            }
        }
    }

    ~HashMap(){
        for (const auto& pair : this->Map) {
            const std::type_info& type = pair.second.type();
            if (type == typeid(A*)){
                A* element = this->get_element<A>(pair.first);
                delete element;
                element = nullptr;
            }
            else if (type == typeid(B*)){
                B* element = this->get_element<B>(pair.first);
                delete element;
                element = nullptr;
            }
            else if (type == typeid(Derived*)){
                Derived* element = this->get_element<Derived>(pair.first);
                delete element;
                element = nullptr;
            }
            else if (type == typeid(Base*)){
                Base* element = this->get_element<Base>(pair.first);
                delete element;
                element = nullptr;
            }
        }
    }
};

class VirtualHashMap {
public:
    std::map<std::string, std::any> Map;

    template<typename T>
    void add_element(const std::string& key, T value) {
        this->Map[key] = value;  // Store value as std::any
    }

    template<typename T>
    T* get_element(const std::string& key) {
        try {
            return dynamic_cast<T*>(std::any_cast<Base*>(this->Map[key]));  // Retrieve the value and cast it
        } catch (const std::bad_any_cast& e) {
            std::cerr << "Bad cast: " << e.what() << std::endl;
            throw e;
        }
    }
    
    void print_info() {
        for (const auto& pair : this->Map) {
            if (const auto& entity = get_element<A>(pair.first)) {
                entity->info();
            }
            else if (const auto& entity = get_element<B>(pair.first)) {
                entity->info();
            }
            else if (const auto& entity = get_element<Derived>(pair.first)) {
                entity->info();
            }
            else {
                std::cout << "Unknown type" << std::endl;
            }
        }
    }

    ~VirtualHashMap(){
        for (const auto& pair : this->Map) {
            if (const auto& entity = get_element<A>(pair.first)) {
                delete entity;
                // entity = nullptr;
            }
            else if (const auto& entity = get_element<B>(pair.first)) {
                delete entity;
                // entity = nullptr;
            }
            else if (const auto& entity = get_element<Derived>(pair.first)) {
                delete entity;
                // entity = nullptr;
            }
            else if (const auto& entity = get_element<Base>(pair.first)){
                delete entity;
                // entity = nullptr;
            }
        }
    }
};

int main() {
    VirtualHashMap* VirtMap = new VirtualHashMap();
    HashMap* Map = new HashMap();

    Base* base = new Base();
    A* a = new A("Not virtual");
    B* b = new B("Not virtual");
    Derived* derived = new Derived("Not virtual");

    Base* aV = new A("Virtual");
    Base* bV = new B("Virtual");
    Base* derivedV = new Derived("Virtual");

    // Adding different types of elements to the map
    VirtMap->add_element("A", aV);
    VirtMap->add_element("B", bV);
    VirtMap->add_element("Derived", derivedV);
    // VirtMap->add_element("Base", base);

    Map->add_element("A", a);
    Map->add_element("B", b);
    Map->add_element("Derived", derived);
    // Map->add_element("Base", base);
    // Retrieving and printing the elements
    try {
        VirtMap->get_element<A>("A")->info();
        VirtMap->get_element<B>("B")->info();
        VirtMap->get_element<Derived>("Derived")->info();
        // VirtMap->get_element<Base>("Base");

        Map->get_element<A>("A")->info();
        Map->get_element<B>("B")->info();
        Map->get_element<Derived>("Derived")->info();
        // Map->get_element<Base>("Base");
    } catch (const std::bad_any_cast& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    VirtMap->print_info();
    delete Map;
    delete VirtMap;
    return 0;
}
