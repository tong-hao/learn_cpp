#include <algorithm>
#include <list>

#include "Base.h"

int main() {
  std::list<int> l1;

  print("在前面添加：1，2，3");
  l1.push_front(1);
  l1.push_front(2);
  l1.push_front(3);
  print(l1.begin(), l1.end());

  print("在后面添加：4，5，6");
  l1.push_back(1);
  l1.push_back(2);
  l1.push_back(3);
  print(l1.begin(), l1.end());

  print("查找2");
  auto it = std::find(l1.begin(), l1.end(), 2);

  print("修改2为20");
  *it = 20;
  print(l1.begin(), l1.end());

  print("在20后面插入30");
  l1.insert(it, 30);
  print(l1.begin(), l1.end());

  print("删除20");
  l1.erase(it);
  print(l1.begin(), l1.end());

  return 0;
}
