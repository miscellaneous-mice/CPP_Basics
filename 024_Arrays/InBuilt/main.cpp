#include <tuple>
#include <string>
#include <iostream>
#include <typeindex>
#include <any>
#include <map>
#include<ranges>
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

template<typename T, const std::size_t N>
struct array {
    T __no_fixed_name__[N];

    T* begin() { return __no_fixed_name__; }

    T* end() { return __no_fixed_name__ + N; }

    const T* begin() const { return __no_fixed_name__; }
    const T* end() const { return __no_fixed_name__ + N; }
};

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
    for (const auto& element : vec) {
        auto [value, type_id] = data[element.type()](element);
        std::cout <<"The type is : "<< type_id.name()<< " the value is : " << value << std::endl;
    }

    array<std::any, 6> manual_vec = {'a', 1, "chy", 2.05f, 5.000034, 5L};
    for (const auto& [value, type_id]: manual_vec | std::views::transform([=](auto val) -> std::tuple<std::string, std::type_index> { return data[val.type()](val); })) {
        std::cout <<"The type is : "<< type_id.name()<< " the value is : " << value << std::endl;        
    }
    return 0;
}