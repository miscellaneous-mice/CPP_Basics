#include <iostream>
#include <cstring>

struct SStream {
    char* __str__;
    size_t N;

    SStream() : __str__(nullptr), N(0) { std::cout<<"Default constructor"<<std::endl; }

    SStream(const char* string) {
        std::cout<<"Constructor"<<std::endl;
        N = strlen(string);
        __str__ = new char[N + 1];  // Allocate memory correctly
        memcpy(__str__, string, N);
        __str__[N] = '\0';  // Null-terminate
    }

    SStream(SStream&& other) noexcept {
        std::cout<<"Move constructor"<<std::endl;
        N = other.N;
        __str__ = other.__str__;  // Take ownership
        other.__str__ = nullptr;  // Prevent double free
        other.N = 0;
    }

    SStream& operator=(SStream&& other) noexcept {
        std::cout<<"Move Assignment Operator"<<std::endl;
        if (this != &other) {
            delete[] __str__;  // Free old memory

            // Take ownership
            N = other.N;
            __str__ = other.__str__;

            // Prevent double free
            other.__str__ = nullptr;
            other.N = 0;
        }
        return *this;
    }
    
    SStream(const SStream&) = delete;
    SStream& operator=(const SStream&) = delete;

    ~SStream() { delete[] __str__; }  // Free allocated memory

    char* begin() const { return __str__; }
    char* end() const { return __str__ + N; }
};

int main() {
    SStream* strng = new SStream("Hola, Mucho Gusto");

    for (auto s : *strng) {
        std::cout << s << ", ";
    }
    
    std::cout<<std::endl;
    
    SStream* strng2 = std::move(strng);
    for (auto s : *strng2) {
        std::cout << s << ", ";
    }    

    std::cout<<std::endl;
    
    SStream* strng3;
    strng3 = std::move(strng2);
    for (auto s : *strng3) {
        std::cout << s << ", ";
    }  

    std::cout<<std::endl;

    SStream strng4 = "Hola, Mucho Gusto";

    for (auto s : *strng) {
        std::cout << s << ", ";
    }
    
    std::cout<<std::endl;
    
    SStream strng5 = std::move(strng4);
    for (auto s : strng5) {
        std::cout << s << ", ";
    }    

    std::cout<<std::endl;
    
    SStream strng6;
    strng6 = std::move(strng5);
    for (auto s : strng6) {
        std::cout << s << ", ";
    }  
}
