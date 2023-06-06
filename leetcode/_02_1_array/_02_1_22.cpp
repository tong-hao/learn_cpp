#include <iostream>
#include <map>
#include <vector>

// 2.1.22 Candy

// There are N children standing in a line. Each child is assigned a rating
// value. You are giving candies to these children subjected to the following
// requirements:
// • Each child must have at least one candy.
// • Children with a higher rating get more candies than their neighbors. What
// is the minimum candies you must give?

class Solution1 {
public:
	int find(const std::vector<int>& children) {
		int ret = children.size();
		std::cout << "init:" << ret << std::endl;

		std::map<int, int> m;
		for (size_t i = 0; i < children.size(); i++) {
			m[children[i]]++;
		}

		int k = 1;
		for (const auto& [rank, count] : m) {
			ret += (k * count);
			std::cout << "rank:" << rank << ", count:" << count
			          << ", ret:" << ret << std::endl;
			k++;
		}

		return ret;
	}
};

int main(int argc, char const* argv[]) {
	{
		std::vector<int> children{1, 2, 3, 1, 2, 3, 5, 1};
		Solution1 s;
		std::cout << s.find(children) << std::endl;
	}

	return 0;
}
