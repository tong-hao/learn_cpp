#include <iostream>

int main(int argc, char const *argv[])
{
	// 引用==别名
	int i = 0;
	int &r_i = i;
	r_i = 1;
	std::cout << "i=" << i << ", r_i=" << r_i;

	

	return 0;
}
