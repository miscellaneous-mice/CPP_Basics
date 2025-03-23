#include <iostream>
#include <tuple>
#include <type_traits>
#include <iomanip>

template <typename T>
void print (const T& arg) {
    std::cout<<arg<<std::endl;
}

template <typename T, typename... Types>
void print (const T& firstArg, const Types&... args) {
    std::cout << firstArg << ", ";
    print(args...);
}

template<typename... Tp>
[[nodiscard]] constexpr std::tuple<std::decay_t<Tp>...> RetFunc(Tp&&... elements) {
    print(std::forward<Tp>(elements)...);
    return std::make_tuple(std::forward<Tp>(elements * elements)...);
}

template<typename... Tp>
[[nodiscard]] constexpr auto RetFuncPair(Tp&&... elements) {
    using CommonType = typename std::common_type<std::decay_t<Tp>...>::type;
    return std::array<std::pair<CommonType, CommonType>, sizeof...(Tp)>{ 
        std::pair(static_cast<CommonType>(elements), static_cast<CommonType>(elements * elements))...
    };
}


int main() {
    auto&& [a, b, c, d, e] = RetFunc(1, 2.74f, 3.33, 4L, 50034);
    std::cout<<a<<", "<<b<<", "<<c<<", "<<d<<", "<<e<<std::endl;

    auto&& result = RetFuncPair(1, 2.74f, 3.33, 4L, 50034);
    for(auto& [a, b]: result){
        std::cout<<std::setprecision(10)<<"("<<a << ", "<<b<<")"<<", ";
    }
    return 0;
}