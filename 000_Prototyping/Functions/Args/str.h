#pragma once
#include <iostream>
#include <cstring>

class String {
public:
    String(const char* s);

    ~String();

    String operator+(const String& other) const;

    String operator+(const char* other) const;

    friend std::ostream& operator<<(std::ostream& os, const String& s);

private:
    char* str;
    size_t len;
};

String operator+(const char* other, const String& str);