#include <iostream>
#include <fstream>
#include <assert.h>

int main(int argc, char const *argv[]) {
	// 1. state
	auto& input = std::cin;

	// four states
	assert(input.good() == true);
	std::cout << input.eof() << std::endl << input.fail() << std::endl << input.bad();

	// get and set state
	auto state = input.rdstate();
	input.setstate(state);

	// 2. tree flush way
	auto& output = std::cout;
	output << "flush" << std::flush;
	output << "flush" << std::endl;
	output << "flush\n" << std::ends;

	// 3. tie
	{
		std::ostream *prevstr;
		std::ofstream ofs;
		ofs.open ("test.txt");

		std::cout << "tie example:\n";
		*std::cin.tie() << "This is inserted into cout\n";
		prevstr = std::cin.tie (&ofs);
		*std::cin.tie() << "This is inserted into the file";
		std::cin.tie (prevstr);

		ofs.close();
	}


	return 0;
}