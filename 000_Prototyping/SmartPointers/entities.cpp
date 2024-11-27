#include "entities.h"

template bool HashMap::add_element(const std::string&, std::shared_ptr<A>);
template bool HashMap::add_element(const std::string&, std::shared_ptr<B>);
template bool HashMap::add_element(const std::string&, std::shared_ptr<Base>);


template std::shared_ptr<A> HashMap::get_element<A>(const std::string&);
template std::shared_ptr<B> HashMap::get_element<B>(const std::string&);
template std::shared_ptr<Base> HashMap::get_element<Base>(const std::string&);

template<typename T>
bool HashMap::add_element(const std::string& key, std::shared_ptr<T> value) {
    if (handlers.find(key) != handlers.end()) {
        return false;  // Element with this key already exists
    }
    // Convert unique_ptr to shared_ptr and store it in std::any
    handlers[key] = value;
    return true;
}

template<typename T>
std::shared_ptr<T> HashMap::get_element(const std::string& key) {
    if (handlers.find(key) == handlers.end()) {
        std::cerr<<"The handler does not exist"<<std::endl;
        return nullptr;
    }
    try {
        // return dynamic_cast<T*>(std::any_cast<Base*>(this->handlers[key])); 
        return std::any_cast<std::shared_ptr<T>>(this->handlers[key]);
    } catch (const std::bad_any_cast& e) {
        // std::cerr << "Bad cast: " << e.what() << std::endl;
        return nullptr;
    }
}

bool HashMap::remove_element(const std::string& key){
    if (handlers.find(key) != handlers.end()) {
        this->handlers.erase(key);
        return true;
    }
    return false;
}

void Base::info(){
    std::cout<<"Base Class"<<std::endl;
}

void A::info() {
    std::cout<<"A Class"<<std::endl;
}

void B::info() {
    std::cout<<"B Class"<<std::endl;
}