#include <iostream>

int Multiply(int a, int b)
{
	return a * b;
}

void no_params()
{
	std::cout << 5 * 8 << std::endl;
}

void MultiplyAndLog(int a = 1, int b = 1) {

	int result = Multiply(a, b);
	std::cout << result << std::endl;

}

int main()
{
	MultiplyAndLog(10, 5);

	MultiplyAndLog(4, 7);

	MultiplyAndLog();

	no_params();
}
/*

- Functions are mainly used to avoid code duplication

- Type we define our function is the return value it would give (int function -> return value is int)

- void function means function will not return anything

- Many functions make code slower as:
  > We first need to make a stack for the function in memory
  > We need to push parameters into the stack
  > We need to also push return address into the stack
  > We jump to a different part of the binary to start executing the code
  > After returning we need to come back to where we left the computer off in the binary
  > We do a lot of jumping back and forth after we call a function -> takes time

*/