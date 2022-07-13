#include <functional>
#include <iostream>
#include <string>

int main() {
	std::string str = "hello";
	std::hash<std::string> hasher;

	std::cout << hasher(str) << std::endl;
}
