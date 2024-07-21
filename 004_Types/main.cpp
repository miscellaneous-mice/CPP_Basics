#include <iostream>

int main()
{
	int a = 8; // -2 Billion to +2 Billion are maximum values we can store in int. Default it is unsigned
	std::cout << a << std::endl;
	a = -20;
	std::cout << a << std::endl;

	char c = 'A';
	std::cout <<"\n"<< c << std::endl;
	c = 65;
	std::cout << c << std::endl;

	short s = 65;
	std::cout << "\n" << s << std::endl;

	int i = 'A';
	std::cout << "\n" << i << std::endl;

	float f = 5.5f; // It is a float but compiler treats it like a double. Add f for compiler to treat the variable like float (i.e. 4 bytes of data)
	double d = 4.4; // 8 bytes of data
	std::cout << "\n" << f << std::endl;
	std::cout << d << std::endl;

	bool b = true;
	std::cout << "\n" << b << std::endl;
	b = 1;
	std::cout << b << std::endl;

	std::cout << "Size of bool: " << sizeof(bool) << std::endl;
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