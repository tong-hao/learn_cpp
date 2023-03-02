#include <iostream>
#include <map>
#include <vector>

template <typename T> void print(const T &t) { std::cout << t << std::endl; }

template <typename T> void print(const std::vector<T> &vct) {
  for (auto &i : vct) {
    std::cout << i << ",";
  }
  std::cout << std::endl;
}

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}

template <typename T> void print(T begin, T end) {
  for (auto i = begin; i != end; i++) {
    std::cout << *i << ",";
  }
  std::cout << std::endl;
}

/*template <typename K, typename V>
void print(typename std::map<K, V>::iterator b,
           typename std::map<K, V>::iterator e) {
  for (auto i = b; i != e; i++) {
    std::cout << i->first << "," << i->second << std::endl;
  }
}*/
