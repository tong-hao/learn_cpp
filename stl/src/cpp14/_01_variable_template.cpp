#include <iostream>
#include <vector>

// 1. 定义一个变量pi，它的类型为T
template <typename T> T pi = T(3.1415926);

// 2. 定义一个静态模版变量
struct limits {
  template <typename T>
  static const T min; // declaration of a static data member template
};
template <typename T>
const T limits::min = {1}; // definition of a static data member template

int main() {
  // 1.
  float p1 = pi<float>;
  double p2 = pi<double>;
  std::cout << p1 << " " << p2 << std::endl;

  // 2.
  int minInt = limits::min<int>;          // 获取int类型的最小值
  double minDouble = limits::min<double>; // 获取double类型的最小值
  std::cout << minInt << " " << minDouble << std::endl;

  return 0;
}
