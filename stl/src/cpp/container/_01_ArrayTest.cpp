#include <algorithm>
#include <array>

#include "Base.h"

int main() {
  std::array<int, 6> arr1;

  print("全部填充0");
  arr1.fill(0);
  print(arr1.begin(), arr1.end());

  print("大小是多少?");
  print(arr1.size());

  print("修改第2个元素");
  arr1[1] = 3;
  print(arr1.begin(), arr1.end());

  print("查找3");
  auto it = std::find(arr1.begin(), arr1.end(), 3);
  print("存在3吗？");
  print(it != arr1.end());

  if (it != arr1.end())
    *it = 4;

  return 0;
}
