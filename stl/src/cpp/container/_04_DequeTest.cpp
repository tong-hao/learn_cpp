#include <deque>

#include "Base.h"

int main() {
  std::deque<int> q1;
  print("进入1，2");
  q1.push_back(1);
  q1.push_back(2);
  print(q1.begin(), q1.end());

  print("插入3");
  q1.insert(q1.begin(), 3);
  print(q1.begin(), q1.end());

  print("队头");
  print(q1.front());
  print("队尾");
  print(q1.back());

  print("从对头删除一个元素");
  q1.pop_front();
  print(q1.begin(), q1.end());

  print("从队尾删除一个元素");
  q1.pop_back();
  print(q1.begin(), q1.end());

  return 0;
}
