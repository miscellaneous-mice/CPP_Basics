#include <iostream>
#include <typeindex>
#include <map>
#include <string>
#include <any>
#include <tuple>
#include "custom_types.h"

template<typename T>
std::shared_ptr<T> castHandler(const std::any& handler) {
    return std::dynamic_pointer_cast<T>(std::any_cast<std::shared_ptr<Base>>(handler));
}

#define cast(c, T) (castHandler<T>(c))

std::map<std::type_index, std::tuple<std::shared_ptr<Base>, std::type_index> (*)(const std::any&)> entities = {
    {std::type_index(typeid(std::shared_ptr<A>)), [](const std::any& a) -> std::tuple<std::shared_ptr<Base>, std::type_index> {
        return std::make_tuple(cast(a, A), std::type_index(typeid(A))); }
    },
    {std::type_index(typeid(std::shared_ptr<B>)), [](const std::any& b) -> std::tuple<std::shared_ptr<Base>, std::type_index> {
        return std::make_tuple(cast(b, B), std::type_index(typeid(B))); }
    },
    {std::type_index(typeid(std::shared_ptr<Base>)), [](const std::any& base) -> std::tuple<std::shared_ptr<Base>, std::type_index> {
        return std::make_tuple(cast(base, Base), std::type_index(typeid(Base))); }
    }
};

int main() {
    std::shared_ptr<Base> a = std::make_shared<A>();
    std::shared_ptr<Base> b = std::make_shared<B>();
    std::shared_ptr<Base> base = std::make_shared<Base>();

    std::get<0>(entities[std::type_index(typeid(std::shared_ptr<A>))](a))->info();
    std::get<0>(entities[std::type_index(typeid(std::shared_ptr<B>))](b))->info();
    std::get<0>(entities[std::type_index(typeid(std::shared_ptr<Base>))](base))->info();
    return 0;
}