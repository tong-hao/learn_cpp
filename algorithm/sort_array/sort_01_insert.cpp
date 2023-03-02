#include "base.h"

// 算法描述：
// 就像对扑克牌排序一样
// 1) 用第二张与第一张比较，并排序
// 2）用第三张 分别与 第 2,1张比较，并排序
void insertSort(std::vector<int>& arr) {
	for (int i = 1; i < arr.size(); i++) {
		for (int j = i; j >= 1; j--) {
			if (arr[j] < arr[j - 1]) {
				std::swap(arr[j], arr[j - 1]);
			}
		}
	}
}

int main(int argc, char const* argv[]) {
	std::vector<int> arr{1, 3, 5, 2, 6, 4};

	insertSort(arr);
	isSort(arr);
	print(arr);
	return 0;
}
