#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <map>
#include <any>
#include <sstream>

#define calc_offset(s, d) ((size_t)&(((s*)nullptr)->d))

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

enum class types {
    i=0, c, f, d, l, PKc
};

struct Data{
    int a = -5;
    char b = 'a';
    float c = 5.423f;
    double d = 5.00032;
    const char* e = "!!!";
    long f = 5L;
    long* g = &f;
    void* h = &e;
    int& i = a;
};

static std::map<types, std::tuple<std::type_index, std::string> (*)(const std::any& a)> datatypes = {
    {types::i, [](const std::any& a) -> std::tuple<std::type_index, std::string> { return {std::type_index(typeid(int)), cast(a, int)}; }},
    {types::c, [](const std::any& a) -> std::tuple<std::type_index, std::string> { return {std::type_index(typeid(char)), cast(a, char)}; }},
    {types::f, [](const std::any& a) -> std::tuple<std::type_index, std::string> { return {std::type_index(typeid(float)), cast(a, float)}; }},
    {types::d, [](const std::any& a) -> std::tuple<std::type_index, std::string> { return {std::type_index(typeid(double)), cast(a, double)}; }},
    {types::l, [](const std::any& a) -> std::tuple<std::type_index, std::string> { return {std::type_index(typeid(long)), cast(a, long)}; }},
    {types::PKc, [](const std::any& a) -> std::tuple<std::type_index, std::string> { return {std::type_index(typeid(const char*)), cast(a, const char*)}; }},
};

int main() {
    Data d;
    Data* Ptr_d = new Data();
    std::unique_ptr<Data> SPtr_d = std::make_unique<Data>();
    std::string str = "Hello world";
    auto log = [=](const char* value) { return (std::string(value) + Ptr_d->e); };

    std::cout<<"1. The data is : "<<std::get<1>(datatypes[types::i](d.a))<<", type is : "<<std::get<0>(datatypes[types::i](d.a)).name()<<std::endl;
    std::cout<<"2. The data is : "<<std::get<1>(datatypes[types::c](d.b))<<", type is : "<<std::get<0>(datatypes[types::c](d.b)).name()<<std::endl;
    std::cout<<"3. The data is : "<<std::get<1>(datatypes[types::f](d.c))<<", type is : "<<std::get<0>(datatypes[types::f](d.c)).name()<<std::endl;
    std::cout<<"4. The data is : "<<std::get<1>(datatypes[types::d](d.d))<<", type is : "<<std::get<0>(datatypes[types::d](d.d)).name()<<std::endl;
    std::cout<<"5. The data is : "<<std::get<1>(datatypes[types::PKc](d.e))<<", type is : "<<std::get<0>(datatypes[types::PKc](d.e)).name()<<std::endl;
    std::cout<<"6. The data is : "<<std::get<1>(datatypes[types::l](d.f))<<", type is : "<<std::get<0>(datatypes[types::l](d.f)).name()<<std::endl;

    std::cout<<"7. The data is : "<<*d.g<<", the type is : "<<typeid(d.g).name()<<std::endl;
    std::cout<<"8. The data is : "<<*((const char**)d.h)<<", the type is : "<<typeid(d.h).name()<<std::endl;
    std::cout<<"9. The data is : "<<d.i<<", the type is : "<<typeid(d.i).name()<<std::endl;

    std::cout<<"10. The type is : "<<typeid(d).name()<<std::endl;
    std::cout<<"11. The type is : "<<typeid(Ptr_d).name()<<std::endl;
    std::cout<<"12. The type is : "<<typeid(SPtr_d).name()<<std::endl;
    std::cout<<"13. The type is : "<<typeid(str).name()<<std::endl;

    std::cout<<"14. The type is : "<<typeid(datatypes).name()<<std::endl;
    std::cout<<"15. The type is : "<<typeid(types).name()<<std::endl;
    std::cout<<"16. Return value of lambda function is : "<<log(str.c_str())<<", the type is : "<<typeid(log).name()<<std::endl;
    std::cout<<"17. Return value of Macro is : "<<calc_offset(Data, f)<<", the type is : "<<typeid(calc_offset(Data, f)).name()<<std::endl;

    delete Ptr_d;
    return 0;
}

/*
P -> Pointer (*)
K -> Constant (const)
c -> char
i -> int
f -> float
d -> double
l -> long
m -> size_t
PKc -> const char*, Pl -> long*, Pi -> int*, etc.
NSt3 -> STL
*/