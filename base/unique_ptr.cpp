#include <iostream>
#include <memory>

int main(int argc, char const *argv[])
{
	
	std::unique_ptr<int> p1 = std::make_unique<int>(5);
	//auto p2 = p1; //error
	auto p2 = std::move(p1);

	std::cout << (p1 == nullptr) << std::endl;
	std::cout << *p2<< std::endl;



	return 0;
}