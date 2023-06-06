#include "Base.h"

#include <iostream>
#include <string>
#include <variant>

int main() {
  print("可以存放 int float string");
  std::variant<int, float, std::string> v;

  print("放int");
  v = 18;
  print("取int");
  std::cout << std::get<int>(v) << std::endl;
  std::cout << v.index() << std::endl;

  print("放string");
  v = "abc";
  print("取string");
  std::cout << std::get<std::string>(v) << std::endl;

  print("大小是多少呢？");
  std::cout << sizeof(v) << std::endl;

  std::variant<std::string> v2;
  std::cout << sizeof(v2) << std::endl;

  return 0;
}
