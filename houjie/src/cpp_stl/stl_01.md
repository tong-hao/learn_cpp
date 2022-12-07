# STL
使用一个东西，却不明白它的道理，不高明！

## 网站推荐
cplusplus.com
cppreference.com
gcc.gnu.org
《The c++ standard library》
《stl源码剖析》

## STL六大部件
Container 容器
Allocators 分配器
Algorithms 算法
Iterator 迭代器
Adapters 适配器
Functors 仿函数

## 一个例子
```
#include <vector>
#include <algorithm>

int ia[6] ={};
vector<int, allocator<int>> vi(ia, ia+6);
cout << count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40)));
```

## Big-oh
O(c)
O(n)
O(log2n)
O(n2)
O(n3)
O(2n)
O(nlog2n)

## 区间
前闭后开，c.begin(), c.end() 注：c的end()是不包含元素的。


## sequence containers
array 固定大
vector 自动扩充
deque 双向队列，两边可进可出
list 链表
forward list 单向链表

## associative containers
set
multiset 元素可重复
map
multimap 元素可重复

## unordered containers
（实现 hash table）
unordered_set
unordered_map
unordered_multiset
unordered_multimap

