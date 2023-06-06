#include <iostream>
#include <vector>

// 2.1.23 Single Number

// Given an array of integers, every element appears twice except for one. Find
// that single one.

// Note: Your algorithm should have a linear runtime complexity. Could you
// implement it without using extra memory?
//

class Solution1 {
public:
	int find(const std::vector<int>& vct) {
		int result = 0;
		for (size_t i = 0; i < vct.size(); i++) {
			result ^= vct[i];
		}
		return result;
	}
};

int main(int argc, char const* argv[]) {
	{
		std::vector<int> vct{1, 1, 2, 3, 2, 4, 5, 4, 5};

		Solution1 s;
		std::cout << s.find(vct) << std::endl;
	}

	return 0;
}
