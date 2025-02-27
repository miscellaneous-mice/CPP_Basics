#include <iostream>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <initializer_list>

template<typename T>
struct Array {
    T* __array__;
    size_t N;

    Array() : __array__(new T[0]), N(0) {};

    Array(std::initializer_list<T> values) : __array__(new T[values.size()]), N(values.size()) {
        size_t i = 0;
        if constexpr (std::is_trivially_copyable_v<T>) {
            std::memcpy(__array__, values.begin(), N * sizeof(T));
        } else {
            for (auto val : values) {
                __array__[i++] = std::move(val);
            }
        }
    }

    Array(const Array& other) : N(other.N), __array__(new T[other.N]) {
        if constexpr (std::is_trivially_copyable_v<T>) {
            std::memcpy(__array__, other.__array__, N * sizeof(T));
        } else {
            for (size_t i = 0; i < N; i++) {
                __array__[i] = std::move(other.__array__[i]);
            }
        }
    }

    Array(Array&& other) {
        N = other.N;
        __array__ = other.__array__;
        other.__array__ = nullptr;
        other.N = 0;
    }

    Array& operator=(Array&& other)  {
        if (this != &other) {
            delete[] __array__;
            N = other.N;
            __array__ = other.__array__;
            other.__array__ = nullptr;
            other.N = 0;
        }
        return *this;
    }

    T& operator[](size_t index) const {
        return __array__[index];
    }

    // Generalized operator+ for different types
    template<typename U>
    auto operator+(const Array<U>& other) const {
        using ResultType = typename std::common_type<T, U>::type;
    
        if (N != other.N) {
            std::cerr << "Elements do not have the same shape!" << std::endl;
            throw std::exception();
        }
    
        Array<ResultType> result;
    
        for (size_t i = 0; i < N; i++) {
            result.push_back(static_cast<ResultType>((*this)[i]) + static_cast<ResultType>(other[i]));
        }
    
        return result;
    }

    Array& operator=(const Array& other) = delete;
    ~Array() { delete[] __array__; }

    void setsize(size_t new_size) {
        T* __temp__ = new T[new_size];
        size_t minSize = (new_size < N) ? new_size : N;
        std::copy(__array__, __array__ + minSize, __temp__);
        delete[] __array__;
        __array__ = __temp__;
        N = new_size;
    }

    void push_back(T element) {
        setsize(N + 1);
        __array__[N - 1] = element;
    }    

    T* begin() { return __array__; }
    T* end() { return __array__ + N; }
    const T* begin() const { return __array__; }
    const T* end() const { return __array__ + N; }
};

template <typename T, size_t N>
struct NDVector {
    using Tensor = Array<typename NDVector<T, N - 1>::Tensor>;
};

// Base case for 1D array
template <typename T>
struct NDVector<T, 1> {
    using Tensor = Array<T>;
};

template<typename T>
std::ostream& operator<<(std::ostream& console, const Array<T>& array){
    for(auto elem : array)
        console<<elem<<" ";
    return console;
}

template<typename T, size_t N> using Tensor = typename NDVector<T, N>::Tensor;

int main() {
    Tensor<int, 3> arr3d = {
        {
            {1, 2, 3, 4},
            {5, 6, 7, 8}
        },
        {
            {9, 10, 11, 12},
            {13, 14, 15, 16}
        }
    };
    for (auto& x: arr3d){
        for(auto& y: x) {
            for(auto z: y) {
                std::cout<<z<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<"-----"<<std::endl;
    }

    Array<int> a = {1, 2, 3, 4, 5};
    Array<float> b = {3.324f, 8.478f, 5.347f, 2.934f, 0.348f};
    auto sum = a + b;
    std::cout<<sum<<std::endl;
}