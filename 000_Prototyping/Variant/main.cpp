#include <iostream>
#include <variant>
#include <vector>

void func(int i) {
  std::cout << "Called func(int): " << i << std::endl;
}

void func(double d) {
  std::cout << "Called func(double): " << d << std::endl;
}

void func(const std::string& s) {
  std::cout << "Called func(string): " << s << std::endl;
}

int main() {
  std::vector<std::variant<int, double, std::string>> myVector = {1, 3.14, "Hello"};

  for (auto& element : myVector) {
    std::visit([](auto&& arg){ func(arg); }, element);
  }

  return 0;
}
