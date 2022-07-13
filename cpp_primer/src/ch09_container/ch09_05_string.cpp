#include <string>
#include <iostream>
#include <algorithm>
#include <assert.h>




template<typename Container>
void print(Container c){
	for(auto iter = c.begin(); iter < c.end(); iter++) {
		std::cout << *iter << " ";
	}

	std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
	// substr
	std::string str = "0123456789";
	std::string sub1 = str.substr(0, 3);
	std::string sub2 = str.substr(1, 3);
	print(sub1);
	print(sub2);

	// insert
	str.insert(0, "a");
	print(str);

	// del
	str.erase(1, 3); // 从位置1开始，删除3个元素
	print(str);

	// replace
	str.replace(1, 3, "del"); // erase + insert
	str.append(" end;");
	print(str);

	// find
	std::cout << str.find("end") << std::endl;

	// to int
	std::string str2 = "65535";
	auto i = stoi(str2);
	assert(i == 65535);






}