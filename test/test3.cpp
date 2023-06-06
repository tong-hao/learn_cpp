#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;
union MyUnion {
	int a;
	float b;
};

int main() {
	MyUnion u1{1};
	MyUnion u2;
	u2.b = 1;

	std::cout << u1.a << std::endl;
	std::cout << u1.b << std::endl;

	return 0;
}
