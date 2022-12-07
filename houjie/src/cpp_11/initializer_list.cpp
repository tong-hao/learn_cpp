#include <initializer_list>
#include <iostream>

// initializer_list
void print(std::initializer_list<int> vals) {
	for (auto p = vals.begin(); p != vals.end(); ++p) {
		std::cout << *p << std::endl;
	}
}

class P {
public:
	P(int, int) {
	}  // 构造1

	P(std::initializer_list<int>) {
	}  // 构造2
};

int main(int argc, char const *argv[]) {
	P p1(1, 2);
	P p2{1, 2};     // 按包传，如果没有构造2，则调用构造1
	P p3 = {1, 2};  // 按包传
	return 0;
}
