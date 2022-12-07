#include <atomic>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

int main(int argc, char const* argv[]) {
	clock_t t1 = clock();

	std::vector<int> active_current;
	std::vector<int> active_next;
	active_current.reserve(100);
	active_next.reserve(100);
	std::cout << (clock() - t1) << std::endl;

	for (int i = 0; i < 100000; i++) {
		active_current.emplace_back(i + 1);
		active_next.emplace_back(i + 5);
	}
	std::cout << (clock() - t1) << std::endl;
	auto s = active_current.size();
	std::cout << (clock() - t1) << ", " << s << std::endl;

	std::swap(active_next, active_current);
	std::cout << (clock() - t1) << std::endl;

	std::cout << "-------" << std::endl;

	clock_t t2 = clock();
	std::set<int> set;
	for (int i = 0; i < 35901623; i++) {
		if (set.find(100) == set.end()) {
			set.insert(i);
		}
	}

	clock_t t3 = clock();
	std::cout << (t3 - t2) / 1000 << ", " << std::endl;

	return 0;
}
