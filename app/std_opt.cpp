
#include <stdio.h>
#include <boost/algorithm/string/predicate.hpp>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

// std::remove_reference
template <typename T1, typename T2>
void print_is_same() {
	std::cout << std::is_same<T1, T2>() << '\n';
}

int main() {
	// std::allocator
	{
		// https://en.cppreference.com/w/cpp/memory/allocator
		std::allocator<int> alloc;
		using traits_t = std::allocator_traits<decltype(alloc)>;
		int *p = traits_t::allocate(alloc, 1);
		*p = 100;
		std::cout << p << std::endl;
		std::cout << *p << std::endl;

		traits_t::deallocate(alloc, p, 1);
	}

	// std::remove_reference
	{
		// https://en.cppreference.com/w/cpp/types/remove_reference
		std::cout << std::boolalpha;

		print_is_same<int, int>();
		print_is_same<int, int &>();
		print_is_same<int, int &&>();
		print_is_same<int, std::remove_reference<int &>::type>();
		print_is_same<int, std::remove_reference<int &&>::type>();
	}

	// rebind_traits

	// fscanf
	{
		char str1[10], str2[10], str3[10];
		int year;
		FILE *fp;

		fp = fopen("temp.txt", "w+");
		fputs("We are in 2014", fp);

		rewind(fp);
		fscanf(fp, "%s %s %s %d", str1, str2, str3, &year);

		printf("Read String1 |%s|\n", str1);
		printf("Read String2 |%s|\n", str2);
		printf("Read String3 |%s|\n", str3);
		printf("Read Integer |%d|\n", year);

		fclose(fp);
	}

	// strcmp
	{
		const char *str1 = "hello";
		const char *str2 = "hello";
		int ret = strcmp(str1, str2);  // if eq, ret == 0
		std::cout << str1 << "==" << str2 << " ? " << ret << "\n";
	}
	// std::is_same
	{
		std::cout << std::is_same<int, int32_t>::value << "\n";
		int i = 10;
		std::cout << std::is_same<int, std::string>::value << "\n";
	}
	// boost::istarts_with
	{
		std::string line = "abcd";
		// std::cout << boost::istarts_with(line, "abc");
	}

	// traits_::allocator_type

	// __sync_fetch_and_add
	{}

	// std::memory_order_relaxed
	{}
}

// //link: -lboost