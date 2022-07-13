#include <time.h>
// #include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void split1(const std::vector<std::string>& lines) {
	for (auto line : lines) {
		char* pToken = nullptr;

		pToken = std::strtok(&line[0], ",");
		while (pToken != nullptr) {
			pToken = std::strtok(nullptr, ",");
		}
	}
}

void split2(const std::vector<std::string>& lines) {
	for (auto line : lines) {
		std::stringstream ss(line);

		while (ss.good()) {
			std::string substr;
			std::getline(ss, substr, ',');
		}
	}
}

// void split3(const std::vector<std::string>& lines) {
// 	for (auto line : lines) {
// 		std::vector<std::string> strs;
// 		boost::split(strs, line, boost::is_any_of(","));
// 	}
// 	// std::strcspn("", ",");
// }
int main() {
	// prepare
	std::vector<std::string> lines;
	for (int i = 0; i < 10000000; i++) {
		std::string line = std::to_string(i) + "," + std::to_string(i + 1) +
		                   "," + std::to_string(i + 2);
		lines.emplace_back(line);
	}

	// split1
	clock_t start1 = clock();
	split1(lines);
	clock_t end1 = clock();

	// split2
	clock_t start2 = clock();
	split2(lines);
	clock_t end2 = clock();

	// std::cout << (double)(end1 - start1) / CLOCKS_PER_SEC << std::endl;
	// std::cout << (double)(end2 - start2) / CLOCKS_PER_SEC << std::endl;

	std::cout << (end1 - start1) << std::endl;
	std::cout << (end2 - start2) << std::endl;
}

// link: --std=c++11 -Wall -O3 -lboost
