#include <iostream>
#include <vector>

// 2.1.4 Search in Rotated Sorted Array II（数组有重复）

// Follow up for ”Search in Rotated Sorted Array”: What if duplicates are
// allowed? Would this affect the run-time complexity? How and why? Write a
// function to determine if a given target is in the array.

class Solution1 {
public:
	int find(const std::vector<int>& vct, int target) {
		return -1;
	}
};

int main(int argc, char const* argv[]) {
	{
		std::vector<int> vct = {1, 2, 2, 3, 1};
		Solution1 s;
		s.find(vct, 1);
	}

	return 0;
}
