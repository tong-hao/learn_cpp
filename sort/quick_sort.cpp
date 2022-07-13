#include <iostream>

using namespace std;

void print(int arr[], int len) {
	for (int i = 0; i < len; i++) {
		cout << arr[i] << "\t";
	}
	cout << endl;
}

void quick_sort(int arr[], int low, int high) {
	if (low >= high) {
		return;
	}

	int i = low;
	int j = high;

	int temp = arr[i];
	cout << "temp=" << temp << ",low=" << low << ",high=" << high << endl;
	cout << "begin:->";
	print(arr, 10);

	while (i != j) {
		while (arr[j] >= temp && j > i) {
			j--;
		}
		if (j > i) {
			arr[i] = arr[j];
			i++;
		}

		while (arr[i] < temp && j > i) {
			i++;
		}
		if (j > i) {
			arr[j] = arr[i];
			j--;
		}
		cout << "     :->";
		print(arr, 10);
	}
	arr[i] = temp;
	cout << "  end:->";
	print(arr, 10);
	cout << endl;

	quick_sort(arr, low, i - 1);
	quick_sort(arr, i + 1, high);
}

int main(int argc, char const *argv[]) {
	int arr[] = {9, 8, 17, 6, 11, 4, 3, 12, 1, 0};
	print(arr, 10);
	quick_sort(arr, 0, 9);
	print(arr, 10);

	return 0;
}
