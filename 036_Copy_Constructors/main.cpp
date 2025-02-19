#include <iostream>
#include <cstring>
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

    // SStream(const SStream& other): __str__(other.__str__), N(other.N) {}; // default copy constructor
    // SStream(const SStream& other) = default // This is what unique ptr does

    SStream(const SStream& other) {
        std::cout<<"Copy constructor"<<std::endl;
        N = other.N;
        __str__ = new char[N];
        memcpy(__str__, other.__str__, N);
    }

    SStream& operator=(const SStream& other) {
        std::cout<<"Assignment Operator"<<std::endl;
        if (this != &other) {
            delete[] __str__;
            N = other.N;
            __str__ = new char[N];
            memcpy(__str__, other.__str__, N);
        }
        return *this;
    }

    char& operator[](size_t N){
        return __str__[N];
    }
    
    SStream(SStream&&) = delete;
    SStream& operator=(SStream&&) = delete;

    ~SStream() { delete[] __str__; }  // Free allocated memory

    char* begin() const { return __str__; }
    char* end() const { return __str__ + N; }
};

std::ostream& operator<<(std::ostream& console, const SStream& str) { // Passes the SStream instance as a reference, hence doesn't get copied
    for(auto s: str){
        console<<s;
    }
    return console;
}

std::ostream& operator<(std::ostream& console, SStream str) { // Each time a instance of SStream is passed it created a new copy using copy constructor
    for(auto s: str){
        console<<s;
    }
    return console;
}

int main() {
    SStream strng = "Hola, Mucho Gusto";

    for (auto s : strng) {
        std::cout << s << ", ";
    }
    
    std::cout<<std::endl;
    
    SStream strng2 = strng;
    for (auto s : strng2) {
        std::cout << s << ", ";
    }    

    std::cout<<std::endl;
    
    SStream strng3;
    strng3 = strng2;
    std::cout<<strng3<<std::endl;
    std::cout<strng3;
    std::cout<<std::endl;

    std::cout<<strng3[2]<<std::endl;

    // SStream strng4 = std::move(strng2); // This will cause issue as move constructor is specified as delete (i.e. disabled)
    return 0;
}
