#include <array>
#include <iostream>
#include <cstring>
#include <typeinfo>
#include <typeindex>


constexpr std::array<const char*, 24> map_size_to_type()
{
	std::array<const char*, 24> table = { "" };
	table[sizeof(char)] = "CHAR";
	table[sizeof(int)] = "INT";
	table[sizeof(float)] = "FLOAT";
	table[sizeof(long)] = "LONG";
	table[sizeof(double)] =  "DOUBLE";
	return table;
}

constexpr std::array<const char*, 24> types = map_size_to_type();

template<typename T, const size_t N>
struct CustomArray {
    T arr[N];
    const T* start = arr;
    const T* final = arr + N;
    const T* begin() const { return start; }
    const T* end() const {return final; }
    const size_t size() const { return N; }
    const size_t elemSize() const { return sizeof(*start); }
    const T get(const size_t pos) const { return *(start +  pos); }
    const T getbyte(const size_t pos) const { return *(T*)((char*)start + (sizeof(T) * pos)); }
    const char* gettype() const { return types[sizeof(*(start))]; }
};

void WontChange(const int& num) {
    int* yikes = (int*)&num;
    *yikes = 25;
}

int main(){
    
    std::cout<<"Const override"<<std::endl;
    const int a = 5;
    std::cout<<"Number is : "<<a<<std::endl;
    int* b = (int*)&a;
    *b = 25;
    // WontChange(a);
    std::cout<<"Number got changed : "<<a<<std::endl;
    
    std::cout<<"Different pointer Initialization"<<std::endl;
    const int* a1 = new int(1); // same as int const* a = new int;
    std::cout<<"Address of a1 : "<<a1<<", Value of a1 : "<<*a1<<std::endl;
    int* const a2 = new int(2);
    std::cout<<"Address of a2 : "<<a2<<", Value of a1 : "<<*a2<<std::endl;
    const int* const a3 = new int(3);
    std::cout<<"Address of a3 : "<<a3<<", Value of a1 : "<<*a3<<std::endl;
    
    int* temp = (int*)a1;
    a1 = &a; // Value at the pointer is constant but the pointer address can be reassigned
    // *a1 = 2; // Error
    std::cout<<"Changed the pointer address of a1 : "<<a1<<", Value of a1 remains constant : "<<*temp<<std::endl;

    *a2 = 7; // Value at the pointer can be reassigned but the pointer address is constant
    //a2 = &a; // Error
    std::cout<<"Pointer address of a2 remains constant : "<<a2<<", Changed the value of a2 : "<<*a2<<std::endl;
    
    // *a3 = 2; // Error
    // a3 = &a; // Error 
    std::cout<<"Pointer address of a3 remains constant : "<<a3<<", Value of a3 remains constant : "<<*a3<<std::endl;
    
    std::cout<<"Array Pointers"<<std::endl;
    const size_t N = 5;
    int arr[N] = {1, 2, 3, 4, 5};
    int* begin = arr;
    int* end = arr + (N - 1);
    std::cout<<"Beginning Address : " << begin <<", Ending Address : " << end <<std::endl;
    std::cout<<"Beginning Value : " << *begin <<", Ending Value : " << *end <<std::endl;
    for (size_t i=0; i<N; i++) {
        std::cout<< "Pointer : " << begin << ", Value : " <<arr[i] <<std::endl;
        begin = begin + 1;
    }
    
    std::cout<<"Char Pointers" <<std::endl;
    char* name = "Joe Halden";
    char arr_name[] = "hullu bullu";
    const char* cname = "Kary Petty";
    char nt_name[10] = {'J', 'o', 'e', ' ', 'H', 'a', 'l', 'd', 'e', 'n'}; 
    char t_name[11] = {'J', 'o', 'e', ' ', 'H', 'a', 'l', 'd', 'e', 'n', 0};
    char* addr_nt_name = nt_name;
    char* addr_t_name = t_name;
    std::cout<<"Name : " << name << ", Length : " << strlen(name) <<std::endl;
    std::cout<<"Name : " << cname << ", Length : " << strlen(cname) <<std::endl;
    std::cout<<"Name : " << nt_name << ", Length : " << strlen(nt_name) <<std::endl;
    std::cout<<"Name : " << t_name << ", Length : " << strlen(t_name) <<std::endl;
    
    t_name[4] = 0;
    std::cout<<"Name : " << t_name << ", Length : " << strlen(t_name) <<std::endl;
    std::cout<< arr_name << std::endl;


    std::cout<<"Accessing elements"<<std::endl;
    CustomArray<float, 5> arr_fl = {1.0f, 5.34f, 3.21f, 6.54f, 0.04f};
    CustomArray<int, 5> arr_int = {1, 2, 3, 4, 5};
    CustomArray<char, 5> arr_ch = {'U', 'I', 'J', 'I', 'M', 0};
    CustomArray<double, 5> arr_db = {50032, 532843, 234873, 829384, 327891};


    std::cout<<arr_fl.get(2)<<std::endl;
    std::cout<<arr_fl.getbyte(2)<<std::endl;
    std::cout<<"Size of array : "<<arr_fl.size()<<", Size of each Element : "<<arr_fl.elemSize() << ", Type of each element : "<<arr_fl.gettype()<<std::endl;

    std::cout<<arr_db.get(4)<<std::endl;
    std::cout<<arr_db.getbyte(4)<<std::endl;
    std::cout<<"Size of array : "<<arr_db.size()<<", Size of each Element : "<<arr_db.elemSize()<< ", Type of each element : "<<arr_db.gettype()<<std::endl;
}

/*
- If you use double quotes to assign a string then the type is char*

- Compiler knows when the string ends for char* because the last element is automatically specified as null value.
  Hence when the compiler notices the null character it knows that string ends at that point.

- But when we manually specify the char string without the null character at the end then garbage values gets printed after the specified string.
*/