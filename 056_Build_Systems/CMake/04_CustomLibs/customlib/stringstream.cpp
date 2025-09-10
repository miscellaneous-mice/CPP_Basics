#include "stringstream.h"

StreamIterator::StreamIterator(PointerType ptr) : m_Ptr(ptr) {};

// PreFix operator
StreamIterator StreamIterator::operator++() const {
    m_Ptr++;
    return *this;
}

// PostFix operator
StreamIterator StreamIterator::operator++(int) const {
    StreamIterator iterator = *this; 
    ++(*this);
    return iterator;
}

StreamIterator StreamIterator::operator--() {
    m_Ptr--;
    return *this;
}

StreamIterator StreamIterator::operator--(int) {
    StreamIterator iterator = *this; 
    --(*this);
    return iterator;
}

StreamIterator::ReferenceType StreamIterator::operator[](int n) const {
    return *(m_Ptr + n);
}

StreamIterator::PointerType StreamIterator::operator->() const {
    return m_Ptr;
}

StreamIterator::ReferenceType StreamIterator::operator*() const {
    return *m_Ptr;
}

bool StreamIterator::operator==(const StreamIterator& other) const {
    return m_Ptr == other.m_Ptr;
}

bool StreamIterator::operator!=(const StreamIterator& other) const {
    return !(*this == other);
}


SStream::SStream() : str(nullptr), N(0) { std::cout<<"Default constructor"<<std::endl; }

SStream::SStream(const char* string) {
    std::cout<<"Constructor"<<std::endl;
    N = strlen(string);
    str = new char[N + 1];  // Allocate memory correctly
    memcpy(str, string, N);
    str[N] = '\0';  // Null-terminate
}

SStream::SStream(SStream&& other) {
    std::cout<<"Move constructor"<<std::endl;
    N = other.N;
    str = other.str;  // Take ownership
    other.str = nullptr;  // Prevent double free
    other.N = 0;
}

SStream& SStream::operator=(SStream&& other) {
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
    
SStream& SStream::operator<<(SStream&& other) {
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

SStream& SStream::operator<<(const char* data) {
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

SStream& SStream::operator<<(const std::string& data) {
    std::cout<<"Overload Operator"<<std::endl;
    char* temp = new char[N];
    if (str != nullptr) {
        strcpy(temp, str);
        delete[] str;  // Free old memory
    }
    // Take ownership
    N = this->N + strlen(data.c_str());
    str = new char[N];
    strcpy(str, temp);
    memcpy(str + strlen(temp), data.c_str(), data.length());
    delete[] temp;
    return *this;
}

std::string SStream::ret_str() {
    return (this->str != nullptr) ? std::string(this->str) : std::string("");
}

SStream::Iterator SStream::begin() { return Iterator(str); }
SStream::Iterator SStream::end() { return Iterator(str + N); }
SStream::constIterator SStream::begin() const { return constIterator(str); }
SStream::constIterator SStream::end() const {  return constIterator(str + N); }

SStream::~SStream() { delete[] str; }  // Free allocated memory



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

int SStreamAccessor::getsize(const SStream& sstream) {
    return sstream.N;
}

void SStreamAccessor::print_contents(const SStream& sstream) {
    for (auto s : sstream) {
        std::cout << s << ", ";
    } 
    std::cout<<std::endl;
}
