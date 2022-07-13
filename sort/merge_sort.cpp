
#include <iostream>

using namespace std;

void print(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void merge(int arr[], int l, int m, int r) {
	int cp[r - l + 1];
	for (int i = 0; i < r - l + 1; i++) {
		cp[i] = arr[l + i];
	}

	int i = l;
	int j = m + 1;
	for (int k = l; k <= r; k++) {
		if (j > r) {
			arr[k] = cp[i - l];
			i++;
		} else if (i > m) {
			arr[k] = cp[j - l];
			j++;
		} else if (cp[i - l] < cp[j - l]) {
			arr[k] = cp[i - l];
			i++;
		} else {
			arr[k] = cp[j - l];
			j++;
		}
	}
	print(arr, 10);
}

void merge_sort(int arr[], int len) {
	for (int group_size = 1; group_size <= len; group_size += group_size) {
		cout << "group_size=" << group_size << endl;
		for (int i = 0; i - group_size < len; i += 2 * group_size) {
			cout << "i=" << i << endl;
			merge(arr, i, i + group_size - 1, min(i + 2 * group_size - 1, len));
		}
	}
}

int main() {
	int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	print(arr, 10);
	merge_sort(arr, 10);
	print(arr, 10);

	return 0;
}