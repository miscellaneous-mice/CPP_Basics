#include <iostream>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <ranges>
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
    using Type = T;
    using Iterator = ArrayIterator<Array<T>>;
    using constIterator = const ArrayIterator<Array<T>>;
    Array() : array(new T[0]), N(0) {};

    template<typename new_T>
    explicit operator Array<new_T>() const {
        Array<new_T> new_array;
        for(auto element: *this)
            new_array.pushback(static_cast<new_T>(element));
        return new_array;
    }

    T& operator[](size_t index) {
        return array[index];
    }

    size_t size() {
        return N;
    }

    void setsize(size_t new_size) {
        size_t minsize = (N < new_size) ? N : new_size;
        T* temp_arr = new T[new_size];
        std::copy(array, array + N, temp_arr);
        delete[] array;
        array = temp_arr;
        N = new_size;
    }

    template<typename val_type>
    void pushback(val_type value) {
        using apptype = typename std::common_type<T, val_type>::type;
        auto val = static_cast<apptype>(value);
        setsize(N + 1);
        array[N - 1] = val;
    }

    Iterator begin() { return Iterator(array); }
    Iterator end() { return Iterator(array + N); }

    constIterator begin() const { return constIterator(array); }
    constIterator end() const { return constIterator(array + N); }
private:
    T* array;
    size_t N;
};

template<typename HashMap>
struct HashMapIterator {
    using KeyType = typename HashMap::KeyType;
    using ValueType = typename HashMap::ValueType;
    using PairStorage = typename std::pair<KeyType, ValueType>;
    using PairType = typename std::pair<typename Array<KeyType>::Iterator, typename Array<ValueType>::Iterator>;
    
    HashMapIterator(PairType HM_pair) : m_Pair(HM_pair) {}

    // PreFix operator
    HashMapIterator operator++() const {
        ++m_Pair.first;
        ++m_Pair.second;
        return *this;
    }

    // PostFix operator
    HashMapIterator operator++(int) const {
        HashMapIterator iterator = *this; 
        ++(*this);
        return iterator;
    }

    PairStorage operator*() const {
        return std::make_pair(*m_Pair.first, *m_Pair.second);
    }

    PairStorage* operator->() const {
        m_PairStorage = std::make_pair(*m_Pair.first, *m_Pair.second);
        return &m_PairStorage;
    }

    bool operator==(const HashMapIterator& other) const {
        return m_Pair.first == other.m_Pair.first;
    }

    bool operator!=(const HashMapIterator& other) const {
        return !(*this == other);
    }

private:
    PairType m_Pair;
    mutable PairStorage m_PairStorage; // Storage for operator->()
};


template<typename K, typename V, template<typename> typename C = Array>
struct HashMap {
    C<K> keys;
    C<V> values;
    using KeyType = K;
    using ValueType = V;
    using Iterator = HashMapIterator<HashMap<K, V>>;
    using constIterator = const HashMapIterator<HashMap<K, V>>;
    V& operator[](const K& key) {
        for (size_t i = 0; i < keys.size(); ++i) {
            if (keys[i] == key) {
                return values[i];
            }
        }
        keys.pushback(key);
        values.pushback(V());
        return values[keys.size() - 1];
    }

    Iterator begin() {
        return Iterator(std::make_pair(keys.begin(), values.begin()));
    }

    Iterator end() {
        return Iterator(std::make_pair(keys.end(), values.end()));
    }

    constIterator begin() const {
        return constIterator(std::make_pair(keys.end(), values.end()));
    }

    constIterator end() const {
        return constIterator(std::make_pair(keys.end(), values.end()));
    }
};

int main() {
    HashMap<const char*, int> hashmap;
    hashmap["a"] = 1;
    hashmap["b"] = 2;
    std::cout<<hashmap["b"]<<std::endl;

    for (const auto& pair: hashmap) {
        std::cout<<pair.first<<" : "<<pair.second<<", ";
    }
    std::cout<<std::endl;

    for (HashMap<const char*, int>::Iterator it = hashmap.begin(); it != hashmap.end(); it++) {
        std::cout<<(*it).first<<" : "<<(*it).second<<", ";
    }
    std::cout<<std::endl;

    for (HashMap<const char*, int>::constIterator it = hashmap.begin(); it != hashmap.end(); it++) {
        std::cout<<it->first<<" : "<<it->second<<", ";
    }

    return 0;
}