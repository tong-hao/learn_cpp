#include <string>

// noexcept
void foo() noexcept;
void foo() noexcept(true);
void swap(std::string x, std::string y) noexcept(noexcept(x.swap(y))) {
	x.swap(y);
}

// 注意：vector的move需要你的类的移动构造和移动赋值声明为noexcept，不然vector是不敢用的。
class MyString {
public:
	MyString(MyString&& str) noexcept {  // 注意 noexcept
		                                 //…
	}
	MyString& operator=(MyString&& str) noexcept {  // 注意 noexcept
		//…
		return *this;
	}
};
