#include <folly/Uri.h>
#include <iostream>

int main(int argc, char const *argv[]) {
	folly::Uri uri("hdfs://127.0.0.1:9200/database1/table1");

	std::cout << uri.host() << std::endl;
	std::cout << uri.port() << std::endl;
	std::cout << uri.path() << std::endl;

	return 0;
}

// link:-lfolly -ldouble-conversion -lboost_regex