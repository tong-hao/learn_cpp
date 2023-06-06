#include <iostream>
#include <map>
#include <vector>

// Single Number II

// Given an array of integers, every element appears three times except for one.
// Find that single one. Note: Your algorithm should have a linear runtime
// complexity. Could you implement it without using extra memory?
//

class Solution1 {
public:
	int find(const std::vector<int>& vct) {
		std::map<int, int> stat;
		for (size_t i = 0; i < vct.size(); i++) {
			auto& count = stat[vct[i]];
			count++;
		}
		for (auto& [k, v] : stat) {
			if (v != 3)
				return k;
		}
		return -1;
	}
};

int main(int argc, char const* argv[]) {
	{
		std::vector<int> vct{1, 1, 1, 4, 2, 2, 2};

		Solution1 s;
		std::cout << s.find(vct) << std::endl;
	}

	return 0;
}
