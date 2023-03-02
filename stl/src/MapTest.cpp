#include <algorithm>
#include <map>

#include "Base.h"

int main() {
  std::map<char, int> m1;
  print("添加元素");
  m1.emplace('a', 1);
  m1.emplace('b', 2);
  m1.insert(std::make_pair<char, int>('c', 3));
  print(m1.begin(), m1.end());

  print("查找b");
  auto it = m1.find('b');
  if (it != m1.end())
    print(it->second);

  print("修改b");
  it->second = 20;
  print(m1.begin(), m1.end());

  print(">=a 的第一个元素");
  auto it1 = m1.lower_bound('a');
  print(*it1);
  print(">a 的第一个元素");
  auto it2 = m1.upper_bound('a');
  print(*it2);

  return 0;
}
