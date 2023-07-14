#include <iostream>
#include <vector>

// 2.1.19 Gray Code

// The gray code is a binary numeral system where two successive values differ
// in only one bit.

// Given a non-negative integer n representing the total number of bits in the
// code, print the sequence of gray code. A gray code sequence must begin with
// 0.

// For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:

// 00 - 0
// 01 - 1
// 11 - 3
// 10 - 2

// Note:
// • For a given n, a gray code sequence is not uniquely defined.
// • For example, [0,2,3,1] is also a valid gray code sequence according to the
// above definition.
// • For now, the judge is able to judge based on one instance of gray code
// sequence. Sorry about that.

class Solution1 {
public:
	std::vector<int> grayCode(int n) {
		auto toGrayCode = [](int num) { return num ^ (num >> 1); };

		std::vector<int> ret;
		for (int i = 0; i < (1 << n); i++) {
			ret.push_back(toGrayCode(i));
		}
		return ret;
	}
};

int main(int argc, char const* argv[]) {
	Solution1 s;
	for (int code : s.grayCode(4)) {
		std::cout << code << std::endl;
	}

	return 0;
}
