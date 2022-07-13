#include <array>
#include <iostream>
#include <algorithm>
#include <assert.h>
// 数组



template<typename Container>
void print(Container c){
	for(auto iter = c.begin(); iter < c.end(); iter++) {
		std::cout << *iter << " ";
	}

	std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
	std::array<int, 3> arr;
	arr[0] = 1;
	arr[1] = 4;
	arr[2] = 7;

	print(arr);

}