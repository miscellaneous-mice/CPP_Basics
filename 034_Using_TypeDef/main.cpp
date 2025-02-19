// https://learn.microsoft.com/en-us/cpp/cpp/typename?view=msvc-170
#include <iostream>
#include <array>

template<typename T, size_t N>
struct Array {
    T arr[N];
    struct plane {
        T x[N], y[N];
    };
    const T* const begin() const { return arr; }
    const T* const end() const { return arr + N; }
}; 

typedef Array<int, 5> intArray5;
typedef Array<int, 10> intArray10;
typedef Array<float, 5> floatArray5;
typedef Array<float, 10> floatArray10;
template<typename T> using Array5 = Array<T, 5>;
template<typename T> using Array10 = Array<T, 10>;
using intplane5 = typename Array<int, 5>::plane;
template<typename T> using plane5 = typename Array<T, 5>::plane;
template<size_t N> using intplane = typename Array<int, N>::plane;
template<typename T, size_t N> using plane_t = typename Array<T, N>::plane; // https://stackoverflow.com/questions/51883423/c-using-and-using-typename-in-a-header-file

template<class T>
void Print(T arr) {
    using std::cout;
    for (auto elem : arr){
        cout<<elem<<", ";
    }
}

constexpr std::array<const char*, 256> morsemapping() {
    std::array<const char*, 256> morse = {};
    morse['A'] = "._";
    morse['B'] = "_...";
    morse['C'] = "_._.";
    morse['D'] = "_..";
    morse['E'] = ".";
    morse['F'] = ".._.";
    morse['G'] = "__.";
    morse['H'] = "....";
    morse['I'] = "..";
    morse['J'] = ".___";
    morse['K'] = "_._";
    morse['L'] = "._..";
    morse['M'] = "__";
    morse['N'] = "_.";
    morse['O'] = "___";
    morse['P'] = ".__.";
    morse['Q'] = "__._";
    morse['R'] = "._.";
    morse['S'] = "...";
    morse['T'] = "_";
    morse['U'] = ".._";
    morse['V'] = "..._";
    morse['W'] = ".__";
    morse['X'] = "_.._";
    morse['Y'] = "_.__";
    morse['Z'] = "__..";
    morse['0'] = "_____";
    morse['1'] = ".____";
    morse['2'] = "..___";
    morse['3'] = "...__";
    morse['4'] = "...._";
    morse['5'] = ".....";
    morse['6'] = "_....";
    morse['7'] = "__...";
    morse['8'] = "___..";
    morse['9'] = "____.";
    return morse;
}

struct Foo {
    struct Elements {
        int a;
        float b;
        const char* c;
        long d;
    };
    struct MorseCode {
        constexpr static std::array<const char*, 256> morsecode = morsemapping();
        const char* operator[](size_t index) const { return MorseCode::morsecode[index]; }
    };
}; typedef Foo::MorseCode Morse;


int main() {
    using namespace std;
    intArray5 arr1 = {1, 2, 3, 4, 5};
    Print<intArray5>(arr1);
    cout<<endl;

    intArray10 arr2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Print<intArray10>(arr2);
    cout<<endl;

    floatArray5 arr3 = {1.0f, 2.3293f, 3.324f, 4.324f, 5.384f};
    Print<floatArray5>(arr3);
    cout<<endl;

    floatArray10 arr4 = {1.0f, 2.3293f, 3.324f, 4.324f, 5.384f, 3.32489f, 3.09324f, 9.432897f, 8.32489f, 2.32487f};
    Print<floatArray10>(arr4);
    cout<<endl;

    Array5<float> arr5 = {1.00f, 2.13f, 3.45f, 4.33f, 5.123f};
    Print<Array5<float>>(arr5);
    cout<<endl;

    Array10<long> arr6 = {1000L, 53000L, 24000L, 143284L, 45892L};
    Print<Array10<long>>(arr6);
    cout<<endl;

    Foo::Elements var = {1, 4.53f, "funny", 5003442L};
    std::cout<<var.a<<", "<<var.b<<", "<<var.c<<", "<<var.d<<std::endl;

    Morse morse;
    std::cout<<morse['A']<<std::endl;


    intplane5 plane1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    plane5<float> plane2 = {1.0f, 2.2f, 3.40f, 4.23f, 5.043f, 6.324f, 7.324f, 8.893f, 9.384f, 10.347f};
    intplane<7> plane3 = {1, 2, 3, 4, 5, 6, 7};
}