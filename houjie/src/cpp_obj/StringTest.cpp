#include "String.h"

int main(int argc, char const *argv[]) {
	String s1 = "this is s1";
	String s2(s1);
	std::cout << "s2:" << s2 << std::endl;
	String s3("hello");
	std::cout << "s3:" << s3 << std::endl;
	String s4 = s1;
	std::cout << "s4:" << s4 << std::endl;
	s3 = s1;
	std::cout << "s3:" << s3 << std::endl;
	return 0;
}
