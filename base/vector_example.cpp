#include <vector>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{

	std::string s = "abc";

	std::vector<std::string> v;
	v.emplace_back(s);

	for(auto i = 0; i < v.size(); i++) {
		std::cout << v[i] << std::endl;
	}

	return 0;
}