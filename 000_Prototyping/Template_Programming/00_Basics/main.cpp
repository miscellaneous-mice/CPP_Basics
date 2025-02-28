#include <iostream>
#include <ranges>

template<typename T, size_t N>
struct Array {
    T arr[N];
    const T* begin() const { return arr; }
    const T* end() const { return arr + N; }
};

template<typename T>
void Print(T&& value){
    std::cout<<"Value : "<<value<<" Type : "<<typeid(value).name()<<std::endl;
}


int main() {
    Print(10); // compiler will create a instance void Print(int&& value) at compile time
    Print("Howa"); // compiler will create a instance void void Print(const char(&&)[6] value) at compile time
    Print(79.03f); // compiler will create a instance void Print(float&& value) at compile time
    Array<int, 10> sample_arr = {1, 2, 3, 4, 5, 6};
    for(auto element : sample_arr | std::views::transform([=](auto e){ return std::pow(e, 2); }))
        std::cout<<element<<std::endl;
}