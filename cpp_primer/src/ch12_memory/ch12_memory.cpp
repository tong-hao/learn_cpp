#include <memory>
#include <iostream>

int main(int argc, char const *argv[])
{
	// unique
	std::unique_ptr<std::string> p1(new std::string("abc"));// error:std::make_unique<std::string>("abc");
	std::cout << *p1 << std::endl;
	std::cout << p1->size() << std::endl;
	p1.release();
	p1.reset(new std::string("hello"));
	std::unique_ptr<std::string> p11;
	p11.reset(p1.release());

	// shared
	std::shared_ptr<std::string> p2 = std::make_shared<std::string>("abc");// abc是构造参数
	std::cout << *p2 << std::endl;
	std::cout << p2->size() << std::endl;
	std::shared_ptr<std::string> p21;
	p21 = p2;
	std::cout << "use_count:" << p2.use_count() << std::endl;
	std::cout << "use_count:" << p21.use_count() << std::endl;
	p21 = nullptr;
	std::cout << "use_count:" << p2.use_count() << std::endl;
	std::cout << "use_count:" << p21.use_count() << std::endl;
	std::cout << p2.unique() << std::endl;

	// weak_ptr
	std::weak_ptr<std::string> p3(p2);
	auto p31 = p3.lock();
	if(p31) {
		std::cout << "week, size:" << p31->size() << std::endl;
	}

	// array
	std::string* p4 = new std::string[2]{"hello", "abc"};
	std::string* p41 = new std::string[2]; // uninited
	std::string* p42 = new std::string[2](); // inited with empty string
	delete [] p4; /// note: delete a array


	// 
	std::unique_ptr<std::string[]> p6(new std::string[10]);
	p6[1] = "string1";
	p6.release();

	std::shared_ptr<std::string> p5(new std::string[10], [](std::string* p){delete[] p;});
	*(p5.get() + 1) = "hello";
	p5.reset();

	// typedef array
	typedef int arrT[5];
	int* p7 = new arrT; // arrT == int[5]


	return 0;
}