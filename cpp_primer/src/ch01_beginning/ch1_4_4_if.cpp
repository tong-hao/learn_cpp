#include <iostream>

int main() {

	


	//1.4.4
	int value;
	int currentValue;
	if(std::cin >> currentValue) {
		int num = 0;
		while(std::cin >> value) {
			if(value == currentValue) {
				++num;
			} else {
				std::cout << currentValue << "occurs " << num << " times." << std::endl;
				num = 1;
				currentValue = value;
			}
		}
	}

	return 0;
}
