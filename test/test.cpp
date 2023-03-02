#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class Base {
public:
	Base() : count(1) {
	}

protected:
	int count;
};

template <typename T>
class Sub : public Base<T> {
public:
	int get_count() {
		return ++Base<T>::count;
	}
};

int main() {
	Sub<int> sub;
	std::cout << sub.get_count() << std::endl;
	std::cout << sub.get_count() << std::endl;
	return 0;
}
