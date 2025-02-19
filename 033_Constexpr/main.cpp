#include <iostream>
#include <array>
#include <cstring>
#include <map>

enum class OPERATIONS {
    FACT=0, FIB
};

constexpr double recusive_func(int n, OPERATIONS op_type) {
    if (n <= 1) return n;
    if (op_type == OPERATIONS::FACT){
        return n * recusive_func(n - 1, op_type);
    }
    else if (op_type == OPERATIONS::FIB){
        return recusive_func(n-1, op_type) + recusive_func(n-2, op_type);
    }
    else {
        return 0;
    }
}

constexpr std::array<char, 128> mapping() {
    std::array<char, 128> values = {};
    values['a'] = 'P';
    values['b'] = 'r';
    values['c'] = 'a';
    values['d'] = 't';
    values['e'] = 'e';
    values['f'] = 'e';
    values['g'] = 'k';
    values['h'] = 0;
    return values;
}

#include <iostream>
#include <type_traits>

static constexpr std::array<char, 128> hashmap = mapping();

int main() {
    constexpr int val = 10;
    constexpr double fib_res = recusive_func(val, OPERATIONS::FIB);
    constexpr double fact_res = recusive_func(val, OPERATIONS::FACT);
    std::cout<<"Factorial "<<val<<" : "<<fact_res<<std::endl;
    std::cout<<"Fibonacci "<<val<<" : "<<fib_res<<std::endl;

    std::cout<<hashmap['a']<<std::endl;
    std::cout<<hashmap['b']<<std::endl;
    for (size_t i = int('a'); i <= int('g'); )
        // std::cout<<hashmap[++i]<<".";
        std::cout<<hashmap[i++]<<".";

    std::cout<<std::endl;
}