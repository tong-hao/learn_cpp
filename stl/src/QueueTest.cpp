#include <queue>

#include "Base.h"

int main() {
  std::queue<int> q1;

  print("入队列：1，2，3");
  q1.push(1);
  q1.push(2);
  q1.push(3);

  print("出队");
  while (!q1.empty()) {
    print(q1.front());
    q1.pop();
  }

  print("队列大小：");
  print(q1.size());

  return 0;
}
