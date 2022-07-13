#include <iostream>

int main(int argc, char const *argv[])
{
	int arr[10] = {1,2,3};
	arr[6] = 7;

	for(auto i : arr){
		std::cout << i << std::endl;
	}

	// point
	int *p1 = std::begin(arr);
	int *p2 = std::end(arr);
	while(p1 != p2) {
		std::cout << *p1 << std::endl;
		p1++;
	}
	p1[1];

	return 0;
}
