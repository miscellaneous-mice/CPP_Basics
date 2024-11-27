#include <tuple>
#include <string>
#include <iostream>
#include <typeindex>
#include <any>
#include <map>
#include <sstream>

#define cast(c, T) (any_to_string<T>(c))

template<typename T>
std::string any_to_string(const std::any& a) {
    try {
        std::stringstream ss;
        ss << std::any_cast<T>(a);
        return ss.str();
    } catch (const std::bad_any_cast& e) {
        return "Bad cast: " + std::string(e.what());
    }
}

static std::map<std::type_index, std::tuple<std::string, std::type_index> (*)(const std::any& a)> data = {
    {std::type_index(typeid(int)), [](const std::any& a) -> std::tuple<std::string, std::type_index> { return std::make_tuple(cast(a, int), std::type_index(typeid(int))); }},
    {std::type_index(typeid(float)), [](const std::any& a) -> std::tuple<std::string, std::type_index> { return std::make_tuple(cast(a, float), std::type_index(typeid(float))); }},
    {std::type_index(typeid(char)), [](const std::any& a) -> std::tuple<std::string, std::type_index> { return std::make_tuple(cast(a, char), std::type_index(typeid(char))); }},
    {std::type_index(typeid(long)), [](const std::any& a) -> std::tuple<std::string, std::type_index> { return std::make_tuple(cast(a, long), std::type_index(typeid(long))); }},
    {std::type_index(typeid(double)), [](const std::any& a) -> std::tuple<std::string, std::type_index> { return std::make_tuple(cast(a, double), std::type_index(typeid(double))); }},
    {std::type_index(typeid(const char*)), [](const std::any& a) -> std::tuple<std::string, std::type_index> { return std::make_tuple(cast(a, const char*), std::type_index(typeid(const char*))); }}
};

int main() {
    std::array<std::any, 6> vec = {'a', 1, "chy", 2.05f, 5.000034, 5L};

    // // Output the results
    for (const auto& element : vec) {
        auto [value, type_id] = data[element.type()](element);
        std::cout <<"The type is : "<< type_id.name()<< " the value is : " << value << std::endl;
    }
    return 0;
}