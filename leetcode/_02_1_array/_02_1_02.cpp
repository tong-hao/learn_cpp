#include <algorithm>
#include <iostream>
#include <vector>

// 2.1.2 Remove Duplicates from Sorted Array II (允许重复两次)
//
// Follow up for ”Remove Duplicates”: What if duplicates are allowed at most
// twice? For example, Given sorted array A=[1,1,1,2,2,3], Your function
// should return length = 5, and A is now [1,1,2,2,3]

template <typename Iter>
void print(Iter begin, Iter end) {
	while (begin != end) {
		std::cout << *begin << ", ";
		begin++;
	}
	std::cout << std::endl;
}

class Solution1 {
public:
	int removeDuplicates(std::vector<int>& data) {
		int index = 0;
		int count = 0;
		int current_item = data[0];
		for (int i = 1; i < data.size(); i++) {
			if (current_item != data[i]) {
				count = 0;
				current_item = data[i];
			}
			count++;
			if (count <= 2) {
				data[index++] = data[i];
			}
		}
		return index;
	}
};

int main(int argc, char const* argv[]) {
	std::vector<int> data = {1, 1, 1, 1, 2, 2, 2, 4, 4, 5, 6, 6, 7};

	print(data.begin(), data.end());

	Solution1 s;
	int r = s.removeDuplicates(data);
	std::cout << r << std::endl;
	print(data.begin(), data.end());

	return 0;
}
