#ifndef BASE
#define BASE

#include <iostream>
#include <vector>

bool isSort(const std::vector<int>& arr) {
	for (int i = 0; i < arr.size() - 1; i++) {
		if (arr[i] > arr[i + 1])
			return false;
	}
	return true;
}

void print(const std::vector<int>& arr) {
	for (auto& item : arr) {
		std::cout << item << " ";
	}
	std::cout << std::endl;
}
#endif
