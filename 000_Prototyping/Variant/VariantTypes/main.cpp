#include <iostream>
#include <variant>
#include <vector>
#include <typeindex>
#include <string>

using Arg = std::variant<int, double, std::string>;

void get_type(const Arg& arg) {
    if (std::holds_alternative<int>(arg))
      std::cout<<"int type"<<std::endl;
    else if (std::holds_alternative<double>(arg))
      std::cout<<"double type"<<std::endl;
    else if (std::holds_alternative<std::string>(arg))
      std::cout<<"string type"<<std::endl;
    else
      std::cout<<"Unknown type"<<std::endl;
}

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
  
  auto get_types = [](auto&&... args) mutable {
    ((get_type(args)), ...);
  };

  get_types(
    12342,
    234578.344,
    std::string("x01"),
    std::string("dsfkj3242k3l")
  );
  return 0;
}
