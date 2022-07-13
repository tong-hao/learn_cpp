#include <iostream>
#include <memory>

struct MyInt{
	int value;
};

int main(int argc, char const *argv[])
{
	std::shared_ptr<MyInt> p1 = std::make_shared<MyInt>();
	auto p2 = p1;
	p2->value = 6;

	auto p3 = std::move(p1);


	std::cout << (p1 == nullptr) << std::endl;
	std::cout << p2->value << std::endl;
	std::cout << p3->value << std::endl;

	return 0;
}