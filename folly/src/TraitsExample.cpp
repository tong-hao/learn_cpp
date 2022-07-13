#include <folly/Traits.h>
#include <iostream>
#include <string>

template <class T1, class T2>
class MyParameterizedType;

class MySimpleType;

/* Definition of My*Type goes here */
// global namespace (not inside any namespace)
namespace folly {
// defining specialization of IsRelocatable for MySimpleType
template <>
struct IsRelocatable<MySimpleType> : std::true_type {};

// defining specialization of IsRelocatable for MyParameterizedType
template <class T1, class T2>
struct IsRelocatable<MyParameterizedType<T1, T2>>
	        : ::std::true_type {};
}


int main(int argc, char const *argv[])
{
	std::cout << std::boolalpha;

	std::cout << folly::IsRelocatable<MySimpleType>::value << std::endl;
	std::cout << folly::IsRelocatable<MyParameterizedType<int, int>>::value << std::endl;

	return 0;
}