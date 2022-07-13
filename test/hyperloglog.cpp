#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <map>

std::map<int, int> log_cout;
const int prefix_max_num = 10;
const int endfix_max_num = 10000000;

int nextInt(int start = 10001234, int end = 99901129) {
	return rand() % (end - start) + start;
}

void addOne(int one) {
	if (one < 0) {
		one = 0 - one;
	}

	int prefix = one;
	while (prefix >= prefix_max_num) {
		prefix = prefix / 10;
	}

	int one_copy = one;
	int end_0_count = 1;
	while (one_copy % 10 == 0) {
		end_0_count *= 10;
		one_copy = one_copy / 10;
		if (one_copy == 0) {
			break;
		}
	}
	if (end_0_count >= endfix_max_num) {
		return;
	}

	if (log_cout[prefix] < end_0_count) {
		log_cout[prefix] = end_0_count;
	} else if (log_cout[prefix] == end_0_count) {
		log_cout[prefix] += end_0_count;
	}
}

int main(int argc, char const *argv[]) {
	std::srand(std::time(nullptr));
	for (size_t i = 0; i < 300000; i++) {
		addOne(nextInt());
	}

	int total = 0;
	for (auto [k, v] : log_cout) {
		std::cout << k << "\t" << v << std::endl;
		total += v;
	}
	total /= prefix_max_num;
	std::cout << total << std::endl;

	return 0;
}

// link:-std=c++17
