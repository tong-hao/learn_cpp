#include <iostream>
#include <vector>

#include "../utils/print.h"

// 2.1.17 Plus One

// Given a number represented as an array of digits, plus one to the number.
//

class Solution1 {
public:
	void plus(std::vector<int>& vct, int num) {
		int carry = num;
		for (size_t i = vct.size() - 1; i >= 0;) {
			vct[i] += carry;
			carry = vct[i] / 10;
			vct[i] = vct[i] % 10;

			if (i == 0) {
				break;
			}
			i--;
		}

		if (carry > 0) {
			vct.insert(vct.begin(), carry);
		}
	}
};

int main(int argc, char const* argv[]) {
	{
		std::vector<int> num{1, 3, 5, 9, 9};
		Solution1 s;
		s.plus(num, 2);

		print(num.begin(), num.end());
	}

	return 0;
}
