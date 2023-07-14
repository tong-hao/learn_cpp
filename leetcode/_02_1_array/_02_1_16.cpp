#include <iostream>
#include <vector>

#include "../utils/print.h"

// 2.1.16 Rotate Image

// You are given an n × n 2D matrix representing an image. Rotate the image by
// 90 degrees (clockwise).

// Follow up: Could you do this in-place?

class Solution1 {
public:
	void rotate(std::vector<std::vector<int>>& data) {
		const size_t n = data.size();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n - i; j++) {
				std::swap(data[i][j], data[n - 1 - j][n - 1 - i]);
			}
		}

		for (int i = 0; i < n / 2; i++) {
			for (int j = 0; j < n; j++) {
				std::swap(data[i][j], data[n - 1 - i][j]);
			}
		}
	}
};

int main(int argc, char const* argv[]) {
	std::vector<std::vector<int>> data{
	    {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

	for (const auto& vct : data) {
		print(vct.cbegin(), vct.cend());
	}
	std::cout << "======================" << std::endl;

	Solution1 s;
	s.rotate(data);

	for (const auto& vct : data) {
		print(vct.cbegin(), vct.cend());
	}

	return 0;
}
