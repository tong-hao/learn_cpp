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
  l1.push_back(4);
  l1.push_back(5);
  l1.push_back(6);
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

  print("## 关于splice");
  {
    print("把5拼接到开头");
    l1.splice(l1.begin(), l1, std::find(l1.begin(), l1.end(), 5));
    print(l1.begin(), l1.end());

    std::list<int> l2{1, 2, 3};
    std::list<int> l3{4, 5, 6};
    print("把l3拼到l2");
    l2.splice(l2.begin(), l3);
    print("l2:");
    print(l2.begin(), l2.end());
    print("l3:");
    print(l3.begin(), l3.end());
  }

  return 0;
}
