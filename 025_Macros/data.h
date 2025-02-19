#pragma once
#include <string>
#include <any>

static int a;

struct Data {
    char* a; // 8 bytes
    int b; // 4 bytes
    Data* c; // 8 bytes
    std::string d; // 24 bytes
    void* e; // 8 bytes
    std::any f;
    char g[6] = "Hello";
};

/*
Remeber that all the pointers are equally sized as they only carry the memory address. So the size of variable changes based on the address length
32 bit : 4 bytes
64 bit : 8 bytes
*/