#include <iostream>
#include <vector>
#include <algorithm>

#include "Base.h"

int main() {
  std::vector<int> vct1;
  
  print("添加元素: 1,2");
  vct1.push_back(1);
  vct1.push_back(2);
  print("插入元素：3");
  vct1.insert(vct1.begin(), 3);
  print(vct1);

  print("查找元素：2");
  auto it = std::find(vct1.begin(), vct1.end(), 2);
  std::cout << "结果： " << (it != vct1.end()) << std::endl;

  print("将2改为5");
  *it = 5;
  print(vct1);

  print("构建一个新的vector");
  std::vector<int> vct2(vct1.begin(), vct1.end());
  print("vct2的元素：");
  print(vct2);

  print("删除前两个元素");
  vct1.erase(vct1.begin(), vct1.begin() + 2);
  print(vct1);

  print("clear所有元素");
  vct1.clear();
  print("元素剩余个数为：");
  print(vct1.size());

  print("访问vct2的第三个元素");
  print(vct2[1]);
  print(vct2.at(1));

  print("第一个元素");
  print(vct2.front());
  print("最后一个元素");
  print(vct2.back());



  return 0;
}
