#include "handler.h"

template std::shared_ptr<A> castHandler<A>(std::shared_ptr<Base>);
template std::shared_ptr<B> castHandler<B>(std::shared_ptr<Base>);
template std::shared_ptr<Base> castHandler<Base>(std::shared_ptr<Base>);

template <typename T>
std::shared_ptr<T> castHandler(std::shared_ptr<Base> handler) {
    return std::dynamic_pointer_cast<T>(handler);
}

void Accessor::GetInfo(std::unique_ptr<Base> handler){
    if (auto a = castHandler<A>(std::move(handler))) {
        a->info();
    } else if (auto b = castHandler<B>(std::move(handler))){
        b->info();
    } else if (auto base = castHandler<Base>(std::move(handler))){
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

void Accessor::addElement(std::unique_ptr<Base> handler){
    std::shared_ptr<Base> shared_handler  = std::shared_ptr<Base>(std::move(handler));
    if (auto a = castHandler<A>(shared_handler)) {
        this->add_element(cls_a, std::move(a));
        std::cout<<"Added A"<<std::endl;
    } else if (auto b = castHandler<B>(shared_handler)){
        this->add_element(cls_b, std::move(b));
        std::cout<<"Added B"<<std::endl;
    } else if (auto base = castHandler<Base>(shared_handler)){
        this->add_element(cls_base, std::move(base));
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