#include <iostream>
#include <typeindex>
#include <map>
#include <string>
#include <any>
#include <tuple>
#include "custom_types.h"

template<typename T>
std::shared_ptr<C> castHandler(const std::any& handler) {
    return std::dynamic_pointer_cast<C>(std::any_cast<std::shared_ptr<T>>(handler));
}

#define castHelper(H) (entities[std::type_index(typeid(H))](H))

#define castMap(H) (entities[std::type_index(H.type())](H))

std::map<std::type_index, std::tuple<std::shared_ptr<C>, std::type_index> (*)(const std::any&)> entities = {
    {std::type_index(typeid(std::shared_ptr<A>)), [](const std::any& a) -> std::tuple<std::shared_ptr<C>, std::type_index> {
        return std::make_tuple(castHandler<A>(a), std::type_index(typeid(A))); }
    },
    {std::type_index(typeid(std::shared_ptr<B>)), [](const std::any& b) -> std::tuple<std::shared_ptr<C>, std::type_index> {
        return std::make_tuple(castHandler<B>(b), std::type_index(typeid(B))); }
    }
};

void printName(const std::any& handler) {
    std::cout<<std::type_index(handler.type()).name()<<std::endl;
    auto cHandler = std::get<0>(castMap(handler));
    std::cout<<AccessEntity::getName(cHandler)<<std::endl;
}

void printName(const std::any& handler) {
    std::type_index handlerType(handler.type());
    if (entities.find(handlerType) == entities.end()) {
        std::cerr << "Type not found in entities map: " << handlerType.name() << std::endl;
        return;
    }
    auto cHandler = std::get<0>(entities[handlerType](handler));
    if (!cHandler) {
        std::cerr << "Failed to cast handler to type C" << std::endl;
        return;
    }
    std::cout << AccessEntity::getName(cHandler) << std::endl;
}

int main() {
    int random = 5;
    std::shared_ptr<A> a = std::make_shared<C>("Radha");
    std::shared_ptr<B> b = std::make_shared<C>("Gokul");

    std::cout<<typeid(a).name()<<std::endl;
    std::cout<<typeid(b).name()<<std::endl;

    printName(a);
    std::cout<<AccessEntity::getName(std::get<0>(castHelper(a)))<<std::endl;
    std::get<0>(castHelper(a))->funcA();
    printName(b);
    std::cout<<AccessEntity::getName(std::get<0>(castHelper(b)))<<std::endl;
    std::get<0>(castHelper(b))->funcB();
    return 0;
}