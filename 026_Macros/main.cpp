#include <iostream>
#include <any>
#include <typeinfo>
#include <sstream>
#include "data.h"

#define calc_offset(s, m) ((size_t)&(((s*)0)->m))
#define cast_any(c, T) (std::any_cast<T>(c))
#define cast_static(c, T) (*((T*)c))

template<typename T>
static std::string any_to_string(const std::any& a) {
    try {
        // Extract the value from std::any and stream it to convert to std::string
        std::stringstream ss;
        ss << cast_any(a, T);
        return ss.str();
    } catch (const std::bad_any_cast& e) {
        return "Bad cast: " + std::string(e.what());
    }
}

#define convert_to_str(c, T) (any_to_string<T>(c))

int main(){
    float a = 5.6f;
    void* data = &a;
    std::any c = "sfdskl";
    std::cout<<"The offset of f is : "<<calc_offset(Data, f)<<" bytes"<<std::endl;
    std::cout<<cast_static(data, int)<<std::endl;
    std::cout<<typeid(cast_any(c, std::string)).name() << " : " << cast_any(c, const char*) <<std::endl;
    std::cout<<convert_to_str(c, const char*)<<std::endl;
}

