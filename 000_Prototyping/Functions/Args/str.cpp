#include "str.h"

String::String(const char* s) {
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
}

String::~String() {
    delete[] str;
}

String String::operator+(const String& other) const {
    size_t new_len = len + other.len;
    char* new_str = new char[new_len + 1];
    std::strcpy(new_str, str);
    std::strcat(new_str, other.str);
    String result(new_str);
    delete[] new_str;
    return result;
}

String String::operator+(const char* other) const {
    size_t new_len = len + strlen(other);
    char* new_str = new char[new_len + 1];
    std::strcpy(new_str, str);
    std::strcat(new_str, other);
    String result(new_str);
    delete[] new_str;
    return result;
}

String operator+(const char* other, const String& str) {
    return str + other;
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    os << s.str;
    return os;
}