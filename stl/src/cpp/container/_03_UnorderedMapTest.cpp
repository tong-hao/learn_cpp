#include <algorithm>
#include <unordered_map>

#include "Base.h"

// unordered_map 是hashmap，O(1)，是无需的
// map是红黑树

int main() {
  std::unordered_map<char, int> m1;
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

  return 0;
}
