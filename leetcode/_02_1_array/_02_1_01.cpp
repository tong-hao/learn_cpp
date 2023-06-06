#include <algorithm>  // for_each
#include <iostream>
#include <vector>

/*
2.1.1 Remove Duplicates from Sorted Array

Given a sorted array, remove the duplicates in place such that each element
appear only once and return the new length. Do not allocate extra space for
another array, you must do this in place with constant memory. For example,
Given input array, Your function should return length = 2, and A is
now.
*/

class Solution1 {
public:
	int duplicate(std::vector<int>& data) {
		int index = 0;
		// for (int i = 1; i < data.size(); i++) {
		// 	if (data[index] != data[i]) {
		// 		data[++index] = data[i];
		// 	}
		// }
		std::for_each(data.begin(), data.end(), [&data, &index](int item) {
			if (data[index] != item) {
				data[++index] = item;
			}
		});

		return ++index;
	}
};

class Solution2 {
public:
	int duplicate(std::vector<int>& data) {
		return std::distance(data.begin(),
		                     std::unique(data.begin(), data.end()));
	}
};

class Solution3 {
public:
	int duplicate(std::vector<int>& data) {
		return std::distance(data.begin(), unique(data.begin(), data.end()));
	}

	template <typename Iter>
	Iter unique(Iter begin, Iter end) {
		auto output = begin;
		while (begin != end) {
			*output = *begin;
			begin = std::upper_bound(begin, end, *begin);
			output++;
		}
		return output;
	}
};

int main(int argc, char const* argv[]) {
	std::vector<int> data = {1, 1, 2, 2, 2, 4, 4, 5, 6, 6, 7};

	Solution3 s;
	auto result = s.duplicate(data);
	std::cout << result << std::endl;

	return 0;
}
