#include <iostream>
#include <ranges>

template<typename T, size_t N>
struct Array {
    T arr[N];
    const T* begin() const { return arr; }
    const T* end() const { return arr + N; }
};


int main() {
    Array<int, 10> sample_arr = {1, 2, 3, 4, 5, 6};
    for(auto element : sample_arr | std::views::transform([=](auto e){ return std::pow(e, 2); }))
        std::cout<<element<<std::endl;
}