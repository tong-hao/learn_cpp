#include <iostream>
#include <vector>

// 2.1.18 Climbing Stairs

// You are climbing a stair case. It takes n steps to reach to the top.

// Each time you can either climb 1 or 2 steps. In how many distinct ways can
// you climb to the top?
//

class Solution1 {
public:
	int climbWays(int n) {
		if (n <= 0) {
			return 0;
		}
		if (n == 1) {
			return 1;
		}
		if (n == 2) {
			return 2;
		}

		return climbWays(n - 1) + climbWays(n - 2);
	}
};

class Solution2 {
public:
	int climbWays(int n) {
		if (n <= 0) {
			return 0;
		}

		int pre = 0;  // n = 0
		int cur = 1;  // n = 1
		for (size_t i = 1; i <= n; i++) {
			int temp = cur;
			cur += pre;
			pre = temp;
		}
		return cur;
	}
};

int main(int argc, char const* argv[]) {
	Solution1 s1;
	for (int i = 0; i < 5; i++) {
		std::cout << "i=" << i << ", ways:" << s1.climbWays(i) << std::endl;
	}

	Solution2 s2;
	for (int i = 0; i < 5; i++) {
		std::cout << "i=" << i << ", ways:" << s2.climbWays(i) << std::endl;
	}

	return 0;
}
