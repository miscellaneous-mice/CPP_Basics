#include <iostream>
#include <tuple>

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type Print(std::tuple<Tp...>& t) {}

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type Print(std::tuple<Tp...>& t) {
    std::cout << std::get<I>(t) << ", ";
    Print<I + 1, Tp...>(t);
}

template <typename T>
void print (const T& arg) {
    std::cout<<arg<<std::endl;
}

template <typename T, typename... Types>
void print (const T& firstArg, const Types&... args) {
    std::cout << firstArg << ", ";
    print(args...);
    std::cout<<std::endl;
}

template<typename... Args>
[[nodiscard]] constexpr auto TotalSum(Args&&... args) {
    print(std::forward<Args>(args)...);
    using resulttype = std::common_type<std::decay_t<Args>...>::type;
    auto values = std::make_tuple(std::forward<Args>(args)...);
    resulttype result{};
    std::apply([&result](auto&&... args) {
        ((result += static_cast<resulttype>(args)), ...);
    }, values);
    return result;
}

template<typename... Tp>
[[nodiscard]] std::ostream& operator<<(std::ostream& stream, const std::tuple<Tp...>& args) {
    stream << "(";
    std::apply([&stream](const auto&... elems) {
        ((stream << elems << ", "), ...);
    }, args);
    stream << ")"; // Removes last ", " and closes the tuple with ")"
    return stream;
}

int main() {
    std::tuple args{1.54f, 3, 23L, 0.334};
    auto total_sum = std::apply([args](auto&&... values) {
        return TotalSum(std::forward<decltype(values)>(values)...);
    }, args);
    std::cout<<total_sum<<std::endl;

    typedef std::tuple<int, float, double> T;
    T t = std::make_tuple(2, 3.14159F, 2345.678);

    std::cout<<"\nUsing apply method"<<std::endl;
    std::apply([](auto&&... args) {
        ((std::cout << args << ", "), ...);
        std::cout<<std::endl;
    }, t);

    std::cout<<"\nUsing apply method for print function"<<std::endl;
    std::apply([](auto&&... args) {
        print(std::forward<decltype(args)>(args)...);
    }, t);

    std::cout<<"\nPrint function"<<std::endl;
    Print(t);

    std::cout<<"\nGeneralised Print function"<<std::endl;
    auto std_tuple = std::make_tuple(1.45f, 3.0, 33L, "Hola");
    std::cout << std_tuple << std::endl;
}