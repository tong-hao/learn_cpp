#include <iostream>
#include <vector>

// 2.1.14 Valid Sudoku

class Solution1 {
public:
	Solution1(const std::vector<std::vector<int>>& data) : data_(data) {
	}

	bool valid() {
		// 检测行
		for (int i = 0; i < 9; i++) {
			std::vector<bool> flags{false};
			for (int j = 0; j < 9; j++) {
				if (data_[i][j] > 9 || data_[i][j] < 1 || flags[data_[i][j]]) {
					return false;
				}
				flags[data_[i][j]] = true;
				// std::cout << i << "," << j << std::endl;
			}
		}
		// std::cout << "\n\n" << std::endl;

		// 检查列
		for (int i = 0; i < 9; i++) {
			std::vector<bool> flags{false};
			for (int j = 0; j < 9; j++) {
				if (data_[j][i] > 9 || data_[j][i] < 1 || flags[data_[j][i]]) {
					return false;
				}
				flags[data_[j][i]] = true;
				// std::cout << i << "," << j << std::endl;
			}
		}
		// std::cout << "\n\n" << std::endl;

		// 检查3*3
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				std::vector<bool> flags{false};
				for (int i = x * 3; i < x * 3 + 3; i++) {
					for (int j = y * 3; j < y * 3 + 3; j++) {
						if (flags[data_[i][j]]) {
							return false;
						}
						flags[data_[i][j]] = true;
						// std::cout << i << "," << j << std::endl;
					}
				}
				// std::cout << "\n" << std::endl;
			}
		}
		return true;
	}

private:
	std::vector<std::vector<int>> data_;
};

int main(int argc, char const* argv[]) {
	{
		std::vector<std::vector<int>> data{
		    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {2, 3, 4, 5, 6, 7, 8, 9, 0},
		    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {2, 3, 4, 5, 6, 7, 8, 9, 0},
		    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {2, 3, 4, 5, 6, 7, 8, 9, 0},
		    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {2, 3, 4, 5, 6, 7, 8, 9, 0},
		    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};

		Solution1 s(data);
		std::cout << s.valid() << std::endl;
	}

	return 0;
}
