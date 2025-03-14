#include <iostream>
#include <typeinfo>
#include <any>

int main()
{
	std::cout<<"-------------int type<-------------"<<std::endl;
	int a = 8; // -2 Billion to +2 Billion are maximum values we can store in int. Default it is unsigned
	std::cout << a << std::endl;
	a = -20;
	std::cout << a << std::endl;
	a = 'A';
	std::cout << "\n" << a << std::endl;

	std::cout<<"-------------char type<-------------"<<std::endl;
	char c = 'A';
	std::cout <<"\n"<< c << std::endl;
	c = 65;
	std::cout << c << std::endl;

	std::cout<<"-------------short type<-------------"<<std::endl;
	short s = 65;
	std::cout << "\n" << s << std::endl;

	std::cout<<"-------------float type<-------------"<<std::endl;
	float f = 5.5f; // It is a float but compiler treats it like a double. Add f for compiler to treat the variable like float (i.e. 4 bytes of data)
	double d = 4.4; // 8 bytes of data
	std::cout << "\n" << f << std::endl;
	std::cout << d << std::endl;

	std::cout<<"-------------bool type<-------------"<<std::endl;
	bool b = true;
	std::cout << "\n" << b << std::endl;
	b = 1;
	std::cout << b << std::endl;

	std::cout<<"-------------void type<-------------"<<std::endl;
	void* typeless;
	typeless = &a;
	std::cout<<"Value is : "<<static_cast<int*>(typeless)<<std::endl;
	// std::cout<<"Value is : "<<*(int*)typeless<<std::endl;

	typeless = &c;
	std::cout<<"Value is : "<<static_cast<char*>(typeless)<<std::endl;
	// std::cout<<"Value is : "<<*(char*)typeless<<std::endl;

	std::cout<<"-------------auto type<-------------"<<std::endl;
	// Compiler tries to deduce the type using the initlialization
    auto x = 10;         // x is of type int
    auto y = 3.14;       // y is of type double
    auto z = "hello";    // s is of type const char*
	std::cout<<"Value : "<<x<<", Type: "<<typeid(x).name()<<std::endl;
	std::cout<<"Value : "<<y<<", Type: "<<typeid(y).name()<<std::endl;
	std::cout<<"Value : "<<z<<", Type: "<<typeid(z).name()<<std::endl;

	std::cout << "Size of bool: " << sizeof(bool) << std::endl;

	std::cout<<"-------------std::any type<-------------"<<std::endl;
	// std::any means that variable will take the type it will be assigned
    std::any var;
    var = "10";

	// To store the typeinfo using this std::type_info keyword
    const std::type_info& type = var.type();

	// But when accessing the std::any variable make sure to cast it back to the last variable it was assigned to
    std::cout<<"Value is : "<<std::any_cast<const char*>(var)<<std::endl;
    if (type == typeid(int)){
        std::cout << "Type of variable is : int"<<std::endl;
    }
    else if (type == typeid(float)){
        std::cout << "Type of variable is : float"<<std::endl;
    }
    else if (type == typeid(std::string) or type == typeid(const char*)){
        std::cout << "Type of variable is : string"<<std::endl;
    }
    else {
        std::cout<<"Unknown type"<<std::endl;
    }

	std::cout<<"-------------std::any type<-------------"<<std::endl;
	std::string str = "Hello world";
	size_t size = str.length();
	std::cout<<"The size of the string is : "<<size<<std::endl;

	size_t pos1 = str.find("o", 0);
	size_t pos2 = str.find("o", pos1 + 1);
	std::cout<<"The character is located at : "<<pos1<<" , "<<pos2<<std::endl;

	std::cout<<"------------decltype-------------"<<std::endl;
	int x1 = 5;
	decltype(x1) x2 = 10;
	std::cout<<"Type of x1 : "<<typeid(x1).name()<<", Value : "<<x1<<std::endl;
	std::cout<<"Type of x2 : "<<typeid(x2).name()<<", Value : "<<x2<<std::endl;
}


/*
Variable is a piece of memory or data we store using a name, hence can use this data multiple times

Types of Variables are:

 - int : integer (4 bytes). Size of int depends on the compiler

 - signed means +ve and -ve values

 - 4 bytes = 32 bits (1 bit is used for storing sign of value) hence 31 bits. 2^31 is close to 2 Billion (which is the maximum value we can store in int 
   variable. Other 2 Billion values are -ve values.

 - unsigned means only +ve values. Here all 32 bits are used for storing data (i.e.) number. 2^32 is close 4 Billion

 - https://www.programiz.com/cpp-programming/examples/sizeof-operator : to see all variable types size

 - we give variable names so as to treat each data as a character or number when given to cout or any other function.

 - Only real difference between data types is size, not the type. Type is upto programmer what they wanna do with the data and variable type.

 - We can only address bytes of information. Not a single bit on information. Hence why bool data type is 1 byte. Even though it is just 1 bit of data.
*/