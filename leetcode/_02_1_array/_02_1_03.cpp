#include <algorithm>
#include <iostream>
#include <vector>

// 2.1.3 Search in Rotated Sorted Array
//
// Suppose a sorted array is rotated at some pivot unknown to you beforehand.
// (i.e., 1234567 might become 4567123).
// You are given a target value to search. If found in the array return its
// index, otherwise return -1. You may assume no duplicate exists in the array.

class Solution1 {
public:
	int find(const std::vector<int>& vct, int target) {
		int start = 0;
		int end = vct.size() - 1;
		while (start <= end) {
			int mid = (end - start) / 2 + start;
			// std::cout << start << "," << end << ", mid=" << mid << std::endl;
			if (vct[mid] == target) {
				return mid;
			}
			if (vct[mid] > vct[start]) {  // inscr in left half
				if (target >= vct[start] && target < vct[mid]) {
					end = mid - 1;
				} else {
					start = mid + 1;
				}
			} else {  // inscr in right half
				if (target > vct[mid] && target <= vct[end]) {
					start = mid + 1;
				} else {
					end = mid - 1;
				}
			}
		}
		return -1;
	}
};

int main(int argc, char const* argv[]) {
	// std::vector<int> vct = {4, 5, 1, 2, 3};
	std::vector<int> vct = {4, 5, 6, 7, 1, 2, 3};

	Solution1 s;
	std::for_each(vct.begin(), vct.end(), [&vct, &s](auto item) {
		int idx = s.find(vct, item);
		std::cout << idx << std::endl;
	});

	return 0;
}
