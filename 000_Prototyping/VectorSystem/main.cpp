#include <iostream>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <initializer_list>

template<typename T>
struct Array {
    T* array;
    size_t N;

    Array() : array(new T[0]), N(0) {};

    Array(std::initializer_list<T> values) : array(new T[values.size()]), N(values.size()) {
        size_t i = 0;
        if constexpr (std::is_trivially_copyable_v<T>) {
            std::memcpy(array, values.begin(), N * sizeof(T));
        } else {
            for (auto val : values) {
                array[i++] = std::move(val);
            }
        }
    }

    Array(const Array& other) : N(other.N), array(new T[other.N]) {
        if constexpr (std::is_trivially_copyable_v<T>) {
            std::memcpy(array, other.array, N * sizeof(T));
        } else {
            for (size_t i = 0; i < N; i++) {
                array[i] = std::move(other.array[i]);
            }
        }
    }

    Array(Array&& other) {
        N = other.N;
        array = other.array;
        other.array = nullptr;
        other.N = 0;
    }

    Array& operator=(Array&& other)  {
        if (this != &other) {
            delete[] array;
            N = other.N;
            array = other.array;
            other.array = nullptr;
            other.N = 0;
        }
        return *this;
    }

    T& operator[](size_t index) const {
        return array[index];
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
    ~Array() { delete[] array; }

    template<typename newtype>
    explicit operator Array<newtype>() const {
        Array<newtype> new_array;
        for (std::size_t i = 0; i < N; i++) {
            new_array.push_back(static_cast<newtype>((*this)[i]));
        }
        return new_array;
    }

    void setsize(size_t new_size) {
        T* temp = new T[new_size];
        size_t minSize = (new_size < N) ? new_size : N;
        std::copy(array, array + minSize, temp);
        delete[] array;
        array = temp;
        N = new_size;
    }

    template<typename U>
    void push_back(const U& element) {
        setsize(N + 1);
        array[N - 1] = static_cast<T>(element);
    }

    T* begin() { return array; }
    T* end() { return array + N; }
    const T* begin() const { return array; }
    const T* end() const { return array + N; }
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
    Array<double> c = Array<double>(a);
    auto res1 = a + b;
    auto res2 = b + c;
    std::cout<<res1<<std::endl;
    std::cout<<res2<<std::endl;
}