#include "handler.h"

template A* castHandler<A>(Base*);
template B* castHandler<B>(Base*);
template Base* castHandler<Base>(Base*);

template <typename T>
T* castHandler(Base* handler){
    return dynamic_cast<T*>(handler);
}

void Accessor::GetInfo(Base* handler){
    if (auto a = castHandler<A>(handler)) {
        a->info();
    } else if (auto b = castHandler<B>(handler)){
        b->info();
    } else if (auto base = castHandler<Base>(handler)){
        base->info();
    }
}

void Accessor::GetMapInfo(std::string key){
    if (auto a = get_element<A>(key)) {
        a->info();
    } else if (auto b = get_element<B>(key)){
        b->info();
    } else if (auto base = get_element<Base>(key)){
        base->info();
    }
}

void Accessor::addElement(Base* handler){
    if (auto a = castHandler<A>(handler)) {
        this->add_element(cls_a, a);
        std::cout<<"Added A"<<std::endl;
    } else if (auto b = castHandler<B>(handler)){
        this->add_element(cls_b, b);
        std::cout<<"Added B"<<std::endl;
    } else if (auto base = castHandler<Base>(handler)){
        this->add_element(cls_base, base);
        std::cout<<"Added Base"<<std::endl;
    }
}

void Accessor::AllElements(){
    for (const auto& pair : this->handlers) {
        if (auto entity = get_element<A>(pair.first)) {
            entity->info();
        }
        else if (auto entity = get_element<B>(pair.first)) {
            entity->info();
        }
        else if (auto entity = get_element<Base>(pair.first)) {
            entity->info();
        }
    }
}