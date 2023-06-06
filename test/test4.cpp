#include <algorithm>
#include <cstring>
#include <ctime>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <utility>
#include <vector>

int main() {
	{
		char* p = "abc\0abc";
		std::cout << strlen(p) << std::endl;

		char* p2 = "abc";
		std::cout << strlen(p2) << std::endl;
	}

	return 0;
}
