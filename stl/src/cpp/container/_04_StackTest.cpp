#include <stack>

#include "Base.h"

int main() {
  std::stack<int> q1;

  print("入栈：1，2，3");
  q1.push(1);
  q1.push(2);
  q1.push(3);

  print("出栈");
  while (!q1.empty()) {
    print(q1.top());
    q1.pop();
  }

  print("栈大小：");
  print(q1.size());

  return 0;
}
