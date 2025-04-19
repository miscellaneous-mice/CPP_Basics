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
std::ostream& operator<<(std::ostream& stream, const std::tuple<Tp...>& args) {
    stream << "(";
    std::apply([&stream](const auto&... elems) {
        ((stream << elems << ", "), ...);
    }, args);
    stream << ")"; // Removes last ", " and closes the tuple with ")"
    return stream;
}

template<typename T, std::size_t N, std::size_t... I>
auto array_to_tuple_impl(const std::array<T, N>& arr, std::index_sequence<I...>) {
    return std::make_tuple(arr[I]...);
}

template<std::size_t N>
constexpr auto arange() {
    std::array<int, N> arr;
    for(size_t i = 0; i < N; i++)
        arr[i] = i;
    return array_to_tuple_impl(arr, std::make_index_sequence<N>{});
}

template<class F, class... Ts, std::size_t... Is>
void for_each_in_tuple(const std::tuple<Ts...> & tuple, F func, std::index_sequence<Is...>){
    using expander = int[];
    (void)expander {0, ((void)func(std::get<Is>(tuple)), 0)... }; // Same as (func(std::get<Is>(tuple)), ...);
}

template<class F, class... Ts>
void for_each_in_tuple(const std::tuple<Ts...> & tuple, F func){
    for_each_in_tuple(tuple, func, std::make_index_sequence<sizeof...(Ts)>());
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

    auto values = arange<10>();
    Print(values);

    std::cout<<"\nGeneralised Print function"<<std::endl;
    auto std_tuple = std::make_tuple(1.45f, 3.0, 33L, "Hola");
    std::cout << std_tuple << std::endl;

    std::cout<<"\nRange based tuple iterator"<<std::endl;
    auto some = std::make_tuple("I am good", 255, 2.1);
    for_each_in_tuple(some, [](const auto &x) { std::cout << x << std::endl; });
}