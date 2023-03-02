#include "base.h"

// 从第2个开始找个最小的，与第1个交换
// 从第3个开始找个最小的，与低2个交换
void selectSort(std::vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		int min = i;

		for (int j = i; j < arr.size(); j++) {
			if (arr[j] < arr[min])
				min = j;
		}
		if (i != min) {
			std::swap(arr[i], arr[min]);
		}
	}
}

int main() {
	std::vector<int> arr{1, 3, 5, 2, 6, 4};

	selectSort(arr);
	isSort(arr);
	print(arr);
	return 0;
}
