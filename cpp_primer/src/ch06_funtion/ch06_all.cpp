#include <iostream>
#include <string>

void m1() {
	std::cout << "m1()" << std::endl;
}

void m1(std::string str) {
	std::cout << "m1(std::string str)" << std::endl;
}

void m1(const std::string* str) {
	std::cout << "m1(std::string* str)" << std::endl;
}

void error_msg(std::initializer_list<std::string> il) {
	for (auto iter = il.begin(); iter != il.end(); iter++) {
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
}

// 返回数组指针
using arr = int[10];
arr* getArray(int num){
	int array[10] = {1,3,1};
	int (*p)[10] = &array;
	return p;
}

auto getArray2() -> int(*)[10] {
	int array[10] = {1,3,1};
	int (*p)[10] = &array;
	return p;
}

int arr3[10];
decltype(arr3) *getArray3() {
	int array[10] = {1,3,1};
	int (*p)[10] = &array;
	return p;
}

int print1(std::string& str){
	std::cout << str << std::endl;
	return 1;
}


int main(int argc, char const *argv[]) {

	std::cout << argv[0] << std::endl;

	m1();

	std::string s1 = "abc";
	m1(s1);

	const std::string s2 = "abc";
	m1(&s2);

	std::string msg1 = "err1";
	error_msg({msg1, "err2"});


	// getArray
	int num = 10;
	auto* p = getArray(num);
	for(int i =0; i < num; i++) {
		std::cout << *p << " ";
		++p;
	}
	std::cout << std::endl;

	// 函数指针: 一个指针指向函数而不是一个对象
	int (*pf)(std::string& str);
	pf = print1;
	std::string hello = "hello";
	pf(hello);


	return 0;
}