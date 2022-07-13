#include <iostream>
#include <vector>

int main(int argc, const char *argv[]) {
	std::vector<int> vct;
	vct.push_back(1);
	vct.push_back(2);
	vct.push_back(3);

	std::cout << vct.back() << std::endl;

	return 0;
}

// link: --std=c++11
