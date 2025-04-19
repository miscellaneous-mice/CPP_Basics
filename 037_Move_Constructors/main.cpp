#include <iostream>
#include <cstring>

struct SStream {
    SStream() : str(nullptr), N(0) { std::cout<<"Default constructor"<<std::endl; }

    SStream(const char* string) {
        std::cout<<"Constructor"<<std::endl;
        N = strlen(string);
        str = new char[N + 1];  // Allocate memory correctly
        memcpy(str, string, N);
        str[N] = '\0';  // Null-terminate
    }

    SStream(SStream&& other) {
        std::cout<<"Move constructor"<<std::endl;
        N = other.N;
        str = other.str;  // Take ownership
        other.str = nullptr;  // Prevent double free
        other.N = 0;
    }

    SStream& operator=(SStream&& other) {
        std::cout<<"Move Assignment Operator"<<std::endl;
        if (this != &other) {
            delete[] str;  // Free old memory

            // Take ownership
            N = other.N;
            str = other.str;

            // Prevent double free
            other.str = nullptr;
            other.N = 0;
        }
        return *this;
    }
    
    SStream& operator<<(SStream&& other) {
        std::cout<<"Move Overload Operator"<<std::endl;
        if (this != &other) {

            char* temp = new char[N];
            if (str != nullptr) {
                strcpy(temp, str);
                delete[] str;  // Free old memory
            }
            // Take ownership
            N = this->N + other.N;
            str = new char[N];
            strcpy(str, temp);
            memcpy(str + strlen(temp), other.str, strlen(other.str));

            // Prevent double free
            other.str = nullptr;
            other.N = 0;
            delete[] temp;
        }
        return *this;
    }

    SStream& operator<<(const char* data) {
        std::cout<<"Overload Operator"<<std::endl;
        char* temp = new char[N];
        if (str != nullptr) {
            strcpy(temp, str);
            delete[] str;  // Free old memory
        }
        // Take ownership
        N = this->N + strlen(data);
        str = new char[N];
        strcpy(str, temp);
        memcpy(str + strlen(temp), data, strlen(data));
        delete[] temp;
        return *this;
    }

    SStream(const SStream&) = delete;
    SStream& operator=(const SStream&) = delete;

    ~SStream() { delete[] str; }  // Free allocated memory

    char* begin() const { return str; }
    char* end() const { return str + N; }

private:
    char* str;
    size_t N;
};

std::ostream& operator<<(std::ostream& stream, const SStream& string) {
    for(auto& s : string){
        stream<<s;
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, SStream&& string) {
    for(auto& s : string){
        stream<<s;
    }
    return stream;
}

class Entity {
public:
    Entity(SStream&& value) : string((SStream&&)value) {}; // Same as Entity(SStream&& value) : string(std::move(value)) {};
    void PrintName() {
        std::cout<<string<<std::endl;
    }
private:
    SStream string;
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

    for (auto s : strng4) {
        std::cout << s << ", ";
    }
    
    std::cout<<std::endl;
    
    SStream strng5 = std::move(strng4);
    for (auto s : strng5) {
        std::cout << s << ", ";
    }    

    std::cout<<std::endl;

    std::cout<<(SStream&&)strng5<<std::endl;
    std::cout<<std::move(strng5)<<std::endl;
    
    Entity e("Viglaw");
    e.PrintName();

    std::array<SStream, 5> strs = {"Joe", "Jim", "Ellen", "Victor", "Susanne"};
    for (auto& s : strs) {
        std::cout<<s<<std::endl;
    }

    SStream ss_val;
    ss_val<<"Just Overloading some";
    ss_val<<", What is that! ";
    ss_val<<std::move(strng5);
    std::cout<<ss_val<<std::endl;
}
