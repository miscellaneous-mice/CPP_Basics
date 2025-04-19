#include <iostream>

template<class T, std::size_t N, class Callable, std::size_t... I>
void iter_apply(Callable callable, const std::array<T, N>& arr, std::index_sequence<I...>) {
    using Expander = int[];
    std::cout<<"Range of elements : "<<sizeof...(I)<<std::endl;
    (void)Expander {0, ((void)callable(arr[I]), 0)...};
    // (callable(arr[I]), ...); // Nesting limit is only 256
}

template<std::size_t N, typename Callable>
void arange(Callable func) {
    std::array<int, N> arr;
    for(size_t i = 0; i < N; i++)
        arr[i] = i;
    iter_apply(func, arr, std::make_index_sequence<N>{});
}

int main() {
    arange<500>([](auto i) -> void { std::cout << std::bitset<sizeof(i) * 8>(i) << " "; });
}