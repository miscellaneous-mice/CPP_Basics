#include <iostream>
#include <variant>
#include <vector>
#include <typeindex>

void func(int i) {
  std::cout << "Called func(int): " << i << std::endl;
}

void func(double d) {
  std::cout << "Called func(double): " << d << std::endl;
}

void func(const std::string& s) {
  std::cout << "Called func(string): " << s << std::endl;
}

template<typename T>
void print(T&& value) {
  std::cout<<"[Default] : Type of value : "<<typeid(value).name()<<", Value is : " << value <<std::endl;
}

template<>
void print<int>(int&& value) {
  std::cout<<"[INT] : Type of value : "<<typeid(value).name()<<", Value is : " << value <<std::endl;
}

template<>
void print<float>(float&& value) {
  std::cout<<"[FLOAT] : Type of value : "<<typeid(value).name()<<", Value is : " << value <<std::endl;
}

template<>
void print<double>(double&& value) {
  std::cout<<"[DOUBLE] : Type of value : "<<typeid(value).name()<<", Value is : " << value <<std::endl;
}

template<>
void print<long>(long&& value) {
  std::cout<<"[LONG] : Type of value : "<<typeid(value).name()<<", Value is : " << value <<std::endl;
}

int main() {
  std::vector<std::variant<int, double, std::string>> myVector = {1, 3.14, "Hello"};

  for (auto& element : myVector) {
    std::visit([](auto&& arg){
      std::cout<<"Type of variable is : "<<typeid(arg).name()<<std::endl;
      func(arg);
    }, element);
  }

  std::variant<int, double, float, long> variant_val = 1.05f;
  print(std::get<float>(variant_val));
  print(std::get<float>(variant_val));

  std::visit([](auto&& arg){
    using var_type = typename std::decay_t<decltype(arg)>;
    std::cout<<"The value is : "<<arg<<", Type is : "<< typeid(arg).name() << std::endl;
    print<var_type>((var_type&&)arg);
  }, variant_val);

  variant_val = 13248932L;

  std::visit([](auto&& arg){
    using var_type = typename std::decay_t<decltype(arg)>;
    std::cout<<"The value is : "<<arg<<", Type is : "<< typeid(arg).name() << std::endl;
    print((var_type&&)arg);
  }, variant_val);

  return 0;
}
