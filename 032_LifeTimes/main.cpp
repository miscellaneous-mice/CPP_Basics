#include <iostream>
#include <functional>
#include <vector>

class Entity {
public:
    Entity() {
        std::cout<<"Created Entity"<<std::endl;
    }
    ~Entity() {
        std::cout<<"Destroyed Entity"<<std::endl;
    }

};

template<typename T>
struct CPPArray {
    T* __custom_array__;
    size_t N;

    CPPArray(): __custom_array__(nullptr), N(0) {};

    CPPArray(std::initializer_list<T> values) {
        N = values.size();
        __custom_array__ = new T[N];  // Use 'new' instead of malloc
        size_t i = 0;
        for (T val : values) {
            __custom_array__[i++] = val;
        }
    }
    ~CPPArray() { delete[] __custom_array__; }
    void setsize(size_t new_size) {
        T* __temp__ = new T[new_size];
        size_t minSize = (new_size < N) ? new_size : N;
        memcpy(__temp__, __custom_array__, minSize);
        delete[] __custom_array__;
        __custom_array__ = __temp__;
        N = new_size;
    }

    void push_back(T element) {
        setsize(N + 1);
        __custom_array__[N - 1] = element;
    }
    std::function<const T*()> begin = [this]() -> const T* { return this->__custom_array__ ; };
    std::function<const T*()> end = [this]() -> const T* { return this->__custom_array__ +  N; };
};

template<typename T>
struct CArray {
    T* __custom_array__;
    size_t N;
    CArray(std::initializer_list<T> values) { // Same as *args in python
        N = values.size();
        __custom_array__ = (T*)malloc(sizeof(T) * N);
        size_t i = 0;
        for (T val : values) {
            __custom_array__[i++] = val;
        }
    }
    ~CArray() { free(__custom_array__); }
    void setsize(size_t new_size) {
        __custom_array__ = (T*)realloc(__custom_array__, sizeof(T) * new_size);
        N = new_size;
    }

    void push_back(T element) {
        setsize(N + 1);
        __custom_array__[N - 1] = element;
    }
    std::function<const T*()> begin = [this]() -> const T* { return this->__custom_array__ ; };
    std::function<const T*()> end = [this]() -> const T* { return this->__custom_array__ +  N; };
};

template<typename T>
void Print(const T& Array){ // Use const & to avoid making copies of the instance
    using namespace std;
    for (auto x : Array) {
        cout<<x<<", ";
    }
    cout<<endl;
}

int main() {
    // The below code is declared on a scope
    { // scope start -> variable allocated on stack
        std::cout<<"Stack allocated"<<std::endl;
        Entity stack_entity;
    } // scope end -> stack variable is automatically deallocated when exiting scope
    { //scope start -> heap variable is allocated
        std::cout<<"Heap allocated"<<std::endl;
        Entity* heap_entity = new Entity();
    } // scope end -> heap variable isn't automatically deallocated when exiting scope

    std::cout<<"Using CPP array"<<std::endl;
    CPPArray<int> cpp_arr = {0, 1, 2, 3, 4, 5};
    for (auto element : cpp_arr) {
        std::cout<<element<<" ";
    }
    std::cout<<std::endl;
    cpp_arr.push_back(5);
    cpp_arr.push_back(6);
    cpp_arr.push_back(7);
    for (auto element : cpp_arr) {
        std::cout<<element<< " ";
    }


    std::cout<<std::endl<<"Using C array"<<std::endl;
    CArray<int> c_arr = {0, 1, 2, 3, 4, 5};
    for (auto element : c_arr) {
        std::cout<<element<<" ";
    }
    std::cout<<std::endl;
    c_arr.push_back(5);
    c_arr.push_back(6);
    c_arr.push_back(7);
    for (auto element : c_arr) {
        std::cout<<element<< " ";
    }
}