#include <assert.h>
#include <stdio.h>

// assert() 宏接受一个参数，即要检查的条件。如果该条件为真，assert()
// 宏不做任何事情。如果该条件为假，assert() 宏将终止程序并打印一条错误消息。

int main() {
  int *p = NULL;
  assert(p != NULL); // 检查指针是否为 NULL
  return 0;
}
