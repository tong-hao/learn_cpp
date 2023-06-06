#include <bitset>

#include "Base.h"

int main() {
  std::bitset<8> b1;
  print(b1.to_string());

  print("将第0位置为1");
  b1.set(0);
  print(b1.to_string());

  print("将所有位置为1");
  b1.reset(1);
  print(b1.to_string());

  print("统计1的数量");
  print(b1.count());

  std::bitset<8> b2(3);
  print("3的bitset");
  print(b2.to_string());

  std::bitset<8> b3(std::string("00001111"));
  print("00001111对应的int值");
  print(b3.to_ulong());

  return 0;
}
