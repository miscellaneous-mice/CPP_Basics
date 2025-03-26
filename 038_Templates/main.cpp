// https://learn.microsoft.com/en-us/cpp/cpp/class-templates?view=msvc-170
#include <iostream>
#include <string>
#include <array>
// #include "entities.h"


template<typename U>
class iterator {
private:
    U* array;
    size_t N;
public:
    // iterator() : array(nullptr), N(0) {};
    iterator(size_t N) : N(N) {
        array = new U[N];
    };
    iterator(const iterator& other) {
        N = other.N;
        std::copy(other.array, other.array + N, this->array);
    }
    iterator(iterator&& other) {
        N = other.N;
        std::copy(other.array, other.array + N, this->array);
        other.array = nullptr;
        other.N = 0;
    }
    iterator& operator=(const iterator& other) {
        if (this != &other){
            N = other.N;
            delete[] array;
            array = new U[N];
            memset(array, other.array, N);
        }
        return *this;
    }
    iterator& operator=(iterator&& other) {
        if (this != &other){
            N = other.N;
            delete[] array;
            array = new U[N];
            memset(array, other.array, N);
            other.array = nullptr;
            other.N = 0;
        }
        return *this;
    }
    U& operator[](size_t index) const {
        return array[index];
    }

    template<typename T>
    auto operator+(const iterator<T>& other) const {
        if (N != other.N){
            std::cerr<<"Arrays of not the same size"<<std::endl;
            throw std::exception();
        }
        using ResultType = typename std::common_type<T, U>::type;
        iterator<ResultType> res_arr;
        res_arr.array = new U[N];
        for(size_t i = 0; i < N; i++) {
            res_arr.array[i] = static_cast<ResultType>(other[i]) + static_cast<ResultType>((*this)[i]);
        }
        return res_arr;
    }

    size_t size() const {
        return N;
    }

    const U* begin() const {return array; }
    const U* end() const {return array + N; }
    ~iterator() { delete[] array; }
};

template<typename T>
class ring {
private:
    size_t max_len, N;
    iterator<T>* iter;
public:
    ring(size_t max_len) : max_len(max_len), N(0) {
        iter = new iterator<T>(max_len);
    };

    ring(ring&& other) {
        max_len = other.max_len;
        iter = std::move(other.iter);
        other.max_len = 0;
    }

    ~ring() { delete[] iter; }

    T& operator[](size_t index) const {
        return (*iter)[index];
    }

    iterator<T>* operator->(){
        iterator<T>* iter_cpy = iter;
        return iter_cpy;
    }

    const iterator<T>* operator->() const {
        iterator<T>* iter_cpy = iter;
        return iter_cpy;
    }

    ring(const ring& other) = delete;

    void add(const std::string& str) {
        N = (N >= max_len) ? 1 : N + 1;
        (*this)[N - 1] = str;
    }

    void Print() const {
        for (auto element : *iter){
            std::cout<<element<<std::endl;
        }
    }
};

template <typename T>
void print (const T& arg) {
    std::cout << arg << std::endl;
}

template <typename T, typename... Types>
void print (const T& firstArg, const Types&... args) {
    std::cout << firstArg << std::endl;
    print(args...);
}

template<typename T>
struct Number { T n; };
 
template<typename T>
struct Array {
    T* array;
    size_t N;
    Array() : array(nullptr), N(0) {};
    Array(std::initializer_list<T> values) : N(values.size()){
        array = new T[N];
        std::memcpy(array, values.begin(), N * sizeof(T));
    }
    Array& operator=(std::initializer_list<T> values) {
        N = values.size();
        delete[] array;
        array = new T[N];
        std::memcpy(array, values.begin(), N * sizeof(T));
        return *this;
    }

    template<typename U>
    Array(const Array<U>& other) : N(other.N) {
        using CT = typename std::common_type<T, U>::type;
        array = new T[N];
        for (size_t i = 0; i < N; i++) {
            array[i] = static_cast<T>(other.array[i]); // Convert elements
        }
    }

    template<typename U>
    auto operator=(const Array<U>& other) {
        using CT = typename std::common_type<std::decay_t<T>, std::decay_t<U>>::type;
        Array<CT> new_array;
        new_array.N = 0;
        new_array.array = new CT[N];
        for (int i = 0; i < N; i++) {
            new_array[i] = static_cast<CT>(other.array[i]);
        }
        return array;
    }

    T& operator[](size_t index) const { return array[index]; };
    const T* begin() const { return array; };
    const T* end() const { return array + N; };
};

template<>
struct Array<int> { // Template specialization for int Arrays
    int* array;
    size_t N;
    Array() : array(nullptr), N(0) { std::cout<<"Specialized for int arrays"<<std::endl; };
    Array(std::initializer_list<int> values) : N(values.size()){
        array = new int[N];
        std::memcpy(array, values.begin(), N * sizeof(int));
        std::cout<<"Specialized for int arrays"<<std::endl;
    }
    Array& operator=(std::initializer_list<int> values) {
        N = values.size();
        delete[] array;
        array = new int[N];
        std::memcpy(array, values.begin(), N * sizeof(int));
        return *this;
    }
    Array& operator=(const Array& other) {
        N = other.N;
        delete[] array;
        array = new int[N];
        std::memcpy(array, other.begin(), N * sizeof(int));
        return *this;
    }
    int& operator[](size_t index) const { return array[index]; };
    const int* begin() const { return array; };
    const int* end() const { return array + N; };
};

template<typename T, typename U>
constexpr Number<std::common_type_t<T, U>>
    operator+(const Number<T>& lhs, const Number<U>& rhs) {
    return {lhs.n + rhs.n};
}

template<typename U, typename T>
auto operator*(const Array<T>& lhs, const Array<U>& rhs){
    using ResultType = typename std::common_type<T, U>::type;
    Array<ResultType> result;
    result.N = lhs.N;
    result.array = new ResultType[lhs.N];
    for (size_t i = 0; i < lhs.N; i++){
        result[i] = static_cast<ResultType>(lhs[i]) * static_cast<ResultType>(rhs[i]);
    }
    return result;
}
 
void describe(const char* expr, const Number<int>& x) {
    std::cout << expr << "  is  Number<int>{" << x.n << "}\n";
}
 
void describe(const char* expr, const Number<double>& x) {
    std::cout << expr << "  is  Number<double>{" << x.n << "}\n";
}


int main(){
    print (7.5, "hello", std::bitset<16>(377), 42);
    
    ring<std::string> textring(4);

    textring.add("One");
    textring.add("Two");
    textring.add("Three");
    textring.add("Four");
    textring.add("Five");

    ring<std::string>* newtextring = &textring;
    newtextring->Print();

    Number<int> i1 = {1}, i2 = {2};
    Number<double> d1 = {2.3}, d2 = {3.5};
    describe("i1 + i2", i1 + i2);
    describe("i1 + d2", i1 + d2);
    describe("d1 + i2", d1 + i2);
    describe("d1 + d2", d1 + d2);    

    Array<int> arr1 = {1, 2, 3, 4, 5};
    Array<float> arr2;
    arr2 = {5.32f, 6.85f, 7.084f, 8.854f, 9.95f};
    Array<float> arr3;
    arr3 = arr1;
    auto res_arr = arr1 * arr2;
    for (auto r : res_arr) {
        std::cout<<r<<" ";
    }
    std::cout<<std::endl;
    return 0;
}