#include <iostream>

int main() {

	// 1.4.1
	int sum = 0, i = 1;
	while (i <= 10) {

		// error: sum =+ i;

		sum += i;
		++i;
	}

	std::cout << "sum of 1 to 10 :" << sum << std::endl;

	//1.4.2
	sum = 0;
	for (int i = 1; i <= 10; i++) {
		sum += i;
	}
	std::cout << "sum of 1 to 10 :" << sum << std::endl;

	
	//1.4.3
	sum = 0;
	int value;
	while(std::cin >> value) {
		sum += value;
	}
	std::cout << "The sum is :" << sum << std::endl;


	//1.4.4
	int currentValue;
	if(std::cin >> currentValue) {
		int num = 0;
		while(std::cin >> value) {
			if(value == currentValue) {
				++num;
			} else {
				std::cout << currentValue << "occurs " << num << " times." << std::endl;
				num = 1;
				currentValue == value;
			}
		}
	}

	return 0;
}
