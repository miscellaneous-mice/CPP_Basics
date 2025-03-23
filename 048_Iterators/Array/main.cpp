#include <iostream>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <initializer_list>

template <typename Array>
struct ArrayIterator {
    using ValueType = typename Array::Type;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
    ArrayIterator(PointerType ptr) : m_Ptr(ptr) {};

    // PreFix operator
    ArrayIterator operator++() const {
        m_Ptr++;
        return *this;
    }

    // PostFix operator
    ArrayIterator operator++(int) const {
        ArrayIterator iterator = *this; 
        ++(*this);
        return iterator;
    }

    ArrayIterator operator--() {
        m_Ptr--;
        return *this;
    }

    ArrayIterator operator--(int) {
        ArrayIterator iterator = *this; 
        --(*this);
        return iterator;
    }

    ReferenceType operator[](int n) const {
        return *(m_Ptr + n);
    }

    PointerType operator->() const {
        return m_Ptr;
    }

    ReferenceType operator*() const {
        return *m_Ptr;
    }

    bool operator==(const ArrayIterator& other) const {
        return m_Ptr == other.m_Ptr;
    }

    bool operator!=(const ArrayIterator& other) const {
        return !(*this == other);
    }

private:
    mutable PointerType m_Ptr;
};

template<typename T>
struct Array {
    T* array;
    size_t N;
    using Type = T;
    using Iterator = ArrayIterator<Array<T>>;
    using constIterator = const ArrayIterator<Array<T>>;

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

    void push_back(T element) {
        setsize(N + 1);
        array[N - 1] = element;
    }    

    Iterator begin() { return Iterator(array); }
    Iterator end() { return Iterator(array + N); }
    constIterator begin() const { return constIterator(array); }
    constIterator end() const {  return constIterator(array + N); }
};

int main() {
    Array<int> arr = {1, 2, 3, 4, 5};
    for (Array<int>::constIterator it = arr.begin(); it != arr.end(); it++) {
        std::cout << *it << ", ";
    }
    std::cout<<std::endl;

    Array<int>::Iterator it = arr.begin();
    auto it1 = it++;
    std::cout<<*it1<<std::endl;

    auto it2 = ++it;
    std::cout<<*it2<<std::endl;

    for (const auto& elem : arr) {
        std::cout << elem << ", ";
    }
    std::cout<<std::endl;
    return 0;
}