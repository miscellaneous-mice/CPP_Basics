#include <iostream>
#include <iomanip>
#include <ranges>

class Entity {
private:
    std::string m_Name;
    int m_Age;
public:
    Entity(const char* name) : m_Name(name), m_Age(-1) {};
    explicit Entity(int age): m_Name("Unknown"), m_Age(age) {};
    void info() const {
        std::cout<<"Name : "<<m_Name<<"\nAge : "<<m_Age<<std::endl;
    }
};

template<typename T>
struct Array {
    T* array;
    size_t N;

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

    T* begin() { return array; }
    T* end() { return array + N; }

    const T* begin() const { return array; }
    const T* end() const { return array + N; }
};

template<typename K, typename V, template<typename> typename C = Array>
struct hmap {
    C<K> key;
    C<V> value;
};

void Print(const Entity& e){
    e.info();
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Array<T>& array) {
    for(auto element : array)
       std::cout<<std::setprecision(2)<<element<<" ";
    return stream;
}

int main() {
    Entity e1 = "Hose"; // Implicit conversion done by compiler
    Entity e2 = Entity(10); // Explicit conversion done by author to eliminate implicit conversion types
    Print("Hose");
    Print((Entity)10);

    Array<float> arr1;
    arr1.pushback(1.348f);
    arr1.pushback(2.3434f);
    std::cout<<arr1<<std::endl;

    Array<double> arr2 = Array<double>(arr1);
    arr2.pushback(43324);
    std::cout<<arr2<<std::endl;
    
}