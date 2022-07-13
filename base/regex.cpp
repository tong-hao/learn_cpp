#include <iostream>
#include <string>
#include <regex>

int main ()
{
  std::string s ("/help/1");
  std::smatch m;
  std::regex e ("^(/help/)");
  std::cout << std::regex_search (s,m,e) << std::endl;
  //for (auto x:m) std::cout << x << " ";
	
  while (std::regex_search (s,m,e)) {
    for (auto x:m) std::cout << x << " ";
    std::cout << std::endl;
    s = m.suffix().str();
  }

  return 0;
}
