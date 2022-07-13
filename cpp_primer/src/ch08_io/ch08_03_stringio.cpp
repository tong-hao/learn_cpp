#include <sstream>
#include <string>
#include <iostream>
#include <assert.h>

int main(int argc, char const *argv[])
{
	// to stringstream
	std::ostringstream os;
	os << "hello " << 1 << true;

	auto str = os.str();
	std::cout << str << std::endl;

	// from stringstream
	std::istringstream is("hello word \n 1 2 3");
	std::string word;
	while(is) {
		is >> word;
		std::cout << word << std::endl;
	}
	
	


	return 0;
}
