#include <memory>
#include <algorithm> // for std::min
#include <cstring>   // for std::memcpy
#include <initializer_list>
#include <type_traits> // for std::is_convertible, std::common_type
#include <iostream> // for testing


template <typename Array>
struct ArrayIterator {
    using VarType = typename Array::Type;
    using PointerType = VarType*;
    using ReferenceType = VarType&;
    ArrayIterator(PointerType ptr) : m_Ptr(ptr) {};
    ArrayIterator operator++() const {
        m_Ptr++;
        return *this;
    }
    ArrayIterator operator++(int) const {
        static ArrayIterator iterator = *this;
        ++(*this);
        return iterator;
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
    using Type = T;
    using Iterator = ArrayIterator<Array<T>>;
    using constIterator = ArrayIterator<Array<T>>;

    Array() : array(nullptr, [](T* p){}), N(0) {}; // Initialize with a null pointer and empty deleter

    template<typename U>
    Array(const std::initializer_list<U>& values) {
        N = values.size();
        array = std::shared_ptr<T[]>(new T[N], [](T* p){ delete[] p; });
        size_t i = 0;
        for(const auto& value : values) {
            array[i++] = value;
        }
    }

    template<typename U>
    Array(const Array<U>& other) {
        auto casted_entity = other.template cast<T>();
        N = other.size();
        array = std::shared_ptr<T[]>(new T[N], [](T* p){ delete[] p; });
        for (size_t i = 0; i < N; ++i) {
            array[i] = casted_entity[i];
        }
    }

    template<typename U>
    Array(Array<U>&& other) {
        auto casted_entity = other.template cast<T>();
        N = other.size(); // Important: Copy the size *before* potentially invalidating other
        array = std::shared_ptr<T[]>(new T[N], [](T* p){ delete[] p; });
        for (size_t i = 0; i < N; ++i) {
            array[i] = casted_entity[i];
        }
        other.array = nullptr; // Prevent double deletion
        other.N = 0;
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            Array temp(other); // Copy-and-swap idiom
            std::swap(array, temp.array);
            std::swap(N, temp.N);
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            array = std::move(other.array);
            N = other.N;
            other.array = nullptr;
            other.N = 0;
        }
        return *this;
    }

    T& operator[](size_t index) {
        return array[index];
    }

    const T& operator[](size_t index) const {
        return array[index];
    }

    template<typename U>
    typename std::enable_if<std::is_convertible_v<T, U>, Array<typename std::common_type<T, U>::type>>::type cast() const {
        using ResultType = typename std::common_type<T, U>::type;
        Array<ResultType> casted_arr;
        for(const T& element : *this)
            casted_arr.pushback(element);
        return casted_arr;
    }

    void resize(size_t new_size) {
        std::shared_ptr<T[]> temp(new T[new_size], [](T* p){ delete[] p; });
        if (array) {
            std::memcpy(temp.get(), array.get(), std::min(N, new_size) * sizeof(T));
        }
        array = temp;
        N = new_size;
    }

    template<typename U>
    void pushback(const U& element) {
        resize(N + 1);
        array[N - 1] = static_cast<T>(element);
    }

    Iterator begin() { return Iterator(array.get()); }
    Iterator end() { return Iterator(array.get() + N); }
    constIterator begin() const { return constIterator(array.get()); }
    constIterator end() const { return constIterator(array.get() + N); }

    size_t size() const { return N; }

    ~Array() = default; // No need to explicitly delete, shared_ptr handles it

private:
    std::shared_ptr<T[]> array;
    size_t N;
};

template<typename U, typename T>
auto operator*(const Array<T>& lhs, const Array<U>& rhs){
    using ResultType = typename std::common_type<T, U>::type;
    Array<ResultType> result;
    for (size_t i = 0; i < std::min(lhs.size(), rhs.size()); i++){
        result.pushback(static_cast<ResultType>(lhs[i]) * static_cast<ResultType>(rhs[i]));
    }
    return result;
}

int main() {
    Array<int> arr = {1, 2, 3, 4, 5};
    std::cout << "Size: " << arr.size() << std::endl;
    for (const auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    Array<double> arr2 = arr.cast<double>();
    std::cout << "Size: " << arr2.size() << std::endl;
    for (const auto& elem : arr2) {
        std::cout << elem << "->" << typeid(elem).name() << " ";
    }
    std::cout << std::endl;

    Array<int> arr3 = std::move(arr);
    std::cout << "Size arr: " << arr.size() << std::endl;
    std::cout << "Size arr3: " << arr3.size() << std::endl;
    for (const auto& elem : arr3) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    arr2.pushback(22);
    auto arr4 = arr3 * arr2;
    std::cout << "Size arr: " << arr.size() << std::endl;
    std::cout << "Size arr3: " << arr3.size() << std::endl;
    for(Array<double>::Iterator iter = arr4.begin(); iter != arr4.end(); iter++) {
        std::cout<<*iter<<" ";
    }
    std::cout << std::endl;
    return 0;
}