#include <set>

#include "Base.h"

int main() {
  std::set<int> s;

  print("添加：1，2, 5");
  s.emplace(1);
  s.emplace(2);
  s.emplace(5);
  print(s.begin(), s.end());

  print("查找2，并修改为20");
  auto it = s.find(2);
  if (it != s.end()) {
    //*it = 20;// 注意：不能修改
  }
  print(s.begin(), s.end());

  print("插入4");
  s.insert(it, 4);
  print(s.begin(), s.end());

  return 0;
}
