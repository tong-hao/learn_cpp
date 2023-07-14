#include <iostream>
#include <vector>

// 2.1.20 Set Matrix Zeroes

// Given a m × n matrix, if an element is 0, set its entire row and column to 0.
// Do it in place. Follow up: Did you use extra space?

// A straight forward solution using O(mn) space is probably a bad idea.

// A simple improvement uses O(m + n) space, but still not the best solution.

// Could you devise a constant space solution?

class Solution1 {
public:
	void set(std::vector<std::vector<int>>& matrix) {
		if (matrix.empty()) {
			return;
		}

		std::vector<bool> rows(matrix.size(), false);
		std::vector<bool> cols(matrix[0].size(), false);
		for (size_t i = 0; i < rows.size(); i++) {
			for (size_t j = 0; j < cols.size(); j++) {
				if (matrix[i][j] == 0) {
					rows[i] = true;
					cols[j] = true;
					std::cout << "i=" << i << ", j=" << j << std::endl;
				}
			}
		}

		// 标记一整行为0
		for (size_t i = 0; i < rows.size(); i++) {
			if (rows[i]) {
				for (size_t j = 0; j < cols.size(); j++) {
					matrix[i][j] = 0;
				}
			}
		}

		// 标记一列为0
		for (size_t i = 0; i < cols.size(); i++) {
			if (cols[i]) {
				for (size_t j = 0; j < rows.size(); j++) {
					matrix[j][i] = 0;
				}
			}
		}
	}
};

int main(int argc, char const* argv[]) {
	{
		std::vector<std::vector<int>> matrix{
		    {1, 2, 3, 4}, {5, 6, 7, 8}, {0, 10, 11, 12}};

		Solution1 s;
		s.set(matrix);

		for (size_t i = 0; i < matrix.size(); i++) {
			for (size_t j = 0; j < matrix[0].size(); j++) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	return 0;
}
