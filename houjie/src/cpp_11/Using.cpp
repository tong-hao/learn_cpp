#include <iostream>
#include <string>

// using
// using 可以用在三个地方:
// 1）namespace 和 namespace members
using namespace std;
using std::cout;

// 2) class members
class A {
protected:
	using str = std::string;
};

// 3) type alias 和 alias template
// Alias Template(化名)
template <typename T>
using Vec = std::vector<T, MyAlloc<T>>;

// type alias(similar to typedef)
typedef void (*func)(int, int);
using func = void (*)(int, int);
typedef basic_string<char> string;

// 一个小例子
namespace {
template <typename Container>
void test_moveable(Container c) {
	typedef typename iterator_traits<typename Container::iterator>::value_type
	    Valtype;

	for (long i = 0; i < SIZE; ++i)
		c.insert(c.end(), Valtype());
	Container c1(c);
	Container c2(std::move(c1));
	c1.swap(c2);
}

// test_moveable(std::list<std::string>());
// test_moveable(std::vector<std::string>());

}  // namespace
