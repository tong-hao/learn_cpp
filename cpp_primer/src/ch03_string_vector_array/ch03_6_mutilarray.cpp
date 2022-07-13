#include <iostream>

int main(int argc, char const *argv[])
{
	int arr[3][5] = {
		{1,2,3,4,5},
		{1,2,3,4,5},
		{1,2,3,4,5}
	};
	
	arr[2][2] = 22;
	arr[1][4] = 14;


	for(auto &a : arr){
		for(auto &i : a){
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
