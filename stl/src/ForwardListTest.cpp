#include <algorithm>
#include <forward_list>

#include "Base.h"

int main() {
  std::forward_list<int> l1;

  print("添加：1，2，3");
  l1.push_front(1);
  l1.push_front(2);
  l1.push_front(3);
  print(l1.begin(), l1.end());

  print("查找2");
  auto it = std::find(l1.begin(), l1.end(), 2);

  print("修改2为20");
  *it = 20;
  print(l1.begin(), l1.end());

  print("在20后面插入30");
  l1.insert_after(it, 30);
  print(l1.begin(), l1.end());

  print("删除20后面的一个元素");
  l1.erase_after(it);
  print(l1.begin(), l1.end());

  return 0;
}
