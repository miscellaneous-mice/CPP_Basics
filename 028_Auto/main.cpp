#include <iostream>
#include <typeinfo>
#include <map>
#include <any>
#include <sstream>

#define calc_offset(s, d) ((size_t)&(((s*)nullptr)->d))

enum class types {
    i=0, c, f, d, l, PKc
};

struct Data{
    int a = -5;
    char b = 'a';
    float c = 5.423f;
    double d = 5.00032;
    long f = 5L;
    const char* e = "!!!";
};

static std::map<types, std::any> datatypes = {
    {types::i, -5},
    {types::c, 'a'},
    {types::f, 5.678f},
    {types::d, -6.785000},
    {types::l, 6L},
    {types::PKc, "Hello world"}
};

template<typename T, std::size_t N>
struct array {
    T data[N];
};

int main(){
    Data d;
    array<int, 5> arr = {1, 2, 3, 4, 5};
    auto data = d.a; // data is of type int;
    auto size = calc_offset(Data, a);
    std::cout<<typeid(data).name()<<std::endl;
    std::cout<<typeid(size).name()<<std::endl;
}