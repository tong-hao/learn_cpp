#include <iostream>

template <typename To, typename From> auto convert(From &&from) {
  return [](auto &&value) -> To {
    return static_cast<To>(std::forward<decltype(value)>(value));
  }(std::forward<From>(from));
}

int main() {
  // 1. auto is used as a type of a parameter
  auto f1 = [](auto num1, auto num2) { return num1 > num2 ? num1 : num2; };
  std::cout << f1(1, 1.2) << std::endl;

  // 2. 泛型lambda
  int i = convert<int, double>(3.14);
  std::cout << i << std::endl;

  // 3. lambda init-capture
  int x = 0;
  auto f1 = [y = x + 1]() { return y };

  return 0;
}
