#include <map>
#include <set>
#include <string>

// decltype
std::map<std::string, float> coll;
decltype(coll)::value_type elem;  // map<string,float>::value_type

// 应用1: return
template <typename T1, typename T2>
auto add(T1 x, T2 y) -> decltype(x + y);

// 应用 2: metaprogramming
template <typename T>
void test(T obj) {
	typedef typename T::iterator type1;
	typedef typename decltype(obj)::iterator type2;

	decltype(obj) obj2(obj);
}

// 应用 3: lambda
auto cmp = []() {};
std::set<std::string, decltype(cmp)> coll(cmp);
