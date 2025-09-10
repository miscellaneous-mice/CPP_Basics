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

void iter_sstream(std::unique_ptr<SStream>&& sstream) {
    std::cout<<"Moved the class instance"<<std::endl;
    for (auto s : *sstream) {
        std::cout << s << ", ";
    } 
    std::cout<<std::endl;
}

void iter_sstream(const SStream& sstream) {
    std::cout<<"Copied the class instance"<<std::endl;
    for (auto s : sstream) {
        std::cout << s << ", ";
    } 
    std::cout<<std::endl;
}

int main() {
    std::cout<<"Move semantics"<<std::endl;
    {
        std::unique_ptr<SStream> strng_uniq_ptr = std::make_unique<SStream>("Move Smart Pointers");
        auto new_owner = std::move(strng_uniq_ptr);
        iter_sstream(std::move(new_owner));
        // std::cout << *strng_uniq_ptr->begin() << std::endl; // Will cause issue
    }

    {
        std::unique_ptr<SStream> strng_uniq_ptr = std::make_unique<SStream>("Copy Smart Pointers");
        iter_sstream(*strng_uniq_ptr.get());
    }
}
