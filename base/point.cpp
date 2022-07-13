#include <iostream>

void change(int* p){
	*p = 5;
}

int main(int argc, char const *argv[])
{
	int a = 1;
	int i = a;
	change(&i);
	std::cout << i << std::endl;

	return 0;
}