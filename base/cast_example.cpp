#include <iostream>
#include <string>

void Write(std::string& ret, int32_t i) {
	char* p = reinterpret_cast<char*>(&i);

	int size = 0;
	char* p2 = p;
	while (p != nullptr) {
		std::cout << "Write:" << *p << std::endl;
		if (*p == '\0')break;
		++p;
		++size;
	}
	std::cout << "size:" << size << std::endl;
	for (int i = 0; i < sizeof(int32_t) - size; i++) {
		char cc = 0;
		ret.append(&cc, 1);
	}

	ret.append(p2, size);
}

int32_t ReadInt32(std::string& encoding_str) {
	std::cout << "begin: ReadInt32" << std::endl;
	std::cout << "encoding_str:" << encoding_str << ",len=" << encoding_str.length() << std::endl;

	int i =0;
	auto* p = encoding_str.data();
	while (i < 4) {
		std::cout << *p << std::endl;

		const int8_t* pi = reinterpret_cast<const int8_t*>(p);
		std::cout << "cast result:"<< std::dec << *pi << std::endl;
		std::cout << "1)" << std::hex << 10 << " " << std::dec << 10 << " " << std::oct << 10 << std::endl;

		++p;
		++i;
	}

	auto ret = *reinterpret_cast<const int32_t*>(encoding_str.data());
	std::cout << "ret:" << ret << std::endl;

	auto sub = encoding_str.erase(0, sizeof(int32_t));
	std::cout << "sub:" << sub << ",len=" << sub.length() << std::endl;

	std::cout << "end: ReadInt32" << std::endl;
	return ret;
}

int main(int argc, char const *argv[])
{

	// static_cast 用于进行比较“自然”和低风险的转换，如整型和浮点型、字符型之间的互相转换
	int8_t i = static_cast <int> (3.14);
	std::cout << "static_cast <int> (3.14) is " << i << std::endl;

	// reinterpret_cast 用于进行各种不同类型的指针之间、不同类型的引用之间以及指针和能容纳指针的整数类型之间的转换。
	for (i = 0; i < 100; i++) {
		char* c = reinterpret_cast<char*>(&i);
		std::cout << i << "=>" << *c << std::endl;

		int8_t* pi = reinterpret_cast<int8_t*>(c);
		std::cout << (i == *pi) << std::endl;
	}


// const_cast 运算符仅用于进行去除 const 属性的转换
	const std::string s1 = "hello";
	std::string& s2 = const_cast<std::string&>(s1);
	std::cout << s2 << std::endl;

// dynamic_cast专门用于将多态基类的指针或引用强制转换为派生类的指针或引用，而且能够检查转换的安全性。
	class Base
	{
	public:
		virtual ~Base() {}
	};
	class Derived : public Base { };
	Base b;
	Derived d;
	Derived* pd;
	pd = reinterpret_cast<Derived*>(&b);
	std::cout << "reinterpret_cast is null ? " << (pd == nullptr) << std::endl;


	//
	std::cout << "-------------------" << std::endl;
	int32_t t1 = 8;
	std::string ret;
	Write(ret, t1);
	std::cout << sizeof(ret) << ":" << ret << std::endl;
	int32_t t2 = ReadInt32(ret);
	std::cout << sizeof(t2) << ",t1==t2?" << (t1 == t2) << std::endl;
	std::cout << t1 << std::endl;
	std::cout << t2 << std::endl;
	std::cout << "-------------------" << std::endl;




	return 0;
}
